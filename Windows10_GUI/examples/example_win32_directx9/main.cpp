// dear imgui: standalone example application for DirectX 9
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include "custom.hpp"

#include "mainfont.hpp"
#include "icons.hpp"

ImFont* icon = nullptr;
ImFont* large = nullptr;
ImFont* medium = nullptr;
ImFont* arrow = nullptr;
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
int main(int, char**)
{
    // Create application window
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
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    io.Fonts->AddFontFromMemoryTTF(regular, sizeof(regular), 17.0f);
    large = io.Fonts->AddFontFromMemoryTTF(regular, sizeof(regular), 24.0f);
    medium = io.Fonts->AddFontFromMemoryTTF(regular, sizeof(regular), 22.0f);
    icon = io.Fonts->AddFontFromMemoryTTF(icons, sizeof(icons), 16.f);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
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

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::Begin( "##fluent_menu", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse); {
                // window render helpers
                auto p = ImGui::GetWindowPos( );
                auto draw = ImGui::GetWindowDrawList( );

                // tab animation
                static auto tabs = 0;
                static float move = 0.f;
                static float move_size = 0.f;
                static float tab = 0.f;
                if (move < 1.f)
                    move += 0.1f;

                // window settings
                ImGui::SetWindowSize( ImVec2( 472, 384 ) );

                // blur
                custom->blur_background( draw, g_pd3dDevice );
                // tabs
                draw->AddRectFilled( p, p + ImVec2( 40, 384 ), IM_COL32( 110, 110, 110, 120 ) );
                // background
                draw->AddRectFilled( p + ImVec2(40, 0), p + ImVec2( 472, 384 ), IM_COL32( 0, 0, 0, 255 ) );
                // title
                draw->AddRectFilled( p, p + ImVec2( 472, 30 ), IM_COL32( 0, 0, 0, 255 ) );
                // cheat name
                draw->AddText( p + ImVec2( 15, 6 ), IM_COL32( 255, 255, 255, 255 ), "Fluent" );

                // tabs
                ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 0, 0 ) );
                ImGui::SetCursorPos( ImVec2( -2,  53.5f) );
                ImGui::BeginGroup( ); // ебать говнокодил я
                if ( custom->tab( "0", ImVec2( 40, 40 ) ) )
                    tabs = 0, move = 0, move_size = 0.f;
                if ( custom->tab( "1", ImVec2( 40, 40 ) ) )
                    tabs = 1, move = 0, move_size = 0.659f;
                if ( custom->tab( "2", ImVec2( 40, 40 ) ) )
                    tabs = 2, move = 0, move_size = 0.665f * 2;
                if ( custom->tab( "3", ImVec2( 40, 40 ) ) )
                    tabs = 3, move = 0, move_size = 0.665f * 3;
                if ( custom->tab( "4", ImVec2( 40, 40 ) ) )
                    tabs = 4, move = 0, move_size = 0.668f * 4;
                if ( custom->tab( "5", ImVec2( 40, 40 ) ) )
                    tabs = 5, move = 0, move_size = 0.667f * 5;
                if ( custom->tab( "6", ImVec2( 40, 40 ) ) )
                    tabs = 6, move = 0, move_size = 0.667f * 6;

                auto size = ImLerp( tab, move_size, move );
                if ( move >= 1.f )
                    tab = move_size;

                draw->AddRectFilled( ImVec2(float(p.x + 6.5f), float(p.y + 90 + 60 * size)), ImVec2( float(p.x + 8.5f), float(p.y + 56 + 60 * size) ), IM_COL32( 0, 120, 215, 255 ) );

                ImGui::EndGroup( );
                ImGui::PopStyleVar( );

                // tabs elements
                ImGui::SetCursorPos(ImVec2(40, 30));
                ImGui::BeginChild( "##tabs", ImVec2( 429, 350 ) );
                {
                    ImGui::BeginGroup(  );
                    switch ( tabs )
                    {
                        case 0:
                        {
                            custom->text( "Ragebot", "Some description text" );

                            ImGui::SetCursorPos( ImVec2( 40, 100 ));
                            ImGui::BeginGroup( );

                            ImGui::PushFont( medium );
                            ImGui::Text( "General" );
                            ImGui::PopFont( );

                            ImGui::Text( "Test text" );
                            ImGui::EndGroup( );

                            break; 
                        }
                        
                        case 1:
                        {
                            custom->text( "Legitbot", "Some description text" );

                            ImGui::SetCursorPos( ImVec2( 40, 100 ));
                            ImGui::BeginGroup( );

                            ImGui::PushFont( medium );
                            ImGui::Text( "General" );
                            ImGui::PopFont( );

                            ImGui::Text( "Test text" );
                            ImGui::EndGroup( );

                            break; 
                        }

                        case 2:
                        {
                            static bool checkbox[2] = { false, false };
                            static int slider = 0, combo = 0;
                            static float color[4] = { 1.f, 1.f, 1.f, 1.f };
                            custom->text( "Visuals", "Set up your visual settings to see all that was\nhidden from your eyes" );

                            ImGui::SetCursorPos( ImVec2(40, 100) );
                            ImGui::BeginGroup( );

                            ImGui::PushFont( medium );
                            ImGui::Text( "General" );
                            ImGui::PopFont( );

                            ImGui::Text( "Test text" );
                            ImGui::Checkbox( "Checkbox", &checkbox[1] );
                            custom->toggle( "Toggle", &checkbox[2] );

                            ImGui::PushItemWidth( 255 );
                            ImGui::SliderInt( "Slider", &slider, 0, 180 );

                            ImGui::Combo( "Combo", &combo, "item1\0item2\0item3" );

                            ImGui::Spacing( );

                            ImGui::Button( "Button", ImVec2( 255, 25 ));

                            ImGui::ColorEdit4( "Colorpicker", color, ImGuiColorEditFlags_DisplayHex );

                            ImGui::Spacing();

                            static char textbox[32] = "textexttexttexttext";

                            ImGui::Text( "Textbox" );
                            ImGui::InputText( "##text", textbox, ARRAYSIZE( textbox ) );

                            for (int i = 0; i < 99; i++) {
                                std::string scroll = "Scrolldemo number " + std::to_string(i);
                                ImGui::Text( scroll.c_str( ) );
                            }
                            ImGui::EndGroup( );

                            break;
                        }

                        case 3:
                        {
                            custom->text("Players", "Some description text");

                            ImGui::SetCursorPos(ImVec2(40, 100));
                            ImGui::BeginGroup();

                            ImGui::PushFont(medium);
                            ImGui::Text("General");
                            ImGui::PopFont();

                            ImGui::Text("Test text");
                            ImGui::EndGroup();

                            break;
                        }

                        case 4:
                        {
                            custom->text("Other", "Some description text");

                            ImGui::SetCursorPos(ImVec2(40, 100));
                            ImGui::BeginGroup();

                            ImGui::PushFont(medium);
                            ImGui::Text("General");
                            ImGui::PopFont();

                            ImGui::Text("Test text");
                            ImGui::EndGroup();

                            break;
                        }

                        case 5:
                        {
                            custom->text("Settings", "Some description text");

                            ImGui::SetCursorPos(ImVec2(40, 100));
                            ImGui::BeginGroup();

                            ImGui::PushFont(medium);
                            ImGui::Text("General");
                            ImGui::PopFont();

                            ImGui::Text("Test text");
                            ImGui::EndGroup();

                            break;
                        }

                        case 6:
                        {
                            custom->text("Configs", "Some description text");

                            ImGui::SetCursorPos(ImVec2(40, 100));
                            ImGui::BeginGroup();

                            ImGui::PushFont(medium);
                            ImGui::Text("General");
                            ImGui::PopFont();

                            ImGui::Text("Test text");
                            ImGui::EndGroup();

                            break;
                        }

                    }
                    ImGui::EndGroup( );
                }
                ImGui::EndChild( );
            }
            ImGui::End();
        }

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
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

// Win32 message handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
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
