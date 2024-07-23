#pragma once
#include "Engine/GameObject.h"
#include <map>

class Playsound :public GameObject
{
	std::map<std::string,int> hSound_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Playsound(GameObject* parent);

	//�f�X�g���N�^
	~Playsound();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SoundON(std::string str);

	void PlayMusics(std::string str);
};

