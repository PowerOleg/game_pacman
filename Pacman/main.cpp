#include <SFML/Graphics.hpp>
//5:07
using namespace sf;

const int H = 21;
const int W = 19;

const int ts = 25;

String tile_map[H] = {
    "AAAAAAAAAAAAAAAAAAA",//0
    "A        A        A",//1
    "A AA AAA A AAA AA A",//2
    "A        A        A",//3
    "A AA AAA A AAA AA A",//4
    "A    A   A   A    A",//5
    "AAAA AAA A AAA AAAA",//6
    "BBBA A       A ABBB",//7
    "AAAA A AAAAA A AAAA",//8
    "BBBB B BAAAB B BBBB",//9
    "AAAA A AAAAA A AAAA",//10
    "BBBA A       A ABBB",//11
    "AAAA A AAAAA A AAAA",//12
    "A        A        A",//13
    "A AA AAA A AAA AA A",//14
    "A  A     C     A  A",//15
    "AA A A AAAAA A A AA",//16
    "A    A   A   A    A",//17
    "A AAAAAA A AAAAAA A",//18
    "A                 A",//19
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
    int score = 0;
};


void RepaintGameField(RenderWindow &window, Sprite &plat, Player &player)
{
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
                plat.setTextureRect(IntRect(ts * int(player.GetFrame()), ts * player.GetRotation(), ts, ts));//arguments: Left, Top, Width, Height 
            }
            if (tile_map[i][j] == ' ')
            {
                plat.setTextureRect(IntRect(ts, 0, ts, ts));
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
    RenderWindow window(VideoMode(W * ts, H * ts), "Maze!");
    Texture t;
    t.loadFromFile("C:\\cpp\\games\\visual_studio\\Pacman\\Pacman\\pacmansprites2.png");
    Sprite plat(t);

    Player player;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
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
        window.clear(Color::Black);
        
        RepaintGameField(window, plat, player);
    }
    return 0;
}