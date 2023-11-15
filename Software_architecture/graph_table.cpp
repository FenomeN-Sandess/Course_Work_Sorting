#pragma once
#include "graph_table.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

void table_window::arrow() {
	sf::Vector2f size_arrow_cell(size_cell_width * 2, size_cell_height);
	sf::RectangleShape arrow_cell;
	g.set_decoration_rectangle(arrow_cell, size_arrow_cell, size_cell_outline, color_cell_outline, color_cell_theFill);
	arrow_cell.setPosition(0, 0);
	g.rectangles.push_back(arrow_cell);

	g.download_image(g.arrow_texture, g.arrow_img);
	g.arrow_sprite.setTexture(g.arrow_texture);
	g.arrow_sprite.setScale((static_cast<float>(arrow_cell.getSize().x) / g.arrow_texture.getSize().x) / 2.0f, // Определяем размеры спрайта под область окна
		(static_cast<float>(arrow_cell.getSize().y /g.arrow_texture.getSize().y)) / 2.0f); // Из документации SFML: размер текстуры равен (1,1) - растягиваем текстуру на весь размер окна
	define_center_position_area(g.arrow_sprite, arrow_cell);


};

void table_window::desctiption_title (sf::RectangleShape rectangle, std::string text_in)
{
	sf::Color color(102,255,255,255);
	color_title = color;
	sf::Text text;
	g.set_decoration_text(text, g.font, size_title, color_title);
	text.setString(text_in);
	define_center_position_area_text(text, g.font, size_title, rectangle);
	g.texts.push_back(text);

}

void table_window::cells(std::vector<std::vector<double>> sort_time, int number_row) {
	for (int i = 1; i < num_columns; i++)
	{
		sf::Vector2f size_cell(size_cell_width, size_cell_height);
		sf::RectangleShape cell;
		g.set_decoration_rectangle(cell, size_cell, size_cell_outline, color_cell_outline, color_cell_theFill);
		cell.setPosition((i + 1) * size_cell.x, number_row*size_cell.y);
		g.rectangles.push_back(cell);
		desctiption_title(cell, std::to_string(sort_time[1][i-1]));

	}
};

void table_window::header()
{
	for (int i = 1; i < num_columns; i++) {
		sf::RectangleShape cell;
		sf::Vector2f size_cell_colomn(size_cell_width, size_cell_height);
		g.set_decoration_rectangle(cell, size_cell_colomn, size_cell_outline, color_cell_outline, color_cell_theFill);
		cell.setPosition((i+1) * size_cell_colomn.x, 0);
		std::string text_in = (std::to_string(names_column.at(i-1))); desctiption_title(cell, text_in);
		g.rectangles.push_back(cell);

	}

	for (int i = 1; i < num_rows; i++) {

		sf::Vector2f size_cell_row(size_cell_width * 2, size_cell_height);
		sf::RectangleShape cell;
		g.set_decoration_rectangle(cell, size_cell_row, size_cell_outline, color_cell_outline, color_cell_theFill);
		cell.setPosition(0, size_cell_row.y * i);
		desctiption_title(cell, names_sort.at(i-1));
		g.rectangles.push_back(cell);

	}
}

void table_window::body()
{
	cells(Func->bubble_time, 1);
	cells(Func->pyramid_time, 2);
	cells(Func->quick_time, 3);
	cells(Func->selection_time, 4);
	cells(Func->insertion_time, 5);
	
}

void table_window::animation_arrow(float width, float width_after, float height, float height_after, sf::Vector2i mouse_pos)
{
	if (is_there_cursor(g.arrow_sprite, mouse_pos)) {


		g.arrow_sprite.setTexture(g.arrow_texture_after);
		g.arrow_sprite.setScale(width_after, height_after);

	}
	else {
		g.arrow_sprite.setTexture(g.arrow_texture);
		g.arrow_sprite.setScale(width, height);
	}
}

void table_window::table()
{
	sf::RenderWindow window(sf::VideoMode(windowTableWidth, windowTableHeight), "Table", sf::Style::None);
	window.setFramerateLimit(g.fps);

	sf::Color color (255, 255, 255, 0);
	color_cell_theFill = color;
	g.download_font(g.font, font);
	g.download_backround(background_img, windowTableWidth, windowTableHeight);
	g.download_image(g.arrow_texture_after, g.arrow_img_after);

	header();
	body();
	arrow();
	
	float arrow_sprite_width_after = g.arrow_sprite.getScale().x * 1.1f;
	float arrow_sprite_width_before = g.arrow_sprite.getScale().x;
	float arrow_sprite_height_after = g.arrow_sprite.getScale().y * 1.1f;
	float arrow_sprite_height_before = g.arrow_sprite.getScale().y;

	while (window.isOpen()) {
		sf::Event event_table;
		while (window.pollEvent(event_table)) {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); 
			switch (event_table.type) {
			case sf::Event::Closed: 
				window.close();
				g.texts.clear(); g.rectangles.clear(); g.circles.clear();
				break;
			case sf::Event::MouseMoved: 
				animation_arrow(arrow_sprite_width_before, arrow_sprite_width_after, 
					arrow_sprite_height_before, arrow_sprite_height_after, mouse_pos);
				if (g.isDragging) {
					g.current_position = sf::Mouse::getPosition();
					g.delta = g.current_position - g.start_position;
					window.setPosition(window.getPosition() + g.delta);
					g.start_position = g.current_position;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if ((event_table.mouseButton.button == sf::Mouse::Left)) {
					if (is_there_cursor(g.arrow_sprite, mouse_pos)) { window.close(); g.texts.clear(); g.rectangles.clear();
					}
				}

				g.isDragging = true;
				g.start_position = sf::Mouse::getPosition();
			
				break;
			case sf::Event::MouseButtonReleased:
				if (event_table.mouseButton.button == sf::Mouse::Left) {
					g.isDragging = false;
				}
				break;

			}
			window.setActive(); 
			window.clear(sf::Color::White);
			window.draw(g.background_sprite);
			window.draw(g.arrow_sprite);
			for (const auto& text : g.rectangles) {
				window.draw(text);
			}

			for (const auto& text : g.texts) {
				window.draw(text);
			}
			window.display(); //Вывод
		}
	}
}




