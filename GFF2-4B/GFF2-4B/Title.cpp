#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"
#include "SelectStage.h"

Title::Title()
{
	//������
	Select = 0;
	Once = TRUE;

}

Title::~Title()
{

}

AbstractScene* Title::Update()
{
	//�\���L�[������
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_DPAD_UP) || KeyInput::OnKey(KEY_INPUT_W)
#else
		PadInput::OnButton(XINPUT_BUTTON_DPAD_UP)
#endif
		)
	{
		Select--;
		if (Select <= -1)Select = 1;
	}
	//�\���L�[������
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_DPAD_DOWN) || KeyInput::OnKey(KEY_INPUT_S)
#else
		PadInput::OnButton(XINPUT_BUTTON_DPAD_DOWN)
#endif
		)
	{
		Select++;
		if (Select > 1)Select = 0;
	}

	//L�X�e�B�b�N�����
	if (PadInput::TipLeftLStick(STICKL_Y) > 0.8f && 
		PadInput::TipLeftLStick(STICKL_Y) < 1.0f &&
		Once == TRUE)
	{
		Once = FALSE;
		Select--;
		if (Select < 0)Select = 1;
	}

	//L�X�e�B�b�N������
	if (PadInput::TipLeftLStick(STICKL_Y) > -1.f && 
		PadInput::TipLeftLStick(STICKL_Y) < -0.8f && 
		Once == TRUE)
	{
		Once = FALSE;
		Select++;
		if (Select > 1)Select = 0;
	}

	//L�X�e�B�b�N�����ɖ߂��ꂽ��Once�����Z�b�g
	if (Once == FALSE && 
		PadInput::TipLeftLStick(STICKL_Y) <= 0.1f &&
		PadInput::TipLeftLStick(STICKL_Y) >= -0.1f)
	{
		Once = TRUE;
	}
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
		PadInput::OnButton(XINPUT_BUTTON_A)
#endif
		)
	{
		switch (static_cast<TITLE_MENU>(Select))
		{
			//�Q�[����ʂ�
		case TITLE_MENU::GAME_START:

			return new SelectStage();
			//�G���h��ʂ�
		case TITLE_MENU::GAME_END:
			
			return nullptr;
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
