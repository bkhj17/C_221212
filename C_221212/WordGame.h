#pragma once
#include "Base.h"
#include "UsefulType.h"

class CWordGame : public Base
{
	static const int SIZE = 128;
	static const int MAX_WORD_NUMBER = 30;
	static const int MAX_LEVEL = 5;
	static const int INPUT_TIME = 5;
	static const char* FILE_NAME;
	
	uint wordCount = 0;
	char words[MAX_WORD_NUMBER][SIZE];

	int numQuestion = 0;


	enum class GameState {
		SETTING,
		PRINT,
		CHECK,
	};
	GameState gameState = GameState::SETTING;


	void Dictionary();
	void WordGame();
	void SaveWord();
	void ShowWords();
	void LoadWord();

	bool IsSameWord(const char* str1, const char* str2);
	bool IsIncludeWords(const char* str);
	void PrintWordGame(const uint& level, char (*questionWords)[SIZE]);
	void MakeQuestionWords(const uint& level, char (*questionWords)[SIZE]);

	bool InputWord(const uint& level, char(*questionWord)[SIZE]);
public:
	// Base을(를) 통해 상속됨
	virtual void Run() override;
};

