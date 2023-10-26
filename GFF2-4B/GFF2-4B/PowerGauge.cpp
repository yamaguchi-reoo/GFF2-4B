#include "PowerGauge.h"

PowerGauge::PowerGauge()
{
	magenta.x = 109;
	magenta.y = 64;
	magenta.h = 45;
	magenta.volume = 0.0f;
	magenta.ratio = 0.0f;
	magenta.maxFlg = 0;

	yellow.x = 80;
	yellow.y = 110;
	yellow.h = 45;
	yellow.volume = 0.0f;
	yellow.ratio = 0.0f;
	yellow.maxFlg = 0;

	cyan.x = 140;
	cyan.y = 110;
	cyan.h = 45;
	cyan.volume = 0.0f;
	cyan.ratio = 0.0f;
	cyan.maxFlg = 0;

	black.x = 140;
	black.y = 130;
	black.h = 115;
	black.volume = 0.0f;
	black.ratio = 0.0f;
	black.maxFlg = 0;

	powerFlg = 0;

	image[0] = LoadGraph("resource/images/�����Q�[�W1.png");
	image[1] = LoadGraph("resource/images/�����Q�[�W2.png");
	image[2] = LoadGraph("resource/images/�����Q�[�W3.png");
}

PowerGauge::~PowerGauge()
{
}

void PowerGauge::Update()
{
	if (black.maxFlg == 0)
	{
		//�f�o�b�N�p(RB���������狭���Q�[�W��MAX�ɂȂ�)
		if ((black.maxFlg == 0) && (PadInput::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) == true))
		{
			magenta.volume += 50.0f;
			cyan.volume += 50.0f;
			yellow.volume += 50.0f;
		}

		CheckVolumeMax();

		VolumeSet();

		//�f�o�b�N�p(RB���������狭���Q�[�W��MAX�ɂȂ�)
		if ((black.maxFlg == 0) && (PadInput::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER) == true))
		{
			black.volume = 100.0f;
			black.maxFlg = 1;
		}

	}
	else if(black.maxFlg == 1)
	{
		//�����Q�[�W��MAX���AX�{�^���������ꂽ�狭����ԃt���O��1��
		if ((black.maxFlg == 1) && (PadInput::OnButton(XINPUT_BUTTON_X) == true))
		{
			powerFlg = 1;
		}
	}

	//������ԃt���O��1�������狭���Q�[�W�����炷
	if (powerFlg == 1)
	{
		BlackGauge();
		VolumeSet();
	}
}

void PowerGauge::Draw() const
{
	DrawGraph(5, 5, image[2], TRUE);

	if (black.maxFlg == 0)
	{
		//�����Q�[�W��MAX����Ȃ��Ƃ�
		if (magenta.volume != 0.0f) 
		{
			DrawBox(magenta.x - 50, magenta.y - (int)magenta.ratio, magenta.x, magenta.y, 0xe4007f, TRUE);
		}
		if (cyan.volume != 0.0f)
		{
			DrawBox(cyan.x - 50, cyan.y - (int)cyan.ratio, cyan.x, cyan.y, 0x00ffff, TRUE);
		}
		if (yellow.volume != 0.0f)
		{
			DrawBox(yellow.x - 50, yellow.y - (int)yellow.ratio, yellow.x, yellow.y, 0xffff00, TRUE);
		}

		DrawGraph(20, 12, image[1], TRUE);
	}
	else if ((black.maxFlg == 1) && (powerFlg == 0))
	{
		//�����Q�[�W��MAX�̂Ƃ�
		DrawBox(black.x - 121, black.y - 115, black.x, black.y, 0x000000, TRUE);
	}
	else if(powerFlg == 1)
	{
		//�����Q�[�W��MAX��X�{�^���������ꂽ�Ƃ�
		DrawBox(black.x - 121, black.y - (int)black.ratio, black.x, black.y, 0x000000, TRUE);
	}
	
	DrawGraph(5, 5, image[0], TRUE);

	//�f�o�b�N�\��
	DrawFormatString(300, 10, 0xffffff, "%f", magenta.volume);
}

//�Q�[�W�̗��܂����v�Z
float PowerGauge::VolumeCalculate(float volume, float h)
{
	float i = 0.0f;

	i = volume / 100.0f * h;

	return i;
}

//�Q�[�W�̗��܂����v�Z�����l����
void PowerGauge::VolumeSet()
{
	magenta.ratio = VolumeCalculate(magenta.volume, magenta.h);
	yellow.ratio = VolumeCalculate(yellow.volume, yellow.h);
	cyan.ratio = VolumeCalculate(cyan.volume, cyan.h);
	black.ratio = VolumeCalculate(black.volume, black.h);
}

//���Ԍo�߂ō��̃Q�[�W�����炷
void PowerGauge::BlackGauge()
{
	float i = 0;

	if (black.volume > 0.0f)
	{
		//������ԂŁA�Q�[�W��0%�ɂȂ�܂ŏ��X�Ɍ��炷
		i = black.volume;
		black.volume = i - 0.17;
	}
	else
	{
		//������Ԃ��I�������A������Ԃ��������ċ����Q�[�W��������Ԃɖ߂�
		powerFlg = 2;
		InitGauge();
	}
}

//������Ԃ��ǂ����n��
int PowerGauge::PowerGaugeState()
{
	if (powerFlg == 1)
	{
		//�������
		return 1;
	}
	else if (powerFlg == 2)
	{
		//��������
		return 2;
	}

	return 0;
}

//������Ԃ��ǂ�����ۑ�����ϐ��̒l�������̒l�ɕύX
void PowerGauge::SetPowerFlg(int i)
{
	powerFlg = i;
}

//�G�����Ƃ����F�A�ʂ��Q�[�W�ɉ��Z
void PowerGauge::SetVolume(int color,int volume)
{
	switch (color)
	{
		case 0:
			//�}�[���^
			if (magenta.maxFlg == 0)
			{
				magenta.volume += (float)volume;
			}
			
			break;

		case 1:
			//�V�A��
			if (cyan.maxFlg == 0)
			{
				cyan.volume += (float)volume;
			}
			
			break;

		case 2:
			//�C�G���[
			if (yellow.maxFlg == 0)
			{
				yellow.volume += (float)volume;
			}

			break;

		default:
			break;
	}

}

//CMYK�̃Q�[�W��MAX���`�F�b�N����
void PowerGauge::CheckVolumeMax()
{
	//�}�[���^���W�߂��ʂ�100%�ȏゾ������}�[���^��MAX�t���O��1��
	if (magenta.volume >= 100.0f)
	{
		magenta.maxFlg = 1;
	}

	//�C�G���[���W�߂��ʂ�100%�ȏゾ������C�G���[��MAX�t���O��1��
	if (yellow.volume >= 100.0f)
	{
		yellow.maxFlg = 1;
	}

	//�V�A�����W�߂��ʂ�100%�ȏゾ������V�A����MAX�t���O��1��
	if (cyan.volume >= 100.0f)
	{
		cyan.maxFlg = 1;
	}

	//CMY���S��100%�ȏゾ�����獕��MAX�t���O��1��
	if ((magenta.maxFlg == 1) && (yellow.maxFlg == 1) && (cyan.maxFlg == 1))
	{
		black.volume = 100.0f;
		black.maxFlg = 1;
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
}