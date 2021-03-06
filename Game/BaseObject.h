#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	
	void SetRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	int GetRect_h() { return rect_.h; };
	int GetRect_w() { return rect_.w; };
	SDL_Texture* GetObject() { return p_object_; }

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
	
	

protected:
	SDL_Rect rect_;
	SDL_Texture* p_object_;
};
#endif // !BASE_OBJECT_H_