#include "TXLib.h"
#include "LEONLib.h"

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

const int    PhotoX   = 150,  PhotoY   = 150 ;
const int    SausageX = 900,  SausageY = 100;
const int    Hero  = 20;

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Game    ();
void Photo   (int Dog1x, int Dog1y, int Dog2x, int Dog2y, int Catx, int Caty, int xmap, int ymap,
              HDC FonZad, HDC FonSer, HDC Dog, HDC Dog2, HDC LoveCat, HDC Cat, HDC FonPered);

//===================================================================================================================================================================================================================================================================================================================================================================================================================================================

int main()
    {
    txCreateWindow (WinX, WinY);
    txBegin();

    Game();

    return 0;
    }

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Game()
    {
    int Dog1x    = 900, Dog1y  = 300, Dog1vx  = 3, Dog1vy  = 3;
    int Dog2x    = 600, Dog2y  = 300, Dog2vx  = 3, Dog2vy  = 3;
    int Catx     = 150, Caty   = 300, Catvx   = 0, Catvy   = 0;
    int xmap     = 0,   ymap   = 0;

    HDC  FonPered = txLoadImage ("��������_�����.bmp");
    HDC  FonZad   = txLoadImage ("��������_���.bmp");
    HDC  FonSer   = txLoadImage ("��������_��������.bmp");
    HDC  Dog      = txLoadImage ("���3.bmp");
    HDC  Dog2     = txLoadImage ("���3.bmp");
    HDC  Cat      = txLoadImage ("�����1.bmp");
    HDC  LoveCat  = txLoadImage ("�������.bmp");

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (TX_BLACK);

        if (!GetAsyncKeyState (VK_SHIFT))  txClear ();

        Photo (Dog1x, Dog1y, Dog2x, Dog2y, Catx, Caty, xmap, ymap,
               FonZad, FonSer, Dog, Dog2, LoveCat, Cat, FonPered);

        if (GetAsyncKeyState (VK_NUMPAD4))
            {
            xmap--;
            }
        if (GetAsyncKeyState (VK_NUMPAD6))
            {
            xmap++;
            }

        Physics (&Dog1x, &Dog1y, &Dog1vx, &Dog1vy);
        Physics (&Dog2x, &Dog2y, &Dog2vx, &Dog2vy);
        Physics (&Catx, &Caty,   &Catvx,   &Catvy);

        Button  (VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE, &Catvx, &Catvy);

        double c = sqrt ((SausageX-Catx)*(SausageX-Catx)+(SausageY-Caty)*(SausageY-Caty));


        if (c <= 30)
            {

            int Answer = txMessageBox ("������ ������� �� 2 level???","������???", MB_YESNO);
            if (Answer == IDYES)
                {

                txDeleteDC (FonPered);
                txDeleteDC (FonSer);

                FonPered = txLoadImage ("�������_�����.bmp");
                FonSer   = txLoadImage ("�������_��������.bmp");

                Catx     = rand()/65;
                Caty     = rand()/65;

                }

             else
                {
                break;
                }

            }

        Logic (Dog1x, Dog1y, Catx, Caty, &Dog1vx, &Dog1vy);

        double f = sqrt ((Catx-Dog1x)*(Catx-Dog1x)+(Caty-Dog1y)*(Caty-Dog1y));

        if (f <= 40)
            {

            int Answer = txMessageBox ("������ ������ �������???","������???", MB_YESNO);
            if (Answer == IDYES)
                {

                txDeleteDC (FonPered);
                txDeleteDC (FonSer);
                txDeleteDC (FonZad);

                FonPered = txLoadImage ("��������_�����.bmp");
                FonSer   = txLoadImage ("��������_��������.bmp");
                FonZad   = txLoadImage ("��������_���.bmp");

                Catx     = rand()/65;
                Caty     = rand()/65;

                }

             else
                {

                }

            }

        txSleep (10);
        }

    }

//===================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Photo (int Dog1x, int Dog1y, int Dog2x, int Dog2y, int Catx, int Caty, int xmap, int ymap,
            HDC FonZad, HDC FonSer, HDC Dog, HDC Dog2, HDC LoveCat, HDC Cat, HDC FonPered)
    {

    txBitBlt         (xmap - Catx/Hero, ymap - Catx/Hero, FonZad);
    txTransparentBlt (xmap,     ymap,     FonSer);

    txTransparentBlt (txDC(),   Dog2x,    Dog2y, PhotoX, PhotoY, Dog2);
    txTransparentBlt (SausageX, SausageY, LoveCat);
    txTransparentBlt (Catx,     Caty,     Cat);
    txTransparentBlt (txDC(),   Dog1x,    Dog1y, PhotoX, PhotoY, Dog);

    txTransparentBlt (xmap + Catx/Hero - 50, ymap + Caty/Hero - 50, FonPered);

    }

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

