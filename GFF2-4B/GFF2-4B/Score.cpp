#include "Score.h"
#include "DxLib.h"

Score::Score()
{
	// �c�w�t�H���g�f�[�^�t�@�C����ǂݍ��݁A�t�H���g�n���h����ϐ� FontHandle �ɕۑ�����
	font_handle = LoadFontDataToHandle("Misogi.dft", 1);

	total_score = 0;
}

Score::~Score()
{
	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(font_handle);
}

void Score::Update()
{
}

void Score::Draw() const
{
	// �쐬�����t�H���g�ŉ�ʍ���Ɂw�g�����������I�I�x�Ɣ��F�̕������`�悷��
	DrawStringToHandle(160, 30, "���_:", 0xffffff, font_handle);
}
