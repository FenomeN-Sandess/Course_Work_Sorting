#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector> 
#include <string>
#include "graph_menu.h"

// Для меню
void graph_menu::mouse_response_button(sf::Vector2i& mouse_pos,
	std::vector <sf::Color>& rgb, int& iter, int& count)
{
	bool contain = is_there_cursor(g.texts.at(iter), mouse_pos); // 
	if (contain) { //Проверка, находится ли курсор в области этого прямоугольника
		sf::Color border_color(border_color_button[0], border_color_button[1], border_color_button[2]);
		g.texts.at(iter).setFillColor(rgb.at(count));
		g.texts.at(iter).setOutlineThickness(border_size_button);
		g.texts.at(iter).setOutlineColor(border_color);
	}
	else { // Возврат настроек по умолчанию. Из документации SFML
		g.texts.at(iter).setFillColor(rgb.at(count + 2));
		g.texts.at(iter).setOutlineThickness(0);
		g.texts.at(iter).setOutlineColor(sf::Color::Black);
	}
}

void graph_menu::definition_button_texts(std::vector <sf::Color>& rgb_default)
{
	int start_value = 0;
	for (int j = 2; j >= 1; j--)
	{
		for (int i = start_value; i < text_operation.size() / j; i++) {
			sf::Text operation;
			set_decoration_text(operation, g.font, size_font, g.rgb[j + 1]);
			operation.setString(text_operation.at(i));
			operation.setPosition(operation.getPosition().x, position_operation_y );
			define_center_position_x(operation, windowWidth);
			operation.setPosition(operation.getPosition().x, operation.getPosition().y + (g.count++) * padding_bottom_operation);
			g.texts.push_back(operation);
		}	start_value += 4;
	} g.count = 0;
}

void graph_menu::set_button(std::vector <sf::Text>& texts, sf::Vector2i& mouse_pos)
{
	for (auto text : texts) {
		if (is_there_cursor(text, mouse_pos)) {
			switch (define_index(text, texts, g.count = 0))
			{
			case 0:
				this->active_button = buttons::generate;
				break;
			case 1:
				this->active_button = buttons::calculate;
				break;
			case 2:
				this->active_button = buttons::save;
				break;
			case 3:
				this->active_button = buttons::download;
				break;
			case 4:
				this->active_button = buttons::table;
				break;
			case 5:
				this->active_button = buttons::plot;
				break;
			case 6:
				this->active_button = buttons::restart;
				break;
			case 7:
				this->active_button = buttons::quit;
				break;
			case -1:
				this->active_button = buttons::none;
				break;
			}
		}
	}
}

// Общие

void graph_menu::define_center_position_window(sf::RenderWindow& window, sf::Vector2i& external_window_position, sf::Vector2i& external_window_size)
{	
	int left_border = external_window_position.x; // Позиция Левой границы внешнего окна
	int right_border = left_border + external_window_size.x; // Правая граница
	int top_border = external_window_position.y; // Верхняя граница
	int button_border = top_border + external_window_size.y; // Нижняя граница 
	float Center_X = left_border + (right_border - left_border)/ 2.0f;
	float Center_Y = top_border + (button_border - top_border) / 2.0f;
	window.setPosition(sf::Vector2i (Center_X - window.getSize().x / 2.0f, Center_Y - window.getSize().y / 2.0f));
}

int graph_menu::define_index(sf::Text& elem, std::vector<sf::Text>& vector, int count)
{
	for (auto iter : vector) {
		if (elem.getString() == iter.getString()) { return count; }
		count += 1;
	}
	return -1;
}



void graph_menu::download_font(sf::Font& font, std::string& str)
{
	if (!font.loadFromFile(str))
	{
		std::cout << "error" << std::endl;
	}
}

void graph_menu::download_image(sf::Texture& texture, const std::string& str)
{
	if (!texture.loadFromFile(str)) {
		std::cout << "error" << std::endl;
	}

}

void graph_menu::set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color& color)
{
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(color);
}

void graph_menu::set_decoration_rectangle(sf::RectangleShape& rectangle, sf::Vector2f& size, float& outline_thickness, sf::Color& outline_color, sf::Color& theFill_color)
{
	rectangle.setSize(size);
	rectangle.setOutlineThickness(outline_thickness);
	rectangle.setOutlineColor(outline_color);
	rectangle.setFillColor(theFill_color);
}

std::vector <sf::Color> graph_menu::definition_color(std::vector <int>& first, std::vector <int>& second,
	std::vector <int>& third, std::vector <int>& fourth)
{
	sf::Color rgb_default_1(first[0], first[1], first[2], first[3]);
	sf::Color rgb_default_2(second[0], second[1], second[2], second[3]);
	sf::Color rgb_following_1(third[0], third[1], third[2], fourth[3]);
	sf::Color rgb_following_2(fourth[0], fourth[1], fourth[2], fourth[3]);
	return { rgb_default_2, rgb_default_1, rgb_following_2, rgb_following_1 };
}