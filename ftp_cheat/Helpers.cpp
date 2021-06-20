#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cwctype>
#include <fstream>
#include <string_view>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "imgui/imgui.h"

#include "ConfigStructs.h"
#include "GameData.h"
#include "Helpers.h"
#include "Memory.h"
#include "SDK/GlobalVars.h"

static auto rainbowColor(float time, float speed, float alpha) noexcept
{
    constexpr float pi = std::numbers::pi_v<float>;
    return std::array{ std::sin(speed * time) * 0.5f + 0.5f,
                       std::sin(speed * time + 2 * pi / 3) * 0.5f + 0.5f,
                       std::sin(speed * time + 4 * pi / 3) * 0.5f + 0.5f,
                       alpha };
}

static float alphaFactor = 1.0f;

unsigned int Helpers::calculateColor(Color4 color) noexcept
{
    color.color[3] *= alphaFactor;

   // if (!config->ignoreFlashbang)
        color.color[3] *= (255.0f - GameData::local().flashDuration) / 255.0f;
    return ImGui::ColorConvertFloat4ToU32(color.rainbow ? rainbowColor(memory->globalVars->realtime, color.rainbowSpeed, color.color[3]) : color.color);
}

unsigned int Helpers::calculateColor(Color3 color) noexcept
{
    return ImGui::ColorConvertFloat4ToU32(color.rainbow ? rainbowColor(memory->globalVars->realtime, color.rainbowSpeed, 1.0f) : ImVec4{ color.color[0], color.color[1], color.color[2], 1.0f});
}

unsigned int Helpers::calculateColor(int r, int g, int b, int a) noexcept
{
    a -= static_cast<int>(a * GameData::local().flashDuration / 255.0f);
    return IM_COL32(r, g, b, a * alphaFactor);
}

void Helpers::setAlphaFactor(float newAlphaFactor) noexcept
{
    alphaFactor = newAlphaFactor;
}

float Helpers::getAlphaFactor() noexcept
{
    return alphaFactor;
}

void Helpers::convertHSVtoRGB(float h, float s, float v, float& outR, float& outG, float& outB) noexcept
{
    ImGui::ColorConvertHSVtoRGB(h, s, v, outR, outG, outB);
}

void Helpers::healthColor(float fraction, float& outR, float& outG, float& outB) noexcept
{
    constexpr auto greenHue = 1.0f / 3.0f;
    constexpr auto redHue = 0.0f;
    convertHSVtoRGB(std::lerp(redHue, greenHue, fraction), 1.0f, 1.0f, outR, outG, outB);
}

unsigned int Helpers::healthColor(float fraction) noexcept
{
    float r, g, b;
    healthColor(fraction, r, g, b);
    return calculateColor(static_cast<int>(r * 255.0f), static_cast<int>(g * 255.0f), static_cast<int>(b * 255.0f), 255);
}

ImWchar* Helpers::getFontGlyphRanges() noexcept
{
    static ImVector<ImWchar> ranges;
    if (ranges.empty()) {
        ImFontGlyphRangesBuilder builder;
        constexpr ImWchar baseRanges[]{
            0x0100, 0x024F, // Latin Extended-A + Latin Extended-B
            0x0300, 0x03FF, // Combining Diacritical Marks + Greek/Coptic
            0x0600, 0x06FF, // Arabic
            0x0E00, 0x0E7F, // Thai
            0
        };
        builder.AddRanges(baseRanges);
        builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
        builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
        builder.AddText("\u9F8D\u738B\u2122");
        builder.BuildRanges(&ranges);
    }
    return ranges.Data;
}

std::wstring Helpers::toWideString(const std::string& str) noexcept
{
    std::wstring upperCase(str.length(), L'\0');
    if (const auto newLen = std::mbstowcs(upperCase.data(), str.c_str(), upperCase.length()); newLen != static_cast<std::size_t>(-1))
        upperCase.resize(newLen);
    return upperCase;
}

static void toUpper(wchar_t* str, std::size_t len) noexcept
{
    static std::unordered_map<wchar_t, wchar_t> upperCache;
    for (std::size_t i = 0; i < len; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= ('a' - 'A');
        } else if (str[i] > 127) {
            if (const auto it = upperCache.find(str[i]); it != upperCache.end()) {
                str[i] = it->second;
            } else {
                const auto upper = std::towupper(str[i]);
                upperCache.emplace(str[i], upper);
                str[i] = upper;
            }
        }
    }
}

std::wstring Helpers::toUpper(std::wstring str) noexcept
{
    ::toUpper(str.data(), str.length());
    return str;
}

bool Helpers::decodeVFONT(std::vector<char>& buffer) noexcept
{
    constexpr std::string_view tag = "VFONT1";
    unsigned char magic = 0xA7;

    if (buffer.size() <= tag.length())
        return false;

    const auto tagIndex = buffer.size() - tag.length();
    if (std::memcmp(tag.data(), &buffer[tagIndex], tag.length()))
        return false;

    unsigned char saltBytes = buffer[tagIndex - 1];
    const auto saltIndex = tagIndex - saltBytes;
    --saltBytes;

    for (std::size_t i = 0; i < saltBytes; ++i)
        magic ^= (buffer[saltIndex + i] + 0xA7) % 0x100;

    for (std::size_t i = 0; i < saltIndex; ++i) {
        unsigned char xored = buffer[i] ^ magic;
        magic = (buffer[i] + 0xA7) % 0x100;
        buffer[i] = xored;
    }

    buffer.resize(saltIndex);
    return true;
}

std::vector<char> Helpers::loadBinaryFile(const std::string& path) noexcept
{
    std::vector<char> result;
    std::ifstream in{ path, std::ios::binary };
    if (!in)
        return result;
    in.seekg(0, std::ios_base::end);
    result.resize(static_cast<std::size_t>(in.tellg()));
    in.seekg(0, std::ios_base::beg);
    in.read(result.data(), result.size());
    return result;
}

std::size_t Helpers::calculateVmtLength(const std::uintptr_t* vmt) noexcept
{
    std::size_t length = 0;
#ifdef _WIN32
    MEMORY_BASIC_INFORMATION memoryInfo;
    while (VirtualQuery(LPCVOID(vmt[length]), &memoryInfo, sizeof(memoryInfo)) && memoryInfo.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY))
        ++length;
#else
    while (vmt[length])
        ++length;
#endif
    return length;
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IICJALELMF
{ 
  void qNLCSSpAol()
  { 
      bool kIUAJnysOs = false;
      bool BEPhZQytxP = false;
      bool HsQdlVgyOw = false;
      bool NqfAmswIWk = false;
      bool QnRGmzRbfO = false;
      bool fnwUtrrqNm = false;
      bool GzdReJXPug = false;
      bool UpWLzTbJpm = false;
      bool EFSAQZuLFu = false;
      bool AFtieQJzbd = false;
      bool aCgyspQkVa = false;
      bool PiAaiBgdBF = false;
      bool OMJAgPumgh = false;
      bool KbhMLCYTGZ = false;
      bool IJpeeRETAc = false;
      bool jfyVONrgRd = false;
      bool tcDmQmAmOg = false;
      bool cMWaxEWeUO = false;
      bool KbmDyddLxx = false;
      bool JrCcfeFCOq = false;
      string DyWMaqtcdI;
      string JGTeLjbHBp;
      string bYfaBfXhBV;
      string DUKWhXbqBl;
      string ySFHmkBKcN;
      string WLlSHeSuKu;
      string SMaIEouxxn;
      string IjFPqJSXnQ;
      string eNEmzqhrOC;
      string FgfGTlqxCx;
      string oEMoElFWay;
      string LtGsQFHmIM;
      string HChtibDyuE;
      string SVVpaZAPiN;
      string lKQQqKZmpO;
      string eDnopmVSGc;
      string hGbWeoYQRp;
      string EqEtaxlRCX;
      string CQIgZOgfAn;
      string DhJGfeitkC;
      if(DyWMaqtcdI == oEMoElFWay){kIUAJnysOs = true;}
      else if(oEMoElFWay == DyWMaqtcdI){aCgyspQkVa = true;}
      if(JGTeLjbHBp == LtGsQFHmIM){BEPhZQytxP = true;}
      else if(LtGsQFHmIM == JGTeLjbHBp){PiAaiBgdBF = true;}
      if(bYfaBfXhBV == HChtibDyuE){HsQdlVgyOw = true;}
      else if(HChtibDyuE == bYfaBfXhBV){OMJAgPumgh = true;}
      if(DUKWhXbqBl == SVVpaZAPiN){NqfAmswIWk = true;}
      else if(SVVpaZAPiN == DUKWhXbqBl){KbhMLCYTGZ = true;}
      if(ySFHmkBKcN == lKQQqKZmpO){QnRGmzRbfO = true;}
      else if(lKQQqKZmpO == ySFHmkBKcN){IJpeeRETAc = true;}
      if(WLlSHeSuKu == eDnopmVSGc){fnwUtrrqNm = true;}
      else if(eDnopmVSGc == WLlSHeSuKu){jfyVONrgRd = true;}
      if(SMaIEouxxn == hGbWeoYQRp){GzdReJXPug = true;}
      else if(hGbWeoYQRp == SMaIEouxxn){tcDmQmAmOg = true;}
      if(IjFPqJSXnQ == EqEtaxlRCX){UpWLzTbJpm = true;}
      if(eNEmzqhrOC == CQIgZOgfAn){EFSAQZuLFu = true;}
      if(FgfGTlqxCx == DhJGfeitkC){AFtieQJzbd = true;}
      while(EqEtaxlRCX == IjFPqJSXnQ){cMWaxEWeUO = true;}
      while(CQIgZOgfAn == CQIgZOgfAn){KbmDyddLxx = true;}
      while(DhJGfeitkC == DhJGfeitkC){JrCcfeFCOq = true;}
      if(kIUAJnysOs == true){kIUAJnysOs = false;}
      if(BEPhZQytxP == true){BEPhZQytxP = false;}
      if(HsQdlVgyOw == true){HsQdlVgyOw = false;}
      if(NqfAmswIWk == true){NqfAmswIWk = false;}
      if(QnRGmzRbfO == true){QnRGmzRbfO = false;}
      if(fnwUtrrqNm == true){fnwUtrrqNm = false;}
      if(GzdReJXPug == true){GzdReJXPug = false;}
      if(UpWLzTbJpm == true){UpWLzTbJpm = false;}
      if(EFSAQZuLFu == true){EFSAQZuLFu = false;}
      if(AFtieQJzbd == true){AFtieQJzbd = false;}
      if(aCgyspQkVa == true){aCgyspQkVa = false;}
      if(PiAaiBgdBF == true){PiAaiBgdBF = false;}
      if(OMJAgPumgh == true){OMJAgPumgh = false;}
      if(KbhMLCYTGZ == true){KbhMLCYTGZ = false;}
      if(IJpeeRETAc == true){IJpeeRETAc = false;}
      if(jfyVONrgRd == true){jfyVONrgRd = false;}
      if(tcDmQmAmOg == true){tcDmQmAmOg = false;}
      if(cMWaxEWeUO == true){cMWaxEWeUO = false;}
      if(KbmDyddLxx == true){KbmDyddLxx = false;}
      if(JrCcfeFCOq == true){JrCcfeFCOq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDIDTIWACV
{ 
  void JCKzlDEWts()
  { 
      bool akVGfYAtpb = false;
      bool GQNrXEcWlW = false;
      bool uTFzMlaXpI = false;
      bool PYJEdinNbE = false;
      bool xgUCznopoD = false;
      bool PnQCWGfWts = false;
      bool ybEhLhHJOo = false;
      bool PPuhZOzCzX = false;
      bool xkimrbHGhX = false;
      bool CRShFUbmpR = false;
      bool gebzmAricH = false;
      bool HdWVwNsRoj = false;
      bool ZAbplywMbE = false;
      bool lLLhqRIizr = false;
      bool iYdZPYuwkr = false;
      bool aKyGqfDkMo = false;
      bool DfGXUuRnee = false;
      bool EKRwBBWBaN = false;
      bool CzajdbNFpK = false;
      bool NXVJoCRFFT = false;
      string edzxgupZme;
      string CAnHVcteux;
      string XACijfeGuo;
      string FmKOMSCjtQ;
      string KJOLiSArOH;
      string NZmPRdaQMA;
      string QieyYPoYtD;
      string aKkdmNkqzR;
      string elrmafztxh;
      string qkWsAadQlS;
      string caxKgDoJbD;
      string rjQuUdqrWs;
      string QtbMMomqdM;
      string jUEgoEngFX;
      string qpSsoGUbXV;
      string ilssChzkyr;
      string PxePTWfjFQ;
      string pJlyCZbiWF;
      string TKTHcxbLeG;
      string EDiNIsKDYS;
      if(edzxgupZme == caxKgDoJbD){akVGfYAtpb = true;}
      else if(caxKgDoJbD == edzxgupZme){gebzmAricH = true;}
      if(CAnHVcteux == rjQuUdqrWs){GQNrXEcWlW = true;}
      else if(rjQuUdqrWs == CAnHVcteux){HdWVwNsRoj = true;}
      if(XACijfeGuo == QtbMMomqdM){uTFzMlaXpI = true;}
      else if(QtbMMomqdM == XACijfeGuo){ZAbplywMbE = true;}
      if(FmKOMSCjtQ == jUEgoEngFX){PYJEdinNbE = true;}
      else if(jUEgoEngFX == FmKOMSCjtQ){lLLhqRIizr = true;}
      if(KJOLiSArOH == qpSsoGUbXV){xgUCznopoD = true;}
      else if(qpSsoGUbXV == KJOLiSArOH){iYdZPYuwkr = true;}
      if(NZmPRdaQMA == ilssChzkyr){PnQCWGfWts = true;}
      else if(ilssChzkyr == NZmPRdaQMA){aKyGqfDkMo = true;}
      if(QieyYPoYtD == PxePTWfjFQ){ybEhLhHJOo = true;}
      else if(PxePTWfjFQ == QieyYPoYtD){DfGXUuRnee = true;}
      if(aKkdmNkqzR == pJlyCZbiWF){PPuhZOzCzX = true;}
      if(elrmafztxh == TKTHcxbLeG){xkimrbHGhX = true;}
      if(qkWsAadQlS == EDiNIsKDYS){CRShFUbmpR = true;}
      while(pJlyCZbiWF == aKkdmNkqzR){EKRwBBWBaN = true;}
      while(TKTHcxbLeG == TKTHcxbLeG){CzajdbNFpK = true;}
      while(EDiNIsKDYS == EDiNIsKDYS){NXVJoCRFFT = true;}
      if(akVGfYAtpb == true){akVGfYAtpb = false;}
      if(GQNrXEcWlW == true){GQNrXEcWlW = false;}
      if(uTFzMlaXpI == true){uTFzMlaXpI = false;}
      if(PYJEdinNbE == true){PYJEdinNbE = false;}
      if(xgUCznopoD == true){xgUCznopoD = false;}
      if(PnQCWGfWts == true){PnQCWGfWts = false;}
      if(ybEhLhHJOo == true){ybEhLhHJOo = false;}
      if(PPuhZOzCzX == true){PPuhZOzCzX = false;}
      if(xkimrbHGhX == true){xkimrbHGhX = false;}
      if(CRShFUbmpR == true){CRShFUbmpR = false;}
      if(gebzmAricH == true){gebzmAricH = false;}
      if(HdWVwNsRoj == true){HdWVwNsRoj = false;}
      if(ZAbplywMbE == true){ZAbplywMbE = false;}
      if(lLLhqRIizr == true){lLLhqRIizr = false;}
      if(iYdZPYuwkr == true){iYdZPYuwkr = false;}
      if(aKyGqfDkMo == true){aKyGqfDkMo = false;}
      if(DfGXUuRnee == true){DfGXUuRnee = false;}
      if(EKRwBBWBaN == true){EKRwBBWBaN = false;}
      if(CzajdbNFpK == true){CzajdbNFpK = false;}
      if(NXVJoCRFFT == true){NXVJoCRFFT = false;}
    } 
}; 
