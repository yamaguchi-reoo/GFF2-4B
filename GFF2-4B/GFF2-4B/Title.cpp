#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"
#include "SelectStage.h"

Title::Title()
{
	//������
	Select = 1;
	Once = TRUE;

}

Title::~Title()
{

}

AbstractScene* Title::Update()
{
	//�\���L�[������
	if (PadInput::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		Select--;
		if (Select < 0)Select = 1;
	}
	//�\���L�[������
	if (PadInput::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		Select++;
		if (Select > 1)Select = 0;
	}

	//L�X�e�B�b�N�����
	if (PadInput::TipLeftLStick(STICKL_X) <= 1 && Once == TRUE)
	{
		Select--;
		if (Select < 0)Select = 1;
		Once = FALSE;
	}

	//L�X�e�B�b�N������
	if (PadInput::TipLeftLStick(STICKL_X) >= -1 && Once == TRUE)
	{
		Select++;
		if (Select > 1)Select = 0;
		Once = FALSE;
	}

	//L�X�e�B�b�N�����ɖ߂��ꂽ��Once�����Z�b�g
	if (Once == FALSE && PadInput::TipLeftLStick(STICKL_X) >= 1 && PadInput::TipLeftLStick(STICKL_X) <= -1)
	{
		Once = TRUE;
	}

	if (PadInput::OnButton(XINPUT_BUTTON_A))
	{
		switch (static_cast<TITLE_MENU>(Select))
		{
			//�Q�[����ʂ�
		case TITLE_MENU::GAME_START:

			return new SelectStage();
			//�G���h��ʂ�
		case TITLE_MENU::GAME_END:

			//return new End();
			//StopSoundMem(TitleBGM);
			break;
		default:
			break;
		}
	}
	return this;
}

void Title::Draw()const
{
	DrawString(150, 100, "�S", 0xffffff);

	//���j���[�̕`��
	DrawString(730, 260, "�J�n", 0xffffff);
	//DrawString(730, 320, "�w���v", 0xffffff);
	DrawString(730, 340/*400*/, "�I��", 0xffffff);
	//DrawFormatString(730, 410/*400*/,0x00ff00, "%d",Select);


	////�J�[�\���̕`��
	//int select_y = 230 + Select * 80;
	//�J�[�\���\��
	DrawTriangle(670, 245 + Select * 80, 700, 265 + Select * 80, 670, 285 + Select * 80, 0xff0000, TRUE);
}
