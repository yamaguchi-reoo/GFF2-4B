#pragma once

#define DEBUG true		//�f�o�b�O�p�\���⑀���K�p���邩 false=�K�p���Ȃ� true=�K�p

//��ʃT�C�Y
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define G_POWER			1	//�d�͂̋���
#define PLAYER_WIDTH  75	//�v���C���[�̕�
#define PLAYER_HEIGHT 150	//�v���C���[�̍���

//�X�N���[���֘A
#define LEFT_END	300
#define RIGHT_END	750
#define SCREEN_LEFT_END 0
#define FLOOR_NUM	3	//���̐�

#define BAMBOO_NUM 3 //�|�̐ς܂�Ă��鐔

#define ATTACK_NUM 100   //��ʂɑ��݂ł���ő�̍U����

//�U�����ɒN���U�������̂����f����p
#define PLAYER	0	//�v���C���[
#define ENEMY	1	//�G

//�U���̎��
#define MELEE 0		//�ߐڍU��
#define BULLET 1	//�������U���i�g�����܂ށj

//�X�e�[�W(�S�������A�ŏI��i)
#define STAGE_HEIGHT 16									//�X�e�[�W�̃u���b�N�̏c�̌�
#define STAGE_WIDTH  32									//�X�e�[�W�̃u���b�N�̉��̌�
#define BOX_SIZE	(SCREEN_HEIGHT/STAGE_HEIGHT)		//�X�e�[�W�̃u���b�N�������̑傫��(�Ƃ�ܐ����`)
//�G�l�~�[�̐�
#define ZAKURO_MAX 5 //�U�N���̍ő吔
#define IRUKA_MAX 5 //�U�N���̍ő吔