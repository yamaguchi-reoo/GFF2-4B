  #pragma once
#include "common.h"
#include "PadInput.h"

//3�F�Q�[�W
struct ColerBase
{
	float x;	  //�F����l�p�̍�����W(x)
	float y;	  //�F����l�p�̍�����W(y)
	float volume; //�Q�[�W�̗��܂�
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
};
