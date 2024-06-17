#pragma once
#include "Engine/GameObject.h"

//�S�[���������N���X
class Goal :public GameObject
{

	int hImage_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Goal(GameObject* parent);

	//�f�X�g���N�^
	~Goal();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetPosition(int _x, int _y) {
		transform_.position_.x = _x;
		transform_.position_.y = _y;
	};
};

