#include "FastPix3D.h"
#include "main.h"

int32 Input::JoyX[2];
int32 Input::JoyY[2];
int32 Input::JoyXSpeed[2];
int32 Input::JoyYSpeed[2];

pros::controller_digital_e_t buttons[12] = { DIGITAL_L1, DIGITAL_L2,
		DIGITAL_R1, DIGITAL_R2, DIGITAL_UP, DIGITAL_DOWN, DIGITAL_LEFT,
		DIGITAL_RIGHT, DIGITAL_X, DIGITAL_Y, DIGITAL_A, DIGITAL_B };

std::map<pros::controller_digital_e_t,bool> Input::KeyDown;



void Input::Initialize(){
}
void Input::Destroy(){}

void Input::Clear()
{
	//SDL_Event e;
	//while (SDL_PollEvent(&e));
}
void Input::Update(int32 dt)
{
  /*
	for (int i = 0; i<1;i++){
		JoyXSpeed[i] = 0;
		JoyYSpeed[i] = 0;
	}
  */

	for (pros::controller_digital_e_t button: buttons){

		KeyDown[button] = (bool)pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, button);
	}
  JoyXSpeed[0] = pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER,pros::E_CONTROLLER_ANALOG_LEFT_X);
  JoyXSpeed[1] = pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER,pros::E_CONTROLLER_ANALOG_RIGHT_X);
  JoyYSpeed[0] = pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER,pros::E_CONTROLLER_ANALOG_LEFT_Y);
  JoyYSpeed[1] = pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER,pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	JoyX[0] = JoyXSpeed[0] * dt;
	JoyX[1] = JoyXSpeed[1] * dt;
	JoyY[0] = JoyYSpeed[0] * dt;
	JoyY[1] = JoyYSpeed[1] * dt;

}

void Input::setJoyPosition(int32 x, int32 y, int32 joy, bool updateMouseSpeed)
{

	if (updateMouseSpeed)
	{
		JoyXSpeed[joy] += JoyX[joy] - x;
		JoyYSpeed[joy] += JoyY[joy] - y;
	}
	JoyX[joy] = x;
	JoyY[joy] = y;

}

int32 Input::getJoyX(int32 joy){
	return JoyX[joy];
};
int32 Input::getJoyY(int32 joy){
	return JoyY[joy];
};
int32 Input::getJoyXSpeed(int32 joy){
	return JoyXSpeed[joy];
};
int32 Input::getJoyYSpeed(int32 joy){
	return JoyYSpeed[joy];
};

bool Input::getKeyDown(pros::controller_digital_e_t key){
	return KeyDown[key];
};
