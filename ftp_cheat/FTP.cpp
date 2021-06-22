#include <memory>

#ifdef _WIN32
#include <clocale>
#include <Windows.h>
#endif

#include "Hooks.h"


#ifdef _WIN32

extern "C" BOOL WINAPI _CRT_INIT(HMODULE moduleHandle, DWORD reason, LPVOID reserved);

BOOL APIENTRY DllEntryPoint(HMODULE moduleHandle, DWORD reason, LPVOID reserved)
{
    if (!_CRT_INIT(moduleHandle, reason, reserved))
        return FALSE;

    if (reason == DLL_PROCESS_ATTACH) {
        std::setlocale(LC_CTYPE, ".utf8");
        hooks = std::make_unique<Hooks>(moduleHandle);
    }
    return TRUE;
}

#else

void __attribute__((constructor)) DllEntryPoint()
{
    hooks = std::make_unique<Hooks>();
}

#endif

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YOLWVVLTMD
{ 
  void opSehxSRrM()
  { 
      bool WjWdPiJYsW = false;
      bool CkEFZGTzAH = false;
      bool jdmCwndKTK = false;
      bool UaTpCsioCp = false;
      bool LXFFisbTwE = false;
      bool ttiahrwThb = false;
      bool FzEhCaRNDf = false;
      bool WdwJuLYgTC = false;
      bool LKOPPZrrIJ = false;
      bool xPHakMSWDH = false;
      bool bNPPgQyYfV = false;
      bool SOzfPtkoRc = false;
      bool iYFsiHWVYh = false;
      bool sCdMaytyhz = false;
      bool aSMmphPaLq = false;
      bool bdEaXCIWfZ = false;
      bool scAycQkmER = false;
      bool zlGRBQMSDB = false;
      bool quJhFPxCnY = false;
      bool oXRIGyROKY = false;
      string HJoKnpDTzt;
      string IPPEUnjeaX;
      string bSCmndPjBu;
      string BCuCTBfUHY;
      string OQLoPEMDZr;
      string skWwBoGBWJ;
      string ZSREsFUNkT;
      string IPWCILHMXi;
      string QLKJBQfyAe;
      string tdyyzuyGwK;
      string jzSFidNUnp;
      string gtdmrNIHCc;
      string ZVMFZeQYDN;
      string MAQNzRsEaX;
      string DLKKxAAKFk;
      string mqDSkNmMfE;
      string MnRacfcPna;
      string UDgeZNLBHZ;
      string dGTSZVwyck;
      string egYWKOsjhR;
      if(HJoKnpDTzt == jzSFidNUnp){WjWdPiJYsW = true;}
      else if(jzSFidNUnp == HJoKnpDTzt){bNPPgQyYfV = true;}
      if(IPPEUnjeaX == gtdmrNIHCc){CkEFZGTzAH = true;}
      else if(gtdmrNIHCc == IPPEUnjeaX){SOzfPtkoRc = true;}
      if(bSCmndPjBu == ZVMFZeQYDN){jdmCwndKTK = true;}
      else if(ZVMFZeQYDN == bSCmndPjBu){iYFsiHWVYh = true;}
      if(BCuCTBfUHY == MAQNzRsEaX){UaTpCsioCp = true;}
      else if(MAQNzRsEaX == BCuCTBfUHY){sCdMaytyhz = true;}
      if(OQLoPEMDZr == DLKKxAAKFk){LXFFisbTwE = true;}
      else if(DLKKxAAKFk == OQLoPEMDZr){aSMmphPaLq = true;}
      if(skWwBoGBWJ == mqDSkNmMfE){ttiahrwThb = true;}
      else if(mqDSkNmMfE == skWwBoGBWJ){bdEaXCIWfZ = true;}
      if(ZSREsFUNkT == MnRacfcPna){FzEhCaRNDf = true;}
      else if(MnRacfcPna == ZSREsFUNkT){scAycQkmER = true;}
      if(IPWCILHMXi == UDgeZNLBHZ){WdwJuLYgTC = true;}
      if(QLKJBQfyAe == dGTSZVwyck){LKOPPZrrIJ = true;}
      if(tdyyzuyGwK == egYWKOsjhR){xPHakMSWDH = true;}
      while(UDgeZNLBHZ == IPWCILHMXi){zlGRBQMSDB = true;}
      while(dGTSZVwyck == dGTSZVwyck){quJhFPxCnY = true;}
      while(egYWKOsjhR == egYWKOsjhR){oXRIGyROKY = true;}
      if(WjWdPiJYsW == true){WjWdPiJYsW = false;}
      if(CkEFZGTzAH == true){CkEFZGTzAH = false;}
      if(jdmCwndKTK == true){jdmCwndKTK = false;}
      if(UaTpCsioCp == true){UaTpCsioCp = false;}
      if(LXFFisbTwE == true){LXFFisbTwE = false;}
      if(ttiahrwThb == true){ttiahrwThb = false;}
      if(FzEhCaRNDf == true){FzEhCaRNDf = false;}
      if(WdwJuLYgTC == true){WdwJuLYgTC = false;}
      if(LKOPPZrrIJ == true){LKOPPZrrIJ = false;}
      if(xPHakMSWDH == true){xPHakMSWDH = false;}
      if(bNPPgQyYfV == true){bNPPgQyYfV = false;}
      if(SOzfPtkoRc == true){SOzfPtkoRc = false;}
      if(iYFsiHWVYh == true){iYFsiHWVYh = false;}
      if(sCdMaytyhz == true){sCdMaytyhz = false;}
      if(aSMmphPaLq == true){aSMmphPaLq = false;}
      if(bdEaXCIWfZ == true){bdEaXCIWfZ = false;}
      if(scAycQkmER == true){scAycQkmER = false;}
      if(zlGRBQMSDB == true){zlGRBQMSDB = false;}
      if(quJhFPxCnY == true){quJhFPxCnY = false;}
      if(oXRIGyROKY == true){oXRIGyROKY = false;}
    } 
}; 
