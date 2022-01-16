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
#include "hashes.h"
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

int subtab = 0;
int tab = 0;

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
    if (subtab == 0)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
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

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 1)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 2)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 3)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }
}

void AntiAim()
{
    if (subtab == 0)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 1)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 2)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 3)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }
}

void Visuals()
{
    if (subtab == 0)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 1)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 2)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 3)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }
}



void Misc()
{
    if (subtab == 0)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 1)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 2)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 3)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }
}

void Configs()
{
    if (subtab == 0)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 1)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 2)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 3)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

}

void Lua()
{
    if (subtab == 0)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 1)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 2)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }

    if (subtab == 3)
    {
        ImGui::SetCursorPos({ 115, 105 });
        ImGui::MenuChild("Main", { 350,430 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 105 });
        ImGui::MenuChild("Other", { 350,230 });
        {

        }
        ImGui::EndChild();

        ImGui::SetCursorPos({ 480, 365 });
        ImGui::MenuChild("exsploit's", { 350, 170 });
        {

        }
        ImGui::EndChild();
    }
}


void tabs()
{
    ImGui::SetCursorPos({ (float)8, (float)38 });
    ImGui::BeginGroup();
    if (ImGui::tab("A", 1 == tab))
        tab = 1;
    if (ImGui::tab("B", 2 == tab))
        tab = 2;
    if (ImGui::tab("K", 3 == tab))
        tab = 3;
    if (ImGui::tab("M", 4 == tab))
        tab = 4;
    if (ImGui::tab("Q", 5 == tab))
        tab = 5;
    if (ImGui::tab("O", 6 == tab))
        tab = 6;
    ImGui::EndGroup();

    switch (tab)
    {
    case 1: Rage(); break;
    case 2: AntiAim(); break;
    case 3: Visuals(); break;
    case 4: Misc(); break;
    case 5: Configs(); break;
    case 6: Lua(); break;
    }
    
}

void sub_tab()
{

    ImGui::SetCursorPos({ 155, 45 });
    ImGui::BeginGroup();
    if (ImGui::subtab("Weapon", 0 == subtab, ImVec2(180, 25)))
        subtab = 0;
    ImGui::SameLine();
    if (ImGui::subtab("Main", 1 == subtab, ImVec2(180, 25)))
        subtab = 1;
    ImGui::SameLine();
    if (ImGui::subtab("General", 2 == subtab, ImVec2(180, 25)))
        subtab = 2;
    ImGui::SameLine();
    if (ImGui::subtab("Other", 3 == subtab, ImVec2(180, 25)))
        subtab = 3;
    ImGui::EndGroup();
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

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    if (!g_Search.find)
        g_Search.Init();

    ImFontConfig icons_config;
    g_pNameFont = io.Fonts->AddFontFromMemoryTTF(MontserratExtraBold, sizeof(MontserratExtraBold), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pBigIconsFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 51, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pIconsWatermarkFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 28, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pIconsFont = io.Fonts->AddFontFromMemoryTTF(EvolutionIconsQunion, sizeof(EvolutionIconsQunion), 33, &icons_config, io.Fonts->GetGlyphRangesDefault());
    g_pTabsFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 14, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pLogoFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 26, NULL, io.Fonts->GetGlyphRangesCyrillic());
    g_pMenuFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 16, NULL, io.Fonts->GetGlyphRangesCyrillic());
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
            auto s = ImVec2{}, p = ImVec2{}, gs = ImVec2{ 890, 570 };
            ImGui::SetNextWindowSize(ImVec2(gs));
            if (ImGui::Begin(("Absend"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar))
            {
                s = ImVec2(ImGui::GetWindowSize().x - ImGui::GetStyle().WindowPadding.x * 2, ImGui::GetWindowSize().y - ImGui::GetStyle().WindowPadding.y * 2);
                p = ImVec2(ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x, ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y);
                auto draw = ImGui::GetWindowDrawList();

                // глав задний фон
                draw->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + 845, p.y + 550), ImColor(12, 12, 12), 1);
                //обводка под название чита
                draw->AddLine(ImVec2(p.x + 0, p.y + 30), ImVec2(p.x + 845, p.y + 30), ImColor(59, 59, 59), 1);
                //линия по середине синего цвета XD
                draw->AddRectFilledMultiColor(ImVec2(p.x + 100, p.y + 30), ImVec2(p.x + 437, p.y + 31), ImColor(59, 59, 59), ImColor(60, 104, 182), ImColor(60, 104, 182), ImColor(59, 59, 59));
                draw->AddRectFilledMultiColor(ImVec2(p.x + 437, p.y + 30), ImVec2(p.x + 745, p.y + 31), ImColor(60, 104, 182), ImColor(59, 59, 59), ImColor(59, 59, 59), ImColor(60, 104, 182));
                //задний фон
                draw->AddRectFilled(ImVec2(p.x + 7, p.y + 37), ImVec2(p.x + 85, p.y + 530), ImColor(12, 12, 12), 1);
                //линии
                draw->AddRect(ImVec2(p.x + 7, p.y + 37), ImVec2(p.x + 85, p.y + 530), ImColor(59, 59, 59), 1);

                //задний фон
                draw->AddRectFilled(ImVec2(p.x + 92, p.y + 37), ImVec2(p.x + 838, p.y + 530), ImColor(12, 12, 12), 1);
                //линии
                draw->AddRect(ImVec2(p.x + 92, p.y + 37), ImVec2(p.x + 838, p.y + 530), ImColor(59, 59, 59), 1);
                draw->AddRect(ImVec2(p.x + 92, p.y + 65), ImVec2(p.x + 838, p.y + 530), ImColor(59, 59, 59), 1);

                draw->AddRect(ImVec2(p.x, p.y), ImVec2(p.x + 845, p.y + 550), ImColor(59, 59, 59), 1);

                ImGui::PushFont(g_pinfoFont);
                draw->AddText(ImVec2(p.x + 790, p.y + 7), ImColor(60, 104, 182), comp_name().c_str());
                ImGui::PopFont();

                sub_tab();
                tabs();
                Rage();

                ImGui::PushFont(g_pinfoFont);
                std::string welcome = "Welcome back :";
                draw->AddText(ImVec2(p.x + 700, p.y + 7), ImColor(100, 100, 100), welcome.c_str());
                ImGui::PopFont();

                ImGui::PushFont(g_pLoaderFont);
                std::string version = "* developed by lycrus *";
                draw->AddText(ImVec2(p.x + 380, p.y + s.y - 22), ImColor(100, 100, 100), version.c_str());
                ImGui::PopFont();

                ImGui::PushFont(g_pMenuFont);
                std::string name = "N O T H I N G";
                draw->AddText({ p.x + 7, p.y + 8 }, ImColor(60, 104, 182), name.c_str());
                ImGui::PopFont();
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
