#include "main.h"

class  Input
{
private:
	static bool Quit;
	static int32 MouseX;
	static int32 MouseY;
	static int32 MouseZ;
	static int32 MouseXSpeed;
	static int32 MouseYSpeed;
	static int32 MouseZSpeed;
	static bool *MouseDown;
	static bool *KeyDown;

	static void Initialize();
	static void Destroy();
public:
	static void Clear();
	static void Update();

	static bool getQuit();
	static int32 getMouseX();
	static int32 getMouseY();
	static int32 getMouseZ();
	static int32 getMouseXSpeed();
	static int32 getMouseYSpeed();
	static int32 getMouseZSpeed();
	static bool getMouseDown(pros::controller_digital_e_t mouseButton);
	static bool getKeyDown(pros::controller_digital_e_t key);

	static void setMousePosition(int32 x, int32 y, bool updateMouseSpeed);

	friend class Device;
};
