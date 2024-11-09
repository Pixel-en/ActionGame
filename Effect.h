#pragma once
#include "Engine/GameObject.h"

class Effect
	: public GameObject
{

public:
	enum EffectType
	{
		KILL, GRASS, JUMP, SLASH, MINE, END
	};
private:

	int hImage_;

	int framecnt_;	//�t���[���̃J�E���g
	int FCmax_;	//�t���[���J�E���g�̍ő�l
	int animframe_;	//�A�j���[�V�����̃t���[���J�E���g
	int AFmax_;		//�A�j���[�V�����̃t���[����
	std::string fileName_;
	XMFLOAT3 cameraPos_;
	bool canLoop_;
	bool isRight_;	//�E�������Ă��邩

public:

	Effect(GameObject* parent);

	~Effect();
	//������
	void Initialize() override;

	void Reset(Transform pos, EffectType _effecttype,bool _isRight);
	void Reset(Transform pos, EffectType _effecttype);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

