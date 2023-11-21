#pragma once

class Score
{
private:
	int score_img[2];//�摜�p�ϐ�
	int num_img[10]; //�����摜�p�ϐ�
	static int total_score; //�g�[�^���X�R�A
	int draw_score;  //�`��p�̃X�R�A
	static int zakuro_num; //�a�����U�N���̐�
	static int iruka_num;  //�a�����C���J�̐�
	static int himawari_num; //�a�����q�}�����̐�

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
	static void ResetScore();

	//�v���C���[���a�����G�̐����J�E���g(0:�U�N�� 1:�C���J 2:�q�}����)
	static void SetAttackEnemyNum(int num);

	//�v���C���[���a�����G�̐���Ԃ�(0:�U�N�� 1:�C���J 2:�q�}����)
	static int GetAttackEnemyNum(int num);
};