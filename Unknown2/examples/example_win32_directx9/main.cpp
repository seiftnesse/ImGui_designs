// dear imgui: standalone example application for DirectX 9
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.

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
#include "aqua-menu-bg.h"

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};
IDirect3DTexture9* aquabgmenu = nullptr;
ImFont* g_pTabsFont;
ImFont* g_pMenuFont;
// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX9 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

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
    //ImGui::StyleColorsClassic();
    if (aquabgmenu == nullptr)
        D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, aqua_menu_bg, sizeof(aqua_menu_bg), 780, 470, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &aquabgmenu);
    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    g_pTabsFont = io.Fonts->AddFontFromFileTTF("../../misc/fonts/Montserrat-SemiBold_0.ttf", 17.f);
    g_pMenuFont = io.Fonts->AddFontFromFileTTF("../../misc/fonts/Montserrat-Medium_2.ttf", 17.f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    auto clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);

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
        ImGuiStyle& style = ImGui::GetStyle();
        style.FrameRounding = 10.f;
        style.ChildBorderSize = 1.f;
        style.ScrollbarSize = 1.5f;
        style.ScrollbarRounding = 5.f;
        style.PopupRounding = 5.f;
        //colors
        auto colors = style.Colors;
        colors[ImGuiCol_FrameBg] = ImColor(30, 30, 30);
        colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40);
        colors[ImGuiCol_FrameBgActive] = ImColor(85, 129, 241);
        colors[ImGuiCol_Separator] = ImColor(85, 129, 241);
        colors[ImGuiCol_SliderGrab] = ImColor(85, 129, 241);
        colors[ImGuiCol_SliderGrabActive] = ImColor(85, 129, 241);
        colors[ImGuiCol_PopupBg] = ImColor(30, 30, 30);
        colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
        colors[ImGuiCol_ScrollbarGrab] = ImColor(85, 129, 241);
        colors[ImGuiCol_ScrollbarGrabActive] = ImColor(85, 129, 241);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(85, 129, 241, 200);
        colors[ImGuiCol_Border] = ImColor(40, 40, 50);
        colors[ImGuiCol_ChildBg] = ImColor(40, 40, 50);
        colors[ImGuiCol_Header] = ImColor(40, 40, 40);
        colors[ImGuiCol_HeaderHovered] = ImColor(85, 129, 241, 200);
        colors[ImGuiCol_HeaderActive] = ImColor(85, 129, 241);
        colors[ImGuiCol_Button] = ImColor(35, 36, 44);
        colors[ImGuiCol_ButtonHovered] = ImColor(85, 129, 241, 200);
        colors[ImGuiCol_ButtonActive] = ImColor(85, 129, 241);
        colors[ImGuiCol_Text] = ImColor(255, 255, 255);
        //menu
        {
            ImGui::SetNextWindowSize(ImVec2(780, 470));
            ImGui::Begin("menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            {
                static int tabs = 0;
                auto d = ImGui::GetWindowDrawList();
                auto p = ImGui::GetWindowPos();
                d->AddImage(aquabgmenu, p, ImVec2(p.x + 780, p.y + 470));
                ImGui::BeginGroup();
                {
                    if (ImGui::ButtonActive("Legit", tabs == 0, ImVec2(121, 35)))
                        tabs = 0;
                    ImGui::SameLine();
                    if (ImGui::ButtonActive("Visuals", tabs == 1, ImVec2(120, 35)))
                        tabs = 1;
                    ImGui::SameLine();
                    if (ImGui::ButtonActive("Misc", tabs == 2, ImVec2(121, 35)))
                        tabs = 2;
                    ImGui::SameLine();
                    if (ImGui::ButtonActive("Changers", tabs == 3, ImVec2(120, 35)))
                        tabs = 3;
                    ImGui::SameLine();
                    if (ImGui::ButtonActive("Colors", tabs == 4, ImVec2(121, 35)))
                        tabs = 4;
                    ImGui::SameLine();
                    if (ImGui::ButtonActive("Configs", tabs == 5, ImVec2(120, 35)))
                        tabs = 5;
                }
                ImGui::EndGroup();
                ImGui::BeginGroup();
                {
                    ImGui::PushFont(g_pMenuFont);
                    static int legit_tabs = 0;
                    static int sliderint = 0;
                    static float sliderfloat = 0.f;
                    static int combo = 0;
                    static bool checkbox = 0;
                    static char* combos[] = {"Test", "Test1"};
                    switch (tabs)
                    {
                    case 0:
                        ImGui::BeginGroup();
                        {
                            if (ImGui::SubTab("General", legit_tabs == 0, ImVec2(150, 35)))
                                legit_tabs = 0;
                            if (ImGui::SubTab("Trigger", legit_tabs == 1, ImVec2(150, 35)))
                                legit_tabs = 1;
                            if (ImGui::SubTab("Other", legit_tabs == 2, ImVec2(150, 35)))
                                legit_tabs = 2;
                        }
                        ImGui::EndGroup();
                        ImGui::SameLine();
                        ImGui::BeginGroup();
                        {
                            switch (legit_tabs)
                            {
                            case 0:
                                ImGui::Columns(2, nullptr, false);
                                ImGui::Checkbox("Checkbox", &checkbox);
                                ImGui::SliderInt("Slider Int", &sliderint, 0, 20, "%d");
                                ImGui::NextColumn();
                                ImGui::SliderFloat("Slider Float", &sliderfloat, 0.f, 20.f, "%.1f");
                                ImGui::Combo("Combo", &combo, combos, IM_ARRAYSIZE(combos));

                                break;
                            case 1:
                                break;
                            case 2:
                                break;
                            }
                        }
                        ImGui::EndGroup();
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    }
                    ImGui::PopFont();
                }
                ImGui::EndGroup();
                
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
