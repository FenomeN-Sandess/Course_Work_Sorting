#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "classes.h"
#include <SFML/Graphics.hpp>



int main()
{
	menu Menu; /*Объект менюшки*/
	while (true) 
	{
		Menu.start(); /*Запуск меню*/
		Menu.choice(); /*Выбор действия в меню*/
	}
}
