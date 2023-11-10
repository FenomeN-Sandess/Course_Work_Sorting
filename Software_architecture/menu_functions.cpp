

/// Файл с определениями функций класса func

#pragma once
#include <iostream> // Стандартная библиотека для организации ввода и вывода
#include <string> // Класс с методами и переменными для организации работы со строками 
#include <vector> // Стандартная библиотека для создания динамического массивов данных 
#include <iomanip> // Стандартная библиотека для управления вводов и выводом. Используется в проекте для вывода таблицы корректно
#include <chrono> // Стандартная библиотека C++ В программе используется как "секундомер"
#include <fstream> // Стандартная библиотека C++. Используется для чтения и записи данных из файла и в файл.
#include "menu.h"

//Второстепенные функции
void menu::functions::print_table(const std::vector<std::vector<double>>& data) {
	const char separator = ' ';
	const int nameWidth = 15;
	const int numWidth = 12;

	for (size_t i = 0; i < data.size(); ++i) {
		std::cout << std::setw(static_cast<std::streamsize>(nameWidth) + 3) << std::setfill('-') << ""; // Граница таблицы
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

void menu::functions::save_time(void view_sorting(std::vector <double> vector), std::vector<std::vector<double>>& view_time, int n)
{
	for (int j = 0; j < diff_par[n]; j++) {
		trial_vect.push_back(vect[j]); // заполнение массива со срезом - голова сгенерированного вектора
	}
	
	auto start = std::chrono::high_resolution_clock::now(); //Сохранение текущего времени
	view_sorting(trial_vect);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> difference = end - start; //Время за которое выполнена сортировка
	view_time[0][n] = diff_par[n];
	view_time[1][n] = difference.count();

	trial_vect.clear(); //Очищение пробного вектора
}

//Основные функции
void menu::functions::generate() {

	vect.clear(); //Очищение элементов в массиве
	for (int iter = 0; iter < C ; iter++) {
		double test = ((rand() % 5001));
		vect.push_back(test); //Заполнение массива данными
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

		save_time(bubble_sorting, bubble_time, n);
		save_time(pyramid_sorting, pyramid_time, n);
		//save_time(std::bind(&sorting::_sorting, &Sort, std::placeholders::_1), Info._time, n);
		//save_time(std::bind(&sorting::_sorting, &Sort, std::placeholders::_1), Info._time, n);
		//save_time(std::bind(&sorting::_sorting, &Sort, std::placeholders::_1), Info._time, n);

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
				file.write(reinterpret_cast<char*>(&bubble_time[i][j]), sizeof(double));
				file.write(reinterpret_cast<char*>(&pyramid_time[i][j]), sizeof(double));
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
				file.read(reinterpret_cast<char*>(&bubble_time[i][j]), sizeof(double));
				file.read(reinterpret_cast<char*>(&pyramid_time[i][j]), sizeof(double));
			}
		}
	}
	file.close();
}

void menu::functions::show() {
	
	//Control.start_menu();
	std::cout << "Bubble Table" << std::endl;
	print_table(bubble_time);
	std::cout << "\nPyramid Table" << std::endl;
	print_table(pyramid_time);
	std::cout << std::endl;
	
}

void menu::functions::display()
{


	//VideoMode desktop = VideoMode::getDesktopMode(); // Получение разрешения экрана
	//unsigned int screenWidth = desktop.width; // Ширина экрана
	//unsigned int screenHeight = desktop.height; // Высота экрана
	//RenderWindow window(VideoMode(screenHeight * 0.9, screenHeight * 0.9), "Plot", sf::Style::Titlebar | sf::Style::Close); //Создание окна

	//double wSize = window.getSize().x;
	//double graph_position_OX = 0.07;
	//double graph_position_OY = 1 - graph_position_OX; // Отступы должны быть равны для сохранения длины единичных отрезков
	//double Unit_segment = wSize * 0.7 / 22;  // Единичный отрезок
	//double Number_unit_segment = 0.00035; // Значение единичного отрезка в секундах
	//bool first_unit_segment = true; // Флаг
	//int lines_count = 32;
	//int vectors_count = 44;
	//int count_OY = 0;
	//int count_OX = 0;
	//VertexArray OX_lines(Lines, lines_count);
	//VertexArray OY_lines(Lines, lines_count);
	//VertexArray vectors(Lines, vectors_count);

	//Vertex OY_axis[] =
	//{
	//	sf::Vertex(sf::Vector2f(wSize * graph_position_OX,   0), sf::Color::Black, sf::Vector2f(0,  0)),
	//	sf::Vertex(sf::Vector2f(wSize * graph_position_OX, screenHeight), sf::Color::Black, sf::Vector2f(10, 10)),
	//};

	//Vertex OX_axis[] =
	//{
	//	Vertex(Vector2f(0, wSize * graph_position_OY), Color::Black, Vector2f(10,10)),
	//	Vertex(Vector2f(screenWidth, wSize * graph_position_OY), Vector2f(10,10)),
	//};

	//Text value_ox_oy;
	//value_ox_oy.setFont(font);
	//value_ox_oy.setCharacterSize(wSize / 70);
	//value_ox_oy.setFillColor(sf::Color::Black);
	 
	//value_ox_oy.setString("t(s)");
	//value_ox_oy.setPosition(wSize * (graph_position_OX + 0.015), wSize * 0.03);
	//texts.push_back(value_ox_oy);
	//value_ox_oy.setString("N");
	//value_ox_oy.setPosition(wSize * (1 - 0.045), wSize * (graph_position_OY - 0.03));
	//texts.push_back(value_ox_oy);

	//for (int i = 2; i < 29; i += 2) {
	//	for (int j = 0; j < 2; j += 1) {
	//		Text text;
	//		text.setFont(font);
	//		text.setCharacterSize(wSize / 70);
	//		text.setFillColor(sf::Color::Black);

	//		if (first_unit_segment) {
	//			text.setString("0");
	//			text.setPosition(wSize * (graph_position_OX - 0.015), wSize * (graph_position_OY + 0.005));
	//			texts.push_back(text);
	//		}

	//		if (first_unit_segment) {
	//			if (j == 0) {
	//				text.setString(std::to_string(50));
	//				text.setPosition(wSize * graph_position_OX + Unit_segment, wSize * (graph_position_OY+0.01));
	//				texts.push_back(text);
	//			}
	//			else {
	//				text.setString(std::to_string(Number_unit_segment));
	//				text.setPosition(wSize * (graph_position_OX-0.065), wSize * graph_position_OY - Unit_segment);
	//				texts.push_back(text);
	//			}
	//		}

	//		if (j == 0) {
	//			text.setString(std::to_string(i * 100 / 2));
	//			text.setPosition(wSize * graph_position_OX + Unit_segment * i, wSize * (graph_position_OY+0.01));
	//			texts.push_back(text);
	//		}
	//		else {
	//			double f = Number_unit_segment * i;
	//			text.setString(std::to_string(f));
	//			text.setPosition(wSize * (graph_position_OX - 0.065), wSize * graph_position_OY - Unit_segment * i);
	//			texts.push_back(text);
	//		}
	//	}

	//	if (first_unit_segment) {
	//		OX_lines[lines_count-2].position = Vector2f(wSize * graph_position_OX + Unit_segment, wSize * (graph_position_OY + 0.01));
	//		OX_lines[lines_count-1].position = Vector2f(wSize * graph_position_OX + Unit_segment, wSize * (graph_position_OY - 0.01));
	//		OX_lines[lines_count-2].color = Color::Black;
	//		OX_lines[lines_count-1].color = Color::Black;

	//		OY_lines[lines_count-2].position = Vector2f(wSize * (graph_position_OX - 0.01), wSize * graph_position_OY - Unit_segment);
	//		OY_lines[lines_count-1].position = Vector2f(wSize * (graph_position_OX + 0.01), wSize * graph_position_OY - Unit_segment);
	//		OY_lines[lines_count-2].color = Color::Black;
	//		OY_lines[lines_count-1].color = Color::Black;
	//	}

	//	first_unit_segment = false;

	//	double xSize = wSize * graph_position_OX + Unit_segment * i;
	//	double ySize = wSize * graph_position_OY - Unit_segment * i;

	//	OX_lines[i].position = Vector2f(xSize, wSize * (graph_position_OY + 0.01));
	//	OX_lines[i + 1].position = Vector2f(xSize, wSize * (graph_position_OY - 0.01));
	//	OY_lines[i].position = Vector2f(wSize * (graph_position_OX - 0.01), ySize);
	//	OY_lines[i + 1].position = Vector2f(wSize * (graph_position_OX + 0.01), ySize);

	//	OX_lines[i].color = Color::Black;
	//	OX_lines[i + 1].color = Color::Black;
	//	OY_lines[i].color = Color::Black;
	//	OY_lines[i + 1].color = Color::Black;
	//}

	//for (int k = 0; k <= 22; k += 22) {
	//	vectors[0+k].position = Vector2f(wSize * graph_position_OX, wSize * graph_position_OY);
	//	vectors[0+k].color = (k!=22) ? Color::Red : Color::Blue;
	//	vectors[1 + k].position = Vector2f(wSize * graph_position_OX + Unit_segment, wSize * graph_position_OY - ((((k!=22) ? Info.bubble_time[1][0] : Info.pyramid_time[1][0]) * Unit_segment / Number_unit_segment)));
	//	vectors[1+k].color = (k != 22) ? Color::Red : Color::Blue;

	//	vectors[2+k].position = Vector2f(wSize * graph_position_OX + Unit_segment, wSize * graph_position_OY - ((((k != 22) ? Info.bubble_time[1][0] : Info.pyramid_time[1][0]) * Unit_segment / Number_unit_segment)));
	//	vectors[2+k].color = (k != 22) ? Color::Red : Color::Blue;
	//	vectors[3+k].position = Vector2f(wSize * graph_position_OX + Unit_segment * 2, wSize * graph_position_OY - ((((k != 22) ? Info.bubble_time[1][1] : Info.pyramid_time[1][1]) * Unit_segment / Number_unit_segment)));
	//	vectors[3+k].color = (k != 22) ? Color::Red : Color::Blue;
	//}

	//for (int j = 4; j <= 20; j+=2) {
	//	count_OY += 1;
	//	count_OX += 2;
	//	vectors[j].position = Vector2f(wSize * graph_position_OX + Unit_segment * (count_OX), wSize * graph_position_OY - ((Info.bubble_time[1][count_OY] * Unit_segment / Number_unit_segment)));
	//	vectors[j].color = Color::Red;
	//	vectors[j+1].position = Vector2f(wSize * graph_position_OX + Unit_segment * (count_OX+2), wSize * graph_position_OY - ((Info.bubble_time[1][count_OY+1] * Unit_segment / Number_unit_segment)));
	//	vectors[j+1].color = Color::Red;
	//}
	//count_OY = 0; count_OX = 0;
	//for (int j = 26; j <= 42; j += 2) {
	//	count_OY += 1;
	//	count_OX += 2;
	//	vectors[j].position = Vector2f(wSize * graph_position_OX + Unit_segment * (count_OX), wSize * graph_position_OY - ((Info.pyramid_time[1][count_OY] * Unit_segment / Number_unit_segment)));
	//	vectors[j].color = Color::Blue;
	//	vectors[j + 1].position = Vector2f(wSize * graph_position_OX + Unit_segment * (count_OX + 2), wSize * graph_position_OY - ((Info.pyramid_time[1][count_OY + 1] * Unit_segment / Number_unit_segment)));
	//	vectors[j + 1].color = Color::Blue;
	//}


	//while (window.isOpen() /* окно открыто - true*/) { //Главный цикл - заканчивается, как только окно закрыто

	//	//Обработка событий
	//	Event event;
	//	while (window.pollEvent(event)) {
	//		//Закрытие окна при нажатии на кнопку закрытия
	//		if (event.type == Event::Closed) window.close();
	//	}

	//	window.setActive(); //Активация окна для отрисовки

	//	window.clear(Color::White);  

	//	window.draw(OY_axis, 2, sf::Lines);
	//	window.draw(OX_axis, 2, sf::Lines);
	//	window.draw(OX_lines);
	//	window.draw(OY_lines);
	//	window.draw(vectors);

	//	for (const auto& text : texts) {
	//		window.draw(text);
	//	}

	//	window.display(); //Вывод

	//}
}

