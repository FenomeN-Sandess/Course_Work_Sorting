#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "classes.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	// Создание окна
	
	VideoMode desktop = VideoMode::getDesktopMode(); // Получение разрешения экрана
	unsigned int screenWidth = desktop.width; // Ширина экрана
	unsigned int screenHeight = desktop.height; // Высота экрана
	RenderWindow window(VideoMode(screenWidth*0.6, screenHeight*0.6), "SFML Window"); //Создание окна

	int posX = static_cast<int>(screenWidth * 0.2);
	int posY = static_cast<int>(screenHeight * 0.2);
	
	window.setPosition(Vector2i(posX,posY));

	int xSize = window.getSize().x;
	int ySize = window.getSize().y;
	//Создание осей 
	sf::Vertex OY_axis[] =
	{
		sf::Vertex(sf::Vector2f(xSize*0.25,   0), sf::Color::Black, sf::Vector2f(0,  0)),
		sf::Vertex(sf::Vector2f(xSize*0.25, screenHeight), sf::Color::Black, sf::Vector2f(10, 10)),
	};

	sf::Vertex OX_axis[] =
	{
		Vertex(Vector2f(0, ySize * 0.75), Color::Black, Vector2f(10,10)),
		Vertex(Vector2f(screenWidth, ySize * 0.75), Vector2f(10,10)),
	};
	
	VertexArray OX_lines(Lines, 20);
	VertexArray OY_lines(Lines, 20);
	for (int i = 0; i < 20; i+=2) {
		OX_lines[i].position = Vector2f(xSize*0.25+xSize*0.75*((i+1)/20), ySize*0.75 + 35);
		OX_lines[i + 1].position = Vector2f(xSize * 0.25 + xSize * 0.75 * ((i + 1) / 20), ySize*0.75-35);
		OX_lines[i].color = Color::Green;
		OX_lines[i + 1].color = Color::Red;
		//OY_lines[i].position = Vector2f();
		//OY_lines[i + 1].position = Vector2f();
	}
	
	// Ограничение частоты кадров до 60 кадров в секунду
	window.setFramerateLimit(60);

	//Главный цикл - заканчивается, как только окно закрыто
	while (window.isOpen() /* окно открыто - true*/) {

		//Обработка событий
		Event event;
		while (window.pollEvent(event)) {
			//Закрытие окна при нажатии на кнопку закрытия
			if (event.type == Event::Closed) window.close(); 
		}

		//Активация окна для отрисовки
		window.setActive();

		window.clear(Color::White); //Очистка
		//window.draw(rectangle); //Отрисовка объекта 


		window.draw(OY_axis, 2, sf::Lines);
		window.draw(OX_axis, 2, sf::Lines);
		window.draw(OX_lines);

		window.display(); //Вывод

		
		


	}

	

	//menu Menu; /*Объект менюшки*/
	//while (true) 
	//{
	//	Menu.start(); /*Запуск меню*/
	//	Menu.choice(); /*Выбор действия в меню*/
	//}
}
