#pragma once
#include "functions.h"


class menu { /* Главный класс менюшки, содержит самые основные поля */
private: 
	functions* Func;
	bool State = false;
public:
	menu(functions* f) : Func(f) {}
	void start();																				/*Запуск работы меню*/
	void end();																					/*Завершение работы меню*/
	void choice();	 																			/*Запуск графического меню */

	menu() = default;
};
