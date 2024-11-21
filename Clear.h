#pragma once
#include "Engine/GameObject.h"

//�N���A�̃N���X
class Clear :public GameObject
{
	bool isgoal_;	//�S�[���������ǂ���
	bool isGetM_;	//�ޗ���S�������
	bool isKillE_;
	bool ischeck_;	//�`�F�b�N�|�C���g��ʂ������ǂ���
	int Mcount_;		//�ޗ��̐�
	int Ecount_;		//�G�̐�

	bool isFlag_;	//���̃X�e�[�W�Ɉړ����Ă�����

	bool isBonusEnemy_;
	bool isBonusMaterial_;

	void BonusScore();
public:

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

	void AddMcount() { Mcount_ += 1; };
	void AddEcount() { Ecount_ += 1; };

	void DeleteMaterial() { Mcount_ = -1; }
	void DeleteEnemy() { Ecount_ = -1; }
	bool GetBonusEnemy() { return isBonusEnemy_; };
	bool GetBonusMaterial() { return isBonusMaterial_; };
};

