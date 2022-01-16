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

static int tab = 0;

ImVec2 s, p, pad;
ImDrawList* d;

static int
rage_subtab,
aa_subtab,
legit_subtab,
players_subtab,
world_subtab,
misc_subtab;

IDirect3DTexture9* bgs = nullptr;
IDirect3DTexture9* logo = nullptr;
IDirect3DTexture9* foto = nullptr;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void rage_tab()
{
    auto settings = &opt.ragebot[0];
    if (rage_subtab == 0)
    {
        ImGui::SetCursorPos(ImVec2(210, 80));
        ImGui::MenuChild("General", ImVec2(310, 300));
        {
            auto settings = &opt.ragebot[0];
            ImGui::Checkbox("Enabled", &settings->enabled);
            ImGui::Checkbox("Silent", &settings->silent);
            ImGui::Combo("Priority", &settings->priority, prioritys, IM_ARRAYSIZE(prioritys));
            ImGui::MultiCombo("Hitboxes", settings->hitbox, hitboxes, IM_ARRAYSIZE(hitboxes), settings->hitboxes);
        }
        ImGui::EndChild();
        ImGui::SetCursorPos(ImVec2(210, 405));
        ImGui::MenuChild("Fakelags", ImVec2(310, 120));
        {

        }
        ImGui::EndChild();
        ImGui::SetCursorPos(ImVec2(530, 80));
        ImGui::MenuChild("Settings", ImVec2(310, 445));
        {

        }
        ImGui::EndChild();
    }
    else if (rage_subtab == 1)
    {
        ImGui::SetCursorPos(ImVec2(210, 80));
        ImGui::MenuChild("General", ImVec2(310, 300));
        {

        }
        ImGui::EndChild();
        ImGui::SetCursorPos(ImVec2(210, 405));
        ImGui::MenuChild("Fakelags", ImVec2(310, 120));
        {
        }
        ImGui::EndChild();
        ImGui::SetCursorPos(ImVec2(530, 80));
        ImGui::MenuChild("Settings", ImVec2(310, 445));
        {
        }
        ImGui::EndChild();
      
    }
}

void tabs()
{
    ImGui::BeginGroup();
    {
        ImGui::PushFont(g_pLoaderFont);
        ImGui::SetCursorPos(ImVec2(10 + pad.x, 90));
        if (ImGui::tab("R", "Ragebot", !tab, g_pBigIconsFont, 0)) tab = 0;
        ImGui::SetCursorPos(ImVec2(10 + pad.x, 130));
        if (ImGui::tab("L", "Legitbot", tab == 1, g_pBigIconsFont, 1)) tab = 1;
        ImGui::SetCursorPos(ImVec2(10 + pad.x, 170));
        if (ImGui::tab("A", "Anti-aimbot", tab == 2, g_pBigIconsFont, 2)) tab = 2;
        d->AddLine(ImVec2(p.x + 10 + pad.x, p.y + 204), ImVec2(p.x + 195 - 12 - pad.x, p.y + 204), ImColor(70, 70, 70, 125));

        ImGui::SetCursorPos(ImVec2(10 + pad.x, 220));
        if (ImGui::tab("P", "Players", tab == 3, g_pBigIconsFont, 3)) tab = 3;
        ImGui::SetCursorPos(ImVec2(10 + pad.x, 260));
        if (ImGui::tab("W", "World", tab == 4, g_pBigIconsFont, 4)) tab = 4;

        d->AddLine(ImVec2(p.x + 10 + pad.x, p.y + 294), ImVec2(p.x + 195 - 12 - pad.x, p.y + 294), ImColor(70, 70, 70, 125));

        ImGui::SetCursorPos(ImVec2(10 + pad.x, 310));
        if (ImGui::tab("I", "Inventory", tab == 5, g_pBigIconsFont, 5)) tab = 5;
        ImGui::SetCursorPos(ImVec2(10 + pad.x, 350));
        if (ImGui::tab("M", "Miscalleous", tab == 6, g_pBigIconsFont, 6)) tab = 6;
        ImGui::SetCursorPos(ImVec2(10 + pad.x, 390));
        if (ImGui::tab("C", "Configs", tab == 7, g_pBigIconsFont, 7)) tab = 7;
        ImGui::SetCursorPos(ImVec2(10 + pad.x, 430));
        if (ImGui::tab("S", "Lua's", tab == 8, g_pBigIconsFont, 8)) tab = 8;
        ImGui::PopFont();
    }
    ImGui::EndGroup();
}

void subtabs()
{
    ImGui::BeginGroup();
    {
        d->AddLine(ImVec2(p.x + 195, p.y + 40), ImVec2(p.x + s.x, p.y + 40), ImColor(24, 24, 24));

        ImGui::SetCursorPos(ImVec2(pad.x + 205, 15));
        ImGui::BeginGroup();
        {
            switch (tab)
            {
            case 0:
                if (ImGui::subtab("General", rage_subtab == 0)) rage_subtab = 0; ImGui::SameLine();
                if (ImGui::subtab("Weapon", rage_subtab == 1)) rage_subtab = 1; ImGui::SameLine();
                break;
            case 1:
                if (ImGui::subtab("General", legit_subtab == 0)) legit_subtab = 0; ImGui::SameLine();
                if (ImGui::subtab("Weapon", legit_subtab == 1)) legit_subtab = 1; ImGui::SameLine();
                if (ImGui::subtab("Trigger", legit_subtab == 2)) legit_subtab = 2; ImGui::SameLine();
                break;
            case 2:
                break;
            case 3:
                if (ImGui::subtab("ESP", players_subtab == 0)) players_subtab = 0; ImGui::SameLine();
                if (ImGui::subtab("Chams", players_subtab == 1)) players_subtab = 1; ImGui::SameLine();
                if (ImGui::subtab("Glow", players_subtab == 2)) players_subtab = 2; ImGui::SameLine();
                break;
            case 4:
                if (ImGui::subtab("General", world_subtab == 0)) world_subtab = 0; ImGui::SameLine();
                if (ImGui::subtab("Other", world_subtab == 1)) world_subtab = 1; ImGui::SameLine();
                break;
            case 5:
                break;
            case 6:
                if (ImGui::subtab("General", misc_subtab == 0)) misc_subtab = 0; ImGui::SameLine();
                if (ImGui::subtab("Movement", misc_subtab == 1)) misc_subtab = 1; ImGui::SameLine();
                if (ImGui::subtab("Other", misc_subtab == 2)) misc_subtab = 2; ImGui::SameLine();
                break;
            case 7:
                break;
            case 8:
                break;
            }
        }
        ImGui::EndGroup();

        switch (tab)
        {
        case 0: rage_tab(); break;
        }

    }
    ImGui::EndGroup();
}

std::string comp_name()
{
    char buff[MAX_PATH];

    GetEnvironmentVariableA("USERNAME", buff, MAX_PATH);
    if (std::string(buff) == "1ns4n")
        std::string(buff) = "insane";
    return std::string(buff);
}

void decoration()
{
    {
        d->AddRectFilled(ImVec2(p.x + 196, p.y), ImVec2(p.x + s.x, p.y + s.y), ImColor(11, 11, 11), 5, ImDrawCornerFlags_Right);
        d->AddRectFilled(p, ImVec2(p.x + 193, p.y + s.y), ImColor(15, 15, 15, 225), 5, ImDrawCornerFlags_Left);
        d->AddRectFilledMultiColor(ImVec2(p.x + 193, p.y), ImVec2(p.x + 196, p.y + s.y), ImColor(10, 10, 10), ImColor(8, 8, 8), ImColor(8, 8, 8), ImColor(10, 10, 10));
        d->AddLine(ImVec2(p.x + 193, p.y), ImVec2(p.x + 193, p.y + s.y), ImColor(24, 24, 24));
    }

    {
        ImGui::PushFont(g_pIconsWatermarkFont);
        d->AddText(ImVec2(p.x + 10, p.y + 13), ImColor(77, 125, 253), "E");
        ImGui::PopFont();
        ImGui::PushFont(g_pLogoFont);
        d->AddText(ImVec2(p.x + 50, p.y + 18), ImColor(200, 200, 200), "EVOLUTION");
        ImGui::PopFont();
    }

    {
        d->AddRectFilledMultiColor(ImVec2(p.x, p.y + s.y - 54), ImVec2(p.x + 193, p.y + s.y - 6), ImColor(0, 0, 0, 25), ImColor(0, 0, 0, 25), ImColor(10, 10, 10), ImColor(10, 10, 10));
        d->AddRectFilled(ImVec2(p.x, p.y + s.y - 50), ImVec2(p.x + 193, p.y + s.y), ImColor(16, 16, 16), 5, ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotLeft);
        d->AddCircleFilled(ImVec2(p.x + 25, p.y + s.y - 25), 22, ImColor(31, 31, 31));

        d->AddCircleFilled(ImVec2(p.x + 40, p.y + s.y - 10), 7, ImColor(0, 255, 31, 25));
        d->AddCircleFilled(ImVec2(p.x + 40, p.y + s.y - 10), 6, ImColor(0, 0, 0, 125));
        d->AddCircleFilled(ImVec2(p.x + 40, p.y + s.y - 10), 5, ImColor(0, 255, 31));

        ImGui::PushFont(g_pLoaderFont);
        d->AddText(ImVec2(p.x + 50, p.y + s.y - 37), ImColor(200, 200, 200), comp_name().c_str());
        ImGui::PopFont();

        ImGui::PushFont(g_pLoaderFont);
        std::string text = "Expires 14.07.2031";
        d->AddText(ImVec2(p.x + 50, p.y + s.y - 23), ImColor(160, 160, 160), text.c_str());
        ImGui::PopFont();
    }

}

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
    g_pBigIconsFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 28, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pIconsWatermarkFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 45, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pIconsFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 28, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pTabsFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 14, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pLogoFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 26, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pMenuFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pLoaderFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 12, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pinfoFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 13, NULL, io.Fonts->GetGlyphRangesCyrillic());

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
            ImGui::SetNextWindowSize(ImVec2(860, 540));
            ImGui::Begin("##main_menu", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse);
            {
                pad = ImGui::GetStyle().WindowPadding;
                p = ImVec2(ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x, ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y);
                s = ImVec2(ImGui::GetWindowSize().x - ImGui::GetStyle().WindowPadding.x * 2, ImGui::GetWindowSize().y - ImGui::GetStyle().WindowPadding.y * 2);
                d = ImGui::GetWindowDrawList();

                decoration();
                tabs();
                subtabs();
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
