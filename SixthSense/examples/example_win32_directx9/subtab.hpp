/////////////////////////////////////////////////////
//                                                   
//    Generated with QuarcStudio. (ex. ImGui Editor) 
//    QuarcStudio is designed with love by pers0na2. 
//    All rights to QuarcStudio belong to pers0na2.  
//                                                   
/////////////////////////////////////////////////////


#ifndef QUARCSUBTAB
#define QUARCSUBTAB

#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include <imgui_internal.h>

namespace QGUI 
{

	bool subtab(const char* label, bool selected)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({400,33}, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		if (hovered || held)
			ImGui::SetMouseCursor(0);

		if (selected)
		{
            window->DrawList->AddRectFilled(ImVec2(bb.Min.x + 0, bb.Max.y - 3), ImVec2(bb.Max.x + 0, bb.Max.y + 0), ImColor(47, 172, 242, 255), 0, 15);
		}
		else
		{
			if (!hovered)
			{
                window->DrawList->AddRectFilled(ImVec2(bb.Min.x + 0, bb.Max.y - 3), ImVec2(bb.Max.x + 0, bb.Max.y + 0), ImColor(67, 66, 66, 255), 0, 15);
			}
			else
			{
                window->DrawList->AddRectFilled(ImVec2(bb.Min.x + 0, bb.Max.y - 3), ImVec2(bb.Max.x + 0, bb.Max.y + 0), ImColor(67, 66, 66, 255), 0, 15);
			}
		}


		if(selected)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229/ 255.f , 229/ 255.f ,229/ 255.f ,255/ 255.f ));
			ImGui::RenderText(ImVec2(bb.Min.x + 0 + (size.x / 2 - label_size.x / 2), bb.Min.y + size.y / 2 - label_size.y / 2), label); 
			ImGui::PopStyleColor();
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229/ 255.f , 229/ 255.f ,229/ 255.f ,255/ 255.f ));
            ImGui::RenderText(ImVec2(bb.Min.x + 0 + (size.x / 2 - label_size.x / 2), bb.Min.y + size.y / 2 - label_size.y / 2), label);
			ImGui::PopStyleColor();
		}

		return pressed;
	}

}

#endif
