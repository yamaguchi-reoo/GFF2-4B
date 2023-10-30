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
	//更新
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
		//強化ゲージMAXでXボタンが押されたらプレイヤーを強化状態に
		player->SetPowerUp();
	}
	else if(powergauge->PowerGaugeState() == 2)
	{
		//強化状態解除
		player->StopPowerUp();
		powergauge->SetPowerFlg(0);
	}

	//イルカ落下判定
	if (iruka->GetLocation().x <= player->GetLocation().x+30 && iruka->GetLocation().x + 30 >= player->GetLocation().x) {
		iruka->Get_Fall_Flg();
	}
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//誰が攻撃したかによって攻撃の判定がついていく対象を変える
		if (attack[i]->GetAttackData().who_attack == player->GetWho())
		{
			attack[i]->Update(player->GetCenterLocation(), player->GetErea());
		}
		/*************************************************************************************************
		* 新しい敵を生成するたびに、whoの変数に1、２、3と数字を割り振っていき(被りなしで　０はプレイヤー)、
		* 攻撃を生成するときにその値をattack_data.who_attackに格納し、
		* ここで画面内の敵の種類分だけifを作り、１種類の敵の数だけforで繰り返す
		* whoはBoxColliderで定義済み
		* 
		*	for(int j = 0; j < (画面内のザクロの数が入っている変数); j++ )
		*	{
		*		if (attack[j]->GetAttackData().who_attack == zakuro[j]->GetWho())
		*		{
		*			attack[j]->Update(zakuro[j]->GetCenterLocation(), zakuro[j]->GetErea());
		*		}
		*	}
		* 
		* 	for(int j = 0; j < (画面内のひまわりの数が入っている変数); j++ )
		*	{
		*		if (attack[j]->GetAttackData().who_attack == himawari[j]->GetWho())
		*		{
		*			attack[j]->Update(himawari[j]->GetCenterLocation(), himawari[j]->GetErea());
		*		}
		*	}
		* 
		* 　for(int i = 0; i < (画面内のいるかの数が入っている変数); i++ )
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
	//床の数だけ繰り返す
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		stage[i]->Update();
	}
	//当たり判定関連の処理を行う
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
	//描画
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
	//エネミーの描画
	zakuro->Draw(); // ザクロ
	himawari->Draw();// ひまわり
	iruka->Draw();// イルカ

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
	//床の数だけ繰り返す
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		if (player->HitBox(stage[i]) == true)
		{
			//触れた面に応じて押し出す
			player->Push(i, stage[i]->GetLocation(), stage[i]->GetErea());
		}
	}

	//攻撃の数だけ繰り返す
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//攻撃の判定がザクロと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
		if (attack[i]->HitBox(zakuro) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && zakuro->GetSpwanFlg() == false)
		{
			//ザクロのダメージ処理
			zakuro->ApplyDamage(attack[i]->GetAttackData().damage);
			powergauge->SetVolume(zakuro->GetColorDate());
			attack[i]->DeleteAttack();
		}
		// 攻撃の判定がザクロと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
		if (attack[i]->HitBox(iruka) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && iruka->GetSpwanFlg() == false)
		{
			//ザクロのダメージ処理
			iruka->ApplyDamage(attack[i]->GetAttackData().damage);
			powergauge->SetVolume(iruka->GetColorDate());
			attack[i]->DeleteAttack();
		}
		//同じようにひまわりとイルカも

		//攻撃の判定がプレイヤーと被っていて、その攻撃が敵によるもので、その判定がダメージを与えられる状態なら
		if (attack[i]->HitBox(player) == true && attack[i]->GetAttackData().who_attack != PLAYER && attack[i]->GetCanApplyDamage() == true)
		{
			//プレイヤーのダメージ処理
			player->ApplyDamage(attack[i]->GetAttackData().damage);
			attack[i]->DeleteAttack();
			zakuro->Stop_Attack();
		}
	}
}
