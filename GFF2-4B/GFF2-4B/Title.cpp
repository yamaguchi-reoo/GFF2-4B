#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"
#include "SelectStage.h"

//�摜�Ǎ��������p�֐�
void Title::ImageLoad(int& _handle, const char* _file_name)
{
	try
	{
		_handle = LoadGraph(_file_name);
		if (_handle == -1)
		{
			throw _file_name;
		}
	}
	catch (const char& err)
	{
		printf("%s������܂���B", &err);
	}
}

Title::Title()
{
	//������
	Select = 0;
	Once = TRUE;
	title_alpha = 0;
	title_x = 0;
	font_alpha = 0;

	//�����摜������(�S)
	ImageLoad(title_font, "resource/font/TitleFont.png");

	//�摜������(�J�n)
	ImageLoad(game_start_image, "resource/font/GameStartFont.png");
	ImageLoad(game_start_select, "resource/font/GameStartSelect.png");
	//�摜������(�I��)
	ImageLoad(game_finish_image, "resource/font/GameFinishFont.png");
	ImageLoad(game_finish_select, "resource/font/GameFinishSelect.png");
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
	if (title_x <= 100) { title_x += 1; }
	title_alpha += 1;
	if(title_alpha >= 150){ font_alpha += 2.5; }
	return this;
}

void Title::Draw()const
{
	//�����x�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_alpha);
	//�^�C�g���摜�\��
	DrawGraph(title_x, 25, title_font, TRUE);
	//�����x�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/***** �I���摜�`�� *****/
	if (title_x >= 100)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, font_alpha);
		//�����`��(�J�n)
		if (Select == 0) { DrawGraph(850, 495, game_start_select, TRUE); }
		if (Select == 1) { DrawGraph(850, 495, game_start_image, TRUE); }
		//�����`��(�I��)
		if (Select == 0) { DrawGraph(850, 575, game_finish_image, TRUE); }
		if (Select == 1) { DrawGraph(850, 575, game_finish_select, TRUE); }
		//�J�[�\���̕\��
		DrawTriangle(790, 500 + (Select * 90), 820, 520 + (Select * 90), 790, 540 + (Select * 90), 0xff0000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}
