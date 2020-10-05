#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>



static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Color Key
const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 0;
const int COLOR_KEY_B = 255;

const int RENDER_DRAW_COLOR = 0Xff;

#define TILE_SIZE 32

const int MAX_MAP_X = 30;
const int MAX_MAP_Y = 15;

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};

typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};




#endif