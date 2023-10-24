#pragma once
#include "common.h"
#include "PadInput.h"

//�Q�[�W
struct GuegeBase
{
	int x;	  //�F����l�p�̉E�����W(x)
	int y;	  //�F����l�p�̉E�����W(y)
	float h;  //�F����l�p�̍���
	float volume; //�F�̗��܂�
	float ratio;  //�Q�[�W�̗��܂�
	int maxFlg;   //CMY�̏ꍇ(0:�Q�[�WMAX���� 1:�Q�[�WMAX),���̏ꍇ(0:����ȊO 1:�Q�[�W�����̏��)
};

class PowerGauge
{
private:
	GuegeBase magenta; //�}�[���^
	GuegeBase cyan;    //�V�A��
	GuegeBase yellow;  //�C�G���[
	GuegeBase black;   //��

	int powerFlg; //(0:����ȊO�@1:������)

	int flamelate; //�t���[����

	int image[3];  //�摜�p�ϐ�

public:
	PowerGauge();  //�R���X�g���N�^
	~PowerGauge(); //�f�X�g���N�^

	void Update();
	void Draw()const;

	float VolumeCalculate(float volume, float h); //�Q�[�W�̗��܂����v�Z
	void VolumeSet();  //�Q�[�W�̗��܂����v�Z�����l����
	void BlackGauge(); //���Ԍo�߂ō��̃Q�[�W�����炷
	int PowerGaugeState(); //������Ԃ��ǂ����n��
};
