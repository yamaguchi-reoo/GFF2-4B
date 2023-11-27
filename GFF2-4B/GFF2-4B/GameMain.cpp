#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"
#include <fstream>
#include <iostream>
#include <string>
#include "EditScene.h"
#include "GameClear.h"
#include "GameOver.h"

static Location camera_location = { (SCREEN_WIDTH / 2),0};	//カメラの座標
static Location screen_origin = { (SCREEN_WIDTH / 2),0 };

GameMain::GameMain(int _stage)
{
	//変数の初期化
	now_stage = _stage;
	now_tuto = 0;
	tuto_flg = false;
	who = 1;
	player = new Player();
	scene_scroll = new SceneScroll();
	item_rand = 0;

	if (now_stage == 3) {
		boss = new Boss();
		hands = nullptr;
	}

	SetStage(now_stage);
	for (int i = 0; i < 2; i++)
	{
		count[i] = 0;
	}
	
	powergauge = new PowerGauge();

	playerhp = new PlayerHP();

	score = new Score();

	for (int i = 0; i < ITEM_MAX; i++)
	{
		heal[i] = nullptr;
	}

	koban = new Koban();

	loading_scene = new Loading();

	flg = false;

	Hands_Delete_Flg = false;

	impact_timer = 0;   
	camera_lock_flg = true;
	lock_pos = camera_location;
	lock_pos_set_once = true;
	lock_flg = 0;
	vine_x1 = -650;
	vine_x2 = 1290;
	vine_y = 730;
	venemy_cnt = 0;
	venemy_num1 = 0;
	venemy_num2 = 0;
	vine_img[0] = LoadGraph("resource/images/KUKYOTR.png");
	vine_img[1] = LoadGraph("resource/images/kusa.png");

	vine[0] = new Vine(0);
	vine[1] = new Vine(1160);
	lockplayer = new LockPlayer();
}

GameMain::~GameMain()
{
	delete player;
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			delete stage[i][j];
			stage[i][j] = nullptr;
		}
	}
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		delete attack[i];
		attack[i] = nullptr;
	}
	for (int i = 0; i < ZAKURO_MAX; i++)
	{
		delete zakuro[i];
		zakuro[i] = nullptr;
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
		himawari[i] = nullptr;
	}
	for (int i = 0; i < BAMBOO_MAX; i++)
	{
		delete bamboo[i];
		bamboo[i] = nullptr;
}
	for (int i = 0; i < ITEM_MAX; i++)
	{
		delete heal[i];
		heal[i] = nullptr;
	}
	for (int i = 0; i < SPLASH_MAX; i++)
	{
		delete effect[i];
		effect[i] = nullptr;
	}
	delete powergauge;
	delete playerhp;
	delete score;
	delete loading_scene;
	delete boss;
	delete hands;
	delete koban;
	delete vine[0];
	delete vine[1];
	delete lockplayer;
}

AbstractScene* GameMain::Update()
{
	//看板非表示時
	if (tuto_flg == false)
	{
		//カメラの更新
		UpdateCamera();

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
				/*if (iruka[i]->GetLocaLocationX() <= screen_origin.x + (SCREEN_WIDTH / 2) && iruka[i]->GetLocaLocationX() >= screen_origin.x - (SCREEN_WIDTH / 2)) {
					iruka[i]->Update(this);
				}*/
				iruka[i]->Update(this);
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
		//竹
		for (int i = 0; i < BAMBOO_MAX; i++)
		{
			if (bamboo[i] != nullptr)
			{
				bamboo[i]->SetScreenPosition(camera_location);
				bamboo[i]->Update(this);
			}
		}

		//ボスの腕アップデート
		if (now_stage == 3) {
			if (boss != nullptr) {
				boss->Update(this);
				boss->SetScreenPosition(camera_location);
				if (boss->New_Hand_Flg == true) {
					hands = new BossHands(who++, boss);
					boss->New_Hand_Flg = false;
				}
			}

			if (hands != nullptr) {
				hands->Update(this);
				hands->SetScreenPosition(camera_location);
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

		for (int i = 0; i < ITEM_MAX; i++)
		{
			if (heal[i] != nullptr)
			{
				heal[i]->SetScreenPosition(camera_location);
			}
		}
		koban->SetScreenPosition(camera_location);

		score->Update();

		koban->Update();

	for (int i = 0; i < SPLASH_MAX; i++)
	{
		if (effect[i] != nullptr)
		{
			effect[i]->Update(this);
			effect[i]->SetScreenPosition(camera_location);

		}
	}

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
				if (iruka[i]->GetLocation().x <= player->GetLocation().x + 30 && iruka[i]->GetLocation().x + 30 >= player->GetLocation().x && iruka[i]->GetReturnFlg() == false)
				{
					iruka[i]->SetFallFlg();
				}
			}
		}

		//攻撃の更新
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

	for (int i = 0; i < SPLASH_MAX; i++)
	{
		if (effect[i] != nullptr)
		{
			//しぶきが移動し終わったら
			if (effect[i]->GetFlg() == 2)
			{
				//ゲージを増加させる
				powergauge->SetVolume(effect[i]->GetSplashColor());
				//移動フラグを待機中に戻す
				effect[i]->SetFlg(0);
			}
		}
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

		//看板の更新
		for (int i = 0; i < SIGH_BOARD_NUM; i++)
		{
			if (sighboard[i] != nullptr)
			{
				sighboard[i]->Update(player->GetLocation(), player->GetLocalLocation());
				sighboard[i]->SetScreenPosition(camera_location);
				if (sighboard[i]->GetDispFlg() == true && sighboard[i]->GetDispOnce() == false)
				{
					tuto_flg = true;
					now_tuto = i;
					sighboard[i]->SetDispOnce(true);
				}
			}
		}

		/**プレイヤーを閉じ込めるここから*/
		//プレイヤーが強化ゲージの看板がある座標に来たら強制戦闘開始
		if (lockplayer->GetLockFlg() == false && now_stage == 0 && player->GetLocation().x >= 10285)
		{
			lockplayer->SetLockFlg(true);
		}

		//蔓を下からはやす
		if (lockplayer->GetLockFlg() == true && vine[0]->GetVineFlg() == false && vine[1]->GetVineFlg() == false)
		{
			vine[0]->VineAnimStart();
			vine[1]->VineAnimStart();
		}
		else if (lockplayer->GetLockFlg() == true && vine[0]->GetVineFlg() == true && vine[1]->GetVineFlg() == true)
		{
			lockplayer->GrassAnim();
		}

		//ザクロを15匹生成
		if (lockplayer->GetLockFlg() == true && lockplayer->GetGrassFlg() == true)
		{
			venemy_cnt++;
			if (venemy_cnt >= 60)
				if (lock_flg == 1 && vine_y <= 70)
				{
					VineEnemy(0);
					venemy_cnt = 0;
					lock_flg = 2;
				}
		}

		//ザクロを15匹倒したら蔓から解放
		if (lockplayer->GetLockFlg() == true && venemy_num2 >= 15)
		{
			lock_flg = 4;
		}

		//ザクロを15匹倒したら蔓から解放
		if (lock_flg == 3 && venemy_num2 >= 15)
		{
			lock_flg = 4;
		}

		//草を解除
		if (lock_flg == 4 && vine_x2 < 1280)
		{
			vine_x1 -= 35;
			vine_x2 += 35;
		}

		if (lock_flg == 4 && vine_x2 >= 1280)
		{
			lock_flg = 5;
		}

		//蔓を解除
		if (lock_flg == 5 && vine_y < 730)
		{
			vine_y += 35;
		}

		if (lock_flg == 5 && vine_y >= 730)
		{
			lock_flg = 6;
		}

		/**プレイヤーを閉じ込めるここまで*/

		//当たり判定関連の処理を行う
		HitCheck(this);

		//強化ゲージから溢れた分をスコアに加算
		if (powergauge->GetColorRem() > 0)
		{
			score->AddScore(powergauge->GetColorRem());
			powergauge->ResetColorRem();
		}

		//ステージクリア
		if (player->GetLocation().x > stage_width - (stage_width * STAGE_GOAL)) {
			if (now_stage == 2)
			{
				SetStage(3);
				//�r���ŃX�e�[�W�̐؂�ւ����������ꍇ�g�p
				if (now_stage == 3 && old_stage != now_stage) {
					//Hands_Delete_Flg = false;
					//boss = new Boss();
					//hands = new BossHands(who++, boss);
				}
			}
			else
			{
				return new Loading;
			}
		}

		//HPが0の状態でダメージを受けたら（HPがマイナスになったら）ゲームオーバーフラグを立てる
		if (player->GetPlayerHP() < 0) {
			game_over_flg = true;
		}

		//フラグが立っていたらゲームオーバー
		if (game_over_flg == true)
		{
			return new GameOver(now_stage);
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
			player->ApplyDamage(this, 1);
		}

		//蔓から解放
		if (KeyInput::OnKey(KEY_INPUT_7))
		{
			lock_flg = 6;
		}

		//ステージをいじるシーンへ遷移
		if (KeyInput::OnPresed(KEY_INPUT_E) && KeyInput::OnPresed(KEY_INPUT_D))
		{
			return new EditScene(now_stage);
		}
#endif
	}
	else
	{
		if (PadInput::OnButton(XINPUT_BUTTON_B) == true)
		{
			tuto_flg = false;
			sighboard[now_tuto]->SetDispFlg(false);
		}
	}
	

	return this;
}

void GameMain::Draw() const
{
	DrawBox(0, 0, 1280, 720, 0xbdbdbd, true);
	//DrawFormatString(600, 100, 0xff000f, "%d", item_rand);

	//ボス表示
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

	for (int i = 0; i < SPLASH_MAX; i++)
	{
		if (effect[i] != nullptr)
		{
			effect[i]->Draw();
		}
	}

	SetFontSize(42);
	//	DrawString(400, 0, "GameMain", 0xffffff);
		//描画
	player->Draw();

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
	//竹
	for (int i = 0; i < BAMBOO_MAX; i++)
	{
		if (bamboo[i]!= nullptr)
		{
			bamboo[i]->Draw();
		}
	}
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (heal[i] != nullptr)
		{
			heal[i]->Draw();
		}
	}

	//小判の描画
	koban->Draw();

	
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		attack[i]->Draw();
	}
	//看板の描画
	for (int i = 0; i < SIGH_BOARD_NUM; i++)
	{
		if (sighboard[i] != nullptr)
		{
			sighboard[i]->Draw();
		}
	}

	//プレイヤーを閉じ込める蔓の描画
	if (lock_flg > 0 || lock_flg < 6)
	{
		DrawGraph(-10, vine_y, vine_img[0], TRUE);
		DrawGraph(1170, vine_y, vine_img[0], TRUE);
		DrawGraph(vine_x1, -5, vine_img[1], TRUE);
		DrawGraph(vine_x2, -5, vine_img[1], TRUE);
	}

	powergauge->Draw();
	playerhp->Draw();
	score->Draw();
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

void GameMain::HitCheck(GameMain* main)
{
	//プレイヤーと床の当たり判定
	PlayerFloorHitCheck();
	//床の数だけ繰り返す
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{

			//ボス面のみボスの腕の当たり判定
			//if (now_stage == 3) {
			//	if (hands != nullptr) {
			//		if (hands->HitBox(stage[i][j]) == true && stage[i][j]->GetStageCollisionType() != 0)
			//		{
			//			hands->hitflg = true;
			//		}
			//	}
			//}

			//ザクロの数だけ繰り返す
			for (int k = 0; k < ZAKURO_MAX; k++)
			{
				ProcessCharacterCollision(zakuro[k], stage[i][j], i);
			}
			//イルカの数だけ繰り返す
			for (int k = 0; k < IRUKA_MAX; k++)
			{
				ProcessCharacterCollision(iruka[k], stage[i][j], i);
			}
			//ひまわりの数だけ繰り返す
			for (int k = 0; k < HIMAWARI_MAX; k++)
			{
				ProcessCharacterCollision(himawari[k], stage[i][j], i);
			}
			//竹の数だけ繰り返す
			for (int k = 0; k < BAMBOO_MAX; k++)
			{
				ProcessCharacterCollision(bamboo[k], stage[i][j], i);
			}
		}
	}
	//攻撃の数だけ繰り返す
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		for (int j = 0; j < ZAKURO_MAX; j++)
		{
			if (zakuro[j] != nullptr)
			{
				// 攻撃の判定がザクロと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
				ProcessAttack(attack[i], zakuro[j]/*, effect, heal, koban */ );
				//竹とエネミーの当たり判定
				HitBamboo(zakuro[j]);
			}
		}
		for (int j = 0; j < IRUKA_MAX; j++)
		{
			if (iruka[j] != nullptr)
			{
				// 攻撃の判定がイルカと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
				ProcessAttack(attack[i], iruka[j]/*,effect , heal,koban*/);
				//竹とエネミーの当たり判定
				HitBamboo(iruka[j]);
			}
		}
		for (int j = 0; j < HIMAWARI_MAX; j++) {
			if (himawari[j] != nullptr) {
				// 攻撃の判定が	ひまわりと被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
				ProcessAttack(attack[i], himawari[j]/*, effect, heal,koban*/);
				//竹とエネミーの当たり判定
				HitBamboo(himawari[j]);
			}
		}
		for (int j = 0; j < BAMBOO_MAX; j++)
		{
			if (bamboo[j] != nullptr)
			{
				// 攻撃の判定が	竹被っていて、その攻撃がプレイヤーによるもので、その判定がダメージを与えられる状態なら
				if (attack[i]->HitBox(bamboo[j]) == true && attack[i]->GetCanApplyDamage() == true && attack[i]->GetAttackData().who_attack == PLAYER && bamboo[j]->GetSpwanFlg() == false)
				{
					//ダメージ量に応じた画面揺れ
					ImpactCamera(10 * attack[i]->GetAttackData().damage);

					bamboo[j]->ApplyDamage(attack[i]->GetAttackData().damage);
					attack[i]->DeleteAttack();
				}
				//プレイヤーと竹の当たり判定
				if (player->HitBox(bamboo[j]) == true && bamboo[j]->GetSpwanFlg() == false)
				{
					player->Push(bamboo[j]->GetLocation(), bamboo[j]->GetErea(), 8);
				}
			}
		}
		if (now_stage == 3) {
			if (hands != nullptr) {
				if (attack[i]->HitBox(hands) == true && attack[i]->GetAttackData().who_attack == PLAYER && attack[i]->GetCanApplyDamage() == true && hands->Death_Flg == false)
				{
					ImpactCamera(10 * attack[i]->GetAttackData().damage);
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
			player->ApplyDamage(main, attack[i]->GetAttackData().damage);
			//攻撃を消す
			attack[i]->DeleteAttack();
		}
		//攻撃がプレイヤーによるもので、その攻撃がジャンプ攻撃で
		if (attack[i]->GetAttackData().who_attack == PLAYER && player->GetAttackStep() == 4)
		{
			attack[i]->SetDirection(player->GetPlayerDirection());
			//プレイヤーが床に触れたなら
			if (player->GetOnFloorFlg() == true)
			{
				//攻撃を消す
				attack[i]->DeleteAttack();
			}
		}
		for (int j = i + 1; j < ATTACK_NUM; j++)
		{
			//攻撃同士が当たっていて、片方の攻撃がプレイヤーによるもので、もう片方の攻撃がひまわり（ボスひまわり）の弾で、プレイヤーの攻撃がダメージを与えられるなら
			if (attack[i]->HitBox(attack[j]) == true && (attack[i]->GetCanApplyDamage() == true && attack[j]->GetCanApplyDamage() == true) && attack[i]->GetAttackData().who_attack == PLAYER && (attack[j]->GetAttackData().effect_type == HIMAWARI_BULLET || attack[j]->GetAttackData().effect_type == BOSSHIMAWARI_BULLET))
			{
				attack[j]->DeleteAttack();
			}
			//攻撃同士が当たっていて、片方の攻撃がプレイヤーによるもので、もう片方の攻撃がひまわり（ボスひまわり）の弾で、プレイヤーの攻撃がダメージを与えられるなら
			if (attack[i]->HitBox(attack[j]) == true && (attack[i]->GetCanApplyDamage() == true && attack[j]->GetCanApplyDamage() == true) && attack[j]->GetAttackData().who_attack == PLAYER && (attack[i]->GetAttackData().effect_type == HIMAWARI_BULLET || attack[i]->GetAttackData().effect_type == BOSSHIMAWARI_BULLET))
			{
				attack[i]->DeleteAttack();
			}
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
	//竹同士が当たったら止まる
	for (int i = 0; i < BAMBOO_MAX; i++)
	{
		for (int j = i + 1; j < BAMBOO_MAX; j++)
		{
			if (bamboo[i] != nullptr && bamboo[j] != nullptr)
			{
				if (bamboo[i]->HitBox(bamboo[j]) == true && bamboo[i]->GetSpwanFlg() == false && bamboo[j]->GetSpwanFlg() == false) {
					bamboo[i]->FalseGravity();
				}
			}
		}
	}
	//腕が死んだ場合
	if (hands != nullptr) {
		if (Hands_Delete_Flg==true) {
			boss->Count_Death--;
			hands = nullptr;
			boss->Once_Flg = true;
			Hands_Delete_Flg = false;
		}
	}

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (heal[i] != nullptr)
		{
			//プレイヤーとアイテムが当たった&回復アイテムがスポーンしている時
			if (player->HitBox(heal[i]) == true && heal[i]->GetSpawnFlg() == true)
			{
				if (player->GetPlayerHP() >= 7)
				{
					score->AddScore(100);
				}
				//プレイヤーのHPを増やす
				player->AddPlayerHp();
				//フラグをflaseにする
				heal[i]->SetSpawnFlg(false);
			}
		}
	}
	if (player->HitBox(koban) == true && koban->GetSpawnFlg() == true)
	{
		score->AddScore(300);
		koban->SetScoreLocation();
		koban->SetSpawnFlg(false);
		koban->SetScoreFlg(true);
	}
}

void GameMain::PlayerFloorHitCheck()
{
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = player->GetPlayerNowErea() - 2; j < player->GetPlayerNowErea() + 2; j++)
		{
			//プレイヤーがステージに触れたなら
			if (j >= 0 && j<stage_width_num && player->HitBox(stage[i][j]) == true && stage[i][j]->GetStageCollisionType() != 0)
			{
				//触れた面に応じて押し出す
				player->Push(stage[i][j]->GetLocation(), stage[i][j]->GetErea(), stage[i][j]->GetStageCollisionType());
			}
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
	for (int i = 0; i < SIGH_BOARD_NUM; i++)
	{
		sighboard[i] = nullptr;
	}
	old_stage = now_stage;
	now_stage = _stage;
	//ファイルの読込


	//�t�@�C���̓Ǎ�
	LoadStageData(now_stage);
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			//ステージ内ブロックを生成
			stage[i][j] = new Stage((float)(j * BOX_WIDTH), (float)(i * BOX_HEIGHT), BOX_WIDTH, BOX_HEIGHT, STAGE_DATA[i][j]);
			switch (STAGE_DATA[i][j])
			{
			//ザクロを生成
			case 5:
				//空いてる枠に生成
				for (int k = 0; k < ZAKURO_MAX; k++)
				{
					if (zakuro[k] == nullptr)
					{
						zakuro[k] = new Zakuro((float)(j * BOX_WIDTH), (float)(i * BOX_HEIGHT), true, who++);
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
						iruka[k] = new Iruka((float)(j * BOX_WIDTH), (float)(i * BOX_HEIGHT), true, who++);
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
						himawari[k] = new Himawari((float)(j * BOX_WIDTH), (float)(i * BOX_HEIGHT), true, who++);
						break;
					}
				}
				break;
			case 8:
				for (int k = 0; k < BAMBOO_MAX; k++) 
				{
					if (bamboo[k] == nullptr)
					{
						bamboo[k] = new Bamboo((float)(j * BOX_WIDTH), (float)(i * BOX_HEIGHT));
						break;
					}
				}
				break;
				//看板を生成
			case 9:
			case 10:
			case 11:
			case 12:
				for (int k = 0; k < SIGH_BOARD_NUM; k++)
				{
					if (sighboard[k] == nullptr)
					{
						sighboard[k] = new SighBoard((float)(j * BOX_WIDTH), (float)(i * BOX_HEIGHT), STAGE_DATA[i][j]);
						break;
					}
				}
				break;
			default:
				break;
			}
		}
	}


	//�r���ŃX�e�[�W�̐؂�ւ����������ꍇ�g�p
	if (now_stage == 3 && old_stage != now_stage) {
		//Hands_Delete_Flg = false;
		boss = new Boss();
		//hands = new BossHands(who++, boss);
	}

	//プレイヤーのリスポーン
	Location res_location = { 100,100 };
	player->Respawn(res_location);
	//カメラのリセット
	ResetCamera();
	//カメラの位置がプレイヤーの位置にならないように
	lock_pos_set_once = true;
	//スコアリセット
	score->ResetScore();
}

void GameMain::CameraLocation(Location _location)
{
	camera_location.x = _location.x - (SCREEN_WIDTH / 2);
	camera_location.y = 0;
}

void GameMain::ResetCamera()
{
	camera_location.x = screen_origin.x;
	camera_location.y = screen_origin.y;
}

Location GameMain::GetPlayerLocation()
{
	return player->GetLocation();
}

void GameMain::ImpactCamera(int _power)
{
	impact_timer = _power;
}

void GameMain::UpdateCamera()
{
	if (player->GetLocation().x > (SCREEN_WIDTH / 2) && player->GetLocation().x < stage_width - (SCREEN_WIDTH / 2) && now_stage != 3 && (lock_flg == 0 || lock_flg == 6))
	{
		camera_lock_flg = false;
		lock_pos_set_once = false;
	}
	else
	{
		camera_lock_flg = true;
		if (lock_pos_set_once == false)
		{
			lock_pos = player->GetLocation();
			lock_pos_set_once = true;
		}
	}

	if (camera_lock_flg == false)
	{
		CameraLocation(player->GetLocation());
	}
	else
	{
		CameraLocation(lock_pos);
	}

	//揺れ処理
	if (--impact_timer > 0)
	{
		camera_location.x += (GetRand(impact_timer) - (impact_timer / 2));
		camera_location.y += (GetRand(impact_timer) - (impact_timer / 2));
	}
}

template <class T>
void GameMain::ProcessCharacterCollision(T* character, Stage* stageObject, int index) {
	// キャラクターオブジェクトが存在し、ヒットボックスがステージオブジェクトと交差し、かつステージの当たり判定がある場合
	if (character != nullptr && character->HitBox(stageObject) == true && stageObject->GetStageCollisionType() != 0) {
		// キャラクターの押し出し処理
		character->Push(index, stageObject->GetLocation(), stageObject->GetErea());
	}
}

template<class T>
void GameMain::ProcessAttack(Attack* attack, T* character/*,Effect* effect, HealItem* heal, Koban* koban*/)
{
	//攻撃がヒットボックスに当たり、ダメージが適用可能で、キャラクターがスポーンしている場合
	if (attack->HitBox(character) && attack->GetAttackData().who_attack == PLAYER && attack->GetCanApplyDamage() == true && character->GetSpwanFlg() == false) {		
		character->ApplyDamage(attack->GetAttackData().damage);
		attack->DeleteAttack();

		// しぶきのスポーン処理
		SpawnEffect(character);

		//ダメージ量に応じた画面揺れ
		impact_timer = (10 * attack->GetAttackData().damage);

		//hpが0なら
		if (character->GetHp() <= 0)
		{	
			if ((powergauge->GetMagentaVolume() >= 100.0f && character->GetColorDate().magenta == 15.0f) ||
				(powergauge->GetYellowVolume() >= 100.0f && character->GetColorDate().yellow == 15.0f) ||
				(powergauge->GetCyanVolume() >= 100.0f && character->GetColorDate().cyan == 15.0f))
			{
				// アイテムの位置を設定
				koban->SetLocation(character->GetLocation());
				// アイテムのスポーン処理
				ItemSpwanRand(character);

			}
			//蔓内で斬った敵の数をカウント
			if (lock_flg == 3 && venemy_num2 < 15)
			{
				venemy_num2++;
			}
		}
	}
}

template<class T>
void GameMain::HitBamboo(T* character)
{
	if (character != nullptr)
	{
		for (int i = 0; i < BAMBOO_MAX; i++)
		{
			if (bamboo[i] != nullptr && character->HitBox(bamboo[i]) == true && bamboo[i]->GetSpwanFlg() == false)
			{
				//触れた面に応じて押し出す
				character->Push(i, bamboo[i]->GetLocation(), bamboo[i]->GetErea());
			}
		}
	}
}

// アイテムスポーンのランダムな処理
template<class T>
void GameMain::ItemSpwanRand(T* character)
{
	item_rand = GetRand(99);  // 0から99のランダムな値を取得

	// 回復アイテムのスポーン
	if (item_rand < 60)  // 0から59までが回復アイテムの範囲
	{
		for (int i = 0; i <ITEM_MAX; i++)
		{
			//配列がnullptrだったら生成
			if (heal[i] == nullptr)
			{
				heal[i] = new HealItem();
				//座標をセット
				heal[i]->SetLocation(character->GetLocation());
				// 回復アイテムをスポーンさせるフラグを設定
				heal[i]->SetSpawnFlg(true);  
				break;
			}
		}
	}
	// スポーン無し
	else if (60 <= item_rand && item_rand < 85)  // 60から84までがスポーン無しの範囲
	{
		// 何もしないか、必要に応じて処理を追加
	}
	// コインのスポーン
	else if (85 <= item_rand && item_rand < 100)  // 85から99までがコインの範囲
	{
		koban->SetSpawnFlg(true); // コインをスポーンさせるフラグを設定
	}
}

//しぶきの生成
template<class T>
void  GameMain::SpawnEffect(T* character)
{
	for (int i = 0; i < SPLASH_MAX; i++)
	{
		if (effect[i] == nullptr)
		{
			effect[i] = new Effect();

			//敵のローカル座標を取得、しぶきのスタート位置にセット
			effect[i]->SetLocation(character->GetLocalLocation());
			//ゲージの中心座標を取得、しぶきのゴール位置にセット
			effect[i]->SetGaugeLocation(powergauge->GetCenterLocation());
		
			//倒したキャラクターの色情報を取得、しぶきに色情報をセット
			effect[i]->SetSplashColor(character->GetColorDate());
			//しぶきを移動させるフラグを設定
			effect[i]->SetFlg(1);
		
			break;
		}
	}
}

//蔓内での敵生成処理
void GameMain::VineEnemy(void)
{
	int num = 0;

	num = GetRand(4);

	//空いてる枠にザクロ生成
	for (int k = 0; k < ZAKURO_MAX; k++)
	{
		if (zakuro[k] == nullptr)
		{
			zakuro[k] = new Zakuro((float)(9900 + (200 * num)), (float)(200), true, who++);
			venemy_num1++;
			break;
		}
	}
}

