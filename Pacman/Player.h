#pragma once
#include "Game.h"

class Score
{
public:
	const static int len = 3;
	Sprite sec[Score::len];
	int s[Score::len], c;
	bool vid[Score::len];

	Score(Texture& image)
	{
		/* for (size_t i = 0; i < Score::len; i++)//TODO
		 {
			 sec[i].setTexture(image);
			 sec[i].setPosition(10 + 22 * i, H * ts + 10);
			 sec[i].setTextureRect(IntRect(0, 0, 22, 45));

			 s[i] = 0;
			 c = 0;
		 }*/
	}

	/*void Update()//TODO
	{
		if (c < 10)
		{
			s[0] = c;

			vid[0] = true;
			vid[1] = false;
			vid[2] = false;
		}
		else if (c >= 10 && c < 100)
		{
			s[0] = c / 10;
			s[1] = c % 10;

			vid[0] = true;
			vid[1] = true;
			vid[2] = false;
		}
		else
		{
			s[0] = c / 100;
			s[1] = (c / 10) % 10;
			s[2] = (c % 100) % 10;

			vid[0] = true;
			vid[1] = true;
			vid[2] = true;
		}
		for (size_t i = 0; i < Score::len; i++)
		{
			sec[i].setTextureRect(IntRect(22 * s[i], 0, 22, 45));
		}
	}*/
	void AddScore()
	{
		this->score++;
	}

	int GetScore()
	{
		return this->score;
	}

private:
	int score = 0;
};

class Player {
public:
	int x = 9;
	int y = 15;
	int new_x = 0;
	int new_y = 0;
	Direction rotate = Direction::RIGHT;//in the begining here was int 1==right, 2==left, 3==up, 4=down
	Score* score;

	Player(String* tile_map_, Score& score_) : tile_map{ tile_map_ }, score { &score_ }
	{}

	~Player()
	{
		delete score;
	}

	void UpdateTileMap()
	{
		frame += 0.01;
		if (frame > 5)
		{
			frame -= 5;
		}

		delay++;
		if (delay >= 300)
		{
			switch (rotate)
			{
			case Direction::LEFT:
				if (tile_map[y][new_x - 1] != 'A')
				{
					new_x--;
				}
				break;
			case Direction::RIGHT:
				if (tile_map[y][new_x + 1] != 'A')
				{
					new_x++;
				}
				break;
			case Direction::UP:
				if (tile_map[new_y - 1][x] != 'A')
				{
					new_y--;
				}
				break;
			case Direction::DOWN:
				if (tile_map[new_y + 1][x] != 'A')
				{
					new_y++;
				}
				break;
			}
			delay = 0;
		}

		if (tile_map[new_y][new_x] == ' ')//the game engine to move the player through dots
		{
			tile_map[y][x] = 'B';
			tile_map[new_y][new_x] = 'C';

			x = new_x;
			y = new_y;
			score->AddScore();
		}
		if (tile_map[new_y][new_x] == 'B')//the game engine to move the player through the field
		{
			tile_map[y][x] = 'B';
			tile_map[new_y][new_x] = 'C';

			x = new_x;
			y = new_y;
		}
		if (tile_map[new_y][new_x] == 'D' || tile_map[new_y][new_x] == 'G' || tile_map[new_y][new_x] == 'E' || tile_map[new_y][new_x] == 'F')
		{
			game_over = true;
		}

		PlayerOutOfBounds();
	};

	float GetFrame()
	{
		return this->frame;
	}

	int GetRotation()
	{
		switch (this->rotate)
		{
		case Direction::LEFT:
			return 2;
		case Direction::RIGHT:
			return 1;
		case Direction::UP:
			return 3;
		case Direction::DOWN:
			return 4;
		}
	}

private:
	float frame = 0;
	int delay = 0;
	String* tile_map;

	void PlayerOutOfBounds()
	{
		if (new_y == 9 && (new_x == 0 || new_x == 18))
		{
			if (new_x == 0)
			{
				new_x = 17;
			}
			else
			{
				new_x = 1;
			}

			tile_map[y][x] = 'B';
			tile_map[new_y][new_x] = 'C';

			x = new_x;
			y = new_y;
		}
	}
};

