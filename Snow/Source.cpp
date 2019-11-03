// ☕ Привет

#include "GameLogic\SnowGame.h"
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
	const auto Move = [&game]()
	{
		while (true)
		{
			game.ClearPlatformOffset();
			char ch = _getch();
			//std::cout << ch << std::endl;
			game.OnKeyPressed(ch);
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	};
	std::thread keyboard_thread(Move);

	while (!game.IsGameOver())
	{
		game.Action();
	}

	keyboard_thread.join();

	std::system("pause");
}