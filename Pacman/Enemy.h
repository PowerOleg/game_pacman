#pragma once
#include "Game.h"

class Enemy {
public:
    int x;
    int y;
    int new_x;
    int new_y;
    int rotate = 1;

    Enemy(String* tile_map_, char name_, int x_, int y_) : tile_map{ tile_map_ }, name{ name_ }, x{ x_ }, y{ y_ }, new_x{ x_ }, new_y{ y }
    {}

    void UpdateTileMap()
    {
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

        if (tile_map[new_y][new_x] == ' ')//the game engine to move the enemy through dots
        {
            tile_map[y][x] = ' ';
            tile_map[new_y][new_x] = name;

            x = new_x;
            y = new_y;
        }
        if (tile_map[new_y][new_x] == 'B')//the game engine to move the enemy through the field
        {
            tile_map[y][x] = 'B';
            tile_map[new_y][new_x] = name;

            x = new_x;
            y = new_y;
        }
        if (tile_map[new_y][new_x] == 'C')//the game engine to kill the player
        {
            game_over = true;
            tile_map[y][x] = ' ';
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
    }

private:
    float frame = 0;
    int score = 0;
    int delay = 0;
    char name;
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
            tile_map[new_y][new_x] = name;

            x = new_x;
            y = new_y;
        }
    }
};