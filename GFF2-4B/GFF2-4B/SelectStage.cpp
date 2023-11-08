#include "SelectStage.h"
#include "GameMain.h"
#include "PadInput.h"

int SelectStage::stage_num = 0;
int SelectStage::goal_flg[3] = {1,1,1}; //�f�o�b�N�p��1

//�R���X�g���N�^
SelectStage::SelectStage()
{
	botton_flg = false;
	img = LoadGraph("resource/images/SelectCursor.png");
}

//�f�X�g���N�^
SelectStage::~SelectStage()
{
}

// �`��ȊO�̍X�V������
AbstractScene* SelectStage::Update()
{
	if (PadInput::TipLeftLStick(STICKL_X) <= -1 && botton_flg == false)
	{//���ړ�
		botton_flg = true;

		--stage_num;

		if (goal_flg[1] == 1)
		{
			if (stage_num < 0)
			{
				stage_num = 2;
			}
		}
		else
		{
			if (stage_num < 0)
			{
				stage_num = 0;
			}
		}
		
	}
	else if (PadInput::TipLeftLStick(STICKL_X) >= 1 && botton_flg == false)
	{//�E�ړ�
		botton_flg = true;

		++stage_num;

		if (goal_flg[1] == 1)
		{
			if (stage_num > 2)
			{
				stage_num = 0;
			}
		}
		else if(goal_flg[0] == 1)
		{
			if (stage_num > 1)
			{
				stage_num = 1;
			}
		}
		else
		{
			if (stage_num > 0)
			{
				stage_num = 0;
			}
		}
		
	}
	else if (PadInput::TipLeftLStick(STICKL_X) > -1 && PadInput::TipLeftLStick(STICKL_X) < 1 && PadInput::OnButton(XINPUT_BUTTON_B) == false)
	{//�������ĂȂ��Ƃ�
		botton_flg = false;
	}

	//A�{�^���������ꂽ��Q�[�����C���ɑJ��
	if (PadInput::OnButton(XINPUT_BUTTON_A) == true)
	{
		return new GameMain(stage_num);
	}

	return this;
}

//�`��Ɋւ��邱�Ƃ�����
void SelectStage::Draw() const
{
	SetFontSize(16);
	DrawBox(0, 0, 1280, 720, 0xadadad, TRUE);

	switch (stage_num)
	{
		case 0:
			DrawCircle(350, 200, 100, 0x000000, 1, 1);
			DrawCircle(650, 200, 100, 0xffffff, 1, 1);
			DrawCircle(950, 200, 100, 0xffffff, 1, 1);
			DrawFormatString(310, 200, 0xffffff, "�X�e�[�W1");
			DrawFormatString(610, 200, 0x000000, "�X�e�[�W2");
			DrawFormatString(910, 200, 0x000000, "�X�e�[�W3");
			break;

		case 1:
			DrawCircle(350, 200, 100, 0xffffff, 1, 1);
			DrawCircle(650, 200, 100, 0x000000, 1, 1);
			DrawCircle(950, 200, 100, 0xffffff, 1, 1);
			DrawFormatString(310, 200, 0x000000, "�X�e�[�W1");
			DrawFormatString(610, 200, 0xffffff, "�X�e�[�W2");
			DrawFormatString(910, 200, 0x000000, "�X�e�[�W3");
			break;

		case 2:
			DrawCircle(350, 200, 100, 0xffffff, 1, 1);
			DrawCircle(650, 200, 100, 0xffffff, 1, 1);
			DrawCircle(950, 200, 100, 0x000000, 1, 1);
			DrawFormatString(310, 200, 0x000000, "�X�e�[�W1");
			DrawFormatString(610, 200, 0x000000, "�X�e�[�W2");
			DrawFormatString(910, 200, 0xffffff, "�X�e�[�W3");
			break;

		default:
		break;
	}

	DrawGraph(280 + (stage_num * 310), 400, img, TRUE);

#ifdef _DEBUG

	DrawFormatString(0, 0, 0xffffff, "%d", stage_num);

#endif // !_DEBUG
}

//�N���A�����X�e�[�W��ۑ�
void SelectStage::SetGoalFlg(int stage_num)
{
	goal_flg[stage_num] = 1;
}