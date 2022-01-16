// Dear ImGui: standalone example application for DirectX 9
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include "bgs.h"
#include "logotype.h"

#include "misc/fonts/Montserrat-Medium.h"
#include "misc/fonts/Montserrat-Regular.h"
#include "misc/fonts/Montserrat-ExtraBold.h"
#include "misc/fonts/EvolutionIconsQunion.h"
#include <vector>
#include <imgui_internal.h>
#include <examples/example_win32_directx9/Search.hpp>
#include "options.hpp"
// Fonts
ImFont* g_pTabsFont;
ImFont* g_pNameFont;
ImFont* g_pMenuFont;
ImFont* g_pLoaderFont;
ImFont* g_pIconsFont;
ImFont* g_pIconsWatermarkFont;
ImFont* g_pBigIconsFont;

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};
IDirect3DTexture9* bgs = nullptr;
IDirect3DTexture9* logo = nullptr;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#pragma region MenuRender
#pragma region RageBotTab
void RageBotTab() {
    ImGui::Columns(2, nullptr, false);
    ImGui::BeginChild("General", ImVec2(230, 200), true);
    {
        auto settings = &opt.ragebot[0];
        ImGui::Checkbox("Enabled", &settings->enabled);
        ImGui::Checkbox("Silent", &settings->silent);
        ImGui::SliderFloat("Fov", &settings->fov, 0.f, 180.f, "%.5f");
        ImGui::Combo("Priority", &settings->priority, prioritys, IM_ARRAYSIZE(prioritys));
        ImGui::MultiCombo("Hitboxes", settings->hitbox, hitboxes, IM_ARRAYSIZE(hitboxes), settings->hitboxes);
        ImGui::Bind("Double Tap", &settings->double_tap, ImVec2(80, 20));
        ImGui::Bind("Hide Shots", &settings->hide_shots, ImVec2(80, 20));
    }
    ImGui::EndChild();
    ImGui::NewLine();
    ImGui::BeginChild("Exploits", ImVec2(230, 200), true);
    {
    }
    ImGui::EndChild();
    ImGui::NewLine();
    ImGui::BeginChild("Exploits##1", ImVec2(230, 200), true);
    {
    }
    ImGui::EndChild();
    ImGui::NextColumn();
    ImGui::BeginChild("Weapons", ImVec2(230, 200), true);
    {

    }
    ImGui::EndChild();
    ImGui::NewLine();
    ImGui::BeginChild("Other", ImVec2(230, 80), true);
    {

    }
    ImGui::EndChild();
    ImGui::NewLine();
    ImGui::BeginChild("Accuracy", ImVec2(230, 140), true);
    {

    }
    ImGui::EndChild();
    ImGui::NewLine();
    ImGui::BeginChild("Accuracy##1", ImVec2(230, 140), true);
    {

    }
    ImGui::EndChild();
}
#pragma endregion

#pragma region AntiAimTab
void AntiAimTab() {

}
#pragma endregion

#pragma region LegitBotTab
void LegitBotTab() {

}
#pragma endregion

#pragma region TriggerBotTab
void TriggerBotTab() {

}
#pragma endregion

#pragma region PlayersTab
void PlayersTab() {

}
#pragma endregion

#pragma region WorldTab
void WorldTab() {

}
#pragma endregion

#pragma region OtherTab
void OtherTab() {

}
#pragma endregion

#pragma region RadarTab
void RadarTab() {

}
#pragma endregion

#pragma region MiscTab
void MiscTab() {

}
#pragma endregion

#pragma region InventoryTab
void InventoryTab() {

}
#pragma endregion

#pragma region ProfileTab
void ProfileTab() {

}
#pragma endregion

#pragma region ScriptsTab
void ScriptsTab() {

}
#pragma endregion

#pragma region ConfigsTab
void ConfigsTab() {

}
#pragma endregion

#pragma region Decoration
void Decoration() {
    auto d = ImGui::GetWindowDrawList();
    auto p = ImGui::GetWindowPos();
    d->AddRectFilled(p, ImVec2(p.x + 700, p.y + 550), ImGui::GetColorU32(ImGuiCol_WindowBg));

    d->AddRectFilled(p, ImVec2(p.x + 160, p.y + 550), ImGui::GetColorU32(ImGuiCol_ChildBg));
    d->AddRectFilled(p, ImVec2(p.x + 700, p.y + 50), ImGui::GetColorU32(ImGuiCol_ChildBg));

    d->AddRectFilled(ImVec2(p.x + 159, p.y), ImVec2(p.x + 160, p.y + 550), ImGui::GetColorU32(ImGuiCol_FrameBg));
    d->AddRectFilled(ImVec2(p.x, p.y + 49), ImVec2(p.x + 700, p.y + 50), ImGui::GetColorU32(ImGuiCol_FrameBg));

    d->AddText(g_pBigIconsFont, 51, ImVec2(p.x + 15, p.y + 4), ImColor(77, 125, 253), "E");
    d->AddText(g_pNameFont, 18, ImVec2(p.x + ImGui::CalcTextSize("E").x * 3 + 23, p.y + (50 - ImGui::CalcTextSize("NAMECHEAT").y) / 2), ImColor(255, 255, 255), "NAMECHEAT");
}
#pragma endregion

static int tabs = 0;
static bool animation_menu = true;
static int plus = 1;
#pragma region Tabs
void Tabs() {
    ImGui::BeginGroup();
    {
        ImGui::PushFont(g_pTabsFont);
        ImGui::SetCursorPos(ImVec2(10, 69));
        ImGui::TextDisabled("Rage");
        ImGui::SetCursorPos(ImVec2(10, 150));
        ImGui::TextDisabled("Legit");
        ImGui::SetCursorPos(ImVec2(10, 230));
        ImGui::TextDisabled("Visuals");
        ImGui::SetCursorPos(ImVec2(10, 353));
        ImGui::TextDisabled("Miscellaneous");
        ImGui::PopFont();
    }
    ImGui::EndGroup();
    ImGui::SetCursorPosX(4);
    ImGui::BeginGroup();
    {
        //Rage
        {
            ImGui::SetCursorPosY(91);
            if (ImGui::Tab("R", "Ragebot", tabs == 0, ImVec2(160, 24))) {
                if (tabs != 0)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 0; 
            }
            ImGui::SetCursorPosY(115);
            if (ImGui::Tab("A", "Anti-Aim", tabs == 1, ImVec2(160, 24))) {
                if (tabs != 1)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 1;
            }
        }

        // Legit
        {
            ImGui::SetCursorPosY(172);
            if (ImGui::Tab("L", "Legitbot", tabs == 2, ImVec2(160, 24))) {
                if (tabs != 2)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 2;
            }
            ImGui::SetCursorPosY(196);
            if (ImGui::Tab("T", "Triggerbot", tabs == 3, ImVec2(160, 24))) {
                if (tabs != 3)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 3;
            }
        }
        
        // Visuals
        {
            ImGui::SetCursorPosY(249);
            if (ImGui::Tab("P", "Players", tabs == 4, ImVec2(160, 24))) {
                if (tabs != 4)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 4;
            }
            ImGui::SetCursorPosY(273);
            if (ImGui::Tab("W", "World", tabs == 5, ImVec2(160, 24))) {
                if (tabs != 5)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 5;
            }
            ImGui::SetCursorPosY(297);
            if (ImGui::Tab("O", "Other", tabs == 6, ImVec2(160, 24))) {
                if (tabs != 6)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 6;
            }
            ImGui::SetCursorPosY(321);
            if (ImGui::Tab("r", "Radar", tabs == 7, ImVec2(160, 24))) {
                if (tabs != 7)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 7;
            }
        }
        
        // Miscellaneous
        {
            ImGui::SetCursorPosY(372);
            if (ImGui::Tab("M", "Main", tabs == 8, ImVec2(160, 24))) {
                if (tabs != 8)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 8;
            }
            ImGui::SetCursorPosY(396);
            if (ImGui::Tab("I", "Inventory", tabs == 9, ImVec2(160, 24))) {
                if (tabs != 9)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 9;
            }
            ImGui::SetCursorPosY(420);
            if (ImGui::Tab("p", "Profile", tabs == 10, ImVec2(160, 24))) {
                if (tabs != 10)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 10;
            }
            ImGui::SetCursorPosY(444);
            if (ImGui::Tab("S", "Scripts", tabs == 11, ImVec2(160, 24))) {
                if (tabs != 11)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 11;
            }
            ImGui::SetCursorPosY(468);
            if (ImGui::Tab("C", "Configs", tabs == 12, ImVec2(160, 24))) {
                if (tabs != 12)
                {
                    animation_menu = true;
                    plus = 0;
                }
                tabs = 12;
            }
        }
    }
    ImGui::EndGroup();
}
#pragma endregion

static char search[64] = "";
#pragma region Search
void Search() {
    auto d = ImGui::GetWindowDrawList();
    auto p = ImGui::GetWindowPos();
    d->AddText(g_pIconsFont, 20, ImVec2(p.x + 171, p.y + 17), ImColor(77, 125, 253), "s");
    ImGui::SetCursorPos(ImVec2(197, 15));
    ImGui::PushFont(g_pMenuFont);
    ImGui::PushItemWidth(160);
    if (ImGui::InputText("Search", search, 16))
        g_Search.find = true;
    ImGui::PopItemWidth();
    ImGui::PopFont();
}
#pragma endregion

static int x, y;
#pragma region Menu
void Menu() {
    ImGui::PushFont(g_pMenuFont);
    ImGui::BeginGroup();
    {
        if (animation_menu)
        {
            plus += 10;
            if (plus >= 480)
            {
                plus = 480;
                animation_menu = false;
            }
        }
        ImGui::SetNextWindowPos(ImVec2(x + 170, y + 60));
        ImGui::SetNextWindowSize(ImVec2(520, plus));
        ImGui::Begin("##tabs", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        {
            if (g_Search.find && search[0] != '\0' && strlen(search) >= 3)
            {
                ImGui::BeginChild("Search", ImVec2(500, 460), true, ImGuiWindowFlags_NoScrollbar);
                {
                    g_Search.drawqueryresults(search);
                }
                ImGui::EndChild();
            }
            else
            {
                switch (tabs) {
                case 0:     RageBotTab();       break;
                case 1:     AntiAimTab();       break;
                case 2:     LegitBotTab();      break;
                case 3:     TriggerBotTab();    break;
                case 4:     PlayersTab();       break;
                case 5:     WorldTab();         break;
                case 6:     OtherTab();         break;
                case 7:     RadarTab();         break;
                case 8:     MiscTab();          break;
                case 9:     InventoryTab();     break;
                case 10:    ProfileTab();       break;
                case 11:    ScriptsTab();       break;
                case 12:    ConfigsTab();       break;
                }
            }
        }
        ImGui::End();
    }
    ImGui::EndGroup();
    ImGui::PopFont();
}
#pragma endregion
#pragma endregion

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX9 Example"), WS_POPUPWINDOW, 0, 0, 1440, 900, NULL, NULL, wc.hInstance, NULL);

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
	if (bgs == nullptr)
        D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, /*bg_one*/bg_two/*bg_three*/, sizeof(/*bg_one*/bg_two/*bg_three*/), 1920, 1080, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &bgs);
    if (logo == nullptr)
        D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, logotype, sizeof(logotype), 120, 120, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &logo);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    if (!g_Search.find)
        g_Search.Init();

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
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFontConfig icons_config; //icons_config.MergeMode = true; //icons_config.PixelSnapH = true;
    g_pNameFont = io.Fonts->AddFontFromMemoryTTF(MontserratExtraBold, sizeof(MontserratExtraBold), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pBigIconsFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 51, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pIconsWatermarkFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 28, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pIconsFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 20, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pTabsFont = io.Fonts->AddFontFromMemoryTTF(MontserratMedium, sizeof(MontserratMedium), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pMenuFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 16, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pLoaderFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 14, NULL, io.Fonts->GetGlyphRangesCyrillic());

    //IM_ASSERT(font != NULL);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
		
		/*		BACKGROUND		*/
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(-1, -1));
        ImGui::SetNextWindowSizeConstraints(ImVec2(w, h), ImVec2(w, h));
        ImGui::SetNextWindowPos({ 0,0 });
        ImGui::Begin("bg", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus);
        {
            auto Render = ImGui::GetWindowDrawList();
            ImVec2 p = ImGui::GetWindowPos();
            Render->AddImage(bgs, p, ImVec2(p.x + w, p.y + h));
        }
        ImGui::End();
        ImGui::PopStyleVar();
		/*		BACKGROUND		*/

        // Style
        auto& s = ImGui::GetStyle();
        s.FrameRounding = 6;
        s.ChildRounding = 10;
        s.PopupRounding = 5;
        s.ScrollbarRounding = 0;
        s.ScrollbarSize = 5;
        s.FramePadding = ImVec2(2,1);
        // Colors
        auto c = s.Colors;
        c[ImGuiCol_WindowBg] = ImColor(4, 16, 30);
        c[ImGuiCol_FrameBg] = ImColor(7, 35, 66);
        c[ImGuiCol_FrameBgHovered] = ImColor(8, 35, 65);
        c[ImGuiCol_FrameBgActive] = ImColor(77, 125, 253);
        c[ImGuiCol_Separator] = ImColor(77, 125, 253);
        c[ImGuiCol_SliderGrab] = ImColor(77, 125, 253, 200);
        c[ImGuiCol_SliderGrabActive] = ImColor(77, 125, 253);
        c[ImGuiCol_PopupBg] = ImColor(7, 35, 66);
        c[ImGuiCol_ScrollbarBg] = ImColor(4, 21, 39);
        c[ImGuiCol_ScrollbarGrab] = ImColor(77, 125, 253);
        c[ImGuiCol_ScrollbarGrabActive] = ImColor(77, 125, 253);
        c[ImGuiCol_ScrollbarGrabHovered] = ImColor(77, 125, 253, 200);
        c[ImGuiCol_Border] = ImColor();
        c[ImGuiCol_ChildBg] = ImColor(4, 21, 39);
        c[ImGuiCol_Header] = ImColor(4, 21, 39);
        c[ImGuiCol_HeaderHovered] = ImColor(77, 125, 253, 200);
        c[ImGuiCol_HeaderActive] = ImColor(77, 125, 253);
        c[ImGuiCol_Button] = ImColor(7, 35, 66);
        c[ImGuiCol_ButtonHovered] = ImColor(77, 125, 253, 200);
        c[ImGuiCol_ButtonActive] = ImColor(77, 125, 253);
        c[ImGuiCol_Text] = ImColor(255, 255, 255);
        c[ImGuiCol_TextDisabled] = ImColor(100, 118, 140);
 
        // menu
        {
            ImGui::SetNextWindowSize(ImVec2(x + 700, y + 550));
            ImGui::Begin("CheatName Menu", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
            {
                x = ImGui::GetWindowPos().x, y = ImGui::GetWindowPos().y;
                Decoration();
                Tabs();
                Search();
                Menu();
            }
            ImGui::End();
        }

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*255.0f), (int)(clear_color.y*255.0f), (int)(clear_color.z*255.0f), (int)(clear_color.w*255.0f));
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
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
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
