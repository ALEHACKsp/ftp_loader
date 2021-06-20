#include <cassert>
#include <utility>

#include "EventListener.h"
#include "fnv.h"
#include "GameData.h"
#include "Hacks/Misc.h"
#include "Hacks/InventoryChanger.h"
#include "Hacks/Visuals.h"
#include "Interfaces.h"
#include "Memory.h"
#include "SDK/UtlVector.h"

EventListener::EventListener() noexcept
{
    assert(interfaces);

    // If you add here listeners which aren't used by client.dll (e.g., item_purchase, bullet_impact), the cheat will be detected by AntiDLL (community anticheat).
    // Instead, register listeners dynamically and only when certain functions are enabled - see Misc::updateEventListeners(), Visuals::updateEventListeners()

    const auto gameEventManager = interfaces->gameEventManager;
    gameEventManager->addListener(this, "round_start");
    gameEventManager->addListener(this, "round_freeze_end");
    gameEventManager->addListener(this, "player_hurt");
    gameEventManager->addListener(this, "player_death");
    gameEventManager->addListener(this, "vote_cast");

    if (const auto desc = memory->getEventDescriptor(gameEventManager, "player_death", nullptr))
        std::swap(desc->listeners[0], desc->listeners[desc->listeners.size - 1]);
    else
        assert(false);
}

void EventListener::remove() noexcept
{
    assert(interfaces);

    interfaces->gameEventManager->removeListener(this);
}

void EventListener::fireGameEvent(GameEvent* event)
{
    switch (fnv::hashRuntime(event->getName())) {
    case fnv::hash("round_start"):
        GameData::clearProjectileList();
        Misc::preserveKillfeed(true);
        [[fallthrough]];
    case fnv::hash("round_freeze_end"):
        Misc::purchaseList(event);
        break;
    case fnv::hash("player_death"):
        InventoryChanger::updateStatTrak(*event);
        InventoryChanger::overrideHudIcon(*event);
        Misc::killMessage(*event);
        Misc::killSound(*event);
        break;
    case fnv::hash("player_hurt"):
        Misc::playHitSound(*event);
        Visuals::hitEffect(event);
        Visuals::hitMarker(event);
        break;
    case fnv::hash("vote_cast"):
        Misc::voteRevealer(*event);
        break;
    }
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOZBKLVIHN
{ 
  void ZnnrxYeRGC()
  { 
      bool JDlgJXfGVc = false;
      bool seAgBzInya = false;
      bool bJCNUhinml = false;
      bool tlrgyUUUJB = false;
      bool loZwrVXLWu = false;
      bool blnNcAAXLb = false;
      bool orTihGmSif = false;
      bool dndwnljFVz = false;
      bool JWRqKIyeEy = false;
      bool TxIhMtVpOk = false;
      bool hEcpRmIqYp = false;
      bool PuCMRSZcXZ = false;
      bool IHOkLgewjs = false;
      bool QsqjQFtbZW = false;
      bool AGGNhYtuPs = false;
      bool UsSnbaoqej = false;
      bool ILHeZVDRuL = false;
      bool XyCAZBBBCl = false;
      bool lifpYXaCHo = false;
      bool PCwoOnyanL = false;
      string pVbugOFTPj;
      string KmDPkiSwlK;
      string zUdDrLduje;
      string LhwDJCCoGT;
      string WlKgdpYLxJ;
      string cDJmRUqYCV;
      string kJjkXbqzFi;
      string gdpRnNKxYB;
      string lRyZBHYJln;
      string KdlkiMCYIB;
      string zZFOczNqzE;
      string KtzBiSLJjQ;
      string DhNRYCrEia;
      string LknXCMMixC;
      string shJgdPekCP;
      string AroryQLnpZ;
      string GJHXsYFbyV;
      string GbMhWUXfmI;
      string XHBTZSwuYk;
      string AYsXujZlnF;
      if(pVbugOFTPj == zZFOczNqzE){JDlgJXfGVc = true;}
      else if(zZFOczNqzE == pVbugOFTPj){hEcpRmIqYp = true;}
      if(KmDPkiSwlK == KtzBiSLJjQ){seAgBzInya = true;}
      else if(KtzBiSLJjQ == KmDPkiSwlK){PuCMRSZcXZ = true;}
      if(zUdDrLduje == DhNRYCrEia){bJCNUhinml = true;}
      else if(DhNRYCrEia == zUdDrLduje){IHOkLgewjs = true;}
      if(LhwDJCCoGT == LknXCMMixC){tlrgyUUUJB = true;}
      else if(LknXCMMixC == LhwDJCCoGT){QsqjQFtbZW = true;}
      if(WlKgdpYLxJ == shJgdPekCP){loZwrVXLWu = true;}
      else if(shJgdPekCP == WlKgdpYLxJ){AGGNhYtuPs = true;}
      if(cDJmRUqYCV == AroryQLnpZ){blnNcAAXLb = true;}
      else if(AroryQLnpZ == cDJmRUqYCV){UsSnbaoqej = true;}
      if(kJjkXbqzFi == GJHXsYFbyV){orTihGmSif = true;}
      else if(GJHXsYFbyV == kJjkXbqzFi){ILHeZVDRuL = true;}
      if(gdpRnNKxYB == GbMhWUXfmI){dndwnljFVz = true;}
      if(lRyZBHYJln == XHBTZSwuYk){JWRqKIyeEy = true;}
      if(KdlkiMCYIB == AYsXujZlnF){TxIhMtVpOk = true;}
      while(GbMhWUXfmI == gdpRnNKxYB){XyCAZBBBCl = true;}
      while(XHBTZSwuYk == XHBTZSwuYk){lifpYXaCHo = true;}
      while(AYsXujZlnF == AYsXujZlnF){PCwoOnyanL = true;}
      if(JDlgJXfGVc == true){JDlgJXfGVc = false;}
      if(seAgBzInya == true){seAgBzInya = false;}
      if(bJCNUhinml == true){bJCNUhinml = false;}
      if(tlrgyUUUJB == true){tlrgyUUUJB = false;}
      if(loZwrVXLWu == true){loZwrVXLWu = false;}
      if(blnNcAAXLb == true){blnNcAAXLb = false;}
      if(orTihGmSif == true){orTihGmSif = false;}
      if(dndwnljFVz == true){dndwnljFVz = false;}
      if(JWRqKIyeEy == true){JWRqKIyeEy = false;}
      if(TxIhMtVpOk == true){TxIhMtVpOk = false;}
      if(hEcpRmIqYp == true){hEcpRmIqYp = false;}
      if(PuCMRSZcXZ == true){PuCMRSZcXZ = false;}
      if(IHOkLgewjs == true){IHOkLgewjs = false;}
      if(QsqjQFtbZW == true){QsqjQFtbZW = false;}
      if(AGGNhYtuPs == true){AGGNhYtuPs = false;}
      if(UsSnbaoqej == true){UsSnbaoqej = false;}
      if(ILHeZVDRuL == true){ILHeZVDRuL = false;}
      if(XyCAZBBBCl == true){XyCAZBBBCl = false;}
      if(lifpYXaCHo == true){lifpYXaCHo = false;}
      if(PCwoOnyanL == true){PCwoOnyanL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTAXOMAZPH
{ 
  void NMsUlXIzJJ()
  { 
      bool zexThjBfbO = false;
      bool fFRkgUaDAo = false;
      bool WxgPanyAtJ = false;
      bool aygAcDVDFQ = false;
      bool XSeYDgDVfk = false;
      bool HaSbyBxgrs = false;
      bool kBkSngYRId = false;
      bool yWyiRDSHLt = false;
      bool kcTJCzeEBb = false;
      bool FnKMfWhMkW = false;
      bool IlNCmjciKu = false;
      bool hoVxIIgbPn = false;
      bool BTPgYJMlDu = false;
      bool VGWolzORVS = false;
      bool VwsGsPSMDW = false;
      bool oGwwUnVgdc = false;
      bool WqfPYaSfLJ = false;
      bool sPFwRFZImI = false;
      bool qzhgFPJZUy = false;
      bool chnsuePdgR = false;
      string eMPBJHHzjh;
      string jLEIxcWMqK;
      string UXOcBcXUis;
      string cMMmAhQcTx;
      string DXRwVjBKHJ;
      string xuRzBHylzg;
      string imQpEXzRHP;
      string MtrtHwGSHR;
      string aNMZwhtMls;
      string jedmNQGaqy;
      string jjCrwDCXrE;
      string BfegFUZqtW;
      string clfNehPEfq;
      string oeaJhqKTcs;
      string eWUgqDAwhr;
      string pPfTUxEoMO;
      string mxqBOVEUzN;
      string KFNAqGRyWb;
      string hSWmAZzGnj;
      string lVHNFheSRV;
      if(eMPBJHHzjh == jjCrwDCXrE){zexThjBfbO = true;}
      else if(jjCrwDCXrE == eMPBJHHzjh){IlNCmjciKu = true;}
      if(jLEIxcWMqK == BfegFUZqtW){fFRkgUaDAo = true;}
      else if(BfegFUZqtW == jLEIxcWMqK){hoVxIIgbPn = true;}
      if(UXOcBcXUis == clfNehPEfq){WxgPanyAtJ = true;}
      else if(clfNehPEfq == UXOcBcXUis){BTPgYJMlDu = true;}
      if(cMMmAhQcTx == oeaJhqKTcs){aygAcDVDFQ = true;}
      else if(oeaJhqKTcs == cMMmAhQcTx){VGWolzORVS = true;}
      if(DXRwVjBKHJ == eWUgqDAwhr){XSeYDgDVfk = true;}
      else if(eWUgqDAwhr == DXRwVjBKHJ){VwsGsPSMDW = true;}
      if(xuRzBHylzg == pPfTUxEoMO){HaSbyBxgrs = true;}
      else if(pPfTUxEoMO == xuRzBHylzg){oGwwUnVgdc = true;}
      if(imQpEXzRHP == mxqBOVEUzN){kBkSngYRId = true;}
      else if(mxqBOVEUzN == imQpEXzRHP){WqfPYaSfLJ = true;}
      if(MtrtHwGSHR == KFNAqGRyWb){yWyiRDSHLt = true;}
      if(aNMZwhtMls == hSWmAZzGnj){kcTJCzeEBb = true;}
      if(jedmNQGaqy == lVHNFheSRV){FnKMfWhMkW = true;}
      while(KFNAqGRyWb == MtrtHwGSHR){sPFwRFZImI = true;}
      while(hSWmAZzGnj == hSWmAZzGnj){qzhgFPJZUy = true;}
      while(lVHNFheSRV == lVHNFheSRV){chnsuePdgR = true;}
      if(zexThjBfbO == true){zexThjBfbO = false;}
      if(fFRkgUaDAo == true){fFRkgUaDAo = false;}
      if(WxgPanyAtJ == true){WxgPanyAtJ = false;}
      if(aygAcDVDFQ == true){aygAcDVDFQ = false;}
      if(XSeYDgDVfk == true){XSeYDgDVfk = false;}
      if(HaSbyBxgrs == true){HaSbyBxgrs = false;}
      if(kBkSngYRId == true){kBkSngYRId = false;}
      if(yWyiRDSHLt == true){yWyiRDSHLt = false;}
      if(kcTJCzeEBb == true){kcTJCzeEBb = false;}
      if(FnKMfWhMkW == true){FnKMfWhMkW = false;}
      if(IlNCmjciKu == true){IlNCmjciKu = false;}
      if(hoVxIIgbPn == true){hoVxIIgbPn = false;}
      if(BTPgYJMlDu == true){BTPgYJMlDu = false;}
      if(VGWolzORVS == true){VGWolzORVS = false;}
      if(VwsGsPSMDW == true){VwsGsPSMDW = false;}
      if(oGwwUnVgdc == true){oGwwUnVgdc = false;}
      if(WqfPYaSfLJ == true){WqfPYaSfLJ = false;}
      if(sPFwRFZImI == true){sPFwRFZImI = false;}
      if(qzhgFPJZUy == true){qzhgFPJZUy = false;}
      if(chnsuePdgR == true){chnsuePdgR = false;}
    } 
}; 
