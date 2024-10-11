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

	bool SetEnd;

	float eraseTime;
	float eraseTimer;
	float flame;
	float eraseAlpha;

	int x1,y1,x2,y2;

	int space = 8;
	int word = 23;
	int  n = x2 + space;
	int a = n;
	int count;
};

