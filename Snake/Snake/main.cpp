#include <SFML/Graphics.hpp>
#include <time.h>
#include "menu.h"

using namespace sf;

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * M;

int dir, num = 4;

struct Snake
{ int x, y; } s[100];

struct apple
{ int x, y; } f;

void Tick()
{
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
		
	}
	
	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;

	if ((s[0].x == f.x) && (s[0].y == f.y))
	{
		num++;
		f.x = rand() % N;
		f.y = rand() % M;
	}

	//Чтобы змейка переходила с одной стороы на другую
	if (s[0].x > N) s[0].x = 0; if (s[0].x < 0) s[0].x = N;
	if (s[0].y > M) s[0].y = 0; if (s[0].y < 0) s[0].y = M;

	//Если натыкаешься на самого себя
	for (int i = 1; i < num; i++)
		if (s[0].x == s[i].x && s[0].y == s[i].y) num = i;
}
	

int main()
{

	srand(time(0));

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(w, h), "Snake game!");
	menu(window);

	Texture t1, t2, t3; //Переменные для текстур
	t1.loadFromFile("C:/Users/Mike/source/repos/Snake/images/image.png");
	t2.loadFromFile("C:/Users/Mike/source/repos/Snake/images/red.png");
	t3.loadFromFile("C:/Users/Mike/source/repos/Snake/images/apple.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);

	Clock clock;
	float timer = 0, delay = 0.1;

	f.x = 10;
	f.y = 10;

	// Главный цикл приложения. Выполняется, пока открыто окно

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event)) //пока есть событие, обрабатывать их
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// Тогда закрываем его
				window.close();
			//вызов меню на эск
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				menu(window);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W) )dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))dir = 0;


		if (timer > delay) { timer = 0; Tick();	}
		// Отрисовка окна	
		window.clear();


		//Отрисовка фона
		for (int i = 0; i < N; i++)
		{
			for(int j=0; j<M; j++)
			{
				sprite1.setPosition(i * size, j * size); 
				window.draw(sprite1);
			}

			
		}

		for (int i = 0; i < num; i++)
		{
			sprite2.setPosition(s[i].x * size, s[i].y * size); window.draw(sprite2);
		}
		sprite3.setPosition(f.x * size, f.y * size); window.draw(sprite3);

		window.display();
		
	}

	return 0;
}