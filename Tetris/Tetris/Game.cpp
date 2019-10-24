#include "Game.h"
#include "GameData.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <Windows.h>
#include "Vector2D.h"
#include <wchar.h>
#include "Tetromino.h"


Game::Game()
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	SetFontSize(gameData::TEXT_WIDTH, gameData::TEXT_HEIGHT);
	SetWindowSize(gameData::SCREEN_WIDTH, gameData::SCREEN_HEIGHT);

	myWindowHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	InitializeBuffer();
	Board board{ 20,30,(int)(gameData::SCREEN_WIDTH / 2),(int)(gameData::SCREEN_HEIGHT / 2), this };
	myBoard = &board;

	Run();
}

Game::~Game()
{
}

void Game::Run() {
	while (true) {
		auto start = std::chrono::system_clock::now();

		if (myCurrentTetromino == NULL) {
			Vector2D temp[4];
			std::srand(time(NULL));
			int random = std::rand() % 7;
			ConvertShapeToPosition(shapes[random], temp);
			Tetromino* tetromino{ new Tetromino{ this, std::vector<Vector2D>(temp,temp + sizeof temp / sizeof temp[0]) } };
			random = 0;
			myCurrentTetromino = tetromino;
		}
		else { //wtf wtf wtf inget händer mellan.
			myCurrentTetromino->Update();
			ClearBuffer();
			myCurrentTetromino->Draw();
			myBoard->Draw();
			DrawBuffer();
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = end - start;
			myDeltaTime = (elapsedTime.count());
		}
		
	}
}

bool Game::Timer(const float& someMaxTime, float& someCurrentTime) {
	someCurrentTime += myDeltaTime;
	if (someCurrentTime > someMaxTime) {
		someCurrentTime = 0;
		return true;
	}
	return false;
}

void Game::SetWindowSize(const int& aWidth, const int& aHeight) {
	COORD bufferSize;
	bufferSize.X = aWidth;
	bufferSize.Y = aHeight;

	SMALL_RECT windowRectangle;
	windowRectangle.Top = windowRectangle.Left = 0;
	windowRectangle.Bottom = aHeight - 1;
	windowRectangle.Right = aWidth - 1;

	HANDLE handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
	SetConsoleScreenBufferSize(handle, bufferSize);
	SetConsoleWindowInfo(handle, TRUE, &windowRectangle);
}

void Game::SetFontSize(const int& aWidth, const int& aHeight)
{
	CONSOLE_FONT_INFOEX consoleFontInfo;
	consoleFontInfo.cbSize = sizeof(consoleFontInfo);
	consoleFontInfo.dwFontSize.X = aWidth;
	consoleFontInfo.dwFontSize.Y = aHeight;
	consoleFontInfo.FontFamily = FF_DONTCARE;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &consoleFontInfo);
}

void Game::InitializeBuffer()
{
	COORD bufferSize{ gameData::SCREEN_WIDTH, gameData::SCREEN_HEIGHT };
	COORD bufferCoordinates{ 0, 0 };
	SMALL_RECT consoleRegion{ 0, 0, gameData::SCREEN_WIDTH - 1, gameData::SCREEN_HEIGHT - 1 };
	ReadConsoleOutput(myWindowHandle, reinterpret_cast<CHAR_INFO*>(myBuffer), bufferSize, bufferCoordinates, &consoleRegion);
}

void Game::ClearBuffer()
{
	for (int y{ 0 }; y < gameData::SCREEN_HEIGHT; ++y)
	{
		for (int x{ 0 }; x < gameData::SCREEN_WIDTH; ++x)
		{
			myBuffer[y][x].Attributes = 0;
			myBuffer[y][x].Char.AsciiChar = ' ';
		}
	}
}

void Game::SetCharacter(const Vector2D& aPosition, const wchar_t& aCharacter, const gameData::Color& aColor)
{
	int x{ aPosition.GetX() }, y{ aPosition.GetY() };
	if (x < 0 || x >= gameData::SCREEN_WIDTH || y < 0 || y >= gameData::SCREEN_HEIGHT)
	{
		return;
	}
	CHAR_INFO& character{ myBuffer[y][x] };
	character.Char.UnicodeChar = aCharacter;
	character.Attributes = static_cast<int>(aColor);
}

bool Game::PositionIsTaken(const Vector2D& aPosition) {
	CHAR_INFO& character{ myBuffer[aPosition.GetY()][aPosition.GetX()] };
	if (character.Char.AsciiChar != ' ') {
		return true;
	}
	return false;
}

float Game::GetDeltaTime() {
	return myDeltaTime;
}

void Game::DrawBuffer() {
	COORD bufferSize{ gameData::SCREEN_WIDTH, gameData::SCREEN_HEIGHT };
	COORD bufferCoordinates{ 0, 0 };
	SMALL_RECT consoleRegion{ 0, 0, gameData::SCREEN_WIDTH - 1, gameData::SCREEN_HEIGHT - 1 };
	WriteConsoleOutputW(myWindowHandle, reinterpret_cast<CHAR_INFO*>(myBuffer), bufferSize, bufferCoordinates, &consoleRegion);
}

void Game::ConvertShapeToPosition(const int(&aShape)[16], Vector2D (&anOutputArray)[4]) {
	Vector2D index;
	int times = 0;
	for (int i = 0; i < 16; i++)
	{
		if (aShape[i] == 1) {		
			anOutputArray[times] = Vector2D(index.GetX(), index.GetY());
			times++;
		}

		if (index.GetX() == 3) {
			index += Vector2D(0, 1);
			index.SetX(0);
		}
		else
		{
			index += Vector2D(1, 0);
		}
	}
}

