#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"
#include "StageData.h"
#include <fstream>
#include <iostream>
#include <string>
#include "EditScene.h"

GameMain::GameMain()
{
	player = new Player();
	scene_scroll = new SceneScroll();
	CreateStage();
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, STAGE_DATA[i][j]);
		}
	}
	zakuro = new Zakuro();
	himawari = new Himawari();
	iruka = new Iruka();
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		attack[i] = new Attack();
	}
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
	delete scene_scroll;
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			delete stage[i][j];
		}
	}
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		delete attack[i];
	}
	delete zakuro;
	delete himawari;
	delete iruka;
	delete powergauge;
	delete playerhp;
	delete effect;
}

AbstractScene* GameMain::Update()
{
	//�X�V
	if (player->GetLocation().x <= SCREEN_LEFT_END)
	{
		player->GetLocation().x + 0.01;
	}
	scene_scroll->Update(player->GetLocation(), player->GetAcs(2), player->GetAcs(3));
	if(scene_scroll->ActionRangeBorder(player->GetLocation()) == true)
	{
		player->ForciblyMovePlayer(scene_scroll->PlayerScroll(player->GetLocation()));
	}
	zakuro->Update(this);
	iruka->Update(this);
	player->Update(this);
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
		powergauge->SetVolume(zakuro->GetColorDate());
		effect->EndFlg(0);

	}

	//�C���J��������
	if (iruka->GetLocation().x <= player->GetLocation().x+30 && iruka->GetLocation().x + 30 >= player->GetLocation().x) {
		iruka->SetFallFlg();
	}
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//�N���U���������ɂ���čU���̔��肪���Ă����Ώۂ�ς���
		if (attack[i]->GetAttackData().who_attack == player->GetWho())
		{
			attack[i]->Update(player->GetCenterLocation(), player->GetErea());
		}
		/*************************************************************************************************
		* �V�����G�𐶐����邽�тɁAwho�̕ϐ���1�A�Q�A3�Ɛ���������U���Ă���(���Ȃ��Ł@�O�̓v���C���[)�A
		* �U���𐶐�����Ƃ��ɂ��̒l��attack_data.who_attack�Ɋi�[���A
		* �����ŉ�ʓ��̓G�̎�ޕ�����if�����A�P��ނ̓G�̐�����for�ŌJ��Ԃ�
		* who��BoxCollider�Œ�`�ς�
		* 
		*	for(int j = 0; j < (��ʓ��̃U�N���̐��������Ă���ϐ�); j++ )
		*	{
		*		if (attack[j]->GetAttackData().who_attack == zakuro[j]->GetWho())
		*		{
		*			attack[j]->Update(zakuro[j]->GetCenterLocation(), zakuro[j]->GetErea());
		*		}
		*	}
		* 
		* 	for(int j = 0; j < (��ʓ��̂Ђ܂��̐��������Ă���ϐ�); j++ )
		*	{
		*		if (attack[j]->GetAttackData().who_attack == himawari[j]->GetWho())
		*		{
		*			attack[j]->Update(himawari[j]->GetCenterLocation(), himawari[j]->GetErea());
		*		}
		*	}
		* 
		* �@for(int i = 0; i < (��ʓ��̂��邩�̐��������Ă���ϐ�); i++ )
		*	{
		*		if (attack[j]->GetAttackData().who_attack == iruka[j]->GetWho())
		*		{
		*			attack[j]->Update(iruka[j]->GetCenterLocation(),iruka[j]->GetErea());
		*		}
		*	}
		*********************************************************************************************/

		//for (int j = 0; j < (1); j++)
		//	 {
			if (attack[i]->GetAttackData().who_attack == zakuro->GetWho())
			{
				attack[i]->Update(zakuro->GetCenterLocation(), zakuro->GetErea());
			}
			if (attack[i]->GetAttackData().who_attack == iruka->GetWho())
			{
				attack[i]->Update(iruka->GetCenterLocation(), iruka->GetErea());
			}
			
		/*}*/
	}
	//���̐������J��Ԃ�
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			stage[i][j]->Update();
		}
	}
	//�����蔻��֘A�̏������s��
	HitCheck();

#if DEBUG
	if (KeyInput::OnKey(KEY_INPUT_S)) 
	{
		flg = true;
		player->ApplyDamage(1);
	}
	//�X�e�[�W��������V�[���֑J��
	if (KeyInput::OnPresed(KEY_INPUT_E) && KeyInput::OnPresed(KEY_INPUT_D))
	{
		return new EditScene();
	}
#endif
	return this;
}

void GameMain::Draw() const
{
	scene_scroll->Draw();
	effect->Draw();
	
	SetFontSize(42);
//	DrawString(400, 0, "GameMain", 0xffffff);
	//�`��
	player->Draw();
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		attack[i]->Draw();
	}
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			stage[i][j]->Draw();
		}
	}
	if (flg == true) {
		//DrawString(300, 300,"flg", 0xffffff);
	}
	//�G�l�~�[�̕`��
	zakuro->Draw(); // �U�N��
	himawari->Draw();// �Ђ܂��
	iruka->Draw();// �C���J

	/*for (int i = 0; i < BAMBOO_NUM; i++) {
		bamboo[i]->Draw();
	}*/

	powergauge->Draw();
	playerhp->Draw();
	
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
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			//�v���C���[�����ȊO�ɐG�ꂽ�ꍇ
			if (player->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
			{
				//�G�ꂽ�ʂɉ����ĉ����o��
				player->Push(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
			}
			//�U�N�������ȊO�ɐG�ꂽ�ꍇ
			if (zakuro->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
			{
				//�G�ꂽ�ʂɉ����ĉ����o��
				zakuro->ZakuroPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
			}
			//���邩�����ȊO�ɐG�ꂽ�ꍇ
			if (iruka->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0) {
				iruka->IrukaPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
			}
		}
	}

	//�U���̐������J��Ԃ�
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//�U���̔��肪�U�N���Ɣ���Ă��āA���̍U�����v���C���[�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
		if (attack[i]->HitBox(zakuro) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && zakuro->GetSpwanFlg() == false)
		{
			//�U�N���̃_���[�W����
			zakuro->ApplyDamage(attack[i]->GetAttackData().damage);
			attack[i]->DeleteAttack();

			//���Ԃ��p
			effect->HitFlg(true);
			effect->SetLocation(zakuro->GetCenterLocation());
		}
		// �U���̔��肪�C���J�Ɣ���Ă��āA���̍U�����v���C���[�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
		if (attack[i]->HitBox(iruka) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && iruka->GetSpwanFlg() == false)
		{
			//���Ԃ��p
			effect->HitFlg(true);
			effect->SetLocation(zakuro->GetCenterLocation());

			//�C���J�̃_���[�W����
			iruka->ApplyDamage(attack[i]->GetAttackData().damage);
			if (iruka->GetHp() < 1) {
				powergauge->SetVolume(iruka->GetColorDate());
			}
			attack[i]->DeleteAttack();
		}
		//�����悤�ɂЂ܂��ƃC���J��

		//�U���̔��肪�v���C���[�Ɣ���Ă��āA���̍U�����G�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
		if (attack[i]->HitBox(player) == true && attack[i]->GetAttackData().who_attack != PLAYER && attack[i]->GetCanApplyDamage() == true)
		{
			//�v���C���[�̃_���[�W����
			player->ApplyDamage(attack[i]->GetAttackData().damage);
			attack[i]->DeleteAttack();
			//zakuro->Stop_Attack();
		}
	}
}

void GameMain::CreateStage()
{
	std::ifstream file("resource/dat/StageData.txt");
	//�t�@�C�����ǂݍ��߂Ă����Ȃ�
	if (file)
	{
		//�����L���O�f�[�^�z����f�[�^��ǂݍ���
		for (int i = 0; i < STAGE_HEIGHT; i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				file >> STAGE_DATA[i][j];
			}
		}
	}
}
