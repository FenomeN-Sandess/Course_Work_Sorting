
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <functional> 

#pragma once

class menu { /* Главный класс меню */
private: 

	bool State = false;

protected:

	/* Класс для работы с функциями */
	class functions { 
	protected:
		//Класс с методами сортировок
		class sorting { 
		public:
			void bubble_sorting(std::vector <double> vector); /* Пузырьковая сортировка */
			void pyramid_sorting(std::vector <double> vector); /* Пирамидальная сортировка*/
		};

		// Класс, содержащий данные двухмерных векторов bubble_time и pyramid_time
		class info_time { 
			
		public:
			std::vector<std::vector<double>> bubble_time; // Создание вектора bubble_time
			std::vector<std::vector<double>> pyramid_time; // Создание вектора pyramid_time

			// Констуктор класса info_time с определением векторов bubble_time и pyramid_time
			info_time() : bubble_time(2, std::vector<double>(11, 0.0)), pyramid_time(2, std::vector<double>(11, 0.0)) {}
		};
		
		std::fstream file; // Объект класса для чтения и записи данных из файла и в файл соответственно
		info_time Info; // Объект класса info_time в области видимости класса menu
		sorting Sort; // Объект описанного класса sorting с методами сортировок
		int C = 1000; //Константа (размер массива вектора)
		std::vector <double> vect; /* Динамический массив с числами double */
		std::vector <double> trial_vect; /* Срезанный массив */
		std::vector <int> diff_par = { 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 }; // Массив с набором параметров сложности
		std::string path_to_file = "Results_of_sortings.txt"; //Путь к файлу

		/*Второстепенные функции, используемые для основных функций*/
		void print_table(const std::vector<std::vector<double>>& data);
		void save_time(std::function<void(std::vector<double>)> view_sorting, std::vector<std::vector<double>>& view_time, int n);

	public:
		void generate(); /*Генерация массива*/
		void sorting(); /*Выполнить сортировку и сохранить время в массив*/
		void saving(); /* Сохранение данных в файл*/
		void downloading(); /* Чтение данных из файла*/
		void show(); /* Показать данные*/
		void display(); /* Отобразить график */

	};

	functions Func; // объект класса functions в области видимости класса menu

public:

	void start(); /*Запуск работы меню*/
	void end(); /*Завершение работы меню*/
	void choice(); /*Выбор действия*/

};

