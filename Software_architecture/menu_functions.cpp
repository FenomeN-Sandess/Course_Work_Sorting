

/// Файл с определениями функций класса func

#pragma once
#include <iostream> // Стандартная библиотека для организации ввода и вывода
#include <string> // Класс с методами и переменными для организации работы со строками 
#include <vector> // Стандартная библиотека для создания динамического массивов данных 
#include <iomanip> // Стандартная библиотека для управления вводов и выводом. Используется в проекте для вывода таблицы корректно
#include <chrono> // Стандартная библиотека C++ В программе используется как "секундомер"
#include <fstream> // Стандартная библиотека C++. Используется для чтения и записи данных из файла и в файл.
#include <SFML/Graphics.hpp>
//#include <Windows.h>

#include "classes.h"

void menu::functions::generate() { 

	vect.clear(); //Очищение элементов в массиве
	for (int iter = 0; iter < C ; iter++) {
		vect.push_back(rand() % 5000 + 1); //Заполнение массива данными
	}

	std::cout << "Generation complete\n" << std::endl;
}

void menu::functions::sorting()
{
	for (int n = 0; n <= 10; n++) {

		
		// Создание среза вектора до n

		for (int j = 0; j < diff_par[n]; j++) {
			trial_vect.push_back(vect[j]); // заполнение массива со срезом - голова сгенерированного вектора
		}
		
		auto start = std::chrono::high_resolution_clock::now(); //Сохранение текущего времени
		Sort.bubble_sorting(trial_vect); //Выполнение пузырьковой сортировки
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> bubble_duration = end - start; //Время за которое выполнена сортировка
		Info.bubble_time[0][n] = diff_par[n]; // Заполнение нулевого столбца параметрами сложности
		Info.bubble_time[1][n] = bubble_duration.count(); // Заполнение первого столбца временем выполнения цикла в секундах

		start = std::chrono::high_resolution_clock::now();
		Sort.pyramid_sorting(trial_vect); //Выполнение пирамидальной сортировки
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> pyramid_duration = end - start;
		Info.pyramid_time[0][n] = diff_par[n];
		Info.pyramid_time[1][n] = pyramid_duration.count();

		trial_vect.clear(); //Очищение пробного вектора
	}
}

void menu::functions::saving()
{
	file.open(path_to_file); //Открытие файла или его создание 
	if (!file.is_open()) { //Проверка на открытие
		std::cout << "File opening error\n";
	}
	else {
		//Запись объекта, содержащего данные о времени выполнения сортировок, в файл.

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 11; j++) {
				file.write(reinterpret_cast<char*>(&Info.bubble_time[i][j]), sizeof(double));
				file.write(reinterpret_cast<char*>(&Info.pyramid_time[i][j]), sizeof(double));
			}
		}
	}
	file.close();
}

void menu::functions::downloading()
{
	file.open(path_to_file); // Открытие файла (не создание!)
	if (!file.is_open()) {
		std::cout << "File opening error";
	}
	else {
		// Чтения объекта, содержащего данные о времени выполнения сортировок, из файла
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 11; j++) {
				file.read(reinterpret_cast<char*>(&Info.bubble_time[i][j]), sizeof(double));
				file.read(reinterpret_cast<char*>(&Info.pyramid_time[i][j]), sizeof(double));
			}
		}
	}
	file.close();
}

void print_table(const std::vector<std::vector<double>>& data) {
	const char separator = ' ';
	const int nameWidth = 15;
	const int numWidth = 12;

	for (size_t i = 0; i < data.size(); ++i) {
		std::cout << std::setw(nameWidth + 3) << std::setfill('-') << ""; // Граница таблицы
		for (size_t j = 0; j < data[i].size(); ++j) {
			std::cout << std::setw(numWidth + 3) << std::setfill('-') << "";
		}
		std::cout << std::endl;

		std::string res = (static_cast<int>(i) == 0 ? "n" : "t (s)");
		std::cout << std::setw(nameWidth) << std::setfill(separator) << "| Row " + res + " |";
		for (size_t j = 0; j < data[i].size(); ++j) {
			std::cout << std::setw(numWidth) << std::setfill(separator) << data[i][j] << " |";
		}
		std::cout << std::endl;
	}

	std::cout << std::setw(nameWidth + 3) << std::setfill('-') << "";
	for (size_t j = 0; j < data[0].size(); ++j) {
		std::cout << std::setw(numWidth + 3) << std::setfill('-') << "";
	}
	std::cout << std::endl;
}

void menu::functions::show() {

	std::cout << "Bubble Table" << std::endl;
	print_table(Info.bubble_time);
	std::cout << "\nPyramid Table" << std::endl;
	print_table(Info.pyramid_time);
	std::cout << std::endl;

}


void menu::functions::display()
{
}

