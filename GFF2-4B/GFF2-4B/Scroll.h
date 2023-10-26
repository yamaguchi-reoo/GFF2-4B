#pragma once
#include "Dxlib.h"
#include "BoxCollider.h"
#include "common.h"

enum class ScrollState : int
{
	INIT_POS_SCROLL = 0,
	MOVE_SCROLL
};

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

	int graph_size_x;
	int graph_size_y;

	ScrollState state;
public:
	//�R���X�g���N�^
	SceneScroll();
	//�f�X�g���N�^
	~SceneScroll();
	//�`��ȊO�̍X�V�Ɋւ��鏈��
	void Update(Location player, float acs_l, float acs_r);
	//�v���C���[�̍s���͈͂��Œ肷�鏈��
	ScrollData PlayerScroll(Location player);
	//�s���͈͂��z���������f���Ēl��Ԃ�����
	int ActionRangeBorder(Location player);
	//�X�N���[����ON�EOFF�̐؂�ւ�����
	void ChangeScrollMode();
	//�`��X�V�Ɋւ��鏈��
	void Draw();
};