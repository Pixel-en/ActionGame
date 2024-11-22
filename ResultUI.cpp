#include "ResultUI.h"
#include "ScoreAndTimeAndMap.h"
#include "Engine/CsvReader.h"


namespace {
	const int TIMETOSCORE{ 5 };
	const XMFLOAT3 ORIGINPOS{ 500,200,0 };
	int spaceNum = 0;
	const float MOVETIME{ 1.0f };
	Transform trans;
	
	//順位、名前スコア
	std::pair<std::string, std::string> ranking[5];
	bool outranking = false;
	bool check = false;
}

void ResultUI::CSVReadRank() {
	CsvReader* csv = new CsvReader("Assets\\Rankings\\RecvRankingsSortDat.csv");
	ranking[0].first = csv->GetString(1, 0);
	ranking[0].second = csv->GetString(1, 1) + " " + csv->GetString(1, 2);
	if (ranking[0].first == "-1") {
		return;
	}
	for (int i = 0; i < 5; i++) {
		ranking[i].first = csv->GetString(i, 0);
		ranking[i].second = csv->GetString(i, 1);
		//for (int j = 0; j <10-ranking[i].second.size(); j++)
		//	ranking[i].second += " ";

		ranking[i].second += " ";
		ranking[i].second += csv->GetString(i, 2);
	}
}

void ResultUI::DrawRank()
{

	if (ranking[0].first == "-1") {
		text_->DrawString(ranking[0].second, trans.position_.x + 2150, trans.position_.y + 350);
		return;
	}

	for (int i = 0; i < 5; i++) {
		std::string space;
		int max = std::stoi(ranking[i].first);
		for (int i = 0; i < DrawSpace(max); i++)
			space += " ";
		text_->DrawString(space + ranking[i].first + " " + ranking[i].second, trans.position_.x + 2050, trans.position_.y + 350 + (i * 40));
	}
}

int ResultUI::DrawSpace(float max)
{
	int sum = 0;

	for (int i = 10000; i >= 10; i /= 10)
	{
		if (i > max)
		{
			sum++;
		}
	}

	return sum;
}

ResultUI::ResultUI(GameObject* parent)
	:GameObject(parent,"ResultUI"), text_(nullptr),moveflag_(false),isrank_(false)
{
}

ResultUI::~ResultUI()
{
}

void ResultUI::Initialize()
{
	time_ = ScoreAndTimeAndMap::GetTimer() / (60 * 2);//2秒でスコア加算がおわる
	transform_.position_ = ORIGINPOS;
	trans.position_ = { 0,0,0 };
	hImage_ = LoadGraph("Assets\\Image\\TestImage\\Test.png");
	text_ = Instantiate<OutText>(GetParent());
}

void ResultUI::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &pad);

	if (TimeToScoreTimer > 0)
	{
		TimeToScoreTimer -= Time::DeltaTime();
	}
	else
	{
		if (ScoreAndTimeAndMap::GetTimer() > 0.0) {
			ScoreAndTimeAndMap::SubTimer(time_);
			oneSecond_ += time_;
			//1秒分たまったら
			while (oneSecond_ >= 1.0)
			{
				oneSecond_ -= 1.0;
				ScoreAndTimeAndMap::AddScore(TIMETOSCORE);
			}
		}
		else {
			ScoreAndTimeAndMap::SetTimer(0.0f);
			if (!moveflag_) {
				moveflag_ = true;
				movetimer_ = MOVETIME;
			}
		}
	}

	if (moveflag_) {
		if (movetimer_ > 0)
			movetimer_ -= Time::DeltaTime();
		else {
			if (transform_.position_.x > -1000)
				transform_.position_.x -= 400 * Time::DeltaTime();
			else {
				if (!isrank_) {
					transform_.position_.x = -1000;
					isrank_ = true;
				}
			}
			movetimer_ = -1.0;
		}
	}
	if (recvmove_&&!check) {
		trans.position_.x -= 400 * Time::DeltaTime();
		
		if (trans.position_.x < -1800) {
			CSVReadRank();
			check = true;
		}
	}
}

void ResultUI::Draw()
{
	text_->DrawString("result", transform_.position_.x, transform_.position_.y, true);

	//合計スコア表示
	std::string scoreStr = "SCORE   ";
	std::string score;
	for (int i = 0; i < DrawSpace(ScoreAndTimeAndMap::GetScore()); i++)
	{
		scoreStr += " ";
	}
	score = std::to_string(ScoreAndTimeAndMap::GetScore());
	scoreStr += score;
	text_->DrawString(scoreStr, transform_.position_.x-100, transform_.position_.y + 100, true);

	//残り時間表示
	std::string timeStr = "TIME    ";
	std::string time;
	for (int i = 0; i < DrawSpace(ScoreAndTimeAndMap::GetTimer()); i++)
	{
		timeStr += " ";
	}
	time = std::to_string(ScoreAndTimeAndMap::GetTimer());
	timeStr += time;
	text_->DrawString(timeStr, transform_.position_.x - 100, transform_.position_.y + 200, true);

	text_->DrawString("ranking",transform_.position_.x+1500, transform_.position_.y, true);

	if (isrank_) {
		text_->DrawString("Write Down ↓ Your Name", trans.position_.x + 200, +trans.position_.y + 300);
		DrawGraph(trans.position_.x + 2050, trans.position_.y+300, hImage_, true);
		if (check) {
			DrawRank();
		}
	}
	
}

void ResultUI::Release()
{
}
