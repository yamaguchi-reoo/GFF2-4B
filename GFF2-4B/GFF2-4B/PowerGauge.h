#pragma once
#include "common.h"
#include "PadInput.h"

//3�F�Q�[�W
struct ColerBase
{
	int x;	  //�F����l�p�̉E�����W(x)
	int y;	  //�F����l�p�̉E�����W(y)
	float h;  //�F����l�p�̍���
	float volume; //�F�̗��܂�
	float ratio;  //�Q�[�W�̗��܂�
	int maxFlg;   //(0:�Q�[�WMAX���� 1:�Q�[�WMAX)
};

class PowerGauge
{
private:
	ColerBase magenta; //�}�[���^
	ColerBase cyan;    //�V�A��
	ColerBase yellow;  //�C�G���[

	int image[3];  //�摜�p�ϐ�

public: 
	PowerGauge();  //�R���X�g���N�^
	~PowerGauge(); //�f�X�g���N�^

	void Update();
	void Draw()const;

	float VolumeCalculate(float volume, float h); //�Q�[�W�̗��܂����v�Z
};
