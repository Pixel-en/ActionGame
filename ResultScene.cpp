#include "ResultScene.h"
#include "BackGround.h"

ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), scoreText(nullptr), timeText(nullptr)
{
}

void ResultScene::Initialize()
{
	Instantiate<BackGround>(this);

	scoreText = Instantiate<TitleText>(this);
	timeText = Instantiate<TitleText>(this);
	ScoreAndTime::Reset(60.0);
	time_ = ScoreAndTime::GetTime() / (60 * 2);//2•b‚ÅƒXƒRƒA‰ÁŽZ‚ª‚¨‚í‚é
}

void ResultScene::Update()
{
	if (TimeToScoreTimer > 0)
	{
		TimeToScoreTimer -= Time::DeltaTime();
	}
	else
	{
		if (a_ >= 1.0)
		{
			a_ -= 1.0;
			ScoreAndTime::AddScore(100);
		}
		ScoreAndTime::SubTime(time_);
		a_ += time_;
	}
}

void ResultScene::Draw()
{
	std::string scoreStr = "SCORE : ";
	std::string score;
	score = std::to_string(ScoreAndTime::GetScore());
	scoreStr += score;
	scoreText->DrawString(scoreStr, 400, 300);

	std::string timeStr = "SCORE : ";
	std::string time;
	time = std::to_string(ScoreAndTime::GetTime());
	timeStr += time;
	timeText->DrawString(timeStr, 400, 400);

}

void ResultScene::Release()
{
}
