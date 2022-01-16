/////////////////////////////////////////////////////
//                                                   
//    Generated with QuarcStudio. (ex. ImGui Editor) 
//    QuarcStudio is designed with love by pers0na2. 
//    All rights to QuarcStudio belong to pers0na2.  
//                                                   
/////////////////////////////////////////////////////


#ifndef QUARCCHECKBOX
#define QUARCCHECKBOX

#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include <imgui_internal.h>

namespace QGUI 
{

	bool checkbox(const char* label, bool* v)
	{
		IM_USE;
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		const float square_sz = ImGui::GetFrameHeight();
		const ImVec2 pos = window->DC.CursorPos;
		const ImRect check_bb(pos + ImVec2(20, 0), pos + ImVec2(square_sz + (style.ItemInnerSpacing.x + label_size.x+0),15+0 + 0));
		const ImRect total_bb(pos, check_bb.Max);
		ItemSize(total_bb, style.FramePadding.y);
		ItemAdd(total_bb, id);

		bool hovered, held;
		bool pressed = ButtonBehavior(check_bb, id, &hovered, &held);

		if (hovered || held)
			ImGui::SetMouseCursor(0);

		if (pressed)
			*v = !(*v);


		if (*v)
		{
				window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(check_bb.Min.x + 15, total_bb.Min.y + 15), ImColor(20,21,22,0),0, 15);
			window->DrawList->AddRect(ImVec2(check_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(check_bb.Min.x + 15, total_bb.Min.y + 15), ImColor(74,74,74,255),0, 15, 1.000000);
 		ImGui::RenderCheckMark(window->DrawList, check_bb.Min + ImVec2(4, 3), ImColor(47, 170, 243), 7);
		}
		else
		{
				window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(check_bb.Min.x + 15, total_bb.Min.y + 15), ImColor(20,21,22,0),0, 15);
			window->DrawList->AddRect(ImVec2(check_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(check_bb.Min.x + 15, total_bb.Min.y + 15), ImColor(74,74,74,255),0, 15, 1.000000);
 		}

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229/ 255.f , 229/ 255.f ,229/ 255.f ,255/ 255.f ));
		ImGui::RenderText(ImVec2(check_bb.Min.x + style.ItemInnerSpacing.x +  20, total_bb.Min.y + style.FramePadding.y + -3), label);
		ImGui::PopStyleColor();
		return pressed;
	}

}

#endif
