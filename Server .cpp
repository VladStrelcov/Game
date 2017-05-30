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

void Server ();

int main ()
    {
    txCreateWindow (WinX, WinY);
    txBegin();

    Server ();

    }

void Server ()
    {
    Hero Cat    {100,  100, 2,  3,  100,  99};
    Hero Dog    {500,  500, 10, 10, 150,  150};
    Hero Fon    {0,    0,   0,  0,  WinX, WinY, txLoadImage (FonImage)};

    int xmap     = 10, ymap   = 10;

    TX_SOCKET Cat_client = txCreateSocket (TX_SERVER, TX_BROADCAST, TX_STD_PORT, TX_NONBLOCK, false);


    if (txnAssert (Cat_client) == TXN_NOT_CREATED)
            {
            printf ("Can't create server. Maybe, port are busy.\nn");

            }

    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        Fon.Photo              ();

        txSetFillColor         (TX_RED);
        txCircle               (Cat.x, Cat.y, 50);
        Cat.Physics            ();
        Cat.Button             ('W', 'S', 'D', 'A', VK_SPACE, 'Q', &Cat);

        txSetFillColor         (TX_YELLOW);
        txCircle               (Dog.x, Dog.y, 50);
        Dog.Physics            ();

        Logic                  (&Dog, &Cat);

        if (GetAsyncKeyState   (VK_F5)) {system      ("Start Client"); Sleep (1000);};
        if (GetAsyncKeyState   (VK_F6)) (txSaveImage ("Screen.bmp") );

        LeftRightWindow        (VK_NUMPAD4, VK_NUMPAD6, &xmap, &ymap);

        Network Cat_network  = {Cat.x, Cat.y};

        txSendTo               (Cat_client, &Cat_network, sizeof(Cat_network));

        txSleep                (25);
        txSetFillColor         (TX_BLACK);
        txClear                ();
        }


    }

