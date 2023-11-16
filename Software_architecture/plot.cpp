#include "plot.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
//void plot_window::

void plot_window::arrow() {

}

void plot_window::define_button_back() {
	sf::RectangleShape arrow_rectangle;
	sf::Vector2f size_arr_rec (2*size_cells_width,2*size_cells_height);
	float size_arr_rec_outline = 0;
	g.set_decoration_rectangle(arrow_rectangle, size_arr_rec, size_arr_rec_outline, color_arr_rec_outline, color_arr_rec_theFill);
	arrow_rectangle.setPosition(size_cells_width*0.5, size_cells_height*0.5);
	g.rectangles.push_back(arrow_rectangle);

	g.download_image(g.arrow_texture, g.arrow_img);
	g.download_image(g.arrow_texture_after, g.arrow_img_after);
	g.arrow_sprite.setTexture(g.arrow_texture);
	g.arrow_sprite.setScale((static_cast<float>(arrow_rectangle.getSize().x) / g.arrow_texture.getSize().x) / 2.0f, 
		(static_cast<float>(arrow_rectangle.getSize().y / g.arrow_texture.getSize().y)) / 2.0f); 
	define_center_position_area(g.arrow_sprite, arrow_rectangle);

}

void plot_window::information_in(sf::RectangleShape rectangle) {
	information_circles_colors = {color_bubble, color_insertion, color_heap, color_quick, color_selection};
	float width = rectangle.getSize().x;
	float height = rectangle.getSize().y;
	float pos_rectangle_x = rectangle.getPosition().x;
	float pos_rectangle_y = rectangle.getPosition().y;
	sf::RectangleShape in_rectangle;
	sf::Vector2f size_in_rectangle(width / 5,height);
	sf::Color color = sf::Color::Transparent;
	g.set_decoration_rectangle(in_rectangle, size_in_rectangle, outline_rectangle, color, color);
	sf::Text text;
	g.set_decoration_text(text, g.font, size_segments, color_text_in);
	for (int i = 0; i < 5; i++)
	{
		in_rectangle.setPosition(pos_rectangle_x + i*(width/5), pos_rectangle_y);
		text.setString(information.at(i));
		define_center_position_area_text(text, g.font, size_segments, in_rectangle);
		sf::Color color = sf::Color::Black;
		circle(text.getPosition().x - 20, text.getPosition().y + (text.getLocalBounds().height / 1.5f), radius, 2, color, information_circles_colors[i]);
		g.texts.push_back(text);
		g.circles.push_back(circle_shape);
		g.rectangles.push_back(in_rectangle);
	}
}

void plot_window::define_rectangle_inf() {
	sf::RectangleShape rectangle;
	sf::Color color = sf::Color::White;
	g.set_decoration_rectangle(rectangle, size_information, outline_rectangle, color, color);
	rectangle.setPosition(position_OX+size_cells_width, position_OY + size_cells_height);
	g.rectangles.push_back(rectangle);
	information_in(rectangle);
}

void plot_window::circle(float pos_x,float before, float radius,float trickness, sf::Color color_outline, sf::Color color_theFill) {
	circle_shape.setRadius(radius);
	circle_shape.setOrigin(circle_shape.getRadius(), circle_shape.getRadius());
	circle_shape.setOutlineColor(color_outline);
	circle_shape.setOutlineThickness(trickness);
	circle_shape.setPosition(pos_x, before);
	circle_shape.setFillColor(color_theFill);
}

void plot_window::graph(sf::Color& color, std::vector<std::vector<double>>& sort_time) {
	float before = position_OY;
	for (size_t i = 0; i < 22; i += 2)
	{
		straight[i].position = sf::Vector2f(position_OX+g.count*size_cells_width, before);
		straight[i + 1].position = sf::Vector2f(position_OX + (g.count+1)*size_cells_width, position_OY - size_cells_height * (sort_time[1][g.count] / unit));
		straight[i].color = color;
		straight[i + 1].color = color;
		before = position_OY - size_cells_height * (sort_time[1][g.count] / unit);
		circle(position_OX + (g.count + 1) * size_cells_width, before, radius, 2, color, color);
		g.circles.push_back(circle_shape);
		g.count += 1;
	} g.count = 0; g.vertexes.push_back(straight);
}

void plot_window::define_graphs() {
	graph(color_bubble, Func->bubble_time); 
	graph(color_insertion, Func->insertion_time);
	graph(color_heap, Func->pyramid_time); 
	graph(color_quick, Func->quick_time);
	graph(color_selection, Func->selection_time);
}

void plot_window::define_designination() {
	g.set_decoration_text(unit_segment, g.font, size_segments, color_segments);
	unit_segment.setPosition(position_OX - 2*size_delta_X_number, position_OY + size_delta_X_number);
	unit_segment.setString("0");
	g.texts.push_back(unit_segment);

	for (size_t i = 0; i < num_paramentres; i++)
	{
		unit_segment.setPosition(position_OX + (g.count + 1) * size_cells_width - 4*size_delta_X_number, position_OY + size_delta_X_number);
		unit_segment.setString(names_param[i]);
		g.count += 1;
		g.texts.push_back(unit_segment);
	} g.count = 0;

	for (size_t j = 0; j < num_paramentres; j++)
	{
		unit_segment.setPosition(position_OX - 7 * size_delta_X_number, position_OY - (g.count + 1) * size_cells_height + size_delta_X_number);
		unit_segment.setString((std::to_string(std::round((10000 * unit * (g.count + 1)) * pow(10, 3)) / pow(10, 3))).substr(0, 5));
		g.texts.push_back(unit_segment);
		g.count += 1;
	} g.count = 0;
}

void plot_window::define_unit_segments_line() {
	g.count = 1;
	for (size_t i = 2; i < count_cells * 2; i += 2)
	{
		unit_segments[i].position = sf::Vector2f(position_OX - size_delta_OX, g.count * size_cells_height);
		unit_segments[i + 1].position = sf::Vector2f(position_OX + size_delta_OX, g.count * size_cells_height);
		g.count += 1;
	} g.count = 1;
	for (size_t j = count_cells*2; j < count_cells * 4; j += 2)
	{
		unit_segments[j].position = sf::Vector2f(plotWidth - g.count * size_cells_width ,position_OY-size_delta_OY);
		unit_segments[j+1].position = sf::Vector2f(plotWidth - g.count * size_cells_width, position_OY+size_delta_OY);
		g.count += 1;
	} g.count = 0;
}

void plot_window::define_axes() {
	axes[0].position = sf::Vector2f(position_OX, 0);
	axes[1].position = sf::Vector2f(position_OX, plotHeight);

	axes[2].position = sf::Vector2f(0, position_OY);
	axes[3].position = sf::Vector2f(plotWidth, position_OY);

	axes[0].color = color_axes;
	axes[2].color = color_axes;
};

void plot_window::define_cell_background()
{
	for (size_t i = 0; i < count_cells * 2; i += 2)
	{
		if (i == count_cells*2-8) { g.count += 1;  continue;  }
		cells[i].position = sf::Vector2f(0, g.count * size_cells_height);
		cells[i].color = color_cells;
		cells[i + 1].color = color_cells;
		cells[i + 1].position = sf::Vector2f(plotWidth, g.count * size_cells_height);
		g.count += 1;
	} g.count = 0;
	
	for (size_t j = count_cells * 2; j < count_cells * 4; j += 2)
	{
		if (j == (count_cells * 2 + 8)) { g.count += 1; continue; }
		cells[j].position = sf::Vector2f(g.count * size_cells_width, 0);
		cells[j].color = color_cells;
		cells[j + 1].color = color_cells;
		cells[j + 1].position = sf::Vector2f(g.count * size_cells_width, plotHeight);
		g.count += 1;
	} g.count = 0;
}

void plot_window::plot()
{


	sf::RenderWindow window(sf::VideoMode(plotWidth, plotHeight), "PLOT", sf::Style::None);
	window.setFramerateLimit(g.fps); 
	window.setPosition(window_pos);
	

	unit = Func->bubble_time[1][10] / 11.0f;
	define_axes(); // Определение осей
	define_cell_background(); // Определение клеточек на фоне
	define_unit_segments_line(); // Определение линий, подчеркивающих единичные отрезки
	define_designination(); // Определение надписей, определяющих единичные отрезки
	define_rectangle_inf(); // Определение окошка с информацией о сортировке
	define_button_back(); // Определение кнопки Back
	define_graphs();
	
	float arrow_sprite_width_after = g.arrow_sprite.getScale().x * 1.1f;
	float arrow_sprite_width_before = g.arrow_sprite.getScale().x;
	float arrow_sprite_height_after = g.arrow_sprite.getScale().y * 1.1f;
	float arrow_sprite_height_before = g.arrow_sprite.getScale().y;



	while (window.isOpen()) { //Главный цикл - заканчивается, как только окно закрыто
		sf::Event event_plot; //Обработка событий
		while (window.pollEvent(event_plot)) {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
			switch (event_plot.type) {
			case sf::Event::Closed:
				window.close();
				g.texts.clear();  g.rectangles.clear();
				break;
			case sf::Event::MouseMoved:
				if (is_there_cursor(g.arrow_sprite, mouse_pos)) {
					g.arrow_sprite.setTexture(g.arrow_texture_after);
					g.arrow_sprite.setScale(arrow_sprite_width_after, arrow_sprite_height_after);

				}
				else {
					g.arrow_sprite.setTexture(g.arrow_texture);
					g.arrow_sprite.setScale(arrow_sprite_width_before, arrow_sprite_height_before);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if ((event_plot.mouseButton.button == sf::Mouse::Left)) {
					if (is_there_cursor(g.arrow_sprite, mouse_pos)) {
						window.close(); g.texts.clear(); g.rectangles.clear(); g.circles.clear(); g.vertexes.clear();
					}
				}


				break;
			case sf::Event::MouseButtonReleased:
				if (event_plot.mouseButton.button == sf::Mouse::Left) {
					g.isDragging = false;
				}
			}
		}
		window.setActive();

		window.clear(sf::Color::White);

		window.draw(g.background_sprite);
		window.draw(cells);
		window.draw(axes);
		window.draw(unit_segments);

		for (const auto& rec : g.rectangles) {	window.draw(rec);	} 

		for (const auto& text : g.texts) {	window.draw(text);	}

		for (const auto& vertex : g.vertexes) {	window.draw(vertex);	}

		for (const auto& circle_sh : g.circles) {	window.draw(circle_sh);	}

		window.draw(g.arrow_sprite);

		window.display(); //Вывод

	}
}