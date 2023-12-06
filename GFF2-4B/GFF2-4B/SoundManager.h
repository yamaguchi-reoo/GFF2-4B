#pragma once
#include"DxLib.h"

#define SOUND_NUM 3	//効果音の数
#define BGM_NUM 1		//BGMの数

#define PLAYER_ATTACK_SOUND  0    //プレイヤーの足音
#define PLAYER_WALK_SOUND  1    //プレイヤーの足音

//使用する音源のパス一覧（上のファイルほど再生優先度が高い）
static char sound_filepath[SOUND_NUM][256] =
{
	"resource/sounds/通常攻撃.mp3",
	"resource/sounds/打撃4.mp3",
	"resource/sounds/体育館で歩く.mp3",
	

};
//使用する音源のパス一覧(優先度は無く、後から再生されたBGMが優先される)
static char bgm_filepath[SOUND_NUM][256] =
{
	"",
};
struct Sound {
	int dat;		//サウンド格納用変数
	int num;		//優先順位
	bool play_flg;	//再生中かどうか
};
struct BGM {
	int dat;		//サウンド格納用変数
	bool play_flg;	//再生中かどうか
};
class SoundManager
{
private:
	static Sound sound_data[SOUND_NUM];
	static int now_play_sound;	//何番目の音が再生中か

	static BGM bgm_data[SOUND_NUM];
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
		for (int i = 0; i < SOUND_NUM; i++)
		{
			//再生するなら
			if (sound_data[i].play_flg == true)
			{
				if (CheckSoundMem(sound_data[i].dat) == false) {
					StopSound(i); // 再生が終了したら停止
				}
				//その音が再生中でない且つ、今再生されている音より再生優先度が高いかなら
				if (CheckSoundMem(sound_data[i].dat) == false && now_play_sound >= sound_data[i].num)
				{
					//優先度が高い音を再生する
					PlaySoundMem(sound_data[i].dat, DX_PLAYTYPE_BACK);
					//優先度が低い音は停止する
					if (now_play_sound != sound_data[i].num)
					{
						StopSoundMem(sound_data[now_play_sound].dat);
						sound_data[now_play_sound].play_flg = false;
						now_play_sound = sound_data[i].num;
					}
				}

			}
		}
		
	}
	static void StartSound(int _num)
	{
		sound_data[_num].play_flg = true;
	}
	static void StopSound(int _num)
	{
		// 指定されたサウンドを停止する
		StopSoundMem(sound_data[_num].dat);
		sound_data[_num].play_flg = false;

	}

	static void StartBGM(int _num)
	{
		now_bgm = _num;
	}
	static void StopAllBGM(int _num)
	{
		now_bgm = -1;
	}
};
