#pragma once
#include "AbstractScene.h"

class Result :public AbstractScene
{
private:

public:
	Result();

	~Result();

	// •`‰æˆÈŠO‚ÌXV‚ğÀ‘•
	AbstractScene* Update() override;

	//•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•
	void Draw() const override;

};

