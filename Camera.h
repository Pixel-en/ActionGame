#pragma once
#include "Engine/GameObject.h"

class Camera :public GameObject
{
	int value;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Camera(GameObject* parent) :GameObject(parent) { value = 0; };
	//�f�X�g���N�^
	~Camera() {};

	void SetValue(int v) { value = v; }
	int GetValue() { return value; }

	////������
	//void Initialize() override;

	////�X�V
	//void Update() override;

	////�`��
	//void Draw() override;

	////�J��
	//void Release() override;
};

