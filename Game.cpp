#include "Books/TXLib.h"

struct Function
    {

    };

const int    WinX = 1350, WinY = 750;

const int    TimeGameFast  = 10;

const int    HeroOfWindow  = 30;

const int    TimeFact      = 4;

const double Fast  = 0.4;

const int    Stop          = 0,
             Continue      = 1;

const char   Player[]      = "Image/Герои/ерк3.bmp";
const char   Player2[]     = "Image/stop.bmp";


#include "Books/LEONLib.h"

void Game ();

void Image (Hero heroPlayer, Hero heroStop);


int main ()
    {
    txCreateWindow (WinX, WinY);

    Game ();

    }

void Game ()
    {
    Hero Circle {243,  400, 2, 3, 150, 150, txLoadImage (Player)};
    Hero Stop   {1200, 50,  0, 0, 50,  50,  txLoadImage (Player2)};


    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (TX_BLACK);

        if      (!GetAsyncKeyState  (VK_SHIFT))  txClear ();

        Image   (Circle, Stop);

        Physics (&Circle);

        Button  (VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE, 'Q', &Circle, &Stop);

/*
        Touching    (&Circle,  &Stop, "Вы выиграли !!!!!!!!!!!!!!!!",
                    &FonPered, &FonSer,  &FonZad, Level1Pered, Level1Ser, Level1Zad);
*/

        txSleep (25);
        }

    }


void Image (Hero heroPlayer, Hero heroStop)
    {

    txTransparentBlt (txDC(), heroPlayer.x, heroPlayer.y, heroPlayer.SizeImageX, heroPlayer.SizeImageY, heroPlayer.Image);
    txTransparentBlt (txDC(), heroStop.x,   heroStop.y,   heroStop.SizeImageX,   heroStop.SizeImageY,   heroStop.Image);

    }

