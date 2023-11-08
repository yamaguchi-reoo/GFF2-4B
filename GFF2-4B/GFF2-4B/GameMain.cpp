#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"
#include "StageData.h"
#include <fstream>
#include <iostream>
#include <string>
#include "EditScene.h"

static Location camera_location = { (SCREEN_WIDTH / 2),(SCREEN_HEIGHT / 2) };	//�J�����̍��W
Location screen_origin =		//�J�������W����X�N���[�����W�ւ̕ϊ�
{
	(SCREEN_WIDTH / 2),
	0
};
GameMain::GameMain(int _stage)
{
	now_stage = _stage;
	who = 1;
	player = new Player();
	scene_scroll = new SceneScroll();

	if (now_stage == 3) {
		hands = new BossHands(who);
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

	effect = new Effect();

	flg = false;
	onfloor_flg = false;

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
	//�G�f�B�b�g���[�h�Ɉڍs���鎞�ɃC���J���n�ʂɎh�����Ă���ƁAdelete�ŗ�O����������o�O���N�����Ă���̂ŁA�R�����g�A�E�g
	//for (int i = 0; i < IRUKA_MAX; i++)
	//{
	//	delete iruka[i];
	//}
	for (int i = 0; i < HIMAWARI_MAX; i++)
	{
		delete himawari[i];
	}
	delete powergauge;
	delete playerhp;
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
			zakuro[i]->Update(this);
			zakuro[i]->SetScreenPosition(camera_location);
		}
	}
	//�C���J
	for (int i = 0; i < IRUKA_MAX; i++)
	{
		if (iruka[i] != nullptr)
		{
			iruka[i]->Update(this);
			iruka[i]->SetScreenPosition(camera_location);
		}
	}
	//�Ђ܂��
	for (int i = 0; i < HIMAWARI_MAX; i++) 
	{
		if (himawari[i] != nullptr) 
		{
			himawari[i]->Update(this);
			himawari[i]->SetScreenPosition(camera_location);
		}
	}

	if (now_stage == 3) {
		hands->Update(this);
	}

	player->Update(this);
	player->SetScreenPosition(camera_location);
	powergauge->Update();
	playerhp->Update(player->GetPlayerHP());

	effect->Update();

	if (powergauge->PowerGaugeState() == 1)
	{
		//�����Q�[�WMAX��X�{�^���������ꂽ��v���C���[��������Ԃ�
		player->SetPowerUp();
	}
	else if(powergauge->PowerGaugeState() == 2)
	{
		//������ԉ���
		player->StopPowerUp();
		powergauge->SetPowerFlg(0);
	}

	if (effect->InitSplash() == 2)
	{
		for (int i = 0; i < ZAKURO_MAX; i++) {
			if (zakuro[i] != nullptr) {
				powergauge->SetVolume(zakuro[i]->GetColorDate());	
			}
		}
		effect->EndFlg(0);
	}
	//�Ђ܂�����
	for (int i = 0; i < HIMAWARI_MAX; i++)
	{
		if (himawari[i] != nullptr)
		{
			if (himawari[i]->GetLocation().x <= player->GetLocation().x	) {
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

	}

		//�{�X�̘r
		if (now_stage == 3) {
			if (attack[i]->GetAttackData().who_attack == hands->GetWho())
			{
				attack[i]->Update(hands->GetCenterLocation(), hands->GetErea());
			}
		}
	}


	//���̐������J��Ԃ�
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			stage[i][j]->Update();
			stage[i][j]->SetScreenPosition(camera_location);
		}
	}
	//�����蔻��֘A�̏������s��
	HitCheck();

#if DEBUG
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
		hands = new BossHands(who);
	}
#endif

	return this;
}

void GameMain::Draw() const
{
	effect->Draw();
	
	SetFontSize(42);
//	DrawString(400, 0, "GameMain", 0xffffff);
	//�`��
	player->Draw();

	if (now_stage == 3) {
		hands->Draw();
	}

	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			stage[i][j]->Draw();
		}
	}
	if (flg == true) {
		//DrawString(300, 300,"flg", 0xffffff);
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
			if (player->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
			{
				//�G�ꂽ�ʂɉ����ĉ����o��
				player->Push(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
			}

			if (now_stage == 3) {
				if (hands->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
				{
					hands->hitflg = true;
				}
			}

			for (int k = 0; k < ZAKURO_MAX; k++)
			{
				if (zakuro[k] != nullptr) {
					if (zakuro[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
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
					if (iruka[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0) 
					{
						iruka[k]->IrukaPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
					}
				}
			}
			//�Ђ܂��
			for (int k = 0; k < HIMAWARI_MAX; k++)
			{
				if (himawari[k] != nullptr) {
					if (himawari[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
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
					effect->HitFlg(true);
					effect->SetLocation(zakuro[j]->GetCenterLocation());
					//powergauge->SetVolume(zakuro[j]->GetColorDate());
				}
			}
		 }
		for (int j = 0; j < IRUKA_MAX; j++) {
			if (iruka[j] != nullptr) {
				// �U���̔��肪�C���J�Ɣ���Ă��āA���̍U�����v���C���[�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
				if (attack[i]->HitBox(iruka[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && iruka[j]->GetSpwanFlg() == false)
				{
					//���Ԃ��p
					effect->HitFlg(true);
					//effect->SetLocation(zakuro->GetCenterLocation());

					//�C���J�̃_���[�W����
					iruka[j]->ApplyDamage(attack[i]->GetAttackData().damage);
					if (iruka[j]->GetHp() < 1) {
						powergauge->SetVolume(iruka[j]->GetColorDate());
					}
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
					effect->HitFlg(true);
					//effect->SetLocation(zakuro->GetCenterLocation());

					//�Ђ܂��̃_���[�W����
					himawari[j]->ApplyDamage(attack[i]->GetAttackData().damage);
					//if (himawari[j]->GetHp() < 1) {
						powergauge->SetVolume(himawari[j]->GetColorDate());
					//}
					attack[i]->DeleteAttack();
				}
			}
		}

		if (now_stage == 3) {
			if (hands != nullptr) {
				if (attack[i]->HitBox(hands) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true)
				{
					//�{�X�̃_���[�W����
					hands->ApplyDamage(attack[i]->GetAttackData().damage);
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
}

void GameMain::LoadStageData(int _stage)
{
	const char* a = "resource/dat/1stStageData.txt";
	switch(_stage)
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
	CameraLocation(screen_origin);
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
			switch (STAGE_DATA[i][j])
			{
				//�X�e�[�W���u���b�N�𐶐�
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, STAGE_DATA[i][j]);
				break;
				//�U�N���𐶐�
			case 5:
				stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, 0);
				//�󂢂Ă�g�ɐ���
				for (int k = 0; k < ZAKURO_MAX; k++)
				{
					if (zakuro[k] == nullptr)
					{
						zakuro[k] = new Zakuro(j * BOX_WIDTH, i * BOX_HEIGHT, true,who++);
						break;
					}
				}
				break;
				//�C���J�𐶐�
			case 6:
				stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, 0);
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
				stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, 0);
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
			}
		}
	}
	//�v���C���[�̃��X�|�[��
	Location res_location = { 100,100 };
	player->Respawn(res_location);
}
void GameMain::CameraLocation(Location _location)
{
	camera_location.x = _location.x - (SCREEN_WIDTH / 2);
	camera_location.y = 0;
}