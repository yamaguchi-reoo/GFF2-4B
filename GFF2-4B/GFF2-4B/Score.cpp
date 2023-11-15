#include "Score.h"
#include "PadInput.h"

int Score::total_score = 0;

//�R���X�g���N�^
Score::Score()
{
	score_img[0] = LoadGraph("resource/images/Score_UI.png");
	score_img[1] = LoadGraph("resource/images/Tokuten.png");
	LoadDivGraph("resource/images/ScoreNum.png", 10, 4, 3, 32, 32, num_img);

	temp_score[0] = 0;
	temp_score[1] = 0;
	temp_score[2] = 0;
	temp_score[3] = 0;
	temp_score[4] = 0;
	temp_score[5] = 0;

	draw_score = 0;

	i = 0;
}

//�f�X�g���N�^
Score::~Score()
{
}

//�X�V����
void Score::Update()
{
#ifdef _DEBUG

	//�T����������X�R�A���Z
	if (KeyInput::OnKey(KEY_INPUT_6))
	{
		total_score += 135;
	}

#endif // _DEBUG

	////�X�R�A�����������₷(��ʕ\��)
	//if (total_score > draw_score)
	//{
	//	draw_score += 4;
	//}
	//else if (total_score < draw_score)
	//{
	//	draw_score = total_score;
	//}

	total_score = 123456;

	i = total_score;

	/*if (i > 0)
	{
		ChangeScore();
	}*/
	
}

//�`�揈��
void Score::Draw() const
{
#ifdef _DEBUG

	DrawFormatString(400, 30, 0xffffff, "%d", temp_score[0]);

#endif // _DEBUG

	//UI�w�i�\��
	DrawGraph(155, 10, score_img[0], TRUE);

	//�X�R�A�\��
	DrawGraph(206, 29, score_img[1], TRUE);
	int a = total_score;

	/*for (int i = 0; i < 6; i++)
	{
	*/	DrawGraph(270 + 15 * i, 24, num_img[a / 100000], TRUE);
	    a = a % 100000;
		DrawGraph(270 + 15 * i, 24, num_img[a / 10000], TRUE);
		a = a % 10000;
		DrawGraph(270 + 15 * i, 24, num_img[a / 1000], TRUE);
		a = a % 1000;
		DrawGraph(270 + 15 * i, 24, num_img[a / 100], TRUE);
		a = a % 100;
		DrawGraph(270 + 15 * i, 24, num_img[a / 10], TRUE);
		a = a % 10;
		DrawGraph(270 + 15 * i, 24, num_img[a / 1], TRUE);
	//}

}

//�g�[�^���X�R�A�ɉ��Z(����:���Z����X�R�A�̐��l)
void Score::AddScore(int score)
{
	total_score += score;
}

//�X�R�A��0�ɏ�����
void Score::SetScore()
{
	total_score = 0;
}

//�X�R�A���摜�ɕύX���邽�߂̏���
//void Score::ChangeScore()
//{
//	temp_score[] = i / x;
//	i = total_score % x;	
//}


