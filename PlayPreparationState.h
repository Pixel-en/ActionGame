#pragma once
#include "Engine/GameObject.h"

class PlayPreparationState :public GameObject
{

	int hImage_;
	int hImageState_;
	int hImageCursor_;
	int poscount_;

	void ParameterReader();
	void ParameterWrite();

	int param_[4];
	bool button_;
	bool startflag_;

	//ステータスの割り振りの残り
	int residue_;

	int filelinecount_;
	std::string message_[6];
	bool cursorflag_;
	int messagenum_;
	XINPUT_STATE pad;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayPreparationState(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool GetStartFlag() { return startflag_; };
};

