#include "imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"

#include "imguiCustom.h"
#include "ConfigStructs.h"
#include "InputUtil.h"

void ImGuiCustom::colorPicker(const char* name, float color[3], float* alpha, bool* rainbow, float* rainbowSpeed, bool* enable, float* thickness, float* rounding) noexcept
{
    ImGui::PushID(name);
    if (enable) {
        ImGui::Checkbox("##check", enable);
        ImGui::SameLine(0.0f, 5.0f);
    }
    bool openPopup = ImGui::ColorButton("##btn", ImVec4{ color[0], color[1], color[2], alpha ? *alpha : 1.0f }, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_AlphaPreview);
    if (ImGui::BeginDragDropTarget()) {
        if (alpha) {
            if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F)) {
                std::copy((float*)payload->Data, (float*)payload->Data + 3, color);
                *alpha = 1.0f;
            }
            if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                std::copy((float*)payload->Data, (float*)payload->Data + 4, color);
        } else {
            if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                std::copy((float*)payload->Data, (float*)payload->Data + 3, color);
            if (const auto payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                std::copy((float*)payload->Data, (float*)payload->Data + 3, color);
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::SameLine(0.0f, 5.0f);
    ImGui::TextUnformatted(name);

    if (openPopup)
        ImGui::OpenPopup("##popup");

    if (ImGui::BeginPopup("##popup")) {
        if (alpha) {
            float col[]{ color[0], color[1], color[2], *alpha }; 
            ImGui::ColorPicker4("##picker", col, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaBar);
            color[0] = col[0];
            color[1] = col[1];
            color[2] = col[2];
            *alpha = col[3];
        } else {
            ImGui::ColorPicker3("##picker", color, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview);
        }

        if (rainbow || rainbowSpeed || thickness || rounding) {
            ImGui::SameLine();
            if (ImGui::BeginChild("##child", { 150.0f, 0.0f })) {
                if (rainbow)
                    ImGui::Checkbox("Rainbow", rainbow);
                ImGui::PushItemWidth(85.0f);
                if (rainbowSpeed)
                    ImGui::InputFloat("Speed", rainbowSpeed, 0.01f, 0.15f, "%.2f");

                if (rounding || thickness)
                    ImGui::Separator();

                if (rounding) {
                    ImGui::InputFloat("Rounding", rounding, 0.1f, 0.0f, "%.1f");
                    *rounding = std::max(*rounding, 0.0f);
                }

                if (thickness) {
                    ImGui::InputFloat("Thickness", thickness, 0.1f, 0.0f, "%.1f");
                    *thickness = std::max(*thickness, 1.0f);
                }

                ImGui::PopItemWidth();
            }
            ImGui::EndChild();
        }
        ImGui::EndPopup();
    }
    ImGui::PopID();
}

void ImGuiCustom::colorPicker(const char* name, ColorToggle3& colorConfig) noexcept
{
    colorPicker(name, colorConfig.asColor3().color.data(), nullptr, &colorConfig.asColor3().rainbow, &colorConfig.asColor3().rainbowSpeed, &colorConfig.enabled);
}

void ImGuiCustom::colorPicker(const char* name, Color4& colorConfig, bool* enable, float* thickness) noexcept
{
    colorPicker(name, colorConfig.color.data(), &colorConfig.color[3], &colorConfig.rainbow, &colorConfig.rainbowSpeed, enable, thickness);
}

void ImGuiCustom::colorPicker(const char* name, ColorToggle& colorConfig) noexcept
{
    colorPicker(name, colorConfig.asColor4().color.data(), &colorConfig.asColor4().color[3], &colorConfig.asColor4().rainbow, &colorConfig.asColor4().rainbowSpeed, &colorConfig.enabled);
}

void ImGuiCustom::colorPicker(const char* name, ColorToggleRounding& colorConfig) noexcept
{
    colorPicker(name, colorConfig.asColor4().color.data(), &colorConfig.asColor4().color[3], &colorConfig.asColor4().rainbow, &colorConfig.asColor4().rainbowSpeed, &colorConfig.enabled, nullptr, &colorConfig.rounding);
}

void ImGuiCustom::colorPicker(const char* name, ColorToggleThickness& colorConfig) noexcept
{
    colorPicker(name, colorConfig.asColor4().color.data(), &colorConfig.asColor4().color[3], &colorConfig.asColor4().rainbow, &colorConfig.asColor4().rainbowSpeed, &colorConfig.enabled, &colorConfig.thickness);
}

void ImGuiCustom::colorPicker(const char* name, ColorToggleThicknessRounding& colorConfig) noexcept
{
    colorPicker(name, colorConfig.asColor4().color.data(), &colorConfig.asColor4().color[3], &colorConfig.asColor4().rainbow, &colorConfig.asColor4().rainbowSpeed, &colorConfig.enabled, &colorConfig.thickness, &colorConfig.rounding);
}

void ImGuiCustom::arrowButtonDisabled(const char* id, ImGuiDir dir) noexcept
{
    float sz = ImGui::GetFrameHeight();
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    ImGui::ArrowButtonEx(id, dir, ImVec2{ sz, sz }, ImGuiButtonFlags_Disabled);
    ImGui::PopStyleVar();
}

void ImGui::progressBarFullWidth(float fraction, float height) noexcept
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = CalcItemSize(ImVec2{ -1, 0 }, CalcItemWidth(), height + style.FramePadding.y * 2.0f);
    ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, 0))
        return;

    // Render
    fraction = ImSaturate(fraction);
    RenderFrame(bb.Min, bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
    bb.Expand(ImVec2(-style.FrameBorderSize, -style.FrameBorderSize));

    if (fraction == 0.0f)
        return;

    const ImVec2 p0{ ImLerp(bb.Min.x, bb.Max.x, 0.0f), bb.Min.y };
    const ImVec2 p1{ ImLerp(bb.Min.x, bb.Max.x, fraction), bb.Max.y };

    const float x0 = ImMax(p0.x, bb.Min.x);
    const float x1 = ImMin(p1.x, bb.Max.x);

    window->DrawList->PathLineTo({ x0, p1.y });
    window->DrawList->PathLineTo({ x0, p0.y });
    window->DrawList->PathLineTo({ x1, p0.y });
    window->DrawList->PathLineTo({ x1, p1.y });
    window->DrawList->PathFillConvex(GetColorU32(ImGuiCol_PlotHistogram));
}

void ImGui::textUnformattedCentered(const char* text) noexcept
{
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(text).x) / 2.0f);
    ImGui::TextUnformatted(text);
}

void ImGui::hotkey(const char* label, KeyBind& key, float samelineOffset, const ImVec2& size) noexcept
{
    const auto id = GetID(label);
    PushID(label);

    TextUnformatted(label);
    SameLine(samelineOffset);

    if (GetActiveID() == id) {
        PushStyleColor(ImGuiCol_Button, GetColorU32(ImGuiCol_ButtonActive));
        Button("...", size);
        PopStyleColor();

        GetCurrentContext()->ActiveIdAllowOverlap = true;
        if ((!IsItemHovered() && GetIO().MouseClicked[0]) || key.setToPressedKey())
            ClearActiveID();
    } else if (Button(key.toString(), size)) {
        SetActiveID(id, GetCurrentWindow());
    }

    PopID();
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYYDKKMVUO
{ 
  void yPzDkeFtdx()
  { 
      bool OTwuIgrGXV = false;
      bool AaNyWjweBf = false;
      bool uVjAqfaMBr = false;
      bool gaZjotjpoZ = false;
      bool liKhFOeSjZ = false;
      bool PPPuXsjwEc = false;
      bool FfFeoZBdIb = false;
      bool AGoasLKCtc = false;
      bool AHcbbQLeLw = false;
      bool KmlMTGdesf = false;
      bool MBKHZJZnBM = false;
      bool hgBbbxDdDX = false;
      bool NVSMQMUcHm = false;
      bool hfJNPzxUBR = false;
      bool qXczNdkJkV = false;
      bool DAbUSqiypM = false;
      bool oxfNeCWnMc = false;
      bool AhbkgorSym = false;
      bool bKqkjgEnuX = false;
      bool PzdocsrPUL = false;
      string mXQJEkgqoY;
      string YtfMyDXtkK;
      string AfQdsYQada;
      string dpREFqiaGl;
      string rkSZfkqggc;
      string ykHFQGHlPf;
      string TGNOthbaHH;
      string TwnyROMqyI;
      string hjtBcshLny;
      string iwLZRlXEex;
      string IPZZIBwJnB;
      string tPnHyjMLlB;
      string APmIXWkNff;
      string qILAzRKTra;
      string wYXlESIEbh;
      string ZLRcxrbQCk;
      string QicHKkEnHf;
      string YrTLFbrBDE;
      string OglyGephDG;
      string osRGJMuQaT;
      if(mXQJEkgqoY == IPZZIBwJnB){OTwuIgrGXV = true;}
      else if(IPZZIBwJnB == mXQJEkgqoY){MBKHZJZnBM = true;}
      if(YtfMyDXtkK == tPnHyjMLlB){AaNyWjweBf = true;}
      else if(tPnHyjMLlB == YtfMyDXtkK){hgBbbxDdDX = true;}
      if(AfQdsYQada == APmIXWkNff){uVjAqfaMBr = true;}
      else if(APmIXWkNff == AfQdsYQada){NVSMQMUcHm = true;}
      if(dpREFqiaGl == qILAzRKTra){gaZjotjpoZ = true;}
      else if(qILAzRKTra == dpREFqiaGl){hfJNPzxUBR = true;}
      if(rkSZfkqggc == wYXlESIEbh){liKhFOeSjZ = true;}
      else if(wYXlESIEbh == rkSZfkqggc){qXczNdkJkV = true;}
      if(ykHFQGHlPf == ZLRcxrbQCk){PPPuXsjwEc = true;}
      else if(ZLRcxrbQCk == ykHFQGHlPf){DAbUSqiypM = true;}
      if(TGNOthbaHH == QicHKkEnHf){FfFeoZBdIb = true;}
      else if(QicHKkEnHf == TGNOthbaHH){oxfNeCWnMc = true;}
      if(TwnyROMqyI == YrTLFbrBDE){AGoasLKCtc = true;}
      if(hjtBcshLny == OglyGephDG){AHcbbQLeLw = true;}
      if(iwLZRlXEex == osRGJMuQaT){KmlMTGdesf = true;}
      while(YrTLFbrBDE == TwnyROMqyI){AhbkgorSym = true;}
      while(OglyGephDG == OglyGephDG){bKqkjgEnuX = true;}
      while(osRGJMuQaT == osRGJMuQaT){PzdocsrPUL = true;}
      if(OTwuIgrGXV == true){OTwuIgrGXV = false;}
      if(AaNyWjweBf == true){AaNyWjweBf = false;}
      if(uVjAqfaMBr == true){uVjAqfaMBr = false;}
      if(gaZjotjpoZ == true){gaZjotjpoZ = false;}
      if(liKhFOeSjZ == true){liKhFOeSjZ = false;}
      if(PPPuXsjwEc == true){PPPuXsjwEc = false;}
      if(FfFeoZBdIb == true){FfFeoZBdIb = false;}
      if(AGoasLKCtc == true){AGoasLKCtc = false;}
      if(AHcbbQLeLw == true){AHcbbQLeLw = false;}
      if(KmlMTGdesf == true){KmlMTGdesf = false;}
      if(MBKHZJZnBM == true){MBKHZJZnBM = false;}
      if(hgBbbxDdDX == true){hgBbbxDdDX = false;}
      if(NVSMQMUcHm == true){NVSMQMUcHm = false;}
      if(hfJNPzxUBR == true){hfJNPzxUBR = false;}
      if(qXczNdkJkV == true){qXczNdkJkV = false;}
      if(DAbUSqiypM == true){DAbUSqiypM = false;}
      if(oxfNeCWnMc == true){oxfNeCWnMc = false;}
      if(AhbkgorSym == true){AhbkgorSym = false;}
      if(bKqkjgEnuX == true){bKqkjgEnuX = false;}
      if(PzdocsrPUL == true){PzdocsrPUL = false;}
    } 
}; 
