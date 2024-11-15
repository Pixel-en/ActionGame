#include "ResultScene.h"
#include "BackGround.h"

ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), scoreText(nullptr), timeText(nullptr), resultText(nullptr)
{
}

void ResultScene::Initialize()
{
	scoreText = Instantiate<TitleText>(this);
	timeText = Instantiate<TitleText>(this);
	resultText = Instantiate<TitleText>(this);
	ScoreAndTime::Reset(123.0);
	time_ = ScoreAndTime::GetTimer() / (60 * 2);//2•b‚ÅƒXƒRƒA‰ÁŽZ‚ª‚¨‚í‚é
}

void ResultScene::Update()
{
	if (TimeToScoreTimer > 0)
	{
		TimeToScoreTimer -= Time::DeltaTime();
	}
	else if (ScoreAndTime::GetTimer() > 0)
	{
		/*if (ScoreAndTime::GetTimer() - time_ < 0)
		{
			time_ = time_ - ScoreAndTime::GetTimer();
		}*/
		ScoreAndTime::SubTimer(time_);
		a_ += time_;
		while (a_ >= 1.0)
		{
			a_ -= 1.0;
			ScoreAndTime::AddScore(TimeToScoreValue);
		}
	}
}

void ResultScene::Draw()
{
	resultText->DrawString("RESULT", 500, 200, false);

	int spaceNum = 0;
	for (int i = 10000; i >= 10; i /= 10)
	{
		if (i > ScoreAndTime::GetScore())
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
	score = std::to_string(ScoreAndTime::GetScore());
	scoreStr += score;
	scoreText->DrawString(scoreStr, 400, 300, false);


	spaceNum = 0;
	for (int i = 10000; i >= 10; i /= 10)
	{
		if (i > ScoreAndTime::GetTimer())
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
	//int timeInt = ScoreAndTime::GetTimer();
	time = std::to_string(ScoreAndTime::GetTimer());
	timeStr += time;
	timeText->DrawString(timeStr, 400, 400, false);

}

void ResultScene::Release()
{
}
