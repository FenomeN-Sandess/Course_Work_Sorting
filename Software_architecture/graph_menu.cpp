
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector> 
#include <string>
#include "graph_menu.h"


void graph_menu::window_message(std::string message, std::string banner, sf::Vector2i window_pos)
{
	download_font(g.font_window, str_font_window);
	sf::RenderWindow window_message(sf::VideoMode(windowMessageWidth, windowMessageHeight), banner, sf::Style::None); //�������� ����
	window_message.setFramerateLimit(fps);
	sf::Vector2i window_size(windowWidth, windowHeight);
	define_center_position_window(window_message, window_pos, window_size);

	sf::RectangleShape rectangle;
	sf::Color color_rectangle_anim(rectangle_theFill_color_animation.at(0),
		rectangle_theFill_color_animation.at(1), rectangle_theFill_color_animation.at(2),
		rectangle_theFill_color_animation.at(3));
	sf::Color rec_cl_outline (rectangle_outline_color[0], rectangle_outline_color[1],
		rectangle_outline_color[2], rectangle_outline_color[3]);
	sf::Vector2f rectangle_size (rectangle_window_size[0], rectangle_window_size[1]);
	set_decoration_rectangle(rectangle, rectangle_size, rectangle_outline_thickness,
		rec_cl_outline, rectangle_theFill_color);
	define_center_position_x(rectangle, windowMessageWidth);
	rectangle.setPosition(rectangle.getPosition().x, position_rectangle_y);
	sf::Text msg; sf::Text ok;

	ok.setString("ok"); msg.setString(message);
	sf::Color agr_outline_color(64,64,64);
	set_decoration_text(ok, g.font_window, size_font_message, sf::Color::Black);
	set_decoration_text(msg, g.font_window, size_font_message, sf::Color::Black);
	define_center_position_x(msg, windowMessageWidth);	
	define_center_position_area_text(ok, g.font_window, size_font_message, rectangle);
	
	msg.setPosition(msg.getPosition().x, position_message_y);

	while (window_message.isOpen()) { //������� ���� - �������������, ��� ������ ���� �������
		sf::Event event; //��������� �������

		while (window_message.pollEvent(event)) {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_message); // ����������� ������� ����
			bool contain = is_there_cursor(rectangle, mouse_pos);
			switch (event.type) {
			case sf::Event::Closed: // �������� ���� ��� ������� �� ������ ��������
				window_message.close();
				break;
			case sf::Event::MouseMoved: // ��������� ������� �������� ����
				if (contain) {
					ok.setOutlineThickness(border_size_button_window);
					ok.setOutlineColor(agr_outline_color);
					rectangle.setFillColor(color_rectangle_anim);
					sf::Color outline_color(0, 0, 255, 100); rectangle.setOutlineColor(outline_color);
				}
				else {
					ok.setOutlineThickness(0);
					rectangle.setOutlineColor(rec_cl_outline);
					rectangle.setFillColor(rectangle_theFill_color);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if ((event.mouseButton.button == sf::Mouse::Left) && contain) {
					window_message.close();
				}
				break;
			}
		} 

		window_message.setActive(); //��������� ���� ��� ���������
		window_message.clear(sf::Color::White);

		window_message.draw(rectangle);
		window_message.draw(ok);
		window_message.draw(msg);


		window_message.display(); //�����
	}
}

bool graph_menu::window()
{
	download_image(g.background_texture, background_img); // ��������� ���
	download_font(g.font, str_font); // ��������� ������
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "MENU", sf::Style::None); //�������� ����
	window.setFramerateLimit(fps); // ����������� ������� ������ �� 60 ������ � �������
	g.background_sprite.setTexture(g.background_texture); // ������������� ��� � sprite 
	g.background_sprite.setScale((static_cast<float>(windowWidth) / g.background_texture.getSize().x), // ���������� ������� ������� ��� ������� ����
	(static_cast<float>(windowHeight) / g.background_texture.getSize().y)); // �� ������������ SFML: ������ �������� ����� (1,1) - ����������� �������� �� ���� ������ ����
	g.rgb = definition_color(event_color_button, second_event_color_button, custom_color_button, second_custom_color_button); // ������ �� ����� �������
	definition_button_texts(g.rgb); // �������� �������� �������� � ����

	while (window.isOpen()) { //������� ���� - �������������, ��� ������ ���� �������
		sf::Event event; //��������� �������
		while (window.pollEvent(event)) {
			set_button(buttons::none); // enum �� ���������
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); // ����������� ������� ����
			sf::Vector2i window_pos = window.getPosition();
			switch (event.type) {
			case sf::Event::Closed: // �������� ���� ��� ������� �� ������ ��������
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					g.isDragging = false;
				}
				break;
			case sf::Event::MouseMoved: // ��������� ������� �������� ����
				g.count = 1; // ����� �������� �� ������ �������. 
				for (int iter = 0; iter < 8; iter++) {
					if ((iter > 3) && (g.count > 0)) g.count -= 1;
					mouse_response_button(mouse_pos, g.rgb, iter, g.count); // ��� ��������� ���������� ����������� ������
				}
				if (g.isDragging) {
					g.current_position = sf::Mouse::getPosition();
					g.delta = g.current_position - g.start_position;
					window.setPosition(window.getPosition() + g.delta);
					g.start_position = g.current_position;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if ((event.mouseButton.button == sf::Mouse::Left)) {
					
					set_button(g.texts, mouse_pos);
					if (get_button() == buttons::none) {
						g.isDragging = true;
						g.start_position = sf::Mouse::getPosition();
					}
					switch (get_button())
					{
					case (buttons::generate):
						window_message("Generation completed", "Message Generation", window_pos);
						Func->generate();
						break;
					case (buttons::calculate):
						window_message("Calculating completed", "Message Calculating", window_pos);
						Func->sorting();
						break;
					case (buttons::save):
						window_message("Saving completed", "Message Saving", window_pos);
						Func->saving();
						break;
					case (buttons::download):
						window_message("downloading completed", "Message Saving", window_pos);
						Func->downloading();
						break;
					case (buttons::table):
						Func->show();
						break;
					case (buttons::plot):
						Func->display();
						break;
					case (buttons::restart):
						Func->reset_data();
						return true;
						break;
					case (buttons::quit):
						window.close();
						break;
					case (buttons::none):
						break;
					}
				}
				break;
			} g.count = 0;
		}
		window.setActive(); //��������� ���� ��� ���������
		window.clear();
		window.draw(g.background_sprite);
		for (const auto& text : g.texts) {
			window.draw(text);
		}
		window.display(); //�����
	}
	return false;
}

void graph_menu::plot()
{
}

void graph_menu::table()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Table"); //�������� ����
	window.setFramerateLimit(fps); // ����������� ������� ������ �� 60 ������ � �������
	while (window.isOpen()) { //������� ���� - �������������, ��� ������ ���� �������
		sf::Event event; //��������� �������
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: // �������� ���� ��� ������� �� ������ ��������
				window.close();
				break;
		}
		window.setActive(); //��������� ���� ��� ���������
		window.clear();
		for (const auto& text : g.texts) {
			window.draw(text);
		}
		window.display(); //�����

}





