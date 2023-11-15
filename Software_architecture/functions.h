#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <functional> 


void bubble_sorting(std::vector <double> vector); /* Пузырьковая сортировка */
void pyramid_sorting(std::vector <double> vector); /* Пирамидальная сортировка*/
void insertion_sorting(std::vector<double> vector); // Сортировка вставками
void selection_sorting(std::vector<double> vector); // Сортировка вставками
void quick_sorting(std::vector<double> vector); // Быстрая сортировка

class functions { /* Класс для работы с функциями */
protected:
	std::fstream file;	// Объект класса для чтения и записи данных из файла и в файл
	std::ofstream outfile;
	std::ifstream inputfile;
	int C = 1000;																			//Константа (размер массива вектора)
	std::vector <double> vect;																/* Динамический массив с числами double */
	std::vector <double> trial_vect;														/* Срезанный массив */
	std::string path_to_file = "Results_of_sortings.txt";								    // Путь к файлу
	std::vector <int> diff_par = { 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 }; // Массив с набором параметров сложности

	
	void print_table(const std::vector<std::vector<double>>& data);
	void save_time(void view_sorting(std::vector <double> vector), std::vector<std::vector<double>>& view_time, int n);
	void save_data(std::vector<std::vector<double>>& sort_time);
	void download_data(std::vector<std::vector<double>>& sort_time);

public:
	functions() : bubble_time(2, std::vector<double>(11, 0.0)), pyramid_time(2, std::vector<double>(11, 0.0)),
		insertion_time(2, std::vector<double>(11, 0.0)), quick_time(2, std::vector<double>(11, 0.0)),
		selection_time(2, std::vector<double>(11, 0.0)) {}

	std::vector<std::vector<double>> bubble_time;											// Создание вектора bubble_time
	std::vector<std::vector<double>> pyramid_time;										    // Создание вектора pyramid_time
	std::vector<std::vector<double>> insertion_time;										
	std::vector<std::vector<double>> quick_time;
	std::vector<std::vector<double>> selection_time;

	void generate();																		/*Генерация массива*/
	void sorting();																			/*Выполнить сортировку и сохранить время в массив*/
	void saving();																			/* Сохранение данных в файл*/
	void downloading();																		/* Чтение данных из файла*/
	void show(); 																			/* Показать данные в таблице*/
	bool check_content_massive(std::vector<std::vector<double>> sorting_time);
	void reset_data();																		// Обновить данные 
	void display();																			/* Отобразить график в консоли */
	bool empty_data();
};

