#include "Books/TXNetwork.h"
#include "Books/TXLib.h"

const int    WinX = 1350, WinY = 750;

const int    TimeGameFast  = 10;

const int    HeroOfWindow  = 30;

const int    TimeFact      = 4;

const double Fast          = 0.4;

const int    Stop          = 0,
             Continue      = 1;

const char   FonImage[]    = "Image/Fon.bmp";

#include "Books/LEONLib.h"

void Game ();


int main ()
    {
    txCreateWindow (WinX, WinY);

    Game ();

    }

void Game ()
    {
    Hero Cat    {0,    0,   0, 0, 100,  99};
    Hero Dog    {500,  500, 5, 5, 150,  150};
    Hero Fon    {0,    0,   0, 0, WinX, WinY, txLoadImage (FonImage)};

    TX_SOCKET Cat_server = txCreateSocket (TX_CLIENT, TX_BROADCAST, TX_STD_PORT, TX_BLOCK, false);


    if (txnAssert (Cat_server) == TXN_NOT_CREATED)
    {
    printf ("Can't create listener. Maybe, port are busy.\n");
    }

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txRecvFrom (Cat_server, &Cat, sizeof(Cat));

        Fon.Photo              ();

        txSetFillColor   (TX_RED);
        txCircle         (Cat.x, Cat.y, 50);
        Cat.Physics      ();

        txSetFillColor   (TX_YELLOW);
        txCircle         (Dog.x, Dog.y, 50);
        Dog.Physics      ();

        Logic            (&Dog, &Cat);

        txSleep      (0);
        }
    }




