#include "CommonFunc.h"
#include "BaseObject.h"
#include "Game_Map.h"
#include "MainObject.h"
#include "ImpTimer.h"

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
	return ret;
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
void Select_Scene(SDL_Renderer* g_screen, MainObject& p_simon, Map& map_data, GameMap& game_map, int scene)
{
	switch (scene)
	{
	case 1:
	{
		char map_direction[] = "map//map1//map01.dat";
		char* map = map_direction;
		game_map.LoadTiles(g_screen, 1);//tile trc map sau
		game_map.LoadMap(map);
	}
	break;
	case 2:
	{
		char map_direction2[] = "map//map2//map02.dat";
		char* map2 = map_direction2;
		game_map.LoadTiles(g_screen, 2);//tile trc map sau
		game_map.LoadMap(map2);
		map_data = game_map.getMap();

		p_simon.SetPos(2900, 0);
	}
	break;
	case 3:
	{
		char map_direction3[] = "map//map3//map03.dat";
		char* map3 = map_direction3;
		game_map.LoadTiles(g_screen, 3);//tile trc map sau
		game_map.LoadMap(map3);
		map_data = game_map.getMap();

		p_simon.SetPos(0, 0);
	}
	break;
	case 4:
	{
		char map_direction2[] = "map//map2//map02.dat";
		char* map2 = map_direction2;
		game_map.LoadTiles(g_screen, 2);//tile trc map sau
		game_map.LoadMap(map2);
		map_data = game_map.getMap();

		p_simon.SetPos(3104, 352); /////load simon o canh vi tri cau thang di xuong scene 2
	}
	break;
	}
}

int main(int arc, char* argv[])
{
	ImpTimer fps_timer;

	int check_point_ = -1;

	if (InitData() == false)
		return -1;
	if (LoadBackground() == false)
		return -1;


	bool is_quit = false;
	GameMap game_map;

	Map map_data;
	

	MainObject p_simon;
	p_simon.LoadImg("img//simon_right1.png", g_screen);
	p_simon.set_clips();

	MainObject game_background;
	game_background.LoadImg("img//map1_background.png", g_screen);
		
	Select_Scene(g_screen, p_simon, map_data, game_map, 1);// load scene 1

	while (!is_quit)
	{
		fps_timer.start();
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

		g_background.SetRect(0, 0);
		g_background.Render(g_screen, NULL);

		map_data = game_map.getMap();



		p_simon.SetMapXY(map_data.start_x_, map_data.start_y_);
		check_point_= p_simon.DoPlayer(map_data);

		Select_Scene(g_screen, p_simon, map_data, game_map, check_point_);//////////

		game_map.setMap(map_data);
		game_map.DrawMap(g_screen);

		p_simon.Show(g_screen);

		SDL_RenderPresent(g_screen);
		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND; //ms
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0)
				SDL_Delay(delay_time);
		}
	}


	close();
	return 0;
}