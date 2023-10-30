#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"

GameMain::GameMain()
{
	player = new Player();
	scene_scroll = new SceneScroll();
	stage[0] = new Stage(0, SCREEN_HEIGHT-100, SCREEN_WIDTH,100);
	stage[1] = new Stage(200, 450, 200, 50);
	stage[2] = new Stage(300, 450, 200, 50);
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
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		delete stage[i];
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

	//�C���J��������
	if (iruka->GetLocation().x <= player->GetLocation().x+30 && iruka->GetLocation().x + 30 >= player->GetLocation().x) {
		iruka->Get_Fall_Flg();
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
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		stage[i]->Update();
	}
	//�����蔻��֘A�̏������s��
	HitCheck();

	if (KeyInput::OnKey(KEY_INPUT_A)) {
		flg = true;
		player->ApplyDamage(1);
	}
	return this;
}

void GameMain::Draw() const
{
	scene_scroll->Draw();
	effect->Draw();
	powergauge->Draw();
	playerhp->Draw();
	

	SetFontSize(42);
//	DrawString(400, 0, "GameMain", 0xffffff);
	//�`��
	player->Draw();
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		attack[i]->Draw();
	}
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		//DrawFormatString(0, 100+(i*20), 0x00ff00, "%d", count[i]);
		stage[i]->Draw();
	}
	if (flg == true) {
		//DrawString(300, 300,"flg", 0xffffff);
	}
	//�G�l�~�[�̕`��
	zakuro->Draw(); // �U�N��
	himawari->Draw();// �Ђ܂��
	iruka->Draw();// �C���J

	for (int i = 0; i < BAMBOO_NUM; i++) {
		bamboo[i]->Draw();
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
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		if (player->HitBox(stage[i]) == true)
		{
			//�G�ꂽ�ʂɉ����ĉ����o��
			player->Push(i, stage[i]->GetLocation(), stage[i]->GetErea());
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
			powergauge->SetVolume(zakuro->GetColorDate());
			attack[i]->DeleteAttack();
		}
		// �U���̔��肪�U�N���Ɣ���Ă��āA���̍U�����v���C���[�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
		if (attack[i]->HitBox(iruka) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && iruka->GetSpwanFlg() == false)
		{
			//�U�N���̃_���[�W����
			iruka->ApplyDamage(attack[i]->GetAttackData().damage);
			powergauge->SetVolume(iruka->GetColorDate());
			attack[i]->DeleteAttack();
		}
		//�����悤�ɂЂ܂��ƃC���J��

		//�U���̔��肪�v���C���[�Ɣ���Ă��āA���̍U�����G�ɂ����̂ŁA���̔��肪�_���[�W��^�������ԂȂ�
		if (attack[i]->HitBox(player) == true && attack[i]->GetAttackData().who_attack != PLAYER && attack[i]->GetCanApplyDamage() == true)
		{
			//�v���C���[�̃_���[�W����
			player->ApplyDamage(attack[i]->GetAttackData().damage);
			attack[i]->DeleteAttack();
			zakuro->Stop_Attack();
		}
	}
}
