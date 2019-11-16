// ☕ Привет

#include "GameLogic\SnowGame.h"
#include "Object\Aim.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

#include <thread>

int main() 
{
	//srand(time(0));
	//for (unsigned char c = 0; c < 255; c++)
	//{
	//	std::cout << (int)c << ' ' << c << std::endl;
	//}

	Shared::ConsoleHelper::Console().SetConsolePositionAndSize(200,200,650, 950);
	const auto size = Shared::ConsoleHelper::Console().Size();
	Snow::GameLogic::SnowGame game({ size.first - 5, size.second - 1});

	const auto Keyboard = [&game]()
	{
		char ch = 0;
		do
		{
			ch = _getch();
		} while (ch != 27);
		game.Stop();
	};

	std::thread keyboard_thread(Keyboard);

	while (!game.IsGameOver())
	{
		game.Action();
	}

	keyboard_thread.join();

	std::system("pause");
}