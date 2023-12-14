#include "GameOver.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Title.h"
#include "Score.h"
#include "SelectStage.h"
#include "GameMain.h"

//�摜�Ǎ��������p�֐�
void GameOver::ImageLoad(int& _handle,const char* _file_name)
{
	try 
	{
		_handle = LoadGraph(_file_name);
		if (_handle == -1)
		{
			throw _file_name;
		}
	}
	catch (const char &err)
	{
		printf("%s������܂���B", &err);
	}
}

GameOver::GameOver(int _stage_num)
{
	//�摜������(�J�n)
	ImageLoad(game_finish_font, "resource/font/GameFinishFont.png");
	ImageLoad(game_finish_select, "resource/font/GameFinishSelect.png");
	
	//�摜������(�I��)
	ImageLoad(game_continue_font, "resource/font/GameContinueFont.png");
	ImageLoad(game_continue_select, "resource/font/GameContinueSelect.png");
	
	//�摜������(���B���s)
	ImageLoad(goal_lose_image, "resource/font/StageLoseFont.png");
	
	//�摜������(�������s)
	ImageLoad(boss_stage_lose_image, "resource/font/PlayerLoseFont.png");
	
	//�w�i�摜������(Player���|��Ă���摜)
	ImageLoad(back_death_image, "resource/images/BackDeathImage.png");
	
	select_count = 0;
	once_flg = TRUE;

	//stage�����i�[�p�ϐ�
	stage_num = _stage_num;

	//�������p�ϐ�
	heading_alpha = 0.0f;
	choise_alpha = 0.0f;

	heading_y = 0.f;
}

GameOver::~GameOver()
{
}

AbstractScene* GameOver::Update()
{
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
		PadInput::OnButton(XINPUT_BUTTON_A)
#endif
		)
	{
		heading_alpha += 100.f;

		if (heading_y <= 80){ heading_y += 40; }
		
		choise_alpha += 20.f;
	}
	if (150 <= heading_alpha)
	{
		//L�X�e�B�b�N�����
		//���X�e�B�b�N�̌X�����Y���W��0.8�ȏォ��
		if (PadInput::TipLeftLStick(STICKL_Y) > 0.8f &&
			PadInput::TipLeftLStick(STICKL_Y) < 1.0f &&
			once_flg == TRUE)
		{
			once_flg = FALSE;
			select_count--;
			if (select_count < 0)select_count = 1;
		}
		//L�X�e�B�b�N�����
		if (PadInput::TipLeftLStick(STICKL_Y) > -1.0f &&
			PadInput::TipLeftLStick(STICKL_Y) < -0.8f &&
			once_flg == TRUE)
		{
			once_flg = FALSE;
			select_count--;
			if (select_count < 0)select_count = 1;
		}
		//L�X�e�B�b�N�����ɖ߂��ꂽ��Once�����Z�b�g
		if (once_flg == FALSE &&
			PadInput::TipLeftLStick(STICKL_Y) <= 0.1f &&
			PadInput::TipLeftLStick(STICKL_Y) >= -0.1f)
		{
			once_flg = TRUE;
		}
		if (
#ifdef _DEBUG
			PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
			PadInput::OnButton(XINPUT_BUTTON_A)
#endif
			)
		{
			switch (static_cast<GAME_OVER_MENU>(select_count))
			{
			case GAME_OVER_MENU::GAME_MAIN:
				//�X�R�A�̏�����
				Score::ResetScore();
				return new GameMain(stage_num);

			case GAME_OVER_MENU::GAME_SELECT:
				//�X�R�A�̏�����
				Score::ResetScore();
				return new SelectStage;

			}

		}
	}

	//------ �摜�����x�Ɋւ��鏈�� ------//

	//�^�C�g���摜��Y���W��350�ȉ��Ȃ�Y���W�ɉ��Z����
	if (heading_y <= 80.f) { heading_y += 0.25f; }

	//���o���摜�̃������ɉ��Z���s��
	heading_alpha += 1.f;

	//���o���摜�̃�������150���傫���Ȃ�����I���摜�̃������ɉ��Z���s��
	if (heading_alpha >= 150) { choise_alpha += 2.5f; }

	return this;
}

void GameOver::Draw() const
{
	//���o�������x�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)heading_alpha);
	//�w�i�摜�\��
	DrawGraph(0, 0, back_death_image, TRUE);

	//stage(�P�`�R)�Ŏ��S�����ꍇ�̉摜��\��
	if (stage_num != 3) { DrawGraphF(250, heading_y, goal_lose_image, TRUE); }

	//stage(Boss)�Ŏ��S�����ꍇ�̉摜��\��
	if (stage_num == 3) { DrawGraphF(250, heading_y, boss_stage_lose_image, TRUE); }

	//�����x�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
	if (heading_alpha >= 100)
	{
		//�I�����摜�ƃJ�[�\�������x�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)choise_alpha);

		//�����`��(���s)
		if (select_count == 0) { DrawGraph(530, 350, game_continue_select, TRUE); }

		if (select_count == 1) { DrawGraph(530, 350, game_continue_font, TRUE); }

		//�����`��(�I��)
		if (select_count == 0) { DrawGraph(530, 450, game_finish_font, TRUE); }

		if (select_count == 1) { DrawGraph(530, 450, game_finish_select, TRUE); }

		//�J�[�\���\��
		DrawTriangle(460, 380 + (select_count * 80), 460, 430 + (select_count * 80), 500, 405 + (select_count * 80), 0x000ff0, TRUE);
		//�`��u�����h��NoBlend�ɂ���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}