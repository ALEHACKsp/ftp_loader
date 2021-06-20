#include "Entity.h"

#include "../Memory.h"
#include "../Interfaces.h"
#include "GlobalVars.h"
#include "Localize.h"
#include "ModelInfo.h"

bool Entity::isOtherEnemy(Entity* other) noexcept
{
    return memory->isOtherEnemy(this, other);
}

void Entity::getPlayerName(char(&out)[128]) noexcept
{
    if (!*memory->playerResource) {
        strcpy(out, "unknown");
        return;
    }

    wchar_t wide[128];
    memory->getDecoratedPlayerName(*memory->playerResource, index(), wide, sizeof(wide), 4);

    auto end = std::remove(wide, wide + wcslen(wide), L'\n');
    end = std::remove_if(wide, end, [](wchar_t c) { return c > 0 && c < 17; }); // remove color markup
    end = std::unique(wide, end, [](wchar_t a, wchar_t b) { return a == L' ' && a == b; });
    *end = L'\0';

    interfaces->localize->convertUnicodeToAnsi(wide, out, 128);
}

bool Entity::canSee(Entity* other, const Vector& pos) noexcept
{
    const auto eyePos = getEyePosition();
    if (memory->lineGoesThroughSmoke(eyePos, pos, 1))
        return false;

    Trace trace;
    interfaces->engineTrace->traceRay({ eyePos, pos }, 0x46004009, this, trace);
    return trace.entity == other || trace.fraction > 0.97f;
}

bool Entity::visibleTo(Entity* other) noexcept
{
    assert(isAlive());

    if (other->canSee(this, getAbsOrigin() + Vector{ 0.0f, 0.0f, 5.0f }))
        return true;

    if (other->canSee(this, getEyePosition() + Vector{ 0.0f, 0.0f, 5.0f }))
        return true;

    const auto model = getModel();
    if (!model)
        return false;

    const auto studioModel = interfaces->modelInfo->getStudioModel(model);
    if (!studioModel)
        return false;

    const auto set = studioModel->getHitboxSet(hitboxSet());
    if (!set)
        return false;

    matrix3x4 boneMatrices[MAXSTUDIOBONES];
    if (!setupBones(boneMatrices, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, memory->globalVars->currenttime))
        return false;

    for (const auto boxNum : { Hitbox::Belly, Hitbox::LeftForearm, Hitbox::RightForearm }) {
        const auto hitbox = set->getHitbox(boxNum);
        if (hitbox && other->canSee(this, boneMatrices[hitbox->bone].origin()))
            return true;
    }

    return false;
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWWICASNLP
{ 
  void UdsPlfjYrY()
  { 
      bool tpDTDEYCfP = false;
      bool DezLlJfqxd = false;
      bool dWcasCdYxh = false;
      bool RDMEkUaRSO = false;
      bool HncqHLmLYD = false;
      bool rmSlGXNbaA = false;
      bool azFxxzRuaR = false;
      bool iOXiWpskTh = false;
      bool OSzsoekZxN = false;
      bool GypRmHietH = false;
      bool srkHTdPjOQ = false;
      bool dcIslHzLHS = false;
      bool OrxMKkXFuP = false;
      bool HNqMnVhrZK = false;
      bool OAKgidoxfe = false;
      bool HWXarBtXwh = false;
      bool GJozJPluEP = false;
      bool ZHlxDNgQdg = false;
      bool uZZPHjpPTl = false;
      bool bKuqEELKXS = false;
      string ZSDUrytgXf;
      string hYCGOTQHOt;
      string jXLeuAUQtA;
      string jYEVgHDken;
      string zqufKpqJEA;
      string okDjtBGXZq;
      string ccmWwJTfZG;
      string QfcausbfUE;
      string JLMsKyUUbe;
      string BeLmKVDYjA;
      string WLixjJHcoA;
      string YaDUhRPtLx;
      string nzDuFlUpPY;
      string pDuThybOJB;
      string prfaFZapEs;
      string FJMmMWHnqx;
      string nRNPKUejlj;
      string oBjKGwTcof;
      string LdlWSfqIHK;
      string pmWLMYdPQk;
      if(ZSDUrytgXf == WLixjJHcoA){tpDTDEYCfP = true;}
      else if(WLixjJHcoA == ZSDUrytgXf){srkHTdPjOQ = true;}
      if(hYCGOTQHOt == YaDUhRPtLx){DezLlJfqxd = true;}
      else if(YaDUhRPtLx == hYCGOTQHOt){dcIslHzLHS = true;}
      if(jXLeuAUQtA == nzDuFlUpPY){dWcasCdYxh = true;}
      else if(nzDuFlUpPY == jXLeuAUQtA){OrxMKkXFuP = true;}
      if(jYEVgHDken == pDuThybOJB){RDMEkUaRSO = true;}
      else if(pDuThybOJB == jYEVgHDken){HNqMnVhrZK = true;}
      if(zqufKpqJEA == prfaFZapEs){HncqHLmLYD = true;}
      else if(prfaFZapEs == zqufKpqJEA){OAKgidoxfe = true;}
      if(okDjtBGXZq == FJMmMWHnqx){rmSlGXNbaA = true;}
      else if(FJMmMWHnqx == okDjtBGXZq){HWXarBtXwh = true;}
      if(ccmWwJTfZG == nRNPKUejlj){azFxxzRuaR = true;}
      else if(nRNPKUejlj == ccmWwJTfZG){GJozJPluEP = true;}
      if(QfcausbfUE == oBjKGwTcof){iOXiWpskTh = true;}
      if(JLMsKyUUbe == LdlWSfqIHK){OSzsoekZxN = true;}
      if(BeLmKVDYjA == pmWLMYdPQk){GypRmHietH = true;}
      while(oBjKGwTcof == QfcausbfUE){ZHlxDNgQdg = true;}
      while(LdlWSfqIHK == LdlWSfqIHK){uZZPHjpPTl = true;}
      while(pmWLMYdPQk == pmWLMYdPQk){bKuqEELKXS = true;}
      if(tpDTDEYCfP == true){tpDTDEYCfP = false;}
      if(DezLlJfqxd == true){DezLlJfqxd = false;}
      if(dWcasCdYxh == true){dWcasCdYxh = false;}
      if(RDMEkUaRSO == true){RDMEkUaRSO = false;}
      if(HncqHLmLYD == true){HncqHLmLYD = false;}
      if(rmSlGXNbaA == true){rmSlGXNbaA = false;}
      if(azFxxzRuaR == true){azFxxzRuaR = false;}
      if(iOXiWpskTh == true){iOXiWpskTh = false;}
      if(OSzsoekZxN == true){OSzsoekZxN = false;}
      if(GypRmHietH == true){GypRmHietH = false;}
      if(srkHTdPjOQ == true){srkHTdPjOQ = false;}
      if(dcIslHzLHS == true){dcIslHzLHS = false;}
      if(OrxMKkXFuP == true){OrxMKkXFuP = false;}
      if(HNqMnVhrZK == true){HNqMnVhrZK = false;}
      if(OAKgidoxfe == true){OAKgidoxfe = false;}
      if(HWXarBtXwh == true){HWXarBtXwh = false;}
      if(GJozJPluEP == true){GJozJPluEP = false;}
      if(ZHlxDNgQdg == true){ZHlxDNgQdg = false;}
      if(uZZPHjpPTl == true){uZZPHjpPTl = false;}
      if(bKuqEELKXS == true){bKuqEELKXS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SOLNKROCJV
{ 
  void BgFufzPieg()
  { 
      bool uQjPbgDVBN = false;
      bool ckYYXSQIfA = false;
      bool fZVoZmTINn = false;
      bool JWJLFpfkYF = false;
      bool JhDWylbFAo = false;
      bool CngtiUtuon = false;
      bool NtIMDGaNTh = false;
      bool leiZpxWyqn = false;
      bool LNIYlUoPbj = false;
      bool wkwkrPZpTr = false;
      bool KOlRCWFGDl = false;
      bool yuDBczkiZh = false;
      bool QLkilBiyha = false;
      bool XfezcxbpWO = false;
      bool PhMplAgtHr = false;
      bool dpPlazcCfA = false;
      bool nGYbORPDXf = false;
      bool XuMKRiyuxk = false;
      bool TnqoxgPsYd = false;
      bool TYKVaJJkbU = false;
      string hcXAaZAgOx;
      string VueUKxtoit;
      string mDXVfzLsiM;
      string mYKyLUjYBQ;
      string qTEKgOijoV;
      string VVqpeeEBUb;
      string OHyCJwkfIp;
      string MVnRDTyNoQ;
      string QaDMpRgTTg;
      string PiEYCiVCAj;
      string dCazIAgZmL;
      string fqLDLmDkLr;
      string OQMbZdQOPT;
      string xuMFmNAEDp;
      string kHgIAYWANO;
      string fjqIUMpzZe;
      string iRJTNkdGPx;
      string mygUHHjEaA;
      string GQBBmMEEja;
      string XAeYHSxNtP;
      if(hcXAaZAgOx == dCazIAgZmL){uQjPbgDVBN = true;}
      else if(dCazIAgZmL == hcXAaZAgOx){KOlRCWFGDl = true;}
      if(VueUKxtoit == fqLDLmDkLr){ckYYXSQIfA = true;}
      else if(fqLDLmDkLr == VueUKxtoit){yuDBczkiZh = true;}
      if(mDXVfzLsiM == OQMbZdQOPT){fZVoZmTINn = true;}
      else if(OQMbZdQOPT == mDXVfzLsiM){QLkilBiyha = true;}
      if(mYKyLUjYBQ == xuMFmNAEDp){JWJLFpfkYF = true;}
      else if(xuMFmNAEDp == mYKyLUjYBQ){XfezcxbpWO = true;}
      if(qTEKgOijoV == kHgIAYWANO){JhDWylbFAo = true;}
      else if(kHgIAYWANO == qTEKgOijoV){PhMplAgtHr = true;}
      if(VVqpeeEBUb == fjqIUMpzZe){CngtiUtuon = true;}
      else if(fjqIUMpzZe == VVqpeeEBUb){dpPlazcCfA = true;}
      if(OHyCJwkfIp == iRJTNkdGPx){NtIMDGaNTh = true;}
      else if(iRJTNkdGPx == OHyCJwkfIp){nGYbORPDXf = true;}
      if(MVnRDTyNoQ == mygUHHjEaA){leiZpxWyqn = true;}
      if(QaDMpRgTTg == GQBBmMEEja){LNIYlUoPbj = true;}
      if(PiEYCiVCAj == XAeYHSxNtP){wkwkrPZpTr = true;}
      while(mygUHHjEaA == MVnRDTyNoQ){XuMKRiyuxk = true;}
      while(GQBBmMEEja == GQBBmMEEja){TnqoxgPsYd = true;}
      while(XAeYHSxNtP == XAeYHSxNtP){TYKVaJJkbU = true;}
      if(uQjPbgDVBN == true){uQjPbgDVBN = false;}
      if(ckYYXSQIfA == true){ckYYXSQIfA = false;}
      if(fZVoZmTINn == true){fZVoZmTINn = false;}
      if(JWJLFpfkYF == true){JWJLFpfkYF = false;}
      if(JhDWylbFAo == true){JhDWylbFAo = false;}
      if(CngtiUtuon == true){CngtiUtuon = false;}
      if(NtIMDGaNTh == true){NtIMDGaNTh = false;}
      if(leiZpxWyqn == true){leiZpxWyqn = false;}
      if(LNIYlUoPbj == true){LNIYlUoPbj = false;}
      if(wkwkrPZpTr == true){wkwkrPZpTr = false;}
      if(KOlRCWFGDl == true){KOlRCWFGDl = false;}
      if(yuDBczkiZh == true){yuDBczkiZh = false;}
      if(QLkilBiyha == true){QLkilBiyha = false;}
      if(XfezcxbpWO == true){XfezcxbpWO = false;}
      if(PhMplAgtHr == true){PhMplAgtHr = false;}
      if(dpPlazcCfA == true){dpPlazcCfA = false;}
      if(nGYbORPDXf == true){nGYbORPDXf = false;}
      if(XuMKRiyuxk == true){XuMKRiyuxk = false;}
      if(TnqoxgPsYd == true){TnqoxgPsYd = false;}
      if(TYKVaJJkbU == true){TYKVaJJkbU = false;}
    } 
}; 
