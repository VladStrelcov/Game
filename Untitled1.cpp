#include "TXLib.h"

const double Fast     = 0.4;
const int    WinX     = 1350, WinY     = 750;
const int    DogX     = 150,  DogY     = 150;
const int    CatX     = 100,  CatY     = 99;
const int    SausageX = 90,   SausageY = 50;
const int    Sausagex = 900,  Sausagey = 100;
const int    Hero     = 20;
const int    TimeFact = 4;

#include "LEONLib.h"

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Game      ();
void Photo     (int Dog1x, int Dog1y, int Dog2x, int Dog2y, int Catx, int Caty, int xmap, int ymap,
                int t, HDC FonZad, HDC FonSer, HDC Dog, HDC Dog2, HDC LoveCat, HDC Cat, HDC FonPered);

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
    int t        = 0;

    HDC  FonPered = txLoadImage ("тропинка_перед.bmp");
    HDC  FonZad   = txLoadImage ("тропинка_зад.bmp");
    HDC  FonSer   = txLoadImage ("тропинка_середина.bmp");
    HDC  Dog      = txLoadImage ("ерк3.bmp");
    HDC  Dog2     = txLoadImage ("ерк3.bmp");
    HDC  Cat      = txLoadImage ("кошка.bmp");
    HDC  LoveCat  = txLoadImage ("колбаса.bmp");

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (TX_BLACK);

        if (!GetAsyncKeyState (VK_SHIFT))  txClear ();

        Photo (Dog1x, Dog1y, Dog2x, Dog2y, Catx, Caty, xmap, ymap,
               t, FonZad, FonSer, Dog, Dog2, LoveCat, Cat, FonPered);

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

        Button  (VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE, 'Q', &Catx, &Caty, &Catvx, &Catvy);

        Touching (Sausagex, Sausagey, Catx, Caty, "Хотите перейти на 2 level???",
                  &FonPered, &FonSer, &FonZad,
                  "Эверест_перед.bmp", "Эверест_середина.bmp", "зад.bmp",
                  &Catx, &Caty);

        Touching (Catx, Caty, Dog1x, Dog1y, "Хотите заново сыграть???",
                  &FonPered, &FonSer, &FonZad,
                  "Тропинка_перед.bmp", "Тропинка_середина.bmp", "Тропинка_зад.bmp",
                  &Catx, &Caty);

        Logic (Dog1x, Dog1y, Catx, Caty, &Dog1vx, &Dog1vy);

        txSleep (10);
        t++;
        }

    }

//===================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Photo (int Dog1x, int Dog1y, int Dog2x, int Dog2y, int Catx, int Caty, int xmap, int ymap,
            int t, HDC FonZad, HDC FonSer, HDC Dog, HDC Dog2, HDC LoveCat, HDC Cat, HDC FonPered)
    {

    txBitBlt         (xmap - Catx/Hero, ymap - Catx/Hero, FonZad);
    txTransparentBlt (xmap,     ymap,     FonSer);

    txTransparentBlt (txDC(),   Dog2x,    Dog2y,    DogX,        DogY,     Dog2,    (t/TimeFact)%2 * DogX);
    txTransparentBlt (txDC(),   Sausagex, Sausagey, SausageX,    SausageY, LoveCat, (t/TimeFact)%2 * SausageX);
    txTransparentBlt (txDC(),   Catx,     Caty,     CatX,        CatY,     Cat,     (t/TimeFact)%2 * CatX);
    txTransparentBlt (txDC(),   Dog1x,    Dog1y,    DogX,        DogY,     Dog,     (t/TimeFact)%2 * DogX);

    txTransparentBlt (xmap + Catx/Hero - 50, ymap + Caty/Hero - 50, FonPered);

    }

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================









