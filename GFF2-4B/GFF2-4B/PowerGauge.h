#pragma once
#include "CharaBase.h"

#define PI    3.1415926535897932384626433832795f

//�Q�[�W
struct GuegeBase
{
	float x;	  //�F����l�p�̉E�����W(x)
	float y;	  //�F����l�p�̉E�����W(y)
	float h;  //�F����l�p�̍���
	float volume; //�F�̗��܂�
	float ratio;  //�Q�[�W�̗��܂�
	int maxFlg;   //CMY�̏ꍇ(0:�Q�[�WMAX���� 1:�Q�[�WMAX),���̏ꍇ(0:����ȊO 1:�Q�[�W�����̏��
};

class PowerGauge :public CharaBase
{
private:
	GuegeBase magenta; //�}�[���^
	GuegeBase cyan;    //�V�A��
	GuegeBase yellow;  //�C�G���[
	GuegeBase black;   //��

	int powerFlg; //(0:����ȊO 1:������ 2:��������)

	int image[3];  //�摜�p�ϐ�

	int MaskHandle[2]; //�}�X�N�摜�p�ϐ�

	float num; //�摜��]�p
	int i,j; //�摜��]�p

	int rotaFlg; //�摜��]�A�j���[�V�����p�t���O(0:����ȊO 1:�A�j���[�V������)

	int remainder; //��ꂽ��

public:
	PowerGauge();  //�R���X�g���N�^
	~PowerGauge(); //�f�X�g���N�^

	void Update(GameMain* main); //�X�V����
	void Draw()const; //�`�揈��

	float CalculateVolume(float volume, float h); //�Q�[�W�̗��܂����v�Z
	void VolumeSet();  //�Q�[�W�̗��܂����v�Z�����l����
	void BlackGauge(); //���Ԍo�߂ō��̃Q�[�W�����炷
	int PowerGaugeState(); //������Ԃ��ǂ����n��
	void SetPowerFlg(int i); //������Ԃ��ǂ�����ۑ�����ϐ��̒l�������̒l�ɕύX
	void SetVolume(ColorDate color); //�G�����Ƃ����F�A�ʂ��Q�[�W�ɉ��Z
	void CheckVolumeMax(); //CMYK�̃Q�[�W��MAX���`�F�b�N����
	void RotaGauge(); //�����Q�[�W�̉�]����
	void InitGauge(); //������Ԃ��I�������̏���������
	int GetColorRem() { return remainder; } //��ꂽ����Ԃ�
	void SetColorRem(); //�����Q�[�W�����ꂽ����0�Ƀ��Z�b�g
};
