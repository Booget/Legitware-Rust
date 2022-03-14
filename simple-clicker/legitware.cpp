#include <windows.h>
#include <thread>

#include "globals.h"
#include "functions.h"
#include "legitware.h"
#include "tables.h"

using namespace functions;
int count = 0;
int afkDelay = 600000;

void recoil::legitware() {
	while (1) {
		if (GetAsyncKeyState(VK_LBUTTON) && globals.enableRecoil) {
			if (globals.enableHipfire && !(GetAsyncKeyState(VK_RBUTTON))) {
				switch (globals.selectedWeapon) {
				case 0:
					if (count < assault_rifle::pattern.size()) {
						smoothing(assault_rifle::delay, assault_rifle::control_time.at(count),
							c_amount(spray(globals.userSens, globals.userFov, assault_rifle::pattern.at(count).x * .6 * globals.controlAmountX / 100), NULL),
							c_amount(spray(globals.userSens, globals.userFov, assault_rifle::pattern.at(count).y * .6 * globals.controlAmountY / 100), NULL));
						count++;

						Sleep(.200);
					}
					break;
				}
			}
			if (globals.enableRecoil && GetAsyncKeyState(VK_RBUTTON)) {
				switch (globals.selectedWeapon) {
				case 0:
					if (count < assault_rifle::pattern.size()) {
						smoothing(assault_rifle::delay, assault_rifle::control_time.at(count),
							c_amount(spray(globals.userSens, globals.userFov, assault_rifle::pattern.at(count).x * globals.controlAmountX / 100), NULL),
							c_amount(spray(globals.userSens, globals.userFov, assault_rifle::pattern.at(count).y * globals.controlAmountY / 100), NULL));
						count++;

						Sleep(.200);
					}
					break;
				}
			}
		}
		else {
			count = 0;
		}

		if (globals.enableAutoCode)
		{
			if (GetAsyncKeyState(keys.enableCodeBind) & 1)
			{
				functions::key_input((int)globals.codeNum1);
				Sleep(globals.delayBetweenKeypress);
				functions::key_input((int)globals.codeNum2);
				Sleep(globals.delayBetweenKeypress);
				functions::key_input((int)globals.codeNum3);
				Sleep(globals.delayBetweenKeypress);
				functions::key_input((int)globals.codeNum4);
			}
		}

		if (globals.enableAntiAfk)
		{
			std::this_thread::sleep_for(std::chrono::seconds(600));
			functions::send_space();
		}

		if (globals.enableBgrade)
		{
			if (globals.selectedUpgradeType == 0)
			{
				globals.x_wood = 50;
				globals.y_wood = -100;

				globals.x_stone = 100;
				globals.y_stone = 0;

				globals.x_metal = -10;
				globals.y_metal = 100;

				globals.x_hqm = -200;
				globals.y_hqm = 0;
			}
			else if (globals.selectedUpgradeType == 1)
			{
				globals.upgradeDelay = 0;
				globals.upgradeSpeed = 0;
			}

			if (GetAsyncKeyState(VK_RBUTTON) & 1)
			{

				switch (globals.selectedBgradeMaterial)
				{
				case 0: // Wood
					Sleep(globals.upgradeDelay);
					functions::move_mouse(globals.upgradeSpeed, functions::convert(globals.userSens, globals.userFov, globals.x_wood), functions::convert(globals.userSens, globals.userFov, globals.y_wood));
					functions::sendKeyPress();
					break;
				case 1: // Stone
					Sleep(globals.upgradeDelay);
					functions::move_mouse(globals.upgradeSpeed, functions::convert(globals.userSens, globals.userFov, globals.x_stone), functions::convert(globals.userSens, globals.userFov, globals.y_stone));
					functions::sendKeyPress();
					break;
				case 2: // Metal
					Sleep(globals.upgradeDelay);
					functions::move_mouse(globals.upgradeSpeed, functions::convert(globals.userSens, globals.userFov, globals.x_metal), functions::convert(globals.userSens, globals.userFov, globals.y_metal));
					functions::sendKeyPress();
					break;
				case 3: // HQM
					Sleep(globals.upgradeDelay);
					functions::move_mouse(globals.upgradeSpeed, functions::convert(globals.userSens, globals.userFov, globals.x_hqm), functions::convert(globals.userSens, globals.userFov, globals.y_hqm));
					functions::sendKeyPress();
					break;
				}
			}
		}
	}
}