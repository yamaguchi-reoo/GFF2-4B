#include"Attack.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define CUT_ANIM_TIME 20

Attack::Attack()
{
	attack_flg = false;
	attack_data = { 0 };
	can_apply_damage = false;
	once = false;
	cut_flg = false;
	cut_time = 0;
	LoadDivGraph("resource/images/Boss/BossBullet.png", 2, 2, 1, 100, 64, bullet_img[BOSSHIMAWARI_BULLET]);
	LoadDivGraph("resource/images/SlashEffect.png", 5, 5, 1, 200, 200, slash_img);
	bullet_img[PLAYER_SLASH_ONE][0] = slash_img[0];
	bullet_img[PLAYER_SLASH_TWO][0] = slash_img[1];
	bullet_img[PLAYER_SLASH_THREE][0] = slash_img[2];
	bullet_img[PLAYER_SLASH_FOUR][0] = slash_img[3];
	bullet_img[4][0] = slash_img[4];
}

Attack::~Attack()
{

}

void Attack::Update(Location _location, Erea _erea)
{
	//ÉvÉåÉCÉÑÅ[ÇÃçUåÇèàóù
	if (attack_flg == true && --attack_data.delay < 0)
	{
		//çUåÇâ¬î\
		can_apply_damage = true;
		//çUåÇÇÃéÌóﬁÇ…âûÇ∂ÇƒãììÆÇïœÇ¶ÇÈ
		switch (attack_data.attack_type)
		{
		case MELEE:
			//âEï˚å¸Ç…çUåÇÇ∑ÇÈ
			if (attack_data.direction == false)
			{
				location.x = _location.x + (_erea.width / 2) + attack_data.shift_x;
				location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

			}
			//ç∂ï˚å¸Ç…çUåÇÇ∑ÇÈ
			else
			{
				location.x = _location.x - erea.width - (_erea.width / 2) - attack_data.shift_x;
				location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

			}
			break;
		case BULLET:
			//àÍâÒÇæÇØç¿ïWÇì«Ç›çûÇﬁ
			if (once == false)
			{
				//âEï˚å¸Ç…çUåÇÇ∑ÇÈ
				if (attack_data.direction == false)
				{
					location.x = _location.x + (_erea.width / 2) + attack_data.shift_x;
					location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

				}
				//ç∂ï˚å¸Ç…çUåÇÇ∑ÇÈ
				else
				{
					location.x = _location.x - erea.width - (_erea.width / 2) - attack_data.shift_x;
					location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

				}
				once = true;
			}
			//íeÇÃäpìxÇ…âûÇ∂ÇΩà⁄ìÆó Çê›íË
			float rad = attack_data.angle * (float)M_PI * 2;

			location.x += attack_data.speed * cosf(rad);
			location.y += attack_data.speed * sinf(rad);
			break;
		}
		//åàÇﬂÇÁÇÍÇΩéûä‘Ç™åoÇ¡ÇΩÇÁçUåÇÇè¡Ç∑
		if (--attack_data.attack_time <= 0)
		{
			attack_flg = false;
			//çUåÇïsî\
			can_apply_damage = false;
			//ÉäÉZÉbÉg
			once = false;
		}
	}
	else
	{
		//çUåÇïsî\
		can_apply_damage = false;
		if (cut_time < CUT_ANIM_TIME)
		{
			cut_time++;
		}
		else
		{
			cut_flg = false;
		}
	}
}

void Attack::Draw()const
{
#ifdef _DEBUG
	if (can_apply_damage == true)
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ff00, false);
		//çUåÇÉGÉtÉFÉNÉgÇ™Ç†ÇÈÇ»ÇÁ
		if (attack_data.effect_type >= 0 && attack_data.effect_type < 15)
		{
			//ï`âÊÇ∑ÇÈ
			DrawFormatStringF(local_location.x, local_location.y, 0x00ffff, "%d", attack_data.effect_type);
		}
	}
#endif
	if (can_apply_damage == true)
	{
		//âºï`âÊÅiå©Ç√ÇÁÇ≥ñhé~Åj
		if (attack_data.effect_type == HIMAWARI_BULLET)
		{
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffff00, true);
		}
		//çUåÇÉGÉtÉFÉNÉgÇ™Ç†ÇÈÇ»ÇÁ
		if (attack_data.effect_type == BOSSHIMAWARI_BULLET)
		{
			//ï`âÊÇ∑ÇÈ
			DrawRotaGraph(local_location.x + (erea.width/2), local_location.y + (erea.height/2), 1, attack_data.angle * M_PI * 2, bullet_img[attack_data.effect_type][0], true);
		}
		else if (attack_data.who_attack == PLAYER && attack_data.effect_type >= 0 && attack_data.effect_type <= 5)
		{
			if (attack_data.direction == false)
			{
				DrawGraph(local_location.x, local_location.y, bullet_img[attack_data.effect_type][0], true);
			}
			else
			{
				DrawTurnGraph(local_location.x , local_location.y, bullet_img[attack_data.effect_type][0], true);

			}
		}
		else if (attack_data.who_attack == PLAYER && attack_data.effect_type >= 6 && attack_data.effect_type <= 11)
		{
			if (attack_data.direction == false)
			{
				DrawGraph(local_location.x, local_location.y, bullet_img[4][0], true);
			}
			else
			{
				DrawTurnGraph(local_location.x, local_location.y, bullet_img[4][0], true);

			}
		}
	}
	if (cut_flg ==true && cut_time < CUT_ANIM_TIME)
	{
		//âºÇ≈êÿÇÁÇÍÇΩï\åª
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255-(cut_time*10));
		if(attack_data.effect_type == BOSSHIMAWARI_BULLET)
		{
			//ï`âÊÇ∑ÇÈ
			DrawRotaGraph(local_location.x + (erea.width / 2), local_location.y + (erea.height / 2), 1, attack_data.angle * M_PI * 2, bullet_img[attack_data.effect_type][1], true);
		}
		else
		{
			DrawBox(local_location.x, local_location.y - cut_time, local_location.x + erea.width, local_location.y - (erea.height / 2) - cut_time, 0xffff00, true);
			DrawBox(local_location.x, local_location.y + cut_time, local_location.x + erea.width, local_location.y + (erea.height / 2) + cut_time, 0xffff00, true);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void Attack::SpawnAttack(AttackData _attackdata)
{
	attack_flg = true;
	attack_data = _attackdata;
	erea.width = attack_data.width;
	erea.height = attack_data.height;
	once = false;
	cut_flg = false;
}

void Attack::DeleteAttack() 
{
	attack_flg = false; 
}

void Attack::SetCutFlg()
{
	cut_flg = true;
	cut_time = 0;
	DeleteAttack();
}