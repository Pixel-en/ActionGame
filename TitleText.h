#pragma once
#include "Engine/GameObject.h"

//�A���t�@�x�b�g�Ɛ����ƃJ�^�J�i��!?���g�����
class TitleText :public GameObject
{
	int hImage_;
	int hImageW_;
	int hImageUI_;

	char CharNum(char c);

	std::string fontarr;

public:
	/// <summary>
	/// �����\��
	/// </summary>
	/// <param name="_text">�\���������e�L�X�g</param>
	/// <param name="_posx">�\������ꏊ��x���W</param>
	/// <param name="_posy">�\������ꏊ��y���W</param>
	void DrawString(std::string _text, float _posx, float _posy);

	/// <summary>
	/// �����\��
	/// </summary>
	/// <param name="_text">�\���������e�L�X�g</param>
	/// <param name="_posx">�\������ꏊ��x���W</param>
	/// <param name="_posy">�\������ꏊ��y���W</param>
	/// <param name="black">�����̐F�����ł����� false�͔�</param>
	void DrawString(std::string _text, float _posx, float _posy,bool black);

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	TitleText(GameObject* parent);

	//�f�X�g���N�^
	~TitleText();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

