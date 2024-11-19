#include "ResultScene.h"
#include "BackGround.h"

ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), scoreText(nullptr), timeText(nullptr), resultText(nullptr)
{
}

void ResultScene::Initialize()
{
	scoreText = Instantiate<OutText>(this);
	timeText = Instantiate<OutText>(this);
	resultText = Instantiate<OutText>(this);
	ScoreAndTimeAndMap::Reset(123.0);
	time_ = ScoreAndTimeAndMap::GetTimer() / (60 * 2);//2•b‚ÅƒXƒRƒA‰ÁŽZ‚ª‚¨‚í‚é
}

void ResultScene::Update()
{
	if (TimeToScoreTimer > 0)
	{
		TimeToScoreTimer -= Time::DeltaTime();
	}
	else if (ScoreAndTimeAndMap::GetTimer() > 0)
	{
		if (ScoreAndTime::GetTimer() < time_)
		{
			time_ = ScoreAndTime::GetTimer();
			a_ = 1.0;
		}
		ScoreAndTime::SubTimer(time_);
		a_ += time_;
		while (a_ >= 1.0)
		{
			a_ -= 1.0;
			ScoreAndTimeAndMap::AddScore(TimeToScoreValue);
		}
	}
}

void ResultScene::Draw()
{
	resultText->DrawString("RESULT", 500, 200, false);

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
	scoreText->DrawString(scoreStr, 400, 300, false);


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
	int timeInt = ScoreAndTime::GetTimer();
	time = std::to_string(timeInt);
	timeStr += time;
	timeText->DrawString(timeStr, 400, 400, false);

}

void ResultScene::Release()
{
}
