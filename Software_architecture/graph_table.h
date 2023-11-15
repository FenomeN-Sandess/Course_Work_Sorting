#pragma once
#include "functions.h"
#include "graph_menu_global.h"
#include <string>
#include <vector>
class table_window {
private:
	global g;
	functions* Func;
protected:
	unsigned int windowTableWidth = static_cast<unsigned int>(g.screenWidth * 0.6);  
	unsigned int windowTableHeight = static_cast<unsigned int>(g.screenHeight * 0.5); 
	unsigned int num_columns = 12;
	unsigned int num_rows = 6;
	unsigned int size_title = static_cast<int>(windowTableWidth / 60);
	float size_cell_outline = 1;
	sf::Color color_cell_outline = sf::Color::Black;
	sf::Color color_cell_theFill;
	sf::Color color_title;
	float size_cell_height = windowTableHeight / static_cast<float>(num_rows);
	float size_cell_width = windowTableWidth / static_cast<float>(num_columns + 1);
	std::vector <int> names_column = { 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 }; // Массив с набором параметров сложности

	std::vector <std::string> names_sort = {"Bubble sort", "Heap sort",
		"Quick sort", "Selection sort", "Insertion sort"}; 
	std::string font = "arial.ttf";
	std::string background_img = "background_table.jpg"; // Картинка фона
	void arrow();
	void desctiption_title(sf::RectangleShape rectangle, std::string text_in);
	void cells(std::vector<std::vector<double>> sort_time, int number_row);
	void header();
	void body();
	void animation_arrow(float width, float width_after, float height, float height_after, sf::Vector2i mouse_pos);
public:
	table_window(functions* f) : Func(f), g(f) {}
	void table();

};