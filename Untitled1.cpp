#include "TXLib.h"

const double Fast     = 0.4;

const int    WinX     = 1350,  WinY     = 750;
const int    DogX     = 150,   DogY     = 150;
const int    CatX     = 100,   CatY     = 99;
const int    SausageX = 90,    SausageY = 50;
const int    Sausagex = 1250,  Sausagey = 100;
const int    Hero     = 30;
const int    TimeFact = 4;

const char   Level1Pered[] = "тропинка_перед.bmp";
const char   Level1Ser[]   = "тропинка_середина.bmp";
const char   Leve1lZad[]   = "тропинка_зад.bmp";

const char   Level2Pered[] = "Ёверест_перед.bmp";
const char   Level2Ser[]   = "Ёверест_середина.bmp";
const char   Level2Zad[]   = "Ёверест_зад.bmp";

const char   Player1[]     = "кошка.bmp";
const char   Player2[]     = "ерк3.bmp";

const char   LovePlayer[]  = "колбаса.bmp";
const char   Scoreboard[]  = "табло.bmp";

#include "LEONLib.h"

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Game            ();

void RenderScreen    (int Dog1x, int Dog1y, int Dog2x, int Dog2y, int Catx, int Caty, int xmap, int ymap,
                      int t, HDC FonZad, HDC FonSer, HDC Dog, HDC Dog2, HDC LoveCat, HDC Cat, HDC FonPered, HDC TimeGame);

void DrawTime        (int timeStart);

void Downloud (HDC *FonPered, HDC *FonSer, HDC *FonZad, HDC *Dog, HDC *Dog2, HDC *Cat, HDC *LoveCat, HDC *TimeGame);

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
    int Dog1x    = 900,  Dog1y  = 300, Dog1vx  = 3, Dog1vy  = 3;
    int Dog2x    = 600,  Dog2y  = 300, Dog2vx  = 3, Dog2vy  = 3;
    int Catx     = 150,  Caty   = 300, Catvx   = 0, Catvy   = 0;
    int xmap     = 0,    ymap   = 0;
    int t        = 0;

    HDC FonPered = NULL, FonSer = NULL, FonZad = NULL, Dog = NULL, Dog2 = NULL, Cat = NULL, LoveCat = NULL, TimeGame = NULL;

    Downloud (&FonPered, &FonSer, &FonZad, &Dog, &Dog2, &Cat, &LoveCat, &TimeGame);

    txSelectFont ("Arial", 35);

    int timeStart = GetTickCount();

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (TX_BLACK);

        if (!GetAsyncKeyState (VK_SHIFT))  txClear ();

        RenderScreen (Dog1x, Dog1y, Dog2x, Dog2y, Catx, Caty, xmap, ymap,
                      t, FonZad, FonSer, Dog, Dog2, LoveCat, Cat, FonPered, TimeGame);

        Physics  (&Dog1x, &Dog1y, &Dog1vx, &Dog1vy);
        Physics  (&Dog2x, &Dog2y, &Dog2vx, &Dog2vy);
        Physics  (&Catx,  &Caty,  &Catvx,  &Catvy);

        Button   (VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE, 'Q', &Catx, &Caty, &Catvx, &Catvy);

        LeftRightWindow (VK_NUMPAD4, VK_NUMPAD6, &xmap, &ymap);

        Touching (Sausagex,  Sausagey, Catx, Caty, "’отите перейти на 2 level???",
                  &FonPered, &FonSer,  &FonZad, Level2Pered, Level2Ser, Level2Zad, &Catx, &Caty);

        Touching (Catx, Caty, Dog1x,   Dog1y, "’отите заново сыграть???",
                  &FonPered,  &FonSer, &FonZad, Level2Pered, Level2Ser, Level2Zad, &Catx, &Caty);

        Logic    (Dog1x, Dog1y, Catx, Caty, &Dog1vx, &Dog1vy);

        DrawTime (timeStart);

        if ((GetTickCount() - timeStart)/1000 > 10)
            {
            break;
            }

        txSleep (10);
        t++;
        }

    }

//===================================================================================================================================================================================================================================================================================================================================================================================================================================================

void RenderScreen (int Dog1x, int Dog1y, int Dog2x, int Dog2y, int Catx, int Caty, int xmap, int ymap,
                   int t, HDC FonZad, HDC FonSer, HDC Dog, HDC Dog2, HDC LoveCat, HDC Cat, HDC FonPered, HDC TimeGame)
    {

    txBitBlt         (xmap - Catx/Hero + 50,   ymap - Catx/Hero,                FonZad);
    txTransparentBlt (xmap,               ymap,                            FonSer);

    txTransparentBlt (txDC(),   Dog2x,    Dog2y,    DogX,        DogY,     Dog2,    (t/TimeFact)%2 * DogX);
    txTransparentBlt (txDC(),   Sausagex, Sausagey, SausageX,    SausageY, LoveCat, (t/TimeFact)%2 * SausageX);
    txTransparentBlt (txDC(),   Catx,     Caty,     CatX,        CatY,     Cat,     (t/TimeFact)%2 * CatX);
    txTransparentBlt (txDC(),   Dog1x,    Dog1y,    DogX,        DogY,     Dog,     (t/TimeFact)%2 * DogX);

    txTransparentBlt (xmap + Catx/Hero - 50,        ymap + Caty/Hero - 50, FonPered);

    txTransparentBlt (txDC(), 0, 0, 100, 70, TimeGame);

    }

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void DrawTime (int timeStart)
    {
    int time = GetTickCount();
    char Temporary [50] = "";
    sprintf    (Temporary, "%d", (time-timeStart)/1000);
    txSetColor (TX_YELLOW);
    txDrawText (0, 25, 100, 70, Temporary);
    }

void Downloud (HDC *FonPered, HDC *FonSer, HDC *FonZad, HDC *Dog, HDC *Dog2, HDC *Cat, HDC *LoveCat, HDC *TimeGame)
    {

    *FonPered = txLoadImage (Level1Pered);
    *FonSer   = txLoadImage (Level1Ser);
    *FonZad   = txLoadImage (Leve1lZad);
    *Dog      = txLoadImage (Player2);
    *Dog2     = txLoadImage (Player2);
    *Cat      = txLoadImage (Player1);
    *LoveCat  = txLoadImage (LovePlayer);
    *TimeGame = txLoadImage (Scoreboard);

    }








