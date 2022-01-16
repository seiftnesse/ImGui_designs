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
#include <string>

#include "Gilroy-Medium.h"
#include "Gilroy-Regular.h"
#include "Gilroy-Semibold.h"
#include "InfinityIcons-Regular.h"
#include "logo.h"

IDirect3DTexture9* logotype = nullptr;

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};
// Fonts
ImFont* g_NameFont;
ImFont* g_TabsFont;
ImFont* g_MenuFont;
ImFont* g_IconsFont;
// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static int l_tabs = 0;
static int v_tabs = 0;
static int m_tabs = 0;
static int s_tabs = 0;
#pragma region TabsRender
#pragma region AimbotTab
void AimbotTab() {
    if (l_tabs == 0) {
        ImGui::BeginChild("General", ImVec2(280, 390), true);
        {
            static bool e, d;
            static int s, c, b;
            const char* i[] = { "1", "2", "3" };
            ImGui::Checkbox("Enabled Checkbox", &e);
            ImGui::Checkbox("Disabled Checkbox", &d);
            ImGui::SliderInt("Slider", &s, 1, 50);
            ImGui::Combo("Combo", &c, i, IM_ARRAYSIZE(i));
            ImGui::Bind("Bind", &b, ImVec2(90, 25));
        }
        ImGui::EndChild();
        ImGui::SameLine(0, 15);
        ImGui::BeginChild("Settings", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
    }
    else if (l_tabs == 1) {
        ImGui::BeginChild("General", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
        ImGui::SameLine(0, 15);
        ImGui::BeginChild("Settings", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
    }
}
#pragma endregion

#pragma region VisualsTab
void VisualsTab() {
    if (v_tabs == 0) {
        ImGui::BeginChild("General", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
        ImGui::SameLine(0, 15);
        ImGui::BeginChild("Players", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
    }
    else if (v_tabs == 1) {
        ImGui::BeginChild("Players", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
        ImGui::SameLine(0, 15);
        ImGui::BeginChild("Other", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
    }
    else if (v_tabs == 2) {
        ImGui::BeginChild("General", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
        ImGui::SameLine(0, 15);
        ImGui::BeginChild("Players", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
    }
    else if (v_tabs == 3) {
        ImGui::BeginChild("General", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
        ImGui::SameLine(0, 15);
        ImGui::BeginChild("Other", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
    }
}
#pragma endregion

#pragma region MiscTab
void MiscTab() {
    if (m_tabs == 0) {
        ImGui::BeginChild("General", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
        ImGui::SameLine(0, 15);
        ImGui::BeginChild("Other", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
    }
    else if (m_tabs == 1) {
        ImGui::BeginChild("General", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
        ImGui::SameLine(0, 15);
        ImGui::BeginChild("Other", ImVec2(280, 390), true);
        {

        }
        ImGui::EndChild();
    }
}
#pragma endregion

#pragma region SkinsTab
void SkinsTab() {

}
#pragma endregion

#pragma region ColorsTab
void ColorsTab() {

}
#pragma endregion

#pragma region ConfigsTab
void ConfigsTab() {

}
#pragma endregion
#pragma endregion

#pragma region MenuRender
#pragma region Decoration
void Decoration() {
    auto& s = ImGui::GetStyle();
    auto d = ImGui::GetWindowDrawList();
    auto p = ImGui::GetWindowPos();
    d->AddRectFilled(p, ImVec2(p.x + 750, p.y + 450), ImGui::GetColorU32(ImGuiCol_WindowBg), s.WindowRounding);
    d->AddRectFilled(p, ImVec2(p.x + 150, p.y + 450), ImGui::GetColorU32(ImGuiCol_ChildBg), s.WindowRounding, ImDrawCornerFlags_Left);

    d->AddImage(logotype, ImVec2(p.x + 40, p.y + 20), ImVec2(p.x + 110, p.y + 90));
    d->AddText(g_NameFont, 14.f, ImVec2(p.x + (150 - ImGui::CalcTextSize("INFINITY").x) / 2, p.y + 73), ImGui::GetColorU32(ImGuiCol_Text), "INFINITY");
}
#pragma endregion

#pragma region Tabs
static int tabs = 0;
void Tabs() {
    auto w = ImGui::GetWindowWidth();
    auto h = ImGui::GetWindowHeight();
    ImGui::SetCursorPos(ImVec2(w - w, h - 325));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::BeginGroup();
    {
        if (ImGui::Tab("A", "Aimbot", tabs == 0, ImVec2(150, 40)))
            tabs = 0;
        if (ImGui::Tab("V", "Visuals", tabs == 1, ImVec2(150, 40)))
            tabs = 1;
        if (ImGui::Tab("M", "Misc", tabs == 2, ImVec2(150, 40)))
            tabs = 2;
        if (ImGui::Tab("S", "Skins", tabs == 3, ImVec2(150, 40)))
            tabs = 3;
        if (ImGui::Tab("C", "Colors", tabs == 4, ImVec2(150, 40)))
            tabs = 4;
        if (ImGui::Tab("c", "Configs", tabs == 5, ImVec2(150, 40)))
            tabs = 5;
    }
    ImGui::EndGroup();
    ImGui::PopStyleVar();
}
#pragma endregion

#pragma region SubTabs
void SubTabs() {
    auto w = ImGui::GetWindowWidth();
    auto h = ImGui::GetWindowHeight();
    ImGui::SetCursorPos(ImVec2(w - 600, h - h));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::BeginGroup();
    {
        switch (tabs) {
        case 0:
            if (ImGui::SubTab("Legit", l_tabs == 0, ImVec2(110, 40)))
                l_tabs = 0;
            ImGui::SameLine(0, 0);
            if (ImGui::SubTab("Trigger", l_tabs == 1, ImVec2(110, 40)))
                l_tabs = 1;
            break;
        case 1:
            if (ImGui::SubTab("ESP", v_tabs == 0, ImVec2(110, 40)))
                v_tabs = 0;
            ImGui::SameLine(0, 0);
            if (ImGui::SubTab("Chams", v_tabs == 1, ImVec2(110, 40)))
                v_tabs = 1;
            ImGui::SameLine(0, 0);
            if (ImGui::SubTab("Glow", v_tabs == 2, ImVec2(110, 40)))
                v_tabs = 2;
            ImGui::SameLine(0, 0);
            if (ImGui::SubTab("Other", v_tabs == 3, ImVec2(110, 40)))
                v_tabs = 3;
            break;
        case 2:
            if (ImGui::SubTab("General", m_tabs == 0, ImVec2(110, 40)))
                m_tabs = 0;
            ImGui::SameLine(0, 0);
            if (ImGui::SubTab("Other", m_tabs == 1, ImVec2(110, 40)))
                m_tabs = 1;
            break;
        case 3:
            if (ImGui::SubTab("Skins", s_tabs == 0, ImVec2(110, 40)))
                s_tabs = 0;
            ImGui::SameLine(0, 0);
            if (ImGui::SubTab("Profile", s_tabs == 1, ImVec2(110, 40)))
                s_tabs = 1;
            break;
        }
    }
    ImGui::EndGroup();
    ImGui::PopStyleVar();
}
#pragma endregion

#pragma region Main
void Main() {
    auto w = ImGui::GetWindowWidth();
    auto h = ImGui::GetWindowHeight();
    ImGui::SetCursorPos(ImVec2(w - 590, h - 400));
    ImGui::PushFont(g_MenuFont);
    ImGui::BeginGroup();
    {
        switch (tabs)
        {
        case 0:     AimbotTab();        break;
        case 1:     VisualsTab();       break;
        case 2:     MiscTab();          break;
        case 3:     SkinsTab();         break;
        case 4:     ColorsTab();        break;
        case 5:     ConfigsTab();       break;
        }
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
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX9 Example"), WS_OVERLAPPEDWINDOW, 0, 0, 1440, 900, NULL, NULL, wc.hInstance, NULL);

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
    if (logotype == nullptr)
        D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, logo, sizeof(logo), 512, 512, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &logotype);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    g_NameFont = io.Fonts->AddFontFromMemoryTTF(GilroySemibold, sizeof(GilroySemibold), 14.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_IconsFont = io.Fonts->AddFontFromMemoryTTF(InfinityIconsRegular, sizeof(InfinityIconsRegular), 35.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_TabsFont = io.Fonts->AddFontFromMemoryTTF(GilroyMedium, sizeof(GilroyMedium), 14.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_MenuFont = io.Fonts->AddFontFromMemoryTTF(GilroyRegular, sizeof(GilroyRegular), 14.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

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

        //styles
        ImGuiStyle& s = ImGui::GetStyle();
        s.FrameRounding = 15.f;
        s.WindowRounding = 25.f;
        s.ChildRounding = 15.f;
        s.ScrollbarRounding = 5.f;
        s.PopupRounding = 10.f;
        s.ScrollbarSize = 4.f;
        s.FramePadding = ImVec2(3,2);

        //colors
        auto c = s.Colors;
        c[ImGuiCol_WindowBg] = ImColor(33, 36, 41);
        c[ImGuiCol_FrameBg] = ImColor(38, 41, 46);
        c[ImGuiCol_FrameBgHovered] = ImColor(255, 90, 90, 200);
        c[ImGuiCol_FrameBgActive] = ImColor(255, 90, 90);
        c[ImGuiCol_Separator] = ImColor(255, 90, 90);
        c[ImGuiCol_PopupBg] = ImColor(33, 36, 41);
        c[ImGuiCol_ScrollbarBg] = ImColor(38, 41, 46);
        c[ImGuiCol_ScrollbarGrab] = ImColor(255, 90, 90, 150);
        c[ImGuiCol_ScrollbarGrabActive] = ImColor(255, 90, 90, 200);
        c[ImGuiCol_ScrollbarGrabHovered] = ImColor(255, 90, 90);
        c[ImGuiCol_Border] = ImColor();
        c[ImGuiCol_ChildBg] = ImColor(43, 46, 51);
        c[ImGuiCol_Header] = ImColor(38, 41, 46);
        c[ImGuiCol_HeaderHovered] = ImColor(255, 90, 90, 200);
        c[ImGuiCol_HeaderActive] = ImColor(255, 90, 90);
        c[ImGuiCol_Button] = ImColor(38, 41, 46);
        c[ImGuiCol_ButtonHovered] = ImColor(255, 90, 90, 200);
        c[ImGuiCol_ButtonActive] = ImColor(255, 90, 90);
        c[ImGuiCol_Text] = ImColor(255, 255, 255);
        c[ImGuiCol_TextDisabled] = ImColor(95, 98, 103);
        // menu
        {
            ImGui::SetNextWindowSize(ImVec2(750, 450));
            ImGui::Begin("INFINITY", nullptr, ImGuiWindowFlags_NoDecoration);
            {
                Decoration();
                Tabs();
                SubTabs();
                Main();
            }
            ImGui::End();
        }

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA(180, 180, 180, 255);
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
