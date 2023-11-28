#pragma once
#include "BoxCollider.h"
class Jar:
	public BoxCollider
{
private:
	bool spawn_flg;
public:

	Jar(float pos_x, float pos_y);
	~Jar();

	void Update();
	void Draw()const;

};

