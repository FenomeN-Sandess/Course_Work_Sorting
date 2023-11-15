#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector> 
#include <string>
#include "graph_menu_global.h"


// Общие

void global::define_center_position_window(sf::RenderWindow& window, sf::Vector2i& external_window_position, sf::Vector2i& external_window_size)
{	
	int left_border = external_window_position.x; // Позиция Левой границы внешнего окна
	int right_border = left_border + external_window_size.x; // Правая граница
	int top_border = external_window_position.y; // Верхняя граница
	int button_border = top_border + external_window_size.y; // Нижняя граница 
	float Center_X = left_border + (right_border - left_border)/ 2.0f;
	float Center_Y = top_border + (button_border - top_border) / 2.0f;
	window.setPosition(sf::Vector2i (Center_X - window.getSize().x / 2.0f, Center_Y - window.getSize().y / 2.0f));
}

int global::define_index(sf::Text& elem, std::vector<sf::Text>& vector, int count)
{
	for (auto iter : vector) {
		if (elem.getString() == iter.getString()) { return count; }
		count += 1;
	}
	return -1;
}

void global::download_font(sf::Font& font, std::string& str)
{
	if (!font.loadFromFile(str))
	{
		std::cout << "error" << std::endl;
	}
}

void global::download_image(sf::Texture& texture, const std::string& str)
{
	if (!texture.loadFromFile(str)) {
		std::cout << "error" << std::endl;
	}

}

void global::set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color& color)
{
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(color);
}

void global::set_decoration_rectangle(sf::RectangleShape& rectangle, sf::Vector2f& size, float& outline_thickness, sf::Color& outline_color, sf::Color& theFill_color)
{
	rectangle.setSize(size);
	rectangle.setOutlineThickness(outline_thickness);
	rectangle.setOutlineColor(outline_color);
	rectangle.setFillColor(theFill_color);
}

void global::download_backround(std::string background_img, unsigned int windowWidth, unsigned int windowHeight )
{
	download_image(background_texture, background_img); // Подгрузка фон
	background_sprite.setTexture(background_texture); // Устанавливаем фон в sprite 
	background_sprite.setScale((static_cast<float>(windowWidth) / background_texture.getSize().x), // Определяем размеры спрайта под область окна
		(static_cast<float>(windowHeight) / background_texture.getSize().y)); // Из документации SFML: размер текстуры равен (1,1) - растягиваем текстуру на весь размер окна

}


