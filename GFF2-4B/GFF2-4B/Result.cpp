#include "Result.h"
#include "SelectStage.h"
#include "Score.h"
#include "PadInput.h"
#include "LoadingScene.h"

//�R���X�g���N�^
Result::Result()
{
	score = Score::GetScore();
	img[0] = LoadGraph("resource/images/Result/makimono1.png");
	img[6] = LoadGraph("resource/images/Result/makimono2.png");
	img[7] = LoadGraph("resource/images/Result/makimono3.png");


	img[1] = LoadGraph("resource/images/Enemy/zakuro.png");
	img[2] = LoadGraph("resource/images/Enemy/H.png");
	img[3] = LoadGraph("resource/images/Enemy/I.png");
	img[4] = LoadGraph("resource/images/Result/Result1.png");
	img[5] = LoadGraph("resource/images/Result/Result2.png");

	x1 = 0;
	x2 = 640;
	anim_flg = 0;

	draw_score = 0;
	LoadDivGraph("resource/images/Result/ResultNum.png", 10, 4, 3, 73, 73, num_img);

	zakuro_num = Score::GetAttackEnemyNum(0);
	iruka_num = Score::GetAttackEnemyNum(1);
	himawari_num = Score::GetAttackEnemyNum(2);
}

//�f�X�g���N�^
Result::~Result()
{
}

// �`��ȊO�̍X�V������
AbstractScene* Result::Update()
{
	if (anim_flg == 0)
	{
		AnimMakimono();
	}
	else
	{
		//�X�R�A�����������₷(��ʕ\��)
		if (score > draw_score)
		{
			draw_score += 110;
		}
		else if (score < draw_score)
		{
			draw_score = score;
		}

		if (draw_score == score)
		{

			//A�{�^���������ꂽ��X�e�[�W�I����ʂɑJ��
			if (
#ifdef _DEBUG
				PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
				PadInput::OnButton(XINPUT_BUTTON_A)
#endif
				)
			{
				Score::ResetScore();
				return new Loading();
			}
		}
	}

	return this;
}

//�`��Ɋւ��邱�Ƃ�����
void Result::Draw() const
{

	DrawBox(0, 0, 1280, 720, 0x7d7d7d, TRUE);

	DrawGraph(89, 25, img[6], TRUE);


	SetFontSize(30);
	//DrawFormatString(600, 150, 0x000000, "����̐���");
	DrawGraph(515, 140 + 10, img[4], TRUE);

	//�q�}����
	DrawGraph(330 - 30, 250 + 10, img[2], TRUE);
	DrawFormatString(430 - 30, 295 + 10, 0x000000, "�~");
	DrawGraph(460 - 40, 280 + 10, num_img[himawari_num / 10], TRUE);
	DrawGraph(460 + 40 - 33, 280 + 10, num_img[himawari_num % 10], TRUE);

	//�C���J
	DrawGraph(555, 300 + 10, img[3], TRUE);
	DrawFormatString(665, 295 + 10, 0x000000, "�~");
	DrawGraph(695 - 15, 280 + 10, num_img[iruka_num / 10], TRUE);
	DrawGraph(695 + 40 - 10, 280 + 10, num_img[iruka_num % 10], TRUE);

	//�U�N��
	DrawGraph(815, 290 + 10, img[1], TRUE);
	DrawFormatString(900, 295 + 10, 0x000000, "�~");
	DrawGraph(930 - 15, 280 + 10, num_img[zakuro_num / 10], TRUE);
	DrawGraph(930 + 40 - 10, 280 + 10, num_img[zakuro_num % 10], TRUE);

	//���_
	DrawGraph(425, 455 + 10, img[5], TRUE);

	int a = draw_score;
	int pos_x = 790;

	do
	{
		DrawGraph(pos_x, 440 + 10, num_img[a % 10], TRUE);
		a /= 10;
		pos_x -= 40;
	} while (a > 0);

	//����
	DrawGraph(x1, 0, img[7], TRUE);
	DrawGraph(x2, 0, img[0], TRUE);

}

//�����̃A�j���[�V����
void Result::AnimMakimono(void)
{
	if (x2 < 1100)
	{
		x1 -= 10;
		x2 += 10;
	}
	else
	{
		anim_flg = 1;
	}
}