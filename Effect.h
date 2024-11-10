#pragma once
#include "Engine/GameObject.h"

class Effect
	: public GameObject
{

public:
	enum EffectType
	{
		KILL, GRASS, JUMP, SLASH, MINE, WALK, RUN, END
	};
private:

	int hImage_;

	int framecnt_;	//フレームのカウント
	int FCmax_;	//フレームカウントの最大値
	int animframe_;	//アニメーションのフレームカウント
	int AFmax_;		//アニメーションのフレーム数
	std::string fileName_;
	XMFLOAT3 cameraPos_;
	bool canLoop_;
	bool isRight_;	//右を向いているか
	VECTOR imagesize_;

public:

	Effect(GameObject* parent);

	~Effect();
	//初期化
	void Initialize() override;

	void Reset(Transform pos, EffectType _effecttype, bool _isRight);
	void Reset(Transform pos, EffectType _effecttype);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetEffectObjectName(std::string _name) { objectName_ = _name; };
	void SetBackEffectPos(XMFLOAT3 pos, bool _dir);
	void SetFrontEffectPos(XMFLOAT3 pos, bool _dir);
};

