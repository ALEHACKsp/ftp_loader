#include "imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"

#include "imguiCustom.h"
#include "ConfigStructs.h"
#include "InputUtil.h"

void ImGuiCustom::colorPicker(const char* name, float color[3], float* alpha, bool* rainbow, float* rainbowSpeed, bool* enable, float* thickness, float* rounding) noexcept
{
    ImGui::PushID(name);
    if (enable) {
        ImGui::Checkbox("##check", enable);
        ImGui::SameLine(0.0f, 5.0f);
    }
    bool openPopup = ImGui::ColorButton("##btn", ImVec4{ color[0], color[1], color[2], alpha ? *alpha : 1.0f }, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_AlphaPreview);
    if (ImGui::BeginDragDropTarget()) {
        if (alpha) {
            if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F)) {
                std::copy((float*)payload->Data, (float*)payload->Data + 3, color);
                *alpha = 1.0f;
            }
            if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                std::copy((float*)payload->Data, (float*)payload->Data + 4, color);
        } else {
            if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                std::copy((float*)payload->Data, (float*)payload->Data + 3, color);
            if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                std::copy((float*)payload->Data, (float*)payload->Data + 3, color);
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::SameLine(0.0f, 5.0f);
    ImGui::TextUnformatted(name);

    if (openPopup)
        ImGui::OpenPopup("##popup");

    if (ImGui::BeginPopup("##popup")) {
        if (alpha) {
            float col[]{ color[0], color[1], color[2], *alpha }; 
            ImGui::ColorPicker4("##picker", col, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaBar);
            color[0] = col[0];
            color[1] = col[1];
            color[2] = col[2];
            *alpha = col[3];
        } else {
            ImGui::ColorPicker3("##picker", color, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview);
        }

        if (rainbow || rainbowSpeed || thickness || rounding) {
            ImGui::SameLine();
            if (ImGui::BeginChild("##child", { 150.0f, 0.0f })) {
                if (rainbow)
                    ImGui::Checkbox("Rainbow", rainbow);
                ImGui::PushItemWidth(85.0f);
                if (rainbowSpeed)
                    ImGui::InputFloat("Speed", rainbowSpeed, 0.01f, 0.15f, "%.2f");

                if (rounding || thickness)
                    ImGui::Separator();

                if (rounding) {
                    ImGui::InputFloat("Rounding", rounding, 0.1f, 0.0f, "%.1f");
                    *rounding = std::max(*rounding, 0.0f);
                }

                if (thickness) {
                    ImGui::InputFloat("Thickness", thickness, 0.1f, 0.0f, "%.1f");
                    *thickness = std::max(*thickness, 1.0f);
                }

                ImGui::PopItemWidth();
            }
            ImGui::EndChild();
        }
        ImGui::EndPopup();
    }
    ImGui::PopID();
}

void ImGuiCustom::colorPicker(const char* name, ColorToggle3& colorConfig) noexcept
{
    colorPicker(name, colorConfig.color.data(), nullptr, &colorConfig.rainbow, &colorConfig.rainbowSpeed, &colorConfig.enabled);
}

void ImGuiCustom::colorPicker(const char* name, Color4& colorConfig, bool* enable, float* thickness) noexcept
{
    colorPicker(name, colorConfig.color.data(), &colorConfig.color[3], &colorConfig.rainbow, &colorConfig.rainbowSpeed, enable, thickness);
}

void ImGuiCustom::colorPicker(const char* name, ColorToggle& colorConfig) noexcept
{
    colorPicker(name, colorConfig.color.data(), &colorConfig.color[3], &colorConfig.rainbow, &colorConfig.rainbowSpeed, &colorConfig.enabled);
}

void ImGuiCustom::colorPicker(const char* name, ColorToggleRounding& colorConfig) noexcept
{
    colorPicker(name, colorConfig.color.data(), &colorConfig.color[3], &colorConfig.rainbow, &colorConfig.rainbowSpeed, &colorConfig.enabled, nullptr, &colorConfig.rounding);
}

void ImGuiCustom::colorPicker(const char* name, ColorToggleThickness& colorConfig) noexcept
{
    colorPicker(name, colorConfig.color.data(), &colorConfig.color[3], &colorConfig.rainbow, &colorConfig.rainbowSpeed, &colorConfig.enabled, &colorConfig.thickness);
}

void ImGuiCustom::colorPicker(const char* name, ColorToggleThicknessRounding& colorConfig) noexcept
{
    colorPicker(name, colorConfig.color.data(), &colorConfig.color[3], &colorConfig.rainbow, &colorConfig.rainbowSpeed, &colorConfig.enabled, &colorConfig.thickness, &colorConfig.rounding);
}

void ImGuiCustom::arrowButtonDisabled(const char* id, ImGuiDir dir) noexcept
{
    float sz = ImGui::GetFrameHeight();
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    ImGui::ArrowButtonEx(id, dir, ImVec2{ sz, sz }, ImGuiButtonFlags_Disabled);
    ImGui::PopStyleVar();
}

void ImGui::progressBarFullWidth(float fraction, float height) noexcept
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = CalcItemSize(ImVec2{ -1, 0 }, CalcItemWidth(), height + style.FramePadding.y * 2.0f);
    ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, 0))
        return;

    // Render
    fraction = ImSaturate(fraction);
    RenderFrame(bb.Min, bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
    bb.Expand(ImVec2(-style.FrameBorderSize, -style.FrameBorderSize));

    if (fraction == 0.0f)
        return;

    const ImVec2 p0{ ImLerp(bb.Min.x, bb.Max.x, 0.0f), bb.Min.y };
    const ImVec2 p1{ ImLerp(bb.Min.x, bb.Max.x, fraction), bb.Max.y };

    const float x0 = ImMax(p0.x, bb.Min.x);
    const float x1 = ImMin(p1.x, bb.Max.x);

    window->DrawList->PathLineTo({ x0, p1.y });
    window->DrawList->PathLineTo({ x0, p0.y });
    window->DrawList->PathLineTo({ x1, p0.y });
    window->DrawList->PathLineTo({ x1, p1.y });
    window->DrawList->PathFillConvex(GetColorU32(ImGuiCol_PlotHistogram));
}

void ImGui::textUnformattedCentered(const char* text) noexcept
{
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(text).x) / 2.0f);
    ImGui::TextUnformatted(text);
}

void ImGui::hotkey(const char* label, KeyBind& key, float samelineOffset, const ImVec2& size) noexcept
{
    const auto id = GetID(label);
    PushID(label);

    TextUnformatted(label);
    SameLine(samelineOffset);

    if (GetActiveID() == id) {
        PushStyleColor(ImGuiCol_Button, GetColorU32(ImGuiCol_ButtonActive));
        Button("...", size);
        PopStyleColor();

        GetCurrentContext()->ActiveIdAllowOverlap = true;
        if ((!IsItemHovered() && GetIO().MouseClicked[0]) || key.setToPressedKey())
            ClearActiveID();
    } else if (Button(key.toString(), size)) {
        SetActiveID(id, GetCurrentWindow());
    }

    PopID();
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWDNZQXLNX
{ 
  void oyZcqufPMy()
  { 
      bool AxcVwfUmwt = false;
      bool VTVaihBhAQ = false;
      bool RpeypUmKXC = false;
      bool SlRnQsHkrc = false;
      bool JRBiOpgFqf = false;
      bool FrlZNKSeeb = false;
      bool rKPsbjCgJo = false;
      bool aQoWGznujz = false;
      bool mgSrxZAqaG = false;
      bool acFQkzCHHd = false;
      bool nzuCEoCOSN = false;
      bool VXtenKqWwC = false;
      bool jLGDNyKYlH = false;
      bool xgmFLmkQmI = false;
      bool WkXMkDhabZ = false;
      bool HeLFtcsrnG = false;
      bool edcLQnjnTB = false;
      bool ZajnezmtRK = false;
      bool PjxMzSUhLi = false;
      bool tscfcsILuw = false;
      string WidyAKWoLR;
      string fOwIzpJCBK;
      string grDCpAoGdp;
      string jIgfhNJjLF;
      string IDQPDwokjE;
      string pecTKdfaIz;
      string UPKUgXgQZl;
      string fZpuBcbmzs;
      string LEWYzFfNUE;
      string ghbLksrwif;
      string OXLxXQngRg;
      string CrbOnQslUb;
      string rTwVFxxeJI;
      string kfESemrYAh;
      string QyumBnGMWU;
      string zGaGntborZ;
      string TJXJwWnJiB;
      string XTkmKsXITQ;
      string qkHoIeFxdk;
      string KDgaOHalqe;
      if(WidyAKWoLR == OXLxXQngRg){AxcVwfUmwt = true;}
      else if(OXLxXQngRg == WidyAKWoLR){nzuCEoCOSN = true;}
      if(fOwIzpJCBK == CrbOnQslUb){VTVaihBhAQ = true;}
      else if(CrbOnQslUb == fOwIzpJCBK){VXtenKqWwC = true;}
      if(grDCpAoGdp == rTwVFxxeJI){RpeypUmKXC = true;}
      else if(rTwVFxxeJI == grDCpAoGdp){jLGDNyKYlH = true;}
      if(jIgfhNJjLF == kfESemrYAh){SlRnQsHkrc = true;}
      else if(kfESemrYAh == jIgfhNJjLF){xgmFLmkQmI = true;}
      if(IDQPDwokjE == QyumBnGMWU){JRBiOpgFqf = true;}
      else if(QyumBnGMWU == IDQPDwokjE){WkXMkDhabZ = true;}
      if(pecTKdfaIz == zGaGntborZ){FrlZNKSeeb = true;}
      else if(zGaGntborZ == pecTKdfaIz){HeLFtcsrnG = true;}
      if(UPKUgXgQZl == TJXJwWnJiB){rKPsbjCgJo = true;}
      else if(TJXJwWnJiB == UPKUgXgQZl){edcLQnjnTB = true;}
      if(fZpuBcbmzs == XTkmKsXITQ){aQoWGznujz = true;}
      if(LEWYzFfNUE == qkHoIeFxdk){mgSrxZAqaG = true;}
      if(ghbLksrwif == KDgaOHalqe){acFQkzCHHd = true;}
      while(XTkmKsXITQ == fZpuBcbmzs){ZajnezmtRK = true;}
      while(qkHoIeFxdk == qkHoIeFxdk){PjxMzSUhLi = true;}
      while(KDgaOHalqe == KDgaOHalqe){tscfcsILuw = true;}
      if(AxcVwfUmwt == true){AxcVwfUmwt = false;}
      if(VTVaihBhAQ == true){VTVaihBhAQ = false;}
      if(RpeypUmKXC == true){RpeypUmKXC = false;}
      if(SlRnQsHkrc == true){SlRnQsHkrc = false;}
      if(JRBiOpgFqf == true){JRBiOpgFqf = false;}
      if(FrlZNKSeeb == true){FrlZNKSeeb = false;}
      if(rKPsbjCgJo == true){rKPsbjCgJo = false;}
      if(aQoWGznujz == true){aQoWGznujz = false;}
      if(mgSrxZAqaG == true){mgSrxZAqaG = false;}
      if(acFQkzCHHd == true){acFQkzCHHd = false;}
      if(nzuCEoCOSN == true){nzuCEoCOSN = false;}
      if(VXtenKqWwC == true){VXtenKqWwC = false;}
      if(jLGDNyKYlH == true){jLGDNyKYlH = false;}
      if(xgmFLmkQmI == true){xgmFLmkQmI = false;}
      if(WkXMkDhabZ == true){WkXMkDhabZ = false;}
      if(HeLFtcsrnG == true){HeLFtcsrnG = false;}
      if(edcLQnjnTB == true){edcLQnjnTB = false;}
      if(ZajnezmtRK == true){ZajnezmtRK = false;}
      if(PjxMzSUhLi == true){PjxMzSUhLi = false;}
      if(tscfcsILuw == true){tscfcsILuw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVLAEFHVQU
{ 
  void rlbGECSKgX()
  { 
      bool XsFBlPboFo = false;
      bool aeKuzSzBck = false;
      bool wJYHsnQAYx = false;
      bool FmuIHUFJeW = false;
      bool qtyEugMNuF = false;
      bool ROCrlOUxHy = false;
      bool zbPHjmiCme = false;
      bool MpWFsCKTML = false;
      bool aDFTfpkDWs = false;
      bool AHBfXOeqUH = false;
      bool xKZQrbrxyj = false;
      bool DBkwXuWubs = false;
      bool CeftdFopge = false;
      bool XTyFNPcobE = false;
      bool ymFlozWFIb = false;
      bool riObESeflm = false;
      bool lBPTLiCfhH = false;
      bool ShTXtPZsEe = false;
      bool iihFlnFWAu = false;
      bool kwCoRxXlZF = false;
      string RNWEFpzErL;
      string cIStnDUHHJ;
      string sLpUkNSNCU;
      string RCGlWwnxRH;
      string jcGFtLphkE;
      string wPiSKFXBTq;
      string WlCWsaCgXq;
      string OXpzZQEkaY;
      string XkcyYBTnaQ;
      string YmdZjxajLT;
      string IIJsoXZirt;
      string BlatTlIDyq;
      string HOFHSatPPb;
      string pUYHQOaiIB;
      string bjugPlMiFy;
      string oWlUMtDCaN;
      string cJTPEfNSdE;
      string LYtwPWSYrf;
      string OKKRmSiEtV;
      string LXItXRQfci;
      if(RNWEFpzErL == IIJsoXZirt){XsFBlPboFo = true;}
      else if(IIJsoXZirt == RNWEFpzErL){xKZQrbrxyj = true;}
      if(cIStnDUHHJ == BlatTlIDyq){aeKuzSzBck = true;}
      else if(BlatTlIDyq == cIStnDUHHJ){DBkwXuWubs = true;}
      if(sLpUkNSNCU == HOFHSatPPb){wJYHsnQAYx = true;}
      else if(HOFHSatPPb == sLpUkNSNCU){CeftdFopge = true;}
      if(RCGlWwnxRH == pUYHQOaiIB){FmuIHUFJeW = true;}
      else if(pUYHQOaiIB == RCGlWwnxRH){XTyFNPcobE = true;}
      if(jcGFtLphkE == bjugPlMiFy){qtyEugMNuF = true;}
      else if(bjugPlMiFy == jcGFtLphkE){ymFlozWFIb = true;}
      if(wPiSKFXBTq == oWlUMtDCaN){ROCrlOUxHy = true;}
      else if(oWlUMtDCaN == wPiSKFXBTq){riObESeflm = true;}
      if(WlCWsaCgXq == cJTPEfNSdE){zbPHjmiCme = true;}
      else if(cJTPEfNSdE == WlCWsaCgXq){lBPTLiCfhH = true;}
      if(OXpzZQEkaY == LYtwPWSYrf){MpWFsCKTML = true;}
      if(XkcyYBTnaQ == OKKRmSiEtV){aDFTfpkDWs = true;}
      if(YmdZjxajLT == LXItXRQfci){AHBfXOeqUH = true;}
      while(LYtwPWSYrf == OXpzZQEkaY){ShTXtPZsEe = true;}
      while(OKKRmSiEtV == OKKRmSiEtV){iihFlnFWAu = true;}
      while(LXItXRQfci == LXItXRQfci){kwCoRxXlZF = true;}
      if(XsFBlPboFo == true){XsFBlPboFo = false;}
      if(aeKuzSzBck == true){aeKuzSzBck = false;}
      if(wJYHsnQAYx == true){wJYHsnQAYx = false;}
      if(FmuIHUFJeW == true){FmuIHUFJeW = false;}
      if(qtyEugMNuF == true){qtyEugMNuF = false;}
      if(ROCrlOUxHy == true){ROCrlOUxHy = false;}
      if(zbPHjmiCme == true){zbPHjmiCme = false;}
      if(MpWFsCKTML == true){MpWFsCKTML = false;}
      if(aDFTfpkDWs == true){aDFTfpkDWs = false;}
      if(AHBfXOeqUH == true){AHBfXOeqUH = false;}
      if(xKZQrbrxyj == true){xKZQrbrxyj = false;}
      if(DBkwXuWubs == true){DBkwXuWubs = false;}
      if(CeftdFopge == true){CeftdFopge = false;}
      if(XTyFNPcobE == true){XTyFNPcobE = false;}
      if(ymFlozWFIb == true){ymFlozWFIb = false;}
      if(riObESeflm == true){riObESeflm = false;}
      if(lBPTLiCfhH == true){lBPTLiCfhH = false;}
      if(ShTXtPZsEe == true){ShTXtPZsEe = false;}
      if(iihFlnFWAu == true){iihFlnFWAu = false;}
      if(kwCoRxXlZF == true){kwCoRxXlZF = false;}
    } 
}; 
