#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Game_Map.h"

#define GRAVITY_SPEED 0.8;
const int MAX_FALL_SPEED =  15;

const int  PLAYER_SPEED = 15;//mac dinh =3
const int  PLAYER_JUMP_VAL = 20;  //10



class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum WalkType
	{
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_NONE = 0,
	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

	int DoPlayer(Map& map_data);
	int CheckToMap(Map& map_data);

	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
	void CenterEmtityOnMap(Map& map_data);

	void UpdateImgPlayer(SDL_Renderer* des);
	void SetPos(int x, int y) { x_pos_ = x; y_pos_ = y; }
	
		

private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;
	bool on_ground_;

	int map_x_;
	int map_y_;

	int type_action_;
	int check_pos_;
	int come_back_time;
	
};
#endif // !MAIN_OBJECT_H_

