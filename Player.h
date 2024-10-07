#pragma once
#include "Engine/GameObject.h"
#include "HitObject.h"

const int ATTACKTYPENUM{ 5 };

class Player :public GameObject
{

	int hImage_;


	enum Animation {
		NONE = -1,
		IDOL = 0,
		WALK,
		RUN,
		JUMP,
		ATTACK,
		ATTACK2,
		ATTACK3,
		CLIMB,
		COLLECTION,
		MAGIC,
		DAMAGE,
		DEATH,
	};

	Animation animtype_;	//�A�j���[�V�����̎��
	Animation BEanimtype_;	//�O�̃t���[���̃A�j���[�V����

	int animframe_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Player(GameObject* parent);

	//�f�X�g���N�^
	~Player();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool HitCheck(int _x, int _y, SIZE _size);

	XMFLOAT3 GetHitBoxPosition();

	void DeadState();

	bool isIdol() {
		if (animtype_ == Animation::IDOL)
			return true;
		return false;
	};

	bool isDie() {
		if (animtype_ == Animation::DEATH)
			return true;
		return false;
	};

};

