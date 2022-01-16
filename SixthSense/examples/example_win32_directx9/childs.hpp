/////////////////////////////////////////////////////
//                                                   
//    Generated with QuarcStudio. (ex. ImGui Editor) 
//    QuarcStudio is designed with love by pers0na2. 
//    All rights to QuarcStudio belong to pers0na2.  
//                                                   
/////////////////////////////////////////////////////


#ifndef QUARCHILD
#define QUARCHILD

#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include <imgui_internal.h>

namespace QGUI 
{

	bool BeginChildEx(const char* name, ImGuiID id, const ImVec2 & size_arg, bool border, ImGuiWindowFlags flags)
	{
		ImGuiContext& g = *GImGui;
		ImGuiWindow* parent_window = g.CurrentWindow;

		flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;
		flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);

		const ImVec2 content_avail = ImGui::GetContentRegionAvail();
		ImVec2 size = ImFloor(size_arg);
		const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
		if (size.x <= 0.0f)
			size.x = ImMax(content_avail.x + size.x, 4.0f);
		if (size.y <= 0.0f)
			size.y = ImMax(content_avail.y + size.y, 4.0f);
		ImGui::SetNextWindowSize(size);
        ImVec2 label_size = ImGui::CalcTextSize(name);

		char title[256];
		if (name)
			ImFormatString(title, IM_ARRAYSIZE(title), "%s/%s_%08X", parent_window->Name, name, id);
		else
		ImFormatString(title, IM_ARRAYSIZE(title), "%s/%08X", parent_window->Name, id);

		const float backup_border_size = g.Style.ChildBorderSize;
		if (!border)
			g.Style.ChildBorderSize = 0.0f;
		bool ret = ImGui::Begin(title, NULL, flags);
		g.Style.ChildBorderSize = backup_border_size;

		ImGuiWindow* child_window = g.CurrentWindow;
		child_window->ChildId = id;
		child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

		if (child_window->BeginCount == 1)
			parent_window->DC.CursorPos = child_window->Pos;

		if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayerActiveMask != 0 || child_window->DC.NavHasScroll))
		{
			ImGui::FocusWindow(child_window);
			ImGui::NavInitWindow(child_window, false);
			ImGui::SetActiveID(id + 1, child_window);
			g.ActiveIdSource = ImGuiInputSource_Nav;
		}
            parent_window->DrawList->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x + 0, ImGui::GetWindowPos().y + size_arg.y - 20), ImVec2(ImGui::GetWindowPos().x + size_arg.x + 0, ImGui::GetWindowPos().y + size_arg.y + 0), ImColor(20, 21, 22, 0), ImColor(20, 21, 22, 0), ImColor(20, 21, 22, 230), ImColor(20, 21, 22, 230));
            parent_window->DrawList->AddRect(ImVec2(ImGui::GetWindowPos().x + 0, ImGui::GetWindowPos().y + 5), ImVec2(ImGui::GetWindowPos().x + size_arg.x + 0, ImGui::GetWindowPos().y + size_arg.y + 0), ImColor(92, 98, 97, 255), 0, 15, 1.000000);
            parent_window->DrawList->AddRectFilled(ImVec2(ImGui::GetWindowPos().x + 15, ImGui::GetWindowPos().y + 0), ImVec2(ImGui::GetWindowPos().x + label_size.x + 25, ImGui::GetWindowPos().y + 10), ImColor(33, 34, 35, 255), 0, 15);
            parent_window->DrawList->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x + 0, ImGui::GetWindowPos().y + 6), ImVec2(ImGui::GetWindowPos().x + size_arg.x, ImGui::GetWindowPos().y + 25), ImColor(20, 21, 22, 230), ImColor(20, 21, 22, 230), ImColor(20, 21, 22, 0), ImColor(20, 21, 22, 0));
            ImGui::RenderText(ImVec2(parent_window->DC.CursorPos.x + 20, parent_window->DC.CursorPos.y + 10 / 2 - label_size.y / 2), name);
		return ret;
	}

	bool BeginChild(const char* str_id, const ImVec2 & size_arg, bool border, ImGuiWindowFlags extra_flags)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		return BeginChildEx(str_id, window->GetID(str_id), size_arg, border, extra_flags);
	}

}

#endif
