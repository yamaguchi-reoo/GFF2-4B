#include"DxLib.h"

#define FRAMERATE 60.0 //�t���[�����[�g

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("GFF2-4B");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	SetGraphMode(1920, 1280, 32);	//��ʃT�C�Y�̐ݒ�

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	// �Q�[�����[�v
	while ((ProcessMessage() == 0)) {
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
	}
	return 0;
}