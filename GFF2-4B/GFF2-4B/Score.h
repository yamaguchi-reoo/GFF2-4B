#pragma once

class Score
{
private:
	int score_img[2];//�摜�p�ϐ�
	int num_img[10]; //�����摜�p�ϐ�
	static int total_score; //�g�[�^���X�R�A
	int draw_score;  //�`��p�̃X�R�A
	int temp_score[6];
	int i;

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
	static int GetScore() { return total_score; }

	//�X�R�A��0�ɏ�����
	static void SetScore();

	//�X�R�A���摜�ɕύX���邽�߂̏���
	void ChangeScore();
};