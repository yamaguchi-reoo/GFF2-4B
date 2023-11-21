#include "Score.h"
#include "PadInput.h"

int Score::total_score = 0;
int Score::zakuro_num = 0;
int Score::iruka_num = 0;
int Score::himawari_num = 0;

//�R���X�g���N�^
Score::Score()
{
	score_img[0] = LoadGraph("resource/images/UI/Score_UI.png");
	score_img[1] = LoadGraph("resource/images/UI/Tokuten.png");
	LoadDivGraph("resource/images/UI/ScoreNum.png", 10, 4, 3, 32, 32, num_img);
	draw_score = 0;
}

//�f�X�g���N�^
Score::~Score()
{
}

//�X�V����
void Score::Update()
{
#ifdef _DEBUG

	//�T����������X�R�A���Z
	if (KeyInput::OnKey(KEY_INPUT_5))
	{
		total_score += 135;
	}

#endif // _DEBUG

	//�X�R�A�����������₷(��ʕ\��)
	if (total_score > draw_score)
	{
		draw_score += 4;
	}
	else if (total_score < draw_score)
	{
		draw_score = total_score;
	}
}

//�`�揈��
void Score::Draw() const
{
#ifdef _DEBUG

	//DrawFormatString(160, 30, 0xffffff, "%d", font_handle);

#endif // _DEBUG

	//UI�w�i�\��
	DrawGraph(155, 10, score_img[0], TRUE);

	//�X�R�A�\��
	DrawGraph(206, 29, score_img[1], TRUE);

	if (draw_score < 10)
	{
		DrawGraph(330, 24, num_img[0], TRUE);
	}

	if (draw_score < 100)
	{
		DrawGraph(315, 24, num_img[0], TRUE);
	}

	if (draw_score < 1000)
	{
		DrawGraph(300, 24, num_img[0], TRUE);
	}
	if (draw_score < 10000)
	{
		DrawGraph(285, 24, num_img[0], TRUE);
	}
	if (draw_score < 100000)
	{
		DrawGraph(270, 24, num_img[0], TRUE);
	}
	int a = draw_score;
	int pos_x = 345;
	do
	{
		DrawGraph(pos_x, 24, num_img[a % 10], TRUE);
		a /= 10;
		pos_x -= 15;
	} while (a > 0);

}

//�g�[�^���X�R�A�ɉ��Z(����:���Z����X�R�A�̐��l)
void Score::AddScore(int score)
{
	total_score += score;
}

//�X�R�A��0�Ƀ��Z�b�g
void Score::ResetScore()
{
	total_score = 0;
	zakuro_num = 0;
	iruka_num = 0;
	himawari_num = 0;
}

//�v���C���[���a�����G�̐����J�E���g(0:�U�N�� 1:�C���J 2:�q�}����)
void Score::SetAttackEnemyNum(int num)
{
	switch (num)
	{
	case 0:
		zakuro_num++;
		break;

	case 1:
		iruka_num++;
		break;

	case 2:
		himawari_num++;
		break;

	default:
		break;
	}
}

//�v���C���[���a�����G�̐���Ԃ�(0:�U�N�� 1:�C���J 2:�q�}����)
int Score::GetAttackEnemyNum(int num)
{
	switch (num)
	{
	case 0:
		return zakuro_num;
		break;

	case 1:
		return iruka_num;
		break;

	case 2:
		return himawari_num;
		break;

	default:
		return -1;
		break;
	}
}

