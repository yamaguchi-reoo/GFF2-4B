#pragma once

//��ʃT�C�Y
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define G_POWER			1	//�d�͂̋���
#define PLAYER_WIDTH  75	//�v���C���[�̕�
#define PLAYER_HEIGHT 160	//�v���C���[�̍���

//�X�N���[���֘A
#define LEFT_END	300
#define RIGHT_END	750
#define SCREEN_LEFT_END 0
#define FLOOR_NUM	3	//���̐�

//�|
#define BAMBOO_NUM 3 //�|�̐ς܂�Ă��鐔
#define BAMBOO_MAX 15 //�|�̍ő吔

#define ATTACK_NUM 200   //��ʂɑ��݂ł���ő�̍U����
#define ATTACK_SUB_NUM 100   //for����ۂ̑��݂ł���ő�̍U����

//�U�����ɒN���U�������̂����f����p
#define PLAYER	0	//�v���C���[
#define ENEMY	1	//�G

//�U���̎��
#define MELEE 0		//�ߐڍU��
#define BULLET 1	//�������U���i�g�����܂ށj

//�X�e�[�W	
#define BOX_HEIGHT	45					//�X�e�[�W�̃u���b�N�������̍���
#define BOX_WIDTH	48					//�X�e�[�W�̃u���b�N�������̕�
#define MAX_STAGE_HEIGHT 60				//�X�e�[�W�̃u���b�N�̏c�̍ő��
#define MAX_STAGE_WIDTH  3000			//�X�e�[�W�̃u���b�N�̉��̍ő��
#define STAGE_GOAL (BOX_WIDTH*5)		//�X�e�[�W�ŃS�[���ƂȂ���W
#define SIGH_BOARD_NUM 5				//�Ŕ̐�
//�G�l�~�[�̐�
#define ZAKURO_MAX 35	//�U�N���̍ő吔
#define IRUKA_MAX 20		//�C���J�̍ő吔
#define HIMAWARI_MAX 20	//�Ђ܂��̍ő吔

//�G�t�F�N�g
#define SPLASH_MAX 50

//�A�C�e��
#define ITEM_MAX 10 //��ʂɏo���ł���A�C�e���̍ő吔
#define JAR_MAX 7  //��̍ő吔

#define PLAYER_SLASH_ONE 0
#define PLAYER_SLASH_TWO 1
#define PLAYER_SLASH_THREE 2
#define PLAYER_SLASH_FOUR 3
#define PLAYER_JUMP_SLASH 4
#define PLAYER_JUMP_SLASH_END 5
#define POWERUP_PLAYER_SLASH_ONE 6
#define POWERUP_PLAYER_SLASH_TWO 7
#define POWERUP_PLAYER_SLASH_THREE 8
#define POWERUP_PLAYER_SLASH_FOUR 9
#define POWERUP_PLAYER_JUMP_SLASH 10
#define POWERUP_PLAYER_JUMP_SLASH_END 11
#define HIMAWARI_BULLET 12
#define BOSSZAKURO_WAVES 13
#define BOSSHIMAWARI_BULLET 14