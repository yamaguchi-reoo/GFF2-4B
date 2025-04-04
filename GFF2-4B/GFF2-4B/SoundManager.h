#pragma once
#include"DxLib.h"

#define SOUND_NUM 100
//効果音の数
#define BGM_NUM 1		//BGMの数

//プレイヤー
#define PLAYER_ATTACK_SOUND  0    //プレイヤーの足音
#define PLAYER_WALK_SOUND  1    //プレイヤーの足音
#define PLAYER_JUMP_SOUND  2    //プレイヤーのジャンプ音
#define PLAYER_HP_SOUND  3    //プレイヤーのHP


//エネミー
#define ENEMY_EXPLOSION_SOUND  4    //エネミーの爆発音
#define HIMAWARI_SHOT_SOUND  5    //エネミーの爆発音


//システム
#define SYSTEM_SELECT_SOUND  6   //決定音
#define SYSTEM_KOZENI_SOUND  7   //小銭(リザルト)

//アイテム
#define ITEM_KOZENI_SOUND  8   //小銭(アイテム)
#define ITEM_TUBO_SOUND  9   //壺割れる音

#define ITEM_THAKUTI_SOUND  10   //着地


#define BGM1  10   //着地




//使用する音源のパス一覧（上のファイルほど再生優先度が高い）
static char sound_filepath[SOUND_NUM][256] =
{

	"resource/sounds/通常攻撃.mp3",
	"resource/sounds/足音.mp3",
	"resource/sounds/ジャンプ.mp3",
	"resource/sounds/紙破る.mp3",
	"resource/sounds/爆発音.mp3",
	"resource/sounds/ショット.mp3",
	"resource/sounds/決定音(太鼓).mp3",
	"resource/sounds/小銭1.mp3"
	"resource/sounds/小銭2.mp3",
	"resource/sounds/壺.mp3",
	"resource/sounds/着地.mp3",

		"resource/sounds/Battle-Ayakashi.mp3",

};
//使用する音源のパス一覧(優先度は無く、後から再生されたBGMが優先される)
static char bgm_filepath[SOUND_NUM][256] =
{
		"resource/sounds/Battle-Ayakashi.mp3",

};
struct Sound {
	int dat;		//サウンド格納用変数
	int num;		//優先順位
	bool play_flg;	//再生中かどうか
};
struct BGM {
	int dat;		//サウンド格納用変数
	int num;
	bool play_flg;	//再生中かどうか
};
class SoundManager
{
private:
	static Sound sound_data[SOUND_NUM];
	static int now_play_sound;	//何番目の音が再生中か

	static BGM bgm_data[BGM_NUM];
	static int now_bgm;
public :
	static void LoadSound()
	{
		now_play_sound = SOUND_NUM;
		for (int i = 0; i < SOUND_NUM; i++)
		{
			sound_data[i].dat = LoadSoundMem(sound_filepath[i]);
			sound_data[i].num = i;
			sound_data[i].play_flg = false;
		}
	}
	static void LoadBgm()
	{
		now_bgm = BGM_NUM;
		for (int i = 0; i < BGM_NUM; i++)
		{
			bgm_data[i].dat = LoadSoundMem(bgm_filepath[i]);
			bgm_data[i].play_flg = false;
		}
	}
	static void DeleteSound()
	{
		for (int i = 0; i < SOUND_NUM; i++)
		{
			DeleteSoundMem(sound_data[i].dat);
		}
	}
	static void UpdateSound() {
		for (int i = 0; i < BGM_NUM; i++)
		{
			if (i == now_bgm)
			{
				//そのBGMを再生

			}
			else
			{
				//そのBGMを停止

			}
		}

		
	}
	static void StartSound(int _num)
	{
		if (CheckSoundMem(sound_data[_num].dat) == false) {

			PlaySoundMem(sound_data[_num].dat, DX_PLAYTYPE_BACK);
			
		}
		
	}
	static void StartSound2(int _num)
	{

			PlaySoundMem(sound_data[_num].dat, DX_PLAYTYPE_BACK);

	

	}
	static void StopSound(int _num)
	{
		// 指定されたサウンドを停止する
		StopSoundMem(sound_data[_num].dat);
		sound_data[_num].play_flg = false;

	}

	static void StartBGM(int _num)
	{
		if (CheckSoundMem(bgm_data[_num].dat) == false) {

			PlaySoundMem(bgm_data[_num].dat, DX_PLAYTYPE_BACK);
		}
	}
	static void StopAllBGM(int _num)
	{
		// 指定されたサウンドを停止する
		StopSoundMem(sound_data[_num].dat);
		sound_data[_num].play_flg = false;
	}
};
