#include "Scroll.h"

SceneScroll::SceneScroll()
{
	stage_image = LoadGraph("resouce/images/SampleStage2.png");
	try 
	{
		if (stage_image == -1)
		{
			throw"resouce/images/SampleStage2.png";
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
void SceneScroll::Update(Location player)
{
	//���X�N���[��
	if (player.x >= LEFT_END)
	{
		//���[��������
		player.x = LEFT_END - 1;
	}
	//�E�X�N���[��
	if (player.x <= RIGHT_END)
	{
		//�E�[��������
		player.x = RIGHT_END + 1;
	}
}