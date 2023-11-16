#include "Result.h"
#include "SelectStage.h"
#include "Score.h"
#include "PadInput.h"

//�R���X�g���N�^
Result::Result()
{
	score = Score::GetScore();
	img[0] = LoadGraph("resource/images/makimono.png");
	img[1] = LoadGraph("resource/images/Enemy/zakuro.png");
	img[2] = LoadGraph("resource/images/Enemy/himawari.png");
	img[3] = LoadGraph("resource/images/Enemy/iruka.png");
	img[4] = LoadGraph("resource/images/Result1.png");
	img[5] = LoadGraph("resource/images/Result2.png");


	draw_score = 0;
	LoadDivGraph("resource/images/ResultNum.png", 10, 4, 3, 73, 73, num_img);
}

//�f�X�g���N�^
Result::~Result()
{
}

// �`��ȊO�̍X�V������
AbstractScene* Result::Update()
{

	//�X�R�A�����������₷(��ʕ\��)
	if (score > draw_score)
	{
		draw_score += 1;
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
			return new SelectStage();
		}
	}

	return this;
}

//�`��Ɋւ��邱�Ƃ�����
void Result::Draw() const
{


	DrawBox(0, 0, 1280, 720, 0xdddddd, TRUE);

	DrawGraph(97, 30, img[0], TRUE);

	//SetFontSize(30);
	//DrawFormatString(600, 150, 0x000000, "����̐���");
	DrawGraph(535, 140, img[4], TRUE);

	DrawGraph(370, 250, img[2], TRUE);
	DrawFormatString(470, 295, 0x000000, "�~");
	DrawGraph(500, 280, num_img[0], TRUE);

	DrawGraph(595, 300, img[3], TRUE);
	DrawFormatString(705, 295, 0x000000, "�~");
	DrawGraph(735, 280, num_img[0], TRUE);

	DrawGraph(855, 290, img[1], TRUE);
	DrawFormatString(940, 295, 0x000000, "�~");
	DrawGraph(970, 280, num_img[0], TRUE);

	DrawGraph(465, 455, img[5], TRUE);

	int a = draw_score;

	int pos_x = 830;

	do
	{
		DrawGraph(pos_x, 440, num_img[a % 10], TRUE);
		a /= 10;
		pos_x -= 40;
	} while (a > 0);

}
