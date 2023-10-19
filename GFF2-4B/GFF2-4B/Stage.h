#pragma once
#include "BoxCollider.h"

class Stage:
	private BoxCollider
{
private:
	
public:
	Stage();
	~Stage();
	void Update();
	void Draw()const;
};
