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

ImFont* g_pTabsFont;
ImFont* g_pNameFont;
ImFont* g_pMenuFont;
ImFont* g_pLogoFont;
ImFont* g_pLoaderFont;
ImFont* g_pIconsFont;
ImFont* g_pIconsWatermarkFont;
ImFont* g_pBigIconsFont;
ImFont* g_pinfoFont;

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

IDirect3DTexture9* bgs = nullptr;
IDirect3DTexture9* logo = nullptr;
IDirect3DTexture9* foto = nullptr;

static int tab;
static int Rage_Tab;
static int Anti_Tab;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::string comp_name()
{
    char buff[MAX_PATH];
    GetEnvironmentVariableA("USERNAME", buff, MAX_PATH);
    if (std::string(buff) == "wansis")
        std::string(buff) = "w2n515";
    return std::string(buff);
}

void Rage()
{
    ImGui::SetCursorPos(ImVec2(200, 110));
    ImGui::MenuChild("Some function", ImVec2(335, 200));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(200, 340));
    ImGui::MenuChild("listboxe's", ImVec2(335, 290));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 110));
    ImGui::MenuChild("Here combo's", ImVec2(335, 280));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 420));
    ImGui::MenuChild("multi", ImVec2(335, 210));
    {
    }
    ImGui::EndChild();
}

void AntiAim()
{
    ImGui::SetCursorPos(ImVec2(200, 110));
    ImGui::MenuChild("Some function", ImVec2(335, 200));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(200, 340));
    ImGui::MenuChild("listboxe's", ImVec2(335, 290));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 110));
    ImGui::MenuChild("Here combo's", ImVec2(335, 280));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 420));
    ImGui::MenuChild("multi", ImVec2(335, 210));
    {
    }
    ImGui::EndChild();
}

void Visuals()
{
    ImGui::SetCursorPos(ImVec2(200, 110));
    ImGui::MenuChild("Some function", ImVec2(335, 200));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(200, 340));
    ImGui::MenuChild("listboxe's", ImVec2(335, 290));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 110));
    ImGui::MenuChild("Here combo's", ImVec2(335, 280));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 420));
    ImGui::MenuChild("multi", ImVec2(335, 210));
    {
    }
    ImGui::EndChild();
}

void Players()
{
    ImGui::SetCursorPos(ImVec2(200, 110));
    ImGui::MenuChild("Some function", ImVec2(335, 200));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(200, 340));
    ImGui::MenuChild("listboxe's", ImVec2(335, 290));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 110));
    ImGui::MenuChild("Here combo's", ImVec2(335, 280));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 420));
    ImGui::MenuChild("multi", ImVec2(335, 210));
    {
    }
    ImGui::EndChild();
}

void Misc()
{
    ImGui::SetCursorPos(ImVec2(200, 110));
    ImGui::MenuChild("Some function", ImVec2(335, 200));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(200, 340));
    ImGui::MenuChild("listboxe's", ImVec2(335, 290));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 110));
    ImGui::MenuChild("Here combo's", ImVec2(335, 280));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 420));
    ImGui::MenuChild("multi", ImVec2(335, 210));
    {
    }
    ImGui::EndChild();
}

void Configs()
{
    ImGui::SetCursorPos(ImVec2(200, 110));
    ImGui::MenuChild("Some function", ImVec2(335, 200));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(200, 340));
    ImGui::MenuChild("listboxe's", ImVec2(335, 290));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 110));
    ImGui::MenuChild("Here combo's", ImVec2(335, 280));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 420));
    ImGui::MenuChild("multi", ImVec2(335, 210));
    {
    }
    ImGui::EndChild();
}

void Lua()
{
    ImGui::SetCursorPos(ImVec2(200, 110));
    ImGui::MenuChild("Some function", ImVec2(335, 200));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(200, 340));
    ImGui::MenuChild("listboxe's", ImVec2(335, 290));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 110));
    ImGui::MenuChild("Here combo's", ImVec2(335, 280));
    {
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(560, 420));
    ImGui::MenuChild("multi", ImVec2(335, 210));
    {
    }
    ImGui::EndChild();
}


void tabs()
{
    ImVec2 pos = ImGui::GetCurrentWindow()->DC.CursorPos;
    ImVec2 size = { 160, 30 };

    ImGui::BeginGroup();
    {
        //RAGE
        ImGui::PushFont(g_pMenuFont);
        ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x + 208, pos.y + 47), ImColor(255, 255, 255), "RAGE");
        ImGui::PopFont();

        ImGui::SetCursorPos(ImVec2{ 200, 15 });
        ImGui::PushFont(g_pIconsFont);
        if (ImGui::tab("A", "", !tab)) tab = 0;

        //ANTI AIM
        ImGui::PushFont(g_pMenuFont);
        ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x + 267, pos.y + 47), ImColor(255, 255, 255), "ANTI AIM");
        ImGui::PopFont();

        ImGui::SetCursorPos(ImVec2{ 270, 15 });
        if (ImGui::tab("B", "", tab == 1)) tab = 1;

        //PLAYER
        ImGui::PushFont(g_pMenuFont);
        ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x + 341, pos.y + 47), ImColor(255, 255, 255), "PLAYER");
        ImGui::PopFont();

        ImGui::SetCursorPos(ImVec2{ 340, 15 });
        if (ImGui::tab("K", "", tab == 2)) tab = 2;

        //VISUAL
        ImGui::PushFont(g_pMenuFont);
        ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x + 414, pos.y + 47), ImColor(255, 255, 255), "VISUAL");
        ImGui::PopFont();

        ImGui::SetCursorPos(ImVec2{ 410, 15 });
        if (ImGui::tab("M", "", tab == 3)) tab = 3;

        //MISC
        ImGui::PushFont(g_pMenuFont);
        ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x + 489, pos.y + 47), ImColor(255, 255, 255), "MISC");
        ImGui::PopFont();

        ImGui::SetCursorPos(ImVec2{ 480, 15 });
        if (ImGui::tab("J", "", tab == 4)) tab = 4;

        //CONFIG
        ImGui::PushFont(g_pMenuFont);
        ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x + 551, pos.y + 47), ImColor(255, 255, 255), "CONFIG");
        ImGui::PopFont();

        ImGui::SetCursorPos(ImVec2{ 550, 15 });
        if (ImGui::tab("Q", "", tab == 5)) tab = 5;

        //LUA
        ImGui::PushFont(g_pMenuFont);
        ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x + 633, pos.y + 47), ImColor(255, 255, 255), "LUA");
        ImGui::PopFont();

        ImGui::SetCursorPos(ImVec2{ 620, 15 });
        if (ImGui::tab("O", "", tab == 6)) tab = 6;
        ImGui::PopFont();
    }
    ImGui::EndGroup();

    switch (tab)
    {
       case 0: Rage(); break;
       case 1: AntiAim(); break;
       case 2: Visuals(); break;
       case 3: Players(); break;
       case 4: Misc(); break;
       case 5: Configs(); break;
       case 6: Lua(); break;
    }
}

void subtab()
{
        if (tab == 0)
        {
            ImGui::SetCursorPos(ImVec2{ 27, 100 });
            ImGui::BeginChild("##Main", ImVec2{ 160, 125 }, false);
            {
                ImGui::SetCursorPos(ImVec2{ 5, 5 });
                if (ImGui::subTab("General", ImVec2(150, 25), Rage_Tab == 1 ? true : false))
                    Rage_Tab = 1;

                ImGui::SetCursorPos(ImVec2{ 5, 35 });
                if (ImGui::subTab("Weapons", ImVec2(150, 25), Rage_Tab == 2 ? true : false))
                    Rage_Tab = 2;
                ImGui::SetCursorPos(ImVec2{ 5, 65 });
                if (ImGui::subTab("Fake Lag", ImVec2(150, 25), Rage_Tab == 3 ? true : false))
                    Rage_Tab = 3;

                ImGui::SetCursorPos(ImVec2{ 5, 95 });
                if (ImGui::subTab("Player list", ImVec2(150, 25), Rage_Tab == 4 ? true : false))
                    Rage_Tab = 4;
            }
            ImGui::EndChild();
        }
        else if (tab == 1)
        {
            ImGui::SetCursorPos(ImVec2{ 25, 100 });
            ImGui::BeginChild("##Main", ImVec2{ 160, 95 }, false);
            {
                ImGui::SetCursorPos(ImVec2{ 5, 5 });
                if (ImGui::subTab("General", ImVec2(150, 25), Anti_Tab == 1 ? true : false))
                    Anti_Tab = 1;

                ImGui::SetCursorPos(ImVec2{ 5, 35 });
                if (ImGui::subTab("Exploits", ImVec2(150, 25), Anti_Tab == 2 ? true : false))
                    Anti_Tab = 2;

                ImGui::SetCursorPos(ImVec2{ 5, 65 });
                if (ImGui::subTab("Other", ImVec2(150, 25), Anti_Tab == 3 ? true : false))
                    Anti_Tab = 3;
            }
            ImGui::EndChild();
        }
};

int main(int, char**)
{

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX9 Example"), WS_POPUPWINDOW, 0, 0, 1440, 900, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    if (bgs == nullptr)
        D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, bg_two, sizeof(bg_two), 1920, 1080, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &bgs);
    if (logo == nullptr)
        D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, logotype, sizeof(logotype), 200, 200, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &logo);
    if (foto == nullptr)
        D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, fototype, sizeof(fototype), 200, 200, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &foto);

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    if (!g_Search.find)
        g_Search.Init();

    ImFontConfig icons_config;
    g_pNameFont = io.Fonts->AddFontFromMemoryTTF(MontserratExtraBold, sizeof(MontserratExtraBold), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pBigIconsFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 51, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pIconsWatermarkFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 28, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pIconsFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 28, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pTabsFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 14, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pLogoFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 35, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pMenuFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 14, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pLoaderFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 12, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pinfoFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 14, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ImGui::GetIO().FontIcons = g_pIconsFont;
    ImGui::GetIO().Font = g_pLoaderFont;
    ImGui::GetIO().Water = g_pIconsFont;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

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

        {
            auto s = ImVec2{}, p = ImVec2{}, gs = ImVec2{ 916, 646 };
            ImGui::SetNextWindowSize(ImVec2(gs));
            if (ImGui::Begin(("Absend"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar))
            {
                s = ImVec2(ImGui::GetWindowSize().x - ImGui::GetStyle().WindowPadding.x * 2, ImGui::GetWindowSize().y - ImGui::GetStyle().WindowPadding.y * 2);
                p = ImVec2(ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x, ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y);
                auto draw = ImGui::GetWindowDrawList();

                float dpi_scale = 1.f;

                draw->AddRectFilled(ImVec2(p.x + 10, p.y), ImVec2(p.x + 900, p.y + 630), ImColor(18, 18, 18), 8);

                {
                    tabs();
                    subtab();
                }

                {
                    ImGui::SetCursorPos(ImVec2(25, 10));
                    ImGui::Image(logo, ImVec2(ImVec2(110.f * dpi_scale * 1.4f, 35.f * dpi_scale * 1.9f)));
                }

                draw->AddRectFilled(ImVec2(p.x + 20, p.y + 90), ImVec2(p.x + 180, p.y + 220), ImColor(12, 12, 12), 8);

                draw->AddRectFilled(ImVec2(p.x + 10, p.y), ImVec2(p.x + 900, p.y + 70), ImColor(12, 12, 12), 8);

                draw->AddCircleFilled(ImVec2(p.x + 860, p.y + 35), 25, ImColor(105, 125, 203));
                {
                    ImGui::PushFont(g_pinfoFont);
                    draw->AddText(ImVec2(p.x + 765, p.y + 20), ImColor(200, 200, 200), comp_name().c_str());
                    ImGui::PopFont();

                    ImGui::PushFont(g_pinfoFont);
                    std::string Expires = "Version : Alpha";
                    draw->AddText(ImVec2(p.x + 700, p.y + 40), ImColor(200, 200, 200), Expires.c_str());
                    ImGui::PopFont();

                    ImGui::PushFont(g_pinfoFont);
                    std::string welcome = "Welcome :";
                    draw->AddText(ImVec2(p.x + 700, p.y + 20), ImColor(200, 200, 200), welcome.c_str());
                    ImGui::PopFont();
                }
     
                draw->AddRectFilledMultiColor(ImVec2(p.x + 10, p.y + 70), ImVec2(p.x + 900, p.y + 71), ImColor(12, 12, 12), ImColor(12, 12, 12), ImColor(12, 12, 12), ImColor(12, 12, 12));
                draw->AddRectFilledMultiColor(ImVec2(p.x + 10, p.y + 72), ImVec2(p.x + 900, p.y + 74), ImColor(15, 15, 15), ImColor(15, 15, 15), ImColor(15, 15, 15), ImColor(15, 15, 15));
            }
            ImGui::End();
        }

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
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
