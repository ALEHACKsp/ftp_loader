#include "AntiAim.h"

#include "../imgui/imgui.h"

#include "../ConfigStructs.h"
#include "../SDK/Entity.h"
#include "../SDK/LocalPlayer.h"
#include "../SDK/UserCmd.h"
#include "../SDK/Vector.h"

#if FTP_ANTIAIM()

struct AntiAimConfig {
    bool enabled = false;
    bool pitch = false;
    bool yaw = false;
    float pitchAngle = 0.0f;
} antiAimConfig;

void AntiAim::run(UserCmd* cmd, const Vector& previousViewAngles, const Vector& currentViewAngles, bool& sendPacket) noexcept
{
    if (antiAimConfig.enabled) {
        if (!localPlayer)
            return;

        if (antiAimConfig.pitch && cmd->viewangles.x == currentViewAngles.x)
            cmd->viewangles.x = antiAimConfig.pitchAngle;

        if (antiAimConfig.yaw && !sendPacket && cmd->viewangles.y == currentViewAngles.y) {
            cmd->viewangles.y += localPlayer->getMaxDesyncAngle();
            if (fabsf(cmd->sidemove) < 5.0f) {
                if (cmd->buttons & UserCmd::IN_DUCK)
                    cmd->sidemove = cmd->tickCount & 1 ? 3.25f : -3.25f;
                else
                    cmd->sidemove = cmd->tickCount & 1 ? 1.1f : -1.1f;
            }
        }
    }
}

static bool antiAimOpen = false;

void AntiAim::menuBarItem() noexcept
{
    if (ImGui::MenuItem("Anti aim")) {
        antiAimOpen = true;
        ImGui::SetWindowFocus("Anti aim");
        ImGui::SetWindowPos("Anti aim", { 100.0f, 100.0f });
    }
}

void AntiAim::tabItem() noexcept
{
    if (ImGui::BeginTabItem("Anti aim")) {
        drawGUI(true);
        ImGui::EndTabItem();
    }
}

void AntiAim::drawGUI(bool contentOnly) noexcept
{
    if (!contentOnly) {
        if (!antiAimOpen)
            return;
        ImGui::SetNextWindowSize({ 0.0f, 0.0f });
        ImGui::Begin("Anti aim", &antiAimOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    }
    ImGui::Checkbox("Enabled", &antiAimConfig.enabled);
    ImGui::Checkbox("##pitch", &antiAimConfig.pitch);
    ImGui::SameLine();
    ImGui::SliderFloat("Pitch", &antiAimConfig.pitchAngle, -89.0f, 89.0f, "%.2f");
    ImGui::Checkbox("Yaw", &antiAimConfig.yaw);
    if (!contentOnly)
        ImGui::End();
}

static void to_json(json& j, const AntiAimConfig& o, const AntiAimConfig& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("Pitch", pitch);
    WRITE("Pitch angle", pitchAngle);
    WRITE("Yaw", yaw);
}

json AntiAim::toJson() noexcept
{
    json j;
    to_json(j, antiAimConfig);
    return j;
}

static void from_json(const json& j, AntiAimConfig& a)
{
    read(j, "Enabled", a.enabled);
    read(j, "Pitch", a.pitch);
    read(j, "Yaw", a.yaw);
    read(j, "Pitch angle", a.pitchAngle);
}

void AntiAim::fromJson(const json& j) noexcept
{
    from_json(j, antiAimConfig);
}

void AntiAim::resetConfig() noexcept
{
    antiAimConfig = { };
}

#else

namespace AntiAim
{
    void run(UserCmd*, const Vector&, const Vector&, bool&) noexcept {}

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

class DWUTQYQHTN
{ 
  void GUklBPxrJU()
  { 
      bool eYujTrVTjT = false;
      bool bVyVFfhIPG = false;
      bool CQTwdFbkzi = false;
      bool ulMrjiOTlA = false;
      bool SygKaCgKLf = false;
      bool toaksOFyFO = false;
      bool PjTAYoJFkV = false;
      bool QNWOnDjIUb = false;
      bool XRZTnFKayV = false;
      bool dQNWkheflk = false;
      bool saZoOfSMwp = false;
      bool dwcdpyKAMS = false;
      bool ehHPrAAAdF = false;
      bool YEWiixrjEH = false;
      bool mydIqgmjfl = false;
      bool XdTSGKTJxO = false;
      bool fRiqQZZsus = false;
      bool GawEffEyXL = false;
      bool NQTqhukDcX = false;
      bool chlpbVOmrQ = false;
      string xtsNqNnWMF;
      string bNHiVXRipJ;
      string apRjKXyfRC;
      string rffTrkaHGW;
      string kKBiSRGkzr;
      string FDrbXHcJCS;
      string PIFJNwhnqj;
      string xKcSXQnhQs;
      string RMgYxnmDuj;
      string HQEmHcEqVW;
      string iStOtuaZDH;
      string StrJBCbgMY;
      string IdrGcgFoKu;
      string LxMtJySReB;
      string NNAnRMXulE;
      string BXewOFZmkN;
      string pkOIuUhyAC;
      string jJCKLtdEoP;
      string IJDFsnSQeD;
      string XegQLbyqrw;
      if(xtsNqNnWMF == iStOtuaZDH){eYujTrVTjT = true;}
      else if(iStOtuaZDH == xtsNqNnWMF){saZoOfSMwp = true;}
      if(bNHiVXRipJ == StrJBCbgMY){bVyVFfhIPG = true;}
      else if(StrJBCbgMY == bNHiVXRipJ){dwcdpyKAMS = true;}
      if(apRjKXyfRC == IdrGcgFoKu){CQTwdFbkzi = true;}
      else if(IdrGcgFoKu == apRjKXyfRC){ehHPrAAAdF = true;}
      if(rffTrkaHGW == LxMtJySReB){ulMrjiOTlA = true;}
      else if(LxMtJySReB == rffTrkaHGW){YEWiixrjEH = true;}
      if(kKBiSRGkzr == NNAnRMXulE){SygKaCgKLf = true;}
      else if(NNAnRMXulE == kKBiSRGkzr){mydIqgmjfl = true;}
      if(FDrbXHcJCS == BXewOFZmkN){toaksOFyFO = true;}
      else if(BXewOFZmkN == FDrbXHcJCS){XdTSGKTJxO = true;}
      if(PIFJNwhnqj == pkOIuUhyAC){PjTAYoJFkV = true;}
      else if(pkOIuUhyAC == PIFJNwhnqj){fRiqQZZsus = true;}
      if(xKcSXQnhQs == jJCKLtdEoP){QNWOnDjIUb = true;}
      if(RMgYxnmDuj == IJDFsnSQeD){XRZTnFKayV = true;}
      if(HQEmHcEqVW == XegQLbyqrw){dQNWkheflk = true;}
      while(jJCKLtdEoP == xKcSXQnhQs){GawEffEyXL = true;}
      while(IJDFsnSQeD == IJDFsnSQeD){NQTqhukDcX = true;}
      while(XegQLbyqrw == XegQLbyqrw){chlpbVOmrQ = true;}
      if(eYujTrVTjT == true){eYujTrVTjT = false;}
      if(bVyVFfhIPG == true){bVyVFfhIPG = false;}
      if(CQTwdFbkzi == true){CQTwdFbkzi = false;}
      if(ulMrjiOTlA == true){ulMrjiOTlA = false;}
      if(SygKaCgKLf == true){SygKaCgKLf = false;}
      if(toaksOFyFO == true){toaksOFyFO = false;}
      if(PjTAYoJFkV == true){PjTAYoJFkV = false;}
      if(QNWOnDjIUb == true){QNWOnDjIUb = false;}
      if(XRZTnFKayV == true){XRZTnFKayV = false;}
      if(dQNWkheflk == true){dQNWkheflk = false;}
      if(saZoOfSMwp == true){saZoOfSMwp = false;}
      if(dwcdpyKAMS == true){dwcdpyKAMS = false;}
      if(ehHPrAAAdF == true){ehHPrAAAdF = false;}
      if(YEWiixrjEH == true){YEWiixrjEH = false;}
      if(mydIqgmjfl == true){mydIqgmjfl = false;}
      if(XdTSGKTJxO == true){XdTSGKTJxO = false;}
      if(fRiqQZZsus == true){fRiqQZZsus = false;}
      if(GawEffEyXL == true){GawEffEyXL = false;}
      if(NQTqhukDcX == true){NQTqhukDcX = false;}
      if(chlpbVOmrQ == true){chlpbVOmrQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDEJXBJRTF
{ 
  void eQWwIVMQoC()
  { 
      bool lwoNyMCVEI = false;
      bool rVdlyGSoBD = false;
      bool WCtunozoRV = false;
      bool mqbXxHDYaC = false;
      bool nUsZZlnboL = false;
      bool dOhSGiCtZJ = false;
      bool NMDiUBsFoq = false;
      bool CsOyPBJTUB = false;
      bool AXzGrYIIQN = false;
      bool EJzQoaQJEY = false;
      bool shlyIjAjDE = false;
      bool ZhYYIoMxqu = false;
      bool rjnalrtxJn = false;
      bool kzOwHSkBxH = false;
      bool YYFLmWjaHz = false;
      bool NTSJfJsKLQ = false;
      bool pCaPTaScQp = false;
      bool DLziWTdcnP = false;
      bool HToJZRgFQx = false;
      bool ZaogRWxprM = false;
      string gxZwiSLCWF;
      string OMNJJAnCYG;
      string JUTWMurpNJ;
      string jscQOimmWk;
      string snSKeegUQr;
      string wghUkMcCim;
      string aVnMVViwua;
      string NAfnNUCJqh;
      string NWYUMCLHfB;
      string FjEiJWzFoJ;
      string ukYpewBsHP;
      string KTKAYEwTAS;
      string JbPsUcwwep;
      string VwThmcxipQ;
      string BSAQqlYDJF;
      string afFVzTUfUC;
      string zEOQsNzcNw;
      string GNciRqazBi;
      string DslYPpqxhS;
      string IRNnRwDiWd;
      if(gxZwiSLCWF == ukYpewBsHP){lwoNyMCVEI = true;}
      else if(ukYpewBsHP == gxZwiSLCWF){shlyIjAjDE = true;}
      if(OMNJJAnCYG == KTKAYEwTAS){rVdlyGSoBD = true;}
      else if(KTKAYEwTAS == OMNJJAnCYG){ZhYYIoMxqu = true;}
      if(JUTWMurpNJ == JbPsUcwwep){WCtunozoRV = true;}
      else if(JbPsUcwwep == JUTWMurpNJ){rjnalrtxJn = true;}
      if(jscQOimmWk == VwThmcxipQ){mqbXxHDYaC = true;}
      else if(VwThmcxipQ == jscQOimmWk){kzOwHSkBxH = true;}
      if(snSKeegUQr == BSAQqlYDJF){nUsZZlnboL = true;}
      else if(BSAQqlYDJF == snSKeegUQr){YYFLmWjaHz = true;}
      if(wghUkMcCim == afFVzTUfUC){dOhSGiCtZJ = true;}
      else if(afFVzTUfUC == wghUkMcCim){NTSJfJsKLQ = true;}
      if(aVnMVViwua == zEOQsNzcNw){NMDiUBsFoq = true;}
      else if(zEOQsNzcNw == aVnMVViwua){pCaPTaScQp = true;}
      if(NAfnNUCJqh == GNciRqazBi){CsOyPBJTUB = true;}
      if(NWYUMCLHfB == DslYPpqxhS){AXzGrYIIQN = true;}
      if(FjEiJWzFoJ == IRNnRwDiWd){EJzQoaQJEY = true;}
      while(GNciRqazBi == NAfnNUCJqh){DLziWTdcnP = true;}
      while(DslYPpqxhS == DslYPpqxhS){HToJZRgFQx = true;}
      while(IRNnRwDiWd == IRNnRwDiWd){ZaogRWxprM = true;}
      if(lwoNyMCVEI == true){lwoNyMCVEI = false;}
      if(rVdlyGSoBD == true){rVdlyGSoBD = false;}
      if(WCtunozoRV == true){WCtunozoRV = false;}
      if(mqbXxHDYaC == true){mqbXxHDYaC = false;}
      if(nUsZZlnboL == true){nUsZZlnboL = false;}
      if(dOhSGiCtZJ == true){dOhSGiCtZJ = false;}
      if(NMDiUBsFoq == true){NMDiUBsFoq = false;}
      if(CsOyPBJTUB == true){CsOyPBJTUB = false;}
      if(AXzGrYIIQN == true){AXzGrYIIQN = false;}
      if(EJzQoaQJEY == true){EJzQoaQJEY = false;}
      if(shlyIjAjDE == true){shlyIjAjDE = false;}
      if(ZhYYIoMxqu == true){ZhYYIoMxqu = false;}
      if(rjnalrtxJn == true){rjnalrtxJn = false;}
      if(kzOwHSkBxH == true){kzOwHSkBxH = false;}
      if(YYFLmWjaHz == true){YYFLmWjaHz = false;}
      if(NTSJfJsKLQ == true){NTSJfJsKLQ = false;}
      if(pCaPTaScQp == true){pCaPTaScQp = false;}
      if(DLziWTdcnP == true){DLziWTdcnP = false;}
      if(HToJZRgFQx == true){HToJZRgFQx = false;}
      if(ZaogRWxprM == true){ZaogRWxprM = false;}
    } 
}; 
