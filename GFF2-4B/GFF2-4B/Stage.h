#pragma once
#include "BoxCollider.h"
#include "Scroll.h"
class Stage:
	public BoxCollider
{
private:
	int type;		//���̎��(0=�� 1=�n�� 2=�� 3=�� 4=�_)
	bool debug_flg;		//���̎�ނ�\�����邩
public:
	Stage(float _x, float _y, float _width, float _height,int _type);
	~Stage();
	void Update();
	void Draw()const;

	//�X�e�[�W�����炷����(�g���₷���p�ɂ������Ă������OK)
	void MoveStage(float _x, float _y);
	//��ނ��擾(0=�� 1=�n�� 2=�� 3=�� 4=�_)
	int GetStageType() { return type; }
	//��ނ�ݒ�
	void SetStageType(int _type) { type = _type; }
	//���̎�ނ�\������
	void SetDebugFlg() { debug_flg = true; }
};
