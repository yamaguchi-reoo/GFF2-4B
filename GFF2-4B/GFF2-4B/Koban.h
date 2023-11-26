#pragma once
#include "BoxCollider.h"

class Koban : public BoxCollider
{
private:
	bool spawn_flg; //�X�|�[���t���O
	bool score_flg; //�X�R�A��\�����邩���Ȃ���
	int score_time; //�X�R�A�̕\������
	float score_x,score_y; //�X�R�A��X,Y���W
	int koban_img[2]; //�摜�p�ϐ�

public:
	Koban(/*float pos_x,float pos_y*/);  //�R���X�g���N�^
	~Koban(); //�f�X�g���N�^

	void Update();     //�X�V����
	void Draw() const; //�`�揈��

	//�X�|�[���t���O���Z�b�g
	void SetSpawnFlg(bool _flg) { spawn_flg = _flg; }
	void SetReturnFlg() { spawn_flg = false; }

	//�X�R�A�t���O���Z�b�g
	void SetScoreFlg(bool _flg) { score_flg = _flg; }

	//�X�|�[���t���O��Ԃ�
	bool GetSpawnFlg() { return spawn_flg; }

	//�\���ʒu��ݒ�
	void SetLocation(Location _location);

	void SetScoreLocation();
};

