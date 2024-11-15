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
	Score::Reset(60.0);
	time_ = Score::GetTime() / (60 * 2);//2•b‚ÅƒXƒRƒA‰ÁŽZ‚ª‚¨‚í‚é
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
			Score::AddScore(100);
		}
		Score::SubTime(time_);
		a_ += time_;
	}
}

void ResultScene::Draw()
{
	std::string scoreStr = "SCORE : ";
	std::string score;
	score = std::to_string(Score::GetScore());
	scoreStr += score;
	scoreText->DrawString(scoreStr, 400, 300);

	std::string timeStr = "SCORE : ";
	std::string time;
	time = std::to_string(Score::GetTime());
	timeStr += time;
	timeText->DrawString(timeStr, 400, 400);

}

void ResultScene::Release()
{
}
