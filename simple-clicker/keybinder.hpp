#ifndef KEYBIND_HPP
#define KEYBIND_HPP

#include "ImGui/imgui.h"

#include <unordered_map>
#include <Windows.h>
#include <string>
#include <vector>

namespace keybind
{
	inline std::string get_key_name_by_id(int id)
	{
		static std::unordered_map< int, std::string > key_names =
		{
			{ 0,  ("None") },
			{ VK_LBUTTON,  ("Mouse 1") },
			{ VK_RBUTTON,  ("Mouse 2") },
			{ VK_MBUTTON,  ("Mouse 3") },
			{ VK_XBUTTON1, ("Mouse 4") },
			{ VK_XBUTTON2,  ("Mouse 5") },
			{ VK_BACK,  ("Back") },
			{ VK_TAB,  ("Tab") },
			{ VK_CLEAR,  ("Clear") },
			{ VK_RETURN,  ("Enter") },
			{ VK_SHIFT,   ("Shift") },
			{ VK_CONTROL,   ("Ctrl") },
			{ VK_MENU,   ("Alt") },
			{ VK_PAUSE,   ("Pause") },
			{ VK_CAPITAL,   ("Caps Lock") },
			{ VK_ESCAPE,   ("Escape") },
			{ VK_SPACE,   ("Space") },
			{ VK_PRIOR,   ("Page Up") },
			{ VK_NEXT,   ("Page Down") },
			{ VK_END,   ("End") },
			{ VK_HOME,   ("Home") },
			{ VK_LEFT,   ("Left Key") },
			{ VK_UP,  ("Up Key") },
			{ VK_RIGHT,  ("Right Key") },
			{ VK_DOWN,  ("Down Key") },
			{ VK_SELECT,  ("Select") },
			{ VK_PRINT,  ("Print Screen") },
			{ VK_INSERT,  ("Insert") },
			{ VK_DELETE,  ("Delete") },
			{ VK_HELP,  ("Help") },
			{ VK_SLEEP,  ("Sleep") },
			{ VK_MULTIPLY,  ("*") },
			{ VK_ADD,  ("+") },
			{ VK_SUBTRACT,  ("-") },
			{ VK_DECIMAL, (".") },
			{ VK_DIVIDE, ("/") },
			{ VK_NUMLOCK,  ("Num Lock") },
			{ VK_SCROLL, ("Scroll") },
			{ VK_LSHIFT,  ("Left Shift") },
			{ VK_RSHIFT,  ("Right Shift") },
			{ VK_LCONTROL,  ("Left Ctrl") },
			{ VK_RCONTROL, ("Right Ctrl") },
			{ VK_LMENU, ("Left Alt") },
			{ VK_RMENU,  ("Right Alt") },
		};

		if (id >= 0x30 && id <= 0x5A)
			return std::string(1, (char)id);

		if (id >= 0x60 && id <= 0x69)
			return  ("Num ") + std::to_string(id - 0x60);

		if (id >= 0x70 && id <= 0x87)
			return  ("F") + std::to_string((id - 0x70) + 1);

		return key_names[id];
	}

	void key_bind(int& key)
	{
		static auto b_get = false;
		static std::string sz_text = ("[Not Bound]");

		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0, 0.5f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.37f, 0.37f, 0.37f, 1.00f));
		if (ImGui::Button(sz_text.c_str(), ImVec2(70, 20)))
			b_get = true;
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor();

		if (b_get)
		{
			for (auto i = 1; i < 256; i++)
			{
				if (GetAsyncKeyState(i) & 0x8000)
				{
					if (i != 12)
					{
						key = i == VK_ESCAPE ? 0 : i;
						b_get = false;
					}
				}
			}
			sz_text = ("[...]");
		}
		else if (!b_get && key == 0)
			sz_text = ("[Not Bound]");
		else if (!b_get && key != 0)
			sz_text = ("[") + get_key_name_by_id(key) + ("]");
	}
}

#endif
