#include "FastPix3D.h"

int32 Device::Width;
int32 Device::Height;
int32 *Device::BackBuffer;
int16 *Device::DepthBuffer;
sbyte *Device::StencilBuffer;

#include <cstring>
// Change device if we are on PC
#ifdef THREADS_STD
SDL_Window *Window;
SDL_Renderer *Renderer;
SDL_Texture *ScreenTexture;

void Device::setTitle(string title)
{
	SDL_SetWindowTitle(Window, title.c_str());
}
void Device::Initialize(int32 width, int32 height){
	Width = width;
	Height = height;
	SDL_Init(SDL_INIT_VIDEO);
	Window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	ScreenTexture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, Width, Height);

	BackBuffer = new int32[Width * Height];
	DepthBuffer = new int16[Width * Height];
	StencilBuffer = new sbyte[Width * Height];

	setTitle("FastPix3D");
	Input::Initialize();
	RenderStates::Initialize();
	Light::Initialize();
	Drawer::Initialize();
}
void Device::Destroy(){
	delete[] DepthBuffer;
	delete[] StencilBuffer;

	RenderStates::Destroy();
	Input::Destroy();

	SDL_DestroyTexture(ScreenTexture);
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
void Device::Present(){
	SDL_UpdateTexture(ScreenTexture, NULL, BackBuffer, Width << 2);
	SDL_RenderCopy(Renderer, ScreenTexture, NULL, NULL);
	SDL_RenderPresent(Renderer);
}

#else

lv_vdb_t *framebuffer;
void Device::Initialize(int32 width, int32 height){
	Width = width;
	Height = height;

    framebuffer = lv_vdb_get();
    memset(framebuffer->buf, 0, LV_HOR_RES * LV_VER_RES * sizeof(lv_color_t));
	BackBuffer = new int32[Width * Height];
	DepthBuffer = new int16[Width * Height];
	StencilBuffer = new sbyte[Width * Height];

	//setTitle("FastPix3D");

	Input::Initialize();
	RenderStates::Initialize();
	Light::Initialize();
	Drawer::Initialize();
}

void Device::Present(){
		memcpy(framebuffer->buf, BackBuffer, Width * Height * sizeof(lv_color_t));
		lv_vdb_flush();
}
void Device::setTitle(string title){}

void Device::Destroy()
{
	delete[] DepthBuffer;
	delete[] StencilBuffer;

	RenderStates::Destroy();
	Input::Destroy();

    /*
	SDL_DestroyTexture(ScreenTexture);
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	*/
}

#endif



void Device::ClearBackBuffer()
{
	memset(BackBuffer, 0, Width * Height);
}
void Device::ClearBackBuffer(Color color)
{
	fill_n(BackBuffer, Width * Height, color.getRGB());
}
void Device::ClearDepthBuffer()
{
	memset(DepthBuffer, 1, Width * Height << 1);
}
void Device::ClearStencilBuffer()
{
	memset(StencilBuffer, 0, Width * Height);
}


string Device::getTitle()
{
	//return string(SDL_GetWindowTitle(Window));
	return "";
}
int32 Device::getWidth()
{
	return Width;
}
int32 Device::getHeight()
{
	return Height;
}
