#include "ImGui/ImGui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "keybinder.hpp"

#include "menu.h"
#include "globals.h"
#include "xor.hpp"

#include <iostream>
#include <windows.h>

bool loadOnce = true;
int bgradeHeight = 136;

static const char* weapon_names[]{ "Assault Rifle", "LR-300", "MP5" };
static const char* scope_names[] { "None", "Holo", "8x", "16x", "Simple"};
static const char* barrel_names[]{ "None", "Muzzle Break", "Suppressor" };

static const char* upgradeType[]{ "Default upgrade", "Upgrade if avaible" };
static const char* materials[]{ "Wood", "Stone", "Metal", "HQM" };

ImVec4 mainColor = ImColor(94, 156, 255, 255);
ImVec4 disabledMainColor = ImColor(107, 107, 107, 255);

ImVec4 firstChildBorder = ImColor(42, 42, 42, 255);
ImVec4 firstChildColor = ImColor(17, 17, 17, 255);

ImVec4 seconedChildBorder = ImColor(42, 42, 42, 255);
ImVec4 seconedChildColor = ImColor(21, 21, 21, 255);


class initWindow {
public:
    const char* window_title = "legitware";
    ImVec2 window_size{ 440, 250 }; // x, y
    
    DWORD window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
} iw;

void load_styles()
{
    loadOnce = !loadOnce;

    ImVec4* colors = ImGui::GetStyle().Colors;
    {
        colors[ImGuiCol_WindowBg] = ImColor(21, 21, 21, 255);

        colors[ImGuiCol_FrameBg] = ImColor(12, 12, 12, 255);
        colors[ImGuiCol_FrameBgHovered] = ImColor(12, 12, 12, 255);
        colors[ImGuiCol_FrameBgActive] = ImColor(12, 12, 12, 255);

        colors[ImGuiCol_Button] = seconedChildColor;
        colors[ImGuiCol_ButtonActive] = seconedChildColor;
        colors[ImGuiCol_ButtonHovered] = seconedChildColor;

        colors[ImGuiCol_SliderGrab] = mainColor;
        colors[ImGuiCol_SliderGrabActive] = mainColor;

        colors[ImGuiCol_TextDisabled] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);

        colors[ImGuiCol_Border] = ImColor(0, 0, 0, 255);
    }

    ImGuiStyle* style = &ImGui::GetStyle();
    {
        style->WindowPadding = ImVec2(5, 5);
        style->WindowBorderSize = 0.f;

        style->FramePadding = ImVec2(2, 2);
        style->FrameRounding = 0.f;
        style->FrameBorderSize = 0.f;

        style->WindowBorderSize = 0.1f;

        style->GrabMinSize = 0.f;
    }
}

void menu::render()
{
    if (loadOnce)
        load_styles();

    if (GetAsyncKeyState(keys.enableBind) & 1)
        globals.enableRecoil = !globals.enableRecoil;

    if (GetAsyncKeyState(keys.enableCodeBind) & 1)
        globals.sendCodeKeys = !globals.sendCodeKeys;

    if (globals.active)
    {
        ImGui::SetNextWindowSize(iw.window_size);
        ImGui::SetNextWindowBgAlpha(1.0f);

        ImGui::Begin(iw.window_title, &globals.active, iw.window_flags);
        {
            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);
            ImGui::BeginChild("##firstChild", ImVec2(ImGui::GetWindowWidth() - 11, ImGui::GetWindowHeight() - 11), true);
            {
                ImGui::PushStyleColor(ImGuiCol_Border, seconedChildBorder);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, seconedChildColor);
                ImGui::BeginChild("##SeconedChild", ImVec2(73, 27), true);
                {
                    ImGui::SetCursorPos(ImVec2(15,7));
                    ImGui::Text("legitware");
                }
                ImGui::EndChild();
                ImGui::PopStyleColor(2);

                ImGui::SameLine();

                ImGui::PushStyleColor(ImGuiCol_Border, seconedChildBorder);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, seconedChildColor);
                ImGui::BeginChild("##header", ImVec2(337, 27), true, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
                {

                    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
                    {
                        ImGui::SetCursorPos(ImVec2(5, 2));

                        ImGui::PushStyleColor(ImGuiCol_Text, globals.selectedTab == 0 ? mainColor : disabledMainColor);
                        if (ImGui::Button("Main", ImVec2(40, 23)))
                        {
                            globals.selectedTab = 0;
                        }
                        ImGui::PopStyleColor();

                        ImGui::SameLine();

                        ImGui::PushStyleColor(ImGuiCol_Text, globals.selectedTab == 1 ? mainColor : disabledMainColor);
                        if (ImGui::Button("Misc", ImVec2(40, 23)))
                        {
                            globals.selectedTab = 1;
                        }
                        ImGui::PopStyleColor();
                    }
                    ImGui::PopStyleVar();
                }
                ImGui::EndChild();
                ImGui::PopStyleColor(2);

                ImGui::PushStyleColor(ImGuiCol_Border, seconedChildBorder);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, seconedChildColor);
                ImGui::BeginChild("##header2", ImVec2(73, 197), true);
                {
                    switch (globals.selectedTab)
                    {
                    case 0:
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
                        {
                            ImGui::SetCursorPos(ImVec2(5, 1));

                            ImGui::PushStyleColor(ImGuiCol_Text, globals.selectedSideTabRecoil == 0 ? mainColor : disabledMainColor);
                            if (ImGui::Button("Recoil", ImVec2(65, 20)))
                            {
                                globals.selectedSideTabRecoil = 0;
                            }
                            ImGui::PopStyleColor();

                            ImGui::PushStyleColor(ImGuiCol_Text, globals.selectedSideTabRecoil == 1 ? mainColor : disabledMainColor);
                            if (ImGui::Button("Settings", ImVec2(65, 20)))
                            {
                                globals.selectedSideTabRecoil = 1;
                            }
                            ImGui::PopStyleColor();
                        }
                        ImGui::PopStyleVar();
                        break;
                    case 1:
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
                        {
                            ImGui::SetCursorPos(ImVec2(5, 1));

                            ImGui::PushStyleColor(ImGuiCol_Text, globals.selectedSideTabMisc == 0 ? mainColor : disabledMainColor);
                            if (ImGui::Button("General", ImVec2(65, 20)))
                            {
                                globals.selectedSideTabMisc = 0;
                            }
                            ImGui::PopStyleColor();
                            
                            ImGui::PushStyleColor(ImGuiCol_Text, globals.selectedSideTabMisc == 1 ? mainColor : disabledMainColor);
                            if (ImGui::Button("Bgrade", ImVec2(65, 20)))
                            {
                                globals.selectedSideTabMisc = 1;
                            }
                            ImGui::PopStyleColor();
                        }
                        ImGui::PopStyleVar();
                    }
                }
                ImGui::EndChild();
                ImGui::PopStyleColor(2);

                ImGui::SameLine();

                ImGui::PushStyleColor(ImGuiCol_Border, seconedChildBorder);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, seconedChildColor);
                ImGui::BeginChild("##mainPage", ImVec2(337, 197), true);
                {
                    switch (globals.selectedTab)
                    {
                    case 0: // Main tab
                        switch (globals.selectedSideTabRecoil)
                        {
                        case 0:
                            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
                            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);
                            ImGui::BeginChild("##recoilMain", ImVec2(135, 59), true);
                            {
                                ImGui::SetCursorPos(ImVec2(33, 3));
                                ImGui::TextDisabled("Recoil Toggles");

                                ImGui::Checkbox("Enable", &globals.enableRecoil);
                                ImGui::SameLine();
                                {
                                    ImGui::PushStyleColor(ImGuiCol_Button, firstChildColor);
                                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, firstChildColor);
                                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, firstChildColor);
                                    {
                                        ImGui::SetCursorPos(ImVec2(70, 15));
                                        keybind::key_bind(keys.enableBind);
                                    }
                                    ImGui::PopStyleColor(3);
                                }
                                ImGui::Checkbox("Hipfire", &globals.enableHipfire);
                            }
                            ImGui::EndChild();
                            ImGui::PopStyleColor(2);

                            ImGui::SameLine();

                            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
                            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);
                            ImGui::BeginChild("##recoilSelection", ImVec2(183, 80), true);
                            {
                                ImGui::SetCursorPos(ImVec2(50, 3));
                                ImGui::TextDisabled("Weapon Config");

                                ImGui::SetNextItemWidth(120);
                                {
                                    ImGui::Combo("Weapon", &globals.selectedWeapon, weapon_names, IM_ARRAYSIZE(weapon_names));
                                }
                                ImGui::SetNextItemWidth(120);
                                {
                                    ImGui::Combo("Scope", &globals.selectedScope, scope_names, IM_ARRAYSIZE(scope_names));
                                }
                                ImGui::SetNextItemWidth(120);
                                {
                                    ImGui::Combo("Barrel", &globals.selectedBarrel, barrel_names, IM_ARRAYSIZE(barrel_names));
                                }
                            }
                            ImGui::EndChild();
                            ImGui::PopStyleColor(2);

                            ImGui::SetCursorPos(ImVec2(5, 69));
                            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
                            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);
                            ImGui::BeginChild("##recoilSettings", ImVec2(135, 95), true);
                            {
                                ImGui::SetCursorPos(ImVec2(33, 3));
                                ImGui::TextDisabled("Recoil Settings");
                                ImGui::Text("X Control                  %.0f%%", globals.controlAmountX);
                                ImGui::SetNextItemWidth(123);
                                {
                                    ImGui::SliderFloat("##X Control", &globals.controlAmountX, 0, 100, "%.0f%%");
                                }
                                ImGui::Text("Y Control                  %.0f%%", globals.controlAmountY);
                                ImGui::SetNextItemWidth(123);
                                {
                                    ImGui::SliderFloat("##Y Control", &globals.controlAmountY, 0, 100, "%.0f%%");
                                }
                            }
                            ImGui::EndChild();
                            ImGui::PopStyleColor(2);
                            break;
                        case 1:
                            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
                            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);
                            ImGui::BeginChild("##userSettings", ImVec2(135, 96), true);
                            {
                                ImGui::SetCursorPos(ImVec2(37, 3));
                                ImGui::TextDisabled("User Settings");
                                ImGui::Text("Sensitivity               %.3f", globals.userSens);
                                ImGui::SetNextItemWidth(123);
                                {
                                    ImGui::SliderFloat("Sensitivity", &globals.userSens, 0.001, 1, "%.3f");
                                }

                                ImGui::Text("FOV                             %i", globals.userFov);
                                ImGui::SetNextItemWidth(123);
                                {
                                    ImGui::SliderInt("##FOV", &globals.userFov, 65, 90);
                                }
                            }
                            ImGui::EndChild();
                            ImGui::PopStyleColor(2);
                            break;
                        }
                        break;
                    case 1: // Misc tab
                        switch (globals.selectedSideTabMisc)
                        {
                        case 0:
                            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
                            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);
                            ImGui::BeginChild("##codeEnter", ImVec2(155, 96), true);
                            {
                                ImGui::SetCursorPos(ImVec2(52, 3));
                                ImGui::TextDisabled("Auto-Code");
                                ImGui::Checkbox("Enable", &globals.enableAutoCode);
                                ImGui::SameLine();
                                {
                                    ImGui::PushStyleColor(ImGuiCol_Button, firstChildColor);
                                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, firstChildColor);
                                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, firstChildColor);
                                    {
                                        ImGui::SetCursorPos(ImVec2(70, 15));
                                        keybind::key_bind(keys.enableCodeBind);
                                    }
                                    ImGui::PopStyleColor(3);
                                }
                                ImGui::Text("Your Code:");
                                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 2));
                                ImGui::PushItemWidth(14.f);
                                {
                                    ImGui::SameLine();
                                    ImGui::InputInt("##First", &globals.codeNum1, 0, 9);
                                    ImGui::SameLine();
                                    ImGui::InputInt("##Seconed", &globals.codeNum2, 0, 9);
                                    ImGui::SameLine();
                                    ImGui::InputInt("##Third", &globals.codeNum3, 0, 9);
                                    ImGui::SameLine();
                                    ImGui::InputInt("##Forth", &globals.codeNum4, 0, 9);
                                }
                                ImGui::PopItemWidth();
                                ImGui::PopStyleVar();

                                ImGui::Text("Delay                                 %i", globals.delayBetweenKeypress);
                                ImGui::SetNextItemWidth(145);
                                {
                                    ImGui::SliderInt("##Delay", &globals.delayBetweenKeypress, 5, 800, "%.06fms");
                                }
                            }
                            ImGui::EndChild();
                            ImGui::PopStyleColor(2);

                            ImGui::SameLine();

                            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
                            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);
                            ImGui::BeginChild("##miscFeats", ImVec2(104, 40), true);
                            {
                                ImGui::SetCursorPos(ImVec2(40, 3));
                                ImGui::TextDisabled("Other");
                                ImGui::Checkbox("Anti-AFK", &globals.enableAntiAfk);
                            }
                            ImGui::EndChild();
                            ImGui::PopStyleColor(2);
                            break;
                        case 1:
                            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
                            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);
                            ImGui::BeginChild("##bgrade", ImVec2(235, bgradeHeight), true);
                            {
                                ImGui::Checkbox("Enable BGrade", &globals.enableBgrade);
                                ImGui::Combo("Upgrade Type", &globals.selectedUpgradeType, upgradeType, IM_ARRAYSIZE(upgradeType));
                                if (globals.selectedUpgradeType == 0)
                                {
                                    bgradeHeight = 136;
                                    ImGui::Combo("Meterial", &globals.selectedBgradeMaterial, materials, IM_ARRAYSIZE(materials));
                                    ImGui::Text("Upgrade Speed                                       %i%ms", globals.upgradeSpeed);
                                    ImGui::SetNextItemWidth(222);
                                    {
                                        ImGui::SliderInt("##Upgrade Speed", &globals.upgradeSpeed, 30, 100, "%.06fms");
                                    }
                                    ImGui::Text("Upgrade Delay                                       %i%ms", globals.upgradeDelay);
                                    ImGui::SetNextItemWidth(222);
                                    {
                                        ImGui::SliderInt("##Upgrade Delay", &globals.upgradeDelay, 0, 500, "%.06fms");
                                    }
                                }
                                else
                                {
                                    bgradeHeight = 50;
                                }
                            }
                            ImGui::EndChild();
                            ImGui::PopStyleColor(2);
                            break;
                        }
                        break;
                                    
                    }
                }
                ImGui::EndChild();
                ImGui::PopStyleColor(2);
            }
            ImGui::EndChild();
            ImGui::PopStyleColor(2);
        }
        ImGui::End();
    }
    else
    {
        exit(0);
    }
}