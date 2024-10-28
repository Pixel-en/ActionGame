#include "Object.h"

namespace {
	const float ENEMY_GRAVITY{ 9.8f / 60.0f };
}

class Enemy :public Object {

	const VECTOR IMAGESIZE{ 64.0f,64.0f };
	const VECTOR HITBOXSIZE{ 32.0f,32.0f };

	enum EAnimation {
		IDOL,
		ATTACK,
		MOVE,
		HURT,
		DEATH,
	};
	EAnimation animtype_;
	EAnimation BEanimtype_;


	virtual void UpdateIdol();
	virtual void UpdateAttack();
	virtual void UpdateMove();
	virtual void UpdateHurt();
	virtual void UpdateDeath();

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Enemy(GameObject* parent);

	//�f�X�g���N�^
	virtual ~Enemy();

	//������
	virtual void Initialize() override;

	//�X�V
	virtual void Update() override;

	//�`��
	virtual void Draw() override;

	//�J��
	virtual void Release() override;
};