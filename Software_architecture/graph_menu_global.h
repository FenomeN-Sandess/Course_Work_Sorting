#pragma once
#include <SFML/Graphics.hpp>
#include "functions.h"

struct global
{
	functions* Func;
	global(functions* f) : Func(f) {}

	// Объявление констант и объектов
	sf::Sprite arrow_sprite;
	sf::Texture arrow_texture;
	sf::Texture arrow_texture_after;
	std::string arrow_img = "arrow_before.png";
	std::string arrow_img_after = "arrow_after.png";

	sf::Font font; // Объект шрифта
	sf::Font font_window; // Объект шрифта в диалоговом окне
	sf::Sprite background_sprite; // Спрайт фона
	sf::Texture background_texture; // Текстура фона
	std::vector<sf::Text> texts; // Вектор объектов текст
	std::vector<sf::RectangleShape> rectangles; // Вектор объектов прямоугольников
	std::vector<sf::CircleShape> circles;
	std::vector<sf::VertexArray> vertexes;
	std::vector <sf::Color> rgb; // Вектор цветов
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); // Получение разрешения экрана
	unsigned int screenWidth = desktop.width; // Ширина экрана
	unsigned int screenHeight = desktop.height; // Высота экрана
	int count = 0; //Счётчик
	bool isDragging; // Булевая переменная, показывающая, нажимается ли левая кнопка мыши
	sf::Vector2i start_position; sf::Vector2i current_position; sf::Vector2i delta; // Векторные объекты для изменения позиции окна
	int define_index(sf::Text& elem, std::vector <sf::Text>& vector, int count); /*Определение индекса элемента типа Text в векторе*/
	void define_center_position_window(sf::RenderWindow& window, sf::Vector2i& external_window_position, sf::Vector2i& external_window_size);
	void download_font(sf::Font& font, std::string& str); // Подгрузка шрифта из файла
	void download_image(sf::Texture& texture, const std::string& str); // Загрузка картинки в текстуру
	void set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color& color); // Декор текстового объекта
	void set_decoration_rectangle(sf::RectangleShape& rectangle, sf::Vector2f& size,
		float& outline_thickness, sf::Color& outline_color, sf::Color& theFill_color);
	void download_backround(std::string background_img, unsigned int windowWidth, unsigned int windowHeight);
	unsigned int fps = 60;

};


// Шаблоны для определения позиции объекта
template<typename T>
void define_center_position_x(T& object, unsigned int& window_width) {
	float Center_X = window_width / 2.0f;
	sf::FloatRect textBounds = object.getLocalBounds();
	object.setPosition(Center_X - textBounds.width / 2.0f, object.getPosition().y);
}
template<typename T>
void define_center_position_x(T& object, sf::RectangleShape& rectangle) {
	int left_border = rectangle.getPosition().x; // Позиция Левой границы
	int right_border = left_border + rectangle.getSize().x; // Правая граница
	float Center_X = left_border + (right_border - left_border) / 2.0f;
	sf::FloatRect objectBounds = object.getGlobalBounds();
	object.setPosition(Center_X - objectBounds.width / 2.0f, object.getPosition().y);
}

template<typename T>
void define_center_position_area(T& object, sf::RectangleShape rectangle) // Не использовать для текстового объекта!!!
{
	float left_border = rectangle.getPosition().x; // Позиция Левой границы 
	float right_border = left_border + rectangle.getSize().x; // Правая граница
	float top_border = rectangle.getPosition().y; // Верхняя граница
	float buttom_border = top_border + rectangle.getSize().y; // Нижняя граница 
	float Center_X = left_border + (right_border - left_border) / 2.0f;
	float Center_Y = top_border + (buttom_border - top_border) / 2.0f;
	sf::FloatRect objectBounds = object.getGlobalBounds();
	object.setPosition(Center_X - objectBounds.width / 2.0f, Center_Y - objectBounds.height / 2.0f);
}

template<typename T>
void define_center_position_area(T& object, unsigned int window_width, unsigned int window_height)
{
	float Center_X = window_width / 2.0f;
	float Center_Y = window_height / 2.0f;
	sf::FloatRect objectBounds = object.getLocalBounds();
	object.setPosition(Center_X - objectBounds.width / 2.0f, Center_Y - objectBounds.height / 2.0f);
}

template<typename T>
void define_center_position_y(T& object, unsigned int& window_height)
{
	float Center_Y = window_height / 2.0f;
	sf::FloatRect objectBounds = object.getLocalBounds();
	object.setPosition(object.getPosition().x, Center_Y - objectBounds.height / 2.0f);
}
template<typename T>
void define_center_position_y(T& object, sf::RectangleShape& rectangle) {
	int top_border = rectangle.getPosition().y; // Позиция верхней границы внешнего объекта относительно окна
	int buttom_border = top_border + rectangle.getSize().y; // нижняя граница
	float Center_Y = top_border + (buttom_border - top_border) / 2.0f;
	sf::FloatRect objectBounds = object.getGlobalBounds();
	object.setPosition(object.getPosition().x, Center_Y - objectBounds.height / 2.0f);

}

template<typename T>
void define_center_position_area_text(sf::Text& text, sf::Font& font, unsigned int& size_font_message, T& rectangle) {

	sf::String str_text = text.getString();
	sf::FloatRect textBounds = text.getGlobalBounds();

	float left_border = rectangle.getPosition().x; // Позиция Левой границы 
	float right_border = left_border + rectangle.getSize().x; // Правая граница
	float top_border = rectangle.getPosition().y; // Верхняя граница
	float buttom_border = top_border + rectangle.getSize().y; // Нижняя граница 
	float Center_X = left_border + (right_border - left_border) / 2.0f;
	float Center_Y = top_border + (buttom_border - top_border) / 2.0f;
	text.setPosition(Center_X - textBounds.width / 2.0f, Center_Y - (textBounds.height));

}

template<typename T>
bool is_there_cursor(T& object, sf::Vector2i& mouse_pos)
{
	sf::FloatRect objectBounds = object.getGlobalBounds();
	return objectBounds.contains(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
}