#include "GameClear.h"
#include "PadInput.h"
#include "Title.h"
#include "Result.h"

void GameClear::ImageLoad(int& _handle, const char* _file_name)
{
	try 
	{
		_handle = LoadGraph(_file_name);
		if(_handle == -1)
		{
			throw _file_name;
		}
	}
	catch (const char& err)
	{
		printf("%s������܂���B", &err);
	}
}

GameClear::GameClear(int _stage_num)
{
	//�J�b�g�C�����o�p�摜
	ImageLoad(cut_in01, "resource/images/GameClear/CutIn01.png");
	ImageLoad(cut_in02, "resource/images/GameClear/CutIn02.png");
	
	//�N���A�t�H���g�\��
	ImageLoad(stage_goal_image, "resource/font/StageClear.png");
	ImageLoad(boss_beat_image, "resource/font/BossStageClear.png");

	//�w�i�摜�p�ϐ�
	ImageLoad(clear_back_image, "resource/images/GameClear/GameClearImage.png");

	//�J�b�g�C��01�̍��W�ϐ�
	cut_in01_loc.x = 0.0f;			//X���W
	cut_in01_loc.y = 0.0f;			//Y���W

	//�J�b�g�C��02�̍��W�ϐ�
	cut_in02_loc.x = 0.0f;			//X���W
	cut_in02_loc.y = 0.0f;			//Y���W

	stage_num = _stage_num;			//stage�����i�[�p�ϐ�

	clear_font_alpha = 0;			//�N���A�摜�̃��l

	font_flg = false;				//�N���A�t�H���g�\���p�t���O
	scene_change_timer = 0;			//�V�[���J�ڃJ�E���g�p�^�C�}�[
}

GameClear::~GameClear()
{
}

AbstractScene* GameClear::Update()
{
	//------ �J�b�g�C�����o ------//
	//�J�b�g�C��01��X���W��300�ȉ����J�b�g�C��02��X���W��-300�ȏ�Ȃ�4��������
	if (cut_in01_loc.x >= -CUTIN_POS_TIMING && cut_in02_loc.x <= (CUTIN_POS_TIMING))
	{
		//�J�b�g�C���p�摜��X���W�𓮂���
		cut_in01_loc.x += -4.f;
		cut_in02_loc.x += 4.f;
	}
	//�J�b�g�C��01��X���W��300�ȏォ�J�b�g�C��02��X���W��-300�ȉ��Ȃ�30��������
	if (cut_in01_loc.x <= -CUTIN_POS_TIMING && cut_in02_loc.x >= (CUTIN_POS_TIMING))
	{
		//�J�b�g�C���p�摜��X���W�𓮂���
		cut_in01_loc.x += -90.f;
		cut_in02_loc.x += 90.f;
		if (cut_in01_loc.x <= -1280.f && cut_in02_loc.x >= 1280.f) { font_flg = true; }
	}

	//------ �V�[���J�ڏ��� ------//
	if (
#ifdef _DEBUG
		//�f�o�b�O���[�h�̊�A�{�^��/Enter�L�[�������Ɖ�ʑJ��
		PadInput::OnButton((XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN))
#else	
		//Release���[�h�Ȃ�A�{�^���ŉ�ʑJ��
		PadInput::OnButton(XINPUT_BUTTON_A)
#endif
		) 
	{
		//���U���g��ʂ֑J��
		return new Result();
	}
	//�V�[���؂�ւ��p�^�C�}�[��30���z������Result��ʂɐ؂�ւ�
	if (scene_change_timer >= 30) { return new Result; }

	//�t�H���g�\���p�t���O��On,Off�̐؂�ւ�����
	if (font_flg == true) { clear_font_alpha += 5; }
	//�t�H���g�\��������������^�C�}�[���N������
	if (clear_font_alpha >= 255) { scene_change_timer += 1; }

	return this;
}

void GameClear::Draw() const
{
	//�w�i�摜�\��
	DrawGraph(0, 0, clear_back_image, TRUE);

	//�J�b�g�C����ʕ\��
	DrawGraphF(cut_in01_loc.x, cut_in01_loc.y, cut_in01, TRUE);
	DrawGraphF(cut_in02_loc.x, cut_in02_loc.y, cut_in02, TRUE);

	//�����x�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, clear_font_alpha);
	//���݂̃X�e�[�W��Boss�X�e�[�W�ȊO�Ȃ�stage_goal_image��\��
	//���݂̃X�e�[�W��Boss�X�e�[�W�Ȃ�boss_beat_image��\��

	if (stage_num != 3) { DrawGraphF(250.f, 50.f, stage_goal_image, TRUE); }

	if (stage_num == 3) { DrawGraphF(250.f, 50.f, boss_beat_image, TRUE); }

	//�`��u�����h��NoBlend�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}