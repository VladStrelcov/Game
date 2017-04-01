
#include "TXNetwork.h"
#include "TXLib.h"

const double Fast          = 0.4;
const int    TimeGameFast  = 10;

const int    WinX          = 1350, WinY = 750;
const int    Stop          = 0,
             Continue      = 1;

const int    HeroOfWindow  = 30;
const int    TimeFact      = 4;
#include "LEONLib.h"


int main ()
    {
    txCreateWindow (1350, 750);
    txBegin();

    Hero Dog2 = {600, 300, 30, 30};


    TX_SOCKET Game_client = txCreateSocket (TX_SERVER, TX_BROADCAST, TX_STD_PORT, TX_BLOCK, false, 1);

    if (txnAssert (Game_client) == TXN_NOT_CREATED)
        {

        printf("Can't create server. Maybe, port are busy.\nn");
        return -1;

        }

    while (!GetAsyncKeyState (VK_F12))
        {



        txSetFillColor (TX_BLACK);
        txClear ();

        txSetFillColor (TX_YELLOW);
        txCircle (Dog2.x, Dog2.y, 10);

        Physics  (&Dog2);

        Network Dog2_network  = {Dog2.x, Dog2.y};

        txSendTo (Game_client, &Dog2_network, sizeof(Dog2_network));

        while (GetAsyncKeyState (VK_CONTROL)) Sleep (100);

        txSleep (10);
        }

    }




