// Timer.cpp: Программа таймер
// Задаём временной период, через который будет подан сигнал
// По окончании периода на экран выводится DING! DING! DING!

#include "Timer.h"
#include <iostream>
#include <ctime>
#include <iomanip>

int main()
{
	std::time_t curTime, dingTime;
	std::tm timeInterval;
	double delta;
	int	minutes, seconds;
	bool ding = false;

	std::cout << "Enter the time interval: ";
	std::cin >> std::get_time(&timeInterval, "%M:%S");
	curTime = std::time(nullptr);
	// Рассчитываем время "звукового сигнала"
	dingTime = curTime + (timeInterval.tm_min * 60) + timeInterval.tm_sec;
	// Рассчитываем разницу между звонком и текущим временем
	delta = (timeInterval.tm_min * 60) + timeInterval.tm_sec;
	while(!ding)
	{	// Если текущее время равно времени сигнала, то сигналим
		if (curTime == dingTime)
		{	// Очищаем консоль
			std::cout << "\x1B[2J\x1B[H";
			// Звеним или звоним
			std::cout << "DING! DING! DING!" << '\n';
			// Данная переменная инициирует выход из цикла и программы
			ding = true;
		}
		else
		{	// Т.к. компьютер будет прокручивать данный цикл
			// Быстрее, чем за одну секунду, то что бы не выводить
			// на экран повторяющуюся информацию проверяем, равна ли delta
			// разнице между текущим временем и временем звонка
			if( delta != difftime(dingTime, curTime) )
			{	// Уменьшаем дельту на 1 секунду
				delta--;
				// Вычисляем оставшиеся минуты и секунды
				minutes = std::trunc(delta / 60);
				seconds = delta - minutes * 60;
				// Очищаем консоль и выводим оставшееся время.
				std::cout << "\x1B[2J\x1B[H";
				printf("You have time: %02d:%02d", minutes, seconds);
			}
		}
		// Считываем текущее время
		curTime = std::time(nullptr);
	}
	std::cout << "Thank you for use my program.\n";
	return 0;
}
