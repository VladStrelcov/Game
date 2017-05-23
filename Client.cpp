#include "Books/TXNetwork.h"
#include "Books/TXLib.h"

const int    WinX = 1350, WinY = 750;

const int    TimeGameFast  = 10;

const int    HeroOfWindow  = 30;

const int    TimeFact      = 4;

const double Fast          = 0.4;

const int    Stop          = 0,
             Continue      = 1;

const char   Player[]      = "Image/Герои/ерк3.bmp";
const char   Player2[]     = "Image/stop.bmp";
const char   Player3[]     = "Image/Герои/кошка.bmp";


#include "Books/LEONLib.h"

void Game ();


int main ()
    {
    txCreateWindow (WinX, WinY);

    Game ();

    }

void Game ()
    {
    Hero Dog    {0,    0,   0, 0, 150, 150, txLoadImage (Player)};
    Hero Dog2   {123,  50,  2, 5, 150, 150, txLoadImage (Player)};
    Hero Brick  {1200, 50,  0, 0, 50,  50,  txLoadImage (Player2)};
    Hero Cat    {500,  500, 5, 3, 100, 99,  txLoadImage (Player3)};

    TX_SOCKET Dog_server = txCreateSocket (TX_CLIENT, TX_BROADCAST, TX_STD_PORT, TX_BLOCK, false);

    if (txnAssert (Dog_server) == TXN_NOT_CREATED)
    {
    printf ("Can't create listener. Maybe, port are busy.\n");
    }

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txRecvFrom (Dog_server, &Dog, sizeof(Dog));

        txSetFillColor (TX_BLACK);

        if           (!GetAsyncKeyState  (VK_SHIFT))  txClear ();

        Dog.Photo    ();
        Dog.Physics  ();

        Logic        (&Dog2, &Cat);

        Dog2.Photo   ();
        Dog2.Physics ();


        Brick.Photo  ();

        Cat.Photo    ();
        Cat.Physics  ();
        Cat.Button   (VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE, 'Q', &Brick);

        txSleep      (0);
        }
    }




