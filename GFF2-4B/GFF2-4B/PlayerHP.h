#pragma once

class PlayerHP
{
private:
	int hpImage;  //�摜�p�ϐ�
	int playerHP; //�v���C���[��HP

public:
	PlayerHP();  //�R���X�g���N�^
	~PlayerHP(); //�f�X�g���N�^

	void Update(int hp); //�X�V����
	void Draw()const; //�`�揈��
};

