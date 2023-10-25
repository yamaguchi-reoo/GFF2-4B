#include "Scroll.h"

SceneScroll::SceneScroll() : state(ScrollState::INIT_POS_SCROLL)
{
	try
	{
		stage_image = LoadGraph("resource/images/SampleStage2.png");
		if (stage_image == -1)
		{
			throw "resource/images/SampleStage2.png";
		}
	}
	catch (int& err)
	{
		printf("�G���[�R�[�h%d\n", err);
	}

	scroll_x = 0.0f;		//�w�i�摜�̍��㒸�_����X���W
	scroll_y = 0.0f;		//�w�i�摜�̍��㒸�_����Y���W
}
SceneScroll::~SceneScroll()
{
}
void SceneScroll::Update(Location player, float acs_l, float acs_r)
{
	//���X�N���[��
	if ((player.x <= LEFT_END) && (state == ScrollState::MOVE_SCROLL))
	{
		scroll_x += 6.0f;
		ActionRangeBorder(player);
	}
	//�E�X�N���[��
	if (player.x >= RIGHT_END)
	{
		scroll_x -= 6.0f;
		ActionRangeBorder(player);
	}
	//�X�N���[����Ԃ̐؂�ւ�(�X�N���[����Ԃ�ON�ɂ���)
	if (player.x >= LEFT_END)
	{
		state = ScrollState::MOVE_SCROLL;
	}
	//�X�N���[����Ԃ̐؂�ւ�(�X�N���[����Ԃ�OFF�ɂ���)
	/*if (scroll_x <= )
	{
		state = ScrollState::INIT_POS_SCROLL;
	}*/
}
void SceneScroll::Draw()
{
	DrawGraphF(scroll_x, 0.0f, stage_image, FALSE);
	DrawFormatString(800, 400, 0x00ff00, "%d", scroll_x);
}
ScrollData SceneScroll::PlayerScroll(Location player)
{
	ScrollData scroll_data{};
	//�������X�N���[��
	if ((player.x <= SCREEN_LEFT_END + 1) && (state == ScrollState::INIT_POS_SCROLL))
	{
		scroll_data.direction = true;
		scroll_data.move += 0.01f;
	}
	if ((player.x <= LEFT_END + 1) && (state == ScrollState::MOVE_SCROLL))
	{
		//�X�N���[����������X���W�̍��[�Ƀv���C���[�����������ꍇ�A���W�������x�����ɂ���
		scroll_data.direction = true;
		scroll_data.move += 0.01f;
	}
	if (player.x >= RIGHT_END + 1)
	{
		//�X�N���[����������X���W�̉E�[�Ƀv���C���[�����������ꍇ�A���W�������x�����ɂ���
		scroll_data.direction = false;
		scroll_data.move += 0.01f;
	}
	return scroll_data;
}
int SceneScroll::ActionRangeBorder(Location player)
{
	if ((player.x <= LEFT_END && state == ScrollState::MOVE_SCROLL) || ((player.x >= RIGHT_END))
		|| (player.x <= SCREEN_LEFT_END + 1) && (state == ScrollState::INIT_POS_SCROLL))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void SceneScroll::ChangeScrollMode()
{

}