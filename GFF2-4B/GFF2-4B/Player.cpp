#include "Player.h"
#include "PadInput.h"
#include "SoundManager.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define ACS_MAX 6	//最大加速度
#define DOWN 0	//下加速度用
#define UP 1	//上加速度用
#define RIGHT 2	//右加速度用
#define LEFT 3	//左加速度用

#define DEFAULT_MOVE_SPEED 0.3f			//基本移動速度(左右)
#define DEFAULT_JUMP_POWER 24			//基本最大跳躍力
#define GRAVITY_POWER  (ACS_MAX * 2.5f) //重力の強さ
#define DEFAULT_ATTACK_INTERVAL	25		//基本攻撃間隔(フレーム)
#define DEFAULT_INVINCIBLE_TIME	100		//基本無敵時間(攻撃を喰らった後)

#define PLAYER_IMAGE_SHIFT_X 100			//画像ずらし用
#define PLAYER_IMAGE_SHIFT_Y 95			//画像ずらし用
#define PLAYER_IDOL 34					//立ち姿アニメーション開始地点
#define PLAYER_WALK 28					//移動アニメーション開始地点
#define PLAYER_JUMP 27					//ジャンプアニメーション開始地点
#define PLAYER_ATTACK_ONE 0				//攻撃１段目アニメーション開始地点
#define PLAYER_ATTACK_TWO 6				//攻撃２段目アニメーション開始地点
#define PLAYER_ATTACK_THREE 13			//攻撃３段目アニメーション開始地点
#define PLAYER_ATTACK_FOUR 20			//攻撃４段目アニメーション開始地点
#define PLAYER_JUMP_ATTACK 15			//ジャンプ攻撃アニメーション開始地点
#define PLAYER_JUMP_ATTACK_END 25		//ジャンプ攻撃（着地）アニメーション開始地点
#define PLAYER_DAMAGE 26				//ジャンプ攻撃（着地）アニメーション開始地点
#define PLAYER_ANIM 5					//次の画像に切り替えるまでの時間（フレーム）

Player::Player()
{
#ifdef _DEBUG
	d_inv_flg = false;
#endif
	frame = 0;
	old_location = { 0 };
	next_location = { 0 };
	location = {0,0};
	erea.height = PLAYER_HEIGHT;
	erea.width = PLAYER_WIDTH;
	who = 0;
	hp = 5;
	move_speed = DEFAULT_MOVE_SPEED;
	jump_power = DEFAULT_JUMP_POWER;
	direction = false;
	attack_interval_count = 0;
	ca_interval_count = 0;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
	combo_attack_interval = (int)(DEFAULT_ATTACK_INTERVAL * 1.5f);
	attack_step = 0;
	attack_time = DEFAULT_ATTACK_INTERVAL;
	attack_time_count = 0;
	for (int i = 0; i < ATTACK_PATTERN; i++)
	{
		attack_motion_flg[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		acs[i] = 0;
		external_move[i] = 0;
	}
	acs_max = ACS_MAX;
	onfloor_flg = false;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	jump_flg = false;
	powerup_flg = false;
	move_flg = true;
	attack_anim_flg = false;
	inv_flg = false;
	damage_flg = false;
	hidden_flg = false;
	death_flg = false;

	SetPlayerAttackData();
	LoadDivGraph("resource/images/Player_Animation.png", 35, 10, 4, 256, 256, player_image);
	player_anim = 0;
	attack_anim = 0;
	player_anim_speed = PLAYER_ANIM;
	inv_time = DEFAULT_INVINCIBLE_TIME;
	damage_time = DEFAULT_INVINCIBLE_TIME / 2;
	death_time = 120;
	player_now_erea = (int)GetCenterLocation().x / BOX_WIDTH;
}

Player::~Player() 
{
	
}

void Player::Update(GameMain* main)
{
	//無敵状態の切り替え（デバッグ用）
#ifdef _DEBUG
	if (KeyInput::OnKey(KEY_INPUT_Q) == true)
	{
		d_inv_flg = !d_inv_flg;
	}
#endif
	frame++;
	player_now_erea = (int)GetCenterLocation().x / BOX_WIDTH;
	//生きているなら重力、ダメージ、攻撃関連の処理を行う
	if (death_flg == false)
	{

		//ダメージを受けている途中でないなら
		if (damage_flg == false)
		{
			//攻撃
			Attack(main);
		}

		//ダメージ演出中なら
		if (inv_flg == true)
		{
			damage_flg = true;
			if (--damage_time < 0)
			{
				damage_flg = false;
			}
			//無敵時間が終わったら
			if (--inv_time < 0)
			{
				inv_flg = false;
				inv_time = DEFAULT_INVINCIBLE_TIME;
				damage_time = DEFAULT_INVINCIBLE_TIME / 2;
			}
		}
	}
	//死んでいるなら死亡時間の測定
	else
	{
		if (--death_time <= 0)
		{
			main->SetGameOver();
		}
	}

	//移動処理
	Move(main);

	PlayerSound();

	//プレイヤーの状態を更新する
	UpdatePlayerState();
	//床に触れていないなら
	if (onfloor_flg == false)
	{
		//重力を与える
		GiveGravity();
		jump_flg = true;
	}
	//各移動用変数をリセット
	Reset();

	//描画関連の変数を動かす
	Anim();
}

void Player::Draw()const
{
	//プレイヤー画像表示
	if (hidden_flg == false)
	{
		switch (player_state)
		{
		case IDOL_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL], true);
			break;
		case IDOL_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL], true);
			break;
		case MOVE_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_WALK + player_anim], true);
			break;
		case MOVE_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_WALK + player_anim], true);
			break;
		case JUMP_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case JUMP_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case FALL_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case FALL_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case ATTACK_RIGHT_ONE:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_ONE + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case ATTACK_RIGHT_TWO:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_TWO + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case ATTACK_RIGHT_THREE:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_THREE + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case ATTACK_RIGHT_FOUR:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_FOUR + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case ATTACK_LEFT_ONE:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_ONE + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case ATTACK_LEFT_TWO:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_TWO + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case ATTACK_LEFT_THREE:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_THREE + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case ATTACK_LEFT_FOUR:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_FOUR + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case JUMP_ATTACK_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case JUMP_ATTACK_RIGHT_END:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK_END], true);
			break;
		case JUMP_ATTACK_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK + attack_anim_num[attack_step][attack_anim]], true);
			break;
		case JUMP_ATTACK_LEFT_END:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK_END], true);
			break;
		case DAMAGE_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_DAMAGE], true);
			break;
		case DAMAGE_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_DAMAGE], true);
			break;
		case DEATH_RIGHT:
			DrawRotaGraphF(local_location.x + PLAYER_IMAGE_SHIFT_X, local_location.y + PLAYER_IMAGE_SHIFT_Y * 1.5f , 1, M_PI / 2, player_image[PLAYER_DAMAGE], true);
			break;
		case DEATH_LEFT:
			DrawRotaGraphF(local_location.x + PLAYER_IMAGE_SHIFT_X, local_location.y + PLAYER_IMAGE_SHIFT_Y * 1.5f , 1, M_PI / 2, player_image[PLAYER_DAMAGE], true);
			break;
		default:
			DrawStringF(local_location.x, local_location.y, "no image", 0xff0000);
			break;
		}
	}

	//デバッグ用表示
#ifdef _DEBUG
	//当たり判定表示
	//強化状態でないなら
	if (powerup_flg == false)
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xff0000, false);
	}
	//強化状態なら
	else
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffff00, false);
	}
	int old_size = GetFontSize();	//元のサイズを保持
	SetFontSize(14);
	DrawBox(0, 200, 260, 400, 0x000000, true);
	DrawBox(0, 200, 260, 400, 0xffffff, false);
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "攻撃%d段階目:%d", i + 1, attack_motion_flg[i]);
			break;
		case 1:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "攻撃%d段階目:%d", i + 1, attack_motion_flg[i]);
			break;
		case 2:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "攻撃%d段階目:%d", i + 1, attack_motion_flg[i]);
			break;
		case 3:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "攻撃%d段階目:%d", i + 1, attack_motion_flg[i]);
			break;
		case 4:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "ジャンプ攻撃:%d", attack_motion_flg[i]);
			break;
		case 5:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "着地攻撃:%d", attack_motion_flg[i]);
			break;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			DrawFormatString(0, 320 + i * 15, 0xffffff, "下加速度:%f", acs[i]);
			break;
		case 1:
			DrawFormatString(0, 320 + i * 15, 0xffffff, "上加速度:%f", acs[i]);
			break;
		case 2:
			DrawFormatString(0, 320 + i * 15, 0xffffff, "右加速度:%f", acs[i]);
			break;
		case 3:
			DrawFormatString(0, 320 + i * 15, 0xffffff, "左加速度:%f", acs[i]);
			break;
		}
	}
	DrawFormatString(0, 290, 0xffffff, "HP %d", hp);
	if (direction == false)
	{
		DrawFormatString(0, 305, 0xffffff, "顔の向き:右", direction);
	}
	else
	{
		DrawFormatString(0, 305, 0xffffff, "顔の向き:左", direction);
	}
	DrawFormatString(0, 380, 0xffffff, "状態:%s", player_state_char[player_state]);
	DrawFormatString(110, 200, 0xffffff, "Q=デバッグ用無敵:%d", d_inv_flg);
	DrawFormatString(110, 230, 0xffffff, "jump_flg=%d", jump_flg);
	SetFontSize(old_size);
#endif // DEBUG
}

void Player::GiveGravity()
{
	if (acs[DOWN] <= GRAVITY_POWER)
	{
		acs[DOWN] += (1.5f + (float)powerup_flg);
	}
}

void Player::DecAcs(int num)
{
	if (acs[num] > 0)
	{
		acs[num] -= 0.5f;
	}
	if (acs[num] < 0)
	{
		acs[num] = 0;
	}
}

void Player::OnFloor()
{
	acs[DOWN] = 0;
	acs[UP] = 0;
	onfloor_flg = true;
	jump_flg = false;
}

void Player::Push(Location _sub_location, Erea _sub_erea ,int _type)
{
	//右の壁に触れた時
	if (location.x + erea.width - 12 < _sub_location.x && location.y + erea.height - 12 > _sub_location.y && (_type == 1 || _type == 3 || _type == 8))
	{
		location.x = _sub_location.x - erea.width;
		//右加速度を0にする
		acs[RIGHT] = 0;
		//右の壁に触れたフラグを立てる
		rightwall_flg = true;
	}
	//左の壁に触れた時
	else if (location.x + 12 > _sub_location.x + _sub_erea.width && location.y + erea.height - 12> _sub_location.y && (_type == 1 || _type == 3 || _type == 8))
	{
		location.x = _sub_location.x + _sub_erea.width;
		//左加速度を0にする
		acs[LEFT] = 0;
		//左の壁に触れたフラグを立てる
		leftwall_flg = true;
	}
	//床に触れた時
	else if (location.y + erea.height -30< _sub_location.y && (_type == 1 || _type == 2 ||_type == 3 || _type == 4 || _type == 8))
	{
		//木と雲は上から降りてきたときだけ乗れるようにする
		if ((_type != 2 && acs[DOWN] - acs[UP] >= 0) || (_type != 4 && acs[DOWN] - acs[UP] >= 0))
		{
			location.y = _sub_location.y - erea.height+0.1f;
			OnFloor();
		}
	}
	//天井に触れた時
	else if (location.y + 30 > _sub_location.y + _sub_erea.height && (_type == 1 || _type == 3))
	{
		location.y = _sub_location.y + _sub_erea.height;
		//上加速度を0にする
		acs[UP] = 0;
		//天井に触れたフラグを立てる
		touch_ceil_flg = true;
	}
	//どっちの壁にも触れていないときの地面すり抜け防止
	//else
	//{
	//	if (onfloor_flg == true)
	//	{
	//		location.y = _sub_location.y - erea.height;
	//		OnFloor();
	//	}
	//	else
	//	{
	//		location.y = _sub_location.y + _sub_erea.height;
	//	}
	//}
}

void Player::Reset()
{
	//重力が働くかの判定をリセット
	apply_gravity = true;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	onfloor_flg = false;
	for (int i = 0; i < 4; i++)
	{
		external_move[i] = 0;
	}
}

void Player::ForciblyMovePlayer(ScrollData _scroll)
{
	if (_scroll.direction == true)
	{
		external_move[RIGHT] += (_scroll.move + acs[LEFT]);
	}
	else
	{
		external_move[LEFT] += (_scroll.move + acs[RIGHT]);
	}
}

void Player::ApplyDamage(GameMain* main,int num)
{
	//無敵状態でない＆死んでいる状態でない、デバッグ用の無敵状態でないなら
	if (inv_flg == false && death_flg == false 
#ifdef _DEBUG
		&& d_inv_flg == false
#endif
		){
		//のけぞる
		acs[UP] += 10;
		acs[!direction + 2] += 10; //今自分の顔が向いている方向と逆方向に
		//体力を減らす
		hp -= num;
		if (hp < 0)
		{
			//仮にHPをリセットする
			/*hp = 5;*/
			//死
			death_flg = true;
			move_flg = false;
		}
		//ダメージ後の無敵状態に入る
		inv_flg = true;
		//カメラを揺らす
		main->ImpactCamera(num * 10);
	}
}

AttackData Player::CreateAttactData(int i)
{
	AttackData attack_data;
	attack_data = player_attack_data[i * 2 + powerup_flg];
	//生成の瞬間に応じて変わる情報はここで格納する
	attack_data.direction = direction;
	//攻撃の角度を顔の向きに応じて変える
	if (attack_data.attack_type == BULLET)
	{
		if (direction == false)
		{
			attack_data.angle = player_attack_data[i * 2 + powerup_flg].angle;
		}
		else
		{
			attack_data.angle = 0.5f - player_attack_data[i * 2 + powerup_flg].angle;
		}
	}
	return attack_data;
}

void Player::SetPowerUp()
{
	powerup_flg = true;								
	acs_max = ACS_MAX * 2;							//最大加速度を2倍
	jump_power = DEFAULT_JUMP_POWER * 1.2f;			//跳躍力を1.2倍
	attack_interval = DEFAULT_ATTACK_INTERVAL / 2;	//攻撃間隔を半分に
	combo_attack_interval = DEFAULT_ATTACK_INTERVAL;//連続攻撃受付時間を半分に
	player_anim_speed = PLAYER_ANIM / 2;			//アニメーション切り替え間隔を二倍
	attack_time = DEFAULT_ATTACK_INTERVAL / 2;		//プレイヤーが動けない時間を半分に
}

void Player::StopPowerUp()
{
	powerup_flg = false;
	//SetPowerUpで変更した値をすべて元通りに
	acs_max = ACS_MAX;
	jump_power = DEFAULT_JUMP_POWER;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
	combo_attack_interval = (int)(DEFAULT_ATTACK_INTERVAL * 1.5f);
	player_anim_speed = PLAYER_ANIM;
	attack_time = DEFAULT_ATTACK_INTERVAL;		
}

void Player::Attack(GameMain* main)
{
	//攻撃
	if (
#ifdef _DEBUG
		(KeyInput::OnKey(KEY_INPUT_RETURN) == true || PadInput::OnButton(XINPUT_BUTTON_B) == true)
#else
		PadInput::OnButton(XINPUT_BUTTON_B) == true
#endif
		&& attack_interval_count <= 0)
	{
		SoundManager::StopSound(PLAYER_ATTACK_SOUND);

		if (acs[DOWN] == 0)
		{
			//攻撃間隔の測定を開始
			attack_interval_count = attack_interval;

			//プレイヤーが移動できない時間
			attack_time_count = attack_time;

			//一定間隔が過ぎる前に攻撃を行っていたなら
			if (ca_interval_count > 0)
			{

				//最大攻撃ではないなら
				if (attack_step < 3)
				{
					attack_step++;
				}
			}
			//一定間隔が過ぎたら
			else
			{
				//攻撃の段階をリセットする
				attack_step = 0;
			}
			//４段目を撃った後に必ず１段目に戻るように間隔を設定する
			if (attack_step >= 3)
			{
				ca_interval_count = 0;
			}
			//それ以外の攻撃の時には正しい間隔を設定する
			else
			{
				ca_interval_count = combo_attack_interval;
			}
			//攻撃を生成する
			main->SpawnAttack(CreateAttactData(attack_step));
			//空中に居ないなら
			SoundManager::StartSound(PLAYER_ATTACK_SOUND);
			//少し前移動
			acs[direction + 2] += 5;
		}
		//空中にいて、落下攻撃中でないなら
		else if (attack_step != 4)
		{
			//落下攻撃を行う
			attack_step = 4;
			//攻撃を生成する
			main->SpawnAttack(CreateAttactData(attack_step));
		}
	}
	//攻撃間隔用変数
	if (attack_interval_count > 0)
	{
		attack_interval_count--;
	}
	//コンボ攻撃間隔用変数(この数値が０以上の時に攻撃を行うと、次の攻撃を行う)
	if (ca_interval_count > 0)
	{
		ca_interval_count--;
	}

	//攻撃演出用
	//落下攻撃以外なら
	switch (attack_step)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		if (--attack_time_count > 0)
		{
			//現在行っている攻撃の段階に応じたフラグをtrueにし、それ以外をfalseにする
			SetAttackFlg(attack_step);
		}
		else
		{
			//行っていた攻撃の段階に応じたフラグをfalseにする
			attack_motion_flg[attack_step] = false;
		}
		break;
	case 4:
		//空中にいる限り攻撃し続ける
		if (onfloor_flg == false)
		{
			//現在行っている攻撃の段階に応じたフラグをtrueにし、それ以外をfalseにする
			SetAttackFlg(attack_step);

		}
		//地面についたら着地攻撃
		else
		{
			//落下攻撃のフラグをfalseにする
			attack_motion_flg[4] = false;
			//着地攻撃の発生
			attack_step = 5;
			//現在行っている攻撃の段階に応じたフラグをtrueにし、それ以外をfalseにする
			SetAttackFlg(attack_step);
			main->SpawnAttack(CreateAttactData(attack_step));
			//攻撃間隔の測定を開始
			attack_interval_count = attack_interval;
			//プレイヤーが移動できない時間
			attack_time_count = attack_time - 10;
		}
		break;
	case 5:
		if (--attack_time_count >= 0)
		{
			//現在行っている攻撃の段階に応じたフラグをtrueにし、それ以外をfalseにする
			SetAttackFlg(attack_step);
		}
		else
		{
			//行っていた攻撃の段階に応じたフラグをfalseにする
			attack_motion_flg[attack_step] = false;
		}
		break;
	}
}

void Player::Move(GameMain* main)
{
	//いずれかの攻撃が発生しているか、ダメージを受けている途中か、死んでいる途中なら
	if ((PlayAnyAttack() == true && attack_motion_flg[4] == false) || damage_flg == true || death_flg == true)
	{
		//動けなくする
		move_flg = false;
	}
	//どちらでもないなら
	else
	{
		//動けるようにする
		move_flg = true;
	}

	//左移動
	if (
#ifdef _DEBUG
	(KeyInput::OnPresed(KEY_INPUT_A) == true || PadInput::TipLeftLStick(STICKL_X) <= -0.5)
#else
		PadInput::TipLeftLStick(STICKL_X) <= -0.5
#endif
		&& move_flg == true)
	{
		//壁に触れていないなら
		if (rightwall_flg == false)
		{
			//最大加速度以下なら
			if (acs[LEFT] <= acs_max)
			{
				//加速度を加算する
				acs[LEFT] += move_speed;
			}
			else
			{
				acs[LEFT] = acs_max;
			}
		}
	}
	else
		{
			DecAcs(LEFT);
		}

	//右移動
	if (
#ifdef _DEBUG
	(KeyInput::OnPresed(KEY_INPUT_D) == true || PadInput::TipLeftLStick(STICKL_X) >= 0.5)
#else
		PadInput::TipLeftLStick(STICKL_X) >= 0.5
#endif 
		&& move_flg == true)
		{
			if (leftwall_flg == false)
			{
				if (acs[RIGHT] <= acs_max)
				{
					acs[RIGHT] += move_speed;
				}
				else
				{
					acs[RIGHT] = acs_max;
				}
			}
		}
	else
		{
			DecAcs(RIGHT);
		}

	

	//ジャンプ
	if (
#ifdef _DEBUG
	(KeyInput::OnKey(KEY_INPUT_SPACE) == true || PadInput::OnButton(XINPUT_BUTTON_A) == true)
#else
		PadInput::OnButton(XINPUT_BUTTON_A) == true
#endif
		&& jump_flg == false && move_flg == true)
		{
			acs[UP] = jump_power;
			jump_flg = true;
			
		}
	else
		{
			//ジャンプしていない時は上に加速する力を弱める
			DecAcs(UP);
		}
	

	//顔の方向処理
	if (acs[LEFT] < acs[RIGHT] && move_flg == true)
	{
		direction = false;
	}
	if (acs[LEFT] > acs[RIGHT] && move_flg == true)
	{
		direction = true;
	}
	
	//ジャンプ中にダメージを受けた時、急速落下する
	if (jump_flg == true && damage_flg == true)
	{
		acs[DOWN]++;
	}
	//カメラ端より先には行けない
	if (main->GetCameraLocation().x+100 > location.x)
	{
		location.x = main->GetCameraLocation().x + 100;
	}
	if (main->GetCameraLocation().x + SCREEN_WIDTH - erea.width-100 < location.x)
	{
		location.x = main->GetCameraLocation().x + SCREEN_WIDTH - erea.width - 100;
	}
	if (main->GetCameraLocation().y + 50 > location.y)
	{
		location.y = main->GetCameraLocation().y + 50;
	}
	//1フレーム前の座標を保存
	old_location = location;
	//移動処理
	next_location.x = location.x - acs[LEFT] + acs[RIGHT];
	if (next_location.x < 0)
	{
		next_location.x = old_location.x;
	}
	next_location.y = location.y - acs[UP] + acs[DOWN];
	MoveLocation(main, next_location.x - old_location.x, next_location.y - old_location.y);

	
	

	//Y座標が一定を上回ったら死
	if (location.y > main->GetStageHeight() + 100)
	{
		death_flg = true;
		move_flg = false;
	}
}

void Player::Anim()
{
	//アニメーション用変数を回す
	if (frame % (PLAYER_ANIM-(int)powerup_flg) == 0)
	{
		if (++player_anim > 5)
		{
			player_anim = 0;
		}
	}
	//攻撃アニメーション用変数を回す
	if (PlayAnyAttack() == true)
	{
		if (frame % (player_anim_speed/2) == 0 && attack_anim < 11)
		{
			attack_anim++;
		}
	}
	//攻撃アニメーション用変数をリセット
	else
	{
		attack_anim = 0;
	}
	//無敵時間中なら
	if (inv_flg == true)
	{
		//5フレーム毎に
		if (frame % 5 == 0)
		{
			//表示するかしないかを切り替える
			hidden_flg = !hidden_flg;
		}
	}
	//無敵時間でないなら
	else
	{
		//常に画像表示状態に
		hidden_flg = false;
	}
}

void Player::UpdatePlayerState()
{
	//顔の向きによって変える
	//右向き
	if (direction == false)
	{
		//重力が加わっているなら
		if (onfloor_flg == false)
		{
			player_state = FALL_RIGHT;
			if (jump_flg == true && acs[UP] >= acs[DOWN])
			{
				player_state = JUMP_RIGHT;
			}
		}
		//重力が加わっていない（地面にいるなら）
		else
		{
			player_state = IDOL_RIGHT;
			//右に移動しているなら
			if (acs[LEFT] < acs[RIGHT])
			{
				player_state = MOVE_RIGHT;
			}
			//左に移動しているなら
			if (acs[LEFT] > acs[RIGHT])
			{
				player_state = MOVE_LEFT;
			}
		}
		//攻撃中なら
		if (attack_motion_flg[0] == true)
		{
			player_state = ATTACK_RIGHT_ONE;
		}
		if (attack_motion_flg[1] == true)
		{
			player_state = ATTACK_RIGHT_TWO;
		}
		if (attack_motion_flg[2] == true)
		{
			player_state = ATTACK_RIGHT_THREE;
		}
		if (attack_motion_flg[3] == true)
		{
			player_state = ATTACK_RIGHT_FOUR;
		}
		if (attack_motion_flg[4] == true)
		{
			player_state = JUMP_ATTACK_RIGHT;
		}
		if (attack_motion_flg[5] == true)
		{
			player_state = JUMP_ATTACK_RIGHT_END;
		}
		//ダメージを喰らった状態なら
		if (damage_flg == true)
		{
			player_state = DAMAGE_RIGHT;
		}
		//死んでいるなら
		if (death_flg == true)
		{
			player_state = DEATH_RIGHT;
		}
	}
	//左向き
	else
	{
		//重力が加わっているなら
		if (onfloor_flg == false)
		{
			player_state = FALL_LEFT;
			if (jump_flg == true && acs[UP] >= acs[DOWN])
			{
				player_state = JUMP_LEFT;
			}
		}
		//重力が加わっていない（地面にいるなら）
		else
		{
			player_state = IDOL_LEFT;
			//右に移動しているなら
			if (acs[LEFT] < acs[RIGHT])
			{
				player_state = MOVE_RIGHT;
			}
			//左に移動しているなら
			if (acs[LEFT] > acs[RIGHT])
			{
				player_state = MOVE_LEFT;
			}
		}
		//攻撃中なら
		if (attack_motion_flg[0] == true)
		{
			player_state = ATTACK_LEFT_ONE;
		}
		if (attack_motion_flg[1] == true)
		{
			player_state = ATTACK_LEFT_TWO;
		}
		if (attack_motion_flg[2] == true)
		{
			player_state = ATTACK_LEFT_THREE;
		}
		if (attack_motion_flg[3] == true)
		{
			player_state = ATTACK_LEFT_FOUR;
		}
		if (attack_motion_flg[4] == true)
		{
			player_state = JUMP_ATTACK_LEFT;
		}
		if (attack_motion_flg[5] == true)
		{
			player_state = JUMP_ATTACK_LEFT_END;
		}

		//ダメージを喰らった状態なら
		if (damage_flg == true)
		{
			player_state = DAMAGE_LEFT;
		}
		//死んでいるなら
		if (death_flg == true)
		{
			player_state = DEATH_LEFT;
		}
	}
}

bool Player::PlayAnyAttack()
{
	bool ret = false;
	for (int i = 0; i < ATTACK_PATTERN; i++)
	{
		//いずれかの攻撃を行っている最中ならフラグをtrueにする
		if (attack_motion_flg[i] == true)
		{
			ret = true;
		}
	}
	return ret;
}

void Player::SetAttackFlg(int num)
{
	for (int i = 0; i < ATTACK_PATTERN; i++)
	{
		//指定した数字以外の攻撃フラグを下げる
		if (i != num)
		{
			attack_motion_flg[i] = false;
		}
		//指定した数字の攻撃フラグを立てる
		else
		{
			attack_motion_flg[i] = true;
		}
	}
}

void Player::SetPlayerAttackData()
{
	//一段階目　
	player_attack_data[0].shift_x = -erea.width;
	player_attack_data[0].shift_y = -100;
	player_attack_data[0].width = erea.width + 120;
	player_attack_data[0].height = 220;
	player_attack_data[0].who_attack = 0;
	player_attack_data[0].attack_time = 17;
	player_attack_data[0].damage = 1;
	player_attack_data[0].delay = 8;
	player_attack_data[0].attack_type = MELEE;
	player_attack_data[0].effect_type = PLAYER_SLASH_ONE;
	//一段階目　強化中
	player_attack_data[1].shift_x = -erea.width;
	player_attack_data[1].shift_y = -110;
	player_attack_data[1].width = erea.width + 110;
	player_attack_data[1].height = 350;
	player_attack_data[1].who_attack = 0;
	player_attack_data[1].attack_time = 8;
	player_attack_data[1].damage = 3;
	player_attack_data[1].delay = 4;
	player_attack_data[1].attack_type = BULLET;
	player_attack_data[1].angle = 0.0f;
	player_attack_data[1].speed = 20;
	player_attack_data[1].effect_type = POWERUP_PLAYER_SLASH_ONE;
	//二段階目
	player_attack_data[2].shift_x = -20;
	player_attack_data[2].shift_y = -120;
	player_attack_data[2].width = 150;
	player_attack_data[2].height = 210;
	player_attack_data[2].who_attack = 0;
	player_attack_data[2].attack_time = 17;
	player_attack_data[2].damage = 1;
	player_attack_data[2].delay = 5;
	player_attack_data[2].attack_type = MELEE;
	player_attack_data[2].effect_type = PLAYER_SLASH_TWO;
	//二段階目　強化中
	player_attack_data[3].shift_x = -erea.width;
	player_attack_data[3].shift_y = -70;
	player_attack_data[3].width = erea.width + 120;
	player_attack_data[3].height = 230;
	player_attack_data[3].who_attack = 0;
	player_attack_data[3].attack_time = 8;
	player_attack_data[3].damage = 2;
	player_attack_data[3].delay = 2;
	player_attack_data[3].attack_type = BULLET;
	player_attack_data[3].angle = 0.0f;
	player_attack_data[3].speed = 20;
	player_attack_data[3].effect_type = POWERUP_PLAYER_SLASH_TWO;
	//三段階目
	player_attack_data[4].shift_x = -erea.width;
	player_attack_data[4].shift_y = -100;
	player_attack_data[4].width = erea.width + 190;
	player_attack_data[4].height = 250;
	player_attack_data[4].who_attack = 0;
	player_attack_data[4].attack_time = 16;
	player_attack_data[4].damage = 1;
	player_attack_data[4].delay = 4;
	player_attack_data[4].attack_type = MELEE;
	player_attack_data[4].effect_type = PLAYER_SLASH_THREE;
	//三段階目　強化中
	player_attack_data[5].shift_x = -erea.width;
	player_attack_data[5].shift_y = -100;
	player_attack_data[5].width = erea.width + 190;
	player_attack_data[5].height = 250;
	player_attack_data[5].who_attack = 0;
	player_attack_data[5].attack_time = 13;
	player_attack_data[5].damage = 2;
	player_attack_data[5].delay = 2;
	player_attack_data[5].attack_type = BULLET;
	player_attack_data[5].angle = 0.0f;
	player_attack_data[5].speed = 15;
	player_attack_data[5].effect_type = POWERUP_PLAYER_SLASH_THREE;
	//四段階目
	player_attack_data[6].shift_x = -erea.width;
	player_attack_data[6].shift_y = -120;
	player_attack_data[6].width = erea.width + 250;
	player_attack_data[6].height = 260;
	player_attack_data[6].who_attack = 0;
	player_attack_data[6].attack_time = 15;
	player_attack_data[6].damage = 2;
	player_attack_data[6].delay = 5;
	player_attack_data[6].attack_type = MELEE;
	player_attack_data[6].effect_type = PLAYER_SLASH_FOUR;
	//四段階目　強化中
	player_attack_data[7].shift_x = -erea.width;
	player_attack_data[7].shift_y = -120;
	player_attack_data[7].width = erea.width + 250;
	player_attack_data[7].height = 260;
	player_attack_data[7].who_attack = 0;
	player_attack_data[7].attack_time = 15;
	player_attack_data[7].damage = 3;
	player_attack_data[7].delay = 2;
	player_attack_data[7].attack_type = BULLET;
	player_attack_data[7].angle = 0.0f;
	player_attack_data[7].speed = 20;
	player_attack_data[7].effect_type = POWERUP_PLAYER_SLASH_FOUR;
	//ジャンプ攻撃
	player_attack_data[8].shift_x = -erea.width;
	player_attack_data[8].shift_y = 0;
	player_attack_data[8].width = erea.width+120;
	player_attack_data[8].height = 150;
	player_attack_data[8].who_attack = 0;
	player_attack_data[8].attack_time = 300;
	player_attack_data[8].damage = 1;
	player_attack_data[8].delay = 5;
	player_attack_data[8].attack_type = MELEE;
	player_attack_data[8].effect_type = PLAYER_JUMP_SLASH;
	//ジャンプ攻撃　強化中
	player_attack_data[9].shift_x = 0;
	player_attack_data[9].shift_y = 50;
	player_attack_data[9].width = 100;
	player_attack_data[9].height = 150;
	player_attack_data[9].who_attack = 0;
	player_attack_data[9].attack_time = 300;
	player_attack_data[9].damage = 1;
	player_attack_data[9].delay = 0;
	player_attack_data[9].attack_type = MELEE;
	player_attack_data[9].effect_type = POWERUP_PLAYER_JUMP_SLASH;
	//ジャンプ攻撃からの着地攻撃
	player_attack_data[10].shift_x = 0;
	player_attack_data[10].shift_y = 50;
	player_attack_data[10].width = 100;
	player_attack_data[10].height = 100;
	player_attack_data[10].who_attack = 0;
	player_attack_data[10].attack_time = 10;
	player_attack_data[10].damage = 2;
	player_attack_data[10].delay = 0;
	player_attack_data[10].attack_type = BULLET;
	player_attack_data[10].angle = 0.0f;
	player_attack_data[10].speed = 10;
	player_attack_data[10].effect_type = PLAYER_JUMP_SLASH_END;
	//ジャンプ攻撃からの着地攻撃　強化用
	player_attack_data[11].shift_x = 0;
	player_attack_data[11].shift_y = 50;
	player_attack_data[11].width = 250;
	player_attack_data[11].height = 100;
	player_attack_data[11].who_attack = 0;
	player_attack_data[11].attack_time = 10;
	player_attack_data[11].damage = 2;
	player_attack_data[11].delay = 0;
	player_attack_data[11].attack_type = BULLET;
	player_attack_data[11].angle = 0.0f;
	player_attack_data[11].speed = 12;
	player_attack_data[11].effect_type = POWERUP_PLAYER_JUMP_SLASH_END;
}

void Player::Respawn(Location _location)
{
	location = _location;
	player_state = IDOL_RIGHT;
	StopPowerUp();
	hp = 5;
	direction = false;
	attack_interval_count = 0;
	ca_interval_count = 0;
	attack_step = 0;
	attack_time_count = 0;
	for (int i = 0; i < ATTACK_PATTERN; i++)
	{
		attack_motion_flg[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		acs[i] = 0;
		external_move[i] = 0;
	}
	onfloor_flg = false;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	jump_flg = false;
	move_flg = true;
	attack_anim_flg = false;
	player_anim = 0;
	attack_anim = 0;
	inv_flg = true;
	inv_time = DEFAULT_INVINCIBLE_TIME;
	damage_flg = false;
	hidden_flg = false;
	death_flg = false;
	death_time = 120;
	damage_time = 0;
}

void Player::MoveLocation(GameMain* main, float _x, float _y)
{
	for (int i = 0; i < (int)(fabsf(_y) * 10); i++)
	{
		if (_y > 0)
		{
			main->PlayerFloorHitCheck();
			if (onfloor_flg == false)location.y += 0.1f;
		}
		else if (_y < 0)
		{
			main->PlayerFloorHitCheck();
			location.y -= 0.1f;
		}
	}
	for (int i = 0; i < (int)(fabsf(_x)*10); i++)
	{
		if (_x > 0)
		{
			main->PlayerFloorHitCheck();
			location.x+=0.1f;
		}
		else if(_x < 0)
		{
			main->PlayerFloorHitCheck();
			location.x-=0.1f;
		}
	}
}

void Player::PlayerSound()
{

	if (jump_flg==true) {
		SoundManager::StartSound(PLAYER_JUMP_SOUND);
	}
	else {
		SoundManager::StopSound(PLAYER_JUMP_SOUND);
	}

	//歩行音を再生する
	if (next_location.x != old_location.x && onfloor_flg == true)
	{
		SoundManager::StartSound(PLAYER_WALK_SOUND);
	}
	else if (next_location.x == old_location.x) {
		SoundManager::StopSound(PLAYER_WALK_SOUND);

	}
}
