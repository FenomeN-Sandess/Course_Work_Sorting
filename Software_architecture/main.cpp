#include "menu.h"
#include "graph_menu.h"
#include "functions.h"



int main()
{
	
	bool restart = false;
	functions Func; // объект класса functions
	menu Menu(&Func); /*Объект менюшки*/
	graph_menu cl(&Func); // Оконное приложение меню

	while (true) 
	{

		std::cout << "Please select the program version\n1. Console application\n2. Window application\n>>";
		int choice;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			Menu.start(); /*Запуск меню*/
			Menu.choice();
			break;
		case 2:
			restart = cl.window(); // Запуск графического меню с доступом к функционалу программы
			while (restart) {
				restart = cl.window();
			}
			break;
		default:
			std::cout << "Please, choose action from list" << std::endl;
			break;
		}		

		Menu.choice(); /*Выбор действия в меню*/
	}
	
	return 0;
}
