#include "Result.h"
#include "SelectStage.h"
#include "Score.h"
#include "PadInput.h"

//�R���X�g���N�^
Result::Result()
{
	score = Score::GetScore();
	draw_score = 0;
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
		draw_score += 30;
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
			Score::SetScore();
			return new SelectStage();
		}
	}

	return this;
}

//�`��Ɋւ��邱�Ƃ�����
void Result::Draw() const
{
	SetFontSize(60);
	DrawFormatString(440, 290, 0xffffff, "���_�F%06d",draw_score);
}