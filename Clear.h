#pragma once
#include "Engine/GameObject.h"

//�N���A�̃N���X
class Clear :public GameObject
{
	bool isgoal_;	//�S�[���������ǂ���
	bool isGetM_;	//�ޗ���S����������H
	int Mval_;		//�Ƃ����ޗ��̐�
	int Eval_;		//�c��̓G�̐�

	float cleartimer_;	//�N���A������̃^�C�}�[

public:

	bool isFlag_;	//���̃X�e�[�W�Ɉړ����Ă�����
	bool GetFlag() { return isFlag_; };


	//�R���X�g���N�^
	Clear(GameObject* parent);

	//�f�X�g���N�^
	~Clear();

	//������
	void Initialize() override;

	void Reset();

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetMaterialValue(int _val) { Mval_ = _val; };
};

