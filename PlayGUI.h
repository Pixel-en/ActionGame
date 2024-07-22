#pragma once
#include "Engine/GameObject.h"

class PlayGUI final :public GameObject
{
	int hImage_;

	int CharNum(char c);

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	PlayGUI(GameObject* parent);

	//�f�X�g���N�^
	~PlayGUI();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

