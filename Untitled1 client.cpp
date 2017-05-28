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
    Hero Cat    {0,    0,   0, 0, 100, 99,  txLoadImage (Player3)};
    Hero Brick  {1200, 50,  0, 0, 50,  50,  txLoadImage (Player2)};
    //Hero Dog2   {123,  50,  2, 5, 150, 150, txLoadImage (Player)};
    Hero Dog    {500,  500, 5, 3, 150, 150, txLoadImage (Player)};

    TX_SOCKET Dog_server = txCreateSocket (TX_CLIENT, TX_BROADCAST, TX_STD_PORT, TX_BLOCK, false);
    TX_SOCKET Cat_server = txCreateSocket (TX_CLIENT, TX_BROADCAST, TX_STD_PORT, TX_BLOCK, false);


    if (txnAssert (Cat_server) == TXN_NOT_CREATED)
    {
    printf ("Can't create listener. Maybe, port are busy.\n");
    }

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txRecvFrom (Cat_server, &Cat, sizeof(Cat));

        txSetFillColor (TX_BLACK);

        if           (!GetAsyncKeyState  (VK_SHIFT))  txClear ();

        Dog.Photo    ();
        Dog.Physics  ();
        Dog.Button   ('W', 'S', 'D', 'A', VK_SPACE, 'Q', &Brick);

        //Dog2.Photo   ();
        //Dog2.Physics ();


        Brick.Photo  ();

        Cat.Photo    ();
        Cat.Physics  ();

        Network Dog_network  = {Dog.x, Dog.y};

        txSendTo     (Dog_server, &Dog_network, sizeof(Dog_network));

        txSleep      (0);
        }
    }

