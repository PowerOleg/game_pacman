#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int H = 21;
const int W = 19;

const int ts = 25;

const int score_to_win = 3;

String tile_map[H] = {
    "AAAAAAAAAAAAAAAAAAA",//0
    "A        A        A",//1
    "A AA AAA A AAA AA A",//2
    "A        A        A",//3
    "A AA AAA A AAA AA A",//4
    "A    A   A   A    A",//5
    "AAAA AAA A AAA AAAA",//6
    "BBBA A   DA  A ABBB",//7
    "AAAA A AAAAA A AAAA",//8
    "BBBB B ABBBA B BBBB",//9
    "AAAA A AAAAA A AAAA",//10
    "BBBA A       A ABBB",//11
    "AAAA A AAAAA A AAAA",//12
    "A  E     A   G    A",//13
    "A AA AAA A AAA AA A",//14
    "A  A     C     A  A",//15
    "AA A A AAAAA A A AA",//16
    "A    A   A   A    A",//17
    "A AAAAAA A AAAAAA A",//18
    "A        F        A",//19
    "AAAAAAAAAAAAAAAAAAA",//20


};

enum class Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN

};

class Player {
public:
    int x = 9;
    int y = 15;
    int new_x = 0;
    int new_y = 0;
    Direction rotate = Direction::RIGHT;//in the begining here was 1==right, 2==left, 3==up, 4=down

	void Update()
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
			score++;
		}
		else if (tile_map[new_y][new_x] == 'B')//the game engine to move the player through the field
		{
			tile_map[y][x] = 'B';
			tile_map[new_y][new_x] = 'C';

			x = new_x;
			y = new_y;
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
   int GetScore()
   {
       return this->score;
   }

private:
    float frame = 0;
    int score = 0;
    int delay = 0;

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


class Enemy {
public:
    int x;
    int y;
    int new_x;
    int new_y;
    int rotate = 1;
    //Direction rotate = Direction::RIGHT;//in the begining here was 1==right, 2==left, 3==up, 4=down
    
    Enemy(char name_, int x_, int y_) : name{ name_ }, x{ x_ }, y{ y_ }, new_x{ x_ }, new_y{ y }
    {}

    void Update()
    {
        //frame += 0.01;
        //if (frame > 5)
        // {
        //    frame -= 5;
        //}

        delay++;
        if (delay >= 300)
        {
            this->rotate = (rand() % 4) + 1;

            switch (rotate)
            {
            case 1:
                if (tile_map[y][new_x - 1] != 'A')
                {
                    new_x--;
                }
                break;
            case 2:
                if (tile_map[y][new_x + 1] != 'A')
                {
                    new_x++;
                }
                break;
            case 3:
                if (tile_map[new_y - 1][x] != 'A')
                {
                    new_y--;
                }
                break;
            case 4:
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
            tile_map[y][x] = ' ';
            tile_map[new_y][new_x] = name;

            x = new_x;
            y = new_y;
        }
        else if (tile_map[new_y][new_x] == 'B')//the game engine to move the player through the field
        {
            tile_map[y][x] = 'B';
            tile_map[new_y][new_x] = name;

            x = new_x;
            y = new_y;
        }

        PlayerOutOfBounds();

    };

    float GetFrame()
    {
        return this->frame;
    }
    int GetRotation()
    {
        return this->rotate;
        /*switch (this->rotate)
        {
        case Direction::LEFT:
            return 2;
        case Direction::RIGHT:
            return 1;
        case Direction::UP:
            return 3;
        case Direction::DOWN:
            return 4;
        }*/
    }

private:
    float frame = 0;
    int score = 0;
    int delay = 0;
    char name;

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
            tile_map[new_y][new_x] = name;

            x = new_x;
            y = new_y;
        }
    }
};


void RepaintGameField(RenderWindow &window, Sprite &plat, Sprite &youwin, Sprite &youlose, Player &player, Enemy &enemy, Enemy &enemy2, Enemy& enemy3, Enemy& enemy4)
{
    if (player.GetScore() >= score_to_win)
    {
        window.draw(youwin);
        window.display();
        return;
    }
    for (size_t i = 0; i < H; i++)
    {
        for (size_t j = 0; j < W; j++)
        {
            if (tile_map[i][j] == 'A')
            {
                plat.setTextureRect(IntRect(0, 0, ts, ts));
            }
            if (tile_map[i][j] == 'C')
            {
                
                plat.setTextureRect(IntRect(ts * int(player.GetFrame()), ts * player.GetRotation(), ts, ts));//arguments IntRect( frame in axis x in picture from sprites, the number of "fragment 25 * 25 of picture" from sprites in axis y, Width, Height);
            }
            if (tile_map[i][j] == ' ')
            {
                plat.setTextureRect(IntRect(ts, 0, ts, ts));
            }
            if (tile_map[i][j] == 'D')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemy.GetRotation(), ts, ts));
            }
            if (tile_map[i][j] == 'G')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemy2.GetRotation(), ts, ts));
            }
            if (tile_map[i][j] == 'E')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemy3.GetRotation(), ts, ts));
            }
            if (tile_map[i][j] == 'F')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemy4.GetRotation(), ts, ts));
            }
            if (tile_map[i][j] == 'B')
            {
                continue;
            }
            plat.setPosition(j * ts, i * ts);
            window.draw(plat);
        }

    }
    
    window.display();
    //sleep(sf::Time(sf::milliseconds(300)));
}


int main(int argc, char** argv)
{
    srand(time(0));
    RenderWindow window(VideoMode(W * ts, H * ts), "Pacman");
    Texture t;
    t.loadFromFile("C:\\cpp\\games\\visual_studio\\Pacman\\Pacman\\pacmansprites2.png");
    Sprite plat(t);

    Texture you_win;
    you_win.loadFromFile("C:\\cpp\\games\\visual_studio\\Pacman\\Pacman\\you_win.png");
    Sprite youwin(you_win);
    youwin.setPosition(30, 210);

    Texture you_lose;
    you_lose.loadFromFile("C:\\cpp\\games\\visual_studio\\Pacman\\Pacman\\you_lose.png");
    Sprite youlose(you_lose);
    youlose.setPosition(30, 210);

    Player player;
    Enemy enemy1('D', 9, 7);
    Enemy wall1('A', 10, 7);
    Enemy enemy2('G', 13, 13);
    Enemy enemy3('E', 3, 13);
    Enemy enemy4('F', 9, 19);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (player.GetScore() >= score_to_win)
            {
                continue;
            }

            if (event.type == Event::KeyPressed)//the key listener changes player fields: x, rotate
            {
                player.new_x = player.x;
                player.new_y = player.y;

                if (event.key.code == Keyboard::Right)
                {
                    player.rotate = Direction::RIGHT;
                }
                if (event.key.code == Keyboard::Left)
                {
                    player.rotate = Direction::LEFT;
                }
                if (event.key.code == Keyboard::Up)
                {
                    player.rotate = Direction::UP;
                }
                if (event.key.code == Keyboard::Down)
                {
                    player.rotate = Direction::DOWN;
                }
            }
        }
        player.Update();
        enemy1.Update();
        wall1.Update();
        enemy2.Update();
        enemy3.Update();
        enemy4.Update();
        window.clear(Color::Black);
        
        RepaintGameField(window, plat, youwin, youlose, player, enemy1, enemy2, enemy3, enemy4);
    }
    return 0;
}