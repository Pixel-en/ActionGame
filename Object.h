#pragma once
#include "Engine/GameObject.h"

class Object :public GameObject
{
protected:
	int hImage_;

public:

	Object(GameObject* parent);
	Object(GameObject* parent, const std::string& name);

	//�f�X�g���N�^
	virtual ~Object();

	//������
 	virtual void Initialize() override;

	virtual void Reset();

	//�X�V
	virtual void Update() override;

	//�`��
	virtual void Draw() override;

	//�J��
	virtual void Release() override;

	virtual bool IsHitting();
};

