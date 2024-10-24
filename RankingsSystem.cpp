#include "RankingsSystem.h"
#include"Engine/CsvReader.h"
#include"CleraLogo.h"
#include"TitleText.h"

namespace
{
	struct NData
	{
		float posX1;
		float posY1;
		float posX2;
		float posY2;
		int Ascii;
	};

	NData N[5][5];

}



RankingsSystem::RankingsSystem(GameObject* parent)
	: GameObject(parent, "RankingsSystem"), width(0), height(0), csv(nullptr), cLogo(nullptr), tText(nullptr), InputHandle(0),SetEnd(false),Name()
	,eraseAlpha(0),eraseTime(0),eraseTimer(0),flame(0),x1(0),y1(0),x2(0),y2(0),space(0),word(0),count(0),a(0),n(0),MaxWord(0)
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

	eraseTime = 1.2f;
	eraseTimer = 0.0f;
	flame = 1.0f / 60.0f;
	eraseAlpha = 0;

	x1 = 455;
	y1 = 440;
	x2 = 455;
	y2 = 445;

	r1 = 485;
	l1 = 400; 
	r2 = 520;
	l2 = 435;
	prevKey = false;

	space = 9;
	word = 23;
	count = 0;
	MaxWord = 10;

	// キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
	InputHandle = MakeKeyInput(MaxWord,FALSE,TRUE,FALSE);
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
	if (cLogo->GetOutput()) {
		DrawWriteUICn();
	}
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

void RankingsSystem::DrawWriteUI()
{
	//文字入力バー表示
	if (eraseTimer > eraseTime) {
		eraseTimer = 0.0f;
		eraseAlpha = 0;
	}
	eraseTimer += flame;
	eraseAlpha = 255 - 255 * eraseTimer / eraseTime;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, eraseAlpha);
	std::string str = Name;
	str.size();
	if (str.size() > 0) {
		DrawBoxAA(450 + (word + space) * str.size(), 405, 455 + (word + space) * str.size(), 435, GetColor(255, 255, 255), TRUE);//入力バー
	}
	else {
		DrawBoxAA(450, 405, 455, 435, GetColor(255, 255, 255), TRUE);//入力バー
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//入力可能文字数がわかるボックス表示
	for (int i = 0; i < MaxWord; i++) {
		if (i > 0) {
			n = a + space;
			DrawBoxAA(n, y1, n + word, y2, GetColor(255, 255, 255), TRUE); //した棒
			a = n + word;
		}
		else
		{
			DrawBoxAA(x1, y1, x2 + word, y2, GetColor(255, 255, 255), TRUE); //した棒
			a = x2 + word;
		}
	}

	DrawBoxAA(430, 380,(x1+25) + MaxWord*word +( MaxWord-1 )* space, 450, GetColor(255, 255, 255), FALSE); //入力枠線
	tText->DrawString(Name, 450, 400);
}

void RankingsSystem::DrawWriteUICn()
{
	static int i = 65;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 6; x++) {
			if (x > 4) {
				NameIn[y][x] = NULL;
			}
			else {
				NameIn[y][x] = i;
				i++;
			}
		}
	}
	int count = 0;
	int l = 0;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 6; x++) {
			char b = static_cast<char>(NameIn[y][x]);
			std::string str(1, b);
			tText->DrawString(str, (450, +35 * x), 400 + (35 * y));
		}
	}
	/*for (int i = 65; i < 91; i++) {
		count++;
		char b = static_cast<char>(i);
		std::string str(1, b);
		if (count > 5) {
			l++;
			count = 1;
		}
		tText->DrawString(str,(450 + 35 * count), 400 +(35 * l));
	}*/
	if (CheckHitKey(KEY_INPUT_UP)) {
		if (prevKey == false) {
			l1 -= 35;
			l2 -= 35;
		}
		prevKey = true;
	} else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if(prevKey == false) {
			r1 += 35;
			r2 += 35;
		}
		prevKey = true;
	} else if (CheckHitKey(KEY_INPUT_DOWN)) {
		
		if (prevKey == false) {
			l1 += 35;
			l2 += 35;
		}
		prevKey = true;
	} else if (CheckHitKey(KEY_INPUT_LEFT)) {
		
		if (prevKey == false) {
		    r1 -= 35;
			r2 -= 35;
		}
		prevKey = true;
	}
	else {
		prevKey = false;
	}
	DrawBoxAA(r1, l1, r2,l2, GetColor(255, 255, 255), FALSE);

	
}
