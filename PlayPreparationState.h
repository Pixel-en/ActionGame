#pragma once
#include "Engine/GameObject.h"

class PlayPreparationState :public GameObject
{

	int hImage_;
	int hImageState_;
	int hImageCursor_;
	int poscount_;

	void ParameterReader();
	void ParameterWrite();

	int param_[4];
	bool button_;
	bool startflag_;

	//�X�e�[�^�X�̊���U��̎c��
	int residue_;

	int filelinecount_;
	std::string message_[6];
	bool cursorflag_;
	int messagenum_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayPreparationState(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool GetStartFlag() { return startflag_; };
};

