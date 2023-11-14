#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <type_traits>


// ������� ��� ����������� ������� �������
template<typename T>
void define_center_position_x(T& object, unsigned int& window_width) {
	float Center_X = window_width / 2.0f;
	sf::FloatRect textBounds = object.getLocalBounds();
	object.setPosition(Center_X - textBounds.width / 2.0f, object.getPosition().y);
}
template<typename T1,typename T2>
void define_center_position_x(T1& object, T2& rectangle) {
	int left_border = rectangle.getPosition().x; // ������� ����� �������
	int right_border = left_border + rectangle.getSize().x; // ������ �������
	float Center_X = left_border + (right_border - left_border) / 2.0f;
	sf::FloatRect objectBounds = object.getGlobalBounds();
	object.setPosition(Center_X - objectBounds.width / 2.0f, object.getPosition().y);
}

template<typename T1, typename T2>
void define_center_position_area(T1& object, sf::RectangleShape rectangle) // �� ������������ ��� ���������� �������!!!
{
	float left_border = rectangle.getPosition().x; // ������� ����� ������� 
	float right_border = left_border + rectangle.getSize().x; // ������ �������
	float top_border = rectangle.getPosition().y; // ������� �������
	float buttom_border = top_border + rectangle.getSize().y; // ������ ������� 
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
template<typename T1, typename T2>
void define_center_position_y(T1& object, T2& rectangle) {
	int top_border = rectangle.getPosition().y; // ������� ������� ������� �������� ������� ������������ ����
	int buttom_border = top_border + rectangle.getSize().y; // ������ �������
	float Center_Y = top_border + (buttom_border - top_border) / 2.0f;
	sf::FloatRect objectBounds = object.getGlobalBounds();
	object.setPosition(object.getPosition().x, Center_Y - objectBounds.height / 2.0f);
	
}



template<typename T>
void define_center_position_area_text(sf::Text& text, sf::Font& font, unsigned int& size_font_message, T& rectangle) {
	
	sf::String str_text = text.getString();
	sf::FloatRect textBounds = text.getGlobalBounds();

	float left_border = rectangle.getPosition().x; // ������� ����� ������� 
	float right_border = left_border + rectangle.getSize().x; // ������ �������
	float top_border = rectangle.getPosition().y; // ������� �������
	float buttom_border = top_border + rectangle.getSize().y; // ������ ������� 
	float Center_X = left_border + (right_border - left_border) / 2.0f;
	float Center_Y = top_border + (buttom_border - top_border) / 2.0f;
	text.setPosition(Center_X - textBounds.width / 2.0f, Center_Y - (textBounds.height));

}

template<typename T>
bool is_there_cursor(T& object, sf::Vector2i& mouse_pos)
{
	sf::FloatRect objectBounds = object.getGlobalBounds();  // ������ ��������������, ������������ ������� Float
	return objectBounds.contains(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
}