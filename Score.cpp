#include "Score.h"
namespace Score {

	int Score_;
}


void Score::Reset()
{
	 Score_ = 0;
}

void Score::AddScore(int _score)
{
	Score_ += _score; 
}
void Score::SubScore(int _score)
{

	Score_ -= _score;
}

int Score::GetScore()
{
	return Score_;
}
