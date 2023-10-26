#include "Player.h"
#include "PadInput.h"

#define ACS_MAX 6	//最大加速度
#define DOWN 0	//下加速度用
#define UP 1	//上加速度用
#define RIGHT 2	//右加速度用
#define LEFT 3	//左加速度用

#define DEFAULT_MOVE_SPEED 0.3f			//基本移動速度(左右)
#define DEFAULT_JUMP_POWER 26			//基本最大跳躍力
#define GRAVITY_POWER  (ACS_MAX * 2.5f) //重力の強さ
#define DEFAULT_ATTACK_INTERVAL	30		//基本攻撃間隔(フレーム)
#define DEFAULT_INVINCIBLE_TIME	80		//基本無敵時間(攻撃を喰らった後)

#define PLAYER_IMAGE_SHIFT_X 80			//画像ずらし用
#define PLAYER_IMAGE_SHIFT_Y 105		//画像ずらし用
#define PLAYER_IDOL 0					//立ち姿アニメーション開始地点
#define PLAYER_WALK 1					//移動アニメーション開始地点
#define PLAYER_JUMP 4					//ジャンプアニメーション開始地点
#define PLAYER_ATTACK_ONE 5				//攻撃１段目アニメーション開始地点
#define PLAYER_ATTACK_TWO 8				//攻撃２段目アニメーション開始地点
#define PLAYER_ATTACK_THREE 11			//攻撃３段目アニメーション開始地点
#define PLAYER_ATTACK_FOUR 14			//攻撃４段目アニメーション開始地点
#define PLAYER_JUMP_ATTACK 12			//ジャンプ攻撃アニメーション開始地点
#define PLAYER_JUMP_ATTACK_END 16		//ジャンプ攻撃（着地）アニメーション開始地点
#define PLAYER_ANIM 10					//次の画像に切り替えるまでの時間（フレーム）
Player::Player()
{
	frame = 0;
	player_state = IDOL_RIGHT;
	old_location = { 0 };
	location.x = 100;
	location.y = 400;
	erea.height = PLAYER_HEIGHT;
	erea.width = PLAYER_WIDTH;
	who = 0;
	hp = 10;
	move_speed = DEFAULT_MOVE_SPEED;
	jump_power = DEFAULT_JUMP_POWER;
	direction = false;
	attack_interval_count = 0;
	ca_interval_count = 0;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
	combo_attack_interval = DEFAULT_ATTACK_INTERVAL * 1.5f;
	attack_step = 0;
	attack_time = 0;
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		attack_motion_flg[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		acs[i] = 0;
		external_move[i] = 0;
	}
	acs_max = ACS_MAX;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	jump_flg = false;
	powerup_flg = false;
	move_flg = true;
	attack_anim_flg = false;
	SetPlayerAttackData();
	LoadDivGraph("resource/images/PlayerAnimation.png", 18, 6, 3, 256, 256, player_image);
	player_anim = 0;
	attack_anim = 0;
	player_anim_speed = PLAYER_ANIM;
	inv_flg = false;
	damage_flg = false;
	inv_time = DEFAULT_INVINCIBLE_TIME;
	damage_time = DEFAULT_INVINCIBLE_TIME / 2;
	hidden_flg = true;
}

Player::~Player() 
{

}

void Player::Update(GameMain* main)
{

	frame++;
	//重力を加えるかの処理
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		if (onfloor_flg[i] == true)
		{
			apply_gravity = false;
		}
	}
	//床に触れていないなら
	if (apply_gravity == true)
	{
		//重力を与える
		GiveGravity();
	}

	//攻撃
	Attack(main);

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

	//いずれかの攻撃が発生しているか、ダメージを受けている途中なら
	if (PlayAnyAttack() == true || damage_flg == true)
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

	//移動処理
	Move();

	//プレイヤーの状態を更新する
	UpdatePlayerState();


	//各移動用変数をリセット
	Reset();

	//描画関連の変数を動かす
	Anim();
}

void Player::Draw()const
{
	SetFontSize(24);
	//強化状態でないなら
	if (powerup_flg == false)
	{
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff0000, true);
		//顔の向き
		if (direction == false)
		{
			DrawBox(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
		}
		else
		{
			DrawBox(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
		}
	}
	else
	{
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffff00, true);
		//顔の向き
		if (direction == false)
		{
			DrawBox(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0xff0000, true);
		}
		else
		{
			DrawBox(location.x + 40, location.y + 10, location.x, location.y + 40, 0xff0000, true);
		}
	}

	//デバッグ用表示
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(0, 100+i*30, 0x00ff00, "%d", attack_motion_flg[i]);
	}
	DrawFormatString(360, 360, 0xfffff0, "HP %d", hp);
	DrawFormatString(360, 380, 0xfffff0, "direction %d", direction);

	//プレイヤー画像表示
	if (hidden_flg == true)
	{
		switch (player_state)
		{
		case IDOL_RIGHT:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL], true);
			break;
		case IDOL_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL], true);
			break;
		case MOVE_RIGHT:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_WALK + walk_anim_num[player_anim]], true);
			break;
		case MOVE_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_WALK + walk_anim_num[player_anim]], true);
			break;
		case JUMP_RIGHT:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case JUMP_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case FALL_RIGHT:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case FALL_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case ATTACK_RIGHT_ONE:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_ONE + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_RIGHT_TWO:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_TWO + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_RIGHT_THREE:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_THREE + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_RIGHT_FOUR:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_FOUR + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_LEFT_ONE:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_ONE + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_LEFT_TWO:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_TWO + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_LEFT_THREE:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_THREE + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_LEFT_FOUR:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_FOUR + attack_anim_num[attack_anim]], true);
			break;
		case JUMP_ATTACK_RIGHT:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK], true);
			break;
		case JUMP_ATTACK_RIGHT_END:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK_END], true);
			break;
		case JUMP_ATTACK_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK], true);
			break;
		case JUMP_ATTACK_LEFT_END:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK_END], true);
			break;
		case DAMAGE_RIGHT:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[17], true);
			break;
		case DAMAGE_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[17], true);
			break;
		}
	}
}

void Player::GiveGravity()
{
	if (acs[DOWN] <= GRAVITY_POWER)
	{
		acs[DOWN] += 1.5f;
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

void Player::OnFloor(int num,Location _sub)
{
	acs[DOWN] = 0;
	acs[UP] = 0.05f;
	onfloor_flg[num] = true;
	jump_flg = false;
}

void Player::TouchCeiling()
{
	acs[UP] = 0;
	touch_ceil_flg = true;
}

void Player::TouchRightWall()
{
	acs[RIGHT] = 0;
	rightwall_flg = true;
}

void Player::TouchLeftWall()
{
	acs[LEFT] = 0;
	leftwall_flg = true;
}

void Player::Push(int num,Location _sub_location, Erea _sub_erea)
{
	Location p_center = { 0 };
	p_center.x = location.x + (erea.width / 2);
	p_center.y = location.y + (erea.height / 2);

	//床に触れた時
	if (location.y +erea.height-12 < _sub_location.y)
	{
		location.y = _sub_location.y- erea.height+0.1f;
		OnFloor(num, _sub_location);
	}
	//天井に触れた時
	else if (location.y +20> _sub_location.y + _sub_erea.height)
	{
		location.y = _sub_location.y + _sub_erea.height;
		TouchCeiling();
	}
	//右の壁に触れた時
	else if (location.x +erea.width-10 < _sub_location.x)
	{
		location.x = _sub_location.x - erea.width;
		TouchRightWall();
	}
	//左の壁に触れた時
	else if (location.x+10 > _sub_location.x + _sub_erea.width)
	{
		location.x = _sub_location.x + _sub_erea.width;
		TouchLeftWall();
	}
	//どっちの壁にも触れていないときの地面すり抜け防止
	else
	{
		location.y = _sub_location.y - erea.height;
		OnFloor(num, _sub_location);
	}
}

void Player::Reset()
{
	//重力が働くかの判定をリセット
	apply_gravity = true;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
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

void Player::ApplyDamage(int num)
{
	//無敵状態でないなら
	if (inv_flg == false)
	{
		//のけぞる
		acs[UP] += 10;
		acs[!direction + 2] += 10; //今自分の顔が向いている方向と逆方向に
		//体力を減らす
		hp -= num;
		if (hp < 0)
		{
			//仮にHPをリセットする
			hp = 5;
		}
		//ダメージ後の無敵状態に入る
		inv_flg = true;
	}
}

AttackData Player::CreateAttactData(int i)
{
	AttackData attack_data;
	attack_data = player_attack_data[i * 2 + powerup_flg];
	//生成の瞬間に応じて変わる情報はここで格納する
	attack_data.direction = direction;
	return attack_data;
}

void Player::SetPowerUp()
{
	powerup_flg = true;
	acs_max = ACS_MAX * 2;
	jump_power = DEFAULT_JUMP_POWER * 1.1;
	attack_interval = DEFAULT_ATTACK_INTERVAL / 2;
	player_anim_speed = PLAYER_ANIM / 2;
}

void Player::StopPowerUp()
{
	powerup_flg = false;
	acs_max = ACS_MAX;
	jump_power = DEFAULT_JUMP_POWER;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
	player_anim_speed = PLAYER_ANIM;
}

void Player::Attack(GameMain* main)
{
	//攻撃
	if (PadInput::OnButton(XINPUT_BUTTON_B) == true && attack_interval_count <= 0)
	{
		//空中に居ないなら
		if (acs[DOWN] == 0)
		{
			//攻撃間隔の測定を開始
			attack_interval_count = attack_interval;
			//プレイヤーが移動できない時間
			if (powerup_flg == false)
			{
				attack_time = DEFAULT_ATTACK_INTERVAL;
			}
			else
			{
				attack_time = DEFAULT_ATTACK_INTERVAL/2;
			}
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
			//４段目を撃った後に必ず１段目に戻るようにする
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
		}
		//空中にいるなら
		else
		{
			//落下攻撃を行う
			attack_step = 4;
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
		if (--attack_time > 0)
		{
			//現在行っている攻撃の段階に応じたフラグをtrueにする
			attack_motion_flg[attack_step] = true;
		}
		else
		{
			//行っていた攻撃の段階に応じたフラグをfalseにする
			attack_motion_flg[attack_step] = false;
		}
		break;
	case 4:
		//空中にいる限り攻撃し続ける
		if (OnAnyFloorFlg() == false)
		{
			//現在行っている攻撃の段階に応じたフラグをtrueにする
			attack_motion_flg[attack_step] = true;
			//攻撃を生成する
			main->SpawnAttack(CreateAttactData(attack_step));

		}
		//地面についたら攻撃終了
		else
		{
			//落下攻撃のフラグをfalseにする
			attack_motion_flg[4] = false;
			//着地攻撃の発生
			attack_step = 5;
			main->SpawnAttack(CreateAttactData(attack_step));
			//プレイヤーが移動できない時間
			if (powerup_flg == false)
			{
				attack_time = DEFAULT_ATTACK_INTERVAL;
			}
			else
			{
				attack_time = DEFAULT_ATTACK_INTERVAL / 2;
			}
		}
		break;
	case 5:
		if (--attack_time > 0)
		{
			//現在行っている攻撃の段階に応じたフラグをtrueにする
			attack_motion_flg[attack_step] = true;
		}
		else
		{
			//行っていた攻撃の段階に応じたフラグをfalseにする
			attack_motion_flg[attack_step] = false;
		}
		break;
	}
}

void Player::Move()
{
	//左移動
	if (PadInput::TipLeftLStick(STICKL_X) <= -0.5 && move_flg == true)
	{
		if (acs[LEFT] <= acs_max && rightwall_flg == false)
			{
				acs[LEFT] += move_speed;
			}
	}
	else
		{
			DecAcs(LEFT);
		}

	//右移動
	if (PadInput::TipLeftLStick(STICKL_X) >= 0.5 && move_flg == true)
		{
			if (acs[RIGHT] <= acs_max && leftwall_flg == false)
			{
				acs[RIGHT] += move_speed;
			}
		}
	else
		{
			DecAcs(RIGHT);
		}
	//ジャンプ
	if (PadInput::OnButton(XINPUT_BUTTON_A) == true && jump_flg == false && move_flg == true)
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
	
	//1フレーム前の座標を保存
	old_location = location;
	//移動処理
	location.x = location.x - acs[LEFT] + acs[RIGHT] - external_move[LEFT] + external_move[RIGHT];
	location.y = location.y - acs[UP] + acs[DOWN] - external_move[UP] + external_move[DOWN];
}

void Player::Anim()
{
	//アニメーション用変数を回す
	if (frame % player_anim_speed == 0)
	{
		if (++player_anim > 3)
		{
			player_anim = 0;
		}
	}
	//攻撃アニメーション用変数を回す
	if (PlayAnyAttack() == true)
	{
		if (frame % player_anim_speed == 0 && attack_anim < 3)
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
		hidden_flg = true;
	}
}

void Player::UpdatePlayerState()
{
	//顔の向きによって変える
	//右向き
	if (direction == false)
	{
		//重力が加わっているなら
		if (apply_gravity == true)
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
	}
	//左向き
	else
	{
		//重力が加わっているなら
		if (apply_gravity == true)
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
	}
}

bool Player::OnAnyFloorFlg()
{
	bool ret = false;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		//触れている床があればループを抜ける
		if (onfloor_flg[i] == true)
		{
			ret = true;
		}
	}
	return ret;
}

bool Player::PlayAnyAttack()
{
	bool ret = false;
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//いずれかの攻撃を行っている最中ならフラグをtrueにする
		if (attack_motion_flg[i] == true)
		{
			ret = true;
		}
	}
	return ret;
}

void Player::SetPlayerAttackData()
{
	//一段階目　
	player_attack_data[0].shift_x = -erea.width;
	player_attack_data[0].shift_y = -50;
	player_attack_data[0].width = erea.width + 100;
	player_attack_data[0].height = 200;
	player_attack_data[0].who_attack = 0;
	player_attack_data[0].attack_time = 10;
	player_attack_data[0].damage = 1;
	player_attack_data[0].delay = 10;
	//一段階目　強化中
	player_attack_data[1].shift_x = -erea.width;
	player_attack_data[1].shift_y = -50;
	player_attack_data[1].width = erea.width + 110;
	player_attack_data[1].height = 220;
	player_attack_data[1].who_attack = 0;
	player_attack_data[1].attack_time = 5;
	player_attack_data[1].damage = 3;
	player_attack_data[1].delay = 5;
	//二段階目
	player_attack_data[2].shift_x = -erea.width;
	player_attack_data[2].shift_y = -70;
	player_attack_data[2].width = erea.width + 100;
	player_attack_data[2].height = 210;
	player_attack_data[2].who_attack = 0;
	player_attack_data[2].attack_time = 10;
	player_attack_data[2].damage = 1;
	player_attack_data[2].delay = 10;
	//二段階目　強化中
	player_attack_data[3].shift_x = -erea.width;
	player_attack_data[3].shift_y = -70;
	player_attack_data[3].width = erea.width + 120;
	player_attack_data[3].height = 230;
	player_attack_data[3].who_attack = 0;
	player_attack_data[3].attack_time = 5;
	player_attack_data[3].damage = 3;
	player_attack_data[3].delay = 5;
	//三段階目
	player_attack_data[4].shift_x = -erea.width;
	player_attack_data[4].shift_y = 50;
	player_attack_data[4].width = erea.width + 170;
	player_attack_data[4].height = 100;
	player_attack_data[4].who_attack = 0;
	player_attack_data[4].attack_time = 10;
	player_attack_data[4].damage = 1;
	player_attack_data[4].delay = 5;
	//三段階目　強化中
	player_attack_data[5].shift_x = -erea.width;
	player_attack_data[5].shift_y = 40;
	player_attack_data[5].width = erea.width + 250;
	player_attack_data[5].height = 110;
	player_attack_data[5].who_attack = 0;
	player_attack_data[5].attack_time = 10;
	player_attack_data[5].damage = 1;
	player_attack_data[5].delay = 5;
	//四段階目
	player_attack_data[6].shift_x = -erea.width;
	player_attack_data[6].shift_y = -90;
	player_attack_data[6].width = erea.width + 150;
	player_attack_data[6].height = 200;
	player_attack_data[6].who_attack = 0;
	player_attack_data[6].attack_time = 10;
	player_attack_data[6].damage = 1;
	player_attack_data[6].delay = 10;
	//四段階目　強化中
	player_attack_data[7].shift_x = -erea.width;
	player_attack_data[7].shift_y = -90;
	player_attack_data[7].width = erea.width + 200;
	player_attack_data[7].height = 200;
	player_attack_data[7].who_attack = 0;
	player_attack_data[7].attack_time = 10;
	player_attack_data[7].damage = 1;
	player_attack_data[7].delay = 10;
	//ジャンプ攻撃
	player_attack_data[8].shift_x = -erea.width;
	player_attack_data[8].shift_y = 50;
	player_attack_data[8].width = erea.width+100;
	player_attack_data[8].height = 100;
	player_attack_data[8].who_attack = 0;
	player_attack_data[8].attack_time = 2;
	player_attack_data[8].damage = 1;
	player_attack_data[8].delay = 0;
	//ジャンプ攻撃　強化中
	player_attack_data[9].shift_x = 0;
	player_attack_data[9].shift_y = 50;
	player_attack_data[9].width = 100;
	player_attack_data[9].height = 150;
	player_attack_data[9].who_attack = 0;
	player_attack_data[9].attack_time = 2;
	player_attack_data[9].damage = 1;
	player_attack_data[9].delay = 0;
	//ジャンプ攻撃からの着地攻撃
	player_attack_data[10].shift_x = 0;
	player_attack_data[10].shift_y = 50;
	player_attack_data[10].width = 200;
	player_attack_data[10].height = 100;
	player_attack_data[10].who_attack = 0;
	player_attack_data[10].attack_time = 10;
	player_attack_data[10].damage = 2;
	player_attack_data[10].delay = 0;
	//ジャンプ攻撃からの着地攻撃　強化用
	player_attack_data[11].shift_x = 0;
	player_attack_data[11].shift_y = 50;
	player_attack_data[11].width = 250;
	player_attack_data[11].height = 100;
	player_attack_data[11].who_attack = 0;
	player_attack_data[11].attack_time = 5;
	player_attack_data[11].damage = 2;
	player_attack_data[11].delay = 0;
}