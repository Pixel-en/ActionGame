#pragma once
#include"Engine//GameObject.h"
class RankingsScene :
    public GameObject
{
public:
	RankingsScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
private:
};

