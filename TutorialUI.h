#pragma once
#include "Engine/GameObject.h"

class TutorialUI :public GameObject
{
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	TutorialUI(GameObject* parent);

	//�f�X�g���N�^
	~TutorialUI();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

