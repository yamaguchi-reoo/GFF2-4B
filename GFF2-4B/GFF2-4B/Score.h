#pragma once

class Score
{
private:
	int font_handle; //�t�H���g�f�[�^�p�ϐ�
	int score_img[2];	 //�摜�p�ϐ�
	int total_score; //�g�[�^���X�R�A
	int draw_score;  //�`��p�̃X�R�A

public:
	//�R���X�g���N�^
	Score();

	//�f�X�g���N�^
	~Score();

	//�X�V����
	void Update(); 

	//�`�揈��
	void Draw()const; 

	//�g�[�^���X�R�A�ɉ��Z(����:���Z����X�R�A�̐��l)
	void AddScore(int score); 

	//�X�R�A�̒l��Ԃ�
	int GetScore() { return total_score; }
};