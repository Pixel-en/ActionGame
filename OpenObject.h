#pragma once
#include "Engine\GameObject.h"


class OpenObject :
	public GameObject
{
	int hImage_;
	int weight;
	int hight;
	int height;
	int frame;
	float timer;
	bool isAnim;
public:
	OpenObject(GameObject* parent);

	//�f�X�g���N�^
	~OpenObject();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
	XMFLOAT3 GetHitTransPos();
	VECTOR GetHitBox();
	void Open();
	void SetPos(int x,int y);
};
