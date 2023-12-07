#include "Stage.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define DOWN 0	//�������x�p
#define UP 1	//������x�p
#define RIGHT 2	//�E�����x�p
#define LEFT 3	//�������x�p

Stage::Stage(float _x, float _y, float _width, float _height,int _type)
{
	location.x = _x;
	location.y = _y;
	erea.height = _height;
	erea.width = _width;
	type = _type;
	inv_flg = false;
	switch (type)
	{
		//�n��
	case 1:
		stage_img[0] = LoadGraph("resource/images/MapTip/MT_G_Center.png");
		stage_img[1] = LoadGraph("resource/images/MapTip/MT_G_edge.png");
		break;
		//��
	case 2:
		//LoadDivGraph("", 2, 2, 1, 48, 48, stage_img);
		break;
		//��
	case 3:	
		stage_img[0] = LoadGraph("resource/images/MapTip/MT_R_Center.png");
		stage_img[1] = LoadGraph("resource/images/MapTip/MT_R_Edge.png");
		break;
		//�_
	case 4:
		stage_img[0] = LoadGraph("resource/images/MapTip/MT_C_Center.png");
		stage_img[1] = LoadGraph("resource/images/MapTip/MT_C_Edge.png");
		break;
		//����ȊO�i�`�斳���j
	default:
		inv_flg = true;
		break;
	}
	for (int i = 0; i < 4; i++)
	{
		end_flg[i] = false;
	}
	draw_rad[UP] = 0;
	draw_rad[LEFT] = 0.75 * M_PI * 2;
	draw_rad[RIGHT] = 0.25 * M_PI * 2;
	draw_rad[DOWN] = 0.5 * M_PI * 2;
	debug_flg = false;
}

Stage::~Stage()
{

}

void Stage::Update()
{
	if (inv_flg == false){
		draw_location[UP] = { local_location.x + (erea.width / 2),local_location.y + (erea.height / 2) };
		draw_location[DOWN] = { local_location.x + (erea.width / 2),local_location.y - (erea.height / 2) + erea.height };
		draw_location[LEFT] = { local_location.x + (erea.width / 2),local_location.y + (erea.height / 2) };
		draw_location[RIGHT] = { local_location.x - (erea.width / 2) + erea.width,local_location.y + (erea.height / 2) };
	}
}

void Stage::Draw()const
{
	//Edit�ł̕\��
	if (debug_flg == true)
	{
		switch (type)
		{
			//��
		case 0:
			DrawFormatStringF(local_location.x, local_location.y, 0xffffff, "%d", type);
			break;
			//�n��
		case 1:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x4C444D, true);
			DrawFormatStringF(local_location.x, local_location.y, 0xB3BBB2, "%d", type);
			break;
			//��
		case 2:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ff00, true);
			DrawFormatStringF(local_location.x, local_location.y, 0xff00ff, "%d", type);
			break;
			//��
		case 3:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x333333, true);
			DrawFormatStringF(local_location.x, local_location.y, 0xCCCCCC, "%d", type);
			break;
			//�_
		case 4:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xdddddd, true);
			DrawFormatStringF(local_location.x, local_location.y, 0x222222, "%d", type);
			break;
			//�U�N��
		case 5:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xff00ff, true);
			DrawFormatStringF(local_location.x, local_location.y, 0x00ff00, "%d", type);
			break;
			//�C���J
		case 6:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ffff, true);
			DrawFormatStringF(local_location.x, local_location.y, 0xff0000, "%d", type);
			break;
			//�Ђ܂��
		case 7:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffff00, true);
			DrawFormatStringF(local_location.x, local_location.y, 0x0000ff, "%d", type);
			break; 
			//�|
		case 8:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x88ff88, true);
			DrawFormatStringF(local_location.x, local_location.y, 0x770077, "%d", type);
			break;
			//��
		case 13:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xBB8B38, true);
			DrawFormatStringF(local_location.x, local_location.y, 0x4474C7, "%d", type);
			break;
			//�퓬�]�[��
		case 14:
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xff0000, true);
			DrawFormatStringF(local_location.x, local_location.y, 0x00ffff, "%d", type);
			break;
			//��
		default:
			DrawFormatStringF(local_location.x, local_location.y, 0xff0000, "%d", type);
			break;
		}
	}
	//�Q�[�����C���ł̕\���i�}�b�v�`�b�v�j
	else
	{
		if (inv_flg == false)
		{
			//DrawGraph(local_location.x, local_location.y, stage_img[draw_type], true);
			switch (type)
			{
				//��
			case 0:
				break;
				//�n��
			case 1:
				//DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x4C444D, true);
				break;
				//��
			case 2:
				DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ff00, true);
				break;
				//��
			case 3:
				/*DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x333333, true);
			*/	break;
				//�_
			case 4:
				/*DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xdddddd, true);
				*/break;
				//��
			default:
				break;
			}
			DrawGraphF(local_location.x, local_location.y, stage_img[0], true);
			for (int i = 0; i < 4; i++)
			{
				if (end_flg[i] == true)
				{
#ifdef _DEBUG
					//DrawFormatStringF(local_location.x, local_location.y, 0x00ffff, "%d", i);
#endif
					DrawRotaGraphF(draw_location[i].x, draw_location[i].y,1,draw_rad[i], stage_img[1], true);
				}
			}
		}
	}
}
int Stage::GetStageCollisionType()
{
	int col_type = 0;
	if (type <= 4)
	{
		col_type = type;
	}
	else
	{
		col_type = 0;
	}
	return col_type;
}

void Stage::SetDrawType(int up_type, int left_type, int right_type, int down_type)
{
	//draw_type - 1;
	////��ƍ��̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA�E�Ɖ��̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type != up_type && up_type != -1) && (type != left_type && left_type != -1) && (type == right_type || right_type == -1) && (type == down_type || down_type == -1))
	//{
	//	draw_type = 0;
	//}
	////��̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA���E�Ɖ��̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type != up_type && up_type != -1) && (type == left_type || left_type == -1) && (type == right_type || right_type == -1) && (type == down_type || down_type == -1))
	//{
	//	draw_type = 1;
	//}
	////��ƉE�̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA���Ɖ��̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type != up_type && up_type != -1) && (type == left_type || left_type == -1) && (type != right_type && right_type != -1) && (type == down_type || down_type == -1))
	//{
	//	draw_type = 2;
	//}
	////���̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA�㉺�ƉE�̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type == up_type || up_type == -1) && (type != left_type && left_type != -1) && (type == right_type || right_type == -1) && (type == down_type || down_type == -1))
	//{
	//	draw_type = 3;
	//}
	////�㉺���E�̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type == up_type || up_type == -1) && (type == left_type || left_type == -1) && (type == right_type || right_type == -1) && (type == down_type || down_type == -1))
	//{
	//	draw_type = 4;
	//}
	////�E�̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA�㉺�ƍ��̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type == up_type || up_type == -1) && (type == left_type || left_type == -1) && (type != right_type && right_type != -1) && (type == down_type || down_type == -1))
	//{
	//	draw_type = 5;
	//}
	////���ƍ��̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA��ƉE�̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type == up_type || up_type == -1) && (type != left_type && left_type != -1) && (type == right_type || right_type == -1) && (type != down_type && down_type != -1))
	//{
	//	draw_type = 6;
	//}
	////���̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA��ƍ��E�̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type == up_type || up_type == -1) && (type == left_type || left_type == -1) && (type == right_type || right_type == -1) && (type != down_type && down_type != -1))
	//{
	//	draw_type = 7;
	//}
	////���ƉE�̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA��ƍ��̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type == up_type || up_type == -1) && (type == left_type || left_type == -1) && (type != right_type && right_type != -1) && (type != down_type && down_type != -1))
	//{
	//	draw_type = 8;
	//}
	////��ƍ��E�̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA���̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type != up_type && up_type != -1) && (type != left_type && left_type != -1) && (type != right_type && right_type != -1) && (type == down_type || down_type == -1))
	//{
	//	draw_type = 9;
	//}
	////�㉺�ƉE�̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�ŁA���̃u���b�N�̃^�C�v�������Ɠ����������͉�ʒ[�Ȃ�
	//if ((type != up_type && up_type != -1) && (type != left_type && left_type != -1) && (type != right_type && right_type != -1) && (type == down_type || down_type == -1))
	//{
	//	draw_type = 10;
	//}


	//��̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�Ȃ�
	if (type != up_type && up_type != -1)
	{
		end_flg[UP] = true;
	}
	//���̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�Ȃ�
	if (type != left_type && left_type != -1)
	{
		end_flg[LEFT] = true;
	}
	//�E�̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�Ȃ�
	if (type != right_type && right_type != -1)
	{
		end_flg[RIGHT] = true;
	}
	//���̃u���b�N�̃^�C�v�������ƈႤ����ʒ[�ȊO�Ȃ�
	if (type != down_type && down_type != -1)
	{
		end_flg[DOWN] = true;
	}

}