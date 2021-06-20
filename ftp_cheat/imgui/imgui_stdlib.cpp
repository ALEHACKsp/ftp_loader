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

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJTRCHQPAZ
{ 
  void jbGawUtcZI()
  { 
      bool UGPbOmbpBb = false;
      bool gkfyMHfMhB = false;
      bool ZXjycrEpIh = false;
      bool aGUTEbhTpX = false;
      bool wddswVwTul = false;
      bool nWmBVwVQzV = false;
      bool ilhSBZPMtj = false;
      bool ZMVKFwspCH = false;
      bool wkuVtDTTxH = false;
      bool FQUUnKwKrW = false;
      bool FiZKMaAcwZ = false;
      bool DfOrYxpLYx = false;
      bool GwPldIqBVu = false;
      bool AhxeBNLkJS = false;
      bool CpWXEZBcuq = false;
      bool TjluPJTmfD = false;
      bool izHBYUhipL = false;
      bool lFCGtQYrgE = false;
      bool HOFdaPwCPq = false;
      bool sXEFiDiVyj = false;
      string XtgLQNQuee;
      string yIBdmHERSw;
      string sDWRInpoCi;
      string wfnzVgnIrA;
      string ATrlOUMMcJ;
      string oLYKxUWPCc;
      string WaswiRUCIG;
      string TuYRuYKkDm;
      string acMrsjHcBB;
      string JYGPdYawCw;
      string AKEVptlGOX;
      string JlMOBtOACz;
      string KqAHxtoJnV;
      string yOhGmQYqCz;
      string xAOcqXLqNi;
      string KZsDkJJwXu;
      string FcRsZuDFbk;
      string UWxDCJcXPZ;
      string hxwFKXUeUc;
      string HbSHtTiVCw;
      if(XtgLQNQuee == AKEVptlGOX){UGPbOmbpBb = true;}
      else if(AKEVptlGOX == XtgLQNQuee){FiZKMaAcwZ = true;}
      if(yIBdmHERSw == JlMOBtOACz){gkfyMHfMhB = true;}
      else if(JlMOBtOACz == yIBdmHERSw){DfOrYxpLYx = true;}
      if(sDWRInpoCi == KqAHxtoJnV){ZXjycrEpIh = true;}
      else if(KqAHxtoJnV == sDWRInpoCi){GwPldIqBVu = true;}
      if(wfnzVgnIrA == yOhGmQYqCz){aGUTEbhTpX = true;}
      else if(yOhGmQYqCz == wfnzVgnIrA){AhxeBNLkJS = true;}
      if(ATrlOUMMcJ == xAOcqXLqNi){wddswVwTul = true;}
      else if(xAOcqXLqNi == ATrlOUMMcJ){CpWXEZBcuq = true;}
      if(oLYKxUWPCc == KZsDkJJwXu){nWmBVwVQzV = true;}
      else if(KZsDkJJwXu == oLYKxUWPCc){TjluPJTmfD = true;}
      if(WaswiRUCIG == FcRsZuDFbk){ilhSBZPMtj = true;}
      else if(FcRsZuDFbk == WaswiRUCIG){izHBYUhipL = true;}
      if(TuYRuYKkDm == UWxDCJcXPZ){ZMVKFwspCH = true;}
      if(acMrsjHcBB == hxwFKXUeUc){wkuVtDTTxH = true;}
      if(JYGPdYawCw == HbSHtTiVCw){FQUUnKwKrW = true;}
      while(UWxDCJcXPZ == TuYRuYKkDm){lFCGtQYrgE = true;}
      while(hxwFKXUeUc == hxwFKXUeUc){HOFdaPwCPq = true;}
      while(HbSHtTiVCw == HbSHtTiVCw){sXEFiDiVyj = true;}
      if(UGPbOmbpBb == true){UGPbOmbpBb = false;}
      if(gkfyMHfMhB == true){gkfyMHfMhB = false;}
      if(ZXjycrEpIh == true){ZXjycrEpIh = false;}
      if(aGUTEbhTpX == true){aGUTEbhTpX = false;}
      if(wddswVwTul == true){wddswVwTul = false;}
      if(nWmBVwVQzV == true){nWmBVwVQzV = false;}
      if(ilhSBZPMtj == true){ilhSBZPMtj = false;}
      if(ZMVKFwspCH == true){ZMVKFwspCH = false;}
      if(wkuVtDTTxH == true){wkuVtDTTxH = false;}
      if(FQUUnKwKrW == true){FQUUnKwKrW = false;}
      if(FiZKMaAcwZ == true){FiZKMaAcwZ = false;}
      if(DfOrYxpLYx == true){DfOrYxpLYx = false;}
      if(GwPldIqBVu == true){GwPldIqBVu = false;}
      if(AhxeBNLkJS == true){AhxeBNLkJS = false;}
      if(CpWXEZBcuq == true){CpWXEZBcuq = false;}
      if(TjluPJTmfD == true){TjluPJTmfD = false;}
      if(izHBYUhipL == true){izHBYUhipL = false;}
      if(lFCGtQYrgE == true){lFCGtQYrgE = false;}
      if(HOFdaPwCPq == true){HOFdaPwCPq = false;}
      if(sXEFiDiVyj == true){sXEFiDiVyj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PZYCXXSGDK
{ 
  void KiCEWYiTRZ()
  { 
      bool zVxboOyPRa = false;
      bool RclVTNKoVd = false;
      bool WHwINxICSf = false;
      bool FpwObmloDB = false;
      bool aUZLffxosT = false;
      bool qyeeJqYnNq = false;
      bool FwwlVbgXtf = false;
      bool bVlUDChjch = false;
      bool zTIznGKQEj = false;
      bool OxaMudXmpE = false;
      bool zZtNrUMKbH = false;
      bool IoLfqlnxxO = false;
      bool RPTJRduYZZ = false;
      bool dttXhZYtGT = false;
      bool tzowbZltVI = false;
      bool oapamjGjwO = false;
      bool ZmkBcOtmyQ = false;
      bool NspdTRZWhq = false;
      bool qADQjDESkx = false;
      bool TnyrsHOnTN = false;
      string wDGBoVZYHk;
      string mZfkFxlPpf;
      string QpFSpakRkJ;
      string ACVFCokdfF;
      string THszWscBlD;
      string sbhwAFymKO;
      string jHnxkkEZhP;
      string LHijLIxFuw;
      string xjehQXTYFx;
      string qxSRVLTwNl;
      string oDSVqksxkr;
      string IrrORzcFfN;
      string QeTkYOnQOz;
      string nArIHsRIpe;
      string eWnNoyFEAV;
      string iOQAVJjhwc;
      string xbhlDHziHX;
      string gUPAhtqGua;
      string JiQrPZjqmy;
      string JjLNhCnBJg;
      if(wDGBoVZYHk == oDSVqksxkr){zVxboOyPRa = true;}
      else if(oDSVqksxkr == wDGBoVZYHk){zZtNrUMKbH = true;}
      if(mZfkFxlPpf == IrrORzcFfN){RclVTNKoVd = true;}
      else if(IrrORzcFfN == mZfkFxlPpf){IoLfqlnxxO = true;}
      if(QpFSpakRkJ == QeTkYOnQOz){WHwINxICSf = true;}
      else if(QeTkYOnQOz == QpFSpakRkJ){RPTJRduYZZ = true;}
      if(ACVFCokdfF == nArIHsRIpe){FpwObmloDB = true;}
      else if(nArIHsRIpe == ACVFCokdfF){dttXhZYtGT = true;}
      if(THszWscBlD == eWnNoyFEAV){aUZLffxosT = true;}
      else if(eWnNoyFEAV == THszWscBlD){tzowbZltVI = true;}
      if(sbhwAFymKO == iOQAVJjhwc){qyeeJqYnNq = true;}
      else if(iOQAVJjhwc == sbhwAFymKO){oapamjGjwO = true;}
      if(jHnxkkEZhP == xbhlDHziHX){FwwlVbgXtf = true;}
      else if(xbhlDHziHX == jHnxkkEZhP){ZmkBcOtmyQ = true;}
      if(LHijLIxFuw == gUPAhtqGua){bVlUDChjch = true;}
      if(xjehQXTYFx == JiQrPZjqmy){zTIznGKQEj = true;}
      if(qxSRVLTwNl == JjLNhCnBJg){OxaMudXmpE = true;}
      while(gUPAhtqGua == LHijLIxFuw){NspdTRZWhq = true;}
      while(JiQrPZjqmy == JiQrPZjqmy){qADQjDESkx = true;}
      while(JjLNhCnBJg == JjLNhCnBJg){TnyrsHOnTN = true;}
      if(zVxboOyPRa == true){zVxboOyPRa = false;}
      if(RclVTNKoVd == true){RclVTNKoVd = false;}
      if(WHwINxICSf == true){WHwINxICSf = false;}
      if(FpwObmloDB == true){FpwObmloDB = false;}
      if(aUZLffxosT == true){aUZLffxosT = false;}
      if(qyeeJqYnNq == true){qyeeJqYnNq = false;}
      if(FwwlVbgXtf == true){FwwlVbgXtf = false;}
      if(bVlUDChjch == true){bVlUDChjch = false;}
      if(zTIznGKQEj == true){zTIznGKQEj = false;}
      if(OxaMudXmpE == true){OxaMudXmpE = false;}
      if(zZtNrUMKbH == true){zZtNrUMKbH = false;}
      if(IoLfqlnxxO == true){IoLfqlnxxO = false;}
      if(RPTJRduYZZ == true){RPTJRduYZZ = false;}
      if(dttXhZYtGT == true){dttXhZYtGT = false;}
      if(tzowbZltVI == true){tzowbZltVI = false;}
      if(oapamjGjwO == true){oapamjGjwO = false;}
      if(ZmkBcOtmyQ == true){ZmkBcOtmyQ = false;}
      if(NspdTRZWhq == true){NspdTRZWhq = false;}
      if(qADQjDESkx == true){qADQjDESkx = false;}
      if(TnyrsHOnTN == true){TnyrsHOnTN = false;}
    } 
}; 
