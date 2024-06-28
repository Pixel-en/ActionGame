#pragma once
#include "Engine/GameObject.h"


class Player :public GameObject
{

	int hImage_;

	float pdir_;

	void TestFunc();

	int framecnt_;
	bool attackon_;
	float rigortimer_;
	bool rigoron_;
	bool onjump_;

	bool flagon_;

	int animtype_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Player(GameObject* parent);

	//�f�X�g���N�^
	~Player();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool HitCheck(int _x, int _y, SIZE _size);

};

