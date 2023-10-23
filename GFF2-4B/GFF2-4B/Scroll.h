#pragma once
#include "Dxlib.h"
#include "BoxCollider.h"
#include "common.h"

struct ScrollData
{
	bool direction;
	float move;
};
class SceneScroll
{
private:
	int stage_image;	//�X�e�[�W�摜(�w�i)
	
	float scroll_x;		//�w�i�摜�̍��㒸�_����X���W
	float scroll_y;		//�w�i�摜�̍��㒸�_����Y���W

public:
	//�R���X�g���N�^
	SceneScroll();
	//�f�X�g���N�^
	~SceneScroll();
	//�`��ȊO�̍X�V�Ɋւ��鏈��
	void Update(Location player, float acs_l, float acs_r);
	//�v���C���[�̍s���͈͂��Œ肷�鏈��
	ScrollData PlayerScroll(Location player);
	//�`��X�V�Ɋւ��鏈��
	void Draw();
};