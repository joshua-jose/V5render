#include "main.h"
#include "FastPix3D/FastPix3D.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	//framebuffer = lv_vdb_get();
	pros::delay(100);
	printf("init");
//	memset(framebuffer->buf, 0, LV_HOR_RES * LV_VER_RES * sizeof(lv_color_t));
	pros::delay(200);

}
void disabled() {}
void competition_initialize() {}
void autonomous() {}

void opcontrol() {
	//framebuffer = lv_vdb_get();
	//memset(framebuffer->buf, 0, LV_HOR_RES * LV_VER_RES * sizeof(lv_color_t));
	//pros::Task current = pros::Task(CURRENT_TASK);
	//current.set_priority(TASK_PRIORITY_MAX);
  /*
	while (true){

		lv_color_t *red = new lv_color_t LV_COLOR_HEX(COLOR_RED);
		for(int i = 0; i < LV_VER_RES * LV_HOR_RES; i++){
        framebuffer->buf[i] = *red;
    }
		lv_vdb_flush();

		pros::delay(20);
	}
	*/

	printf("test");
  pros::delay(100);
	Device::Initialize(LV_HOR_RES, LV_VER_RES);

	RenderStates::ClipNear = .1f;
	RenderStates::Zoom = 2;

	//FPSCounter *fpsCounter = new FPSCounter(500);

	//Font *font = new Font("/usd/Media/Fonts/16x16.png");

	Mesh *gear1 = Mesh::FromFile("/usd/Media/Meshes/Gear1.fp3d");

  Mesh *gear2 = Mesh::FromFile("/usd/Media/Meshes/Gear2.fp3d");
	Mesh *gear3 = Mesh::FromFile("/usd/Media/Meshes/Gear3.fp3d");
	//Mesh *cube = new Mesh(1);

	RenderStates::CameraSpace = Matrix::RotateY(-30) * Matrix::RotateX(-20) * Matrix::Translate(Vector3f(0, 0, 20));
	int last_time = pros::millis();
	pros::delay(20);

	while (true){
		float time = pros::millis() - last_time;
		last_time = pros::millis();

		Device::ClearBackBuffer(Color(0, 0, 0));
		Device::ClearDepthBuffer();
		//gear1->Draw(Matrix::Identity());
		gear1->Draw(Matrix::RotateX(-90) * Matrix::RotateZ(last_time * 0.05) * Matrix::Translate(Vector3f(-3, -2, 0)));
		gear2->Draw(Matrix::RotateX(-90) * Matrix::RotateZ(last_time * 0.05 * -2 + 25) * Matrix::Translate(Vector3f(3.1f, -2, 0)));
		gear3->Draw(Matrix::RotateX(-90) * Matrix::RotateZ(last_time * 0.05 * -2 + 10) * Matrix::Translate(Vector3f(-3.1f, 4.1f, 0)));

		//Examples::DrawRenderingInformation(font, fpsCounter, gear1->getTriangleCount() + gear2->getTriangleCount() + gear3->getTriangleCount(), false);
		//Graphics::FillRectangle(0, 0, LV_HOR_RES, LV_VER_RES, Color(255, 0, 0), 1.0f);
	  Device::Present();

		//Input::Update();
		pros::delay(20);
	}


	//delete fpsCounter;
	//delete gear1, gear2, gear3;

	Device::Destroy();




}
