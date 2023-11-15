#include "Score.h"
#include "PadInput.h"

int Score::total_score = 0;

//�R���X�g���N�^
Score::Score()
{
	score_img[0] = LoadGraph("resource/images/Score_UI.png");
	score_img[1] = LoadGraph("resource/images/Tokuten.png");
	LoadDivGraph("resource/images/ScoreNum.png", 10, 4, 3, 32, 32, num_img);

	draw_score = 0;
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

	//�X�R�A�����������₷(��ʕ\��)
	if (total_score > draw_score)
	{
		draw_score += 4;
	}
	else if (total_score < draw_score)
	{
		draw_score = total_score;
	}
}

//�`�揈��
void Score::Draw() const
{
#ifdef _DEBUG

	//DrawFormatString(160, 30, 0xffffff, "%d", font_handle);

#endif // _DEBUG

	//UI�w�i�\��
	DrawGraph(155, 10, score_img[0], TRUE);

	//�X�R�A�\��
	DrawGraph(206, 29, score_img[1], TRUE);
	for (int i = 0; i < 6; i++)
	{
		DrawGraph(270 + 15 * i, 24, num_img[0], TRUE);
	}
	
}

//�g�[�^���X�R�A�ɉ��Z(����:���Z����X�R�A�̐��l)
void Score::AddScore(int score)
{
	total_score += score;
}

void Score::SetScore()
{
	total_score = 0;
}


