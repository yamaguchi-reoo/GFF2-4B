#include "Score.h"
#include "DxLib.h"

Score::Score()
{
	// �c�w�t�H���g�f�[�^�t�@�C����ǂݍ��݁A�t�H���g�n���h����ϐ� FontHandle �ɕۑ�����
	FontHandle = LoadFontDataToHandle("Misogi.dft", 1);

	Score = 0;
}

Score::~Score()
{
	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(FontHandle);
}

void Score::Update()
{
}

void Score::Draw() const
{
	// �쐬�����t�H���g�ŉ�ʍ���Ɂw�g�����������I�I�x�Ɣ��F�̕������`�悷��
	DrawStringToHandle(0, 0, "���_:�Z�Z�Z", GetColor(255, 255, 255), FontHandle);
}
