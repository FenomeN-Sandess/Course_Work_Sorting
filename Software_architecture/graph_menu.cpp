
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector> 
#include <string>
#include "graph_menu.h"

void graph_menu::window_message(std::string message, std::string banner, sf::Vector2i window_pos)
{
	g.download_font(g.font_window, str_font_window);
	sf::RenderWindow window_message(sf::VideoMode(windowMessageWidth, windowMessageHeight), banner, sf::Style::None); //Создание окна
	window_message.setFramerateLimit(g.fps);
	sf::Vector2i window_size(windowWidth, windowHeight);
	g.define_center_position_window(window_message, window_pos, window_size);

	sf::RectangleShape rectangle;
	sf::Color color_rectangle_anim(rectangle_theFill_color_animation.at(0),
		rectangle_theFill_color_animation.at(1), rectangle_theFill_color_animation.at(2),
		rectangle_theFill_color_animation.at(3));
	sf::Color rec_cl_outline (rectangle_outline_color[0], rectangle_outline_color[1],
		rectangle_outline_color[2], rectangle_outline_color[3]);
	sf::Vector2f rectangle_size (rectangle_window_size[0], rectangle_window_size[1]);
	g.set_decoration_rectangle(rectangle, rectangle_size, rectangle_outline_thickness,
		rec_cl_outline, rectangle_theFill_color);
	define_center_position_x(rectangle, windowMessageWidth);
	rectangle.setPosition(rectangle.getPosition().x, position_rectangle_y);
	sf::Text msg; sf::Text ok;

	ok.setString("ok"); msg.setString(message);
	sf::Color agr_outline_color(64,64,64);
	g.set_decoration_text(ok, g.font_window, size_font_message, sf::Color::Black);
	g.set_decoration_text(msg, g.font_window, size_font_message, sf::Color::Black);
	define_center_position_x(msg, windowMessageWidth);	
	define_center_position_area_text(ok, g.font_window, size_font_message, rectangle);
	
	msg.setPosition(msg.getPosition().x, position_message_y);

	while (window_message.isOpen()) { //Главный цикл - заканчивается, как только окно закрыто
		sf::Event event; //Обработка событий

		while (window_message.pollEvent(event)) {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_message); // Определение позиции мыши
			bool contain = is_there_cursor(rectangle, mouse_pos);
			switch (event.type) {
			case sf::Event::Closed: // Закрытие окна при нажатии на кнопку закрытия
				window_message.close();
				break;
			case sf::Event::MouseMoved: // Обработка событий движения мыши
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

		window_message.setActive(); //Активация окна для отрисовки
		window_message.clear(sf::Color::White);

		window_message.draw(rectangle);
		window_message.draw(ok);
		window_message.draw(msg);


		window_message.display(); //Вывод
	}
}

bool graph_menu::window()
{
	g.download_image(g.background_texture, background_img); // Подгрузка фон
	g.download_font(g.font, str_font); // Подгрузка шрифта
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "MENU", sf::Style::None); //Создание окна
	window.setFramerateLimit(g.fps); // Ограничение частоты кадров до 60 кадров в секунду
	g.background_sprite.setTexture(g.background_texture); // Устанавливаем фон в sprite 
	g.background_sprite.setScale((static_cast<float>(windowWidth) / g.background_texture.getSize().x), // Определяем размеры спрайта под область окна
	(static_cast<float>(windowHeight) / g.background_texture.getSize().y)); // Из документации SFML: размер текстуры равен (1,1) - растягиваем текстуру на весь размер окна
	g.rgb = definition_color(event_color_button, second_event_color_button, custom_color_button, second_custom_color_button); // Массив со всеми цветами
	definition_button_texts(g.rgb); // Описание тестовых объектов в меню

	while (window.isOpen()) { //Главный цикл - заканчивается, как только окно закрыто
		sf::Event event; //Обработка событий
		while (window.pollEvent(event)) {
			set_button(buttons::none); // enum по умолчанию
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); // Определение позиции мыши
			sf::Vector2i window_pos = window.getPosition();
			switch (event.type) {
			case sf::Event::Closed: // Закрытие окна при нажатии на кнопку закрытия
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					g.isDragging = false;
				}
				break;
			case sf::Event::MouseMoved: // Обработка событий движения мыши
				g.count = 1; // Снова приходит на помощь счётчик. 
				for (int iter = 0; iter < 8; iter++) {
					if ((iter > 3) && (g.count > 0)) g.count -= 1;
					mouse_response_button(mouse_pos, g.rgb, iter, g.count); // При наведении появляется графический эффект
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
						Func->generate();
						window_message("Generation completed", "Message Generation", window_pos);
						break;
					case (buttons::calculate):
						Func->sorting();

						window_message("Calculating completed", "Message Calculating", window_pos);
						break;
					case (buttons::save):
						Func->saving();
						window_message("Saving completed", "Message Saving", window_pos);
						break;
					case (buttons::download):
						Func->downloading();
						window_message("Downloading completed", "Message Saving", window_pos);
						break;
					case (buttons::table):
						t.table();
						break;
					case (buttons::plot):
						if (Func->empty_data()) window_message("Download data", "Error", window_pos);
						else p.plot();
						//Func->display();
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
		window.setActive(); //Активация окна для отрисовки
		window.clear();
		window.draw(g.background_sprite);
		for (const auto& text : g.texts) {
			window.draw(text);
		}
		window.display(); //Вывод
	}
	return false;
}

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
			g.set_decoration_text(operation, g.font, size_font, g.rgb[j + 1]);
			operation.setString(text_operation.at(i));
			operation.setPosition(operation.getPosition().x, position_operation_y);
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
			switch (g.define_index(text, texts, g.count = 0))
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

std::vector <sf::Color> graph_menu::definition_color(std::vector <int>& first, std::vector <int>& second,
	std::vector <int>& third, std::vector <int>& fourth)
{
	sf::Color rgb_default_1(first[0], first[1], first[2], first[3]);
	sf::Color rgb_default_2(second[0], second[1], second[2], second[3]);
	sf::Color rgb_following_1(third[0], third[1], third[2], fourth[3]);
	sf::Color rgb_following_2(fourth[0], fourth[1], fourth[2], fourth[3]);
	return { rgb_default_2, rgb_default_1, rgb_following_2, rgb_following_1 };
}