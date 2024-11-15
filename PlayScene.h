#pragma once
#include "Engine/GameObject.h"
#include "vector"
#include "ScoreAndTime.h"

//�e�X�g�V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
private:
	std::string Filename_;

	//float playtimer_;	//�v���C���̐�������

	float starttimer_;	//�X�^�[�g����܂ł̑ҋ@���Ԃ̃^�C�}�[
	float counttimer_;	//�N���A���Ă���̎��ɍs���܂ł̃^�C�}�[
	float deathtimer_;	//����ł���̃^�C�}�[

	enum PlayState {
		STAY,
		PLAY,
		CLEAR,
		DEATH,
	};
	PlayState state;

	void UpdateStay();
	void UpdatePlay();
	void UpdateClear();
	void UpdateDeath();

	std::vector<std::string> maplist;
	int listnum;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	void Reset();

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool CanMove() { return (state == PlayState::PLAY); };

	void DeadState();

	float GetPlayTimer() { return Score::GetTime(); };
};