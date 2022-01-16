#include "custom.hpp"

extern ImFont* icon;
extern ImFont* large;
std::map<ImGuiID, float> tab_hover;

auto c_gui::tab(const char* label, ImVec2 size_arg) -> bool {
	IM_USE;
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);
    ImGuiButtonFlags flags = 0;


    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrentLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrentLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;

    if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
        flags |= ImGuiButtonFlags_Repeat;
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

    float* alpha = &tab_hover[id];

    if (*alpha >= GetStyle().Alpha) {
        *alpha = GetStyle().Alpha;
    }

    if (*alpha <= 0.f) {
        *alpha = 0.f;
    }

    if (hovered) {
        if (*alpha <= GetStyle().Alpha) {
            *alpha += ImGui::GetIO().DeltaTime * 5;
        }

    }

    if (!hovered) {
        if (*alpha > 0.f) {
            *alpha -= ImGui::GetIO().DeltaTime * 5;
        }
    }


    window->DrawList->AddRectFilled( bb.Min, bb.Max + ImVec2( 2, 0 ), GetColorU32( ImVec4( 130 / 255.f, 130 / 255.f, 130 / 255.f,  *alpha ) ) );

    PushFont( icon );
    RenderTextClipped( bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb );
    PopFont( );
    return pressed;
}

auto c_gui::text(const char* name, const char* desc, ImVec2 pos) -> void {

    ImGui::SetCursorPos( pos );
    ImGui::BeginGroup( );

    ImGui::PushFont( large );
    ImGui::TextColored( ImVec4( 1.f, 1.f, 1.f, 1.f ), name );
    ImGui::PopFont( );

    spacing( );

    ImGui::TextColored( ImVec4( 1.f, 1.f, 1.f, 0.4f ), desc );
    ImGui::EndGroup( );
}

auto c_gui::spacing() -> void {

    IM_USE;

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return;
    ItemSize(ImVec2(0, 0));

}

std::map<ImGuiID, float> toggle_pos;
auto c_gui::toggle( const char* label, bool* v ) -> bool {
    IM_USE;
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw = ImGui::GetWindowDrawList();

    float height = 13.2f;
    float width = height * 1.5f; 
    float radius = height * 0.50f;

    ImGui::InvisibleButton(label, ImVec2(width + 8.f, height));
    if (ImGui::IsItemClicked())
        *v = !*v;

    float t = *v ? 1.0f : 0.0f;

    ImGuiContext& g = *GImGui;
    float ANIM_SPEED = 0.2f;
    if (g.LastActiveId == g.CurrentWindow->GetID(label))
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }
    ItemSize(ImVec2(0, 0));

    ImU32 col_bg;
    if (ImGui::IsItemHovered())
        col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 0.0f), ImVec4(0.f, 120 / 255.f, 215 / 255.f, 1.f), t));
    else
        col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 0.0f), ImVec4(0.f, 120 / 255.f, 215 / 255.f, 1.f), t));

    draw->AddRect(p, ImVec2(p.x + width + 8.f, p.y + height + 3.f), ImGui::IsItemHovered() ? IM_COL32(255, 255, 255, 255) : IM_COL32(153, 153, 153, 255), height * 0.5f);
    draw->AddRectFilled(p, ImVec2(p.x + width + 8.f, p.y + height + 3.f), col_bg, height * 0.5f);
    draw->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 1.2f) + 2.f, p.y + radius + 1.5f), radius - 2.5f, IM_COL32(255, 255, 255, 255));

    draw->AddText(p + ImVec2(35, -2), IM_COL32( 255, 255, 255, 255 ), label);

    return true;
}
