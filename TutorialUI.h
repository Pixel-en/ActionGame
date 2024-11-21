#pragma once
#include "Engine/GameObject.h"

class TutorialUI :public GameObject
{

	int hImageGuide_;
	int guidenum_;
	VECTOR UIpos_;
	VECTOR UIpos2_;
	int hImageFrame_;
	

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

