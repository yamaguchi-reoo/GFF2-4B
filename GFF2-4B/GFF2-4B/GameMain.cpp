#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"
#include "StageData.h"
#include <fstream>
#include <iostream>
#include <string>
#include "EditScene.h"

int snum=0;
GameMain::GameMain()
{
	switch (snum) {

	case 0:
		who = 1;

		hands=new BossHands(who);

		player = new Player();
		LoadStageData();
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, STAGE_DATA[i][j]);
			}
		}
		for (int i = 0; i < ATTACK_NUM; i++)
		{
			attack[i] = new Attack();
		}
		for (int i = 0; i < 2; i++)
		{
			count[i] = 0;
		}
		powergauge = new PowerGauge();

		playerhp = new PlayerHP();

		effect = new Effect();

		flg = false;
		onfloor_flg = false;
		break;
	case 1:
		who = 1;
		player = new Player();
		scene_scroll = new SceneScroll();
		for (int i = 0; i < ZAKURO_MAX; i++) {
			zakuro[i] = nullptr;
		}
		zakuro[0] = new Zakuro(200, 0, true, who++);
		zakuro[1] = new Zakuro(400, 0, false, who++);
		zakuro[2] = new Zakuro(900, 0, false, who++);
		for (int i = 0; i < IRUKA_MAX; i++) {
			iruka[i] = nullptr;
		}
		iruka[0] = new Iruka(1400, 0, true, who++);
		iruka[1] = new Iruka(500, 0, false, who++);
		iruka[2] = new Iruka(900, 0, true, who++);

		LoadStageData();
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, STAGE_DATA[i][j]);
			}
		}
		himawari = new Himawari();
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
		break;
	default:
		break;
	}

}

GameMain::~GameMain()
{
	delete player;
	delete scene_scroll;
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
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
	delete himawari;
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
	/*scene_scroll->Update(player->GetLocation(), player->GetAcs(2), player->GetAcs(3));
	if (scene_scroll->ActionRangeBorder(player->GetLocation()) == true)
	{
		player->ForciblyMovePlayer(scene_scroll->PlayerScroll(player->GetLocation()));
	}*/
	//for (int i = 0; i < ZAKURO_MAX; i++)
	//{
	//	if (zakuro[i] != nullptr)
	//	{
	//		zakuro[i]->Update(this);
	//	}
	//}
	//for (int i = 0; i < IRUKA_MAX; i++)
	//{
	//	if (iruka[i] != nullptr)
	//	{
	//		iruka[i]->Update(this);
	//	}
	//}
	player->Update(this);
	hands->Update(this);
	powergauge->Update();
	playerhp->Update(player->GetPlayerHP());

	effect->Update();

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

	//if (effect->InitSplash() == 2)
	//{
	//	for (int i = 0; i < ZAKURO_MAX; i++) {
	//		if (zakuro[i] != nullptr) {
	//			powergauge->SetVolume(zakuro[i]->GetColorDate());
	//		}
	//	}
	//	effect->EndFlg(0);
	//}

	//�C���J��������
	//for (int i = 0; i < IRUKA_MAX; i++)
	//{
	//	if (iruka[i] != nullptr)
	//	{
	//		if (iruka[i]->GetLocation().x <= player->GetLocation().x + 30 && iruka[i]->GetLocation().x + 30 >= player->GetLocation().x)
	//		{
	//			iruka[i]->SetFallFlg();
	//		}
	//	}
	//}

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

		//for (int j = 0; j < ZAKURO_MAX; j++)
		//{
		//	if (zakuro[j] != nullptr) {
		//		if (attack[i]->GetAttackData().who_attack == zakuro[j]->GetWho())
		//		{
		//			attack[i]->Update(zakuro[j]->GetCenterLocation(), zakuro[j]->GetErea());
		//		}
		//	}
		//}
		//for (int j = 0; j < IRUKA_MAX; j++)
		//{
		//	if (iruka[j] != nullptr)
		//	{
		//		if (attack[i]->GetAttackData().who_attack == iruka[j]->GetWho())
		//		{
		//			attack[i]->Update(iruka[j]->GetCenterLocation(), iruka[j]->GetErea());
		//		}
		//	}
		//}

		//if (attack[i]->GetAttackData().who_attack == hands->GetWho()) {
		//	attack[i]->Update(hands->GetCenterLocation(), hands->GetErea());
		//}

	}
	//���̐������J��Ԃ�
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
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
	//scene_scroll->Draw();
	//effect->Draw();

	SetFontSize(42);
	//	DrawString(400, 0, "GameMain", 0xffffff);
		//�`��
	player->Draw();
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j]->Draw();
		}
	}
	if (flg == true) {
		//DrawString(300, 300,"flg", 0xffffff);
	}
	//�G�l�~�[�̕`��
	//for (int i = 0; i < ZAKURO_MAX; i++) {
	//	if (zakuro[i] != nullptr)
	//	{
	//		zakuro[i]->Draw(); // �U�N��
	//	}
	//}
	//himawari->Draw();// �Ђ܂��

	//for (int i = 0; i < IRUKA_MAX; i++) {
	//	if (iruka[i] != nullptr)
	//	{
	//		iruka[i]->Draw(); // �C���J
	//	}
	//}

	/*for (int i = 0; i < BAMBOO_NUM; i++) {
		bamboo[i]->Draw();
	}*/

	hands->Draw();
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
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{

			if (hands->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
			{
				hands->hitflg = true;
			}


			if (player->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
			{
				//�G�ꂽ�ʂɉ����ĉ����o��
				player->Push(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
			}
			//for (int k = 0; k < ZAKURO_MAX; k++)
			//{
			//	if (zakuro[k] != nullptr) {
			//		if (zakuro[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
			//		{
			//			//�G�ꂽ�ʂɉ����ĉ����o��
			//			zakuro[k]->ZakuroPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
			//		}
			//	}
			//}
			//for (int k = 0; k < IRUKA_MAX; k++)
			//{
			//	if (iruka[k] != nullptr) {
			//		if (iruka[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
			//		{
			//			iruka[k]->IrukaPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
			//		}
			//	}
			//}
		}
	}

	//�U���̐������J��Ԃ�
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//for (int j = 0; j < ZAKURO_MAX; j++)
		//{
		//	if (zakuro[j] != nullptr) {
		//		//�U���̔��肪�U�N���Ɣ���Ă��āA���̍U�����v���C���[�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
		//		if (attack[i]->HitBox(zakuro[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && zakuro[j]->GetSpwanFlg() == false)
		//		{
		//			//�U�N���̃_���[�W����
		//			zakuro[j]->ApplyDamage(attack[i]->GetAttackData().damage);
		//			attack[i]->DeleteAttack();

		//			//���Ԃ��p
		//			effect->HitFlg(true);
		//			effect->SetLocation(zakuro[j]->GetCenterLocation());
		//			//powergauge->SetVolume(zakuro[j]->GetColorDate());
		//		}
		//	}
		//}
		//for (int j = 0; j < IRUKA_MAX; j++) {
		//	if (iruka[j] != nullptr) {
		//		// �U���̔��肪�C���J�Ɣ���Ă��āA���̍U�����v���C���[�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
		//		if (attack[i]->HitBox(iruka[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && iruka[j]->GetSpwanFlg() == false)
		//		{
		//			//���Ԃ��p
		//			effect->HitFlg(true);
		//			//effect->SetLocation(zakuro->GetCenterLocation());

		//			//�C���J�̃_���[�W����
		//			iruka[j]->ApplyDamage(attack[i]->GetAttackData().damage);
		//			if (iruka[j]->GetHp() < 1) {
		//				powergauge->SetVolume(iruka[j]->GetColorDate());
		//			}
		//			attack[i]->DeleteAttack();
		//		}
		//	}
		//}

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

void GameMain::LoadStageData()
{
	std::ifstream file("resource/dat/StageData.txt");
	//�t�@�C�����ǂݍ��߂Ă����Ȃ�
	if (file)
	{
		file >> stage_width;
		file >> stage_height;
		//�����L���O�f�[�^�z����f�[�^��ǂݍ���
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				file >> STAGE_DATA[i][j];
			}
		}
	}
}
