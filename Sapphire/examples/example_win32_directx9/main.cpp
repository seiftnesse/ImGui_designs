// Dear ImGui: standalone example application for DirectX 9
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include <d3d9.h>
#include <tchar.h>
#include <string>
#include <vector>
#define random_f (float a, float b) rand() % (b - a + 1) + a;
template<class T, class U>
static T clamp(const T& in, const U& low, const U& high)
{
    if (in <= low)
        return low;

    if (in >= high)
        return high;

    return in;
}
// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// Main code
#define IM_USE using namespace ImGui;
static int tab = 0;
#include <math.h>
#include "Header.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Elements.h"
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")
void CircularProgressBar(int x, int y, int r1, int r2, int s, int d, ImColor col, bool invert = false)
{
    for (int i = s; i < s + d; i++)
    {
        auto rad = i * 3.1415 / 180;
        if (!invert)
           ImGui::GetOverlayDrawList()->AddLine(ImVec2(x + cos(rad) * r1, y + sin(rad) * r1), ImVec2(x + cos(rad) * r2, y + sin(rad) * r2), col);
        else
            ImGui::GetOverlayDrawList()->AddLine(ImVec2(x - cos(rad) * r1, y - sin(rad) * r1), ImVec2(x - cos(rad) * r2, y - sin(rad) * r2), col);
    }
}

void FadedCircle(int x, int y, int radius, ImColor color) {
    auto step = color.Value.w / (radius * 0.5);

    for (int i = 5; i <= radius; i++) {
        ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), 15 + i, ImColor(color.Value.x, color.Value.y, color.Value.z, color.Value.w - step * i));
    }
}

#include <iostream>
#include <chrono>
#include <ctime> 
int rand_between(const int from, const int to) {
    if (to == from)
        return to;
    if (to < from)
        return rand_between(to, from);
    return from + rand() % (to - from + 1);
}
void CurPosx(int pos)
{
    ImGui::SetCursorPosX(pos);
}
void CurPosy(int pos)
{
    ImGui::SetCursorPosY(pos);
}
void CurPos(ImVec2 pos)
{
    ImGui::SetCursorPos(pos);
}
 bool one = true;
 bool two = false;
//MAIN COLOR: 112, 146, 190
int main(int, char**)
{
   
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX9 Example"), WS_POPUP, 0, 0, 1366, 768, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    
    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);
    LPDIRECT3DTEXTURE9 lg = nullptr;
    if (lg == nullptr) {
        D3DXCreateTextureFromFileInMemory(g_pd3dDevice, &logo, sizeof(logo), &lg);
    }
    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    ImFontConfig font_config;
    font_config.OversampleH = 1; //or 2 is the same
    font_config.OversampleV = 1;
    font_config.PixelSnapH = 1;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x044F, // Cyrillic
        0,
    };
    ImFont* name = io.Fonts->AddFontFromFileTTF("../../misc/fonts/Museo Sans Cyrl 700.ttf", 38.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFont* isis = io.Fonts->AddFontFromFileTTF("../../misc/fonts/Museo Sans Cyrl 700.ttf", 24.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFont* icon_font = io.Fonts->AddFontFromMemoryTTF((void*)Icons, sizeof(Icons), 40, &font_config, io.Fonts->GetGlyphRangesDefault());
    ImFont* weapon_icons = io.Fonts->AddFontFromMemoryTTF((void*)weapons_font, sizeof(weapons_font), 18, &font_config, io.Fonts->GetGlyphRangesDefault());
    ImFont* font = io.Fonts->AddFontFromFileTTF("../../misc/fonts/Museo Sans Cyrl 700.ttf", 14.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.51f, 0.55f, 0.57f, 1.00f);
    static int beep = 0;
    static float alpha = 0.f;
    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;
        bool open = false;
        
        static int sl = 0;
        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        auto st = ImGui::GetStyle();
        st.Colors[ImGuiCol_ResizeGrip] = ImColor(0, 0, 0, 0);
        st.Colors[ImGuiCol_ResizeGripActive] = ImColor(0, 0, 0, 0);
        st.Colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 0, 0, 0);
        auto s = ImVec2{}, p = ImVec2{}, GuiSize = ImVec2{653, 460 };
        std::string uname, build, build_at;
        uname = "insania"; build = "[alpha]"; build_at = __DATE__; build_at += " "; build_at += __TIME__;
        bool hellllo = GetKeyState(VK_INSERT);
        bool hellllo2 = GetKeyState(VK_HOME);
        static float tab_anim_br = 0.f;
        static int tab_anim = 42;
        bool tab_hovered = false;
        ImGui::GetIO().Font = font;
        //menu
       
        ImGui::SetNextWindowSize(ImVec2(GuiSize));
        ImGui::Begin("##GUI", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground);
        {
            ImVec2 pad = ImGui::GetStyle().WindowPadding;
            {//draw
                s = ImVec2(ImGui::GetWindowSize().x - pad.x * 2, ImGui::GetWindowSize().y - pad.y * 2); p = ImVec2(ImGui::GetWindowPos().x + pad.x, ImGui::GetWindowPos().y + pad.y); auto draw = ImGui::GetWindowDrawList();
                draw->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + s.x, p.y + s.y), ImColor(33,33,33));
                if (tab_anim_br > 0)
                    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + s.x, p.y + s.y), ImColor(0, 0, 0, int(140 * tab_anim_br)));
                ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + tab_anim, p.y + s.y - 20), ImColor(39, 39, 39));
                ImGui::PushFont(font);
                draw->AddText(ImVec2(p.x + 5, p.y + s.y - 20 + (10 - ImGui::CalcTextSize(std::string("saphire " + build + " | build at: " + build_at).c_str()).y / 2)), ImColor(220, 220, 220), std::string("saphire " + build + " | build at: " + build_at).c_str());
                draw->AddText(ImVec2(p.x + s.x - 5 - ImGui::CalcTextSize(std::string("Welcome back, " + uname).c_str()).x, p.y + s.y - 20 + (10 - ImGui::CalcTextSize(std::string("Welcome back, " + uname).c_str()).y / 2)), ImColor(220, 220, 220), std::string("Welcome back, " + uname).c_str());
                ImGui::PopFont();
                {
                    static float ss = 0.f;
                    if (tab_anim > 220 && ss < 1.f)
                        ss += 0.02f;
                    else if (tab_anim < 220 && ss > 0.f)
                        ss -= 0.04f;
                    ImGui::PushFont(name);
                    ImGui::GetForegroundDrawList()->AddText(ImVec2(p.x + tab_anim / 2 - ImGui::CalcTextSize("Saphire").x / 2, p.y + 20 - ImGui::CalcTextSize("Saphire").y / 2), ImColor(48 / 255.f, 119 / 255.f, 233 / 255.f, ImClamp(ss * 2.f, 0.f, 1.f)), "Saphire");
                    ImGui::PopFont();
                }
            }
            ImGui::SetCursorPos(pad);
            ImGui::BeginGroup(/*MAIN SPACE START*/);
            {
                {//tabs
                    {
                        ImGui::PushFont(icon_font);
                        ImGui::SetCursorPosY(50);
                        if (ImGui::tab("R", "Ragebot", "Ragebot, Weapons settings", tab == 0, tab_anim))tab = 0; if (ImGui::IsItemHovered())tab_hovered = true;
                        ImGui::SetCursorPosY(100);
                        if (ImGui::tab("L", "Legitbot", "Legitbot, Triggerbot", tab == 1, tab_anim))tab = 1; if (ImGui::IsItemHovered())tab_hovered = true;
                        ImGui::SetCursorPosY(150);
                        if (ImGui::tab("A", "Anti-aim", "Antiaim, Yaw, Pitch, Desync", tab == 2, tab_anim))tab = 2; if (ImGui::IsItemHovered())tab_hovered = true;
                        ImGui::SetCursorPosY(200);
                        if (ImGui::tab("W", "Visuals", "Chams, ESP, World", tab == 3, tab_anim))tab = 3; if (ImGui::IsItemHovered())tab_hovered = true;
                        ImGui::SetCursorPosY(245);
                        if (ImGui::tab("I", "Skins", "Skincahnger, Agentchanger", tab == 4, tab_anim))tab = 4; if (ImGui::IsItemHovered())tab_hovered = true;
                        ImGui::SetCursorPosY(295);
                        if (ImGui::tab("M", "Misc", "Movement, Gameplay", tab == 5, tab_anim))tab = 5; if (ImGui::IsItemHovered())tab_hovered = true;
                        ImGui::SetCursorPosY(345);
                        if (ImGui::tab("C", "Configs", "Save, Load, Share configs", tab == 6, tab_anim))tab = 6; if (ImGui::IsItemHovered())tab_hovered = true;
                        ImGui::SetCursorPosY(390);
                        if (ImGui::tab("S", "Lua", "Adjust your game", tab == 7, tab_anim))tab = 7; if (ImGui::IsItemHovered())tab_hovered = true;
                        ImGui::PopFont();
                    }
                    if (tab_hovered && tab_anim < 220 /** ImGui::GetIO().gui_scale*/)
                        tab_anim += 6;
                    else if (!tab_hovered && tab_anim > 42 /** ImGui::GetIO().gui_scale*/)
                        tab_anim -= 6;
                    if (tab_hovered && tab_anim_br < 1.f)
                        tab_anim_br += 0.05f;
                    else if (!tab_hovered && tab_anim_br > 0.f)
                        tab_anim_br -= 0.05f;
                }
                ImGui::PushFont(font);
                {
                    static int stab = 0;
                    ImGui::SetCursorPos(ImVec2(pad.x + 48, pad.y));
                    ImGui::BeginGroup(/*SUBTABs SPACE START*/);
                    {
                       
                        ImGui::PushFont(font);
                        //bomb y
                        if (ImGui::subtab("Main", stab == 0, 285, 1))stab = 0; ImGui::SameLine();
                        if (ImGui::subtab("Weapons", stab == 1, 285, 1))stab = 1; ImGui::SameLine();
                        ImGui::PopFont();
                    }
                    ImGui::EndGroup(/*SUBTABs SPACE END*/);
                    static float stab_anim = 0.f;
                    if (stab && stab_anim < 1.f)
                        stab_anim += 0.05f;
                    else if (!stab && stab_anim > 0)
                        stab_anim -= 0.1f;
                    if (stab_anim) {
                        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, stab_anim);
                        ImGui::SetCursorPos(ImVec2(pad.x + 48, pad.y + 22));
                        ImGui::BeginGroup(/*SUBTABs SPACE START*/);
                        {
                            static int subtab = 0;
                            ImGui::PushFont(weapon_icons);
                            //bomb y
                            if (ImGui::subtab("G", subtab == 0, 58, 1, 1))subtab = 0; ImGui::SameLine();//pistol 
                            if (ImGui::subtab("J", subtab == 1, 58, 1, 1))subtab = 1; ImGui::SameLine();//revolv 
                            if (ImGui::subtab("A", subtab == 2, 58, 1, 1))subtab = 2; ImGui::SameLine();//deagle 
                            if (ImGui::subtab("S", subtab == 3, 58, 1, 1))subtab = 3; ImGui::SameLine();//rifle  
                            if (ImGui::subtab("L", subtab == 4, 58, 1, 1))subtab = 4; ImGui::SameLine();//smg    
                            if (ImGui::subtab("d", subtab == 5, 58, 1, 1))subtab = 5; ImGui::SameLine();//heavy  
                            if (ImGui::subtab("a", subtab == 6, 58, 1, 1))subtab = 6; ImGui::SameLine();//ssg
                            if (ImGui::subtab("Y", subtab == 7, 57, 1, 1))subtab = 7; ImGui::SameLine();//auto   
                            if (ImGui::subtab("Z", subtab == 8, 57, 1, 1))subtab = 8; ImGui::SameLine();//awp    
                            ImGui::PopFont();
                        }
                        ImGui::EndGroup(/*SUBTABs SPACE END*/);
                        ImGui::PopStyleVar();
                    }
                    ImGui::SetCursorPos(ImVec2(pad.x + 48, pad.y + 54 + 20 * stab_anim));
                    ImGui::BeginGroup(/*CHILDs SPACE START*/);
                    {   ImGui::MenuChild("first", ImVec2(290, 400 - 20 * stab_anim));
                        {
                        
                        }
                        ImGui::EndMenuChild();

                        ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 295, pad.y + 54 + 20 * stab_anim));
                        ImGui::MenuChild("second", ImVec2(290, 400 - 20 * stab_anim));
                        {
                            ImGui::Checkbox("Checkbox one", &one);
                            ImGui::Checkbox("Checkbox two", &two);
                            ImGui::SliderInt("Slider", &sl, 0, 100);
                            if (ImGui::BeginCombo("Combo", "Say hello :^D"))
                            {
                                ImGui::EndCombo();
                            }
                            ImGui::SliderInt("Slider", &sl, 0, 100);
                            if (ImGui::ListBoxHeader("Not Combo", ImVec2(290 - 18, 300)))
                            {
                                ImGui::ListBoxFooter();
                            }
                        }
                        ImGui::EndMenuChild();
                    }
                    ImGui::EndGroup(/*CHILDs SPACE END*/);
                }
                ImGui::PopFont();
            }
            ImGui::EndGroup(/*MAIN SPACE END*/);
        }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(301, 20));
        ImGui::Begin("##WM", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground);
        {
            static float ss = 0.f;
            ImVec2 pad = ImGui::GetStyle().WindowPadding;
           
            s = ImVec2(ImGui::GetWindowSize().x - pad.x * 2, ImGui::GetWindowSize().y - pad.y * 2); p = ImVec2(ImGui::GetWindowPos().x + pad.x, ImGui::GetWindowPos().y + pad.y); auto draw = ImGui::GetForegroundDrawList();
            draw->AddRectFilled(p, ImVec2(p.x + s.x, p.y + s.y), ImColor(33, 33, 33, 210));
            ImVec4 col = ImLerp(ImVec4{ 162 / 255.f, 91 / 255.f, 169 / 255.f, 1.f }, ImVec4{ 48 / 255.f, 119 / 255.f, 253 / 255.f, 1.f }, 1.f);
            ImVec4 col2 = ImLerp(ImVec4{ 48 / 255.f, 119 / 255.f, 253 / 255.f, 1.f }, ImVec4{ 162 / 255.f, 91 / 255.f, 169 / 255.f, 1.f }, 1.f);
            draw->AddRectFilledMultiColor(p, ImVec2(p.x + s.x / 2, p.y + 2), ImColor(col), ImColor(col2), ImColor(col2), ImColor(col));
            draw->AddRectFilledMultiColor(ImVec2(p.x + s.x / 2, p.y), ImVec2(p.x + s.x, p.y + 2), ImColor(col2), ImColor(col), ImColor(col), ImColor(col2));
            ImGui::PushFont(font);
            draw->AddText(ImVec2(p.x + 2, p.y + (9 - ImGui::CalcTextSize("saphire [alpha] | insania | ip address | 15 ping | 19:36").y / 2)), ImColor(220, 220, 220), "saphire [alpha] | insania | ip address | 15 ping | 19:36");
            ImGui::PopFont();
        }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(220, 60));
        ImGui::Begin("##KB", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground);
        {
            static float ss = 0.f;
            ImVec2 pad = ImGui::GetStyle().WindowPadding;

            s = ImVec2(ImGui::GetWindowSize().x - pad.x * 2, ImGui::GetWindowSize().y - pad.y * 2); p = ImVec2(ImGui::GetWindowPos().x + pad.x, ImGui::GetWindowPos().y + pad.y); auto draw = ImGui::GetForegroundDrawList();
            draw->AddRectFilled(p, ImVec2(p.x + s.x, p.y + 20), ImColor(33, 33, 33, 210));
            draw->AddRectFilled(ImVec2(p.x, p.y + 20), ImVec2(p.x + s.x, p.y + 60), ImColor(33, 33, 33, 60));
            ImVec4 col = ImLerp(ImVec4{ 162 / 255.f, 91 / 255.f, 169 / 255.f, 1.f }, ImVec4{ 48 / 255.f, 119 / 255.f, 253 / 255.f, 1.f }, 1.f);
            ImVec4 col2 = ImLerp(ImVec4{ 48 / 255.f, 119 / 255.f, 253 / 255.f, 1.f }, ImVec4{ 162 / 255.f, 91 / 255.f, 169 / 255.f, 1.f }, 1.f);
            draw->AddRectFilledMultiColor(p, ImVec2(p.x + s.x / 2, p.y + 2), ImColor(col), ImColor(col2), ImColor(col2), ImColor(col));
            draw->AddRectFilledMultiColor(ImVec2(p.x + s.x / 2, p.y), ImVec2(p.x + s.x, p.y + 2), ImColor(col2), ImColor(col), ImColor(col), ImColor(col2));
            ImGui::PushFont(font);
            draw->AddText(ImVec2(p.x + 100 - ImGui::CalcTextSize("Keybindings").x / 2, p.y + (9 - ImGui::CalcTextSize("Keybindings").y / 2)), ImColor(220, 220, 220), "Keybindings");
            ImGui::PopFont();


            ImGui::PushFont(font);
            draw->AddText(ImVec2(p.x + 5, p.y + 20 + (10 - ImGui::CalcTextSize("Doubletap").y / 2)), ImColor(220, 220, 220), "Doubletap");
            draw->AddText(ImVec2(p.x + 195 - ImGui::CalcTextSize("Toggled").x, p.y + 20 + (10 - ImGui::CalcTextSize("Toggled").y / 2)), ImColor(220, 220, 220), "Toggled");
            ImGui::PopFont();

            ImGui::PushFont(font);
            draw->AddText(ImVec2(p.x + 5, p.y + 40 + (10 - ImGui::CalcTextSize("On shot antiaim").y / 2)), ImColor(220, 220, 220), "On shot antiaim");
            draw->AddText(ImVec2(p.x + 195 - ImGui::CalcTextSize("Toggled").x, p.y + 40 + (10 - ImGui::CalcTextSize("Toggled").y / 2)), ImColor(220, 220, 220), "Toggled");
            ImGui::PopFont();
        }
        ImGui::End();

        ImGui::PushFont(font);
        auto draw = ImGui::GetOverlayDrawList();
        auto size = ImGui::CalcTextSize("Missed shot due to occlusion");
        draw->AddRectFilledMultiColor(ImVec2(0, 50), ImVec2(size.x + 45, 18 + 50), ImColor(33,33,33, 125), ImColor(33, 33, 33, 5), ImColor(33, 33, 33, 5), ImColor(33, 33, 33, 125));
        draw->AddText(ImVec2(5, 9 - size.y / 2 + 50), ImColor(250, 120, 20), "[Miss] ");
        draw->AddText(ImVec2(40, 9 - size.y / 2 + 50), ImColor(220, 220, 220), "Missed shot due to occlusion");
        ImGui::PopFont();
        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, 0);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*clear_color.w*255.0f), (int)(clear_color.y*clear_color.w*255.0f), (int)(clear_color.z*clear_color.w*255.0f), (int)(clear_color.w*255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
     
        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }
   
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
