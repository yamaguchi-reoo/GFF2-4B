#pragma once
#include "BoxCollider.h"

class Stage:
	public BoxCollider
{
private:
	
public:
	Stage();
	~Stage();
	void Update();
	void Draw()const;
};
