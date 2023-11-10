
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector> 
#include <string>

#include "menu_control.h"

// Второстепенные методы


void menu_control::download_font(std::string& str)
{
	if (!font.loadFromFile(str))
	{
		std::cout << "error" << std::endl;
	}
}

void menu_control::download_image(sf::Texture& texture, const std::string& str)
{
	if (!texture.loadFromFile(str)) {
		std::cout << "error" << std::endl;
	}
	else std::cout << "it works" << std::endl;
}


void menu_control::set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color& color)
{
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(color);
}

void menu_control::choice_texts()
{
	for (auto &i : text_operation) {

		sf::Text operation; 
		set_decoration_text(operation, font, size_font, sf::Color::Black);
		operation.setString(i);
		float Center_X = windowWidth/2.0f;
		sf::FloatRect textBounds = operation.getLocalBounds();
		operation.setPosition(Center_X - textBounds.width/2.0f, position_opertation_y + (count++) * padding_bottom_operation);
		texts.push_back(operation);
	}
	count = 0;
}

// Основные методы
void menu_control::window()
{
	download_image(background_texture, background_img); // Подгрузка фон

	background_sprite.setTexture(background_texture);

	download_font(str_font); // Подгрузка шрифта
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "MENU", sf::Style::Titlebar | sf::Style::Close); //Создание окна
	window.setFramerateLimit(fps); // Ограничение частоты кадров до 60 кадров в секунду

	background_sprite.setPosition(0, 0);
	background_sprite.setScale(windowWidth,windowHeight);

	choice_texts();

	while (window.isOpen()) { //Главный цикл - заканчивается, как только окно закрыто
		sf::Event event; //Обработка событий
		while (window.pollEvent(event)) {//Закрытие окна при нажатии на кнопку закрытия
			if (event.type == sf::Event::Closed) window.close();
		}

		window.setActive(); //Активация окна для отрисовки
		window.clear(sf::Color::White);

		window.draw(background_sprite);

		for (const auto& text : texts) {
			window.draw(text);
		}

		window.display(); //Вывод
	}
}

void menu_control::plot()
{
}

void menu_control::table()
{
}
