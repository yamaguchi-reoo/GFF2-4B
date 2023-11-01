#include "PowerGauge.h"

PowerGauge::PowerGauge()
{
	magenta.x = 112;
	magenta.y = 70;
	magenta.h = 65;
	magenta.volume = 0.0f;
	magenta.ratio = 0.0f;
	magenta.maxFlg = 0;

	cyan.x = 152;
	cyan.y = 130;
	cyan.h = 115;
	cyan.volume = 0.0f;
	cyan.ratio = 0.0f;
	cyan.maxFlg = 0;

	yellow.x = 103;
	yellow.y = 150;
	yellow.h = 84;
	yellow.volume = 0.0f;
	yellow.ratio = 0.0f;
	yellow.maxFlg = 0;

	black.x = 143;
	black.y = 134;
	black.h = 124;
	black.volume = 0.0f;
	black.ratio = 0.0f;
	black.maxFlg = 0;

	powerFlg = 0;

	image[0] = LoadGraph("resource/images/magatama_line.png");
	image[1] = LoadGraph("resource/images/black_line.png");

	
	//�}�X�N�f�[�^�ǂݍ���	
	MaskHandle[0] = LoadMask("resource/images/Magatama_mask1.png");
	MaskHandle[1] = LoadMask("resource/images/black_mask.png");

}

PowerGauge::~PowerGauge()
{
	// �}�X�N�f�[�^���폜
	DeleteMask(MaskHandle[0]);
	DeleteMask(MaskHandle[1]);
}

void PowerGauge::Update()
{
	if (black.maxFlg == 0)
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

		/*if (magenta.maxFlg == 0)
		{
			magenta.volume += 1.0f;
		}*/
		/*if (cyan.maxFlg == 0)
		{
			cyan.volume += 0.5f;
		}
		if (yellow.maxFlg == 0)
		{
			yellow.volume += 1.0f;
		}*/

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
#ifdef _DEBUG

	//�f�o�b�N�\��
	//DrawFormatString(300, 10, 0xffffff, "%d", MaskHandle[1]);

#endif // _DEBUG
	DrawBox(200, 10, 230, 40, 0xffff00, TRUE);

	//�}�X�N��ʂ��쐬
	CreateMaskScreen();

	if (black.maxFlg == 0)
	{
		//DrawGraph(5, 3, image[0], TRUE);

		//���[�h�����}�X�N�f�[�^����ʂ̍���ɕ`��
		DrawMask(5, 3, MaskHandle[0], DX_MASKTRANS_NONE);

		DrawBox(5, 3, 155, 153, 0xffffff, TRUE);

		//�����Q�[�W��MAX����Ȃ��Ƃ�
		if (yellow.volume != 0.0f)
		{
			DrawBox(yellow.x - 92, yellow.y - (int)yellow.ratio, yellow.x, yellow.y, 0xffff00, TRUE);
		}
		if (cyan.volume != 0.0f)
		{
			DrawBox(cyan.x - 65, cyan.y - (int)cyan.ratio, cyan.x, cyan.y, 0x00ffff, TRUE);
		}
		if (magenta.volume != 0.0f)
		{
			DrawBox(magenta.x - 107, magenta.y - (int)magenta.ratio, magenta.x, magenta.y, 0xe4007f, TRUE);
		}
		
		//�}�`�`��̏d�Ȃ���B��
		DrawBox(87, 70, 112, 130, 0xffffff, TRUE);

		if (cyan.volume >= 2.0f)
		{
			DrawBox(87, 130 - (int)((cyan.volume * 2.0f) / 100.0f * 57.5f), 112, 130, 0x00ffff, TRUE);
		}

		if (magenta.volume >= 2.0f)
		{
			DrawBox(15, 66, 70, 70, 0xffffff, TRUE);

			if (yellow.volume > 95.0f)
			{
				DrawBox(15, 70 - (int)(yellow.volume / 100.0f * 4), 70, 70, 0xffff00, TRUE);
		    }
		}

		DrawBox(80, 10, 112, 70, 0xffffff, TRUE);

		if (magenta.volume >= 14.0f)
		{
			DrawBox(80, 70 - (int)((magenta.volume * 1.1f) / 100.0f * 59.5f ), 112, 70, 0xe4007f, TRUE);
		}
	}
	else if ((black.maxFlg == 1) && (powerFlg == 0))
	{
		//DrawGraph(5, 2, image[1], TRUE);
		
		//���[�h�����}�X�N�f�[�^����ʂ̍���ɕ`��
		DrawMask(5, 3, MaskHandle[1], DX_MASKTRANS_NONE);

		DrawBox(5, 3, 155, 138, 0xffffff, TRUE);

		//�����Q�[�W��MAX�̂Ƃ�
		DrawBox(black.x - 127, black.y - 124, black.x, black.y, 0x000000, TRUE);
	}
	else if(powerFlg == 1)
	{
		//DrawGraph(5, 2, image[1], TRUE);

		//���[�h�����}�X�N�f�[�^����ʂ̍���ɕ`��
		DrawMask(5, 3, MaskHandle[1], DX_MASKTRANS_NONE);

		DrawBox(5, 3, 150, 138, 0xffffff, TRUE);

		//�����Q�[�W��MAX��X�{�^���������ꂽ�Ƃ�
		DrawBox(black.x - 127, black.y - (int)black.ratio, black.x, black.y, 0x000000, TRUE);
	}

	// �}�X�N��ʂ��폜
	DeleteMaskScreen();
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
		black.volume = i - 0.17f;
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
		magenta.maxFlg = 1;
		magenta.volume = 100.0f;
	}

	//�C�G���[���W�߂��ʂ�100%�ȏゾ������C�G���[��MAX�t���O��1��
	if (yellow.volume >= 100.0f)
	{
		yellow.maxFlg = 1;
		yellow.volume = 100.0f;
	}

	//�V�A�����W�߂��ʂ�100%�ȏゾ������V�A����MAX�t���O��1��
	if (cyan.volume >= 100.0f)
	{
		cyan.maxFlg = 1;
		cyan.volume = 100.0f;
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