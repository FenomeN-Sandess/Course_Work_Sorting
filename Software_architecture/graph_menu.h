#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <type_traits>
#include "functions.h"
#include "graph_table.h"
#include "graph_menu_global.h"
#include "plot.h"
#pragma once

enum buttons {
	generate,
	calculate,
	save,
	download,
	table,
	plot,
	restart,
	quit,
	none
};

class graph_menu {
private:
	functions* Func;
	global g;
	table_window t;
	plot_window p;
	buttons active_button;
	buttons get_button() { return active_button; }
	void set_button(buttons button) { this->active_button = button; }
	void set_button(std::vector <sf::Text>& texts, sf::Vector2i& mouse_pos);
protected:
	std::string background_img = "background_4.jpg"; // �������� ����
	unsigned int windowWidth = static_cast<unsigned int>(g.screenWidth * 0.3); // ������ ����
	unsigned int windowHeight = static_cast<unsigned int>(g.screenHeight * 0.7); // ������ ����
	unsigned int windowMessageWidth = static_cast<unsigned int>(g.screenWidth * 0.15); //������ ���� � ����������
	unsigned int windowMessageHeight = static_cast<unsigned int>(g.screenHeight * 0.10); // ������ ���� � ����������
	
	std::vector <std::string> text_operation = { "Generate", "Calculate", "Save", "Download",
	"Display the table", "Display a plot", "Restart", "Quit" }; // ������������ ������ � ����������� ����
	std::string str_font = "JosefinSans-Bold.ttf"; // ������������ ����� � ����
	std::string str_font_window = "Kanit-Thin.ttf"; // ������������ ����� � ����

	float position_operation_y = windowHeight * 0.11f; // ������ ������ ������ ����
	float padding_bottom_operation = windowHeight * 0.1f; // ������� �����
	float position_message_y = windowMessageHeight * 0.25f; // ������� ��������� �� ��� OY
	float position_agreement_y = windowMessageHeight * 0.7f; // ������� ok �� ��� OY
	float position_rectangle_y = windowMessageHeight * 0.65f; // ������ �������������� �� OY 

	unsigned int size_font = static_cast<unsigned int>(windowWidth / 15); // ������ ������ � ����
	unsigned int size_font_message = static_cast<unsigned int>(windowMessageWidth / 15); // ������ ������ � ���������� ����
	float rectangle_outline_thickness = 2;
	float border_size_button = 3; // ������ ������ � ������ � ������� ����
	float border_size_button_window = 0.1; // ������ ������ � ������ � ���������� ����
	std::vector <float> rectangle_window_size = {
		static_cast<float>(size_font_message*4),
		static_cast<float>(size_font_message*1.2)
	};

	sf::Color rectangle_theFill_color = sf::Color::White;
	std::vector <int> custom_color_button = { 102, 255, 255, 190 }; // ���� ������ ������� ������ �� ���������
	std::vector <int> second_custom_color_button = { 255, 102, 255, 190 }; // ���� ��������� ������� ������
	std::vector <int> event_color_button = { 102, 255, 255, 255 }; // ���� ������ ��� ��������� ������ ������� ������
	std::vector <int> second_event_color_button = { 255, 102, 255, 255 }; // ���� ������ ��� ��������� ������ ������� ������
	std::vector <int> border_color_button = { 0, 0, 0 }; // ���� ������� � ������
	std::vector <int> rectangle_theFill_color_animation = { 160,160,160,20 };
	std::vector <int> rectangle_outline_color = { 160,160,160,255 };

	std::vector <sf::Color> definition_color(std::vector <int>& first, std::vector <int>& second,
	std::vector <int>& third, std::vector <int>& fourth); // ������� ����������� ������� � rgb �������
	void definition_button_texts(std::vector <sf::Color>& rgb_default); // �������� �������� � ����
	void mouse_response_button(sf::Vector2i& mouse_pos,	std::vector <sf::Color>& rgb,
	int& iter, int& count); // ������� ����������� �������, ����������� ��� ��������� �� ������ �������

public:
	graph_menu(functions* f) : Func(f), g(f), t(f), p(f) {}

	bool window(); // ������� ��� �������� ����, ��������� ����������� � ��������� �������
	void window_message(std::string message, std::string banner, sf::Vector2i window_pos);
};




