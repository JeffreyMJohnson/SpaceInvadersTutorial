#include "HighScores.h"

//comparison, not case sensitive
bool compare_descending(const int& first, const int& second)
{
	return (first > second);
}

Highscores::Highscores()
{

}

Highscores::~Highscores()
{
}

void Highscores::LoadScores()
{
	std::fstream fs;
	//load file if exists, otherwise create file and then open for write
	fs.open("leaderboard.txt", std::fstream::in);
	if (fs.is_open())
	{
		//read until end of file bit is true
		while (!fs.eof())
		{
			int score = 0;
			fs >> score;
			//was an int read in?
			if (fs.good())
			{
				scores.push_back(score);
			}
		}
		fs.close();
	}
}

void Highscores::SaveScores()
{
	std::fstream fs;
	//open file for writing and to overwrite existing data
	fs.open("leaderboard.txt", std::fstream::out | std::fstream::trunc);
	if (fs.is_open())
	{
		int counter = 0;
		for (std::list<int>::iterator it = scores.begin(); it != scores.end(); it++)
		{
			fs << *it << std::endl;
			counter++;
			if (counter >= 5)
				break;
		}
		fs.close();
	}
}

void Highscores::AddScore(int score)
{
	scores.push_back(score);
}

void Highscores::SortScores()
{
	scores.sort(compare_descending);
}

bool Highscores::IsEmpty()
{
	return (scores.size() == 0);
}

const std::list<int> Highscores::GetScores()
{
	return scores;
}

