#pragma once
#include"DxLib.h"

#define SOUND_NUM 1		//音源の数

#define PLAYER_WALK  0    //プレイヤーの足音

//使用する音源のパス一覧（上のファイルほど再生優先度が高い）
static char sound_filepath[SOUND_NUM][256] =
{
	"resource/sounds/打撃4.mp3",
};

struct Sound {
	int dat;		//サウンド格納用変数
	int num;		//優先順位
	bool play_flg;	//再生中かどうか
};

class SoundManager
{
private:
	static Sound sound_data[SOUND_NUM];
public :
	static void LoadSound()
	{
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
		for (int i = 0; i < SOUND_NUM; i++)
		{
			//再生するなら
			if (sound_data[i].play_flg == true)
			{
				//その音が再生中でないなら
				if (CheckSoundMem(sound_data[i].dat) == false)
				{
					//再生する
					PlaySoundMem(sound_data[i].dat, DX_PLAYTYPE_BACK);
				}
				sound_data[i].play_flg = false;
			}
		}
		//優先度が高い音が再生されたなら他の音の音量は下げる

	}
	static void StartSound(int _num)
	{
		sound_data[_num].play_flg = true;
	}
};
