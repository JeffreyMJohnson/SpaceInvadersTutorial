#pragma once
#ifndef _HIGHSCORES_H_
#define _HIGHSCORES_H_
#include <list>
#include <fstream>

class Highscores
{
public:
	Highscores();
	~Highscores();

	void LoadScores();
	void SaveScores();
	void AddScore(int score);
	void SortScores();
	bool IsEmpty();
	const std::list<int> GetScores();

private:
	std::list<int> scores;
};

#endif //_HIGHSCORES_H_