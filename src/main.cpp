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
    /*
    fprintf(stderr,"start\n");
    pros::delay(10);
    Device::Initialize(LV_HOR_RES, LV_VER_RES);

    RenderStates::ClipNear = 1.0f;
    RenderStates::Zoom = 2;

    //FPSCounter* fpsCounter = new FPSCounter(20);
    FreelookManager *freelookManager = new FreelookManager();

    Font* font = new Font("/usd/Media/Fonts/16x16.png");

    //Mesh* gear1 = Mesh::FromFile("/usd/Media/Meshes/Gear1.fp3d");
    //Mesh* gear2 = Mesh::FromFile("/usd/Media/Meshes/Gear2.fp3d");
    //Mesh* gear3 = Mesh::FromFile("/usd/Media/Meshes/Gear3.fp3d");

    static const float positions[6][4][3] = {
        {{-1, -1, -1}, {-1, -1, +1}, {-1, +1, -1}, {-1, +1, +1}},
        {{+1, -1, -1}, {+1, -1, +1}, {+1, +1, -1}, {+1, +1, +1}},
        {{-1, +1, -1}, {-1, +1, +1}, {+1, +1, -1}, {+1, +1, +1}},
        {{-1, -1, -1}, {-1, -1, +1}, {+1, -1, -1}, {+1, -1, +1}},
        {{-1, -1, -1}, {-1, +1, -1}, {+1, -1, -1}, {+1, +1, -1}},
        {{-1, -1, +1}, {-1, +1, +1}, {+1, -1, +1}, {+1, +1, +1}}
    };
    static const float normals[6][3] = {
        {-1, 0, 0},
        {+1, 0, 0},
        {0, +1, 0},
        {0, -1, 0},
        {0, 0, -1},
        {0, 0, +1}
    };
    static const float uvs[6][4][2] = {
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
        {{1, 0}, {0, 0}, {1, 1}, {0, 1}},
        {{0, 1}, {0, 0}, {1, 1}, {1, 0}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{1, 0}, {1, 1}, {0, 0}, {0, 1}}
    };
    static const int indices[6][6] = {
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3},
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3},
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3}
    };

    Mesh *cube = new Mesh(6);
    int32 vertexCount = 4, triangleCount= 2;
    for (int32 i = 0; i < cube->SubsetCount; i++)
  	{
  		Subset *subset = new Subset(vertexCount, triangleCount);

      subset->AppliedTexture = new Texture(256,256);

      for (int32 a = 0; a < vertexCount; a++)
  		{
  			Vector3f position = Vector3f(positions[i][a][0],positions[i][a][1],positions[i][a][2]);
  			Vector3f normal= Vector3f(normals[i][0],normals[i][1],normals[i][2]);
  			Vector2f UVs = Vector2f(uvs[i][a][0],uvs[i][a][1]);
        subset->Vertices[a] = Vertex(position,normal,UVs);
  			subset->Vertices[a].VertexColor = Color(255, 255, 255);

  		}

      subset->Triangles[0].Vertex1 = &subset->Vertices[indices[i][0]];
      subset->Triangles[0].Vertex2 = &subset->Vertices[indices[i][1]];
      subset->Triangles[0].Vertex3 = &subset->Vertices[indices[i][2]];
      subset->Triangles[1].Vertex1 = &subset->Vertices[indices[i][3]];
      subset->Triangles[1].Vertex2 = &subset->Vertices[indices[i][4]];
      subset->Triangles[1].Vertex3 = &subset->Vertices[indices[i][5]];


  		cube->Subsets[i] = subset;
    };



    RenderStates::CameraSpace = Matrix::RotateY(-30) * Matrix::RotateX(-20) * Matrix::Translate(Vector3f(0, 0, 20));
    int last_time = pros::millis();
    pros::delay(20);

    ShadowVolume *cubeShadow = new ShadowVolume(cube);

    RenderStates::Lights[0]->Enabled = true;
  	RenderStates::Lights[0]->Type = LightType::Spot;
  	RenderStates::Lights[0]->Intensity = 40;
  	RenderStates::Lights[0]->DiffuseColor = Color(165, 210, 255);

  	for (int32 x = -1, i = 1; x <= 1; x += 2)
  	{
  		for (int32 z = -1; z <= 1; z += 2, i++)
  		{
  			RenderStates::Lights[i]->Enabled = true;
  			RenderStates::Lights[i]->Type = LightType::Point;
  			RenderStates::Lights[i]->Intensity = 2;
  			RenderStates::Lights[i]->DiffuseColor = Color(127, 100, 75);
  			RenderStates::Lights[i]->Position = Vector3f(x * 8, -.5f, z * 8 - (z < 0 ? 1.f : 0.f));
  		}
  	}

    while (true) {
        float time = pros::millis() - last_time;
        last_time = pros::millis();

        Device::ClearBackBuffer(Color(0,0,0));
    		Device::ClearDepthBuffer();
    		Device::ClearStencilBuffer();

    		RenderStates::CameraSpace = freelookManager->Update();
    		RenderStates::Lights[0]->Enabled = true;
    		RenderStates::Lights[0]->Position = Vector3f(cos(time * .01f) * 8.5f, 1.5f, sin(time * .01f) * 8.5f);
    		RenderStates::Lights[0]->Rotation = Vector3f(0, (-1.5f - time * .01f) * 180 / float(M_PI), 0);
    		RenderStates::EnableStencilMask = false;
    		RenderStates::cullMode = CullMode::Back;
    		Light::AmbientColor = Color(50, 50, 50);

    		cube->Draw(Matrix::Identity());

    		RenderStates::cullMode = CullMode::None;
    		int32 shadowTriangleCount =
    			cubeShadow->Draw(RenderStates::Lights[0], Matrix::Identity(), 20);

    		RenderStates::Lights[0]->Enabled = false;
    		RenderStates::EnableStencilMask = true;
    		RenderStates::cullMode = CullMode::Back;

    		cube->Draw(Matrix::Identity());
        //gear1->Draw(Matrix::Identity());
        //gear1->Draw(Matrix::RotateX(-90) * Matrix::RotateZ(last_time * 0.05) * Matrix::Translate(Vector3f(-3, -2, 0)));
        //gear2->Draw(Matrix::RotateX(-90) * Matrix::RotateZ(last_time * 0.05 * -2 + 25) * Matrix::Translate(Vector3f(3.1f, -2, 0)));
        //gear3->Draw(Matrix::RotateX(-90) * Matrix::RotateZ(last_time * 0.05 * -2 + 10) * Matrix::Translate(Vector3f(-3.1f, 4.1f, 0)));


        //Examples::DrawRenderingInformation(font, fpsCounter, gear1->getTriangleCount() + gear2->getTriangleCount() + gear3->getTriangleCount(), false);
        //Graphics::FillRectangle(0, 0, LV_HOR_RES, LV_VER_RES, Color(255, 0, 0), 1.0f);
        Device::Present();

        Input::Update(time);
        pros::delay(20);
    }

    //delete fpsCounter;
    //delete gear1, gear2, gear3;

    Device::Destroy();
    */
}
