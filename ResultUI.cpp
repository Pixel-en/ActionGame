#include "ResultUI.h"
#include "ScoreAndTimeAndMap.h"

namespace {
	const int TIMETOSCORE{ 10 };
}

ResultUI::ResultUI(GameObject* parent)
	:GameObject(parent,"ResultUI"), text_(nullptr)
{
}

ResultUI::~ResultUI()
{
}

void ResultUI::Initialize()
{
	text_ = Instantiate<OutText>(GetParent());
	time_ = ScoreAndTimeAndMap::GetTimer() / (60 * 2);//2•b‚ÅƒXƒRƒA‰ÁŽZ‚ª‚¨‚í‚é
}

void ResultUI::Update()
{
	if (TimeToScoreTimer > 0)
	{
		TimeToScoreTimer -= Time::DeltaTime();
	}
	else
	{
		if (ScoreAndTimeAndMap::GetTimer() > 0.0) {
			ScoreAndTimeAndMap::SubTimer(time_);
			oneSecond_ += time_;
			//1•b•ª‚½‚Ü‚Á‚½‚ç
			if (oneSecond_ >= 1.0)
			{
				oneSecond_ = 0.0f;
				ScoreAndTimeAndMap::AddScore(TIMETOSCORE);
			}
		}
		else
			ScoreAndTimeAndMap::SetTimer(0.0f);
	}
}

void ResultUI::Draw()
{
	text_->DrawString("result", 500, 200, true);

	int spaceNum = 0;
	for (int i = 10000; i >= 10; i /= 10)
	{
		if (i > ScoreAndTimeAndMap::GetScore())
		{
			spaceNum++;
		}
	}

	std::string scoreStr = "SCORE   ";
	std::string score;
	for (int i = 0; i < spaceNum; i++)
	{
		scoreStr += " ";
	}
	score = std::to_string(ScoreAndTimeAndMap::GetScore());
	scoreStr += score;
	text_->DrawString(scoreStr, 400, 300, true);


	spaceNum = 0;
	for (int i = 10000; i >= 10; i /= 10)
	{
		if (i > ScoreAndTimeAndMap::GetTimer())
		{
			spaceNum++;
		}
	}

	std::string timeStr = "TIME    ";
	std::string time;
	for (int i = 0; i < spaceNum; i++)
	{
		timeStr += " ";
	}
	//int timeInt = ScoreAndTimeAndMap::GetTimer();
	time = std::to_string(ScoreAndTimeAndMap::GetTimer());
	timeStr += time;
	text_->DrawString(timeStr, 400, 400, true);

}

void ResultUI::Release()
{
}
