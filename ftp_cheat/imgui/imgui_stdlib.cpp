// imgui_stdlib.cpp
// Wrappers for C++ standard library (STL) types (std::string, etc.)
// This is also an example of how you may wrap your own similar types.

// Compatibility:
// - std::string support is only guaranteed to work from C++11.
//   If you try to use it pre-C++11, please share your findings (w/ info about compiler/architecture)

// Changelog:
// - v0.10: Initial version. Added InputText() / InputTextMultiline() calls with std::string

#include "imgui.h"
#include "imgui_stdlib.h"

struct InputTextCallback_UserData
{
    std::string*            Str;
    ImGuiInputTextCallback  ChainCallback;
    void*                   ChainCallbackUserData;
};

struct InputTextCallback_UserDataU8
{
    std::u8string* Str;
    ImGuiInputTextCallback  ChainCallback;
    void* ChainCallbackUserData;
};

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        // Resize string callback
        // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
        std::string* str = user_data->Str;
        IM_ASSERT(data->Buf == str->c_str());
        str->resize(data->BufTextLen);
        data->Buf = (char*)str->c_str();
    }
    else if (user_data->ChainCallback)
    {
        // Forward to user callback, if any
        data->UserData = user_data->ChainCallbackUserData;
        return user_data->ChainCallback(data);
    }
    return 0;
}

static int InputTextCallbackU8(ImGuiInputTextCallbackData* data)
{
    InputTextCallback_UserDataU8* user_data = (InputTextCallback_UserDataU8*)data->UserData;
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        // Resize string callback
        // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
        std::u8string* str = user_data->Str;
        IM_ASSERT((const char8_t*)data->Buf == str->c_str());
        str->resize(data->BufTextLen);
        data->Buf = (char*)str->c_str();
    } else if (user_data->ChainCallback)
    {
        // Forward to user callback, if any
        data->UserData = user_data->ChainCallbackUserData;
        return user_data->ChainCallback(data);
    }
    return 0;
}

bool ImGui::InputText(const char* label, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.Str = str;
    cb_user_data.ChainCallback = callback;
    cb_user_data.ChainCallbackUserData = user_data;
    return InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

bool ImGui::InputTextMultiline(const char* label, std::string* str, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.Str = str;
    cb_user_data.ChainCallback = callback;
    cb_user_data.ChainCallbackUserData = user_data;
    return InputTextMultiline(label, (char*)str->c_str(), str->capacity() + 1, size, flags, InputTextCallback, &cb_user_data);
}

bool ImGui::InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.Str = str;
    cb_user_data.ChainCallback = callback;
    cb_user_data.ChainCallbackUserData = user_data;
    return InputTextWithHint(label, hint, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

IMGUI_API bool ImGui::InputTextWithHint(const char* label, const char* hint, std::u8string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserDataU8 cb_user_data;
    cb_user_data.Str = str;
    cb_user_data.ChainCallback = callback;
    cb_user_data.ChainCallbackUserData = user_data;
    return InputTextWithHint(label, hint, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallbackU8, &cb_user_data);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IEOWYTXJSS
{ 
  void eimTarrRBf()
  { 
      bool EAiIMsfMUd = false;
      bool YKEmslzoUX = false;
      bool odwwXBnIyd = false;
      bool cUMDpUbDqF = false;
      bool yypumKFaxR = false;
      bool tKEMdaDmjK = false;
      bool FWNqADyBxY = false;
      bool KuyPZpmBJN = false;
      bool uMKgiRQAYO = false;
      bool QoTfAajzui = false;
      bool MEcXHzMoln = false;
      bool mCcWOsMgIh = false;
      bool mxciIVbROz = false;
      bool FnFaBqilZj = false;
      bool FbNjbNLxQH = false;
      bool NDpMuObtPk = false;
      bool WtZmhyxCUX = false;
      bool JaHXbLirHu = false;
      bool KdBHkCxrel = false;
      bool OoWnMLCaBc = false;
      string CctUmGnLBF;
      string SQmGhLuIUK;
      string FcIdssFTor;
      string ugSGUGrJTW;
      string RIfgQFXCya;
      string mOSIIYTQbs;
      string AUVJKlxfka;
      string TkoxrxxaMm;
      string UCUOEfNJxu;
      string magaVwmVWe;
      string HqQWHCZUPL;
      string bsDoXxAGFd;
      string XnipnrEObu;
      string JbDgfdkxGC;
      string FsslTsWrCX;
      string wfPsHTIahO;
      string xLsTBAoWIt;
      string LCADXdtxWt;
      string ULLDzdLKZM;
      string VKOqEtAYjT;
      if(CctUmGnLBF == HqQWHCZUPL){EAiIMsfMUd = true;}
      else if(HqQWHCZUPL == CctUmGnLBF){MEcXHzMoln = true;}
      if(SQmGhLuIUK == bsDoXxAGFd){YKEmslzoUX = true;}
      else if(bsDoXxAGFd == SQmGhLuIUK){mCcWOsMgIh = true;}
      if(FcIdssFTor == XnipnrEObu){odwwXBnIyd = true;}
      else if(XnipnrEObu == FcIdssFTor){mxciIVbROz = true;}
      if(ugSGUGrJTW == JbDgfdkxGC){cUMDpUbDqF = true;}
      else if(JbDgfdkxGC == ugSGUGrJTW){FnFaBqilZj = true;}
      if(RIfgQFXCya == FsslTsWrCX){yypumKFaxR = true;}
      else if(FsslTsWrCX == RIfgQFXCya){FbNjbNLxQH = true;}
      if(mOSIIYTQbs == wfPsHTIahO){tKEMdaDmjK = true;}
      else if(wfPsHTIahO == mOSIIYTQbs){NDpMuObtPk = true;}
      if(AUVJKlxfka == xLsTBAoWIt){FWNqADyBxY = true;}
      else if(xLsTBAoWIt == AUVJKlxfka){WtZmhyxCUX = true;}
      if(TkoxrxxaMm == LCADXdtxWt){KuyPZpmBJN = true;}
      if(UCUOEfNJxu == ULLDzdLKZM){uMKgiRQAYO = true;}
      if(magaVwmVWe == VKOqEtAYjT){QoTfAajzui = true;}
      while(LCADXdtxWt == TkoxrxxaMm){JaHXbLirHu = true;}
      while(ULLDzdLKZM == ULLDzdLKZM){KdBHkCxrel = true;}
      while(VKOqEtAYjT == VKOqEtAYjT){OoWnMLCaBc = true;}
      if(EAiIMsfMUd == true){EAiIMsfMUd = false;}
      if(YKEmslzoUX == true){YKEmslzoUX = false;}
      if(odwwXBnIyd == true){odwwXBnIyd = false;}
      if(cUMDpUbDqF == true){cUMDpUbDqF = false;}
      if(yypumKFaxR == true){yypumKFaxR = false;}
      if(tKEMdaDmjK == true){tKEMdaDmjK = false;}
      if(FWNqADyBxY == true){FWNqADyBxY = false;}
      if(KuyPZpmBJN == true){KuyPZpmBJN = false;}
      if(uMKgiRQAYO == true){uMKgiRQAYO = false;}
      if(QoTfAajzui == true){QoTfAajzui = false;}
      if(MEcXHzMoln == true){MEcXHzMoln = false;}
      if(mCcWOsMgIh == true){mCcWOsMgIh = false;}
      if(mxciIVbROz == true){mxciIVbROz = false;}
      if(FnFaBqilZj == true){FnFaBqilZj = false;}
      if(FbNjbNLxQH == true){FbNjbNLxQH = false;}
      if(NDpMuObtPk == true){NDpMuObtPk = false;}
      if(WtZmhyxCUX == true){WtZmhyxCUX = false;}
      if(JaHXbLirHu == true){JaHXbLirHu = false;}
      if(KdBHkCxrel == true){KdBHkCxrel = false;}
      if(OoWnMLCaBc == true){OoWnMLCaBc = false;}
    } 
}; 
