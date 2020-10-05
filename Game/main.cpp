#include "CommonFunc.h"
#include "BaseObject.h"
#include "Game_Map.h"
#include "MainObject.h"

#undef main

BaseObject g_background;

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("Game: CastleVania",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (g_window == NULL)
		success = false;
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if (g_screen == NULL)
				success = false;
			else
			{
				SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) && imgFlags))
					success = false;
			}
	}
	return success;
	
}
bool LoadBackground()
{
	bool ret = g_background.LoadImg("img//map1_background.png", g_screen);
	if (ret == false)
		return false;
	return true;
}
void close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();

}
int main(int arc, char* argv[])
{
	if (InitData() == false)
		return -1;
	if (LoadBackground() == false)
		return -1;

	GameMap game_map;
	
	char map_direction[] = "map//map01.dat";
	char* map = map_direction;

	game_map.LoadMap(map);
	game_map.LoadTiles(g_screen);

	MainObject p_simon;
	p_simon.LoadImg("img//simon_right.png", g_screen);
	p_simon.set_clips();


	bool is_quit = false;
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event) != 0) 
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			p_simon.HandleInputAction(g_event, g_screen);
		
		}
		
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);

		game_map.DrawMap(g_screen);

		p_simon.Show(g_screen);

		SDL_RenderPresent(g_screen);
	}
	close();
	return 0;
}