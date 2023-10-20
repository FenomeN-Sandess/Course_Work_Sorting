
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <fstream>
#pragma once

class sorting { //Класс с методами сортировок
public:
	void bubble_sorting(std::vector <float> vector); /* Пузырьковая сортировка */
	void pyramid_sorting(std::vector <float> vector); /* Пирамидальная сортировка*/
};


class menu { /* Класс для работы с меню */
private: 

	bool work_process = false;

protected:

	class functions { /* Класс для работы с функциями */
	protected:

		class info_time { /* Класс, содержащий данные двухмерных векторов bubble_time и pyramid_time */
			/* Класс создан для его записи в файл и чтения */
		public:
			std::vector<std::vector<double>> bubble_time; // Создание вектора bubble_time
			std::vector<std::vector<double>> pyramid_time; // Создание вектора pyramid_time

			// Констуктор класса info_time с определением векторов bubble_time и pyramid_time
			info_time() : bubble_time(2, std::vector<double>(11, 0.0)), pyramid_time(2, std::vector<double>(11, 0.0)) {}
		};

		info_time Info; // Объект класса info_time в области видимости класса menu

		std::fstream file; // Объект класса для чтения и записи данных из файла и в файл соответственно
		sorting Sort; // Объект описанного класса sorting с методами сортировок
		
		int C = 1000; //Константа (размер массива вектора)
		std::vector <float> vect; /* Динамический массив с целыми числами */
		std::vector <float> trial_vect; /* Срезанный массив */
		std::vector <int> diff_par = { 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 }; // Массив с набором параметров сложности


		std::string path_to_file = "Results_of_sortings.txt"; //Путь к файлу


	public:

		void generate(); /*Генерация массива*/
		void sorting(); /*Выполнить сортировку и сохранить время в массив*/
		void saving(); /* Сохранение данных в файл*/
		void downloading(); /* Чтениеданных из файла*/
		void show(); /* Показать данные*/
		void display(); /* Отобразить график */

	};

	functions Func; // объект класса functions в области видимости класса menu

public:

	void start(); /*Запуск работы меню*/
	void end(); /*Завершение работы меню*/
	void choice(); /*Выбор действия*/

};

