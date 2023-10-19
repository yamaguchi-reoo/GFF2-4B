#pragma once
#include "BoxCollider.h"

class Stage:
	public BoxCollider
{
private:
	
public:
	Stage(float _x, float _y, float _width, float _height);
	~Stage();
	void Update();
	void Draw()const;
};
