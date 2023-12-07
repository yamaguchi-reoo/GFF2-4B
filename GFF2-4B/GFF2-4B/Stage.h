#pragma once
#include "BoxCollider.h"
#include "Scroll.h"
class Stage:
	public BoxCollider
{
private:
	int type;		//���̎��(0=�� 1=�n�� 2=�� 3=�� 4=�_)
	bool inv_flg;		//�����`�悵�Ȃ������f
	int stage_img[2];	//�摜�i�[�p
	bool end_flg[4];	//�[���ǂ������f
	Location draw_location[4];	//�e�[�̕`��ʒu
	float draw_rad[4];	//�e�[�̕`��p�x
	float draw_angle;			//�e�[�̕`��p�x
	bool debug_flg;		//���̎�ނ�\�����邩
public:
	Stage(float _x, float _y, float _width, float _height,int _type);
	~Stage();
	void Update();
	void Draw()const;

	//��ނ��擾(0=�� 1=�n�� 2=�� 3=�� 4=�_  �e�I�u�W�F�N�g���X�|�[������ʒu�͂��ׂ�0(����Ȃ�)�ƕԂ�)
	int GetStageCollisionType();
	//��ނ�ݒ�
	void SetStageType(int _type) { type = _type; }
	//��ނ��擾
	int GetStageType() { return type; }
	//���̎�ނ�\������
	void SetDebugFlg() { debug_flg = true; }
	//�`�悷��摜�̎�ނ𔻒f����
	void SetDrawType(int up_type, int left_type, int right_type, int down_type);
};
