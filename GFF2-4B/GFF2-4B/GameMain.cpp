#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"
#include "StageData.h"
#include <fstream>
#include <iostream>
#include <string>
#include "EditScene.h"
#include "GameClear.h"
#include "GameOver.h"

static Location camera_location = { (SCREEN_WIDTH / 2),(SCREEN_HEIGHT / 2) };	//�J�����̍��W
static Location screen_origin =	{(SCREEN_WIDTH / 2),0};
GameMain::GameMain(int _stage)
{
	now_stage = _stage;
	who = 1;
	player = new Player();
	scene_scroll = new SceneScroll();

	if (now_stage == 3) {
		hands = new BossHands(who++,boss);
		boss = new Boss();

	}
	SetStage(now_stage);
	for (int i = 0; i < 2; i++)
	{
		count[i] = 0;
	}
	for (int i = 0; i < BAMBOO_NUM; i++) {
		bamboo[i] = new Bamboo(i * 60);
	}

	powergauge = new PowerGauge();

	playerhp = new PlayerHP();

	score = new Score();

	effect = new Effect();

	flg = false;
	onfloor_flg = false;

	Hands_Delete_Flg = false;
}

GameMain::~GameMain()
{
	delete player;
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			delete stage[i][j];
		}
	}
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		delete attack[i];
	}
	for (int i = 0; i < ZAKURO_MAX; i++)
	{
		delete zakuro[i];
	}
#ifdef _DEBUG
	//�G�f�B�b�g���[�h�Ɉڍs���鎞�ɃC���J���n�ʂɎh�����Ă���ƁA
	//delete�ŗ�O����������o�O���N�����Ă���̂ŁA�G�f�B�b�g�̏o����f�o�b�O���[�h�ł͎��s���Ȃ��悤��
#else
	for (int i = 0; i < IRUKA_MAX; i++)
	{
		delete iruka[i];
	}
#endif
	for (int i = 0; i < HIMAWARI_MAX; i++)
	{
		delete himawari[i];
	}
	delete powergauge;
	delete playerhp;
	delete score;
	delete effect;
}

AbstractScene* GameMain::Update()
{
	//�X�V
	if (player->GetLocation().x > (SCREEN_WIDTH / 2) && player->GetLocation().x < stage_width - (SCREEN_WIDTH / 2) && now_stage != 3)
	{
		CameraLocation(player->GetLocation());
	}
	//�U�N��
	for (int i = 0; i < ZAKURO_MAX; i++)
	{
		if (zakuro[i] != nullptr)
		{
			zakuro[i]->SetScreenPosition(camera_location);

			if (zakuro[i]->GetLocaLocationX() <= screen_origin.x + (SCREEN_WIDTH / 2) && zakuro[i]->GetLocaLocationX() >= screen_origin.x - (SCREEN_WIDTH / 2)) {
				zakuro[i]->Update(this);
			}
			
		}
	}
	//�C���J
	for (int i = 0; i < IRUKA_MAX; i++)
	{
		if (iruka[i] != nullptr)
		{
			iruka[i]->SetScreenPosition(camera_location);
			if (iruka[i]->GetLocaLocationX() <= screen_origin.x + (SCREEN_WIDTH / 2) && iruka[i]->GetLocaLocationX() >= screen_origin.x - (SCREEN_WIDTH / 2)) {
				iruka[i]->Update(this);
			}
			
		}
	}
	//�Ђ܂��
	for (int i = 0; i < HIMAWARI_MAX; i++)
	{
		if (himawari[i] != nullptr)
		{
			himawari[i]->SetScreenPosition(camera_location);
			if (himawari[i]->GetLocaLocationX() <= screen_origin.x + (SCREEN_WIDTH / 2) && himawari[i]->GetLocaLocationX() >= screen_origin.x - (SCREEN_WIDTH / 2)) {
				himawari[i]->Update(this);
			}
		}
	}

	//�{�X�̘r�A�b�v�f�[�g
	if (now_stage == 3) {
		if (hands != nullptr) {
			hands->Update(this);
			//�␶��
			if (hands->Rock_Once == true) {
				hands->Rock_Once = false;
				if (hands->switching == 3) {
					rock[0] = new Rock(who++, 2);
					rock[1] = new Rock(who++, 3);
				}
				else {
					rock[0] = new Rock(who++, hands->switching);
				}

			}


		}
		
		//��A�b�v�f�[�g

			for (int i = 0; i < 2; i++) {
				if (rock[i] != nullptr) {
					rock[i]->Update(this);
					if (rock[i]->Rock_Delete == true) {
						rock[i] = nullptr;
					}
				}
			}
		

	}

	player->Update(this);
	player->SetScreenPosition(camera_location);
	
	powergauge->Update(this);
	powergauge->SetScreenPosition(camera_location);

	playerhp->Update(player->GetPlayerHP());

	score->Update();

	effect->Update(this);
	effect->SetScreenPosition(camera_location);

	if (powergauge->PowerGaugeState() == 1)
	{
		//�����Q�[�WMAX��X�{�^���������ꂽ��v���C���[��������Ԃ�
		player->SetPowerUp();
	}
	else if (powergauge->PowerGaugeState() == 2)
	{
		//������ԉ���
		player->StopPowerUp();
		powergauge->SetPowerFlg(0);
	}

	//�Ђ܂�����
	for (int i = 0; i < HIMAWARI_MAX; i++)
	{
		if (himawari[i] != nullptr)
		{
			if (himawari[i]->GetLocation().x <= player->GetLocation().x) {
				himawari[i]->ReverseDirection();

			}
			if (himawari[i]->GetLocation().x >= player->GetLocation().x) {
				himawari[i]->ObverseDirection();

			}
		}
	}

	//�C���J��������
	for (int i = 0; i < IRUKA_MAX; i++)
	{
		if (iruka[i] != nullptr)
		{
			if (iruka[i]->GetLocation().x <= player->GetLocation().x + 30 && iruka[i]->GetLocation().x + 30 >= player->GetLocation().x)
			{
				iruka[i]->SetFallFlg();
			}
		}
	}

	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//�N���U���������ɂ���čU���̔��肪���Ă����Ώۂ�ς���
		if (attack[i]->GetAttackData().who_attack == player->GetWho())
		{
			attack[i]->Update(player->GetCenterLocation(), player->GetErea());
			attack[i]->SetScreenPosition(camera_location);
		}
		//�U�N��
		for (int j = 0; j < ZAKURO_MAX; j++)
		{
			if (zakuro[j] != nullptr) {
				if (attack[i]->GetAttackData().who_attack == zakuro[j]->GetWho())
				{
					attack[i]->Update(zakuro[j]->GetCenterLocation(), zakuro[j]->GetErea());
					attack[i]->SetScreenPosition(camera_location);
				}
			}
		}
		//�C���J
		for (int j = 0; j < IRUKA_MAX; j++)
		{
			if (iruka[j] != nullptr)
			{
				if (attack[i]->GetAttackData().who_attack == iruka[j]->GetWho())
				{
					attack[i]->Update(iruka[j]->GetCenterLocation(), iruka[j]->GetErea());
					attack[i]->SetScreenPosition(camera_location);
				}
			}
		}
		//�Ђ܂��
		for (int j = 0; j < HIMAWARI_MAX; j++)
		{
			if (himawari[j] != nullptr)
			{
				if (attack[i]->GetAttackData().who_attack == himawari[j]->GetWho())
				{
					attack[i]->Update(himawari[j]->GetCenterLocation(), himawari[j]->GetErea());
					attack[i]->SetScreenPosition(camera_location);
				}
			}
		}

		////�{�X�̘r
		//if (now_stage == 3) {
		//	//if (hands != nullptr) {
		//	//	if (attack[i]->GetAttackData().who_attack == hands->GetWho())
		//	//	{
		//	//		attack[i]->Update(hands->GetCenterLocation(), hands->GetErea());
		//	//	}
		//	//}
		//}

		//�{�X�̘r
		if (now_stage == 3) {
			if (hands != nullptr) {
				if (attack[i]->GetAttackData().who_attack == hands->GetWho())
				{
					attack[i]->Update(hands->GetCenterLocation(), hands->GetErea());
					attack[i]->SetScreenPosition(camera_location);

				}

			}
				//��
				for (int j = 0; j < 2; j++) {
					if (rock[j] != nullptr) {
						if (attack[i]->GetAttackData().who_attack == rock[j]->GetWho())
						{
							attack[i]->Update(rock[j]->GetCenterLocation(), rock[j]->GetErea());
							attack[i]->SetScreenPosition(camera_location);
							if (hands->Death_Flg == true) {
								//boss->Count_Death--;
								attack[i]->DeleteAttack();
								//hands = nullptr;
							}
						}
					}
				}
			
		}

	}

	if (effect->GetFlg() == 2)
	{
		powergauge->SetVolume(effect->GetSplashColor());
		effect->SetFlg(0);
	}
	
	//���̐������J��Ԃ�
	for(int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			stage[i][j]->Update();
			stage[i][j]->SetScreenPosition(camera_location);
		}
	}

	//�����蔻��֘A�̏������s��
	HitCheck();

	if (powergauge->GetColorRem() > 0)
	{
		score->AddScore(powergauge->GetColorRem());
		powergauge->SetColorRem(0);
	}

	//�X�e�[�W�N���A
	if (player->GetLocation().x > stage_width - (stage_width * STAGE_GOAL)) {
		return new GameClear();
	}
	if (player->GetPlayerHP() < 0) {
		return new GameOver();
	}

#ifdef _DEBUG
	//�X�e�[�W�J��
	if (KeyInput::OnPresed(KEY_INPUT_0))
	{
		SetStage(0);
	}
	if (KeyInput::OnPresed(KEY_INPUT_1))
	{
		SetStage(1);
	}
	if (KeyInput::OnPresed(KEY_INPUT_2))
	{
		SetStage(2);
	}
	if (KeyInput::OnPresed(KEY_INPUT_3))
	{
		SetStage(3);
	}

	//�X�e�[�W�I����ʂ֑J��
	if (KeyInput::OnPresed(KEY_INPUT_4))
	{
		return new SelectStage();
	}
	//�v���C���[�ɋ����_���[�W
	if (KeyInput::OnKey(KEY_INPUT_S))
	{
		flg = true;
		player->ApplyDamage(1);
	}
	//�X�e�[�W��������V�[���֑J��
	if (KeyInput::OnPresed(KEY_INPUT_E) && KeyInput::OnPresed(KEY_INPUT_D))
	{
		return new EditScene(now_stage);
	}

	//�r���ŃX�e�[�W�̐؂�ւ����������ꍇ�g�p
	if (now_stage == 3 && old_stage!=now_stage) {
		//Hands_Delete_Flg = false;
		boss = new Boss();
		hands = new BossHands(who++, boss);
	}
#endif



	return this;
}

void GameMain::Draw() const
{
	DrawBox(0, 0, 1280, 720, 0xbdbdbd, true);
	effect->Draw();

	SetFontSize(42);
	//	DrawString(400, 0, "GameMain", 0xffffff);
		//�`��
	player->Draw();

	//�{�X�̘r�\��
	if (now_stage == 3) {
		if (boss != nullptr) {
			boss->Draw();
		}
		if (hands != nullptr) {
			hands->Draw();
		}

			for (int i = 0; i < 2; i++) {
				if (rock[i] != nullptr) {
					rock[i]->Draw();
				}
			}
	}
	


	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			stage[i][j]->Draw();
		}
	}
	//�G�l�~�[�̕`��
	// �U�N��
	for (int i = 0; i < ZAKURO_MAX; i++)
	{
		if (zakuro[i] != nullptr)
		{
			zakuro[i]->Draw();
		}
	}
	// �Ђ܂��
	for (int i = 0; i < HIMAWARI_MAX; i++)
	{
		if (himawari[i] != nullptr)
		{
			himawari[i]->Draw();
		}
	}
	// �C���J
	for (int i = 0; i < IRUKA_MAX; i++)
	{
		if (iruka[i] != nullptr)
		{
			iruka[i]->Draw();
		}
	}


	/*for (int i = 0; i < BAMBOO_NUM; i++) {
		bamboo[i]->Draw();
	}*/

	powergauge->Draw();
	playerhp->Draw();
	score->Draw();
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		attack[i]->Draw();
	}
}

void GameMain::SpawnAttack(AttackData _attackdata)
{
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		if (attack[i]->GetAttackFlg() == false)
		{
			attack[i]->SpawnAttack(_attackdata);
			break;
		}
	}
}

void GameMain::HitCheck()
{
	//���̐������J��Ԃ�
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			if (player->HitBox(stage[i][j]) == true && stage[i][j]->GetStageCollisionType() != 0)
			{
				//�G�ꂽ�ʂɉ����ĉ����o��
				player->Push(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea(),stage[i][j]->GetStageCollisionType());
			}

			if (now_stage == 3) {
				if (hands != nullptr) {
					if (hands->HitBox(stage[i][j]) == true && stage[i][j]->GetStageCollisionType() != 0)
					{
						hands->hitflg = true;
					}
				}
			}

			for (int k = 0; k < ZAKURO_MAX; k++)
			{
				if (zakuro[k] != nullptr) {
					if (zakuro[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageCollisionType() != 0)
					{
						//�G�ꂽ�ʂɉ����ĉ����o��
						zakuro[k]->ZakuroPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
					}
				}
			}
			//�C���J
			for (int k = 0; k < IRUKA_MAX; k++)
			{
				if (iruka[k] != nullptr) {
					if (iruka[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageCollisionType() != 0)
					{
						iruka[k]->IrukaPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
					}
				}
			}
			//�Ђ܂��
			for (int k = 0; k < HIMAWARI_MAX; k++)
			{
				if (himawari[k] != nullptr) {
					if (himawari[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageCollisionType() != 0)
					{
						himawari[k]->HimawariPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
					}
				}
			}
		}
	}
	//�U���̐������J��Ԃ�
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		for (int j = 0; j < ZAKURO_MAX; j++)
		{
			if (zakuro[j] != nullptr) {
				//�U���̔��肪�U�N���Ɣ���Ă��āA���̍U�����v���C���[�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
				if (attack[i]->HitBox(zakuro[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && zakuro[j]->GetSpwanFlg() == false)
				{
					//�U�N���̃_���[�W����
					zakuro[j]->ApplyDamage(attack[i]->GetAttackData().damage);
					attack[i]->DeleteAttack();

					//���Ԃ��p
					effect->SetFlg(1);
					effect->SetGaugeLocation(powergauge->GetCenterLocation());
					effect->SetLocation(zakuro[j]->GetLocalLocation());
					effect->SetSplashColor(zakuro[j]->GetColorDate());
				}
			}
		}
		for (int j = 0; j < IRUKA_MAX; j++) {
			if (iruka[j] != nullptr) {
				// �U���̔��肪�C���J�Ɣ���Ă��āA���̍U�����v���C���[�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
				if (attack[i]->HitBox(iruka[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && iruka[j]->GetSpwanFlg() == false)
				{
					//���Ԃ��p
					effect->SetFlg(1);
					effect->SetGaugeLocation(powergauge->GetCenterLocation());
					effect->SetLocation(iruka[j]->GetLocalLocation());
					effect->SetSplashColor(iruka[j]->GetColorDate());

					//�C���J�̃_���[�W����
					iruka[j]->ApplyDamage(attack[i]->GetAttackData().damage);
					/*if (iruka[j]->GetHp() < 1) {
						powergauge->SetVolume(iruka[j]->GetColorDate());
					}*/
					attack[i]->DeleteAttack();
				}
			}
		}
		for (int j = 0; j < HIMAWARI_MAX; j++) {
			if (himawari[j] != nullptr) {
				// �U���̔��肪	�Ђ܂��Ɣ���Ă��āA���̍U�����v���C���[�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
				if (attack[i]->HitBox(himawari[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && himawari[j]->GetSpwanFlg() == false)
				{
					//���Ԃ��p
					effect->SetFlg(1);
					effect->SetGaugeLocation(powergauge->GetCenterLocation());
					effect->SetLocation(himawari[j]->GetLocalLocation());
					effect->SetSplashColor(himawari[j]->GetColorDate());

					//�Ђ܂��̃_���[�W����
					himawari[j]->ApplyDamage(attack[i]->GetAttackData().damage);
					//if (himawari[j]->GetHp() < 1) {
					//powergauge->SetVolume(himawari[j]->GetColorDate());
					//}
					attack[i]->DeleteAttack();
				}

			}
		}

		if (now_stage == 3) {
			if (hands != nullptr) {
				if (attack[i]->HitBox(hands) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && hands->Death_Flg == false)
				{

					//�{�X�̃_���[�W����
					hands->ApplyDamage(attack[i]->GetAttackData().damage);
					attack[i]->DeleteAttack();
					//�W�����v�U�����i�h�~
					if (player->GetAcs(0) > 0.1) {
						hands->HitJumpAttack = true;
					}
					else {
						hands->HitJumpAttack = false;
					}
				}
				if (hands->Death_Flg == true) {
					attack[i]->DeleteAttack();

				}

			}
		}
		
	

		//�U���̔��肪�v���C���[�Ɣ���Ă��āA���̍U�����G�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
		if (attack[i]->HitBox(player) == true && attack[i]->GetAttackData().who_attack != PLAYER && attack[i]->GetCanApplyDamage() == true)
		{
			//�v���C���[�̃_���[�W����
			player->ApplyDamage(attack[i]->GetAttackData().damage);
			attack[i]->DeleteAttack();
			//zakuro->Stop_Attack();
		}

	}
	//�U�N�����m�œ���������...
	for (int i = 0; i < ZAKURO_MAX; i++)
	{
		for (int j = i + 1; j < ZAKURO_MAX; j++)
		{
			if (zakuro[i] != nullptr && zakuro[j] != nullptr)
			{
				if (zakuro[i]->HitBox(zakuro[j]) == true) {
					zakuro[i]->HitZakuro();
				}
				if (zakuro[j]->HitBox(zakuro[i]) == true) {
					zakuro[j]->HitZakuro();
				}
			}
		}
	}


	//�r�����񂾏ꍇ
	if (hands != nullptr) {
		if (Hands_Delete_Flg==true) {
			
			boss->Count_Death--;
			hands = nullptr;
		}
	}

}

void GameMain::LoadStageData(int _stage)
{
	const char* a = "resource/dat/1stStageData.txt";
	switch (_stage)
	{
	case 0:
		a = "resource/dat/1stStageData.txt";
		break;
	case 1:
		a = "resource/dat/2ndStageData.txt";
		break;
	case 2:
		a = "resource/dat/3rdStageData.txt";
		break;
	case 3:
		a = "resource/dat/BossStageData.txt";
		break;
	}

	std::ifstream file(a);
	//�t�@�C�����ǂݍ��߂Ă����Ȃ�
	if (file)
	{
		file >> stage_width_num;
		file >> stage_height_num;

		stage_width = stage_width_num * BOX_WIDTH;
		//�����L���O�f�[�^�z����f�[�^��ǂݍ���
		for (int i = 0; i < stage_height_num; i++)
		{
			for (int j = 0; j < stage_width_num; j++)
			{
				file >> STAGE_DATA[i][j];
			}
		}
	}
}

void GameMain::SetStage(int _stage)
{
	//�G�ƍU�������Z�b�g
	for (int i = 0; i < ZAKURO_MAX; i++) {
		zakuro[i] = nullptr;
	}
	for (int i = 0; i < IRUKA_MAX; i++) {
		iruka[i] = nullptr;
	}
	for (int i = 0; i < HIMAWARI_MAX; i++) {
		himawari[i] = nullptr;
	}
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		attack[i] = new Attack();
	}
	old_stage = now_stage;
	now_stage = _stage;
	//�t�@�C���̓Ǎ�
	LoadStageData(now_stage);
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			//�X�e�[�W���u���b�N�𐶐�
			stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, STAGE_DATA[i][j]);
			switch (STAGE_DATA[i][j])
			{
			//�U�N���𐶐�
			case 5:
				//�󂢂Ă�g�ɐ���
				for (int k = 0; k < ZAKURO_MAX; k++)
				{
					if (zakuro[k] == nullptr)
					{
						zakuro[k] = new Zakuro(j * BOX_WIDTH, i * BOX_HEIGHT, true, who++);
						break;
					}
				}
				break;
				//�C���J�𐶐�
			case 6:
				//�󂢂Ă�g�ɐ���
				for (int k = 0; k < IRUKA_MAX; k++)
				{
					if (iruka[k] == nullptr)
					{
						iruka[k] = new Iruka(j * BOX_WIDTH, i * BOX_HEIGHT, true, who++);
						break;
					}
				}
				break;
				//�Ђ܂��𐶐�
			case 7:
				//�󂢂Ă�g�ɐ���
				for (int k = 0; k < HIMAWARI_MAX; k++)
				{
					if (himawari[k] == nullptr)
					{
						himawari[k] = new Himawari(j * BOX_WIDTH, i * BOX_HEIGHT, true, who++);
						break;
					}
				}
				break;
			default:
				break;
			}
		}
	}
	//�v���C���[�̃��X�|�[��
	Location res_location = { 100,100 };
	player->Respawn(res_location);
	//�J�����̃��Z�b�g
	ResetCamera();
}

void GameMain::CameraLocation(Location _location)
{
	camera_location.x = _location.x - (SCREEN_WIDTH / 2);
	camera_location.y = 0;
}

void GameMain::ResetCamera()
{
	camera_location.x = screen_origin.x - (SCREEN_WIDTH / 2);
	camera_location.y = screen_origin.y;
}