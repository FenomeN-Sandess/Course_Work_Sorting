#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <type_traits>
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

struct global
{
	functions* Func;
	global(functions* f) : Func(f) {}

	// Объявление констант и объектов
	sf::Font font; // Объект шрифта
	sf::Font font_window; // Объект шрифта в диалоговом окне
	sf::Sprite background_sprite; // Спрайт фона
	sf::Texture background_texture; // Текстура фона
	std::vector<sf::Text> texts; // Вектор объектов текст
	std::vector <sf::Color> rgb; // Вектор цветов
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); // Получение разрешения экрана
	unsigned int screenWidth = desktop.width; // Ширина экрана
	unsigned int screenHeight = desktop.height; // Высота экрана
	int count = 0; //Счётчик
	bool isDragging; // Булевая переменная, показывающая, нажимается ли левая кнопка мыши
	sf::Vector2i start_position; sf::Vector2i current_position; sf::Vector2i delta; // Векторные объекты для изменения позиции окна
}; 

class graph_menu {
private:
	functions* Func;
	global g;
	buttons active_button;
	buttons get_button() { return active_button; }
	void set_button(buttons button) { this->active_button = button; }
	void set_button(std::vector <sf::Text>& texts, sf::Vector2i& mouse_pos);
protected:
	// объекты для управления графикой
	unsigned int fps = 144;
	std::string background_img = "background_4.jpg"; // Картинка фона
	unsigned int windowWidth = static_cast<unsigned int>(g.screenWidth * 0.3); // Ширина окна
	unsigned int windowHeight = static_cast<unsigned int>(g.screenHeight * 0.7); // Высота окна
	unsigned int windowMessageWidth = static_cast<unsigned int>(g.screenWidth * 0.2); //Ширина окна с сообщением
	unsigned int windowMessageHeight = static_cast<unsigned int>(g.screenHeight * 0.15); // Высота окна с сообщением
	unsigned int windowTableWidth = static_cast<unsigned int>(g.screenWidth * 0.4); // Высота окна с сообщением
	unsigned int windowTableHeight = static_cast<unsigned int>(g.screenHeight * 0.4); // Высота окна с сообщением
	
	std::vector <std::string> text_operation = { "Generate", "Calculate", "Save", "Download",
	"Display the table", "Display a plot", "Restart", "Quit" }; // Наименование кнопок в графическом окне
	std::string str_font = "JosefinSans-Bold.ttf"; // Используемый шрифт в меню
	std::string str_font_window = "Kanit-Thin.ttf"; // Используемый шрифт в окне

	float position_operation_y = windowHeight * 0.11f; // Отступ кнопок сверху вниз
	float padding_bottom_operation = windowHeight * 0.1f; // Отступы снизу
	float position_message_y = windowMessageHeight * 0.35f; // Позиция сообщения по оси OY
	float position_agreement_y = windowMessageHeight * 0.7f; // Позиции ok по оси OY
	float position_rectangle_y = windowMessageHeight * 0.7f;

	unsigned int size_font = static_cast<unsigned int>(windowWidth / 15); // Размер шрифта в меню
	unsigned int size_font_message = static_cast<unsigned int>(windowMessageWidth / 20); // Размер шрифта в диалоговом окне
	float rectangle_outline_thickness = 2;
	float border_size_button = 3; // Размер границ у кнопок в главном меню
	float border_size_button_window = 0.1; // Размер границ у кнопок в диалоговом окне
	std::vector <float> rectangle_window_size = {
		static_cast<float>(size_font_message*4),
		static_cast<float>(size_font_message*1.2)
	};

	sf::Color rectangle_theFill_color = sf::Color::White;
	std::vector <int> custom_color_button = { 102, 255, 255, 190 }; // Цвет первых четырех кнопок по умолчанию
	std::vector <int> second_custom_color_button = { 255, 102, 255, 190 }; // Цвет следующий четырех кнопок
	std::vector <int> event_color_button = { 102, 255, 255, 255 }; // Цвет кнопок при наведении первых четырех кнопок
	std::vector <int> second_event_color_button = { 255, 102, 255, 255 }; // Цвет кнопок при наведении вторых четырех кнопок
	std::vector <int> border_color_button = { 0, 0, 0 }; // Цвет границы у кнопок
	std::vector <int> rectangle_theFill_color_animation = { 160,160,160,20 };
	std::vector <int> rectangle_outline_color = { 160,160,160,255 };

	// Общие, глобальные методы 
	void download_font(sf::Font& font, std::string& str); // Подгрузка шрифта из файла
	void download_image(sf::Texture& texture, const std::string& str); // Загрузка картинки в текстуру
	std::vector <sf::Color> definition_color(std::vector <int>& first, std::vector <int>& second,
	std::vector <int>& third, std::vector <int>& fourth); // Функция определения вектора с rgb цветами
	void set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color &color); // Декор текстового объекта
	void set_decoration_rectangle(sf::RectangleShape& rectangle, sf::Vector2f& size,
		float& outline_thickness, sf::Color& outline_color, sf::Color& theFill_color);
	int define_index(sf::Text& elem, std::vector <sf::Text>& vector, int count); /*Определение индекса элемента типа Text в векторе*/
	void define_center_position_window(sf::RenderWindow& window, sf::Vector2i& external_window_position, sf::Vector2i& external_window_size);

	// Методы, использующиеся для менюшки
	void definition_button_texts(std::vector <sf::Color>& rgb_default); // Описание операций в меню
	void mouse_response_button(sf::Vector2i& mouse_pos,	std::vector <sf::Color>& rgb,
	int& iter, int& count); // Функция описывающая событие, возникающее при наведении на кнопку курсора

public:
	graph_menu(functions* f) : Func(f), g(f) {}

	bool window(); // Функция для создания окна, отрисовки содержимого и обработки событий
	void window_message(std::string message, std::string banner, sf::Vector2i window_pos);
	void plot(); // Функция для вывода графика
	void table();	// Функция для вывода таблицы
};

#include "graph_menu_templates.cpp"