#include "ScoreAndTime.h"
namespace ScoreAndTime {

	int Score_;
	float Timer_;
}


void ScoreAndTime::Reset()
{
	 Score_ = 0;
}

void ScoreAndTime::AddScore(int _score)
{
	Score_ += _score; 
}
void ScoreAndTime::SubScore(int _score)
{

	Score_ -= _score;
}

int ScoreAndTime::GetScore()
{
	return Score_;
}
