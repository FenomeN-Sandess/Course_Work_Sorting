
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector> 
#include <string>

#include "menu_control.h"

// �������������� ������


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

// �������� ������
void menu_control::window()
{
	download_image(background_texture, background_img); // ��������� ���

	background_sprite.setTexture(background_texture);

	download_font(str_font); // ��������� ������
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "MENU", sf::Style::Titlebar | sf::Style::Close); //�������� ����
	window.setFramerateLimit(fps); // ����������� ������� ������ �� 60 ������ � �������

	background_sprite.setPosition(0, 0);
	background_sprite.setScale(windowWidth,windowHeight);

	choice_texts();

	while (window.isOpen()) { //������� ���� - �������������, ��� ������ ���� �������
		sf::Event event; //��������� �������
		while (window.pollEvent(event)) {//�������� ���� ��� ������� �� ������ ��������
			if (event.type == sf::Event::Closed) window.close();
		}

		window.setActive(); //��������� ���� ��� ���������
		window.clear(sf::Color::White);

		window.draw(background_sprite);

		for (const auto& text : texts) {
			window.draw(text);
		}

		window.display(); //�����
	}
}

void menu_control::plot()
{
}

void menu_control::table()
{
}
