#pragma once
#include "BoxCollider.h"
#include "Scroll.h"
class Stage:
	public BoxCollider
{
private:
	
public:
	Stage(float _x, float _y, float _width, float _height);
	~Stage();
	void Update();
	void Draw()const;

	//�X�e�[�W�����炷����(�g���₷���p�ɂ������Ă������OK)
	void MoveStage(ScrollData _scroll);
};
