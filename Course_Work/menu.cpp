
/// Файл с определениями функций класса menu

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "classes.h"



void menu::start()
{

	std::cout << "Would you like to start a menu? enter y/n\n>>";
	std::string y_n;
	std::cin >> y_n;
	this->State = (y_n == "Y") or (y_n == "y") ? true : false;
}

void menu::end()
{

	std::cout << "Would you like to turn off the menu? enter y/n\n>>";
	std::string y_n;
	std::cin >> y_n;
	this->State = (y_n == "Y") or (y_n == "y") ? false : true;
}

void menu::choice()
{
	while (this->State) {
		int CHOICE;
		std::cout << "Choose action from list:\n1.Generate\n2.Calculate\n3.Save\n4.Download\n5.Display the table\n6.Display a plot\n7.Quit\n";
		std::cin >> CHOICE;
		switch (CHOICE)
		{
		case 1:
			Func.generate();
			// Создание массива и его заполнение рандомными числами до 5000
			break;
		case 2:
			Func.sorting();
			// Выполнение сортировок и сохранение времени их выполнения
			break;
		case 3:
			Func.saving();
			// Сохранение полученных массивов в файл
			break;
		case 4:
			Func.downloading();
			// Загрузка массивов из файла
			break;
		case 5:
			Func.show();
			// Вывод таблицы по данным из массивов на экран + график
			break;
		case 6:
			Func.display();
			// Вывод графика по данным из массивов.
			break;
		case 7:
			end(); // Выход из меню
			break;
		default:
			std::cout << "Please, choose action from list." << std::endl;
			break;
		}
	}
	}



