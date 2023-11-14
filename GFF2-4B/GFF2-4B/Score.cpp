#include "Score.h"
#include "PadInput.h"

Score::Score()
{
	// �c�w�t�H���g�f�[�^�t�@�C����ǂݍ��݁A�t�H���g�n���h����ϐ� FontHandle �ɕۑ�����
	font_handle = LoadFontDataToHandle("resource/font/Misogi.dft", 0);
	score_img = LoadGraph("resource/images/Score_UI.png");

	total_score = 0;
	draw_score = 0;
}

Score::~Score()
{
	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(font_handle);
}

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

void Score::Draw() const
{
#ifdef _DEBUG

	//DrawFormatString(160, 30, 0xffffff, "%d", font_handle);

#endif // _DEBUG

	//UI�w�i�\��
	DrawGraph(155, 10, score_img, TRUE);

	//�X�R�A�\��
	DrawFormatStringToHandle(210, 26, 0x000000, font_handle, "�_��:%6d", draw_score);
}

void Score::AddScore(int score)
{
	total_score += score;
}
