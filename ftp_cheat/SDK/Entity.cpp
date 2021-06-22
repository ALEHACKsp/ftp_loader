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

class TNDEFKXJBN
{ 
  void oJOeVFmpFB()
  { 
      bool SYPYCmLXXD = false;
      bool BMRJSnBYle = false;
      bool YLClGmmxWn = false;
      bool HOGmJQNIqe = false;
      bool FAhEATuiXk = false;
      bool rePniGWcRP = false;
      bool zNAiumGdzB = false;
      bool ashGYXdylm = false;
      bool rEZkucySEC = false;
      bool tjpberAyIM = false;
      bool MQiVKzwIOL = false;
      bool cXpeWumPmS = false;
      bool nmZxGqCGag = false;
      bool XeoYZbVDau = false;
      bool fpDrZVsLEj = false;
      bool EjKpYZqlPT = false;
      bool xphhnxiREu = false;
      bool ZioqlyjgWj = false;
      bool xqCqbmTzAA = false;
      bool jinGypIVEb = false;
      string hWGUkOgSIT;
      string FTAktNKjUZ;
      string DoPzJjzxBd;
      string AgBlnUXTVs;
      string LCmlZFoKWW;
      string nrrEMrHHKB;
      string PjRdTYSNwZ;
      string opOaNBCdYE;
      string tnaeoHnwZu;
      string NQJTdbkIRA;
      string maOxgydQpL;
      string pchFGaIlnL;
      string jVnALYgtxl;
      string PsLXRTZcyq;
      string dXFOFjiDMD;
      string SzUFQQmNkI;
      string RiTEuxRJmm;
      string AfnwhMPZub;
      string pchtSQYFHB;
      string fMrpZtEBSH;
      if(hWGUkOgSIT == maOxgydQpL){SYPYCmLXXD = true;}
      else if(maOxgydQpL == hWGUkOgSIT){MQiVKzwIOL = true;}
      if(FTAktNKjUZ == pchFGaIlnL){BMRJSnBYle = true;}
      else if(pchFGaIlnL == FTAktNKjUZ){cXpeWumPmS = true;}
      if(DoPzJjzxBd == jVnALYgtxl){YLClGmmxWn = true;}
      else if(jVnALYgtxl == DoPzJjzxBd){nmZxGqCGag = true;}
      if(AgBlnUXTVs == PsLXRTZcyq){HOGmJQNIqe = true;}
      else if(PsLXRTZcyq == AgBlnUXTVs){XeoYZbVDau = true;}
      if(LCmlZFoKWW == dXFOFjiDMD){FAhEATuiXk = true;}
      else if(dXFOFjiDMD == LCmlZFoKWW){fpDrZVsLEj = true;}
      if(nrrEMrHHKB == SzUFQQmNkI){rePniGWcRP = true;}
      else if(SzUFQQmNkI == nrrEMrHHKB){EjKpYZqlPT = true;}
      if(PjRdTYSNwZ == RiTEuxRJmm){zNAiumGdzB = true;}
      else if(RiTEuxRJmm == PjRdTYSNwZ){xphhnxiREu = true;}
      if(opOaNBCdYE == AfnwhMPZub){ashGYXdylm = true;}
      if(tnaeoHnwZu == pchtSQYFHB){rEZkucySEC = true;}
      if(NQJTdbkIRA == fMrpZtEBSH){tjpberAyIM = true;}
      while(AfnwhMPZub == opOaNBCdYE){ZioqlyjgWj = true;}
      while(pchtSQYFHB == pchtSQYFHB){xqCqbmTzAA = true;}
      while(fMrpZtEBSH == fMrpZtEBSH){jinGypIVEb = true;}
      if(SYPYCmLXXD == true){SYPYCmLXXD = false;}
      if(BMRJSnBYle == true){BMRJSnBYle = false;}
      if(YLClGmmxWn == true){YLClGmmxWn = false;}
      if(HOGmJQNIqe == true){HOGmJQNIqe = false;}
      if(FAhEATuiXk == true){FAhEATuiXk = false;}
      if(rePniGWcRP == true){rePniGWcRP = false;}
      if(zNAiumGdzB == true){zNAiumGdzB = false;}
      if(ashGYXdylm == true){ashGYXdylm = false;}
      if(rEZkucySEC == true){rEZkucySEC = false;}
      if(tjpberAyIM == true){tjpberAyIM = false;}
      if(MQiVKzwIOL == true){MQiVKzwIOL = false;}
      if(cXpeWumPmS == true){cXpeWumPmS = false;}
      if(nmZxGqCGag == true){nmZxGqCGag = false;}
      if(XeoYZbVDau == true){XeoYZbVDau = false;}
      if(fpDrZVsLEj == true){fpDrZVsLEj = false;}
      if(EjKpYZqlPT == true){EjKpYZqlPT = false;}
      if(xphhnxiREu == true){xphhnxiREu = false;}
      if(ZioqlyjgWj == true){ZioqlyjgWj = false;}
      if(xqCqbmTzAA == true){xqCqbmTzAA = false;}
      if(jinGypIVEb == true){jinGypIVEb = false;}
    } 
}; 
