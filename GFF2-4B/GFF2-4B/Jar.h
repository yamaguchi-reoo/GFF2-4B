#pragma once
#include "CharaBase.h"
class Jar:
	public BoxCollider
{
private:
	ColorDate Date{ 0 };
	bool spawn_flg;
	int jar_image;

	bool onfloor_flg;	//�����ꂩ�̒n�ʂɐG��Ă��邩�ǂ���
	bool apply_gravity;		//�d�͂�K�p���邩�ǂ���

	int hp;

public:

	Jar(float pos_x, float pos_y);
	~Jar();

	void Update();
	void Draw()const;

	void JarReset();// �����蔻��̃��Z�b�g
	//�d�͂�����
	void JarGiveGravity();
	//�����o��(num = �������Ă��鏰 _sub = �������Ă��鏰�̍�����W)
	void Push(int num, Location _sub_location, Erea _sub_erea);

	//�_���[�W���󂯂鏈��
	bool ApplyDamage(int num);
	//�X�|�[���t���O�擾
	int GetSpwnFlg() { return spawn_flg; }

	int GetHp() { return hp; }

	//�F�̎擾
	ColorDate GetColorDate() { return Date; }
};

