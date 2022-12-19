#include <SFML/Graphics.hpp>
#include "settings.h"
#include "Header.h"

using namespace sf;
int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FPS);

	//создание объектов
	RectangleShape leftBat, rightBat;

	/*leftBat.setSize(BAT_SIZE);
	leftBat.setFillColor(LEFT_BAT_COLOR);
	leftBat.setPosition(BAT_OFFSET, (WINDOW_HEIGHT - BAT_SIZE.y) / 2);*/

	batInit(leftBat, LEFT_BAT_COLOR, LEFT_BAT_START_POS);
	batInit(rightBat, RIGHT_BAT_COLOR, RIGHT_BAT_START_POS);
	CircleShape ball(BALL_RADIUS);
	ballInit(ball);

	/*ball.setFillColor(BALL_COLOR);
	ball.setPosition((WINDOW_WIDTH - 2 * BALL_RADIUS) / 2,
		(WINDOW_HEIGHT - 2 * BALL_RADIUS) / 2);*/

	float ballSpeedX = 2.f;
	float ballSpeedY = 3.f;

	//счет
	//шрифт
	Font font;
	font.loadFromFile("DS-DIGIB.ttf");
	//переменные для счета
	int leftScore = 0;
	int rightScore = 0;
	//тексты для отображения на экране
	//текс для левого счета
	Text leftText;
	textInit(leftText,font,leftScore,LEFT_TEXT_POS);
	/*leftText.setString(std::to_string(leftScore));
	leftText.setFont(font);
	leftText.setCharacterSize(FONT_SIZE);
	leftText.setPosition(LEFT_TEXT_POS);*/

	//текст для правого счета 
	Text rightText;
	textInit(rightText,font, leftScore, LEFT_TEXT_POS);
	/*leftText.setString(std::to_string(leftScore));
	leftText.setFont(font);
	leftText.setCharacterSize(FONT_SIZE);
	leftText.setPosition(LEFT_TEXT_POS);*/
	while (window.isOpen())
	{
		//1 отработка событий
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		// обновление игровых объектов 
		//мяч
		ball.move(ballSpeedX, ballSpeedY);
		//мяч отскакивает от левой границы экрана 
		if (ball.getPosition().x <= 0)
		{
			ballSpeedX = -ballSpeedX;
			rightScore++;
		}
		//мяч отскакивает от правой границы экрана 
		if (ball.getPosition().x + 2 * BALL_RADIUS >= WINDOW_WIDTH)
		{
			ballSpeedX = -ballSpeedX;
			leftScore++;
			leftText.setString(std::to_string(leftScore));
		}
		if (ball.getPosition().y <= 0 ||
			ball.getPosition().y + 2 * BALL_RADIUS >= WINDOW_HEIGHT)
		{
			ballSpeedY = -ballSpeedY;
			rightScore++;
			rightText.setString(std::to_string(rightScore));
		}
		//левая ракета 
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			leftBat.move(0.f, -BAT_DY);
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			leftBat.move(0.f, BAT_DY);
		}
		//не даем левой ракете выйти за верхний край экрана 
		if (leftBat.getPosition().y < 0) {
			leftBat.setPosition(BAT_OFFSET, 0.f);
		}
		//не даем левой ракете выйти за нижний край экрана 
		if (leftBat.getPosition().y > WINDOW_HEIGHT - BAT_SIZE.y) {
			leftBat.setPosition(BAT_OFFSET, WINDOW_HEIGHT - BAT_SIZE.y);
		}
		//правая ракета
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			rightBat.move(0.f, -BAT_DY);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			rightBat.move(0.f, BAT_DY);
		}
		//не даем правой ракете выйти за верхний край экрана 
		if (rightBat.getPosition().y < 0) {
			rightBat.setPosition(WINDOW_WIDTH - BAT_OFFSET - BAT_SIZE.x, 0.f);
		}
		//не даем правой ракете выйти за нижний край экрана 
		if (rightBat.getPosition().y < 0) {
			rightBat.setPosition(WINDOW_WIDTH - BAT_OFFSET - BAT_SIZE.x,
				WINDOW_HEIGHT - BAT_SIZE.y);
		}
		//отскок мяча от ракеток 
		Vector2f leftTop{ ball.getPosition().x, ball.getPosition().y };
		Vector2f midLeft{ ball.getPosition().x, ball.getPosition().y + BALL_RADIUS };
		Vector2f leftBottom{ ball.getPosition().x, ball.getPosition().y +
			2 * BALL_RADIUS };
		Vector2f midTop{ ball.getPosition().x + BALL_RADIUS,  ball.getPosition().y };
		Vector2f midBottom{ ball.getPosition().x + BALL_RADIUS,  ball.getPosition().y +
			2 * BALL_RADIUS };
		Vector2f rightTop{ ball.getPosition().x + 2 * BALL_RADIUS,
			ball.getPosition().y };
		Vector2f midRight{ ball.getPosition().x + 2 * BALL_RADIUS,
			ball.getPosition().y + BALL_RADIUS };
		Vector2f rightBottom{ ball.getPosition().x + 2 * BALL_RADIUS,
			ball.getPosition().y + 2 * BALL_RADIUS };
		//ËÅÂÀß ÐÀÊÅÒÊÀ
		//îò ïðàâîãî êðàÿ ëåâîé ðàêåòêè
		if (pointInRect(leftBat, midLeft) && pointInRect(leftBat, leftTop) ||
			pointInRect(leftBat, midLeft) && pointInRect(leftBat, leftBottom))
		{
			ballSpeedX = -ballSpeedX;
		}
		//îò âåðõíåãî êðàÿ ëåâîé ðàêåòêè
		if (pointInRect(leftBat, midBottom) && pointInRect(leftBat, leftBottom) ||
			pointInRect(leftBat, midBottom) && pointInRect(leftBat, rightBottom))
		{
			ballSpeedY = -ballSpeedY;
		}
		//îò íèæíåãî êðàÿ ëåâîãî ðàêåòêè
		if (pointInRect(leftBat, midTop) && pointInRect(leftBat, leftTop) ||
			pointInRect(leftBat, midTop) && pointInRect(leftBat, rightTop))
		{
			ballSpeedY = -ballSpeedY;
		}
		//â ðàêåòêó ïîïàë òîëüêî ëåâûé íèæíèé óãîë
		//â ðàêåòêó ïîïàë òîëüêî ëåâûé âåðõíèé óãîë
		if ((pointInRect(leftBat, leftTop) || pointInRect(leftBat, leftBottom)) &&
			!pointInRect(leftBat, midLeft))
		{
			ballSpeedY = -ballSpeedY;
		}
		//ÏÐÀÂÀß ÐÀÊÅÒÊÀ
		//îò ëåâîãî êðàÿ ÏÐÀÂÎÉ ðàêåòêè
		if (pointInRect(rightBat, midRight) && pointInRect(rightBat, rightTop) ||
			pointInRect(rightBat, midRight) && pointInRect(rightBat, rightBottom))
		{
			ballSpeedX = -ballSpeedX;
		}
		//îò âåðõíåãî êðàÿ ïðàâîé ðàêåòêè
		if (pointInRect(rightBat, midBottom) && pointInRect(rightBat, leftBottom) ||
			pointInRect(rightBat, midBottom) && pointInRect(rightBat, rightBottom))
		{
			ballSpeedY = -ballSpeedY;
		}
		//îò íèæíåãî êðàÿ ïðàâîé ðàêåòêè
		if (pointInRect(rightBat, midTop) && pointInRect(rightBat, leftTop) ||
			pointInRect(rightBat, midTop) && pointInRect(rightBat, rightTop))
		{
			ballSpeedY = -ballSpeedY;
		}
		//â ðàêåòêó ïîïàë òîëüêî ïðàâûé íèæíèé óãîë
		//â ðàêåòêó ïîïàë òîëüêî ïðàâûé âåðõíèé óãîë
		if ((pointInRect(rightBat, rightTop) || pointInRect(rightBat, rightBottom)) &&
			!pointInRect(rightBat, midRight))
		{
			ballSpeedY = -ballSpeedY;
		}
		//3 îòðèñîâêà îáúåêòîâ è îáíîâëåíèå îêíà
		window.clear();
		window.draw(leftBat);
		window.draw(rightBat);
		window.draw(ball);
		window.draw(leftText);
		//window.draw(rightText);
		window.display();
	}

	return 0;
}
