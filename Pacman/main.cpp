#include <vector>
#include <time.h>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"


using namespace sf;
void RepaintAnimation(RenderWindow& window, Sprite& plat, Player& player, std::vector<Enemy*> enemy_vector);

// Frame counter for walking animation (H symbol)
static int walking_frame_counter = 0;
static int walking_frame_delay = 0;

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
    "A H      F        A",//19
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
    //score_texture.loadFromFile(".\\resources\\score.png");

    Score score_local(score_texture);
    Player player(tile_map, score_local);
    Enemy enemy1(tile_map, 'D', 9, 7);
    Enemy wall1(tile_map, 'A', 10, 7);
    Enemy enemy2(tile_map, 'G', 13, 13);
    Enemy enemy3(tile_map, 'E', 3, 13);
    Enemy enemy4(tile_map, 'F', 9, 19);
    Enemy enemy5(tile_map, 'H', 2, 19);
    std::vector<Enemy*> enemy_vector = { &wall1, &enemy1 , &enemy2, &enemy3, &enemy4, &enemy5 };//Enemy** enemies = new Enemy*[5]{ &wall1, &enemy1, &enemy2, &enemy3, &enemy4 };//not beautiful

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
        
        player.UpdateTileMap();
        enemy1.UpdateTileMap();
        wall1.UpdateTileMap();
        enemy2.UpdateTileMap();
        enemy3.UpdateTileMap();
        enemy4.UpdateTileMap();
        enemy5.UpdateTileMap();
        
        // Update walking animation frame counter for H symbol
        walking_frame_delay++;
        if (walking_frame_delay >= 400)  // Change frame every 400 game loops
        {
            walking_frame_counter = (walking_frame_counter + 1) % 4;  // Cycle through 0-3 (4 frames, rows 2-5)
            walking_frame_delay = 0;
        }

        window.clear(Color::Black);
        if (player.score->GetScore() >= score_to_win)
        {
            window.draw(youwin);
            window.display();
            continue;
        }
        if (game_over)
        {
            window.draw(youlose);
            window.display();
            continue;
        }

        RepaintAnimation(window, plat, player, enemy_vector);
        window.display();
        //sleep(sf::Time(sf::milliseconds(300)));
    }
    return 0;
}


void RepaintAnimation(RenderWindow& window, Sprite& plat, Player& player, std::vector<Enemy*> enemy_vector)
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

                plat.setTextureRect(IntRect(ts * int(player.GetFrame()), ts * player.GetRotation(), ts, ts));//arguments IntRect( frame in axis x in picture from sprites, the number of "fragment 25 * 25 of picture" from sprites in axis y, Width, Height);
            }
            if (tile_map[i][j] == ' ')
            {
                plat.setTextureRect(IntRect(ts, 0, ts, ts));
            }
            if (tile_map[i][j] == 'D')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemy_vector.at(1)->rotate, ts, ts));
            }
            if (tile_map[i][j] == 'G')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemy_vector.at(2)->rotate, ts, ts));
            }
            if (tile_map[i][j] == 'H')
            {
                // Use column 6 (ts * 6) and cycle through rows 1-4 (walking frames, rows 2-5 in 1-indexed)
                // walking_frame_counter is 0-3, add 1 to get rows 1-4 (0-indexed) = rows 2-5 (1-indexed)
                int walking_row = walking_frame_counter + 1;
                plat.setTextureRect(IntRect(ts * 6, ts * walking_row, ts, ts));
            }
            if (tile_map[i][j] == 'E')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemy_vector.at(3)->rotate, ts, ts));
            }
            if (tile_map[i][j] == 'F')
            {
                plat.setTextureRect(IntRect(ts * 5, ts * enemy_vector.at(4)->rotate, ts, ts));
            }
            if (tile_map[i][j] == 'B')
            {
                continue;
            }
            plat.setPosition(j * ts, i * ts);
            window.draw(plat);
        }

    }

}