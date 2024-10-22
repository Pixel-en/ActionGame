#pragma once
#include "Object.h"
#include <vector>

//�ޗ��̃N���X
class Material :public Object
{
	int sizeX_;
	int sizeY_;

	std::vector<std::string> Mlist;
	float Gaccel;

	float durability_;	//�ϋv(�b)
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Material(GameObject* parent);

	//�f�X�g���N�^
	~Material();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Mining(float _mintime);

};

