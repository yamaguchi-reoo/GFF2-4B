#pragma once
#include"DxLib.h"

#define SOUND_NUM 1		//�����̐�

#define PLAYER_WALK  0    //�v���C���[�̑���

//�g�p���鉹���̃p�X�ꗗ�i��̃t�@�C���قǍĐ��D��x�������j
static char sound_filepath[SOUND_NUM][256] =
{
	"resource/sounds/�Ō�4.mp3",
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
			//�Đ�����Ȃ�
			if (sound_data[i].play_flg == true)
			{
				//���̉����Đ����łȂ��Ȃ�
				if (CheckSoundMem(sound_data[i].dat) == false)
				{
					//�Đ�����
					PlaySoundMem(sound_data[i].dat, DX_PLAYTYPE_BACK);
				}
				sound_data[i].play_flg = false;
			}
		}
		//�D��x�����������Đ����ꂽ�Ȃ瑼�̉��̉��ʂ͉�����

	}
	static void StartSound(int _num)
	{
		sound_data[_num].play_flg = true;
	}
};
