#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>
#include <imgui_internal.h>

ImVec2 pos;
ImDrawList* draw;

ImFont* one = nullptr;
ImFont* two = nullptr;
ImFont* three = nullptr;
ImFont* four = nullptr;

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static int selected = 0;
static int sub_selected;
bool checkboxon;
bool checkbox;
int slider1;
int slider;
static const char* items[]{ "75%", "100%", "150%", "200%"};
static int combo = 1;

void MiscTab()
{
    if (selected == 2)
    {
        ImGui::SetCursorPos(ImVec2(11, 63));
        if (ImGui::Навалил_Кринжа("General", 0 == sub_selected, 310.f))
            sub_selected = 0;
        ImGui::SetCursorPos(ImVec2(320, 63));
        if (ImGui::Навалил_Кринжа("Player List", 1 == sub_selected, 310.f))
            sub_selected = 1;

        if (sub_selected == 0)
        {
            ImGui::MenuChild("General ", ImVec2(286, 473), ImVec2(29, 115));
            ImGui::Checkbox("Bunnyhop", &checkboxon);
            ImGui::SliderInt("Max Hops", &slider1, 0, 100);
            ImGui::SliderInt("Successrate", &slider, 0, 100);
            ImGui::SetCursorPosX(37);
            ImGui::Checkbox("Emulate Scrollwheel", &checkbox);
            ImGui::Checkbox("Auto Strafer", &checkboxon);
            ImGui::Checkbox("Air Duck", &checkbox);
            ImGui::Checkbox("Edgejump", &checkbox);
            ImGui::Checkbox("Jumpbug Assistant", &checkbox);
            ImGui::Checkbox("Edgebug Assistant", &checkbox);
            ImGui::Checkbox("Auto Pre-Speed", &checkboxon);
            ImGui::Checkbox("Blockbot", &checkbox);
            ImGui::Checkbox("Slidewalk", &checkbox);
            ImGui::Checkbox("Fastwalk", &checkbox);
            ImGui::Checkbox("Zeusbot", &checkbox);
            ImGui::Checkbox("Autopistol", &checkboxon);
            ImGui::Checkbox("Auto Grenade Throw", &checkbox);
            ImGui::Checkbox("Removw Duck Cooldown", &checkbox);
            ImGui::Checkbox("Knifebot", &checkboxon);
            ImGui::Checkbox("Spectator List", &checkboxon);
            ImGui::EndMenuChild();


            ImGui::MenuChild("Other ", ImVec2(286, 473), ImVec2(328, 115));
            ImGui::Checkbox("Menu Key", &checkbox);
            ImGui::Checkbox("Panic key", &checkbox);
            ImGui::Checkbox("Anti-Untrusted", &checkboxon);
            ImGui::Checkbox("Auto-Accept Matchmaking", &checkboxon);
            ImGui::Checkbox("Chat Spammer", &checkbox);
            ImGui::Checkbox("Remove name", &checkbox);
            ImGui::Checkbox("Name Stealer", &checkbox);
            ImGui::Checkbox("Animated Clantag", &checkboxon);
            ImGui::Checkbox("Custom Clantag", &checkbox);
            ImGui::Checkbox("Event Logger", &checkbox);
            ImGui::Checkbox("Autocock Revolver", &checkboxon);
            ImGui::Checkbox("Show Scoreboard Ranks", &checkboxon);
            ImGui::Checkbox("Show Scoreboard Money", &checkbox);
            ImGui::Checkbox("Preserve Killfeed", &checkboxon);
            ImGui::Checkbox("Draggable Netgraph", &checkbox);
            ImGui::Checkbox("Custom DPI", &checkboxon);
            ImGui::Combo("Custom DPI", &combo, items, IM_ARRAYSIZE(items));
            ImGui::Button("Recconect Matchmaking", ImVec2(212, 25));
            ImGui::EndMenuChild();
        }

    }

}

int main(int, char**)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX9 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

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
    ImGui::StyleColorsDark();

    one = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arialbd.ttf", 14.0f);
    two = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arialbd.ttf", 13.0f);
    three = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arialbd.ttf", 12.0f);
    four = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/arialbd.ttf", 11.0f);

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done = false;
    while (!done)
    {
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

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(641, 618));
        ImGui::Begin("interwebz v2", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration);
        {
            pos = ImGui::GetWindowPos();
            draw = ImGui::GetWindowDrawList();

            draw->AddRect(ImVec2(pos.x + 1, pos.y + 1), ImVec2(pos.x + 640, pos.y + 617), ImColor(67, 56, 82), 3.f);
            draw->AddRectFilled(ImVec2(pos.x + 10, pos.y + 30), ImVec2(pos.x + 631, pos.y + 608), ImColor(27, 17, 37), 2.f);
            draw->AddRect(ImVec2(pos.x + 10, pos.y + 30), ImVec2(pos.x + 631, pos.y + 608), ImColor(67, 56, 82), 2.f);
            draw->AddText(one, 14.f, ImVec2(pos.x + 11, pos.y + 9), ImColor(255, 255, 255), "INTERWEBZ - Counter-Strike: Global Offensive");

            ImGui::SetCursorPos(ImVec2(11, 31));
            if (ImGui::Навалил_Кринжа("Legit", 0 == selected))
                selected = 0;
            ImGui::SetCursorPos(ImVec2(135, 31));
            if (ImGui::Навалил_Кринжа("Visuals", 1 == selected))
                selected = 1;
            ImGui::SetCursorPos(ImVec2(259, 31));
            if (ImGui::Навалил_Кринжа("Misc", 2 == selected))
                selected = 2;
            ImGui::SetCursorPos(ImVec2(383, 31));
            if (ImGui::Навалил_Кринжа("Skins", 3 == selected))
                selected = 3;
            ImGui::SetCursorPos(ImVec2(507, 31));
            if (ImGui::Навалил_Кринжа("Configs", 4 == selected))
                selected = 4;

            MiscTab();
        }
        ImGui::End();

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
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


bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; 
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

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
