#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <string>
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


class menu_control {
protected:
	buttons active_button;
	buttons get_button() {return active_button;}
	void set_button(std::vector <sf::Text>& texts, sf::Vector2i& mouse_pos);
	void set_button(buttons button) {this->active_button = button; }
	int define_index(sf::Text& elem, std::vector <sf::Text>& vector, int count);
	int count = 0; //Счётчик
	sf::Font font; // Объект шрифта
	sf::Sprite background_sprite;
	sf::Texture background_texture;
	std::vector<sf::Text> texts; // Вектор объектов текст
	std::vector <sf::Color> rgb; // Вектор цветов
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); // Получение разрешения экрана
	unsigned int screenWidth = desktop.width; // Ширина экрана
	unsigned int screenHeight = desktop.height; // Высота экрана
	unsigned int windowWidth = static_cast<unsigned int>(screenWidth * 0.3); // Ширина окна
	unsigned int windowHeight = static_cast<unsigned int>(screenHeight * 0.7); // Высота окна
	std::string background_img = "background_4.jpg"; // Картинка рабочего стола
	unsigned int fps = 144;

	std::vector <std::string> text_operation = { "Generate", "Calculate", "Save", "Download",
		"Display the table", "Display a plot", "Restart", "Quit"};
	unsigned int size_font = windowWidth/15; // Размер кнопок
	float position_operation_x = windowWidth * 0.35f; // Позиции кнопок по OX
	float position_opertation_y = windowHeight * 0.11f; // По OY
	float padding_bottom_operation = windowHeight * 0.1f; // Отступы снизу
	std::string str_font = "JosefinSans-Bold.ttf"; // Используемый шрифт
	std::vector <int> custom_color_button = { 102, 255, 255, 190 }; // Цвет первых четырех кнопок по умолчанию
	std::vector <int> second_custom_color_button = { 255, 102, 255, 190 }; // Цвет следующий четырех кнопок
	std::vector <int> event_color_button = { 102, 255, 255, 255 }; // Цвет кнопок при наведении первых четырех кнопок
	std::vector <int> second_event_color_button = { 255, 102, 255, 255 }; // Цвет кнопок при наведении вторых четырех кнопок
	std::vector <int> border_color_button = { 0, 0, 0 }; // Цвет границы у кнопок
	float border_size_button = 3; // Размер границ у кнопок

	bool is_there_cursor(sf::Text& text, sf::Vector2i& mouse_pos); // Функция показывающая находится ли курсор в данной области
	void download_font(std::string& str); // Подгрузка шрифта из файла
	void download_image(sf::Texture& texture, const std::string& str);
	void set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color &color);
	void definition_button_texts(std::vector <sf::Color>& rgb_default); // Описание операций в меню
	void mouse_response_button(sf::Vector2i& mouse_pos,	std::vector <sf::Color>& rgb,
		int& iter, int& count); // Функция описывающая событие, возникающее при наведении
	//на кнопку курсора
	void click_response_button(); // функция, описывающая событие, возникающее при нажатии на кнопку 

	std::vector <sf::Color> definition_color(std::vector <int>& first, std::vector <int>& second,
		std::vector <int>& third, std::vector <int>& fourth);

public:

	void window(); // Функция для создания окна, отрисовки содержимого и обработки собыnbq
	void plot(); // Функция для вывода графика
	void table(); // Функция для вывода таблицы
};


