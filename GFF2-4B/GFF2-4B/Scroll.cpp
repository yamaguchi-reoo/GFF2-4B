#include "Scroll.h"

SceneScroll::SceneScroll()
{
	stage_image = LoadGraph("resource/images/SampleStage2.png");
	try 
	{
		if (stage_image == -1)
		{
			throw"resource/images/SampleStage2.png";
		}
	}
	catch (int& err)
	{
		printf("�G���[�R�[�h%d\n", err);
	}

	scroll_x = 0.0;		//�w�i�摜�̍��㒸�_����X���W
	scroll_y = 0.0;		//�w�i�摜�̍��㒸�_����Y���W
}
SceneScroll::~SceneScroll()
{
}
void SceneScroll::Update(Location player, float acs_l, float acs_r)
{
	//���X�N���[��
	if (player.x >= LEFT_END)
	{
		scroll_x -= acs_l;

		//���[��������
		player.x = LEFT_END - 1;
	}
	//�E�X�N���[��
	if (player.x <= RIGHT_END)
	{
		scroll_x += acs_r;

		//�E�[��������
		player.x = RIGHT_END + 1;
	}
}
void SceneScroll::Draw()
{
	DrawGraph(0, 0, stage_image, FALSE);
}