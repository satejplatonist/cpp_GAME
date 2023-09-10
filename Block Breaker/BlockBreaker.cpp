#include <iostream>
#include <vector>
#include <raylib.h>

class Ball
{
public:
	int posx;int posy;
	int radius;
	Color color;
	int speedx = 4;
	int speedy = 4;
public:
	Ball(){}
	Ball(int x, int y, int r, Color c)
	{
		fill(x, y, r, c);
		DrawCircle(posx, posy, radius, color);
	}
	void update()
	{
		posx += speedx;
		posy += speedy;
		if (posx - radius <= 0 || posx + radius >= GetScreenWidth())
		{
			speedx *= -1;
		}
		if (posy - radius <= 0 || posy + radius >= GetScreenHeight())
		{
			speedy *= -1;
		}
		Ball(posx, posy, radius, color);
	}
private:
	void fill(int x, int y, int r, Color c)
	{
		posx = x;
		posy = y;
		radius = r;
		color = c;
	}
};

class Paddle
{
public:
	int posx; int posy;
	int height; int width;
	Color color;
	int speedx = 4;
public:
	Paddle(){}
	Paddle(int x, int y, int w, int h, Color c)
	{
		fill(x, y, w, h, c);
		DrawRectangle(posx, posy, width, height, color);
	}
	/**/void update()
	{
		if (IsKeyDown(KEY_LEFT))
		{
			posx -= speedx;
			if (posx <= 0)
			{
				posx = 0;
			}
		}
		else if (IsKeyDown(KEY_RIGHT))
		{
			posx += speedx;
			if (posx >= GetScreenWidth()-width)
			{
				posx = GetScreenWidth() - width;
			}
		}
		Paddle(posx, posy, width, height, color);
	}
private:
	void fill(int x, int y, int w, int h, Color c)
	{
		posx = x; posy = y;
		width = w; height = h;
		color = c;
	}
};

class Block
{
public:
	int posx; int posy;
	int height; int width;
	Color color;
public:
	Block(){}
	void Draw(int x, int y, int w, int h, Color c)
	{
		fill(x, y, w, h, c);
		DrawRectangle(posx, posy, width, height, color);
	}
private:
	void fill(int x, int y, int w, int h, Color c)
	{
		posx = x; posy = y;
		width = w; height = h;
		color = c;
	}
};

int main()
{
	const int ScreenHeight = 950;
	const int ScreenWidth = 800;

	InitWindow(ScreenWidth, ScreenHeight, "my window");
	SetTargetFPS(100);
	Ball b(200, 300, 20, RED);
	Paddle p(ScreenWidth / 2, ScreenHeight-20, 120, 20, YELLOW);

	Block r11; Block r12; Block r13; Block r14; Block r15; Block r16;

	Block r21; Block r22; Block r23; Block r24; Block r25; Block r26;

	Block r31; Block r32; Block r33; Block r34; Block r35; Block r36;

	Block r41; Block r42; Block r43; Block r44; Block r45; Block r46;

	Block r51; Block r52; Block r53; Block r54; Block r55; Block r56;

	Block r61; Block r62; Block r63; Block r64; Block r65; Block r66;

	std::vector<Block> r
	{
		r11,r12,r13,r14,r15,r16,
		r21,r22,r23,r24,r25,r26,
		r31,r32,r33,r34,r35,r36,
		r41,r42,r43,r44,r45,r46,
		r51,r52,r53,r54,r55,r56,
		r61,r62,r63,r64,r65,r66
	};
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		b.update();
		p.update();
		if (CheckCollisionCircleRec(Vector2{ static_cast<float>(b.posx),static_cast<float>(b.posy) }, static_cast<float>(b.radius), 
			Rectangle{ static_cast<float>(p.posx),static_cast<float>(p.posy),static_cast<float>(p.width),static_cast<float>(p.height)}))
		{
			b.speedy *= -1;
		}

		
		int m = 0, n = 0;
		for (int j = 0; j < r.size(); j++)
		{
		    r[j].Draw(m * ((ScreenWidth / 6) + 3), n * (20 + 6), ScreenWidth / 6 - 3, 20, GREEN);
			m++;
			if (j == 5 || j==11 || j==17 || j==23 || j==29 || j==35)
			{
				m = 0;
				++n;
			}
		}
		std::vector<Block>::iterator it;
		for (int i = 0; i < r.size(); i++)
		{
			if (CheckCollisionCircleRec(Vector2{ static_cast<float>(b.posx),static_cast<float>(b.posy) }, static_cast<float>(b.radius),
				Rectangle{ static_cast<float>(r[i].posx),static_cast<float>(r[i].posy),static_cast<float>(r[i].width),static_cast<float>(r[i].height) }))
			{
				b.speedy *= -1;
				it = r.begin();
				
				r.erase(it);
			}
		}

		
		ClearBackground(BLACK);
		EndDrawing();
    }
	return 0;
}
