#pragma once
#include "Engine/GameObject.h"

class Field :public GameObject
{
	int hImage_;

	int* Map;
	int width;
	int height;

	std::string filename;

	/// <summary>
	/// ���̃u���b�N��
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <returns>�u���b�N�̖��O</returns>
	std::string WhatBlock(int x, int y);

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Field(GameObject* parent);

	//�f�X�g���N�^
	~Field();

	//������
	void Initialize() override;

	void Reset();

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/// <summary>
	/// �t�@�C���̖��O���Z�b�g����
	/// </summary>
	/// <param name="_filename">�t�@�C���̖��O</param>
	void SetFileName(std::string _filename) { filename = _filename; };

	/// <summary>
	/// �������̓����蔻��̃`�F�b�N
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <returns></returns>
	int CollisionDownCheck(int x, int y);

	/// <summary>
	/// ������̓����蔻��̃`�F�b�N
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <returns></returns>
	int CollisionUpCheck(int x, int y);

	/// <summary>
	/// �������̓����蔻��`�F�b�N
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <returns></returns>
	int CollisionLeftCheck(int x, int y);


	/// <summary>
	/// �E�����̓����蔻��`�F�b�N
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <returns></returns>
	int CollisionRightCheck(int x, int y);
	
	/// <summary>
	/// �I�u�W�F�N�g�Ƃ̓����蔻����`�F�b�N
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <returns></returns>
	bool CollisionObjectCheck(int x, int y);
};

