
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <functional> 
#include "menu_control.h"


#pragma once
void bubble_sorting(std::vector <double> vector); /* Пузырьковая сортировка */
void pyramid_sorting(std::vector <double> vector); /* Пирамидальная сортировка*/


class menu { /* Главный класс меню */
private: 
	bool State = false;
	menu_control cl;
protected:
	class functions { /* Класс для работы с функциями */
	protected:
		std::vector<std::vector<double>> bubble_time;											// Создание вектора bubble_time
		std::vector<std::vector<double>> pyramid_time;										    // Создание вектора pyramid_time
		std::fstream file;																		// Объект класса для чтения и записи данных из файла и в файл
		int C = 1000;																			//Константа (размер массива вектора)
		std::vector <double> vect;																/* Динамический массив с числами double */
		std::vector <double> trial_vect;														/* Срезанный массив */
		std::string path_to_file = "Results_of_sortings.txt";								    //Путь к файлу
		std::vector <int> diff_par = { 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 }; // Массив с набором параметров сложности

		/*Второстепенные функции, используемые для основных функций*/
		void print_table(const std::vector<std::vector<double>>& data);
		void save_time(void view_sorting(std::vector <double> vector), std::vector<std::vector<double>>& view_time, int n);
	public:
		functions() : bubble_time(2, std::vector<double>(11, 0.0)), pyramid_time(2, std::vector<double>(11, 0.0)) {}

		void generate();																		/*Генерация массива*/
		void sorting();																			/*Выполнить сортировку и сохранить время в массив*/
		void saving();																			/* Сохранение данных в файл*/
		void downloading();																		/* Чтение данных из файла*/
		void show();																			/* Показать данные*/
		void display();																			/* Отобразить график */
	};

	functions Func; // объект класса functions в области видимости класса menu

public:
	void start();																				/*Запуск работы меню*/
	void end();																				    /*Завершение работы меню*/
	void choice();																				/*Выбор действия*/

	menu() = default;
};

