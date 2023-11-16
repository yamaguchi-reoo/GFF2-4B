#include "PowerGauge.h"
#include "PadInput.h"
#include "GameMain.h"

//�R���X�g���N�^
PowerGauge::PowerGauge()
{
	location.x = 5;
	location.y = 3;
	erea.height = 140;
	erea.width = 150;

	magenta.x = 112.0f;
	magenta.y = 70.0f;
	magenta.h = 65.0f;
	magenta.volume = 0.0f;
	magenta.ratio = 0.0f;
	magenta.maxFlg = 0;

	cyan.x = 152.0f;
	cyan.y = 130.0f;
	cyan.h = 115.0f;
	cyan.volume = 0.0f;
	cyan.ratio = 0.0f;
	cyan.maxFlg = 0;

	yellow.x = 103.0f;
	yellow.y = 150.0f;
	yellow.h = 84.0f;
	yellow.volume = 0.0f;
	yellow.ratio = 0.0f;
	yellow.maxFlg = 0;

	black.x = 147.0f;
	black.y = 138.0f;
	black.h = 131.0f;
	black.volume = 0.0f;
	black.ratio = 0.0f;
	black.maxFlg = 0;

	power_flg = 0;

	image[0] = LoadGraph("resource/images/koban.png");
	image[1] = LoadGraph("resource/images/black.png");
	image[2] = LoadGraph("resource/images/magatama_max.png");

	mask_handle[0] = LoadMask("resource/images/Magatama_mask1.png");
	mask_handle[1] = LoadMask("resource/images/black_mask.png");

	num = 0.0f;
	rota_flg = 0;
	i = 0;
	j = 0;

	remainder = 0;
}

//�f�X�g���N�^
PowerGauge::~PowerGauge()
{
	// �}�X�N�f�[�^���폜
	DeleteMask(mask_handle[0]);
	DeleteMask(mask_handle[1]);
}

//�X�V����
void PowerGauge::Update(GameMain* main)
{
	if ((black.maxFlg == 0) && (rota_flg == 0))
	{
		//�f�o�b�N�p(LB���������狭���Q�[�W�����܂�)
		if ((black.maxFlg == 0) && (PadInput::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) == true))
		{
			if (magenta.maxFlg == 0)
			{
				magenta.volume += 40.0f;
			}
			if (cyan.maxFlg == 0)
			{
				cyan.volume += 40.0f;
			}
			if (yellow.maxFlg == 0)
			{
				yellow.volume += 40.0f;
			}
		}

		CheckVolumeMax();

		VolumeSet();

		//�f�o�b�N�p(RB���������狭���Q�[�W��MAX�ɂȂ�)
		if ((black.maxFlg == 0) && (PadInput::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER) == true))
		{
			rota_flg = 1;
		}

	}
	else if(rota_flg == 1)
	{
		RotaGauge();
	}
	else if(black.maxFlg == 1)
	{
		//�����Q�[�W��MAX���AX�{�^���������ꂽ�狭����ԃt���O��1��
		if ((black.maxFlg == 1) && (PadInput::OnButton(XINPUT_BUTTON_Y) == true))
		{
			power_flg = 1;
		}
	}

	//������ԃt���O��1�������狭���Q�[�W�����炷
	if (power_flg == 1)
	{
		BlackGauge();
		VolumeSet();
	}
}

//�`�揈��
void PowerGauge::Draw() const
{
#ifdef _DEBUG

	//�f�o�b�N�\��
	//DrawFormatString(400, 10, 0xffffff, "%d", remainder);

#endif // _DEBUG
	
	//�}�X�N��ʂ��쐬
	CreateMaskScreen();

	if ((black.maxFlg == 0) && (rota_flg == 0))
	{
		//���[�h�����}�X�N�f�[�^����ʂ̍���ɕ`��
		DrawMask(5, 3, mask_handle[0], DX_MASKTRANS_NONE);

		//���ʂ̔w�i�𔒂�
		DrawBox(5, 3, 155, 153, 0x7d7d7d, TRUE);

		//�����Q�[�W��0%�ȏ�̎��ɕ\��
		
		
		//�}�[���^
		DrawBox(80, 10, 112, 70, 0x7d7d7d, TRUE);
		DrawBoxAA(magenta.x - 107, magenta.y - magenta.ratio, magenta.x, magenta.y, 0xe4007f, TRUE);
		
		
		//�C�G���[
		DrawBox(15, 66, 70, 70, 0x7d7d7d, TRUE);
		DrawBoxAA(yellow.x - 92, yellow.y - yellow.ratio, yellow.x, yellow.y, 0xffff00, TRUE);
		
		
		//�V�A��
		DrawBox(87, 70, 112, 130, 0x7d7d7d, TRUE);
		DrawBoxAA(cyan.x - 65, cyan.y - cyan.ratio, cyan.x, cyan.y, 0x00ffff, TRUE);
	
		
		/**�}�`�`��̏d�Ȃ���B��(��������)**/
		DrawBox(87, 70, 112, 130, 0x7d7d7d, TRUE);

		if (cyan.volume >= 2.0f)
		{
			DrawBoxAA(87, 130 - ((cyan.volume * 2.0f) / 100.0f * 57.5f), 112.0f, 130.0f, 0x00ffff, TRUE);
		}

		if (magenta.volume >= 2.0f)
		{

			if (yellow.volume > 95.0f)
			{
				DrawBoxAA(15.0f, 70.0f - (yellow.volume / 100.0f * 4), 70.0f, 70.0f, 0xffff00, TRUE);
		    }
		}

		DrawBox(80, 10, 112, 70, 0x7d7d7d, TRUE);

		if (magenta.volume >= 14.0f)
		{
			DrawBoxAA(80.0f, 70.0f - ((magenta.volume * 1.1f) / 100.0f * 59.5f ), 112.0f, 70.0f, 0xe4007f, TRUE);
		}
		/**�}�`�`��̏d�Ȃ���B��(�����܂�)**/
	}
	else if ((rota_flg == 1) && (black.maxFlg == 0))
	{
		//�����Q�[�W����]�`��
		DrawRotaGraph(80, 80, 1.0f, PI / 180 * num, image[2], TRUE, FALSE);
	}
	else if ((black.maxFlg == 1) && (power_flg == 0))
	{//�����Q�[�W��MAX(��)�̂Ƃ�

		//���[�h�����}�X�N�f�[�^����ʂ̍���ɕ`��
		DrawMask(5, 3, mask_handle[1], DX_MASKTRANS_NONE);

		DrawBox(5, 3, 155, 138, 0xffffff, TRUE);
		
		DrawBoxAA(black.x - 135.0f, black.y - 131.0f, black.x, black.y, 0x000000, TRUE);
	}
	else if(power_flg == 1)
	{//�����Q�[�W��MAX��X�{�^���������ꂽ�Ƃ�

		//���[�h�����}�X�N�f�[�^����ʂ̍���ɕ`��
		DrawMask(5, 3, mask_handle[1], DX_MASKTRANS_NONE);

		DrawBox(5, 3, 150, 138, 0xffffff, TRUE);

		DrawBoxAA(black.x - 135.0f, black.y - black.ratio, black.x, black.y, 0x000000, TRUE);
	}

	// �}�X�N��ʂ��폜
	DeleteMaskScreen();
}

//�Q�[�W�̗��܂����v�Z
float PowerGauge::CalculateVolume(float volume, float h)
{
	float i = 0.0f;

	i = volume / 100.0f * h;

	return i;
}

//�Q�[�W�̗��܂����v�Z�����l����
void PowerGauge::VolumeSet()
{
	magenta.ratio = CalculateVolume(magenta.volume, magenta.h);
	yellow.ratio = CalculateVolume(yellow.volume, yellow.h);
	cyan.ratio = CalculateVolume(cyan.volume, cyan.h);
	black.ratio = CalculateVolume(black.volume, black.h);
}

//���Ԍo�߂ō��̃Q�[�W�����炷
void PowerGauge::BlackGauge()
{
	float i = 0;

	if (black.volume > 0.0f)
	{
		//������ԂŁA�Q�[�W��0%�ɂȂ�܂ŏ��X�Ɍ��炷
		i = black.volume;
		black.volume = i - 0.17f;
	}
	else
	{
		//������Ԃ��I�������A������Ԃ��������ċ����Q�[�W��������Ԃɖ߂�
		power_flg = 2;
		InitGauge();
	}
}

//������Ԃ��ǂ����n��
int PowerGauge::PowerGaugeState()
{
	if (power_flg == 1)
	{
		//�������
		return 1;
	}
	else if (power_flg == 2)
	{
		//��������
		return 2;
	}

	return 0;
}

//������Ԃ��ǂ�����ۑ�����ϐ��̒l�������̒l�ɕύX
void PowerGauge::SetPowerFlg(int i)
{
	power_flg = i;
}

//�G�����Ƃ����F�A�ʂ��Q�[�W�ɉ��Z
void PowerGauge::SetVolume(ColorDate color)
{
	//�}�[���^
	if (magenta.maxFlg == 0)
	{
		magenta.volume += color.magenta;
	}

	//�V�A��
	if (cyan.maxFlg == 0)
	{
		cyan.volume += color.syan;
	}
	
	//�C�G���[
	if (yellow.maxFlg == 0)
	{
		yellow.volume += color.yellow;
	}
}

//CMYK�̃Q�[�W��MAX���`�F�b�N����
void PowerGauge::CheckVolumeMax()
{
	//�}�[���^���W�߂��ʂ�100%�ȏゾ������}�[���^��MAX�t���O��1��
	if (magenta.volume >= 100.0f)
	{
		remainder += (int)magenta.volume - 100;
		magenta.volume = 100.0f;
		magenta.maxFlg = 1;
	}

	//�C�G���[���W�߂��ʂ�100%�ȏゾ������C�G���[��MAX�t���O��1��
	if (yellow.volume >= 100.0f)
	{
		remainder += (int)yellow.volume - 100;
		yellow.volume = 100.0f;
		yellow.maxFlg = 1;
	}

	//�V�A�����W�߂��ʂ�100%�ȏゾ������V�A����MAX�t���O��1��
	if (cyan.volume >= 100.0f)
	{
		remainder += (int)cyan.volume - 100;
		cyan.volume = 100.0f;
		cyan.maxFlg = 1;
	}

	//CMY���S��100%�ȏゾ������摜��]�A�j���[�V�����t���O��1��
	if ((magenta.maxFlg == 1) && (yellow.maxFlg == 1) && (cyan.maxFlg == 1))
	{
		rota_flg = 1;
	}
}

//�����Q�[�W�̉�]����
void PowerGauge::RotaGauge()
{
	num += 2.5f * i++;

	if (num >= 360.0f)
	{
		//3���]�����狭���Q�[�W����(MAX)��
		if (j >= 6)
		{
			black.volume = 100.0f;
			black.maxFlg = 1;
			rota_flg = 0;
		}

		j++;
		num = 0.0f;
	}
}

//������Ԃ��I�������̏���������
void PowerGauge::InitGauge()
{
	black.volume = 0.0f;
	magenta.volume = 0.0f;
	yellow.volume = 0.0f;
	cyan.volume = 0.0f;
	black.maxFlg = 0;
	magenta.maxFlg = 0;
	cyan.maxFlg = 0;
	yellow.maxFlg = 0;
	num = 0.0f;
	i = 0;
	j = 0;
}

void PowerGauge::SetColorRem()
{
	remainder = 0;
}