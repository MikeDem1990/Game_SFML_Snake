#include <SFML/Graphics.hpp>
using namespace sf;

#pragma once
//функция принимает окно по ссылке которое передается в мейн
void menu(RenderWindow& window) {
	//создал текстуры
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;

	//загрузил изображения
	menuTexture1.loadFromFile("C:/Users/Mike/source/repos/Snake/images/GameMenu/play button.png");
	menuTexture2.loadFromFile("C:/Users/Mike/source/repos/Snake/images/GameMenu/Quit button.png");

	//создал спрайты
	Sprite menu1(menuTexture1);
	Sprite menu2(menuTexture2);
	//лог переменная  нужно ли создавать меню
	bool isMenu = 1;
	//элемент меню
	int menuNum = 0;

	menu1.setPosition(100, 30);
	menu2.setPosition(100, 120);


	////////////////МЕНЮ////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 120, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false; //если нажать правую кнопку выходим из меню
			
			if (menuNum == 2) { window.close(); isMenu = false; }
		}

		window.draw(menu1);
		window.draw(menu2);
		window.display();
	}

}