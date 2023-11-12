#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "functions.h"
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
protected:

	// ���������� �������� � ��������
	buttons active_button;
	buttons get_button() {return active_button;}
	void set_button(std::vector <sf::Text>& texts, sf::Vector2i& mouse_pos);
	void set_button(buttons button) {this->active_button = button; } 
	sf::Font font; // ������ ������
	sf::Font font_window;
	sf::Sprite background_sprite; // ������ ����
	sf::Texture background_texture; // �������� ����
	std::vector<sf::Text> texts; // ������ �������� �����
	std::vector <sf::Color> rgb; // ������ ������
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); // ��������� ���������� ������
	unsigned int screenWidth = desktop.width; // ������ ������
	unsigned int screenHeight = desktop.height; // ������ ������
	int define_index(sf::Text& elem, std::vector <sf::Text>& vector, int count); /*����������� ������� �������� ���� Text � �������*/
	unsigned int fps = 144;
	int count = 0; //�������
	bool isDragging;
	sf::Vector2i start_position;
	sf::Vector2i current_position;
	sf::Vector2i delta;

	// ���� ��� ���������� ��������
	std::string background_img = "background_4.jpg"; // �������� ����
	unsigned int windowWidth = static_cast<unsigned int>(screenWidth * 0.3); // ������ ����
	unsigned int windowHeight = static_cast<unsigned int>(screenHeight * 0.7); // ������ ����
	unsigned int windowMessageWidth = static_cast<unsigned int>(screenWidth * 0.2); //������ ���� � ����������
	unsigned int windowMessageHeight = static_cast<unsigned int>(screenHeight * 0.15); // ������ ���� � ����������
	float position_message_y = windowMessageHeight * 0.25f; // ������� ��������� �� ��� OY
	float position_agreement_y = windowMessageHeight * 0.6f; // �������  ok �� ��� OY
	float position_operation_y = windowHeight * 0.11f; // ������ ������ ������ ����
	float padding_bottom_operation = windowHeight * 0.1f; // ������� �����
	std::vector <std::string> text_operation = { "Generate", "Calculate", "Save", "Download",
		"Display the table", "Display a plot", "Restart", "Quit"}; // ������������ ������ � ����������� ����
	unsigned int size_font = static_cast<unsigned int>(windowWidth / 15); // ������ ������
	unsigned int size_font_message = static_cast<unsigned int>(windowMessageWidth / 20);
	std::string str_font = "JosefinSans-Bold.ttf"; // ������������ ����� � ����
	std::string str_font_window = "Roboto-Light.ttf"; // ������������ ����� � ����
	std::vector <int> custom_color_button = { 102, 255, 255, 190 }; // ���� ������ ������� ������ �� ���������
	std::vector <int> second_custom_color_button = { 255, 102, 255, 190 }; // ���� ��������� ������� ������
	std::vector <int> event_color_button = { 102, 255, 255, 255 }; // ���� ������ ��� ��������� ������ ������� ������
	std::vector <int> second_event_color_button = { 255, 102, 255, 255 }; // ���� ������ ��� ��������� ������ ������� ������
	std::vector <int> border_color_button = { 0, 0, 0 }; // ���� ������� � ������
	float border_size_button = 3; // ������ ������ � ������

	//������
	bool is_there_cursor(sf::Text& text, sf::Vector2i& mouse_pos); // ������� ������������ ��������� �� ������ � ������ �������
	void download_font(sf::Font& font, std::string& str); // ��������� ������ �� �����
	void download_image(sf::Texture& texture, const std::string& str); // �������� �������� � ��������
	void set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color &color);
	void definition_button_texts(std::vector <sf::Color>& rgb_default); // �������� �������� � ����
	void mouse_response_button(sf::Vector2i& mouse_pos,	std::vector <sf::Color>& rgb,
	int& iter, int& count); // ������� ����������� �������, ����������� ��� ��������� �� ������ �������
	std::vector <sf::Color> definition_color(std::vector <int>& first, std::vector <int>& second,
	std::vector <int>& third, std::vector <int>& fourth); // ������� ����������� ������� � rgb �������
	void define_center_position(sf::Text& operation, unsigned int& width, float pos_y);
	void define_center_position(sf::RectangleShape& rectangle, unsigned int& width, float pos_y);

public:
	graph_menu(functions* f) : Func(f) {}

	bool window(); // ������� ��� �������� ����, ��������� ����������� � ��������� �������
	void window_message(std::string message, std::string banner);
	void plot(); // ������� ��� ������ �������
	void table(); // ������� ��� ������ �������
};


