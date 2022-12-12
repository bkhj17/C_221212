#include "WordGame.h"
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>

const char* CWordGame::FILE_NAME = "Dictionary.txt";

void CWordGame::Dictionary()
{
	int menuNum = 0;
	while (1) {
		printf("1. 단어등록, 2. 단어보기, 3. 나가기");
		scanf_s("%d", &menuNum);

		switch (menuNum)
		{
		case 1:
			SaveWord();
			break;
		case 2:
			ShowWords();
			break;
		case 3:
			return;
		}
	}
}

void CWordGame::WordGame()
{
	uint level = 1;
	time_t startTime = 0, lastTime = 0, curTime = 0;
	char questionWords[MAX_LEVEL][SIZE];

	while (1) {
		curTime = time(0);
		if (lastTime != curTime) {
			system("cls");
			printf("Time : %lld", curTime - startTime);
			lastTime = curTime;
		}

		switch (gameState)
		{
		case CWordGame::GameState::SETTING:
			startTime = time(0);
			MakeQuestionWords(level, questionWords); 
			gameState = GameState::PRINT;
			break;
		case CWordGame::GameState::PRINT:
			PrintWordGame(level, questionWords);
			gameState = GameState::CHECK;
			break;
		case CWordGame::GameState::CHECK:
			if (InputWord(level, questionWords)) {
				level++;
				gameState = GameState::SETTING;
			}
			else {
				gameState = GameState::PRINT;
			}
			break;
		default:
			
			break;
		}
	}
}

void CWordGame::SaveWord()
{
	printf("등록할 단어를 입력하시오.\n");
	scanf_s("%s", words[wordCount], SIZE);

	if (IsIncludeWords(words[wordCount])) {
		printf("%s는 이미 등록된 단어입니다.\n", words[wordCount]);
		return;
	}
	wordCount++;

	FILE* file = NULL;
	fopen_s(&file, FILE_NAME, "w");
	if (file != NULL) {
		fprintf(file, "%d\n", wordCount);

		for(uint i = 0; i < wordCount; i++)
			fprintf(file, "%s\n", words[i]);
		fclose(file);
	}
}

void CWordGame::ShowWords()
{
	LoadWord();
	printf("등록된 단어 %d개\n", wordCount);
	for (uint i = 0; i < wordCount; i++) {
		printf("%s\n", words[i]);
	}
}

void CWordGame::LoadWord()
{
	FILE* file = NULL;
	fopen_s(&file, FILE_NAME, "r");

	if (file != NULL) {
		fscanf_s(file, "%d", &wordCount);
		for (uint i = 0; i < wordCount; i++)
			fscanf_s(file, "%s", words[i], SIZE);
		fclose(file);
	}
}

bool CWordGame::IsSameWord(const char* str1, const char* str2)
{

	size_t str1length = strlen(str1), str2length = strlen(str2);

	if (str1length != str2length)
		return false;

	for(int i = 0; i < str1length; i++)
		if(str1[i] != str2[i])
			return false;

	return true;
}

bool CWordGame::IsIncludeWords(const char* str)
{
	for (uint i = 0; i < wordCount; i++) {
		if (IsSameWord(words[i], str)) {
			return true;
		}
	}

	return false;
}

void CWordGame::PrintWordGame(const uint& level, char(*questionWords)[SIZE])
{
	printf("--------------WordGame---------------\nLevel : %d\n", level);
	for (uint i = 0; i < level; i++) {
		printf("%d. %s ", i + 1, questionWords[i]);
	}
	printf("\n");
}

void CWordGame::MakeQuestionWords(const uint& level, char(*questionWords)[SIZE])
{
	for (uint i = 0; i < level; i++) {
		int randomNum = rand() % wordCount;
		strcpy_s(questionWords[i], SIZE, words[randomNum]);
	}
}

bool CWordGame::InputWord(const uint& level, char(*questionWord)[SIZE])
{
	char inputWord[SIZE] = "";
	scanf_s("%s", inputWord, SIZE);
	int checkCount = 0;
	for (int i = 0; i < level; i++) {
		if (IsSameWord(questionWord[i], inputWord)) {
			strcpy_s(questionWord[i], SIZE, "");
			break;
		}
	}

	for(int i = 0; i < level; i++)
		if (strlen(questionWord[i]) == 0)
			checkCount++;

	if (checkCount == level)
		return true;

	return false;
}

void CWordGame::Run()
{
	int menuNum = 0;
	LoadWord();
	while (1) {
		printf("1.단어도감, 2. 게임, 3. 종료");
		scanf_s("%d", &menuNum);

		switch (menuNum)
		{
		case 1:
			Dictionary();
			break;
		case 2:
			WordGame();
			break;
		case 3:
			return;
		}
	}
}
