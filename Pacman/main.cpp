#include <SFML/Graphics.hpp>
//2:48
using namespace sf;

const int H = 21;
const int W = 19;

const int ts = 25;

String title_map[H] = {
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
class Player {
public:
    void Update()
    {
        frame += 0.01;
        if (frame > 5)
        {
            frame -= 5;
        }
    };

   float GetFrame()
   {
       return this->frame;
   }
private:
    float frame = 0;
};


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
        }
        player.Update();
        window.clear(Color::Black);
        

        for (size_t i = 0; i < H; i++)
        {
            for (size_t j = 0; j < W; j++)
            {
                if (title_map[i][j] == 'A')
                {
                    plat.setTextureRect(IntRect(0,0,ts,ts));
                }
                if (title_map[i][j] == 'C')
                {
                    plat.setTextureRect(IntRect(ts * int(player.GetFrame()), ts, ts, ts));
                }
                if (title_map[i][j] == ' ')
                {
                    plat.setTextureRect(IntRect(ts, 0, ts, ts));
                }
                if (title_map[i][j] == 'B')
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
    return 0;
}


/* RenderWindow window(VideoMode(400, 400), L"Новый проект", Style::Default);

    window.setVerticalSyncEnabled(true);

    CircleShape shape(100.f, 3);
    shape.setPosition(100, 100);
    shape.setFillColor(Color::Magenta);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Blue);
        window.draw(shape);
        window.display();
    }*/