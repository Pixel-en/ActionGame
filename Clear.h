#pragma once
#include "Engine/GameObject.h"

//�N���A�̃N���X
class Clear :public GameObject
{
public:

	//�R���X�g���N�^
	Clear(GameObject* parent);

	//�f�X�g���N�^
	~Clear();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;


};

