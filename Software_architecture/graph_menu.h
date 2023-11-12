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

	// Объявление констант и объектов
	buttons active_button;
	buttons get_button() {return active_button;}
	void set_button(std::vector <sf::Text>& texts, sf::Vector2i& mouse_pos);
	void set_button(buttons button) {this->active_button = button; } 
	sf::Font font; // Объект шрифта
	sf::Font font_window;
	sf::Sprite background_sprite; // Спрайт фона
	sf::Texture background_texture; // Текстура фона
	std::vector<sf::Text> texts; // Вектор объектов текст
	std::vector <sf::Color> rgb; // Вектор цветов
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); // Получение разрешения экрана
	unsigned int screenWidth = desktop.width; // Ширина экрана
	unsigned int screenHeight = desktop.height; // Высота экрана
	int define_index(sf::Text& elem, std::vector <sf::Text>& vector, int count); /*Определение индекса элемента типа Text в векторе*/
	unsigned int fps = 144;
	int count = 0; //Счётчик
	bool isDragging;
	sf::Vector2i start_position;
	sf::Vector2i current_position;
	sf::Vector2i delta;

	// Типы для управления графикой
	std::string background_img = "background_4.jpg"; // Картинка фона
	unsigned int windowWidth = static_cast<unsigned int>(screenWidth * 0.3); // Ширина окна
	unsigned int windowHeight = static_cast<unsigned int>(screenHeight * 0.7); // Высота окна
	unsigned int windowMessageWidth = static_cast<unsigned int>(screenWidth * 0.2); //Ширина окна с сообщением
	unsigned int windowMessageHeight = static_cast<unsigned int>(screenHeight * 0.15); // Высота окна с сообщением
	float position_message_y = windowMessageHeight * 0.25f; // Позиция сообщения по оси OY
	float position_agreement_y = windowMessageHeight * 0.6f; // Позиции  ok по оси OY
	float position_operation_y = windowHeight * 0.11f; // Отступ кнопок сверху вниз
	float padding_bottom_operation = windowHeight * 0.1f; // Отступы снизу
	std::vector <std::string> text_operation = { "Generate", "Calculate", "Save", "Download",
		"Display the table", "Display a plot", "Restart", "Quit"}; // Наименование кнопок в графическом окне
	unsigned int size_font = static_cast<unsigned int>(windowWidth / 15); // Размер кнопок
	unsigned int size_font_message = static_cast<unsigned int>(windowMessageWidth / 20);
	std::string str_font = "JosefinSans-Bold.ttf"; // Используемый шрифт в меню
	std::string str_font_window = "Roboto-Light.ttf"; // Используемый шрифт в окне
	std::vector <int> custom_color_button = { 102, 255, 255, 190 }; // Цвет первых четырех кнопок по умолчанию
	std::vector <int> second_custom_color_button = { 255, 102, 255, 190 }; // Цвет следующий четырех кнопок
	std::vector <int> event_color_button = { 102, 255, 255, 255 }; // Цвет кнопок при наведении первых четырех кнопок
	std::vector <int> second_event_color_button = { 255, 102, 255, 255 }; // Цвет кнопок при наведении вторых четырех кнопок
	std::vector <int> border_color_button = { 0, 0, 0 }; // Цвет границы у кнопок
	float border_size_button = 3; // Размер границ у кнопок

	//Методы
	bool is_there_cursor(sf::Text& text, sf::Vector2i& mouse_pos); // Функция показывающая находится ли курсор в данной области
	void download_font(sf::Font& font, std::string& str); // Подгрузка шрифта из файла
	void download_image(sf::Texture& texture, const std::string& str); // Загрузка картинки в текстуру
	void set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color &color);
	void definition_button_texts(std::vector <sf::Color>& rgb_default); // Описание операций в меню
	void mouse_response_button(sf::Vector2i& mouse_pos,	std::vector <sf::Color>& rgb,
	int& iter, int& count); // Функция описывающая событие, возникающее при наведении на кнопку курсора
	std::vector <sf::Color> definition_color(std::vector <int>& first, std::vector <int>& second,
	std::vector <int>& third, std::vector <int>& fourth); // Функция определения вектора с rgb цветами
	void define_center_position(sf::Text& operation, unsigned int& width, float pos_y);
	void define_center_position(sf::RectangleShape& rectangle, unsigned int& width, float pos_y);

public:
	graph_menu(functions* f) : Func(f) {}

	bool window(); // Функция для создания окна, отрисовки содержимого и обработки событий
	void window_message(std::string message, std::string banner);
	void plot(); // Функция для вывода графика
	void table(); // Функция для вывода таблицы
};


