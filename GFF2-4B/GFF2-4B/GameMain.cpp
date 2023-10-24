#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"

GameMain::GameMain()
{
	player = new Player();
	scene_scroll = new SceneScroll();
	stage[0] = new Stage(0, SCREEN_HEIGHT-100, SCREEN_WIDTH,100);
	stage[1] = new Stage(200, 300, 200, 50);

	zakuro = new Zakuro();
	himawari = new Himawari();
	iruka = new Iruka();
	for (int i = 0; i < 10; i++)
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
	for (int i = 0; i < 10; i++)
	{
		delete attack[i];
	}
	delete zakuro;
	delete himawari;
	delete iruka;
	delete powergauge;
}

AbstractScene* GameMain::Update()
{
	//�X�V
	scene_scroll->Update(player->GetLocation(), player->GetAcs(2), player->GetAcs(3));
	scene_scroll->PlayerScroll(player->GetLocation());
	if(scene_scroll->ActionRangeBorder(player->GetLocation()) == true)
	{
		player->MovePlayer(scene_scroll->PlayerScroll(player->GetLocation()));
	}
	zakuro->Update(this);
	iruka->Update(this);
	player->Update(this);
	powergauge->Update();

	//�C���J��������
	if (iruka->GetLocation().x <= player->GetLocation().x+30 && iruka->GetLocation().x + 30 >= player->GetLocation().x) {
		iruka->Get_Fall_Flg();
	}
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		attack[i]->Update(player->GetCenterLocation(), player->GetErea());
		attack[i]->Update(zakuro->GetCenterLocation(), zakuro->GetErea());
	}
	//���̐������J��Ԃ�
	for (int i = 0; i < 2; i++)
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
	powergauge->Draw();

	SetFontSize(42);
	DrawString(400, 0, "GameMain", 0xffffff);
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
		DrawString(300, 300,"flg", 0xffffff);
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
		//if (attack[i]->HitBox(/*�G*/) == true && /*�v���C���[���o�����U����*/)
		//{
	}
}
