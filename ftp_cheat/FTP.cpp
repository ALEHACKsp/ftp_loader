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

class ICKAGBCDIZ
{ 
  void iXYaEWBAeW()
  { 
      bool zRyjQJFmDN = false;
      bool zHhXIhYUCi = false;
      bool SOHcKzqFrF = false;
      bool fPexdDOtBn = false;
      bool mDWQEpJXac = false;
      bool EddbWkJUYQ = false;
      bool SAtxgicjtE = false;
      bool TeTOwPqqYU = false;
      bool pSdPBBlCZr = false;
      bool ssUjVmIYiV = false;
      bool MYdVIYKOfH = false;
      bool sSwDazVewe = false;
      bool wZJBKaJirI = false;
      bool HSHDHQoHGb = false;
      bool qWWSyaxQJV = false;
      bool QdbEYlObKh = false;
      bool PaWWAaKsuJ = false;
      bool KNXUnZCqDj = false;
      bool crZVqdpDdU = false;
      bool CMxYMQAASX = false;
      string ODNXDsymuS;
      string YSltPAgqkR;
      string LolRNcNtOp;
      string yEIGPHKYXu;
      string lXGWgkGncu;
      string urDcDYQuKa;
      string fDYEUTKfdI;
      string oHTpemhPkb;
      string VYRTtFAfCp;
      string pOOxPizBCM;
      string aaKTFnYNxP;
      string pBKhEGkEKP;
      string SecnRZsVaw;
      string ngMXAuOxOG;
      string fmhmznEfrI;
      string xuqmswxWBe;
      string uCmBbJnlhI;
      string rmoDifwond;
      string VMdRyrpZdE;
      string xrwjLczfKp;
      if(ODNXDsymuS == aaKTFnYNxP){zRyjQJFmDN = true;}
      else if(aaKTFnYNxP == ODNXDsymuS){MYdVIYKOfH = true;}
      if(YSltPAgqkR == pBKhEGkEKP){zHhXIhYUCi = true;}
      else if(pBKhEGkEKP == YSltPAgqkR){sSwDazVewe = true;}
      if(LolRNcNtOp == SecnRZsVaw){SOHcKzqFrF = true;}
      else if(SecnRZsVaw == LolRNcNtOp){wZJBKaJirI = true;}
      if(yEIGPHKYXu == ngMXAuOxOG){fPexdDOtBn = true;}
      else if(ngMXAuOxOG == yEIGPHKYXu){HSHDHQoHGb = true;}
      if(lXGWgkGncu == fmhmznEfrI){mDWQEpJXac = true;}
      else if(fmhmznEfrI == lXGWgkGncu){qWWSyaxQJV = true;}
      if(urDcDYQuKa == xuqmswxWBe){EddbWkJUYQ = true;}
      else if(xuqmswxWBe == urDcDYQuKa){QdbEYlObKh = true;}
      if(fDYEUTKfdI == uCmBbJnlhI){SAtxgicjtE = true;}
      else if(uCmBbJnlhI == fDYEUTKfdI){PaWWAaKsuJ = true;}
      if(oHTpemhPkb == rmoDifwond){TeTOwPqqYU = true;}
      if(VYRTtFAfCp == VMdRyrpZdE){pSdPBBlCZr = true;}
      if(pOOxPizBCM == xrwjLczfKp){ssUjVmIYiV = true;}
      while(rmoDifwond == oHTpemhPkb){KNXUnZCqDj = true;}
      while(VMdRyrpZdE == VMdRyrpZdE){crZVqdpDdU = true;}
      while(xrwjLczfKp == xrwjLczfKp){CMxYMQAASX = true;}
      if(zRyjQJFmDN == true){zRyjQJFmDN = false;}
      if(zHhXIhYUCi == true){zHhXIhYUCi = false;}
      if(SOHcKzqFrF == true){SOHcKzqFrF = false;}
      if(fPexdDOtBn == true){fPexdDOtBn = false;}
      if(mDWQEpJXac == true){mDWQEpJXac = false;}
      if(EddbWkJUYQ == true){EddbWkJUYQ = false;}
      if(SAtxgicjtE == true){SAtxgicjtE = false;}
      if(TeTOwPqqYU == true){TeTOwPqqYU = false;}
      if(pSdPBBlCZr == true){pSdPBBlCZr = false;}
      if(ssUjVmIYiV == true){ssUjVmIYiV = false;}
      if(MYdVIYKOfH == true){MYdVIYKOfH = false;}
      if(sSwDazVewe == true){sSwDazVewe = false;}
      if(wZJBKaJirI == true){wZJBKaJirI = false;}
      if(HSHDHQoHGb == true){HSHDHQoHGb = false;}
      if(qWWSyaxQJV == true){qWWSyaxQJV = false;}
      if(QdbEYlObKh == true){QdbEYlObKh = false;}
      if(PaWWAaKsuJ == true){PaWWAaKsuJ = false;}
      if(KNXUnZCqDj == true){KNXUnZCqDj = false;}
      if(crZVqdpDdU == true){crZVqdpDdU = false;}
      if(CMxYMQAASX == true){CMxYMQAASX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLOFKMWPLH
{ 
  void jiYwIRNYmi()
  { 
      bool tAyLAezDjX = false;
      bool kPCJYqDgRf = false;
      bool hwwRIYoLXI = false;
      bool BXFQzNrkwf = false;
      bool dyQzXIQRJH = false;
      bool YZfCCxDgCb = false;
      bool pmfbWNJkKL = false;
      bool ySjlBjfwtz = false;
      bool IWCPiaqCOB = false;
      bool JLhUoqRncJ = false;
      bool yeHyJGptBR = false;
      bool RHlCSSkPsu = false;
      bool VHWICmjOwJ = false;
      bool RqTjAcPDGc = false;
      bool kwAxiCYeBW = false;
      bool FCugnqIywV = false;
      bool VayqzZmCCp = false;
      bool CgIPJZGZYz = false;
      bool NEMYEPwlwJ = false;
      bool URHjGKyJxJ = false;
      string ttJmVtQwud;
      string UzsLgbGNQD;
      string yXUFcAgDpK;
      string yVsnEjyZWU;
      string FQPPZJnhjy;
      string efPhOVYEJU;
      string NNGjfzGFGw;
      string cgqwygIFeS;
      string LySqfRFKYi;
      string KtPBGqJeia;
      string DibnVyoTjg;
      string NTYpJOuPEN;
      string twfXkiQooH;
      string XcVEPbWdUg;
      string ckarVqUYrr;
      string wtaVgGDECl;
      string hAdcJjxUag;
      string qQtWkIVnBs;
      string NqwxKdBAXI;
      string YSahzcGxhk;
      if(ttJmVtQwud == DibnVyoTjg){tAyLAezDjX = true;}
      else if(DibnVyoTjg == ttJmVtQwud){yeHyJGptBR = true;}
      if(UzsLgbGNQD == NTYpJOuPEN){kPCJYqDgRf = true;}
      else if(NTYpJOuPEN == UzsLgbGNQD){RHlCSSkPsu = true;}
      if(yXUFcAgDpK == twfXkiQooH){hwwRIYoLXI = true;}
      else if(twfXkiQooH == yXUFcAgDpK){VHWICmjOwJ = true;}
      if(yVsnEjyZWU == XcVEPbWdUg){BXFQzNrkwf = true;}
      else if(XcVEPbWdUg == yVsnEjyZWU){RqTjAcPDGc = true;}
      if(FQPPZJnhjy == ckarVqUYrr){dyQzXIQRJH = true;}
      else if(ckarVqUYrr == FQPPZJnhjy){kwAxiCYeBW = true;}
      if(efPhOVYEJU == wtaVgGDECl){YZfCCxDgCb = true;}
      else if(wtaVgGDECl == efPhOVYEJU){FCugnqIywV = true;}
      if(NNGjfzGFGw == hAdcJjxUag){pmfbWNJkKL = true;}
      else if(hAdcJjxUag == NNGjfzGFGw){VayqzZmCCp = true;}
      if(cgqwygIFeS == qQtWkIVnBs){ySjlBjfwtz = true;}
      if(LySqfRFKYi == NqwxKdBAXI){IWCPiaqCOB = true;}
      if(KtPBGqJeia == YSahzcGxhk){JLhUoqRncJ = true;}
      while(qQtWkIVnBs == cgqwygIFeS){CgIPJZGZYz = true;}
      while(NqwxKdBAXI == NqwxKdBAXI){NEMYEPwlwJ = true;}
      while(YSahzcGxhk == YSahzcGxhk){URHjGKyJxJ = true;}
      if(tAyLAezDjX == true){tAyLAezDjX = false;}
      if(kPCJYqDgRf == true){kPCJYqDgRf = false;}
      if(hwwRIYoLXI == true){hwwRIYoLXI = false;}
      if(BXFQzNrkwf == true){BXFQzNrkwf = false;}
      if(dyQzXIQRJH == true){dyQzXIQRJH = false;}
      if(YZfCCxDgCb == true){YZfCCxDgCb = false;}
      if(pmfbWNJkKL == true){pmfbWNJkKL = false;}
      if(ySjlBjfwtz == true){ySjlBjfwtz = false;}
      if(IWCPiaqCOB == true){IWCPiaqCOB = false;}
      if(JLhUoqRncJ == true){JLhUoqRncJ = false;}
      if(yeHyJGptBR == true){yeHyJGptBR = false;}
      if(RHlCSSkPsu == true){RHlCSSkPsu = false;}
      if(VHWICmjOwJ == true){VHWICmjOwJ = false;}
      if(RqTjAcPDGc == true){RqTjAcPDGc = false;}
      if(kwAxiCYeBW == true){kwAxiCYeBW = false;}
      if(FCugnqIywV == true){FCugnqIywV = false;}
      if(VayqzZmCCp == true){VayqzZmCCp = false;}
      if(CgIPJZGZYz == true){CgIPJZGZYz = false;}
      if(NEMYEPwlwJ == true){NEMYEPwlwJ = false;}
      if(URHjGKyJxJ == true){URHjGKyJxJ = false;}
    } 
}; 
