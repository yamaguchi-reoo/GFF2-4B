#pragma once
#include"DxLib.h"

#define SOUND_NUM 100
//���ʉ��̐�
#define BGM_NUM 1		//BGM�̐�

#define PLAYER_ATTACK_SOUND  0    //�v���C���[�̑���
#define PLAYER_WALK_SOUND  1    //�v���C���[�̑���
#define PLAYER_JUMP_SOUND  2    //�v���C���[�̃W�����v��


//�g�p���鉹���̃p�X�ꗗ�i��̃t�@�C���قǍĐ��D��x�������j
static char sound_filepath[SOUND_NUM][256] =
{
	"resource/sounds/�ʏ�U��.mp3",
	"resource/sounds/����.mp3",
	"resource/sounds/�W�����v.mp3",
	"resource/sounds/�Ō�4.mp3",
	"resource/sounds/�̈�قŕ���.mp3",
	

};
//�g�p���鉹���̃p�X�ꗗ(�D��x�͖����A�ォ��Đ����ꂽBGM���D�悳���)
static char bgm_filepath[SOUND_NUM][256] =
{
	"",
};
struct Sound {
	int dat;		//�T�E���h�i�[�p�ϐ�
	int num;		//�D�揇��
	bool play_flg;	//�Đ������ǂ���
};
struct BGM {
	int dat;		//�T�E���h�i�[�p�ϐ�
	bool play_flg;	//�Đ������ǂ���
};
class SoundManager
{
private:
	static Sound sound_data[SOUND_NUM];
	static int now_play_sound;	//���Ԗڂ̉����Đ�����

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
				//����BGM���Đ�

			}
			else
			{
				//����BGM���~

			}
		}

		
	}
	static void StartSound(int _num)
	{
		if (CheckSoundMem(sound_data[_num].dat) == false) {

			PlaySoundMem(sound_data[_num].dat, DX_PLAYTYPE_BACK);
		}
		
	}
	static void StopSound(int _num)
	{
		// �w�肳�ꂽ�T�E���h���~����
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
