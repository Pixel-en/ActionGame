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

#if 0
namespace RankingsSystem
{
	void SetRankings(std::string _Pname,float _Pscore);
	void SortScore();
	void DrawRankings();
};
#endif

class RankingsSystem : public GameObject
{
public:
	RankingsSystem(GameObject* parent);

	~RankingsSystem();

	void Initialize();

	void Update();

	void Draw();

	void Release();

private:
	std::string output_csv_file_path_ScoreData;
	std::string output_csv_file_path_SortData;
	CsvReader* csv;
	int width;
	int height;
	std::map <std::string, float> Rankings;
	std::vector<std::pair<float, std::string>> r;

	int InputHandle;
	char Name[256];
	std::string PlayerName;
};

