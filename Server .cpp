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

void Server ();

int main ()
    {
    txCreateWindow (WinX, WinY);
    txBegin();

    Server ();

    }

void Server ()
    {
    Hero Cat    {100,  100, 2, 3, 100, 99,  txLoadImage (Player3)};
    Hero Brick  {1200, 50,  0, 0, 50,  50,  txLoadImage (Player2)};
    Hero Dog    {500,  500, 5, 3, 150, 150, txLoadImage (Player)};
    Hero Dog2   {500,  800, 5, 3, 150, 150, txLoadImage (Player)};

    TX_SOCKET Cat_client = txCreateSocket (TX_SERVER, TX_BROADCAST, TX_STD_PORT, TX_NONBLOCK, false);




    if (txnAssert (Cat_client) == TXN_NOT_CREATED)
            {
            printf ("Can't create server. Maybe, port are busy.\nn");

            }

    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        Cat.Photo              ();
        Cat.Physics            ();
        Cat.Button             (VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE, 'Q', &Brick);

        Dog.Photo              ();
        Dog.Physics            ();

        Dog2.Photo             ();
        Dog2.Physics           ();

        Logic (&Dog, &Cat);
        Logic (&Dog2, &Cat);

        Brick.Photo            ();

        if (GetAsyncKeyState   (VK_F5)) {system ("Start Client"); Sleep (1000);};
        if (GetAsyncKeyState   (VK_F6)) (txSaveImage ("Screen.bmp"));

        Network Cat_network  = {Cat.x, Cat.y};

        txSendTo               (Cat_client, &Cat_network, sizeof(Cat_network));

        txSleep                (25);
        txSetFillColor         (TX_BLACK);
        txClear                ();
        }


    }

