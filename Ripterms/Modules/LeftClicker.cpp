#include "Modules.h"
#include "../GUI/GUI.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

void Ripterms::Modules::LeftClicker::LC()
{
	static CTimer timer(std::chrono::milliseconds(1000 / min_cps));
	POINT cursorPos{};
	GetCursorPos(&cursorPos);
	PostMessageA(Ripterms::window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
	PostMessageA(Ripterms::window, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
	std::uniform_int_distribution<> distr(min_cps, max_cps);
	timer.setEvery(std::chrono::milliseconds(1000 / distr(gen)));
}

void Ripterms::Modules::LeftClicker::run()
{
	static CTimer timer(std::chrono::milliseconds(1000/min_cps));
	if (!enabled || Ripterms::GUI::draw)
		return;
	if (!timer.isElapsed()) 
		return;
	if (Ripterms::cache->theMinecraft.getObjectMouseOver().getType().isEqualTo(MovingObjectType::getType("BLOCK")))
		return;

	if (cache->theMinecraft.getCurrentScreen().isValid()) {
		if (in_gui)
		{
			if (hold_mb)
			{
				if ((GetKeyState(VK_LBUTTON) & 0x8000))
				{
					LC();
				}
			}
			else {
				LC();
			}
		}
	}else {
		if (hold_mb)
		{
			if ((GetKeyState(VK_LBUTTON) & 0x8000))
			{
				LC();
			}
		}
		else {
			LC();
		}
	}
}

void Ripterms::Modules::LeftClicker::renderGUI()
{
	ImGui::Checkbox("Left Clicker", &enabled);
	if (enabled)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.0f);
		ImGui::BeginGroup();
		ImGui::Checkbox("Hold mb", &hold_mb);
		ImGui::Checkbox("In GUI", &in_gui);
		ImGui::SliderInt("Min CPS", &min_cps, 1, 150);
		ImGui::SliderInt("Max CPS", &max_cps, 1, 150);
		ImGui::EndGroup();
	}
}
