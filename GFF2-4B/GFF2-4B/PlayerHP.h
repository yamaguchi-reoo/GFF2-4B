#pragma once

class PlayerHP
{
private:
	int hpImage[6];  //�摜�p�ϐ�
	int player_hp; //�v���C���[��HP
	int draw_hp; //HP�_�ŗp�ϐ�
	int flash_flg; //HP�_�ŗp�ϐ�
	int flash_hp; //�_�ł�����HP

public:
	//�R���X�g���N�^
	PlayerHP();  

	//�f�X�g���N�^
	~PlayerHP();

	//�X�V����
	void Update(int hp);

	//�`�揈��
	void Draw()const;

	//HP�_��
	void FlashHP(void);

	//HP����
	void AnimHP(void);
};

