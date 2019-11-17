#include "api.h"
#include <chrono>
#include <thread>

const Uint8 *keys;

std::uint32_t pros::millis(){
	milliseconds ms = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch()
	);
	return static_cast<std::uint32_t>(ms.count());
}

void pros::delay(const std::uint32_t milliseconds){
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

namespace pros{


namespace c{
	int32_t controller_get_analog(controller_id_e_t id, controller_analog_e_t channel){
		keys = SDL_GetKeyboardState(NULL);
		if(keys[SDL_SCANCODE_W] && channel == pros::E_CONTROLLER_ANALOG_RIGHT_Y) return 5;
		if(keys[SDL_SCANCODE_S] && channel == pros::E_CONTROLLER_ANALOG_RIGHT_Y) return -5;
		if(keys[SDL_SCANCODE_A] && channel == pros::E_CONTROLLER_ANALOG_RIGHT_X) return -5;
		if(keys[SDL_SCANCODE_D] && channel == pros::E_CONTROLLER_ANALOG_RIGHT_X) return 5;

		if(keys[SDL_SCANCODE_I] && channel == pros::E_CONTROLLER_ANALOG_LEFT_Y) return 5;
		if(keys[SDL_SCANCODE_K] && channel == pros::E_CONTROLLER_ANALOG_LEFT_Y) return -5;
		if(keys[SDL_SCANCODE_J] && channel == pros::E_CONTROLLER_ANALOG_LEFT_X) return -5;
		if(keys[SDL_SCANCODE_L] && channel == pros::E_CONTROLLER_ANALOG_LEFT_X) return 5;
		return 0;
	};
	int32_t controller_get_digital(controller_id_e_t id, controller_digital_e_t button){
		Uint32 mouse_state = SDL_GetMouseState(NULL, NULL);
		if ((mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))&& button == DIGITAL_L1) return 1;
		if ((mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT))&& button == DIGITAL_R1) return 1;
		return 0;
	};
}

}
