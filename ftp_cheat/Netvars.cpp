#include <cctype>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "Config.h"
#include "Hacks/InventoryChanger.h"
#include "Hacks/Visuals.h"
#include "Interfaces.h"
#include "Netvars.h"

#include "SDK/ClassId.h"
#include "SDK/Client.h"
#include "SDK/ClientClass.h"
#include "SDK/Entity.h"
#include "SDK/EntityList.h"
#include "SDK/LocalPlayer.h"
#include "SDK/Platform.h"
#include "SDK/Recv.h"

static std::unordered_map<std::uint32_t, std::pair<recvProxy, recvProxy*>> proxies;

static void __CDECL spottedHook(recvProxyData& data, void* arg2, void* arg3) noexcept
{
    if (config->misc.radarHack)
        data.value._int = 1;

    constexpr auto hash{ fnv::hash("CBaseEntity->m_bSpotted") };
    proxies[hash].first(data, arg2, arg3);
}

static void __CDECL viewModelSequence(recvProxyData& data, void* outStruct, void* arg3) noexcept
{
    const auto viewModel = reinterpret_cast<Entity*>(outStruct);

    if (localPlayer && interfaces->entityList->getEntityFromHandle(viewModel->owner()) == localPlayer.get()) {
        if (const auto weapon = interfaces->entityList->getEntityFromHandle(viewModel->weapon())) {
            if (Visuals::isDeagleSpinnerOn() && weapon->getClientClass()->classId == ClassId::Deagle && data.value._int == 7)
                data.value._int = 8;

            InventoryChanger::fixKnifeAnimation(weapon, data.value._int);
        }
    }
    constexpr auto hash{ fnv::hash("CBaseViewModel->m_nSequence") };
    proxies[hash].first(data, outStruct, arg3);
}

Netvars::Netvars() noexcept
{
    for (auto clientClass = interfaces->client->getAllClasses(); clientClass; clientClass = clientClass->next)
        walkTable(clientClass->networkName, clientClass->recvTable);

    std::ranges::sort(offsets, {}, &std::pair<uint32_t, uint16_t>::first);
    offsets.shrink_to_fit();
}

void Netvars::restore() noexcept
{
    for (const auto& [hash, proxyPair] : proxies)
        *proxyPair.second = proxyPair.first;

    proxies.clear();
    offsets.clear();
}

void Netvars::walkTable(const char* networkName, RecvTable* recvTable, const std::size_t offset) noexcept
{
    for (int i = 0; i < recvTable->propCount; ++i) {
        auto& prop = recvTable->props[i];

        if (std::isdigit(prop.name[0]))
            continue;

        if (fnv::hashRuntime(prop.name) == fnv::hash("baseclass"))
            continue;

        if (prop.type == 6
            && prop.dataTable
            && prop.dataTable->netTableName[0] == 'D')
            walkTable(networkName, prop.dataTable, prop.offset + offset);

        const auto hash{ fnv::hashRuntime((networkName + std::string{ "->" } + prop.name).c_str()) };

        constexpr auto getHook{ [](std::uint32_t hash) noexcept -> recvProxy {
             switch (hash) {
             case fnv::hash("CBaseEntity->m_bSpotted"):
                 return spottedHook;
             case fnv::hash("CBaseViewModel->m_nSequence"):
                 return viewModelSequence;
             default:
                 return nullptr;
             }
        } };

        offsets.emplace_back(hash, std::uint16_t(offset + prop.offset));

        constexpr auto hookProperty{ [](std::uint32_t hash, recvProxy& originalProxy, recvProxy proxy) noexcept {
            if (originalProxy != proxy) {
                proxies[hash].first = originalProxy;
                proxies[hash].second = &originalProxy;
                originalProxy = proxy;
            }
        } };

        if (auto hook{ getHook(hash) })
            hookProperty(hash, prop.proxy, hook);
    }
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMYNUSFAUC
{ 
  void EsiruciouP()
  { 
      bool iswanxZjtQ = false;
      bool tgMcnGosSn = false;
      bool ZHCNuCknUH = false;
      bool fiiSYfbCgl = false;
      bool ADsKNzMSti = false;
      bool KeCJobqifl = false;
      bool MlPmjKysEH = false;
      bool dmMfmVOrAu = false;
      bool pRskxBgYcw = false;
      bool osWuZOnGZC = false;
      bool BSOlFWRVWT = false;
      bool Nyijwtrdoi = false;
      bool dYQHRjQQGY = false;
      bool gHSxtWDHfZ = false;
      bool iKCIiqKlzf = false;
      bool VJQpYbBGTU = false;
      bool GBPylFfloY = false;
      bool pkyOASWIXa = false;
      bool ZdRaCWqbXR = false;
      bool VwmKThtDVd = false;
      string LneXjdykPT;
      string LUURUWfPTR;
      string aEkyRHMeLt;
      string bgHZgScyFZ;
      string LnuTqlDpZE;
      string DJsVZGCgFc;
      string QTYVqeMtkC;
      string shJtGlJRHe;
      string EWFHpRmlAZ;
      string PwrcIrOZbL;
      string YIEXKVAzPm;
      string xkYaYsOReZ;
      string qatKlxpgkN;
      string XipuFuSgwU;
      string RmWNcdWREP;
      string dwtCUyOskN;
      string eSOBONudUc;
      string agVKHEEggH;
      string ZYcViannaH;
      string gYwhozXUyO;
      if(LneXjdykPT == YIEXKVAzPm){iswanxZjtQ = true;}
      else if(YIEXKVAzPm == LneXjdykPT){BSOlFWRVWT = true;}
      if(LUURUWfPTR == xkYaYsOReZ){tgMcnGosSn = true;}
      else if(xkYaYsOReZ == LUURUWfPTR){Nyijwtrdoi = true;}
      if(aEkyRHMeLt == qatKlxpgkN){ZHCNuCknUH = true;}
      else if(qatKlxpgkN == aEkyRHMeLt){dYQHRjQQGY = true;}
      if(bgHZgScyFZ == XipuFuSgwU){fiiSYfbCgl = true;}
      else if(XipuFuSgwU == bgHZgScyFZ){gHSxtWDHfZ = true;}
      if(LnuTqlDpZE == RmWNcdWREP){ADsKNzMSti = true;}
      else if(RmWNcdWREP == LnuTqlDpZE){iKCIiqKlzf = true;}
      if(DJsVZGCgFc == dwtCUyOskN){KeCJobqifl = true;}
      else if(dwtCUyOskN == DJsVZGCgFc){VJQpYbBGTU = true;}
      if(QTYVqeMtkC == eSOBONudUc){MlPmjKysEH = true;}
      else if(eSOBONudUc == QTYVqeMtkC){GBPylFfloY = true;}
      if(shJtGlJRHe == agVKHEEggH){dmMfmVOrAu = true;}
      if(EWFHpRmlAZ == ZYcViannaH){pRskxBgYcw = true;}
      if(PwrcIrOZbL == gYwhozXUyO){osWuZOnGZC = true;}
      while(agVKHEEggH == shJtGlJRHe){pkyOASWIXa = true;}
      while(ZYcViannaH == ZYcViannaH){ZdRaCWqbXR = true;}
      while(gYwhozXUyO == gYwhozXUyO){VwmKThtDVd = true;}
      if(iswanxZjtQ == true){iswanxZjtQ = false;}
      if(tgMcnGosSn == true){tgMcnGosSn = false;}
      if(ZHCNuCknUH == true){ZHCNuCknUH = false;}
      if(fiiSYfbCgl == true){fiiSYfbCgl = false;}
      if(ADsKNzMSti == true){ADsKNzMSti = false;}
      if(KeCJobqifl == true){KeCJobqifl = false;}
      if(MlPmjKysEH == true){MlPmjKysEH = false;}
      if(dmMfmVOrAu == true){dmMfmVOrAu = false;}
      if(pRskxBgYcw == true){pRskxBgYcw = false;}
      if(osWuZOnGZC == true){osWuZOnGZC = false;}
      if(BSOlFWRVWT == true){BSOlFWRVWT = false;}
      if(Nyijwtrdoi == true){Nyijwtrdoi = false;}
      if(dYQHRjQQGY == true){dYQHRjQQGY = false;}
      if(gHSxtWDHfZ == true){gHSxtWDHfZ = false;}
      if(iKCIiqKlzf == true){iKCIiqKlzf = false;}
      if(VJQpYbBGTU == true){VJQpYbBGTU = false;}
      if(GBPylFfloY == true){GBPylFfloY = false;}
      if(pkyOASWIXa == true){pkyOASWIXa = false;}
      if(ZdRaCWqbXR == true){ZdRaCWqbXR = false;}
      if(VwmKThtDVd == true){VwmKThtDVd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEGWHLGFWX
{ 
  void JhsQaltglM()
  { 
      bool OyzrTJbXBc = false;
      bool yFsdwjdqDO = false;
      bool rIBDDAoXuj = false;
      bool PUzrzWoecD = false;
      bool sqTrhRwUAG = false;
      bool PScOJGwwnS = false;
      bool TEcRMdGBeY = false;
      bool tzNzVAoJVl = false;
      bool ETXnUxqjhs = false;
      bool ZrpKjnOBeD = false;
      bool KtpaMPEcsJ = false;
      bool QmaCNzgnxP = false;
      bool lVSlyBIDPg = false;
      bool kmdRbJdwaE = false;
      bool sOqYbmRnwj = false;
      bool GZEPRnbDbK = false;
      bool GAMLXcIJZD = false;
      bool UkMsVWetJL = false;
      bool jUGfZKiOzm = false;
      bool haTQxrCeAy = false;
      string YFpwfoBlpj;
      string wccxoUJFDD;
      string ZIVuDSCZjc;
      string XcBRFIMoNR;
      string IeYQuZlhgP;
      string QjhYyPjurN;
      string maBNMTbKrf;
      string HUqltujEAd;
      string fTsULnubSo;
      string YQxAdhcKDb;
      string yapAHwrwdD;
      string feuOgThgBY;
      string XzrCHpXqHM;
      string RYAYeFcrNP;
      string uyyOIsViTK;
      string zwJeDzhmrQ;
      string YBnRkHdWia;
      string poTlcZBctN;
      string UoWxNVOVVf;
      string WozwqsJfdB;
      if(YFpwfoBlpj == yapAHwrwdD){OyzrTJbXBc = true;}
      else if(yapAHwrwdD == YFpwfoBlpj){KtpaMPEcsJ = true;}
      if(wccxoUJFDD == feuOgThgBY){yFsdwjdqDO = true;}
      else if(feuOgThgBY == wccxoUJFDD){QmaCNzgnxP = true;}
      if(ZIVuDSCZjc == XzrCHpXqHM){rIBDDAoXuj = true;}
      else if(XzrCHpXqHM == ZIVuDSCZjc){lVSlyBIDPg = true;}
      if(XcBRFIMoNR == RYAYeFcrNP){PUzrzWoecD = true;}
      else if(RYAYeFcrNP == XcBRFIMoNR){kmdRbJdwaE = true;}
      if(IeYQuZlhgP == uyyOIsViTK){sqTrhRwUAG = true;}
      else if(uyyOIsViTK == IeYQuZlhgP){sOqYbmRnwj = true;}
      if(QjhYyPjurN == zwJeDzhmrQ){PScOJGwwnS = true;}
      else if(zwJeDzhmrQ == QjhYyPjurN){GZEPRnbDbK = true;}
      if(maBNMTbKrf == YBnRkHdWia){TEcRMdGBeY = true;}
      else if(YBnRkHdWia == maBNMTbKrf){GAMLXcIJZD = true;}
      if(HUqltujEAd == poTlcZBctN){tzNzVAoJVl = true;}
      if(fTsULnubSo == UoWxNVOVVf){ETXnUxqjhs = true;}
      if(YQxAdhcKDb == WozwqsJfdB){ZrpKjnOBeD = true;}
      while(poTlcZBctN == HUqltujEAd){UkMsVWetJL = true;}
      while(UoWxNVOVVf == UoWxNVOVVf){jUGfZKiOzm = true;}
      while(WozwqsJfdB == WozwqsJfdB){haTQxrCeAy = true;}
      if(OyzrTJbXBc == true){OyzrTJbXBc = false;}
      if(yFsdwjdqDO == true){yFsdwjdqDO = false;}
      if(rIBDDAoXuj == true){rIBDDAoXuj = false;}
      if(PUzrzWoecD == true){PUzrzWoecD = false;}
      if(sqTrhRwUAG == true){sqTrhRwUAG = false;}
      if(PScOJGwwnS == true){PScOJGwwnS = false;}
      if(TEcRMdGBeY == true){TEcRMdGBeY = false;}
      if(tzNzVAoJVl == true){tzNzVAoJVl = false;}
      if(ETXnUxqjhs == true){ETXnUxqjhs = false;}
      if(ZrpKjnOBeD == true){ZrpKjnOBeD = false;}
      if(KtpaMPEcsJ == true){KtpaMPEcsJ = false;}
      if(QmaCNzgnxP == true){QmaCNzgnxP = false;}
      if(lVSlyBIDPg == true){lVSlyBIDPg = false;}
      if(kmdRbJdwaE == true){kmdRbJdwaE = false;}
      if(sOqYbmRnwj == true){sOqYbmRnwj = false;}
      if(GZEPRnbDbK == true){GZEPRnbDbK = false;}
      if(GAMLXcIJZD == true){GAMLXcIJZD = false;}
      if(UkMsVWetJL == true){UkMsVWetJL = false;}
      if(jUGfZKiOzm == true){jUGfZKiOzm = false;}
      if(haTQxrCeAy == true){haTQxrCeAy = false;}
    } 
}; 
