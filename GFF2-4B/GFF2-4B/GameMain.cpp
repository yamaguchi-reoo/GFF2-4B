#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"
#include "StageData.h"
#include <fstream>
#include <iostream>
#include <string>
#include "EditScene.h"

GameMain::GameMain(int _stage)
{
	now_stage = _stage;
	who = 1;
	player = new Player();
	scene_scroll = new SceneScroll();
	//zakuroとirukaの生成はSetStageに移動
	//for (int i = 0; i < ZAKURO_MAX; i++) {
	//	zakuro[i] = nullptr;
	//}
	//zakuro[0] = new Zakuro(200, 0, true, who++);
	//zakuro[1] = new Zakuro(400, 0, false, who++);
	//zakuro[2] = new Zakuro(900, 0, false, who++);
	//for (int i = 0; i < IRUKA_MAX; i++) {
	//	iruka[i] = nullptr;
	//}
	//iruka[0] = new Iruka(1400,0,true, who++);
	//iruka[1] = new Iruka(500,0,false, who++);
	//iruka[2] = new Iruka(900,0,true, who++);

	//for (int i = 0; i < HIMAWARI_MAX; i++) {
	//	himawari[i] = nullptr;
	//}
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
	//エディットモードに移行する時にイルカが地面に刺さっていると、deleteで例外が発生するバグが起こっているので、コメントアウト
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
	//ザクロ
	for (int i = 0; i < ZAKURO_MAX; i++)
	{
		if (zakuro[i] != nullptr) 
		{
			zakuro[i]->Update(this);
		}
	}
	//イルカ
	for (int i = 0; i < IRUKA_MAX; i++)
	{
		if (iruka[i] != nullptr)
		{
			iruka[i]->Update(this);
		}
	}
	//ひまわり
	for (int i = 0; i < HIMAWARI_MAX; i++) 
	{
		if (himawari[i] != nullptr) 
		{
			himawari[i]->Update(this);
		}
	}
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

	if (effect->InitSplash() == 2)
	{
		for (int i = 0; i < ZAKURO_MAX; i++) {
			if (zakuro[i] != nullptr) {
				powergauge->SetVolume(zakuro[i]->GetColorDate());	
			}
		}
		effect->EndFlg(0);
	}

	//イルカ落下判定
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
		//ザクロ
		for (int j = 0; j < ZAKURO_MAX; j++)
		{
			if (zakuro[j] != nullptr) {
				if (attack[i]->GetAttackData().who_attack == zakuro[j]->GetWho())
				{
					attack[i]->Update(zakuro[j]->GetCenterLocation(), zakuro[j]->GetErea());
				}
			}		
		}
		//イルカ
		for (int j = 0; j < IRUKA_MAX; j++) 
		{
			if (iruka[j] != nullptr) 
			{
				if (attack[i]->GetAttackData().who_attack == iruka[j]->GetWho())
				{
					attack[i]->Update(iruka[j]->GetCenterLocation(), iruka[j]->GetErea());
				}
			}
		}
		for (int j = 0; j < HIMAWARI_MAX; j++)
		{
			if (himawari[j] != nullptr)
			{
				if (attack[i]->GetAttackData().who_attack == himawari[j]->GetWho())
				{
					attack[i]->Update(himawari[j]->GetCenterLocation(), himawari[j]->GetErea());
				}
			}
		}

	}
	//床の数だけ繰り返す
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j]->Update();
		}
	}
	//当たり判定関連の処理を行う
	HitCheck();

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

#if DEBUG
	if (KeyInput::OnKey(KEY_INPUT_S)) 
	{
		flg = true;
		player->ApplyDamage(1);
	}
	//ステージをいじるシーンへ遷移
	if (KeyInput::OnPresed(KEY_INPUT_E) && KeyInput::OnPresed(KEY_INPUT_D))
	{
		return new EditScene(now_stage);
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
	//描画
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
	//エネミーの描画
	// ザクロ
	for (int i = 0; i < ZAKURO_MAX; i++) 
	{
		if (zakuro[i] != nullptr) 
		{
			zakuro[i]->Draw(); 
		}
	}
	// ひまわり
	for (int i = 0; i < HIMAWARI_MAX; i++) 
	{
		if (himawari[i] != nullptr)
		{
			himawari[i]->Draw();
		}
	}
	// イルカ
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
	//床の数だけ繰り返す
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			if (player->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
			{
				//触れた面に応じて押し出す
				player->Push(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
			}
			for (int k = 0; k < ZAKURO_MAX; k++)
			{
				if (zakuro[k] != nullptr) {
					if (zakuro[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0)
					{
						//触れた面に応じて押し出す
						zakuro[k]->ZakuroPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
					}
				}
			}
			for (int k = 0; k < IRUKA_MAX; k++)
			{
				if (iruka[k] != nullptr) {
					if (iruka[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageType() != 0) 
					{
						iruka[k]->IrukaPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
					}
				}
			}
		}
	}

	//攻撃の数だけ繰り返す
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		for (int j = 0; j < ZAKURO_MAX; j++)
		{
			if (zakuro[j] != nullptr) {
				//攻撃の判定がザクロと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
				if (attack[i]->HitBox(zakuro[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && zakuro[j]->GetSpwanFlg() == false)
				{
					//ザクロのダメージ処理
					zakuro[j]->ApplyDamage(attack[i]->GetAttackData().damage);
					attack[i]->DeleteAttack();

					//しぶき用
					effect->HitFlg(true);
					effect->SetLocation(zakuro[j]->GetCenterLocation());
					//powergauge->SetVolume(zakuro[j]->GetColorDate());
				}
			}
		 }
		for (int j = 0; j < IRUKA_MAX; j++) {
			if (iruka[j] != nullptr) {
				// 攻撃の判定がイルカと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
				if (attack[i]->HitBox(iruka[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && iruka[j]->GetSpwanFlg() == false)
				{
					//しぶき用
					effect->HitFlg(true);
					//effect->SetLocation(zakuro->GetCenterLocation());

					//イルカのダメージ処理
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
				// 攻撃の判定がイルカと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
				if (attack[i]->HitBox(himawari[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && himawari[j]->GetSpwanFlg() == false)
				{
					//しぶき用
					effect->HitFlg(true);
					//effect->SetLocation(zakuro->GetCenterLocation());

					//イルカのダメージ処理
					himawari[j]->ApplyDamage(attack[i]->GetAttackData().damage);
					//if (himawari[j]->GetHp() < 1) {
						powergauge->SetVolume(himawari[j]->GetColorDate());
					//}
					attack[i]->DeleteAttack();
				}
			}
		}

		//攻撃の判定がプレイヤーと被っていて、その攻撃が敵によるもので、その判定がダメージを与えられる状態なら
		if (attack[i]->HitBox(player) == true && attack[i]->GetAttackData().who_attack != PLAYER && attack[i]->GetCanApplyDamage() == true)
		{
			//プレイヤーのダメージ処理
			player->ApplyDamage(attack[i]->GetAttackData().damage);
			attack[i]->DeleteAttack();
			//zakuro->Stop_Attack();
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
	//ファイルが読み込めていたなら
	if (file)
	{
		file >> stage_width;
		file >> stage_height;
		//ランキングデータ配分列データを読み込む
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				file >> STAGE_DATA[i][j];
			}
		}
	}
}

void GameMain::SetStage(int _stage)
{
	//敵と攻撃をリセット
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
	now_stage = _stage;
	//ファイルの読込
	LoadStageData(now_stage);
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			switch (STAGE_DATA[i][j])
			{
				//ステージ内ブロックを生成
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, STAGE_DATA[i][j]);
				break;
				//ザクロを生成
			case 5:
				stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, 0);
				//空いてる枠に生成
				for (int k = 0; k < ZAKURO_MAX; k++)
				{
					if (zakuro[k] == nullptr)
					{
						zakuro[k] = new Zakuro(j * BOX_SIZE, i * BOX_SIZE, true,who++);
						break;
					}
				}
				break;
				//イルカを生成
			case 6:
				stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, 0);
				//空いてる枠に生成
				for (int k = 0; k < IRUKA_MAX; k++)
				{
					if (iruka[k] == nullptr)
					{
						iruka[k] = new Iruka(j * BOX_SIZE, i * BOX_SIZE, true, who++);
						break;
					}
				}
				break;
				//ひまわりを生成
			case 7:
				stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, 0);
				//空いてる枠に生成
				for (int k = 0; k < HIMAWARI_MAX; k++)
				{
					if (himawari[k] == nullptr)
					{
						himawari[k] = new Himawari(j * BOX_SIZE, i * BOX_SIZE, true, who++);
						break;
					}
				}
				break;
			}
		}
	}
	//プレイヤーのリスポーン
	Location res_location = { 100,100 };
	player->Respawn(res_location);
}
