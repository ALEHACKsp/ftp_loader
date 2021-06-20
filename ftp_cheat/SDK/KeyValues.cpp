#include "KeyValues.h"
#include "../Memory.h"

KeyValues* KeyValues::fromString(const char* name, const char* value) noexcept
{
#ifdef _WIN32
    const auto keyValuesFromString = memory->keyValuesFromString;
    KeyValues* keyValues;
    __asm {
        push 0
        mov edx, value
        mov ecx, name
        call keyValuesFromString
        add esp, 4
        mov keyValues, eax
    }
    return keyValues;
#else
    return reinterpret_cast<KeyValues*(*)(const char*, const char*, const char**)>(memory->keyValuesFromString)(name, value, nullptr);
#endif
}

KeyValues* KeyValues::findKey(const char* keyName, bool create) noexcept
{
    return memory->keyValuesFindKey(this, keyName, create);
}

void KeyValues::setString(const char* keyName, const char* value) noexcept
{
    if (const auto key = findKey(keyName, true))
        memory->keyValuesSetString(key, value);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBDXJYDHCR
{ 
  void BnoVbbqUQR()
  { 
      bool kodlqgROgE = false;
      bool cfjbadeQRW = false;
      bool bKalNaKWSx = false;
      bool DguPftHwbC = false;
      bool rKMnhyglBk = false;
      bool SuTnlZOrXQ = false;
      bool VuwjAukTug = false;
      bool WinOeQymDO = false;
      bool sXUheINGcF = false;
      bool fPXLfxOcmm = false;
      bool NNpUOiHEJV = false;
      bool aanIXyZNEr = false;
      bool gdpoBGKbih = false;
      bool CVzQBfhATu = false;
      bool AJxHeEaOnh = false;
      bool WAXuFiWASH = false;
      bool XeVbSFaXHr = false;
      bool PYtIqWgiKx = false;
      bool ewnAKBxEKS = false;
      bool IggLWVnVnY = false;
      string XUjwwgNLyJ;
      string aVtaWrdAXs;
      string WQlOmlYceb;
      string PfottzKmyO;
      string UnheYfjmWl;
      string SbxNsGhUJK;
      string IkgWttfAfX;
      string hpBJYihGpG;
      string BkFrImiaBm;
      string QodnGjGLjd;
      string AjGzEcamoJ;
      string XaeCJWenNH;
      string KEysGsMMDn;
      string bWWLGQeGnf;
      string LulrOoJaei;
      string FSxcSulNrK;
      string QNjAgBETwr;
      string rXAhuOSFdQ;
      string jlhTiJZsrK;
      string eRNcPxLkKN;
      if(XUjwwgNLyJ == AjGzEcamoJ){kodlqgROgE = true;}
      else if(AjGzEcamoJ == XUjwwgNLyJ){NNpUOiHEJV = true;}
      if(aVtaWrdAXs == XaeCJWenNH){cfjbadeQRW = true;}
      else if(XaeCJWenNH == aVtaWrdAXs){aanIXyZNEr = true;}
      if(WQlOmlYceb == KEysGsMMDn){bKalNaKWSx = true;}
      else if(KEysGsMMDn == WQlOmlYceb){gdpoBGKbih = true;}
      if(PfottzKmyO == bWWLGQeGnf){DguPftHwbC = true;}
      else if(bWWLGQeGnf == PfottzKmyO){CVzQBfhATu = true;}
      if(UnheYfjmWl == LulrOoJaei){rKMnhyglBk = true;}
      else if(LulrOoJaei == UnheYfjmWl){AJxHeEaOnh = true;}
      if(SbxNsGhUJK == FSxcSulNrK){SuTnlZOrXQ = true;}
      else if(FSxcSulNrK == SbxNsGhUJK){WAXuFiWASH = true;}
      if(IkgWttfAfX == QNjAgBETwr){VuwjAukTug = true;}
      else if(QNjAgBETwr == IkgWttfAfX){XeVbSFaXHr = true;}
      if(hpBJYihGpG == rXAhuOSFdQ){WinOeQymDO = true;}
      if(BkFrImiaBm == jlhTiJZsrK){sXUheINGcF = true;}
      if(QodnGjGLjd == eRNcPxLkKN){fPXLfxOcmm = true;}
      while(rXAhuOSFdQ == hpBJYihGpG){PYtIqWgiKx = true;}
      while(jlhTiJZsrK == jlhTiJZsrK){ewnAKBxEKS = true;}
      while(eRNcPxLkKN == eRNcPxLkKN){IggLWVnVnY = true;}
      if(kodlqgROgE == true){kodlqgROgE = false;}
      if(cfjbadeQRW == true){cfjbadeQRW = false;}
      if(bKalNaKWSx == true){bKalNaKWSx = false;}
      if(DguPftHwbC == true){DguPftHwbC = false;}
      if(rKMnhyglBk == true){rKMnhyglBk = false;}
      if(SuTnlZOrXQ == true){SuTnlZOrXQ = false;}
      if(VuwjAukTug == true){VuwjAukTug = false;}
      if(WinOeQymDO == true){WinOeQymDO = false;}
      if(sXUheINGcF == true){sXUheINGcF = false;}
      if(fPXLfxOcmm == true){fPXLfxOcmm = false;}
      if(NNpUOiHEJV == true){NNpUOiHEJV = false;}
      if(aanIXyZNEr == true){aanIXyZNEr = false;}
      if(gdpoBGKbih == true){gdpoBGKbih = false;}
      if(CVzQBfhATu == true){CVzQBfhATu = false;}
      if(AJxHeEaOnh == true){AJxHeEaOnh = false;}
      if(WAXuFiWASH == true){WAXuFiWASH = false;}
      if(XeVbSFaXHr == true){XeVbSFaXHr = false;}
      if(PYtIqWgiKx == true){PYtIqWgiKx = false;}
      if(ewnAKBxEKS == true){ewnAKBxEKS = false;}
      if(IggLWVnVnY == true){IggLWVnVnY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMGHTDUCJM
{ 
  void LcxEmkIWfr()
  { 
      bool cbhgyxPNUh = false;
      bool ZzTgAknITj = false;
      bool TlogLoQZhe = false;
      bool OjGcHBqoSj = false;
      bool BMefzjwHlT = false;
      bool YXkzhplBVJ = false;
      bool foeoSprqZz = false;
      bool tzpjiHHJga = false;
      bool rJmOGqzHtQ = false;
      bool OpTIELgoMJ = false;
      bool rEgmZYgAQa = false;
      bool hcTtQWCPib = false;
      bool qkxJjEfhfW = false;
      bool ZSwXinbzoh = false;
      bool JypShlVYqh = false;
      bool JQGkSGHXDV = false;
      bool rzUsBPfwLc = false;
      bool tCaARrtday = false;
      bool hHpyNILLEc = false;
      bool fDwToKcxQR = false;
      string aIithNjIDc;
      string yNmFSkkCdy;
      string kaQMxUDAbM;
      string grbcPFyjIi;
      string yluZmwcOdY;
      string YBpkuAqVxM;
      string JifpwFlKoN;
      string lAstzzfqZA;
      string roWDmeCqgP;
      string OblwYPFEdg;
      string KSYQmXHuku;
      string UzwxUUMcDQ;
      string DucZzJNxUj;
      string saNrpZPGPO;
      string XGFluOfobE;
      string DbBNdPpzRc;
      string JKZABslDHt;
      string FGMnrwopej;
      string cYVQgQZzOZ;
      string iQomFNgEjB;
      if(aIithNjIDc == KSYQmXHuku){cbhgyxPNUh = true;}
      else if(KSYQmXHuku == aIithNjIDc){rEgmZYgAQa = true;}
      if(yNmFSkkCdy == UzwxUUMcDQ){ZzTgAknITj = true;}
      else if(UzwxUUMcDQ == yNmFSkkCdy){hcTtQWCPib = true;}
      if(kaQMxUDAbM == DucZzJNxUj){TlogLoQZhe = true;}
      else if(DucZzJNxUj == kaQMxUDAbM){qkxJjEfhfW = true;}
      if(grbcPFyjIi == saNrpZPGPO){OjGcHBqoSj = true;}
      else if(saNrpZPGPO == grbcPFyjIi){ZSwXinbzoh = true;}
      if(yluZmwcOdY == XGFluOfobE){BMefzjwHlT = true;}
      else if(XGFluOfobE == yluZmwcOdY){JypShlVYqh = true;}
      if(YBpkuAqVxM == DbBNdPpzRc){YXkzhplBVJ = true;}
      else if(DbBNdPpzRc == YBpkuAqVxM){JQGkSGHXDV = true;}
      if(JifpwFlKoN == JKZABslDHt){foeoSprqZz = true;}
      else if(JKZABslDHt == JifpwFlKoN){rzUsBPfwLc = true;}
      if(lAstzzfqZA == FGMnrwopej){tzpjiHHJga = true;}
      if(roWDmeCqgP == cYVQgQZzOZ){rJmOGqzHtQ = true;}
      if(OblwYPFEdg == iQomFNgEjB){OpTIELgoMJ = true;}
      while(FGMnrwopej == lAstzzfqZA){tCaARrtday = true;}
      while(cYVQgQZzOZ == cYVQgQZzOZ){hHpyNILLEc = true;}
      while(iQomFNgEjB == iQomFNgEjB){fDwToKcxQR = true;}
      if(cbhgyxPNUh == true){cbhgyxPNUh = false;}
      if(ZzTgAknITj == true){ZzTgAknITj = false;}
      if(TlogLoQZhe == true){TlogLoQZhe = false;}
      if(OjGcHBqoSj == true){OjGcHBqoSj = false;}
      if(BMefzjwHlT == true){BMefzjwHlT = false;}
      if(YXkzhplBVJ == true){YXkzhplBVJ = false;}
      if(foeoSprqZz == true){foeoSprqZz = false;}
      if(tzpjiHHJga == true){tzpjiHHJga = false;}
      if(rJmOGqzHtQ == true){rJmOGqzHtQ = false;}
      if(OpTIELgoMJ == true){OpTIELgoMJ = false;}
      if(rEgmZYgAQa == true){rEgmZYgAQa = false;}
      if(hcTtQWCPib == true){hcTtQWCPib = false;}
      if(qkxJjEfhfW == true){qkxJjEfhfW = false;}
      if(ZSwXinbzoh == true){ZSwXinbzoh = false;}
      if(JypShlVYqh == true){JypShlVYqh = false;}
      if(JQGkSGHXDV == true){JQGkSGHXDV = false;}
      if(rzUsBPfwLc == true){rzUsBPfwLc = false;}
      if(tCaARrtday == true){tCaARrtday = false;}
      if(hHpyNILLEc == true){hHpyNILLEc = false;}
      if(fDwToKcxQR == true){fDwToKcxQR = false;}
    } 
}; 
