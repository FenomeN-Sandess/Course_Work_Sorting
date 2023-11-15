#pragma once
#include "functions.h"
#include "graph_menu_global.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class plot_window
{
private:
	functions* Func;
	global g;
protected:
	sf::Color color_cells;
	sf::Color color_axes;
	unsigned int plotWidth = static_cast<unsigned int>(g.screenWidth * 0.7); 
	unsigned int plotHeight = static_cast<unsigned int>(g.screenHeight * 0.7); 
	std::string str_font = "JosefinSans-Bold.ttf"; 
	std::string background_img = "backgroundPlot_6.jpg";
	float size_delta_OX = plotWidth / 100.0f;
	float size_delta_OY = size_delta_OX;
	float size_delta_X_number = plotWidth/ 200.0f;
	float unit;
	float outline_rectangle = 2;
	int num_paramentres = 11;
	float count_cells = (num_paramentres + 1) * (4 / 3.0f);
	float size_cells_height = plotHeight / count_cells; // Единичный отрезок по времени
	float size_cells_width = plotWidth / count_cells; // Единичный отрезок по параметру сложности
	std::vector <std::string> names_param = { "50", "100", "200", "300", "400", "500", "600", "700", "800", "900", "1000"};
	std::vector <std::string> information = { "- bubble sorting", "- insertion sorting", "- pyramid sorting", "- quick sorting", "- selection sorting" };
	std::vector <sf::Color> information_circles_colors;
	float position_OX = plotWidth * 0.25f;
	float position_OY = plotHeight * 0.75f;
	float radius = plotWidth / 250.0f;
	sf::VertexArray axes; sf::VertexArray cells;
	sf::VertexArray straight; sf::VertexArray unit_segments;
	sf::Text unit_segment; sf::CircleShape circle_shape;
	sf::Color color_segments; sf::Color color_bubble;
	sf::Color color_insertion; sf::Color color_heap;
	sf::Color color_quick; sf::Color color_selection;
	sf::Color color_text_in; sf::Color color_arr_rec_outline = sf::Color::Transparent;
	sf::Color color_arr_rec_theFill;

	sf::Vector2f size_information;


	unsigned int size_segments = static_cast<unsigned int>(plotWidth / 100.0f);
	void graph(sf::Color& color, std::vector<std::vector<double>>& sort_time);
	void define_designination();
	void define_button_back();
	void arrow();
	void define_unit_segments_line();
	void define_axes();
	void define_rectangle_inf();
	void define_cell_background();
	void circle(float pos_x, float before,
		float radius, float trickness, 
		sf::Color color_outline, sf::Color theFill);
	void information_in(sf::RectangleShape rectangle);

public:
	plot_window(functions* f) : Func(f), g(f), axes(sf::Lines, 4),
		cells(sf::Lines, count_cells * 4),
		unit_segments(sf::Lines, count_cells * 4),
		size_information(10 * size_cells_width, size_cells_height),
		straight(sf::Lines, 150),
		color_cells(120, 120, 120),
		color_axes(255, 255, 255),
		color_segments(255, 255, 255),
		color_bubble(255, 255, 204),
		color_heap(204, 255, 204),
		color_quick(204, 255, 255),
		color_selection(204, 204, 255),
		color_insertion(255, 204, 255),
		color_text_in(0, 0, 0),
		color_arr_rec_theFill(255,255,255,80)
	{
			g.download_font(g.font, str_font); // Подгрузка шрифта
			g.download_backround(background_img, plotWidth, plotHeight); // Подгрузка фона
	};
	
	void plot();
};

