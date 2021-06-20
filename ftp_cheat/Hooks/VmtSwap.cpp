#include <algorithm>

#include "VmtSwap.h"
#include "../Helpers.h"

void VmtSwap::init(void* base) noexcept
{
    this->base = base;
    oldVmt = *reinterpret_cast<std::uintptr_t**>(base);
    std::size_t length = Helpers::calculateVmtLength(oldVmt) + dynamicCastInfoLength;
    newVmt = std::make_unique<std::uintptr_t[]>(length);
    std::copy(oldVmt - dynamicCastInfoLength, oldVmt - dynamicCastInfoLength + length, newVmt.get());
    *reinterpret_cast<std::uintptr_t**>(base) = newVmt.get() + dynamicCastInfoLength;
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VUSEWZCMSZ
{ 
  void EZpTKsmhdM()
  { 
      bool MfDoTaKfZR = false;
      bool dnTaAQIMoK = false;
      bool nYADhSqxQz = false;
      bool BqrnhiMygl = false;
      bool eCXeFWBcNn = false;
      bool uUFwxnezGB = false;
      bool iMPZQmwesQ = false;
      bool EKfDflAUyL = false;
      bool ROicDfkuqs = false;
      bool EMqfCRlyOS = false;
      bool ZVixikoBPL = false;
      bool mJBuiTcmVj = false;
      bool BAnzMrTzBN = false;
      bool zCGekuelsS = false;
      bool qiffGtKuwh = false;
      bool ozbeQZhjkq = false;
      bool RpACMjDVKn = false;
      bool optDsRUIsR = false;
      bool gXCSYzaaOL = false;
      bool MuBBAAicSV = false;
      string eXqQpFileI;
      string VPTIzRMIbS;
      string GfQPXGLlLz;
      string jSwxMnAYKF;
      string pknGkUOVKZ;
      string aQwNfyHarj;
      string sxZeXDSVuK;
      string RmxWbVrJeD;
      string qpakYTWiQN;
      string gYgaLsKIhg;
      string BraAHmSZkK;
      string GxuorDWoGE;
      string fjFgdrGWKi;
      string KjaxByOack;
      string AxxGHicqiI;
      string WVBdAQmsVP;
      string fwOBzVVxns;
      string nwLVEimyZt;
      string OPmBMohxxj;
      string LUENEEhuGk;
      if(eXqQpFileI == BraAHmSZkK){MfDoTaKfZR = true;}
      else if(BraAHmSZkK == eXqQpFileI){ZVixikoBPL = true;}
      if(VPTIzRMIbS == GxuorDWoGE){dnTaAQIMoK = true;}
      else if(GxuorDWoGE == VPTIzRMIbS){mJBuiTcmVj = true;}
      if(GfQPXGLlLz == fjFgdrGWKi){nYADhSqxQz = true;}
      else if(fjFgdrGWKi == GfQPXGLlLz){BAnzMrTzBN = true;}
      if(jSwxMnAYKF == KjaxByOack){BqrnhiMygl = true;}
      else if(KjaxByOack == jSwxMnAYKF){zCGekuelsS = true;}
      if(pknGkUOVKZ == AxxGHicqiI){eCXeFWBcNn = true;}
      else if(AxxGHicqiI == pknGkUOVKZ){qiffGtKuwh = true;}
      if(aQwNfyHarj == WVBdAQmsVP){uUFwxnezGB = true;}
      else if(WVBdAQmsVP == aQwNfyHarj){ozbeQZhjkq = true;}
      if(sxZeXDSVuK == fwOBzVVxns){iMPZQmwesQ = true;}
      else if(fwOBzVVxns == sxZeXDSVuK){RpACMjDVKn = true;}
      if(RmxWbVrJeD == nwLVEimyZt){EKfDflAUyL = true;}
      if(qpakYTWiQN == OPmBMohxxj){ROicDfkuqs = true;}
      if(gYgaLsKIhg == LUENEEhuGk){EMqfCRlyOS = true;}
      while(nwLVEimyZt == RmxWbVrJeD){optDsRUIsR = true;}
      while(OPmBMohxxj == OPmBMohxxj){gXCSYzaaOL = true;}
      while(LUENEEhuGk == LUENEEhuGk){MuBBAAicSV = true;}
      if(MfDoTaKfZR == true){MfDoTaKfZR = false;}
      if(dnTaAQIMoK == true){dnTaAQIMoK = false;}
      if(nYADhSqxQz == true){nYADhSqxQz = false;}
      if(BqrnhiMygl == true){BqrnhiMygl = false;}
      if(eCXeFWBcNn == true){eCXeFWBcNn = false;}
      if(uUFwxnezGB == true){uUFwxnezGB = false;}
      if(iMPZQmwesQ == true){iMPZQmwesQ = false;}
      if(EKfDflAUyL == true){EKfDflAUyL = false;}
      if(ROicDfkuqs == true){ROicDfkuqs = false;}
      if(EMqfCRlyOS == true){EMqfCRlyOS = false;}
      if(ZVixikoBPL == true){ZVixikoBPL = false;}
      if(mJBuiTcmVj == true){mJBuiTcmVj = false;}
      if(BAnzMrTzBN == true){BAnzMrTzBN = false;}
      if(zCGekuelsS == true){zCGekuelsS = false;}
      if(qiffGtKuwh == true){qiffGtKuwh = false;}
      if(ozbeQZhjkq == true){ozbeQZhjkq = false;}
      if(RpACMjDVKn == true){RpACMjDVKn = false;}
      if(optDsRUIsR == true){optDsRUIsR = false;}
      if(gXCSYzaaOL == true){gXCSYzaaOL = false;}
      if(MuBBAAicSV == true){MuBBAAicSV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NRUZCHAEUC
{ 
  void PyXwbomwUd()
  { 
      bool GPeddCKFYB = false;
      bool ebCCurPTEz = false;
      bool oMAHnfDoDb = false;
      bool MUuBJSYECe = false;
      bool VyIVakntKR = false;
      bool MdUyhsPWoy = false;
      bool zVCxoJfBrc = false;
      bool SKQYdqEdfC = false;
      bool rIekOhAxSQ = false;
      bool CBPEeAuLgR = false;
      bool FlBgyCNuTp = false;
      bool olplFpqQhG = false;
      bool JihbaQuMsd = false;
      bool urwOxFGxlM = false;
      bool UFcbaQKcyo = false;
      bool IedaHVEZGh = false;
      bool GBBptxpbnA = false;
      bool isdVlDFFBK = false;
      bool GRNEUQOUGb = false;
      bool BgpEFTDmhd = false;
      string fbkbCykYou;
      string XAUZRgUFis;
      string jJxUZqYRFX;
      string chMxDnNmaN;
      string mHCaMRQnPT;
      string ZpCdxWdQBL;
      string YSSQRpmXWc;
      string ThdUFcHVHI;
      string ajCkymfizf;
      string KxkPnTnkJW;
      string dsRlArMgXU;
      string PIIrjnQgSe;
      string JEXpSVwOfk;
      string nVMkehRPkF;
      string ayKeQCnrfA;
      string DHSdMYUbSd;
      string uxAlgsuXNB;
      string VAwMEKtsYQ;
      string hDhfhgDhXF;
      string NpxGJcyYxX;
      if(fbkbCykYou == dsRlArMgXU){GPeddCKFYB = true;}
      else if(dsRlArMgXU == fbkbCykYou){FlBgyCNuTp = true;}
      if(XAUZRgUFis == PIIrjnQgSe){ebCCurPTEz = true;}
      else if(PIIrjnQgSe == XAUZRgUFis){olplFpqQhG = true;}
      if(jJxUZqYRFX == JEXpSVwOfk){oMAHnfDoDb = true;}
      else if(JEXpSVwOfk == jJxUZqYRFX){JihbaQuMsd = true;}
      if(chMxDnNmaN == nVMkehRPkF){MUuBJSYECe = true;}
      else if(nVMkehRPkF == chMxDnNmaN){urwOxFGxlM = true;}
      if(mHCaMRQnPT == ayKeQCnrfA){VyIVakntKR = true;}
      else if(ayKeQCnrfA == mHCaMRQnPT){UFcbaQKcyo = true;}
      if(ZpCdxWdQBL == DHSdMYUbSd){MdUyhsPWoy = true;}
      else if(DHSdMYUbSd == ZpCdxWdQBL){IedaHVEZGh = true;}
      if(YSSQRpmXWc == uxAlgsuXNB){zVCxoJfBrc = true;}
      else if(uxAlgsuXNB == YSSQRpmXWc){GBBptxpbnA = true;}
      if(ThdUFcHVHI == VAwMEKtsYQ){SKQYdqEdfC = true;}
      if(ajCkymfizf == hDhfhgDhXF){rIekOhAxSQ = true;}
      if(KxkPnTnkJW == NpxGJcyYxX){CBPEeAuLgR = true;}
      while(VAwMEKtsYQ == ThdUFcHVHI){isdVlDFFBK = true;}
      while(hDhfhgDhXF == hDhfhgDhXF){GRNEUQOUGb = true;}
      while(NpxGJcyYxX == NpxGJcyYxX){BgpEFTDmhd = true;}
      if(GPeddCKFYB == true){GPeddCKFYB = false;}
      if(ebCCurPTEz == true){ebCCurPTEz = false;}
      if(oMAHnfDoDb == true){oMAHnfDoDb = false;}
      if(MUuBJSYECe == true){MUuBJSYECe = false;}
      if(VyIVakntKR == true){VyIVakntKR = false;}
      if(MdUyhsPWoy == true){MdUyhsPWoy = false;}
      if(zVCxoJfBrc == true){zVCxoJfBrc = false;}
      if(SKQYdqEdfC == true){SKQYdqEdfC = false;}
      if(rIekOhAxSQ == true){rIekOhAxSQ = false;}
      if(CBPEeAuLgR == true){CBPEeAuLgR = false;}
      if(FlBgyCNuTp == true){FlBgyCNuTp = false;}
      if(olplFpqQhG == true){olplFpqQhG = false;}
      if(JihbaQuMsd == true){JihbaQuMsd = false;}
      if(urwOxFGxlM == true){urwOxFGxlM = false;}
      if(UFcbaQKcyo == true){UFcbaQKcyo = false;}
      if(IedaHVEZGh == true){IedaHVEZGh = false;}
      if(GBBptxpbnA == true){GBBptxpbnA = false;}
      if(isdVlDFFBK == true){isdVlDFFBK = false;}
      if(GRNEUQOUGb == true){GRNEUQOUGb = false;}
      if(BgpEFTDmhd == true){BgpEFTDmhd = false;}
    } 
}; 
