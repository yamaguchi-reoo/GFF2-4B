#pragma once
#include"DxLib.h"
#define SOUND_NUM 1		//�����̐�

//�g�p���鉹���̃p�X�ꗗ�i��̃t�@�C���قǍĐ��D��x�������j
static char sound_filepath[SOUND_NUM][256] =
{
	"",
};

struct Sound {
	int dat;		//�T�E���h�i�[�p�ϐ�
	int num;		//�D�揇��
	bool play_flg;	//�Đ������ǂ���
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
			if (sound_data[i].play_flg == true)
			{
				//���ŉ����d�Ȃ��Ă����̂܂܍Đ�����
			}
		}
	}
	static void StartSound(int _num)
	{
		PlaySoundMem(sound_data[_num].dat, DX_PLAYTYPE_BACK);
		sound_data[_num].play_flg = true;
	}
};
