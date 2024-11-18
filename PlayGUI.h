#pragma once
#include "Engine/GameObject.h"
#include <vector>

class PlayGUI final :public GameObject
{
	int hImage_;
	int hImageUI_;

	int hImagekey_;

	std::string text;
	float x, y;

	std::vector<VECTOR> chipnum_;
	std::vector<VECTOR> scorechipnum_;

	int Enum;
	int Mnum;
	struct Data
	{
		int handle;
		SIZE imagesize;
	};
	Data Edata;
	Data Mdata;

	float CDtimer_;
	bool outset_;

	int playtimer_;
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

	/// <summary>
	/// 文字表示
	/// </summary>
	/// <param name="_text">表示したいテキスト</param>
	/// <param name="_posx">表示する場所のx座標</param>
	/// <param name="_posy">表示する場所のy座標</param>
	void DrawString(std::string _text, float _posx, float _posy);
};

