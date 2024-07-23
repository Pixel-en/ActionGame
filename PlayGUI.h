#pragma once
#include "Engine/GameObject.h"

class PlayGUI final :public GameObject
{
	int hImage_;
	int hImageUI_;

	int CharNum(char c);

	std::string text;
	float x, y;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	PlayGUI(GameObject* parent);

	//デストラクタ
	~PlayGUI();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;


private:

	/// <summary>
	/// 文字表示
	/// </summary>
	/// <param name="_text">表示したいテキスト</param>
	/// <param name="_posx">表示する場所のx座標</param>
	/// <param name="_posy">表示する場所のy座標</param>
	void DrawString(std::string _text, float _posx, float _posy);
};

