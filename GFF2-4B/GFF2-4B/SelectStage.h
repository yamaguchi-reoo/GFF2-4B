#pragma once
#include "AbstractScene.h"

class SelectStage :public AbstractScene
{
private:
	static int stage_num;
	static int goal_flg[3]; //�ǂ��܂ŃN���A������
	bool botton_flg;
	int img[12];
	int Limg;
	int Stage_img[10];
	int x1, x2; //�����A�j���[�V�����p
	int anim_flg; //�����A�j���[�V�����p

public:
	//�R���X�g���N�^
	SelectStage();

	//�f�X�g���N�^
	~SelectStage();

	// �`��ȊO�̍X�V������
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

	//�N���A�����X�e�[�W��ۑ�
	void SetGoalFlg(int stage_num);

	//�����̃A�j���[�V����
	void AnimMakimono(void);
};

