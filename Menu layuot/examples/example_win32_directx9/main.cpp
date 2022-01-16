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
int tab = 0;
#include <math.h>
#include "Header.h"
#include "bgs.h"
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

bool gui_key(const char* key_code)
{
    static bool return_me = false;
    ImGui::SameLine(ImGui::GetWindowSize().x - (ImGui::CalcTextSize(key_code).x + 12));
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0,0,0,0));
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
    if (ImGui::Button(key_code, ImVec2(ImGui::CalcTextSize(key_code).x + 4, ImGui::CalcTextSize(key_code).y + 2)))return_me = true;
    ImGui::PopStyleColor(3);
    return return_me;
}
#include "imgui_internal.h"
float DEG2RAD(float x)
{
    return x * (3.141592 / 180.0f); 
}


void draw_peek()
{
    for (int i = 0; i < 15; i++)
    {
        ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(100, 100), 0 + i * 5, ImColor(130, 132, 170, 150 / ImMax(1,i)), 88);
    }
}
#include <map>
ImColor calc_alpha_for_layer(int r, int g, int b, float alpha, int layer)
{
    return ImColor(r, g, b, int(min(alpha * layer, 1) * 255));
}

ImColor calc_alpha_for_layer(float r, float g, float b, float alpha, int layer)
{
    return ImColor(r, g, b, min(alpha * layer, 1));
}

void decoration(float al, ImVec2 p, ImVec2 s, ImFont* icons, LPDIRECT3DTEXTURE9 logo)
{
    auto draw = ImGui::GetWindowDrawList();
    al *= 1.2;
    al = ImClamp(al, 0.f, 1.f);
    int a = int(al * 255);
    draw->AddRectFilled(ImVec2(p.x + 50, p.y + 40), ImVec2(p.x + s.x, p.y + s.y), ImColor(10, 10, 10, a), 4, ImDrawCornerFlags_::ImDrawCornerFlags_BotRight);
    draw->AddRectFilled(ImVec2(p.x + 50, p.y), ImVec2(p.x + s.x, p.y + 40), ImColor(21, 21, 21, a), 4, ImDrawCornerFlags_::ImDrawCornerFlags_TopRight);
    draw->AddRectFilled(ImVec2(p.x, p.y + 40), ImVec2(p.x + 50, p.y + s.y), ImColor(21, 21, 21, a), 4, ImDrawCornerFlags_::ImDrawCornerFlags_BotLeft);
    draw->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + 50, p.y + 40), ImColor(24, 24, 24, a), 4, ImDrawCornerFlags_::ImDrawCornerFlags_TopLeft);
}

void DrawCircleTimer(int x, int y, int size, float amount_full, ImColor fill, int thi)
{
    std::vector<ImVec2> vertexes;
    for (int i = 0; i < 180; i++) {
        float angle = ((float)i / -180) * (3.14115 * (2 * amount_full));
        vertexes.push_back(ImVec2(x + (size * sin(angle)), y + (size * cos(angle))));
    }
    ImGui::GetOverlayDrawList()->AddPolyline(vertexes.data(), vertexes.size(), fill, ImDrawFlags_None, thi);
}

float inverse_smoothstep(float x) {
    return 0.5 - sin(asin(1.0 - 2.0 * x) / 3.0);
}
float clip(float n, float lower, float upper)
{
    n = (n > lower) * n + !(n > lower) * lower;
    return (n < upper) * n + !(n < upper) * upper;
}
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
    LPDIRECT3DTEXTURE9 bg = nullptr;
    if (bg == nullptr) {
        D3DXCreateTextureFromFileInMemory(g_pd3dDevice, &bg_one, sizeof(bg_one), &bg);
    }
    LPDIRECT3DTEXTURE9 agent = nullptr;
    if (agent == nullptr) {
        D3DXCreateTextureFromFileInMemory(g_pd3dDevice, &bg_two, sizeof(bg_two), &agent);
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
    ImFont* name = io.Fonts->AddFontFromFileTTF("../../misc/fonts/MuseoSansCyrl_1.otf", 28.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFont* isis = io.Fonts->AddFontFromFileTTF("../../misc/fonts/MuseoSansCyrl_1.otf", 16.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFont* icon_font = io.Fonts->AddFontFromMemoryTTF((void*)Icons, sizeof(Icons), 18, &font_config, io.Fonts->GetGlyphRangesDefault());
    ImFont* weapon_icons = io.Fonts->AddFontFromMemoryTTF((void*)weapons_font, sizeof(weapons_font), 18, &font_config, io.Fonts->GetGlyphRangesDefault());
    ImFont* font_desc = io.Fonts->AddFontFromFileTTF("../../misc/fonts/Museo Sans Cyrl 700.ttf", 13.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFont* font = io.Fonts->AddFontFromFileTTF("../../misc/fonts/MuseoSansCyrl_2.otf", 14.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ImFont* GuiIcons = io.Fonts->AddFontFromFileTTF("../../misc/fonts/GuiIcons.ttf", 14.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.66f, 0.65f, 0.67f, 1.00f);
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
       
        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(-1, -1));
        ImGui::SetNextWindowSizeConstraints(ImVec2(w, h), ImVec2(w, h));
        ImGui::SetNextWindowPos({ 0,0 });
        ImGui::Begin("bg", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_::ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
        {
            auto Render = ImGui::GetWindowDrawList();
            ImVec2 p = ImGui::GetWindowPos();
            Render->AddImage(bg, p, ImVec2(p.x + w, p.y + h));
        }
        ImGui::End();
        ImGui::PopStyleVar();
        static auto alpha2 = 1.0f;
        static auto switch_alpha = false;

        if (alpha2 <= 0.0f || alpha2 >= 1.0f)
            switch_alpha = !switch_alpha;

        alpha2 += switch_alpha ? 0.05f : -0.05f;
        alpha2 = ImClamp(alpha2, 0.0f, 1.0f);
        static int sl = 0;
        static int sl2 = 0;
        ImVec2 p, s, pos;
        static auto alpha = 0.01f;
        if (GetKeyState(VK_INSERT) && alpha < 1.f)
            alpha += 0.05f;
        else if (!GetKeyState(VK_INSERT) && alpha > 0.f)
            alpha -= 0.05f;
        ImGui::GetIO().Font = isis;
        ImGui::GetIO().FontIcons = icon_font;
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
        ImGui::SetNextWindowSizeConstraints(ImVec2(800, 596), ImVec2(1800 , 1596));
        ImGui::Begin("##GUI", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground);
        {
            auto l = ImGui::GetStyle().WindowPadding;
            static int last_tab = tab;
            pos = ImGui::GetWindowPos();
            auto al = ImGui::GetStyle().Alpha;
            auto draw = ImGui::GetWindowDrawList(); p = ImVec2(ImGui::GetWindowPos().x+ l.x, ImGui::GetWindowPos().y + l.y), s = ImVec2(ImGui::GetWindowSize().x- l.x * 2, ImGui::GetWindowSize().y- l.y * 2);
            decoration(al, p, s, name, lg);
            auto pad = ImGui::GetStyle().WindowPadding;
            auto deltatime = ImGui::GetIO().DeltaTime * 75.f;
            int tab_height = (s.x / 2) - 40;
            int tab_width = (s.y) - 65;
            ImGui::SetCursorPos(ImVec2(pad.x, 40 + pad.y));
            ImGui::BeginGroup();
            {
                ImGui::PushFont(icon_font);
                if (ImGui::tab("A", "Ragebot", tab == 0, 0)) { tab = 0; }
                if (ImGui::tab("H", "Legitbot", tab == 1, 0)) { tab = 1; }
                if (ImGui::tab("B", "Antiaim", tab == 2, 0)) { tab = 2; }
                if (ImGui::tab("M", "Players", tab == 3, 0)) { tab = 3; }
                if (ImGui::tab("K", "Visuals", tab == 4, 0)) { tab = 4; }
                if (ImGui::tab("C", "Inventory", tab == 5, 0)) { tab = 5; }
                if (ImGui::tab("D", "Misc", tab == 6, 0)) { tab = 6; }
                if (ImGui::tab("Q", "Configs", tab == 7, 0)) { tab = 7; }
                if (ImGui::tab("O", "Scripts", tab == 8, 0)) { tab = 8; }
                if (ImGui::tab("I", "Cheat", tab == 9, 0)) { tab = 9; }
                ImGui::PopFont();
            }
            ImGui::EndGroup();
            ImGui::PushFont(font);
            ImGui::SetCursorPos(ImVec2(60 + l.x, 60 + l.y));
            ImGui::MenuChild("Main", ImVec2((tab_height), tab_width));
            {
                static bool check[5];
                ImGui::Checkbox("Enable", &check[0]);
                ImGui::Checkbox("Backtracking", &check[1]);
                ImGui::Checkbox("Auto-fire", &check[2]);
                ImGui::Checkbox("Auto-Stope", &check[3]);
                ImGui::Checkbox("Ne pridumal", &check[4]);
                static int slider[5];
                ImGui::SliderInt("Slider", &slider[0], 0, 100);
                const char* combo[] = { "Off", "Static" ,"LBY", "No police", "BEZ BAB", "AUE", "I am GAY" }; static int aaaaa = 0;
                ImGui::Combo("Type", &aaaaa, combo, IM_ARRAYSIZE(combo));
                static char buf[24] = { 0 };
                ImGui::InputText("Text", buf, IM_ARRAYSIZE(buf));
            }
            ImGui::EndMenuChild();

            ImGui::SetCursorPos(ImVec2(tab_height + l.x + 70, 60 + l.y));
            ImGui::MenuChild("Accuracy", ImVec2((tab_height), tab_width));
            {

            }
            ImGui::EndMenuChild();

            ImGui::PopFont();
           
        }   
        ImGui::End();
        ImGui::PopStyleVar();
    

        ImGui::SetNextWindowSize(ImVec2(720, 500));
        ImGui::Begin("13123123132", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground);
        {
            auto l = ImGui::GetStyle().WindowPadding;
            auto al = ImGui::GetStyle().Alpha;
            auto draw = ImGui::GetWindowDrawList(); p = ImVec2(ImGui::GetWindowPos().x + l.x, ImGui::GetWindowPos().y + l.y), s = ImVec2(ImGui::GetWindowSize().x - l.x * 2, ImGui::GetWindowSize().y - l.y * 2);
            draw->AddImage(agent, ImVec2(p), ImVec2(p.x + s.x, p.y + s.y));
        }
        ImGui::End();

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
