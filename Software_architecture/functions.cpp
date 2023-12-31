#include "functions.h"
#include <SFML/Graphics.hpp>
using namespace sf;

/// ���� � ������������� ������� ������ func

#pragma once
#include <iostream> // ����������� ���������� ��� ����������� ����� � ������
#include <string> // ����� � �������� � ����������� ��� ����������� ������ �� �������� 
#include <vector> // ����������� ���������� ��� �������� ������������� �������� ������ 
#include <iomanip> // ����������� ���������� ��� ���������� ������ � �������. ������������ � ������� ��� ������ ������� ���������
#include <chrono> // ����������� ���������� C++ � ��������� ������������ ��� "����������"
#include <fstream> // ����������� ���������� C++. ������������ ��� ������ � ������ ������ �� ����� � � ����.
#include "functions.h"

//�������������� �������
void functions::print_table(const std::vector<std::vector<double>>& data) {
	const char separator = ' ';
	const int nameWidth = 15;
	const int numWidth = 12;

	for (size_t i = 0; i < data.size(); ++i) {
		std::cout << std::setw(static_cast<std::streamsize>(nameWidth) + 3) << std::setfill('-') << ""; // ������� �������
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

void functions::save_time(void (*view_sorting)(std::vector <double>& vector), std::vector<std::vector<double>>& view_time)
{
	for (int n = 0; n <= 10; n++) {
		for (int j = 0; j < diff_par[n]; j++) {
			trial_vect.push_back(vect[j]); // ���������� ������� �� ������ - ������ ���������������� �������
		}

		auto start = std::chrono::high_resolution_clock::now(); //���������� �������� �������
		view_sorting(trial_vect);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> difference = end - start; //����� �� ������� ��������� ����������
		view_time[0][n] = diff_par[n];
		view_time[1][n] = difference.count();

		trial_vect.clear(); //�������� �������� �������
	}
}

void functions::save_data(std::vector<std::vector<double>>& sort_time) {
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 11; j++)
		{
			outfile << sort_time[i][j] << " ";
		}
	}
};

void functions::download_data(std::vector<std::vector<double>>& sort_time) {
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 11; j++)
		{
			inputfile >> sort_time[i][j];
		}
	}
};


//�������� �������
void functions::generate() {

	vect.clear(); //�������� ��������� � �������
	for (int iter = 0; iter < C; iter++) {
		double test = ((rand() % 5001));
		vect.push_back(test); //���������� ������� �������
	}
}

void functions::sorting()
{

	save_time(pyramid_sorting, pyramid_time);
	save_time(quick_sorting, quick_time);
	save_time(insertion_sorting, insertion_time);
	save_time(selection_sorting, selection_time);
	save_time(bubble_sorting, bubble_time);

}

void functions::saving()
{
	outfile.open(path_to_file); //�������� ����� ��� ��� �������� 
	if (!outfile.is_open()) { //�������� �� ��������
		std::cout << "file is not open" << std::endl;
	}
	else {
		save_data(bubble_time);
		save_data(pyramid_time);
		save_data(insertion_time);
		save_data(quick_time);
		save_data(selection_time);
	}
	outfile.close();
}

void functions::downloading()
{
	inputfile.open(path_to_file); // �������� ����� (�� ��������!)
	if (!inputfile.is_open()) {
	}
	else {
		download_data(bubble_time);
		download_data(pyramid_time);
		download_data(insertion_time);
		download_data(quick_time);
		download_data(selection_time);
	}
	inputfile.close();
}

void functions::show() {
	std::cout << "Bubble Table" << std::endl;
	print_table(bubble_time);
	std::cout << "\nHeap Table" << std::endl;
	print_table(pyramid_time);
	std::cout << "\nQuick Table" << std::endl;
	print_table(quick_time);
	std::cout << "\nSelection Table" << std::endl;
	print_table(selection_time);
	std::cout << "\nInsertion Table" << std::endl;
	print_table(insertion_time);
	std::cout << std::endl;
}

bool functions::check_content_massive(std::vector<std::vector<double>> sorting_time)
{
	for (std::vector <double> iter_1 : sorting_time) {
		for (double iter_2 : iter_1) { 
			if (iter_2 != 0) { return true; }
		} 
	} 
	return false;
}
void cycle_cleaning(std::vector<std::vector<double>>& sorting_time){
	for (int i = 0; i < 2; i++) 	{
		for (int iter = 0; iter < (sorting_time[i].size()); iter++) {
			sorting_time[i][iter] = 0.0;
		}
	}
}
void functions::reset_data()
{
	if (check_content_massive(bubble_time) == true) {
		cycle_cleaning(bubble_time);
		cycle_cleaning(pyramid_time);
		cycle_cleaning(insertion_time);
		cycle_cleaning(quick_time);
		cycle_cleaning(selection_time);
	} 
}

void functions::display()
{



	sf::Font font_display;
	if (!font_display.loadFromFile("arial.ttf"))
	{
		std::cout << "error" << std::endl;
	}
	std::vector <Text> unit_texts;

	VideoMode desktop = VideoMode::getDesktopMode(); // ��������� ���������� ������
	unsigned int screenWidth = desktop.width; // ������ ������
	unsigned int screenHeight = desktop.height; // ������ ������
	RenderWindow window(VideoMode(screenHeight * 0.9, screenHeight * 0.9), "Plot", sf::Style::Titlebar | sf::Style::Close); //�������� ����

	double wSize = window.getSize().x;
	double graph_position_OX = 0.07;
	double graph_position_OY = 1 - graph_position_OX; // ������� ������ ���� ����� ��� ���������� ����� ��������� ��������
	double Unit_segment = wSize * 0.7 / 22;  // ��������� �������
	double Number_unit_segment = 0.001; // �������� ���������� ������� � ��������
	bool first_unit_segment = true; // ����
	int lines_count = 32;
	int vectors_count = 44;
	int count_OY = 0;
	int count_OX = 0;
	VertexArray OX_lines(Lines, lines_count);
	VertexArray OY_lines(Lines, lines_count);
	VertexArray vectors(Lines, vectors_count);

	Vertex OY_axis[] =
	{
		sf::Vertex(sf::Vector2f(wSize * graph_position_OX,   0), sf::Color::Black, sf::Vector2f(0,  0)),
		sf::Vertex(sf::Vector2f(wSize * graph_position_OX, screenHeight), sf::Color::Black, sf::Vector2f(10, 10)),
	};

	Vertex OX_axis[] =
	{
		Vertex(Vector2f(0, wSize * graph_position_OY), Color::Black, Vector2f(10,10)),
		Vertex(Vector2f(screenWidth, wSize * graph_position_OY), Vector2f(10,10)),
	};

	Text value_ox_oy;
	value_ox_oy.setFont(font_display);
	value_ox_oy.setCharacterSize(wSize / 70);
	value_ox_oy.setFillColor(sf::Color::Black);

	value_ox_oy.setString("t(s)");
	value_ox_oy.setPosition(wSize * (graph_position_OX + 0.015), wSize * 0.03);
	unit_texts.push_back(value_ox_oy);
	value_ox_oy.setString("N");
	value_ox_oy.setPosition(wSize * (1 - 0.045), wSize * (graph_position_OY - 0.03));
	unit_texts.push_back(value_ox_oy);

	for (int i = 2; i < 29; i += 2) {
		for (int j = 0; j < 2; j += 1) {
			Text text;
			text.setFont(font_display);
			text.setCharacterSize(wSize / 70);
			text.setFillColor(sf::Color::Black);

			if (first_unit_segment) {
				text.setString("0");
				text.setPosition(wSize * (graph_position_OX - 0.015), wSize * (graph_position_OY + 0.005));
				unit_texts.push_back(text);
			}

			if (first_unit_segment) {
				if (j == 0) {
					text.setString(std::to_string(50));
					text.setPosition(wSize * graph_position_OX + Unit_segment, wSize * (graph_position_OY+0.01));
					unit_texts.push_back(text);
				}
				else {
					text.setString(std::to_string(Number_unit_segment));
					text.setPosition(wSize * (graph_position_OX-0.065), wSize * graph_position_OY - Unit_segment);
					unit_texts.push_back(text);
				}
			}

			if (j == 0) {
				text.setString(std::to_string(i * 100 / 2));
				text.setPosition(wSize * graph_position_OX + Unit_segment * i, wSize * (graph_position_OY+0.01));
				unit_texts.push_back(text);
			}
			else {
				double f = Number_unit_segment * i;
				text.setString(std::to_string(f));
				text.setPosition(wSize * (graph_position_OX - 0.065), wSize * graph_position_OY - Unit_segment * i);
				unit_texts.push_back(text);
			}
		}

		if (first_unit_segment) {
			OX_lines[lines_count-2].position = Vector2f(wSize * graph_position_OX + Unit_segment, wSize * (graph_position_OY + 0.01));
			OX_lines[lines_count-1].position = Vector2f(wSize * graph_position_OX + Unit_segment, wSize * (graph_position_OY - 0.01));
			OX_lines[lines_count-2].color = Color::Black;
			OX_lines[lines_count-1].color = Color::Black;

			OY_lines[lines_count-2].position = Vector2f(wSize * (graph_position_OX - 0.01), wSize * graph_position_OY - Unit_segment);
			OY_lines[lines_count-1].position = Vector2f(wSize * (graph_position_OX + 0.01), wSize * graph_position_OY - Unit_segment);
			OY_lines[lines_count-2].color = Color::Black;
			OY_lines[lines_count-1].color = Color::Black;
		}

		first_unit_segment = false;

		double xSize = wSize * graph_position_OX + Unit_segment * i;
		double ySize = wSize * graph_position_OY - Unit_segment * i;

		OX_lines[i].position = Vector2f(xSize, wSize * (graph_position_OY + 0.01));
		OX_lines[i + 1].position = Vector2f(xSize, wSize * (graph_position_OY - 0.01));
		OY_lines[i].position = Vector2f(wSize * (graph_position_OX - 0.01), ySize);
		OY_lines[i + 1].position = Vector2f(wSize * (graph_position_OX + 0.01), ySize);

		OX_lines[i].color = Color::Black;
		OX_lines[i + 1].color = Color::Black;
		OY_lines[i].color = Color::Black;
		OY_lines[i + 1].color = Color::Black;
	}

	for (int k = 0; k <= 22; k += 22) {
		vectors[0+k].position = Vector2f(wSize * graph_position_OX, wSize * graph_position_OY);
		vectors[0+k].color = (k!=22) ? Color::Red : Color::Blue;
		vectors[1 + k].position = Vector2f(wSize * graph_position_OX + Unit_segment, wSize * graph_position_OY - ((((k!=22) ? bubble_time[1][0] : pyramid_time[1][0]) * Unit_segment / Number_unit_segment)));
		vectors[1+k].color = (k != 22) ? Color::Red : Color::Blue;

		vectors[2+k].position = Vector2f(wSize * graph_position_OX + Unit_segment, wSize * graph_position_OY - ((((k != 22) ? bubble_time[1][0] : pyramid_time[1][0]) * Unit_segment / Number_unit_segment)));
		vectors[2+k].color = (k != 22) ? Color::Red : Color::Blue;
		vectors[3+k].position = Vector2f(wSize * graph_position_OX + Unit_segment * 2, wSize * graph_position_OY - ((((k != 22) ? bubble_time[1][1] : pyramid_time[1][1]) * Unit_segment / Number_unit_segment)));
		vectors[3+k].color = (k != 22) ? Color::Red : Color::Blue;
	}

	for (int j = 4; j <= 20; j+=2) {
		count_OY += 1;
		count_OX += 2;
		vectors[j].position = Vector2f(wSize * graph_position_OX + Unit_segment * (count_OX), wSize * graph_position_OY - ((bubble_time[1][count_OY] * Unit_segment / Number_unit_segment)));
		vectors[j].color = Color::Red;
		vectors[j+1].position = Vector2f(wSize * graph_position_OX + Unit_segment * (count_OX+2), wSize * graph_position_OY - ((bubble_time[1][count_OY+1] * Unit_segment / Number_unit_segment)));
		vectors[j+1].color = Color::Red;
	}
	count_OY = 0; count_OX = 0;
	for (int j = 26; j <= 42; j += 2) {
		count_OY += 1;
		count_OX += 2;
		vectors[j].position = Vector2f(wSize * graph_position_OX + Unit_segment * (count_OX), wSize * graph_position_OY - ((pyramid_time[1][count_OY] * Unit_segment / Number_unit_segment)));
		vectors[j].color = Color::Blue;
		vectors[j + 1].position = Vector2f(wSize * graph_position_OX + Unit_segment * (count_OX + 2), wSize * graph_position_OY - ((pyramid_time[1][count_OY + 1] * Unit_segment / Number_unit_segment)));
		vectors[j + 1].color = Color::Blue;
	}


	while (window.isOpen() /* ���� ������� - true*/) { //������� ���� - �������������, ��� ������ ���� �������

		//��������� �������
		Event event;
		while (window.pollEvent(event)) {
			//�������� ���� ��� ������� �� ������ ��������
			if (event.type == Event::Closed) window.close();
		}

		window.setActive(); //��������� ���� ��� ���������

		window.clear(Color::White);  

		window.draw(OY_axis, 2, sf::Lines);
		window.draw(OX_axis, 2, sf::Lines);
		window.draw(OX_lines);
		window.draw(OY_lines);
		window.draw(vectors);

		for (const auto& text : unit_texts) {
			window.draw(text);
		}

		window.display(); //�����

	}
}

bool functions::empty_data() {
	return !(check_content_massive(bubble_time) && check_content_massive(pyramid_time)
		&& check_content_massive(insertion_time) && check_content_massive(quick_time)
		&& check_content_massive(selection_time));

}
