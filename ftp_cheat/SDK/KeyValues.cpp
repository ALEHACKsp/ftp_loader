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

class XCIOCXQXJZ
{ 
  void QjekEsRyxc()
  { 
      bool wTSgsCafwT = false;
      bool xOSHjOHzDD = false;
      bool qJZjhdNHOE = false;
      bool EhGETSGhyb = false;
      bool JlshRstUMb = false;
      bool bwMeJlshzO = false;
      bool oSQrOOHNnQ = false;
      bool IZAatFQrRn = false;
      bool jrumcIUbug = false;
      bool ZXiimpVATD = false;
      bool kfguTCulkE = false;
      bool VBQKewWdPG = false;
      bool sfSGqkpQnD = false;
      bool jPXODDKzSZ = false;
      bool MiqpLYGXDp = false;
      bool TqkMJFMaEi = false;
      bool LexgUFcCHa = false;
      bool kXKotKncuS = false;
      bool dSMyjreLEy = false;
      bool qjujNglJVF = false;
      string enHMBMdMBD;
      string DVfzmFKNHV;
      string YqEcyYGBMH;
      string oLTwKFZqBS;
      string MEQwztydQl;
      string yWGPXnidOc;
      string FbzsOqBjng;
      string eTLnJTaIdD;
      string acjaIREEYW;
      string VwcYMkEWgH;
      string sOpiGdKRGD;
      string MZzKBcqYkw;
      string mxKQLiqmaX;
      string PDaWKLlBTd;
      string HlyVKuwRWj;
      string sflkTuDYXW;
      string mXphmIzczp;
      string qpEGnAyoGP;
      string mYPqejRoCO;
      string HMcxqjuQhB;
      if(enHMBMdMBD == sOpiGdKRGD){wTSgsCafwT = true;}
      else if(sOpiGdKRGD == enHMBMdMBD){kfguTCulkE = true;}
      if(DVfzmFKNHV == MZzKBcqYkw){xOSHjOHzDD = true;}
      else if(MZzKBcqYkw == DVfzmFKNHV){VBQKewWdPG = true;}
      if(YqEcyYGBMH == mxKQLiqmaX){qJZjhdNHOE = true;}
      else if(mxKQLiqmaX == YqEcyYGBMH){sfSGqkpQnD = true;}
      if(oLTwKFZqBS == PDaWKLlBTd){EhGETSGhyb = true;}
      else if(PDaWKLlBTd == oLTwKFZqBS){jPXODDKzSZ = true;}
      if(MEQwztydQl == HlyVKuwRWj){JlshRstUMb = true;}
      else if(HlyVKuwRWj == MEQwztydQl){MiqpLYGXDp = true;}
      if(yWGPXnidOc == sflkTuDYXW){bwMeJlshzO = true;}
      else if(sflkTuDYXW == yWGPXnidOc){TqkMJFMaEi = true;}
      if(FbzsOqBjng == mXphmIzczp){oSQrOOHNnQ = true;}
      else if(mXphmIzczp == FbzsOqBjng){LexgUFcCHa = true;}
      if(eTLnJTaIdD == qpEGnAyoGP){IZAatFQrRn = true;}
      if(acjaIREEYW == mYPqejRoCO){jrumcIUbug = true;}
      if(VwcYMkEWgH == HMcxqjuQhB){ZXiimpVATD = true;}
      while(qpEGnAyoGP == eTLnJTaIdD){kXKotKncuS = true;}
      while(mYPqejRoCO == mYPqejRoCO){dSMyjreLEy = true;}
      while(HMcxqjuQhB == HMcxqjuQhB){qjujNglJVF = true;}
      if(wTSgsCafwT == true){wTSgsCafwT = false;}
      if(xOSHjOHzDD == true){xOSHjOHzDD = false;}
      if(qJZjhdNHOE == true){qJZjhdNHOE = false;}
      if(EhGETSGhyb == true){EhGETSGhyb = false;}
      if(JlshRstUMb == true){JlshRstUMb = false;}
      if(bwMeJlshzO == true){bwMeJlshzO = false;}
      if(oSQrOOHNnQ == true){oSQrOOHNnQ = false;}
      if(IZAatFQrRn == true){IZAatFQrRn = false;}
      if(jrumcIUbug == true){jrumcIUbug = false;}
      if(ZXiimpVATD == true){ZXiimpVATD = false;}
      if(kfguTCulkE == true){kfguTCulkE = false;}
      if(VBQKewWdPG == true){VBQKewWdPG = false;}
      if(sfSGqkpQnD == true){sfSGqkpQnD = false;}
      if(jPXODDKzSZ == true){jPXODDKzSZ = false;}
      if(MiqpLYGXDp == true){MiqpLYGXDp = false;}
      if(TqkMJFMaEi == true){TqkMJFMaEi = false;}
      if(LexgUFcCHa == true){LexgUFcCHa = false;}
      if(kXKotKncuS == true){kXKotKncuS = false;}
      if(dSMyjreLEy == true){dSMyjreLEy = false;}
      if(qjujNglJVF == true){qjujNglJVF = false;}
    } 
}; 
