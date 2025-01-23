#include <time.h>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

using namespace sf;
void RepaintGameField(RenderWindow& window, Sprite& plat, Sprite& youwin, Sprite& youlose, Player& player, Enemy* enemies);

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



int main(int argc, char** argv)
{
    srand(time(0));
    RenderWindow window(VideoMode(W * ts, H * ts), "Pacman");
    Texture texture;
    texture.loadFromFile(".\\resources\\pacmansprites2.png");
    Sprite plat(texture);

    Texture you_win;
    you_win.loadFromFile(".\\resources\\you_win.png");
    Sprite youwin(you_win);
    youwin.setPosition(30, 210);

    Texture you_lose;
    you_lose.loadFromFile(".\\resources\\you_lose.png");
    Sprite youlose(you_lose);
    youlose.setPosition(30, 210);

    Texture score_texture;
    score_texture.loadFromFile(".\\resources\\score.png");

    Score score_local(score_texture);
    Player player(tile_map, score_local);
    Enemy enemy1(tile_map, 'D', 9, 7);
    Enemy wall1(tile_map, 'A', 10, 7);
    Enemy enemy2(tile_map, 'G', 13, 13);
    Enemy enemy3(tile_map, 'E', 3, 13);
    Enemy enemy4(tile_map, 'F', 9, 19);
    Enemy enemies[]{ wall1, enemy1 , enemy2, enemy3, enemy4 };
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
        enemy1.Update();
        wall1.Update();
        enemy2.Update();
        enemy3.Update();
        enemy4.Update();
        window.clear(Color::Black);
        
        RepaintGameField(window, plat, youwin, youlose, player, enemies);
    }
    return 0;
}


void RepaintGameField(RenderWindow& window, Sprite& plat, Sprite& youwin, Sprite& youlose, Player& player, Enemy* enemies)
{
    if (player.score->GetScore() >= score_to_win)
    {
        window.draw(youwin);
        window.display();
        return;
    }
    if (game_over)
    {
        window.draw(youlose);
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
                plat.setTextureRect(IntRect(ts * 5, ts * enemies[1].GetRotation(), ts, ts));
            }
            if (tile_map[i][j] == 'G')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemies[2].GetRotation(), ts, ts));
            }
            if (tile_map[i][j] == 'E')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemies[3].GetRotation(), ts, ts));
            }
            if (tile_map[i][j] == 'F')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemies[4].GetRotation(), ts, ts));
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