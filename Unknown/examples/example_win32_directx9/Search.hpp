#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <imgui.h>
#include "options.hpp"
class searchfunc {
private:
    void initialize() {
        {
            auto settings = &opt.ragebot[0];
            AddCheckbox("Enabled##r>g", &settings->enabled, "Ragebot > General");
            AddCheckbox("Silent##r>g", &settings->silent, "Ragebot > General");
            AddSliderFloat("Fov##r>g", &settings->fov, 0.f, 180.f, "%.5f", "Ragebot > General");
            AddCombo("Priority##r>g", &settings->priority, prioritys, IM_ARRAYSIZE(prioritys), "Ragebot > General");
            AddMultiCombo("Hitboxes##r>g", settings->hitbox, hitboxes, IM_ARRAYSIZE(hitboxes), settings->hitboxes, "Ragebot > General");
            AddBind("Double Tap##r>g", &settings->double_tap, ImVec2(80, 20), "Ragebot > General");
            AddBind("Hide Shots##r>g", &settings->hide_shots, ImVec2(80, 20), "Ragebot > General");
        }
        {
            static bool enabled;
            AddCheckbox("Enabled##a>g", &enabled, "Anti-Aim > General");
        }
    }

public:
    bool find = false;
    void Init() {
        initialize();
    }

    void AddCheckbox(const std::string& label, bool* value_ptr, const std::string& category) {
        checkbox_.push_back(std::make_tuple(label, value_ptr, category));
    }

    void AddSliderInt(const std::string& label, int* value_ptr, int min_value, int max_value, const std::string& format, const std::string& category) {
        slider_int_.push_back(std::make_tuple(label, value_ptr, min_value, max_value, format, category));
    }

    void AddSliderFloat(const std::string& label, float* value_ptr, float min_value, float max_value, const std::string& format, const std::string& category) {
        slider_float_.push_back(std::make_tuple(label, value_ptr, min_value, max_value, format, category));
    }

    void AddCombo(const std::string& label, int* current_item, const char* const items[], int items_count, const std::string& category) {
        combo_.push_back(std::make_tuple(label, current_item, items, items_count, category));
    }

    void AddMultiCombo(const std::string& label, int current_item, const char* items[], int items_count, bool combos[], const std::string& category) {
        multi_combo_.push_back(std::make_tuple(label, current_item, items, items_count, combos, category));
    }

    void AddBind(const std::string& label, int* key, const ImVec2 size, const std::string& category) {
        bind_.push_back(std::make_tuple(label, key, size, category));
    }

    bool findquery(const std::string& query, const std::string& str) {
        return std::search(str.begin(), str.end(), query.begin(), query.end(),
            [](char lhs, char rhs) { return std::toupper(lhs) == std::toupper(rhs); }) != str.end();
    }

    void drawqueryresults(const std::string& query) {

        for (const auto& checkbox_args : checkbox_) {
            if (findquery(query, std::get<0>(checkbox_args))) {
                ImGui::Text(std::get<2>(checkbox_args).c_str());
                ImGui::Separator();
                ImGui::Checkbox(std::get<0>(checkbox_args).c_str(), std::get<1>(checkbox_args));
                ImGui::NewLine();
            }
        }

        for (const auto& slider_int_args : slider_int_) {
            if (findquery(query, std::get<0>(slider_int_args))) {
                ImGui::Text(std::get<5>(slider_int_args).c_str());
                ImGui::Separator();
                ImGui::SliderInt(std::get<0>(slider_int_args).c_str(), std::get<1>(slider_int_args), std::get<2>(slider_int_args), std::get<3>(slider_int_args), std::get<4>(slider_int_args).c_str());
                ImGui::NewLine();
            }
        }

        for (const auto& slider_float_args : slider_float_) {
            if (findquery(query, std::get<0>(slider_float_args))) {
                ImGui::Text(std::get<5>(slider_float_args).c_str());
                ImGui::Separator();
                ImGui::SliderFloat(std::get<0>(slider_float_args).c_str(), std::get<1>(slider_float_args), std::get<2>(slider_float_args), std::get<3>(slider_float_args), std::get<4>(slider_float_args).c_str());
                ImGui::NewLine();
            }
        }

        for (const auto& combo_args : combo_) {
            if (findquery(query, std::get<0>(combo_args))) {
                ImGui::Text(std::get<4>(combo_args).c_str());
                ImGui::Separator();
                ImGui::Combo(std::get<0>(combo_args).c_str(), std::get<1>(combo_args), std::get<2>(combo_args), std::get<3>(combo_args));
                ImGui::NewLine();
            }
        }

        for (const auto& multi_combo_args : multi_combo_) {
            if (findquery(query, std::get<0>(multi_combo_args))) {
                ImGui::Text(std::get<5>(multi_combo_args).c_str());
                ImGui::Separator();
                ImGui::MultiCombo(std::get<0>(multi_combo_args).c_str(), std::get<1>(multi_combo_args), std::get<2>(multi_combo_args), std::get<3>(multi_combo_args), std::get<4>(multi_combo_args));
                ImGui::NewLine();
            }
        }

        for (const auto& bind_args : bind_) {
            if (findquery(query, std::get<0>(bind_args))) {
                ImGui::Text(std::get<3>(bind_args).c_str());
                ImGui::Separator();
                ImGui::Bind(std::get<0>(bind_args).c_str(), std::get<1>(bind_args), std::get<2>(bind_args));
                ImGui::NewLine();
            }
        }
    }

private:
    std::vector<std::tuple<std::string, bool*, std::string>> checkbox_;
    std::vector<std::tuple<std::string, int*, int, int, std::string, std::string>> slider_int_;
    std::vector<std::tuple<std::string, float*, float, float, std::string, std::string>> slider_float_;
    std::vector<std::tuple<std::string, int*, const char* const*, int, std::string>> combo_;
    std::vector<std::tuple<std::string, int, const char**, int, bool*, std::string>> multi_combo_;
    std::vector<std::tuple<std::string, int*, const ImVec2, std::string>> bind_;

};

extern searchfunc g_Search;
searchfunc g_Search;