#pragma once
#include "CharaBase.h"

#define PI    3.1415926535897932384626433832795f  //��

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

	int power_flg; //(0:����ȊO 1:������ 2:��������)

	int image[3];  //�摜�p�ϐ�

	int mask_handle[2]; //�}�X�N�摜�p�ϐ�

	float num; //�摜��]�p
	int i,j; //�摜��]�p

	int rota_flg; //�摜��]�A�j���[�V�����p�t���O(0:����ȊO 1:�A�j���[�V������)

	int remainder; //��ꂽ��

public:
	//�R���X�g���N�^
	PowerGauge();

	//�f�X�g���N�^
	~PowerGauge();

	//�X�V����
	void Update(GameMain* main);

	//�`�揈��
	void Draw()const;

	//�Q�[�W�̗��܂����v�Z
	float CalculateVolume(float volume, float h);

	//�Q�[�W�̗��܂����v�Z�����l����
	void VolumeSet(); 

	//���Ԍo�߂ō��̃Q�[�W�����炷
	void BlackGauge(); 

	//������Ԃ��ǂ����n��
	int PowerGaugeState(); 

	//������Ԃ��ǂ�����ۑ�����ϐ��̒l�������̒l�ɕύX
	void SetPowerFlg(int i);

	//�G�����Ƃ����F�A�ʂ��Q�[�W�ɉ��Z
	void SetVolume(ColorDate color); 

	//CMYK�̃Q�[�W��MAX���`�F�b�N����
	void CheckVolumeMax(); 

	//�����Q�[�W�̉�]����
	void RotaGauge(); 

	//������Ԃ��I�������̏���������
	void InitGauge(); 

	//�����Q�[�W�����ꂽ����Ԃ�
	int GetColorRem() { return remainder; } 

	//�����Q�[�W�����ꂽ����0�Ƀ��Z�b�g
	void ResetColorRem(); 

	// �}�[���^�Q�[�W�̗ʂ��擾
	float GetMagentaVolume() const {
		return magenta.volume;
	}

	// �C�G���[�Q�[�W�̗ʂ��擾
	float GetYellowVolume() const {
		return yellow.volume;
	}

	// �V�A���Q�[�W�̗ʂ��擾
	float GetCyanVolume() const {
		return cyan.volume;
	}
};
