// ☕ Привет

#include "GameLogic\SnowGame.h"
#include "Object\Aim.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

#include <thread>

int main() {

	//for (unsigned char c = 0; c < 255; c++)
	//{
	//	std::cout << (int)c << ' ' << c << std::endl;
	//}

	Shared::ConsoleHelper::Console().SetConsolePositionAndSize(200,200,650, 950);
	const auto size = Shared::ConsoleHelper::Console().Size();
	Snow::GameLogic::SnowGame game({ size.first - 5, size.second - 1});

	//Snow::Object::Aim aim({ 25,5 }, { 25,20 });
	//char ch = 0;
	//do
	//{
	//	ch = _getch();
	//	aim.MoveAim(ch);
	//} while (ch != 27);

	while (!game.IsGameOver())
	{
		game.Action();
	}

	std::system("pause");
}