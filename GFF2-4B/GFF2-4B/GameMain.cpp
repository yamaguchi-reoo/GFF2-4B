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

static Location camera_location = { (SCREEN_WIDTH / 2),(SCREEN_HEIGHT / 2) };	//カメラの座標
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
	//エディットモードに移行する時にイルカが地面に刺さっていると、
	//deleteで例外が発生するバグが起こっているので、エディットの出来るデバッグモードでは実行しないように
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
	//更新
	if (player->GetLocation().x > (SCREEN_WIDTH / 2) && player->GetLocation().x < stage_width - (SCREEN_WIDTH / 2) && now_stage != 3)
	{
		CameraLocation(player->GetLocation());
	}
	//ザクロ
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
	//イルカ
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
	//ひまわり
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

	//ボスの腕アップデート
	if (now_stage == 3) {
		if (hands != nullptr) {
			hands->Update(this);
			//岩生成
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
		
		//岩アップデート

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
		//強化ゲージMAXでXボタンが押されたらプレイヤーを強化状態に
		player->SetPowerUp();
	}
	else if (powergauge->PowerGaugeState() == 2)
	{
		//強化状態解除
		player->StopPowerUp();
		powergauge->SetPowerFlg(0);
	}

	//ひまわり向き
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
			attack[i]->SetScreenPosition(camera_location);
		}
		//ザクロ
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
		//イルカ
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
		//ひまわり
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

		////ボスの腕
		//if (now_stage == 3) {
		//	//if (hands != nullptr) {
		//	//	if (attack[i]->GetAttackData().who_attack == hands->GetWho())
		//	//	{
		//	//		attack[i]->Update(hands->GetCenterLocation(), hands->GetErea());
		//	//	}
		//	//}
		//}

		//ボスの腕
		if (now_stage == 3) {
			if (hands != nullptr) {
				if (attack[i]->GetAttackData().who_attack == hands->GetWho())
				{
					attack[i]->Update(hands->GetCenterLocation(), hands->GetErea());
					attack[i]->SetScreenPosition(camera_location);

				}

			}
				//岩
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
	
	//床の数だけ繰り返す
	for(int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			stage[i][j]->Update();
			stage[i][j]->SetScreenPosition(camera_location);
		}
	}

	//当たり判定関連の処理を行う
	HitCheck();

	if (powergauge->GetColorRem() > 0)
	{
		score->AddScore(powergauge->GetColorRem());
		powergauge->SetColorRem(0);
	}

	//ステージクリア
	if (player->GetLocation().x > stage_width - (stage_width * STAGE_GOAL)) {
		return new GameClear();
	}
	if (player->GetPlayerHP() < 0) {
		return new GameOver();
	}

#ifdef _DEBUG
	//ステージ遷移
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

	//ステージ選択画面へ遷移
	if (KeyInput::OnPresed(KEY_INPUT_4))
	{
		return new SelectStage();
	}
	//プレイヤーに強制ダメージ
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

	//途中でステージの切り替えがあった場合使用
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
		//描画
	player->Draw();

	//ボスの腕表示
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
	//床の数だけ繰り返す
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			if (player->HitBox(stage[i][j]) == true && stage[i][j]->GetStageCollisionType() != 0)
			{
				//触れた面に応じて押し出す
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
						//触れた面に応じて押し出す
						zakuro[k]->ZakuroPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
					}
				}
			}
			//イルカ
			for (int k = 0; k < IRUKA_MAX; k++)
			{
				if (iruka[k] != nullptr) {
					if (iruka[k]->HitBox(stage[i][j]) == true && stage[i][j]->GetStageCollisionType() != 0)
					{
						iruka[k]->IrukaPush(i, stage[i][j]->GetLocation(), stage[i][j]->GetErea());
					}
				}
			}
			//ひまわり
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
					effect->SetFlg(1);
					effect->SetGaugeLocation(powergauge->GetCenterLocation());
					effect->SetLocation(zakuro[j]->GetLocalLocation());
					effect->SetSplashColor(zakuro[j]->GetColorDate());
				}
			}
		}
		for (int j = 0; j < IRUKA_MAX; j++) {
			if (iruka[j] != nullptr) {
				// 攻撃の判定がイルカと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
				if (attack[i]->HitBox(iruka[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && iruka[j]->GetSpwanFlg() == false)
				{
					//しぶき用
					effect->SetFlg(1);
					effect->SetGaugeLocation(powergauge->GetCenterLocation());
					effect->SetLocation(iruka[j]->GetLocalLocation());
					effect->SetSplashColor(iruka[j]->GetColorDate());

					//イルカのダメージ処理
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
				// 攻撃の判定が	ひまわりと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
				if (attack[i]->HitBox(himawari[j]) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && himawari[j]->GetSpwanFlg() == false)
				{
					//しぶき用
					effect->SetFlg(1);
					effect->SetGaugeLocation(powergauge->GetCenterLocation());
					effect->SetLocation(himawari[j]->GetLocalLocation());
					effect->SetSplashColor(himawari[j]->GetColorDate());

					//ひまわりのダメージ処理
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

					//ボスのダメージ処理
					hands->ApplyDamage(attack[i]->GetAttackData().damage);
					attack[i]->DeleteAttack();
					//ジャンプ攻撃多段防止
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
		
	

		//攻撃の判定がプレイヤーと被っていて、その攻撃が敵によるもので、その判定がダメージを与えられる状態なら
		if (attack[i]->HitBox(player) == true && attack[i]->GetAttackData().who_attack != PLAYER && attack[i]->GetCanApplyDamage() == true)
		{
			//プレイヤーのダメージ処理
			player->ApplyDamage(attack[i]->GetAttackData().damage);
			attack[i]->DeleteAttack();
			//zakuro->Stop_Attack();
		}

	}
	//ザクロ同士で当たったら...
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


	//腕が死んだ場合
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
	//ファイルが読み込めていたなら
	if (file)
	{
		file >> stage_width_num;
		file >> stage_height_num;

		stage_width = stage_width_num * BOX_WIDTH;
		//ランキングデータ配分列データを読み込む
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
	old_stage = now_stage;
	now_stage = _stage;
	//ファイルの読込
	LoadStageData(now_stage);
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			//ステージ内ブロックを生成
			stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, STAGE_DATA[i][j]);
			switch (STAGE_DATA[i][j])
			{
			//ザクロを生成
			case 5:
				//空いてる枠に生成
				for (int k = 0; k < ZAKURO_MAX; k++)
				{
					if (zakuro[k] == nullptr)
					{
						zakuro[k] = new Zakuro(j * BOX_WIDTH, i * BOX_HEIGHT, true, who++);
						break;
					}
				}
				break;
				//イルカを生成
			case 6:
				//空いてる枠に生成
				for (int k = 0; k < IRUKA_MAX; k++)
				{
					if (iruka[k] == nullptr)
					{
						iruka[k] = new Iruka(j * BOX_WIDTH, i * BOX_HEIGHT, true, who++);
						break;
					}
				}
				break;
				//ひまわりを生成
			case 7:
				//空いてる枠に生成
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
	//プレイヤーのリスポーン
	Location res_location = { 100,100 };
	player->Respawn(res_location);
	//カメラのリセット
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