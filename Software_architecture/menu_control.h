#include <SFML/Graphics.hpp>
#include <string>
#pragma once



class menu_control {
protected:
	int count = 0; //�������

	sf::Font font; // ������ ������
	sf::Sprite background_sprite;
	sf::Texture background_texture;
	std::vector<sf::Text> texts; // ������ �������� �����
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); // ��������� ���������� ������
	unsigned int screenWidth = desktop.width; // ������ ������
	unsigned int screenHeight = desktop.height; // ������ ������
	unsigned int windowWidth = screenWidth*0.3; // ������ ����
	unsigned int windowHeight = screenHeight*0.7; // ������ ����
	std::string background_img = "background_2.jpeg"; // �������� �������� �����
	unsigned int fps = 60;

	std::vector <std::string> text_operation = { "Generate", "Calculate", "Save", "Download", "Display the table", "Display a plot", "Quit" };
	unsigned int size_font = windowWidth/15;
	float position_operation_x = windowWidth*0.35f; 
	float position_opertation_y = windowHeight*0.15f;
	float padding_bottom_operation = windowHeight*0.1f;
	std::string str_font = "Montserrat-Bold.ttf"; // ������������ �����
	

	void download_font(std::string& str); // ��������� ������ �� �����
	void download_image(sf::Texture& texture, const std::string& str);
	void set_decoration_text(sf::Text& text, sf::Font& font, unsigned int& size, const sf::Color &color);
	void choice_texts(); // �������� �������� � ����


public:

	void window(); // ������� ��� �������� ���� � ��������� �����������
	void plot(); // ������� ��� ������ �������
	void table(); // ������� ��� ������ �������
};


