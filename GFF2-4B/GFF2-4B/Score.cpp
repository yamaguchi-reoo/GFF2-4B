#include "Score.h"
#include "PadInput.h"

int Score::total_score = 0;

//�R���X�g���N�^
Score::Score()
{
	// �c�w�t�H���g�f�[�^�t�@�C����ǂݍ��݁A�t�H���g�n���h����ϐ� FontHandle �ɕۑ�����
	font_handle = LoadFontDataToHandle("resource/font/Misogi.dft", 0);
	score_img[0] = LoadGraph("resource/images/Score_UI.png");
	score_img[1] = LoadGraph("resource/images/Tokuten.png");
	draw_score = 0;
}

//�f�X�g���N�^
Score::~Score()
{
	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(font_handle);
}

//�X�V����
void Score::Update()
{
#ifdef _DEBUG

	//�T����������X�R�A���Z
	if (KeyInput::OnKey(KEY_INPUT_5))
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
	DrawGraph(205, 29, score_img[1], TRUE);
	DrawFormatStringToHandle(288, 27, 0x000000, font_handle, "%06d", draw_score);
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


