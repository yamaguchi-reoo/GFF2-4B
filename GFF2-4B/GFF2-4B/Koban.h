#pragma once
#include "BoxCollider.h"

class Koban : public BoxCollider
{
private:
	int KobanImg; //�摜�p�ϐ�

public:
	Koban(float pos_x,float pos_y);  //�R���X�g���N�^
	~Koban(); //�f�X�g���N�^

	void Update();     //�X�V����
	void Draw() const; //�`�揈��
};

