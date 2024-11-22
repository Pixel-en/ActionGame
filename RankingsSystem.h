#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<algorithm>
#include"Engine/GameObject.h"

class CsvReader;
class OutText;

class RankingsSystem : public GameObject
{
public:
	RankingsSystem(GameObject* parent);

	~RankingsSystem();

	void Initialize();

	void Update();

	void Draw();

	void Release();

	void DrawOK(bool _output) { output_ = _output; };

	//受信したかどうか
	bool RecvOK() { return RecvOK_; };
private:

	/// <summary>
	/// 名前入力用UI表示(キーマウ用)
	/// </summary>
	void DrawWriteUI();

	/// <summary>
	/// 名前入力用UI表示(パッド用)
	/// </summary>
	void DrawWriteUICn();

	void NameBar(std::string _str, float _fSize, float _space, float _x1, float _y1, float _x2, float _y2, float _eraseTimer, float _eraseTime);

	void RecvDataInsert(std::vector<std::string> n, std::vector<std::string> s, std::vector<std::string> r);

	std::string output_csv_file_path_RecvRankingsSortData;
	CsvReader* csv;
	int width;
	int height;
	std::map <std::string, float> Rankings;
	std::vector<std::pair<float, std::string>> r;

	OutText* tText;

	bool SetEnd;

	float eraseTime;
	float eraseTimer;
	float flame;
	float eraseAlpha;

	int x1, y1, x2, y2;

	int space;
	int word;
	int n;
	int a;
	int count;
	int MaxWord;

	int cx1, cy1, cx2, cy2;
	bool prevKey;

	int InputHandle;
	char Name[256];
	char cName[256];
	std::string str;

	

	enum DEVICE
	{
		KEY_AND_MOUSE = 0,
		PAD
	};

	int nowDevice;

	XINPUT_STATE pad;




	//表示開始していいか
	bool output_;
	//受信まで行った
	bool RecvOK_;

	float movetiemr_;
	void Move();
};

