#include <SFML/Graphics.hpp>
#include <string>
#pragma once



class menu_control {
protected:
	int count = 0; //Счётчик

	sf::Font font; // Объект шрифта
	sf::Sprite background_sprite;
	sf::Texture background_texture;
	std::vector<sf::Text> texts; // Вектор объектов текст
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); // Получение разрешения экрана
	unsigned int screenWidth = desktop.width; // Ширина экрана
	unsigned int screenHeight = desktop.height; // Высота экрана
	unsigned int windowWidth = screenWidth*0.3; // Ширина окна
	unsigned int windowHeight = screenHeight*0.7; // Высота окна
	std::string background_img = "background_2.jpeg"; // Картинка рабочего стола
	unsigned int fps = 60;

	std::vector <std::string> text_operation = { "Generate", "Calculate", "Save", "Download", "Display the table", "Display a plot", "Quit" };
	unsigned int size_font = windowWidth/15;
	float position_operation_x = windowWidth*0.35f; 
	float position_opertation_y = windowHeight*0.15f;
	float padding_bottom_operation = windowHeight*0.1f;
	std::string str_font = "Montserrat-Bold.ttf"; // Используемый шрифт
	

	void download_font(std::string& str); // Подгрузка шрифта из файла
	void download_image(sf::Texture& texture, const std::string& str);
	void set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color &color);
	void choice_texts(); // Описание операций в меню


public:

	void window(); // Функция для создания окна и отрисовки содержимого
	void plot(); // Функция для вывода графика
	void table(); // Функция для вывода таблицы
};


