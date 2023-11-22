#include "LockPlayer.h"
#include "DxLib.h"

//�R���X�g���N�^
LockPlayer::LockPlayer()
{
	lock_flg = false;
	grass_lx = -650;
	grass_rx = 1290;
	grass_flg = false;
	enemy_cnt = 0;
	create_en = 0;
	attack_en = 0;
	img = LoadGraph("resource/images/kusa.png");
}

//�f�X�g���N�^
LockPlayer::~LockPlayer()
{
}

//�X�V����
void LockPlayer::Update()
{
	//���̃A�j���[�V������A���̃A�j���[�V����
	if (grass_flg == false)
	{
		GrassAnim();
	}
}

//�`�揈��
void LockPlayer::Draw() const
{
	if (lock_flg == true)
	{
		//��
		DrawGraph(grass_lx, -5, img, TRUE);
		DrawGraph(grass_rx, -5, img, TRUE);

	}
}

//���̃A�j���[�V����
void LockPlayer::GrassAnim()
{
	//����������͂₷
	if (grass_lx < 0)
	{
		grass_lx += 35;
		grass_rx -= 35;
	}
	else
	{
		grass_flg = true;
	}
}