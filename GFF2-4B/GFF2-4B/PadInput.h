#pragma once
#include"DxLib.h"

#define KEY_MAX 256
#define MOUSE_MAX 256

#define BUTTONS 16
#define STICKL_X 1		
#define STICKL_Y 2		
#define MAXL_X 32767.f  //���X�e�B�b�NX���̍ő�l(float�^)
#define MAXL_Y 32767.f  //���X�e�B�b�NY���̍ő�l(float�^)

//�X�e�B�b�N
struct Stick
{
	short ThumbX;	//�����l
	short ThumbY;	//�c���l
};

//�}�E�X�J�[�\��
struct CURSOR
{
	int x;	//�����l
	int y;	//�c���l
};

class PadInput
{
private:
	static char NowKey[BUTTONS]; //����̓��̓L�[
	static char OldKey[BUTTONS]; //�O��̓��̓L�[
	static XINPUT_STATE Input; //�p�b�h
	static Stick Rstick; //�E�X�e�B�b�N
	static Stick Lstick; //���X�e�B�b�N
	
public:
	//�p�b�h���̍X�V
	static void UpdateKey()
	{
		// ���̓L�[�擾
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input);
		for (int i = 0; i < BUTTONS; i++)
		{
			OldKey[i] = NowKey[i];
			NowKey[i] = Input.Buttons[i];
		}

		//���X�e�B�b�N
		Lstick.ThumbX = Input.ThumbLX;
		Lstick.ThumbY = Input.ThumbLY;
	}

	//�{�^���������ꂽ�u��
	static bool OnButton(int button)
	{
		bool ret = (NowKey[button] == 1 && OldKey[button] == 0);
		return ret;
	}

	//�{�^���������Ă��
	static bool OnPressed(int button)
	{
		bool ret = (NowKey[button] == 1);
		return ret;
	}

	//�{�^���𗣂����u��
	static bool OnRelease(int button)
	{
		bool ret = (NowKey[button] == 0 && OldKey[button] == 1);
		return ret;
	}

	//�X�e�B�b�N�̌X������
	static float TipLeftLStick(short StickL)
	{
		if (StickL == STICKL_X)
		{
			float ratioL_X = Input.ThumbLX / MAXL_X;

			//���X�e�B�b�N�̉������ő�l���P�Ƃ�������
			return ratioL_X;
		}
		else if (StickL == STICKL_Y)
		{
			float ratioL_Y = Input.ThumbLY / MAXL_Y;

			//���X�e�B�b�N�̏c���l�̍ő�l���P�Ƃ�������
			return ratioL_Y;
		}

		return 0;
	}

};
//�L�[����
class KeyInput
{
private:
	static int NowKey[KEY_MAX];		//����̓��̓L�[
	static int OldKey[KEY_MAX];		//�O��̓��̓L�[
	static int NowMouse[MOUSE_MAX]; //����̓��̓}�E�X�{�^��
	static int OldMouse[MOUSE_MAX]; //�O��̓��̓}�E�X�{�^��
	static CURSOR Cursor; //�J�[�\��
public:
	//�p�b�h���̍X�V
	static void UpdateKey() {
		// ���̓L�[�擾
		for (int i = 0; i < KEY_MAX; i++) {
			OldKey[i] = NowKey[i];
			NowKey[i] = CheckHitKey(i);
		}
		for (int i = 0; i < MOUSE_MAX; i++)
		{
			OldMouse[i] = NowMouse[i];
			if (GetMouseInput() == i)
			{
				NowMouse[i] = 1;
			}
			else
			{
				NowMouse[i] = 0;
			}
		}
		GetMousePoint(&Cursor.x, &Cursor.y);
	}
	//�{�^�����������u��
	static bool OnKey(int key) {
		return (NowKey[key] == 1 && OldKey[key] == 0);
	}

	//�{�^�����������u��
	static bool OnPresed(int key) {
		return (NowKey[key] == 1);

	}
	//�{�^�����������u��
	static bool OnRelease(int key) {
		return (NowKey[key] == 0 && OldKey[key] == 1);
	}
	//�}�E�X�{�^���������ꂽ�u��
	static bool OnMouse(int mouse)
	{
		return (NowMouse[mouse] == 1 && OldMouse[mouse] == 0);
	}

	//�}�E�X�{�^���������Ă��
	static bool OnPressedMouse(int mouse)
	{
		return (NowMouse[mouse] == 1);
	}

	//�}�E�X�{�^���𗣂����u��
	static bool OnReleaseMouse(int mouse)
	{
		return (NowMouse[mouse] == 0 && OldMouse[mouse] == 1);
	}
	//�}�E�X�J�[�\���̈ʒu��Ԃ�
	static CURSOR GetMouseCursor()
	{
		return  Cursor;
	}
};
