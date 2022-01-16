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
ImFont* font;
ImFont* fontbig;
#define random_f (float a, float b) rand() % (b - a + 1) + a;

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
    draw->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + 169 - 2, p.y + s.y), ImColor(47, 47, 47, int(180 * al)), 6, ImDrawFlags_RoundCornersLeft);
    draw->AddRect(ImVec2(p.x, p.y), ImVec2(p.x + 169 + 2, p.y + s.y), ImColor(47, 47, 47, int(205 * al)), 6, ImDrawFlags_RoundCornersLeft);
    draw->AddLine(ImVec2(p.x + 25, p.y + 49), ImVec2(p.x + 146, p.y + 49), ImColor(47, 47, 47, int(100 * al)));
    draw->AddRectFilledMultiColor(ImVec2(p.x + 169 - 2, p.y), ImVec2(p.x + 169 + 2, p.y + s.y), ImColor(47, 47, 47, int(180 * al)), ImColor(32, 31, 33, int(255 * al)), ImColor(32, 31, 33, int(255 * al)), ImColor(47, 47, 47, int(180 * al)));
    draw->AddRectFilled(ImVec2(p.x + 169 + 2, p.y), ImVec2(p.x + s.x, p.y + s.y), ImColor(32, 31, 33, int(255 * al)), 6, ImDrawFlags_RoundCornersRight);

}
void decoration2(float al, ImVec2 p, ImVec2 s, ImFont* icons, LPDIRECT3DTEXTURE9 logo)
{
    auto draw = ImGui::GetWindowDrawList();
    al *= 1.2;
    al = ImClamp(al, 0.f, 1.f);
    draw->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + s.x, p.y + s.y), ImColor(47, 47, 47, int(180 * al)), 6);
    draw->AddRectFilled(ImVec2(p.x + 5, p.y + 5), ImVec2(p.x + s.x - 5, p.y + s.y - 5), ImColor(32, 31, 33, int(255 * al)), 6);

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

const char* test_combo_items[] =
{
    "Selectable 1",
    "Selectable 2",
    "Selectable 3"
};

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
    LPDIRECT3DTEXTURE9 logo1 = nullptr;
    if (logo1 == nullptr) {
        D3DXCreateTextureFromFileInMemory(g_pd3dDevice, &logo, sizeof(logo), &logo1);
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
    ImFont* name = io.Fonts->AddFontFromFileTTF("../../misc/fonts/Museo Sans Cyrl 700.ttf", 24.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFont* isis = io.Fonts->AddFontFromFileTTF("../../misc/fonts/MuseoSansCyrl_1.otf", 16.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFont* icon_font = io.Fonts->AddFontFromMemoryTTF((void*)Icons, sizeof(Icons), 18, &font_config, io.Fonts->GetGlyphRangesDefault());

    ImFont* weapon_icons = io.Fonts->AddFontFromMemoryTTF((void*)weapons_font, sizeof(weapons_font), 18, &font_config, io.Fonts->GetGlyphRangesDefault());
    ImFont* font_desc = io.Fonts->AddFontFromFileTTF("../../misc/fonts/Museo Sans Cyrl 700.ttf", 13.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    font = io.Fonts->AddFontFromFileTTF("../../misc/fonts/MuseoSansCyrl_1.otf", 13.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    fontbig = io.Fonts->AddFontFromFileTTF("../../misc/fonts/MuseoSansCyrl_1.otf", 15.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

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
        bool colortheme = true;

        ImGuiStyle* style = &ImGui::GetStyle();

        if (colortheme == true)
            ImGui::StyleColorsDark();
        else
            ImGui::StyleColorsLight();

        ImGui::Begin("##fluent_menu", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse); {
            // window render helpers
            auto p = ImGui::GetWindowPos();
            auto draw = ImGui::GetWindowDrawList();
            auto s = ImGui::GetWindowSize();
            static int last_tab = tab;
            static int sub_tab;
            bool testcheckbox;
            int testslider;
            int testcombo = 1;
            int weapon;


            ImGui::SetWindowSize(ImVec2(680, 470));
            draw->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + 177, p.y + s.y), ImColor(0, 0, 0, 220), 6);
            draw->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + 177, p.y + 40), ImColor(17, 16, 17, 255), 6);
            draw->AddLine(ImVec2(p.x + 0, p.y + 432), ImVec2(p.x + 177, p.y + 432), ImColor(50, 50, 50, 255), 1);
            draw->AddRectFilled(ImVec2(p.x, p.y + 432), ImVec2(p.x + 177, p.y + 470), ImColor(17, 16, 17, 255), 6);

            draw->AddCircleFilled(ImVec2(p.x + 27, p.y + 452), 10.f, ImColor(255, 255, 255));
            draw->AddLine(ImVec2(p.x, p.y + 40), ImVec2(p.x + 176, p.y + 40), ImColor(223, 98, 24, 255), 2);
            draw->AddImage(logo1, ImVec2(p.x + 70, p.y + 7), ImVec2(p.x + 110, p.y + 32));
            ImGui::PushFont(fontbig);
            draw->AddText(ImVec2(p.x + 50, p.y + 444), ImColor(255, 255, 255), "devoloper");
            ImGui::PopFont();
            ImGui::SetCursorPosY(50);
            ImGui::BeginGroup();
            {
                ImGui::PushFont(icon_font);
                if (ImGui::tab("A", "Ragebot", !tab, true)) tab = 0;
                if (tab == 0)
                {
                    ImGui::BeginGroup();
                    {
                        if (ImGui::subtab("Aimbot", sub_tab == 0)) sub_tab = 0;
                        if (ImGui::subtab("Exploits", sub_tab == 1)) sub_tab = 1;
                        if (ImGui::subtab("Anti-aim", sub_tab == 2)) sub_tab = 2;
                        if (ImGui::subtab("Misc", sub_tab == 3)) sub_tab = 3;
                    }
                    ImGui::EndGroup();
                }
                if (ImGui::tab("B", "Legitbot", tab == 1, true)) tab = 1;
                if (ImGui::tab("C", "Visuals", tab == 2, true)) tab = 2;
                if (ImGui::tab("D", "Misc", tab == 3, false)) tab = 3;
                if (ImGui::tab("E", "Skins", tab == 4, false)) tab = 4;
                if (ImGui::tab("F", "Scripts", tab == 5, false)) tab = 5;
                if (ImGui::tab("G", "Configs", tab == 6, false)) tab = 6;
                ImGui::PopFont();
            }
            ImGui::EndGroup();
            ImGui::PushFont(font);
            ImGui::PopFont();
            ImGui::SetCursorPos(ImVec2(185, 0));
            ImGui::BeginChild("##Main", ImVec2(600, 470));
            {
                draw->AddLine(ImVec2(p.x + 185, p.y + 40), ImVec2(p.x + s.x, p.y + 40), ImColor(223, 98, 24, 255), 2);
                ImGui::SetCursorPos(ImVec2(12, 50));
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(21, 20, 21)));
                ImGui::BeginChild("##weaponsTAB", ImVec2(467, 47));
                {
                    ImGui::PushFont(weapon_icons);
                    //bomb y
                    ImGui::SetCursorPosX(10);
                    ImGui::SetCursorPosY(7);

                    ImGui::BeginGroup();
                    {
                        if (ImGui::weapon("X", weapon == 0, 58, 1, 1))weapon = 0; ImGui::SameLine();
                        if (ImGui::weapon("Y", weapon == 1, 58, 1, 1))weapon = 1; ImGui::SameLine();
                        if (ImGui::weapon("a", weapon == 2, 58, 1, 1))weapon = 2; ImGui::SameLine();
                        if (ImGui::weapon("Z", weapon == 3, 58, 1, 1))weapon = 3; ImGui::SameLine(); 
                        if (ImGui::weapon("S", weapon == 4, 58, 1, 1))weapon = 4; ImGui::SameLine();
                        if (ImGui::weapon("G", weapon == 5, 58, 1, 1))weapon = 5; ImGui::SameLine();
                        if (ImGui::weapon("A", weapon == 6, 58, 1, 1))weapon = 6; ImGui::SameLine();
                    }
                    ImGui::EndGroup();
                    ImGui::PopFont();
                }
                ImGui::EndChild();
                ImGui::SetCursorPos({ 12, 135 });
                style->ChildRounding = 0.f;
                style->ChildBorderSize = 0.f;
                ImGui::MenuChild("General", ImVec2(230, 348 - 12 - 13));
                {
                    ImGui::PushFont(font);
                    ImGui::Checkbox("Test checkbox", &testcheckbox);
                    ImGui::SliderInt("Test slider", &testslider, 0, 100);
                    ImGui::Combo("Test combo", &testcombo, test_combo_items, 3);
                    ImGui::PopFont();
                }
                ImGui::EndMenuChild();
                ImGui::SetCursorPos({ 250, 135 });
                ImGui::MenuChild("Weapons", ImVec2(230, 348 - 12 - 13));
                {

                }
                ImGui::EndMenuChild();
                ImGui::PopStyleColor();
            }
            ImGui::EndChild();
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
