
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector> 
#include <string>
#include "graph_menu.h"



// Второстепенные методы

// Для меню
void graph_menu::mouse_response_button(sf::Vector2i& mouse_pos,
	std::vector <sf::Color>& rgb, int& iter, int& count)
{
	bool contain = is_there_cursor(texts.at(iter), mouse_pos); // 
	if (contain) { //Проверка, находится ли курсор в области этого прямоугольника
		sf::Color border_color(border_color_button[0], border_color_button[1], border_color_button[2]);
		texts.at(iter).setFillColor(rgb.at(count));
		texts.at(iter).setOutlineThickness(border_size_button);
		texts.at(iter).setOutlineColor(border_color);
	}
	else { // Возврат настроек по умолчанию. Из документации SFML
		texts.at(iter).setFillColor(rgb.at(count + 2));
		texts.at(iter).setOutlineThickness(0);
		texts.at(iter).setOutlineColor(sf::Color::Black);
	}
}

void graph_menu::definition_button_texts(std::vector <sf::Color>& rgb_default)
{
	int start_value = 0;
	for (int j = 2; j >= 1; j--)
	{
		for (int i = start_value; i < text_operation.size() / j; i++) {
			sf::Text operation;
			set_decoration_text(operation, font, size_font, rgb[j + 1]);
			operation.setString(text_operation.at(i));
			define_center_position(operation, windowWidth, position_operation_y);
			operation.setPosition(operation.getPosition().x, operation.getPosition().y + (count++) * padding_bottom_operation);
			texts.push_back(operation);
		}	start_value += 4;
	} count = 0;
}

void graph_menu::set_button(std::vector <sf::Text>& texts, sf::Vector2i& mouse_pos)
{
	for (auto text : texts) {
		if (is_there_cursor(text, mouse_pos)) {
			switch (define_index(text, texts, count = 0))
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
void graph_menu::define_center_position(sf::Text& text, unsigned int& width, float pos_y)
{
	float Center_X = width / 2.0f;
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setPosition(Center_X - textBounds.width / 2.0f, pos_y);
}
void graph_menu::define_center_position(sf::RectangleShape& rectangle, unsigned int& width, float pos_y) {
	float Center_X = width / 2.0f;
	sf::FloatRect rectangleBounds = rectangle.getLocalBounds();
	rectangle.setPosition(Center_X - rectangleBounds.width / 2.0f, pos_y);
}

int graph_menu::define_index(sf::Text& elem, std::vector<sf::Text>& vector, int count)
{
	for (auto iter : vector) {
		if (elem.getString() == iter.getString()) { return count; }
		count += 1;
	}
	return -1;
}

bool graph_menu::is_there_cursor(sf::Text& text, sf::Vector2i& mouse_pos)
{
	sf::FloatRect textBounds = text.getGlobalBounds();  // Объект прямоугольника, заполненного числами Float
	return textBounds.contains(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
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

std::vector <sf::Color> graph_menu::definition_color(std::vector <int>& first, std::vector <int>& second,
	std::vector <int>& third, std::vector <int>& fourth)
{
	sf::Color rgb_default_1(first[0], first[1], first[2], first[3]);
	sf::Color rgb_default_2(second[0], second[1], second[2], second[3]);
	sf::Color rgb_following_1(third[0], third[1], third[2], fourth[3]);
	sf::Color rgb_following_2(fourth[0], fourth[1], fourth[2], fourth[3]);
	return { rgb_default_2, rgb_default_1, rgb_following_2, rgb_following_1 };
}

// Основные методы
bool graph_menu::window()
{
	download_image(background_texture, background_img); // Подгрузка фон
	download_font(font, str_font); // Подгрузка шрифта
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "MENU", sf::Style::None); //Создание окна
	window.setFramerateLimit(fps); // Ограничение частоты кадров до 60 кадров в секунду
	background_sprite.setTexture(background_texture); // Устанавливаем фон в sprite 
	background_sprite.setScale((static_cast<float>(windowWidth) / background_texture.getSize().x), // Определяем размеры спрайта под область окна
	(static_cast<float>(windowHeight) / background_texture.getSize().y)); // Из документации SFML: размер текстуры равен (1,1) - растягиваем текстуру на весь размер окна
	rgb = definition_color(event_color_button, second_event_color_button, custom_color_button, second_custom_color_button); // Массив со всеми цветами
	definition_button_texts(rgb); // Описание тестовых объектов в меню

	while (window.isOpen()) { //Главный цикл - заканчивается, как только окно закрыто
		sf::Event event; //Обработка событий
		while (window.pollEvent(event)) {
			set_button(buttons::none); // enum по умолчанию
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); // Определение позиции мыши
			switch (event.type) {
			case sf::Event::Closed: // Закрытие окна при нажатии на кнопку закрытия
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					isDragging = false;
				}
				break;
			case sf::Event::MouseMoved: // Обработка событий движения мыши
				count = 1; // Снова приходит на помощь счётчик. 
				for (int iter = 0; iter < 8; iter++) {
					if ((iter > 3) && (count > 0)) count -= 1;
					mouse_response_button(mouse_pos, rgb, iter, count); // При наведении появляется графический эффект
				}
				if (isDragging) {
					current_position = sf::Mouse::getPosition();
					delta = current_position - start_position;
					window.setPosition(window.getPosition() + delta);
					start_position = current_position;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if ((event.mouseButton.button == sf::Mouse::Left)) {
					
					set_button(texts, mouse_pos);
					if (get_button() == buttons::none) {
						isDragging = true;
						start_position = sf::Mouse::getPosition();
					}
					switch (get_button())
					{
					case (buttons::generate):
						window_message("Generation completed", "Message Generation");
						Func->generate();
						break;
					case (buttons::calculate):
						window_message("Calculating completed", "Message Calculating");
						Func->sorting();
						break;
					case (buttons::save):
						window_message("Saving completed", "Message Saving");
						Func->saving();
						break;
					case (buttons::download):
						window_message("downloading completed", "Message Saving");
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
			} count = 0;
		}
		window.setActive(); //Активация окна для отрисовки
		window.clear();
		window.draw(background_sprite);
		for (const auto& text : texts) {
			window.draw(text);
		}
		window.display(); //Вывод
	}
	return false;
}

void graph_menu::plot()
{
}

void graph_menu::table()
{
}

void graph_menu::window_message(std::string message, std::string banner)
{
	download_font(font_window, str_font_window);

	sf::RenderWindow window(sf::VideoMode(windowMessageWidth, windowMessageHeight), banner); //Создание окна
	window.setFramerateLimit(fps);

	sf::Text msg; sf::Text ok;
	ok.setString("Ok"); msg.setString(message);
	std::vector <sf::Text> window_texts = { msg, ok };
	std::vector <float> positions = { position_message_y, position_agreement_y };

	for (int i = 0; i < 2; i++) {
		set_decoration_text(window_texts[i], font_window, size_font_message, sf::Color::Black);
		define_center_position(window_texts[i], windowMessageWidth, positions[i]);
	}

	while (window.isOpen()) { //Главный цикл - заканчивается, как только окно закрыто
		sf::Event event; //Обработка событий
		
		while (window.pollEvent(event)) {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); // Определение позиции мыши
			bool contain = is_there_cursor(window_texts[1], mouse_pos);
			switch (event.type) {
			case sf::Event::Closed: // Закрытие окна при нажатии на кнопку закрытия
				window.close();
				break;
			case sf::Event::MouseMoved: // Обработка событий движения мыши
				if (contain) {
					window_texts[1].setOutlineThickness(0.5);
				}
				else {
					window_texts[1].setOutlineThickness(0);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if ((event.mouseButton.button == sf::Mouse::Left) && contain) {
					window.close();
				}
				break;
			} 
		}

		window.setActive(); //Активация окна для отрисовки
		window.clear(sf::Color::White);

		for (const auto& text : window_texts) {
			window.draw(text);
		}


		window.display(); //Вывод
	}
}




