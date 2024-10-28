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
class ClearLogo;
class TitleText;

class RankingsSystem : public GameObject
{
public:
	RankingsSystem(GameObject* parent);

	~RankingsSystem();

	void Initialize();

	void Update();

	void Draw();

	void Release();

	/// <summary>
	/// ランキングのに必要なデータをcsvに挿入
	/// </summary>
	void SetRankings(std::string _name, float _score);

	/// <summary>
	/// csvに保存されたデータをソート
	/// </summary>
	void SortScore();

	void DrawWriteUI();

	void DrawWriteUICn();

private:
	std::string output_csv_file_path_ScoreData;
	std::string output_csv_file_path_SortData;
	CsvReader* csv;
	int width;
	int height;
	std::map <std::string, float> Rankings;
	std::vector<std::pair<float, std::string>> r;

	ClearLogo* cLogo;
	TitleText* tText;

	int InputHandle;
	char Name[256];
	char cName[256];
	std::string str;

	bool SetEnd;

	float eraseTime;
	float eraseTimer;
	float flame;
	float eraseAlpha;

	int x1,y1,x2,y2;

	int space;
	int word;
	int n;
	int a;
	int count;
	int MaxWord;

	int r1, l1, r2, l2;
	bool prevKey;

	enum DEVICE
	{
		KEY_AND_MOUSE = 0,
		PAD
	};

	int nowDevice;
};

