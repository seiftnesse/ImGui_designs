// dear imgui: standalone example application for DirectX 9
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include "Fonts.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#define IM_USE using namespace ImGui; 

static int theme = 0;
// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include "../imgui_internal.h"

ImFont* icons = nullptr;
ImFont* big = nullptr;
ImFont* bigger = nullptr;
ImFont* tab_ico = nullptr;
ImFont* weapon_icons = nullptr;
ImFont* custom_sz = nullptr;





#define ALPHA (ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar| ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoSidePreview)
#define NOALPHA (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float)



bool Tab(const char* icon, const char* label,  const ImVec2& size_arg, const bool selected)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    static float sizeplus = 0.f;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;

    ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ImGui::ItemSize(size, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

    if (hovered || held)
        ImGui::SetMouseCursor(7);

    if (selected)
        window->DrawList->AddRectFilled(bb.Min,bb.Max,ImColor(50, 50, 65));

    
    ImGui::PushFont(big);
    window->DrawList->AddText(ImVec2(bb.Min.x + 30, bb.Min.y + 34), ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), label );
    ImGui::PopFont();

   // window->DrawList->AddText(ImVec2(bb.Min.x + 35, bb.Min.y + 26), ImColor(100 / 255.f, 100 / 255.f, 100 / 255.f, 255.f / 255.f), desc);

    ImGui::PushFont(tab_ico);
    window->DrawList->AddText(ImVec2(bb.Min.x + 40, bb.Min.y + size_arg.y / 3 - ImGui::CalcTextSize(icon).y / 2), ImColor(186 / 255.f, 189 / 255.f, 225 / 255.f, 255.f / 255.f), icon);
    ImGui::PopFont();
    

    return pressed;
}


bool SubTab(const char* label, const ImVec2& size_arg, const bool selected)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    static float sizeplus = 0.f;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;

    ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ImGui::ItemSize(size, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

    if (hovered || held)
        ImGui::SetMouseCursor(7);

    if (selected)
       window->DrawList->AddRectFilled({ bb.Min.x - 40,bb.Min.y }, { bb.Max.x,bb.Max.y }, ImColor(50, 50, 65), 8.f);

    //if (selected)
      //  window->DrawList->AddRectFilled({ bb.Max.x,bb.Max.y }, { bb.Max.x - 3,bb.Min.y }, ImColor(84 / 255.f, 182 / 255.f, 225 / 255.f, 255.f / 255.f));

    ImGui::PushFont(custom_sz);
    window->DrawList->AddText(ImVec2(bb.Min.x , bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2), ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), label);
    ImGui::PopFont();


    return pressed;
}

/*void RenderCheckMar1k(ImVec2 pos, ImU32 col, float sz)
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    float thickness = ImMax(sz / 5.0f, 1.0f);
    sz -= thickness * 0.5f;
    pos = ImVec2(pos.x + thickness * 0.25f, pos.y + thickness * 0.25f);

    float third = sz / 3.0f;
    float bx = pos.x + third;
    float by = pos.y + sz - third * 0.5f;
    window->DrawList->PathLineTo(ImVec2(bx - third, by - third));
    window->DrawList->PathLineTo(ImVec2(bx, by));
    window->DrawList->PathLineTo(ImVec2(bx + third * 2, by - third * 2));
    window->DrawList->PathStroke(col, false, thickness);
}*/

bool Checkbox(const char* label, bool* v)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    const float square_sz = ImGui::GetFrameHeight();
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect total_bb(pos, ImVec2(pos.x + square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), pos.y + label_size.y + style.FramePadding.y * 2.0f));
    ImGui::ItemSize(total_bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(total_bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
    {
        *v = !(*v);
        ImGui::MarkItemEdited(id);
    }

    const ImRect check_bb(pos, ImVec2(pos.x + square_sz, pos.y + square_sz));

    float t = *v ? 1.0f : 0.0f;

    float ANIM_SPEED = 0.05f;
    if (g.LastActiveIdTimer == g.CurrentWindow->GetID(label))// && g.LastActiveIdTimer < ANIM_SPEED)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 col_bg = ImGui::GetColorU32(ImVec4(120 / 255.f, 120 / 255.f, 120 / 255.f, 120 / 255.f));
    ImU32 col_bg2;
    ImU32 col_bg3;

    col_bg2 = ImGui::GetColorU32(ImLerp(ImVec4(190 / 255.f, 190 / 255.f, 190 / 255.f, 0 / 255.f), ImVec4(5 / 255.f, 193 / 255.f, 245 / 255.f, 255.f / 255.f), t));
    col_bg3 = ImGui::GetColorU32(ImLerp(ImVec4(190 / 255.f, 190 / 255.f, 190 / 255.f, 0 / 255.f), ImVec4(255, 255, 255, 255), t));

    window->DrawList->AddRect(check_bb.Min, check_bb.Max, col_bg, 4.f, 15, 2.f);
    window->DrawList->AddRectFilled(check_bb.Min, check_bb.Max, col_bg2, 4.f);

    //if (*v)
   // {
   //    RenderCheckMar1k(ImVec2{ check_bb.Min.x + 4,check_bb.Min.y + 4 }, col_bg3, square_sz - 8);
    //}

    if (label_size.x > 0.0f)
        ImGui::RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label);

    return pressed;
}

#include <string>
#include <unordered_map>

class HotkeyListener
{
public:
    virtual void OnHotkeyPressed() = 0;
};

struct HotkeyButton
{
    HotkeyButton(UINT defaultKey, HotkeyListener* callback);

    UINT key;
    bool waitingForKey = false;
    HotkeyListener* cb;
};

static std::unordered_map<std::string, HotkeyButton> g_ExistingHotkeys;

namespace ImGui
{
    void HandleKeyPress(UINT key);

    void Hotkey(const char* id, const char* msg, UINT defaultKey, const ImVec2& size, HotkeyListener* cb);
}

HotkeyButton::HotkeyButton(UINT defaultKey, HotkeyListener* callback)
    :
    key(defaultKey),
    cb(callback)
{}

void HandleKeyPress(UINT key)
{
    for (auto& hotkey : g_ExistingHotkeys)
    {
        if (hotkey.second.waitingForKey)
        {
            hotkey.second.key = key;
            hotkey.second.waitingForKey = false;
        }
        else if (hotkey.second.key == key)
        {
            hotkey.second.cb->OnHotkeyPressed();
        }
    }
}

void Hotkey(const char* id, const char* msg, UINT defaultKey, const ImVec2& size, HotkeyListener* cb)
{
    auto pair = g_ExistingHotkeys.emplace(id, HotkeyButton{ defaultKey, cb });
    auto hotkey = pair.first;

    UINT key = hotkey->second.key;

    LONG sc = MapVirtualKey(key, 0);

    char buf[256];
    memset(buf, 0, 256);

    unsigned short int temp;
    int asc = (key <= 32) ? 1 : 0;
    if (!asc && key != VK_DIVIDE)
        asc = ToAscii(key, sc, reinterpret_cast<BYTE*>(buf), &temp, 1);

    // Set bits
    sc <<= 16;
    sc |= 0x1 << 25;  // <- don't care
    if (!asc)
        sc |= 0x1 << 24; // <- extended bit

                         // Convert to ANSI string
    if (GetKeyNameTextA(sc, buf, 256) > 0)
    {
        ImGui::Text(msg);
        ImGui::SameLine();
        if (ImGui::Button(buf, size))
        {
            hotkey->second.waitingForKey = true;
        }
    }
}

#include <ShlObj_core.h>
#include <Windows.h>
#include <filesystem>
#include <fstream>

#include <dinput.h>
#include <tchar.h>
#include <fstream>
#include <functional>
#include <string>
#include <ShlObj.h>
#include <intrin.h>
#include <Windows.h>

#include <winerror.h>

#include <strsafe.h>

#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")



// Main code
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
    ImFontConfig m_config;
    ImGuiStyle* style = &ImGui::GetStyle();


    ImGui::StyleColorsDark();

    style->Alpha = 1.f;
    
    
    
    
    
    style->WindowRounding = 12.f;
    style->FramePadding = ImVec2(4, 3);
    style->WindowPadding = ImVec2(8, 8);
    style->ItemInnerSpacing = ImVec2(4, 4);
    style->ItemSpacing = ImVec2(8, 4);
    style->FrameRounding = 4.f;
    style->ScrollbarSize = 2.f;
    style->ScrollbarRounding = 12.f;


    ImVec4* colors = ImGui::GetStyle().Colors;

    colors[ImGuiCol_ChildBg] = ImColor(24, 29, 59, 0);
    colors[ImGuiCol_Border] = ImVec4(0.07f, 0.07f, 0.11f, 0.50f);
    colors[ImGuiCol_FrameBg] = ImColor(25, 25, 33, 255);
    colors[ImGuiCol_FrameBgActive] = ImColor(25, 25, 33, 255);
    colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 33, 255);
    colors[ImGuiCol_Header] = ImColor(25, 25, 33, 255);
    colors[ImGuiCol_HeaderActive] = ImColor(28, 28, 36, 255);
    colors[ImGuiCol_HeaderHovered] = ImColor(30, 30, 38, 255);
    colors[ImGuiCol_PopupBg] = ImColor(35, 35, 45, 255);
    colors[ImGuiCol_Button] = ImColor(160, 30, 30, 255);
    colors[ImGuiCol_ButtonHovered] = ImColor(190, 45, 35, 255);
    colors[ImGuiCol_ButtonActive] = ImColor(220, 60, 40, 255);

    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Droid_compressed_data, Droid_compressed_size, 12.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    icons = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(MyFont_compressed_data1, MyFont_compressed_size1, 30.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    big = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Droid_compressed_data, Droid_compressed_size, 14.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    bigger = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Droid_compressed_data, Droid_compressed_size, 26.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    tab_ico = io.Fonts->AddFontFromMemoryTTF((void*)main_icon, sizeof(main_icon), 22.f, &m_config, io.Fonts->GetGlyphRangesCyrillic());
    weapon_icons = io.Fonts->AddFontFromMemoryTTF((void*)Cord, sizeof(Cord), 10.f, &m_config, io.Fonts->GetGlyphRangesCyrillic());
    custom_sz = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Droid_compressed_data, Droid_compressed_size, 16.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);

    // Main loop
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


        //////////////////////////////////
        static int tab = 0;        ///////////////////////////
        static int subtab = 0;     ///////////////////////////
        static bool checkboxbool = false;        ////////////////////////  TEST 
        static int sliderint = 254; //////////////////////////
        static float coloredit[3] = { 0.f,0.f,0.f }; /////////////////////
        ///////////////////////////////////

        auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 6.f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
        ImGui::SetNextWindowSize({ 720,600 });
        ImGui::Begin("##menu", nullptr, flags);
        {
            ImDrawList* draw = ImGui::GetWindowDrawList();
            ImVec2 pos = ImGui::GetWindowPos();

            draw->AddRectFilled({ pos.x ,pos.y}, { pos.x + 920,pos.y + 720 }, ImColor(50, 50, 65), 0.f, ImDrawCornerFlags_Top); //background
            draw->AddLine(ImVec2(pos.x, pos.y + 60), ImVec2(pos.x + 920, pos.y + 60), ImColor(50, 50, 65), 1.000000);
            draw->AddRectFilled({ pos.x + 149 ,pos.y + 60 }, { pos.x + 920,pos.y + 720 }, ImColor(51, 52, 65), 0.f, ImDrawCornerFlags_Top); // center background

            draw->AddLine(ImVec2(pos.x + 149, pos.y), ImVec2(pos.x + 149, pos.y + 703), ImColor(50, 50, 65), 1.000000);/// lines
            draw->AddLine(ImVec2(pos.x , pos.y + 60), ImVec2(pos.x + 920, pos.y + 60 ), ImColor(50, 50, 65), 1.000000);///
            draw->AddRectFilled({ pos.x ,pos.y + 703 }, { pos.x + 920,pos.y + 720 }, ImColor(50, 50, 65), 0.f); /// down line

            ImGui::PushFont(big);
            ImGui::SetCursorPos({ 30,20 });
            ImGui::Text("zoom-project.pw");
            //my discord x1lte#0051 add xD

            ImGui::PopFont();



            ImGui::SetCursorPos(ImVec2(10, 550));
            ImGui::BeginGroup();
            if (ImGui::RadioButton("Defult", 0 == theme))
                theme = 0;
            if (ImGui::RadioButton("Black", 1 == theme))
                theme = 1;
         

            ImVec4* colors = ImGui::GetStyle().Colors;

            if (theme == 0)
            {
                colors[ImGuiCol_ScrollbarGrab] = ImVec4(110 / 255.f, 122 / 255.f, 200 / 255.f, 1.f);
                colors[ImGuiCol_SliderGrab] = ImVec4(110 / 255.f, 122 / 255.f, 200 / 255.f, 1.f);
                colors[ImGuiCol_CheckMark] = ImVec4(255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f);

            }
            if (theme == 1)
            {
                colors[ImGuiCol_ScrollbarGrab] = ImVec4(255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f);
                colors[ImGuiCol_SliderGrab] = ImVec4(219 / 255.f, 219 / 255.f, 219 / 255.f, 1.f);
                colors[ImGuiCol_CheckMark] = ImVec4(0 / 255.f, 0 / 255.f, 0 / 255.f, 1.f);

            }

            ImGui::EndGroup();

            ImGui::SetCursorPos({ 25,75 });//расположение ебаных табов 

            ImGui::BeginGroup();
            {

                if (Tab("B", "Ragebot", ImVec2(100, 60), tab == 0 ? true : false))  //J B
                    tab = 0;
                //ImGui::SameLine();
                ImGui::Spacing();
                ImGui::Spacing();
                if (Tab("F", "LegitBot", ImVec2(100, 60), tab == 5 ? true : false))
                    tab = 5;
                //ImGui::SameLine();
                ImGui::Spacing();
                ImGui::Spacing();
                if (Tab("C", "Visuals", ImVec2(100, 60), tab == 1 ? true : false))
                    tab = 1;
                //ImGui::SameLine();
                ImGui::Spacing();
                ImGui::Spacing();
                if (Tab("D", "  Misc", ImVec2(100, 60), tab == 2 ? true : false))
                    tab = 2;
                //ImGui::SameLine();
                ImGui::Spacing();
                ImGui::Spacing();
                if (Tab("A", "Skins", ImVec2(100, 60), tab == 3 ? true : false))
                    tab = 3;
                //ImGui::SameLine();
                ImGui::Spacing();
                ImGui::Spacing();
                if (Tab("E", "Configs", ImVec2(100, 60), tab == 4 ? true : false))
                    tab = 4;

            }
            ImGui::EndGroup();

            ImGui::SetCursorPos({ 220,20 });//расположение ебаных табов для функций

            ImGui::BeginGroup();
            {
                if (tab == 0) {

                    if (SubTab("General", ImVec2(100, 25), subtab == 0 ? true : false))
                        subtab = 0;
                    ImGui::SameLine();
                    ImGui::SameLine();
                    ImGui::SameLine();
                    if (SubTab("Adaptive", ImVec2(100, 25), subtab == 1 ? true : false))
                        subtab = 1;
                    ImGui::SameLine();
                    ImGui::SameLine();
                    ImGui::SameLine();

                    if (SubTab("Anti-Aims", ImVec2(100, 25), subtab == 2 ? true : false))
                        subtab = 2;
                    ImGui::SameLine();
                    ImGui::SameLine();
                    ImGui::SameLine();
                 
                    if (SubTab("   Extra", ImVec2(100, 25), subtab == 3 ? true : false))
                        subtab = 3;
                    ImGui::SameLine();
                }

                if (tab == 5) {

                    if (SubTab("General", ImVec2(100, 25), subtab == 0 ? true : false))
                        subtab = 0;
                    ImGui::SameLine();
                    if (SubTab("Settings", ImVec2(100, 25), subtab == 1 ? true : false))
                        subtab = 1;
                    ImGui::SameLine();
                    if (SubTab("Trigger", ImVec2(100, 25), subtab == 2 ? true : false))
                        subtab = 2;

                }

                if (tab == 1) {

                    if (SubTab(" General", ImVec2(100, 25), subtab == 4 ? true : false))
                        subtab = 4;
                    ImGui::SameLine();
                    if (SubTab("   Local", ImVec2(100, 25), subtab == 5 ? true : false))
                        subtab = 5;
                    ImGui::SameLine();
                    if (SubTab("   World", ImVec2(100, 25), subtab == 6 ? true : false))
                        subtab = 6;
                    ImGui::SameLine();
                    if (SubTab("   Other", ImVec2(100, 25), subtab == 7 ? true : false))
                        subtab = 7;

                }

                if (tab == 2) {

                    if (SubTab(" General", ImVec2(100, 25), subtab == 8 ? true : false))
                        subtab = 8;
                    ImGui::SameLine();
                    if (SubTab("  Other", ImVec2(100, 25), subtab == 9 ? true : false))
                        subtab = 9;


                }

                if (tab == 3) {

                    if (SubTab("  Knifes", ImVec2(100, 25), subtab == 10 ? true : false))
                        subtab = 10;
                    ImGui::SameLine();
                    if (SubTab("  Gloves", ImVec2(100, 25), subtab == 11 ? true : false))
                        subtab = 11;
                    ImGui::SameLine();
                    if (SubTab("  Model", ImVec2(100, 25), subtab == 12 ? true : false))
                        subtab = 12;

                }

                if (tab == 4) {

                    if (SubTab("  Config", ImVec2(100, 25), subtab == 13 ? true : false))
                        subtab = 13;
                    ImGui::SameLine();
                    if (SubTab("  Lua", ImVec2(100, 25), subtab == 14 ? true : false))
                        subtab = 14;
                }


            }
            ImGui::EndGroup();

           

            ImGui::PushFont(big);
            ImGui::SetCursorPos({ 155,75 });
            ImGui::BeginGroup(); {

                if (tab == 0) {   ///////// RAGETAB

                    if (subtab == 0) {   ////////// GENERAL SUBTAB

                        Checkbox("Enable", &checkboxbool);

                        ImGui::Spacing();
                        ImGui::Spacing();












                    }
                }
            }
            ImGui::EndGroup();
            ImGui::PopFont();
        }
        ImGui::End();
        ImGui::PopStyleVar(3);

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
extern IDirect3DTexture9* logotype;

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

