#pragma once
#include "Object.h"


class MoveObject :public Object
{
	float sinAngle_;
	float baseY_;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	MoveObject(GameObject* parent);

	//�f�X�g���N�^
	~MoveObject() override;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Setpos(float x, float y);
};

