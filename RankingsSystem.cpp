#include "RankingsSystem.h"
#include"Engine/CsvReader.h"
#include"CleraLogo.h"
#include"TitleText.h"

RankingsSystem::RankingsSystem(GameObject* parent)
	: GameObject(parent, "RankingsSystem"), width(0), height(0), csv(nullptr), cLogo(nullptr), tText(nullptr), InputHandle(0),SetEnd(false),Name()
{
	
}

RankingsSystem::~RankingsSystem()
{
}

void RankingsSystem::Initialize()
{
	output_csv_file_path_ScoreData = "Assets\\Rankings\\RankingsSystem.csv";
	output_csv_file_path_SortData = "Assets\\Rankings\\RankingsSystemClearSort.csv";
	csv = new CsvReader(output_csv_file_path_ScoreData);
	width = csv->GetColumns(0);
	height = csv->GetLines();

	SetEnd = false;

	cLogo = Instantiate<ClearLogo>(this);
	tText = Instantiate<TitleText>(this);

	// キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
	InputHandle = MakeKeyInput(10,FALSE,TRUE,FALSE);
}

void RankingsSystem::Update()
{
	if (cLogo->GetOutput()) {
		// 入力が終了している場合は終了
		if (CheckKeyInput(InputHandle) != 0) {
			if (!SetEnd) {
				SetRankings(Name, 500);

				SetEnd = true;
				SortScore();
			}
		}
		// 作成したキー入力ハンドルをアクティブにする
		SetActiveKeyInput(InputHandle);

		//入力モードを描画
		DrawKeyInputModeString(640, 480);

		// 入力途中の文字列を描画
		DrawKeyInputString(0, 0, InputHandle);

		// 入力された文字列を取得
		GetKeyInputString(Name, InputHandle);

	}
}

void RankingsSystem::Draw()
{
	DrawBoxAA(0,0,30,10, GetColor(255, 255, 255), TRUE);
	tText->DrawString(Name, 450, 400);
   /* DrawString(450,400, Name, GetColor(255, 255, 255));*/
	SetFontSize(50);
}

void RankingsSystem::Release()
{
}

void RankingsSystem::SetRankings(std::string _Pname, float _Pscore)
{
	std::ofstream ofs_csv_file(output_csv_file_path_ScoreData, std::ios::app);
	ofs_csv_file << _Pname << "," << _Pscore;
	ofs_csv_file << std::endl;
	ofs_csv_file.close();
}

void RankingsSystem::SortScore()
{
	csv = new CsvReader(output_csv_file_path_ScoreData);
	height = csv->GetLines();
	if (height > 1) {
		for (int h = 1; h < height; h++) {
			Rankings.insert(std::pair<std::string, float>(csv->GetString(h, 0), csv->GetFloat(h, 1)));
		}

		for (std::map<std::string, float>::iterator it = Rankings.begin(); it != Rankings.end(); it++) {
			r.push_back({ it->second, it->first });
		}

		sort(r.rbegin(), r.rend());
	}

	std::ofstream ofs_csv_file(output_csv_file_path_SortData);
	ofs_csv_file << "PlayerName" << "," << "PlayerScore";
	ofs_csv_file << std::endl;
	for (auto itr = r.begin(); itr != r.end(); ++itr) {
		ofs_csv_file << itr->second << "," << itr->first;
		ofs_csv_file << std::endl;
		ofs_csv_file.close();
	}
}