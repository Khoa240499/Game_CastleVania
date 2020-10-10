#include "MainObject.h"

MainObject::MainObject()
{
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = WALK_NONE;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	bool on_ground_ = false;
	map_x_ = 0;
	map_y_ = 0;

	type_action_ = 0;
	come_back_time = 0;

	
}
MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / 7;
		height_frame_ = rect_.h / 1;
	}
	return ret;
}


void MainObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			frame_clip_[i].x = i* width_frame_;
			frame_clip_[i].y = 0* height_frame_;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
		
	}
}

void MainObject::Show(SDL_Renderer* des)
{
	UpdateImgPlayer(des);
	if (input_type_.left_ == 1 || input_type_.right_ == 1)
	{
		frame_++;
	}
	else
		frame_ = type_action_;
	if (frame_ >= 7)
	{
		frame_ = type_action_;
	}
	if (come_back_time == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;

		SDL_Rect* current_clip = &frame_clip_[frame_];
		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
	

}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			type_action_ = 1;
			UpdateImgPlayer(screen);
		}
		break;
		case SDLK_RIGHT:
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			type_action_ = 1;
			UpdateImgPlayer(screen);

		}
		break;
		case SDLK_s:
		{
			input_type_.jump_ = 1;
			UpdateImgPlayer(screen);
		}
		break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			input_type_.left_ = 0;
			type_action_ = 0;

		}
		break;
		case SDLK_RIGHT:
		{
			input_type_.right_ = 0;
			type_action_ = 0;
		}
		break;

		case SDLK_s:
		{
			/*if (on_ground_ == true)
				type_action_ = 0;*/
		}
		break;
		}
	}
	
}
bool MainObject::DoPlayer(Map& map_data)
{
	bool check_point_ = false;
	if (come_back_time == 0)
	{
		x_val_ = 0;
		y_val_ += GRAVITY_SPEED;

		if (y_val_ >= MAX_FALL_SPEED)
		{
			y_val_ = MAX_FALL_SPEED;
		}
		if (input_type_.left_ == 1)
		{
			x_val_ -= PLAYER_SPEED;
		}
		else if (input_type_.right_ == 1)
		{
			x_val_ += PLAYER_SPEED;
		}
		if (input_type_.jump_ == 1)
		{
			if (on_ground_ == true)
			{
				y_val_ = -PLAYER_JUMP_VAL;
				on_ground_ = false;
			}

			input_type_.jump_ = 0;
		}
		check_point_= CheckToMap(map_data);
		CenterEmtityOnMap(map_data);
	}
	if (come_back_time > 0)
	{
		come_back_time--;
		if (come_back_time == 0) 
		{
			on_ground_ = false;
			y_pos_ = 0;
			x_pos_ -= TILE_SIZE * 3;
			x_val_ = 0;
			y_val_ = 0;
		}		

	}
	return check_point_;


}
bool MainObject::CheckToMap(Map& map_data)
{
	bool check_point_ = false;
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	//check chieu ngang

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < map_data.MAX_MAP_X && y1 >= 0 && y2 < map_data.MAX_MAP_Y)
	{
		if (x_val_ > 0)
		{
			if (map_data.tile[y1][x2] == CHECK_POINT || map_data.tile[y2][x2] == CHECK_POINT)
			{
				check_point_ = true;
			}
			if (map_data.tile[y1][x2] > map_data.BLANK_TILE || map_data.tile[y2][x2] > map_data.BLANK_TILE)
			{
				
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
								

			}
			else if (x_val_ < 0)
			{
				if (map_data.tile[y1][x1] == CHECK_POINT || map_data.tile[y2][x1] == CHECK_POINT)
				{
					check_point_ = true;
				}
				if (map_data.tile[y1][x1] > map_data.BLANK_TILE || map_data.tile[y2][x1] > map_data.BLANK_TILE)
				{
					
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
				}
			}
		}
	}

	//-------Chech chieu doc

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;


	if (x1 >= 0 && x2 < map_data.MAX_MAP_X && y1 >= 0 && y2 < map_data.MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			
			if (map_data.tile[y2][x1] > map_data.BLANK_TILE || map_data.tile[y2][x2] > map_data.BLANK_TILE)
			{
				
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				on_ground_ = true;
				if (status_ == WALK_NONE)
					status_ = WALK_RIGHT;
				
								
			}
		}
		if (y_val_ < 0)
		{
			
			if (map_data.tile[y1][x1] > map_data.BLANK_TILE || map_data.tile[y1][x2] > map_data.BLANK_TILE)
			{
				
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else
	{
		if (x_pos_ + width_frame_ > map_data.max_x_)
		{
			x_pos_ = map_data.max_x_ - width_frame_ - 1;
		}
	}
	if (y_pos_ > map_data.max_y_ + 32)
	{
		come_back_time = 30;
	
	}
	return check_point_;
}
void MainObject::CenterEmtityOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT + 64 / 1);
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}

}
void MainObject :: UpdateImgPlayer(SDL_Renderer* des)
{
	if (on_ground_ == true)
	{
		if (status_ == WALK_LEFT)
		{
			LoadImg("img//simon_left1.png", des);
		}
		else
		{
			LoadImg("img//simon_right1.png", des);
		}
	}
	else
	{
		if (status_ == WALK_LEFT)
		{
			LoadImg("img//jump_left.png", des);
		}
		else
		{
			LoadImg("img//jump_right.png", des);
		}
	}
}

