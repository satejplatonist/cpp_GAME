#include <iostream>
#include <tuple>
#include <raylib.h>

struct Ball
{
public:
	int radius = 0;
	Color SB_Color;
	int posx = 0, posy = 0;
	int speedX = 4, speedY = 4;
public:
	Ball() {};
	Ball(int x,int y,int r,Color color)
	{
		fillInputs(x,y,r,color);
		DrawCircle(posx, posy, radius,SB_Color);
	}
	int getPosY() { return posy; }
	void update(int& PLAYER_Score,int& CPU_Score)
	{
		posx += speedX;
		posy += speedY;

		if (posx + radius >= GetScreenWidth()-25)
		{
			if (posy + radius >= GetScreenHeight() / 2 - 180 && posy + radius <= GetScreenHeight() / 2 + 180)
			{
				CPU_Score++;
				reset();
			}
			speedX *= -1;
		}
		else if (posx - radius <= 25)
		{
			if (posy + radius >= GetScreenHeight() / 2 - 180 && posy + radius <= GetScreenHeight() / 2 + 180)
			{
				PLAYER_Score++;
				reset();
			}
			speedX *= -1;
		}
		else if (posy + radius >= GetScreenHeight()-25 || posy - radius <= 25)
		{
			speedY *= -1;
		}
		Ball(posx, posy, radius, SB_Color);
	}
private:
	void fillInputs(int x, int y, int r, Color color)
	{
		posx = x; posy = y;
		radius = r;
		SB_Color = color;
	}
	void reset()
	{
		Ball(GetScreenWidth() - 700, GetScreenHeight() - 700, 15, WHITE);
	}
};

struct Paddle
{
public:
	int posx = 0, posy = 0;
	int height = 0, width = 0;
	int speedY = 5;
	Color SP_Color;
public:
	Paddle(){}
	Paddle(int x, int y, int w, int h, Color color)
	{
		fillInputs(x, y, w, h, color);
		DrawRectangle(posx, posy, width, height, SP_Color);
	}
	void update()
	{
		if (IsKeyDown(KEY_UP))
		{
			posy = posy - speedY;
			if (posy <= 0)
			{
				posy = 0;
			}
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			posy = posy + speedY;
			if (posy >= GetScreenHeight() - height)
			{
				posy = GetScreenHeight() - height;
			}
		}
		Paddle(posx, posy, width, height, SP_Color);
	}
private:
	void fillInputs(int x, int y, int w, int h, Color color)
	{
		posx = x; posy = y;
		height = h; width = w;
		SP_Color = color;
	}
};

struct CPU_Paddle
{
public:
	int posx = 0, posy = 0;
	int height = 0, width = 0;
	int speedY = 5;
	Color SP_Color;
public:
	CPU_Paddle() {};
	CPU_Paddle(int x, int y, int w, int h, Color color)
	{
		fillInputs(x, y, w, h, color);
		DrawRectangle(posx, posy, width, height, SP_Color);
	}
	void update(int ball_t)
	{
		if (posy + height / 2 > ball_t)
		{
			posy = posy - speedY;
			if (posy <= 0)
			{
				posy = 0;
			}
		}
		else if (posy + height / 2 < ball_t)
		{
			posy = posy + speedY;
			if (posy >= GetScreenHeight() - height)
			{
				posy = GetScreenHeight() - height;
			}
		}
		CPU_Paddle(posx, posy, width, height, SP_Color);
	}
private:
	void fillInputs(int x, int y, int w, int h, Color color)
	{
		posx = x; posy = y;
		height = h; width = w;
		SP_Color = color;
	}
};

struct GoalPost
{
public:
	int posx = 0, posy = 0;
	int height = 0, width = 0;
	int speedY = 5;
	Color SP_Color;
public:
	GoalPost(int x, int y, int w, int h, Color color)
	{
		fillInputs(x, y, w, h, color);
		DrawRectangle(posx, posy, width, height, SP_Color);
	}
private:
	void fillInputs(int x, int y, int w, int h, Color color)
	{
		posx = x; posy = y;
		height = h; width = w;
		SP_Color = color;
	}
};

void Line()
{
	DrawLine(25, 0, 27,GetScreenHeight(), RED);
	DrawLine(GetScreenWidth() - 25, 0,GetScreenWidth() - 27, GetScreenHeight(), RED);
	DrawLine(GetScreenWidth() / 2 - 5, 0, GetScreenWidth() / 2 + 5, GetScreenHeight(), RED);
}

int main()
{
	const int screenWidth = 1200;
	const int screenHeight = 800;

	int CPU_Score = 0;
	int PLAYER_Score = 0;

	SetTargetFPS(100);
	InitWindow(screenWidth, screenHeight, "satej");

	Ball b{screenWidth-700,screenHeight-700,15,WHITE};
	Paddle p1{ 30,screenHeight / 2 - 35,17,70,GOLD };
	CPU_Paddle cp2{ screenWidth - 45,screenHeight / 2 - 35,17,70,GOLD };
	

	while (!WindowShouldClose())
	{
		BeginDrawing();

		Line();

		GoalPost g1{ 0,screenHeight / 2 - 180,25,360,WHITE };
		GoalPost g2{ screenWidth - 25,screenHeight / 2 - 180,25,360,WHITE };

		
		b.update(PLAYER_Score,CPU_Score);
		
		p1.update();
		cp2.update(b.getPosY());

		if (CheckCollisionCircleRec(Vector2{ static_cast<float>(b.posx),static_cast<float>(b.posy) }, b.radius,
			Rectangle{ static_cast<float>(p1.posx),static_cast<float>(p1.posy),static_cast<float>(p1.width),static_cast<float>(p1.height) }))
		{
			b.speedX *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ static_cast<float>(b.posx),static_cast<float>(b.posy) }, b.radius,
			Rectangle{ static_cast<float>(cp2.posx),static_cast<float>(cp2.posy),static_cast<float>(cp2.width),static_cast<float>(cp2.height) }))
		{
			b.speedX *= -1;
		}

		DrawText(TextFormat("%i", CPU_Score), GetScreenWidth() / 4 + 120, 20, 54, WHITE);
		DrawText(TextFormat("%i", PLAYER_Score), 3 * GetScreenWidth() / 4 - 170, 20, 54, WHITE);
		
		ClearBackground(BLACK);

		EndDrawing();
	}
	CloseWindow();
	return 0;
}
