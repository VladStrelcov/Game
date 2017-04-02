
#include "TXNetwork.h"
#include "TXLib.h"

const double Fast          = 0.4;
const int    TimeGameFast  = 10;

const int    WinX          = 1350, WinY = 750;
const int    Stop          = 0,
             Continue      = 1;

const int    HeroOfWindow  = 30;
const int    TimeFact      = 4;

const char   LovePlayer[]  = "колбаса.bmp";
const char   Level2Zad[]   = "Эверест_зад.bmp";

#include "LEONLib.h"


int main ()
    {
    txCreateWindow (1350, 750);
    txBegin();

    HDC LoveCat   = txLoadImage (LovePlayer);
    HDC FonPered  = txLoadImage (Level2Zad);
    HDC FonSer    = txLoadImage (Level2Zad);
    HDC FonZad    = txLoadImage (Level2Zad);

    Hero Dog2     = {600,  300, 15, 15};
    Hero Circle   = {1250, 100, 0,  0, 90, 50};
    int t         = 0;

    TX_SOCKET Game_client = txCreateSocket (TX_SERVER, TX_BROADCAST, TX_STD_PORT, TX_BLOCK, false, 1);

    if (txnAssert (Game_client) == TXN_NOT_CREATED)
        {

        printf("Can't create server. Maybe, port are busy.\nn");
        return -1;

        }

    while (!GetAsyncKeyState (VK_F12))
        {

        Button ('W', 'S', 'D', 'A', 'E', 'Q', &Dog2, &Circle);

        txSetFillColor (TX_BLACK);
        txClear ();

        txTransparentBlt (txDC(), Circle.x, Circle.y, Circle.SizeImageX, Circle.SizeImageY, LoveCat, (t/TimeFact)%2 * Circle.SizeImageX);

        Touching    (&Circle,   &Dog2,    "Хотите перейти на 2 level???",
                     &FonPered, &FonSer,  &FonZad, Level2Zad, Level2Zad, Level2Zad);

        txSetFillColor (TX_YELLOW);
        txCircle (Dog2.x, Dog2.y, 10);

        Physics  (&Dog2);

        Network Dog2_network  = {Dog2.x, Dog2.y};

        txSendTo (Game_client, &Dog2_network, sizeof(Dog2_network));

        while (GetAsyncKeyState (VK_CONTROL)) Sleep (100);

        txSleep (10);
        }

    }




