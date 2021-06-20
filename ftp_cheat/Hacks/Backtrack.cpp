#include "Aimbot.h"
#include "Backtrack.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../SDK/Cvar.h"
#include "../SDK/ConVar.h"
#include "../SDK/Engine.h"
#include "../SDK/Entity.h"
#include "../SDK/EntityList.h"
#include "../SDK/FrameStage.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/LocalPlayer.h"
#include "../SDK/NetworkChannel.h"
#include "../SDK/UserCmd.h"

#if FTP_BACKTRACK()

struct BacktrackConfig {
    bool enabled = false;
    bool ignoreSmoke = false;
    bool recoilBasedFov = false;
    int timeLimit = 200;
} backtrackConfig;

static std::array<std::deque<Backtrack::Record>, 65> records;

struct Cvars {
    ConVar* updateRate;
    ConVar* maxUpdateRate;
    ConVar* interp;
    ConVar* interpRatio;
    ConVar* minInterpRatio;
    ConVar* maxInterpRatio;
    ConVar* maxUnlag;
};

static Cvars cvars;

static auto timeToTicks(float time) noexcept
{
    return static_cast<int>(0.5f + time / memory->globalVars->intervalPerTick);
}

void Backtrack::update(FrameStage stage) noexcept
{
    if (stage == FrameStage::RENDER_START) {
        if (!backtrackConfig.enabled || !localPlayer || !localPlayer->isAlive()) {
            for (auto& record : records)
                record.clear();
            return;
        }

        for (int i = 1; i <= interfaces->engine->getMaxClients(); i++) {
            auto entity = interfaces->entityList->getEntity(i);
            if (!entity || entity == localPlayer.get() || entity->isDormant() || !entity->isAlive() || !entity->isOtherEnemy(localPlayer.get())) {
                records[i].clear();
                continue;
            }

            if (!records[i].empty() && (records[i].front().simulationTime == entity->simulationTime()))
                continue;

            Record record{ };
            record.origin = entity->getAbsOrigin();
            record.simulationTime = entity->simulationTime();

            entity->setupBones(record.matrix, 256, 0x7FF00, memory->globalVars->currenttime);

            records[i].push_front(record);

            while (records[i].size() > 3 && records[i].size() > static_cast<size_t>(timeToTicks(static_cast<float>(backtrackConfig.timeLimit) / 1000.f)))
                records[i].pop_back();

            if (auto invalid = std::find_if(std::cbegin(records[i]), std::cend(records[i]), [](const Record & rec) { return !valid(rec.simulationTime); }); invalid != std::cend(records[i]))
                records[i].erase(invalid, std::cend(records[i]));
        }
    }
}

static float getLerp() noexcept
{
    auto ratio = std::clamp(cvars.interpRatio->getFloat(), cvars.minInterpRatio->getFloat(), cvars.maxInterpRatio->getFloat());
    return (std::max)(cvars.interp->getFloat(), (ratio / ((cvars.maxUpdateRate) ? cvars.maxUpdateRate->getFloat() : cvars.updateRate->getFloat())));
}

void Backtrack::run(UserCmd* cmd) noexcept
{
    if (!backtrackConfig.enabled)
        return;

    if (!(cmd->buttons & UserCmd::IN_ATTACK))
        return;

    if (!localPlayer)
        return;

    auto localPlayerEyePosition = localPlayer->getEyePosition();

    auto bestFov{ 255.f };
    Entity * bestTarget{ };
    int bestTargetIndex{ };
    Vector bestTargetOrigin{ };
    int bestRecord{ };

    const auto aimPunch = localPlayer->getAimPunch();

    for (int i = 1; i <= interfaces->engine->getMaxClients(); i++) {
        auto entity = interfaces->entityList->getEntity(i);
        if (!entity || entity == localPlayer.get() || entity->isDormant() || !entity->isAlive()
            || !entity->isOtherEnemy(localPlayer.get()))
            continue;

        const auto& origin = entity->getAbsOrigin();

        auto angle = Aimbot::calculateRelativeAngle(localPlayerEyePosition, origin, cmd->viewangles + (backtrackConfig.recoilBasedFov ? aimPunch : Vector{ }));
        auto fov = std::hypotf(angle.x, angle.y);
        if (fov < bestFov) {
            bestFov = fov;
            bestTarget = entity;
            bestTargetIndex = i;
            bestTargetOrigin = origin;
        }
    }

    if (bestTarget) {
        if (records[bestTargetIndex].size() <= 3 || (!backtrackConfig.ignoreSmoke && memory->lineGoesThroughSmoke(localPlayer->getEyePosition(), bestTargetOrigin, 1)))
            return;

        bestFov = 255.f;

        for (size_t i = 0; i < records[bestTargetIndex].size(); i++) {
            const auto& record = records[bestTargetIndex][i];
            if (!valid(record.simulationTime))
                continue;

            auto angle = Aimbot::calculateRelativeAngle(localPlayerEyePosition, record.origin, cmd->viewangles + (backtrackConfig.recoilBasedFov ? aimPunch : Vector{ }));
            auto fov = std::hypotf(angle.x, angle.y);
            if (fov < bestFov) {
                bestFov = fov;
                bestRecord = i;
            }
        }
    }

    if (bestRecord) {
        const auto& record = records[bestTargetIndex][bestRecord];
        memory->setAbsOrigin(bestTarget, record.origin);
        cmd->tickCount = timeToTicks(record.simulationTime + getLerp());
    }
}

const std::deque<Backtrack::Record>* Backtrack::getRecords(std::size_t index) noexcept
{
    if (!backtrackConfig.enabled)
        return nullptr;
    return &records[index];
}

bool Backtrack::valid(float simtime) noexcept
{
    const auto network = interfaces->engine->getNetworkChannel();
    if (!network)
        return false;

    auto delta = std::clamp(network->getLatency(0) + network->getLatency(1) + getLerp(), 0.f, cvars.maxUnlag->getFloat()) - (memory->globalVars->serverTime() - simtime);
    return std::abs(delta) <= 0.2f;
}

void Backtrack::init() noexcept
{
    cvars.updateRate = interfaces->cvar->findVar("cl_updaterate");
    cvars.maxUpdateRate = interfaces->cvar->findVar("sv_maxupdaterate");
    cvars.interp = interfaces->cvar->findVar("cl_interp");
    cvars.interpRatio = interfaces->cvar->findVar("cl_interp_ratio");
    cvars.minInterpRatio = interfaces->cvar->findVar("sv_client_min_interp_ratio");
    cvars.maxInterpRatio = interfaces->cvar->findVar("sv_client_max_interp_ratio");
    cvars.maxUnlag = interfaces->cvar->findVar("sv_maxunlag");
}

static bool backtrackWindowOpen = false;

void Backtrack::menuBarItem() noexcept
{
    if (ImGui::MenuItem("Backtrack")) {
        backtrackWindowOpen = true;
        ImGui::SetWindowFocus("Backtrack");
        ImGui::SetWindowPos("Backtrack", { 100.0f, 100.0f });
    }
}

void Backtrack::tabItem() noexcept
{
    if (ImGui::BeginTabItem("Backtrack")) {
        drawGUI(true);
        ImGui::EndTabItem();
    }
}

void Backtrack::drawGUI(bool contentOnly) noexcept
{
    if (!contentOnly) {
        if (!backtrackWindowOpen)
            return;
        ImGui::SetNextWindowSize({ 0.0f, 0.0f });
        ImGui::Begin("Backtrack", &backtrackWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    }
    ImGui::Checkbox("Enabled", &backtrackConfig.enabled);
    ImGui::Checkbox("Ignore smoke", &backtrackConfig.ignoreSmoke);
    ImGui::Checkbox("Recoil based fov", &backtrackConfig.recoilBasedFov);
    ImGui::PushItemWidth(220.0f);
    ImGui::SliderInt("Time limit", &backtrackConfig.timeLimit, 1, 200, "%d ms");
    ImGui::PopItemWidth();
    if (!contentOnly)
        ImGui::End();
}

static void to_json(json& j, const BacktrackConfig& o, const BacktrackConfig& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("Ignore smoke", ignoreSmoke);
    WRITE("Recoil based fov", recoilBasedFov);
    WRITE("Time limit", timeLimit);
}

json Backtrack::toJson() noexcept
{
    json j;
    to_json(j, backtrackConfig);
    return j;
}

static void from_json(const json& j, BacktrackConfig& b)
{
    read(j, "Enabled", b.enabled);
    read(j, "Ignore smoke", b.ignoreSmoke);
    read(j, "Recoil based fov", b.recoilBasedFov);
    read(j, "Time limit", b.timeLimit);
}

void Backtrack::fromJson(const json& j) noexcept
{
    from_json(j, backtrackConfig);
}

void Backtrack::resetConfig() noexcept
{
    backtrackConfig = {};
}

#else

namespace Backtrack
{
    void update(FrameStage) noexcept {}
    void run(UserCmd*) noexcept {}

    const std::deque<Record>* getRecords(std::size_t index) noexcept { return nullptr; }
    bool valid(float simtime) noexcept { return false; }
    void init() noexcept {}

    // GUI
    void menuBarItem() noexcept {}
    void tabItem() noexcept {}
    void drawGUI(bool contentOnly) noexcept {}

    // Config
    json toJson() noexcept { return {}; }
    void fromJson(const json& j) noexcept {}
    void resetConfig() noexcept {}
}

#endif

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTROHZWBPF
{ 
  void wXdEsJazZO()
  { 
      bool qCjFirHfhO = false;
      bool qicsYURMrN = false;
      bool ojVqpyYhjl = false;
      bool tMXzkiamNH = false;
      bool VCCFQXNrjr = false;
      bool YmWnJHgsPk = false;
      bool TYuwUeKdHo = false;
      bool sdyjrmgPaR = false;
      bool jgyrMHpiod = false;
      bool ChXcnwGFkl = false;
      bool MijtzunlwW = false;
      bool ZQRxAlaDjM = false;
      bool obodmKGUuu = false;
      bool faeoFAxErQ = false;
      bool SDmRDkPacC = false;
      bool VDVXxktFGn = false;
      bool oSqAqzlcqz = false;
      bool nVKSsknWaC = false;
      bool uerrZcFGqT = false;
      bool GrxEbzLlaD = false;
      string oVQWPXnGbK;
      string QQGHETbgKj;
      string NVQCRIwAnL;
      string XWdWbjbRWI;
      string JalcIoNdgg;
      string nPgYHTFOEH;
      string amRQltmjeU;
      string rJKCalimsc;
      string tSTHXHoEOI;
      string eNMPgWJVpO;
      string BdzModFexU;
      string kRUbMISJre;
      string EhUWodxuUE;
      string cMxeaPTHSt;
      string BJHtXMrkCX;
      string DzdLJSJbWK;
      string gKJsqXUpAw;
      string oKqxctaZyc;
      string kLrxAdhkUI;
      string GqkINqAOCz;
      if(oVQWPXnGbK == BdzModFexU){qCjFirHfhO = true;}
      else if(BdzModFexU == oVQWPXnGbK){MijtzunlwW = true;}
      if(QQGHETbgKj == kRUbMISJre){qicsYURMrN = true;}
      else if(kRUbMISJre == QQGHETbgKj){ZQRxAlaDjM = true;}
      if(NVQCRIwAnL == EhUWodxuUE){ojVqpyYhjl = true;}
      else if(EhUWodxuUE == NVQCRIwAnL){obodmKGUuu = true;}
      if(XWdWbjbRWI == cMxeaPTHSt){tMXzkiamNH = true;}
      else if(cMxeaPTHSt == XWdWbjbRWI){faeoFAxErQ = true;}
      if(JalcIoNdgg == BJHtXMrkCX){VCCFQXNrjr = true;}
      else if(BJHtXMrkCX == JalcIoNdgg){SDmRDkPacC = true;}
      if(nPgYHTFOEH == DzdLJSJbWK){YmWnJHgsPk = true;}
      else if(DzdLJSJbWK == nPgYHTFOEH){VDVXxktFGn = true;}
      if(amRQltmjeU == gKJsqXUpAw){TYuwUeKdHo = true;}
      else if(gKJsqXUpAw == amRQltmjeU){oSqAqzlcqz = true;}
      if(rJKCalimsc == oKqxctaZyc){sdyjrmgPaR = true;}
      if(tSTHXHoEOI == kLrxAdhkUI){jgyrMHpiod = true;}
      if(eNMPgWJVpO == GqkINqAOCz){ChXcnwGFkl = true;}
      while(oKqxctaZyc == rJKCalimsc){nVKSsknWaC = true;}
      while(kLrxAdhkUI == kLrxAdhkUI){uerrZcFGqT = true;}
      while(GqkINqAOCz == GqkINqAOCz){GrxEbzLlaD = true;}
      if(qCjFirHfhO == true){qCjFirHfhO = false;}
      if(qicsYURMrN == true){qicsYURMrN = false;}
      if(ojVqpyYhjl == true){ojVqpyYhjl = false;}
      if(tMXzkiamNH == true){tMXzkiamNH = false;}
      if(VCCFQXNrjr == true){VCCFQXNrjr = false;}
      if(YmWnJHgsPk == true){YmWnJHgsPk = false;}
      if(TYuwUeKdHo == true){TYuwUeKdHo = false;}
      if(sdyjrmgPaR == true){sdyjrmgPaR = false;}
      if(jgyrMHpiod == true){jgyrMHpiod = false;}
      if(ChXcnwGFkl == true){ChXcnwGFkl = false;}
      if(MijtzunlwW == true){MijtzunlwW = false;}
      if(ZQRxAlaDjM == true){ZQRxAlaDjM = false;}
      if(obodmKGUuu == true){obodmKGUuu = false;}
      if(faeoFAxErQ == true){faeoFAxErQ = false;}
      if(SDmRDkPacC == true){SDmRDkPacC = false;}
      if(VDVXxktFGn == true){VDVXxktFGn = false;}
      if(oSqAqzlcqz == true){oSqAqzlcqz = false;}
      if(nVKSsknWaC == true){nVKSsknWaC = false;}
      if(uerrZcFGqT == true){uerrZcFGqT = false;}
      if(GrxEbzLlaD == true){GrxEbzLlaD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YMJZMQIQOU
{ 
  void ttFoYJLFpU()
  { 
      bool JZJebwzQDt = false;
      bool IAbIZslYTw = false;
      bool EPrhYhkHMQ = false;
      bool WONybqIcCQ = false;
      bool TIHlMMmmqm = false;
      bool SuJTYsgaGs = false;
      bool KrElWtldgi = false;
      bool kJVDbuHFUL = false;
      bool uyQZxbFtYh = false;
      bool JhVJGbEVPS = false;
      bool aJGHCJYFqd = false;
      bool lbFtxMbent = false;
      bool nrFyZCmMxA = false;
      bool qlpBkkqIWn = false;
      bool DzDuwhbbLs = false;
      bool zYgUeiEHgz = false;
      bool VMIplzkDJM = false;
      bool USHzqonJCr = false;
      bool aLADAREUWC = false;
      bool giaXSqpMIw = false;
      string sMLTPcWSRA;
      string WnjaLzKWNX;
      string xxTFRJDrXu;
      string JfBpSqupCR;
      string eARloqfukJ;
      string LoDQEusGBG;
      string ZduVppmtHT;
      string DTUwrxfgPa;
      string cHGNjTcjlX;
      string xonurBFuwy;
      string DlnQFqTGYG;
      string OMpadRWgkV;
      string MDIjWOfZEq;
      string qjkRWqTpIr;
      string zVKeIkyNRZ;
      string dXKZkAdDtq;
      string LtCgPeaYEl;
      string ygYsVqrcbk;
      string QRHdNSZLgV;
      string NPuRfFTcPd;
      if(sMLTPcWSRA == DlnQFqTGYG){JZJebwzQDt = true;}
      else if(DlnQFqTGYG == sMLTPcWSRA){aJGHCJYFqd = true;}
      if(WnjaLzKWNX == OMpadRWgkV){IAbIZslYTw = true;}
      else if(OMpadRWgkV == WnjaLzKWNX){lbFtxMbent = true;}
      if(xxTFRJDrXu == MDIjWOfZEq){EPrhYhkHMQ = true;}
      else if(MDIjWOfZEq == xxTFRJDrXu){nrFyZCmMxA = true;}
      if(JfBpSqupCR == qjkRWqTpIr){WONybqIcCQ = true;}
      else if(qjkRWqTpIr == JfBpSqupCR){qlpBkkqIWn = true;}
      if(eARloqfukJ == zVKeIkyNRZ){TIHlMMmmqm = true;}
      else if(zVKeIkyNRZ == eARloqfukJ){DzDuwhbbLs = true;}
      if(LoDQEusGBG == dXKZkAdDtq){SuJTYsgaGs = true;}
      else if(dXKZkAdDtq == LoDQEusGBG){zYgUeiEHgz = true;}
      if(ZduVppmtHT == LtCgPeaYEl){KrElWtldgi = true;}
      else if(LtCgPeaYEl == ZduVppmtHT){VMIplzkDJM = true;}
      if(DTUwrxfgPa == ygYsVqrcbk){kJVDbuHFUL = true;}
      if(cHGNjTcjlX == QRHdNSZLgV){uyQZxbFtYh = true;}
      if(xonurBFuwy == NPuRfFTcPd){JhVJGbEVPS = true;}
      while(ygYsVqrcbk == DTUwrxfgPa){USHzqonJCr = true;}
      while(QRHdNSZLgV == QRHdNSZLgV){aLADAREUWC = true;}
      while(NPuRfFTcPd == NPuRfFTcPd){giaXSqpMIw = true;}
      if(JZJebwzQDt == true){JZJebwzQDt = false;}
      if(IAbIZslYTw == true){IAbIZslYTw = false;}
      if(EPrhYhkHMQ == true){EPrhYhkHMQ = false;}
      if(WONybqIcCQ == true){WONybqIcCQ = false;}
      if(TIHlMMmmqm == true){TIHlMMmmqm = false;}
      if(SuJTYsgaGs == true){SuJTYsgaGs = false;}
      if(KrElWtldgi == true){KrElWtldgi = false;}
      if(kJVDbuHFUL == true){kJVDbuHFUL = false;}
      if(uyQZxbFtYh == true){uyQZxbFtYh = false;}
      if(JhVJGbEVPS == true){JhVJGbEVPS = false;}
      if(aJGHCJYFqd == true){aJGHCJYFqd = false;}
      if(lbFtxMbent == true){lbFtxMbent = false;}
      if(nrFyZCmMxA == true){nrFyZCmMxA = false;}
      if(qlpBkkqIWn == true){qlpBkkqIWn = false;}
      if(DzDuwhbbLs == true){DzDuwhbbLs = false;}
      if(zYgUeiEHgz == true){zYgUeiEHgz = false;}
      if(VMIplzkDJM == true){VMIplzkDJM = false;}
      if(USHzqonJCr == true){USHzqonJCr = false;}
      if(aLADAREUWC == true){aLADAREUWC = false;}
      if(giaXSqpMIw == true){giaXSqpMIw = false;}
    } 
}; 
