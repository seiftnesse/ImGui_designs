/////////////////////////////////////////////////////
//                                                   
//    Generated with QuarcStudio. (ex. ImGui Editor) 
//    QuarcStudio is designed with love by pers0na2. 
//    All rights to QuarcStudio belong to pers0na2.  
//                                                   
/////////////////////////////////////////////////////


#ifndef QUARCSLIDER
#define QUARCSLIDER

#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include <imgui_internal.h>

namespace QGUI 
{

	static const char* PatchFormatStringFloatToInt(const char* fmt)
	{
		if (fmt[0] == '%' && fmt[1] == '.' && fmt[2] == '0' && fmt[3] == 'f' && fmt[4] == 0)
			return "%d";

		const char* fmt_start = ImParseFormatFindStart(fmt); 
		const char* fmt_end = ImParseFormatFindEnd(fmt_start);  
		if (fmt_end > fmt_start && fmt_end[-1] == 'f')
		{
			if (fmt_start == fmt && fmt_end[0] == 0)
				return "%d";
			ImGuiContext& g = *GImGui;
			ImFormatString(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer),"%.*s%%d%s", (int)(fmt_start - fmt), fmt, fmt_end); 
			return g.TempBuffer;
		}
		return fmt;
	}

	bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const float w = ImGui::CalcItemWidth();

		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		const ImRect frame_bb(window->DC.CursorPos + ImVec2(20,22), window->DC.CursorPos + ImVec2(w+0,32));
		const ImRect total_bb(window->DC.CursorPos, frame_bb.Max + ImVec2(0,0) + ImVec2(0.0f, 0.0f));

		ImGui::ItemSize(total_bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(total_bb, id, &frame_bb))
			return false;

		if (format == NULL)
			format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;
		else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0)
			format = PatchFormatStringFloatToInt(format);
		const bool hovered = ImGui::ItemHoverable(frame_bb, id);
		const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
		bool temp_input_is_active = temp_input_allowed && ImGui::TempInputIsActive(id);
		if (!temp_input_is_active)
		{
			const bool focus_requested = temp_input_allowed && ImGui::FocusableItemRegister(window, id);
			const bool clicked = (hovered && g.IO.MouseClicked[0]);
			if (focus_requested || clicked || g.NavActivateId == id || g.NavInputId == id)
			{
				ImGui::SetActiveID(id, window);
				ImGui::SetFocusID(id, window);
				ImGui::FocusWindow(window);
				g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
			}
		}
		if (!hovered)
		{
			window->DrawList->AddRectFilled(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 0), ImVec2(frame_bb.Max.x + 0, frame_bb.Max.y + 0), ImColor(42,43,45,255),0, 15); 
		}
		else
		{
			window->DrawList->AddRectFilled(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 0), ImVec2(frame_bb.Max.x + 0, frame_bb.Max.y + 0), ImColor(42,43,45,255),0, 15); 
		}
        
		ImRect grab_bb;
		const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, 1, &grab_bb);

		grab_bb.Min = frame_bb.Min;
		grab_bb.Min += ImVec2(0,0);
		grab_bb.Max += ImVec2(0,0);

		if (!hovered)
		{
			window->DrawList->AddRectFilled(ImVec2(grab_bb.Min.x + 3, grab_bb.Min.y + 3), ImVec2(grab_bb.Max.x + 0, grab_bb.Max.y + -1), ImColor(47,172,242,255),0, 15); 
		}
		else
		{
			window->DrawList->AddRectFilled(ImVec2(grab_bb.Min.x + 3, grab_bb.Min.y + 3), ImVec2(grab_bb.Max.x + 0, grab_bb.Max.y + -1), ImColor(47,172,242,255),0, 15); 
		}
        window->DrawList->AddCircleFilled(ImVec2(grab_bb.Max.x, frame_bb.Min.y + 5), 9, ImColor(52, 53, 51), 360);
		char value_buf[64];
		const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, 255 / 255.f));
		ImGui::RenderText(ImVec2(frame_bb.Min.x + w / 2 - ImGui::CalcTextSize(value_buf).x / 2 - 10, frame_bb.Min.y + style.FramePadding.y +12), value_buf);
		ImGui::PopStyleColor();
		if (hovered)
			ImGui::SetMouseCursor(0);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229/255.f,229/255.f,229/255.f,255/255.f));
		ImGui::RenderText(total_bb.Min, label);
		ImGui::PopStyleColor();
		return value_changed;
	}

	bool slider_float(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
	{
		return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
	}

	bool slider_int(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
	{
		return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
	}

}

#endif
