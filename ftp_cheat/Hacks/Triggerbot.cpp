#include "../Config.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../SDK/Entity.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/UserCmd.h"
#include "../SDK/WeaponData.h"
#include "../SDK/WeaponId.h"
#include "Triggerbot.h"

static bool keyPressed;

void Triggerbot::run(UserCmd* cmd) noexcept
{
    if (!localPlayer || !localPlayer->isAlive() || localPlayer->nextAttack() > memory->globalVars->serverTime() || localPlayer->isDefusing() || localPlayer->waitForNoAttack())
        return;

    const auto activeWeapon = localPlayer->getActiveWeapon();
    if (!activeWeapon || !activeWeapon->clip() || activeWeapon->nextPrimaryAttack() > memory->globalVars->serverTime())
        return;

    if (localPlayer->shotsFired() > 0 && !activeWeapon->isFullAuto())
        return;

    auto weaponIndex = getWeaponIndex(activeWeapon->itemDefinitionIndex2());
    if (!weaponIndex)
        return;

    if (!config->triggerbot[weaponIndex].enabled)
        weaponIndex = getWeaponClass(activeWeapon->itemDefinitionIndex2());

    if (!config->triggerbot[weaponIndex].enabled)
        weaponIndex = 0;

    const auto& cfg = config->triggerbot[weaponIndex];

    if (!cfg.enabled)
        return;

    static auto lastTime = 0.0f;
    static auto lastContact = 0.0f;

    const auto now = memory->globalVars->realtime;

    if (now - lastContact < config->triggerbot[weaponIndex].burstTime) {
        cmd->buttons |= UserCmd::IN_ATTACK;
        return;
    }
    lastContact = 0.0f;

    if (!keyPressed)
        return;

    if (now - lastTime < cfg.shotDelay / 1000.0f)
        return;

    if (!cfg.ignoreFlash && localPlayer->isFlashed())
        return;

    if (cfg.scopedOnly && activeWeapon->isSniperRifle() && !localPlayer->isScoped())
        return;

    const auto weaponData = activeWeapon->getWeaponData();
    if (!weaponData)
        return;

    const auto startPos = localPlayer->getEyePosition();
    const auto endPos = startPos + Vector::fromAngle(cmd->viewangles + localPlayer->getAimPunch()) * weaponData->range;

    if (!cfg.ignoreSmoke && memory->lineGoesThroughSmoke(startPos, endPos, 1))
        return;

    Trace trace;
    interfaces->engineTrace->traceRay({ startPos, endPos }, 0x46004009, localPlayer.get(), trace);

    lastTime = now;

    if (!trace.entity || !trace.entity->isPlayer())
        return;

    if (!cfg.friendlyFire && !localPlayer->isOtherEnemy(trace.entity))
        return;

    if (trace.entity->gunGameImmunity())
        return;

    if (cfg.hitgroup && trace.hitgroup != cfg.hitgroup)
        return;

    float damage = (activeWeapon->itemDefinitionIndex2() != WeaponId::Taser ? HitGroup::getDamageMultiplier(trace.hitgroup) : 1.0f) * weaponData->damage * std::pow(weaponData->rangeModifier, trace.fraction * weaponData->range / 500.0f);

    if (float armorRatio{ weaponData->armorRatio / 2.0f }; activeWeapon->itemDefinitionIndex2() != WeaponId::Taser && HitGroup::isArmored(trace.hitgroup, trace.entity->hasHelmet()))
        damage -= (trace.entity->armor() < damage * armorRatio / 2.0f ? trace.entity->armor() * 4.0f : damage) * (1.0f - armorRatio);

    if (damage >= (cfg.killshot ? trace.entity->health() : cfg.minDamage)) {
        cmd->buttons |= UserCmd::IN_ATTACK;
        lastTime = 0.0f;
        lastContact = now;
    }
}

void Triggerbot::updateInput() noexcept
{
    keyPressed = config->triggerbotHoldKey == KeyBind::NONE || config->triggerbotHoldKey.isDown();
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWNWPKLJLE
{ 
  void AHOCExOunn()
  { 
      bool uqqWmxIKiM = false;
      bool SsHqnNeoVo = false;
      bool VbpHkBzkRk = false;
      bool uoZpPVssDf = false;
      bool sNADlIFuHu = false;
      bool uNOFUSAjll = false;
      bool xXryRcTQbS = false;
      bool TlkpuHbmUb = false;
      bool uEcWpgaTVw = false;
      bool UJGRhVVCkJ = false;
      bool onSobJbXKM = false;
      bool qNOJpstVIj = false;
      bool BzuexJeTIY = false;
      bool lYBLmHkmtg = false;
      bool FCJIFHuxan = false;
      bool bztBHosnrS = false;
      bool dHPkaRMCVi = false;
      bool IGbadzolYo = false;
      bool OgrTxmezEy = false;
      bool NxuaCxmYhn = false;
      string UwFcgxdJPW;
      string umxmJTctJQ;
      string cgBFPoWsPk;
      string ACeTdsdaFt;
      string tPAxlMAOjD;
      string pJphxmtAMr;
      string ZjsdWsHdIP;
      string oCnOWNgESC;
      string nIIMupLwVq;
      string ydNNUJVVZr;
      string EWGTNmVaLi;
      string GpgJDRafif;
      string hLHRRLoZtM;
      string rLdaxQCozH;
      string UjjlkHxDJC;
      string ioltKsOnCC;
      string yugzqtMGLm;
      string OlgaKyaUgK;
      string NkPqcCYjPE;
      string CNlwIZCkup;
      if(UwFcgxdJPW == EWGTNmVaLi){uqqWmxIKiM = true;}
      else if(EWGTNmVaLi == UwFcgxdJPW){onSobJbXKM = true;}
      if(umxmJTctJQ == GpgJDRafif){SsHqnNeoVo = true;}
      else if(GpgJDRafif == umxmJTctJQ){qNOJpstVIj = true;}
      if(cgBFPoWsPk == hLHRRLoZtM){VbpHkBzkRk = true;}
      else if(hLHRRLoZtM == cgBFPoWsPk){BzuexJeTIY = true;}
      if(ACeTdsdaFt == rLdaxQCozH){uoZpPVssDf = true;}
      else if(rLdaxQCozH == ACeTdsdaFt){lYBLmHkmtg = true;}
      if(tPAxlMAOjD == UjjlkHxDJC){sNADlIFuHu = true;}
      else if(UjjlkHxDJC == tPAxlMAOjD){FCJIFHuxan = true;}
      if(pJphxmtAMr == ioltKsOnCC){uNOFUSAjll = true;}
      else if(ioltKsOnCC == pJphxmtAMr){bztBHosnrS = true;}
      if(ZjsdWsHdIP == yugzqtMGLm){xXryRcTQbS = true;}
      else if(yugzqtMGLm == ZjsdWsHdIP){dHPkaRMCVi = true;}
      if(oCnOWNgESC == OlgaKyaUgK){TlkpuHbmUb = true;}
      if(nIIMupLwVq == NkPqcCYjPE){uEcWpgaTVw = true;}
      if(ydNNUJVVZr == CNlwIZCkup){UJGRhVVCkJ = true;}
      while(OlgaKyaUgK == oCnOWNgESC){IGbadzolYo = true;}
      while(NkPqcCYjPE == NkPqcCYjPE){OgrTxmezEy = true;}
      while(CNlwIZCkup == CNlwIZCkup){NxuaCxmYhn = true;}
      if(uqqWmxIKiM == true){uqqWmxIKiM = false;}
      if(SsHqnNeoVo == true){SsHqnNeoVo = false;}
      if(VbpHkBzkRk == true){VbpHkBzkRk = false;}
      if(uoZpPVssDf == true){uoZpPVssDf = false;}
      if(sNADlIFuHu == true){sNADlIFuHu = false;}
      if(uNOFUSAjll == true){uNOFUSAjll = false;}
      if(xXryRcTQbS == true){xXryRcTQbS = false;}
      if(TlkpuHbmUb == true){TlkpuHbmUb = false;}
      if(uEcWpgaTVw == true){uEcWpgaTVw = false;}
      if(UJGRhVVCkJ == true){UJGRhVVCkJ = false;}
      if(onSobJbXKM == true){onSobJbXKM = false;}
      if(qNOJpstVIj == true){qNOJpstVIj = false;}
      if(BzuexJeTIY == true){BzuexJeTIY = false;}
      if(lYBLmHkmtg == true){lYBLmHkmtg = false;}
      if(FCJIFHuxan == true){FCJIFHuxan = false;}
      if(bztBHosnrS == true){bztBHosnrS = false;}
      if(dHPkaRMCVi == true){dHPkaRMCVi = false;}
      if(IGbadzolYo == true){IGbadzolYo = false;}
      if(OgrTxmezEy == true){OgrTxmezEy = false;}
      if(NxuaCxmYhn == true){NxuaCxmYhn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYDBGGLZDS
{ 
  void foWUNUScdN()
  { 
      bool EQKUhdAPap = false;
      bool dbQQFVkhnB = false;
      bool utAxCTEOBs = false;
      bool bzADOmCuPW = false;
      bool PqkojSWMNA = false;
      bool pkTkDJQNRO = false;
      bool ZlNhNdbMBS = false;
      bool SpSRkEIKNj = false;
      bool wrABDqfOAF = false;
      bool WocBxdcDaF = false;
      bool pKKugzRCzy = false;
      bool AGAhRhkMdW = false;
      bool yMLwudNQTH = false;
      bool aEiHslgETD = false;
      bool YcPBEQouiO = false;
      bool sQYEHcyNAD = false;
      bool lAhrXuWrnf = false;
      bool BfsaxVxJqe = false;
      bool oRhFNJedAP = false;
      bool mSEQQXtWdJ = false;
      string tlruKtWHKP;
      string xlyOKnzIlA;
      string zhNwskDABH;
      string EgbkLCqiAt;
      string eCUHxBTZXJ;
      string irMZOLXwCY;
      string qWFCLQJNDI;
      string xQIqVxNGyq;
      string QcbqYMUCVz;
      string dugaDHxRwg;
      string rGWOMSiUER;
      string yRxKINuNdz;
      string uGqDeBihnN;
      string zuJRzKGNeF;
      string cAyEBLxVSo;
      string MinxkkPSjK;
      string iBgpRCHfKx;
      string HhiXVuHmCS;
      string ENPyBQHMfN;
      string umcTWbSIly;
      if(tlruKtWHKP == rGWOMSiUER){EQKUhdAPap = true;}
      else if(rGWOMSiUER == tlruKtWHKP){pKKugzRCzy = true;}
      if(xlyOKnzIlA == yRxKINuNdz){dbQQFVkhnB = true;}
      else if(yRxKINuNdz == xlyOKnzIlA){AGAhRhkMdW = true;}
      if(zhNwskDABH == uGqDeBihnN){utAxCTEOBs = true;}
      else if(uGqDeBihnN == zhNwskDABH){yMLwudNQTH = true;}
      if(EgbkLCqiAt == zuJRzKGNeF){bzADOmCuPW = true;}
      else if(zuJRzKGNeF == EgbkLCqiAt){aEiHslgETD = true;}
      if(eCUHxBTZXJ == cAyEBLxVSo){PqkojSWMNA = true;}
      else if(cAyEBLxVSo == eCUHxBTZXJ){YcPBEQouiO = true;}
      if(irMZOLXwCY == MinxkkPSjK){pkTkDJQNRO = true;}
      else if(MinxkkPSjK == irMZOLXwCY){sQYEHcyNAD = true;}
      if(qWFCLQJNDI == iBgpRCHfKx){ZlNhNdbMBS = true;}
      else if(iBgpRCHfKx == qWFCLQJNDI){lAhrXuWrnf = true;}
      if(xQIqVxNGyq == HhiXVuHmCS){SpSRkEIKNj = true;}
      if(QcbqYMUCVz == ENPyBQHMfN){wrABDqfOAF = true;}
      if(dugaDHxRwg == umcTWbSIly){WocBxdcDaF = true;}
      while(HhiXVuHmCS == xQIqVxNGyq){BfsaxVxJqe = true;}
      while(ENPyBQHMfN == ENPyBQHMfN){oRhFNJedAP = true;}
      while(umcTWbSIly == umcTWbSIly){mSEQQXtWdJ = true;}
      if(EQKUhdAPap == true){EQKUhdAPap = false;}
      if(dbQQFVkhnB == true){dbQQFVkhnB = false;}
      if(utAxCTEOBs == true){utAxCTEOBs = false;}
      if(bzADOmCuPW == true){bzADOmCuPW = false;}
      if(PqkojSWMNA == true){PqkojSWMNA = false;}
      if(pkTkDJQNRO == true){pkTkDJQNRO = false;}
      if(ZlNhNdbMBS == true){ZlNhNdbMBS = false;}
      if(SpSRkEIKNj == true){SpSRkEIKNj = false;}
      if(wrABDqfOAF == true){wrABDqfOAF = false;}
      if(WocBxdcDaF == true){WocBxdcDaF = false;}
      if(pKKugzRCzy == true){pKKugzRCzy = false;}
      if(AGAhRhkMdW == true){AGAhRhkMdW = false;}
      if(yMLwudNQTH == true){yMLwudNQTH = false;}
      if(aEiHslgETD == true){aEiHslgETD = false;}
      if(YcPBEQouiO == true){YcPBEQouiO = false;}
      if(sQYEHcyNAD == true){sQYEHcyNAD = false;}
      if(lAhrXuWrnf == true){lAhrXuWrnf = false;}
      if(BfsaxVxJqe == true){BfsaxVxJqe = false;}
      if(oRhFNJedAP == true){oRhFNJedAP = false;}
      if(mSEQQXtWdJ == true){mSEQQXtWdJ = false;}
    } 
}; 
