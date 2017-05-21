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
    Hero Dog    {100,  100, 2, 3, 150, 150};


    TX_SOCKET Dog_client = txCreateSocket (TX_SERVER, TX_BROADCAST, TX_STD_PORT, TX_BLOCK, false);


    if (txnAssert (Dog_client) == TXN_NOT_CREATED)
            {
            printf("Can't create server. Maybe, port are busy.\nn");

            }

    while (!GetAsyncKeyState (VK_ESCAPE), true);
        {

        txSetFillColor (TX_RED);

        txCircle (Dog.x, Dog.y, 50);
        Dog.Physics  ();

        Network Dog_network  = {Dog.x, Dog.y};

        txSendTo (Dog_client, &Dog_network, sizeof(Dog_network));

        txSleep      (25);
        }


    }
