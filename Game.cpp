#include "TXLib.h"

const double Fast          = 0.4;
const int    TimeGameFast  = 10;

const int    Stop          = 0,
             Continue      = 1;

const int    WinX          = 1350, WinY = 750;
const int    HeroOfWindow  = 30;
const int    TimeFact      = 4;

const char   Level1Pered[] = "тропинка_перед.bmp";
const char   Level1Ser[]   = "тропинка_середина.bmp";
const char   Level1Zad[]   = "тропинка_зад.bmp";

const char   Level2Pered[] = "Эверест_перед.bmp";
const char   Level2Ser[]   = "Эверест_середина.bmp";
const char   Level2Zad[]   = "Эверест_зад.bmp";

const char   Player1[]     = "кошка.bmp";
const char   Player2[]     = "ерк3.bmp";

const char   LovePlayer[]  = "колбаса.bmp";
const char   Scoreboard[]  = "табло.bmp";

#include "LEONLib.h"

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Game                          ();

void RenderScreen                  (Hero* heroCat, Hero* heroDog2, Hero* heroDog1, Hero* heroSausage, int xmap, int ymap,
                                    int t, HDC FonZad, HDC FonSer, HDC Dog, HDC Dog2, HDC LoveCat, HDC Cat, HDC FonPered, HDC TimeGame);

void DrawTime                      (int timeStart);

void Downloud                      (HDC *FonPered, HDC *FonSer, HDC *FonZad, HDC *Dog, HDC *Dog2, HDC *Cat, HDC *LoveCat, HDC *TimeGame);

//===================================================================================================================================================================================================================================================================================================================================================================================================================================================

int main()
    {
    txCreateWindow                 (WinX, WinY);
    txBegin                        ();

    Game                           ();

    return 0;
    }

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Game()
    {

    Hero Dog1    = {900,  300, 3, 3, 150, 150};
    Hero Dog2    = {600,  300, 3, 3, 150, 150};
    Hero Cat     = {150,  300, 0, 0, 100, 99};
    Hero Sausage = {1250, 100, 0, 0, 90,  50};

    int xmap     = 0, ymap   = 0;
    int t        = 0;

    HDC FonPered = NULL, FonSer = NULL, FonZad = NULL, Dog = NULL, Dog2Image = NULL, CatImage = NULL, LoveCat = NULL, TimeGame = NULL;

    Downloud                       (&FonPered, &FonSer, &FonZad, &Dog, &Dog2Image, &CatImage, &LoveCat, &TimeGame);


    txSelectFont                   ("Arial", 35);

    int timeStart = GetTickCount();

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor             (TX_BLACK);

        if (!GetAsyncKeyState      (VK_SHIFT))  txClear ();

        RenderScreen               (&Cat, &Dog2, &Dog1, &Sausage, xmap, ymap,
                                    t, FonZad, FonSer, Dog, Dog2Image, LoveCat, CatImage, FonPered, TimeGame);

        Physics                    (&Dog1);
        Physics                    (&Dog2);
        Physics                    (&Cat);

        Button                     (VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE, 'Q', &Cat, &Sausage);

        LeftRightWindow            (VK_NUMPAD4, VK_NUMPAD6, &xmap, &ymap);

        int StopGame = Touching    (&Sausage,  &Cat,    "Хотите перейти на 2 level???",
                                    &FonPered, &FonSer,  &FonZad, Level2Pered, Level2Ser, Level2Zad);

        StopGame     = Touching    (&Cat, &Dog1, "Хотите заново сыграть???",
                                    &FonPered,  &FonSer, &FonZad, Level1Pered, Level1Ser, Level1Zad);

        Logic                      (&Dog1, &Cat);

        DrawTime                   (timeStart);

        StopGame    = UpdateTime   (&Cat, &timeStart, "Вы ПРОИГРАЛИ, вы ЛУЗЕР!!! ",
                                    &FonPered,  &FonSer, &FonZad, Level1Pered, Level1Ser, Level1Zad);

        if (StopGame == Stop)
            {
            break;
            }

        txSleep (10);
        t++;
        }

    }

//===================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Downloud      (HDC *FonPered, HDC *FonSer, HDC *FonZad, HDC *Dog, HDC *Dog2, HDC *Cat, HDC *LoveCat, HDC *TimeGame)
    {

    *FonPered = txLoadImage (Level1Pered);
    *FonSer   = txLoadImage (Level1Ser);
    *FonZad   = txLoadImage (Level1Zad);
    *Dog      = txLoadImage (Player2);
    *Cat      = txLoadImage (Player1);
    *LoveCat  = txLoadImage (LovePlayer);
    *TimeGame = txLoadImage (Scoreboard);

    }

void RenderScreen  (Hero* heroCat, Hero* heroDog2, Hero* heroDog1, Hero* heroSausage, int xmap, int ymap,
                    int t, HDC FonZad, HDC FonSer, HDC Dog, HDC Dog2, HDC LoveCat, HDC Cat, HDC FonPered, HDC TimeGame)
    {

    txBitBlt         (xmap - (*heroCat).x/HeroOfWindow + 50,   ymap - (*heroCat).x/HeroOfWindow,                FonZad);
    txTransparentBlt (xmap, ymap, FonSer);

    txTransparentBlt (txDC(), (*heroDog1).x,    (*heroDog1).y,    (*heroDog1).SizeImageX,    (*heroDog1).SizeImageY,    Dog,    (t/TimeFact)%2 * (*heroDog1).SizeImageX);
    txTransparentBlt (txDC(), (*heroSausage).x, (*heroSausage).y, (*heroSausage).SizeImageX, (*heroSausage).SizeImageY, LoveCat, (t/TimeFact)%2 * (*heroSausage).SizeImageX);
    txTransparentBlt (txDC(), (*heroCat).x,     (*heroCat).y,     (*heroCat).SizeImageX,     (*heroCat).SizeImageY,     Cat,     (t/TimeFact)%2 * (*heroCat).SizeImageX);
    txTransparentBlt (txDC(), (*heroDog2).x,    (*heroDog2).y,    (*heroDog2).SizeImageX,    (*heroDog2).SizeImageY,    Dog,     (t/TimeFact)%2 * (*heroDog2 ).SizeImageX);

    txTransparentBlt (xmap + (*heroCat).x/HeroOfWindow - 50,   ymap + (*heroCat).y/HeroOfWindow - 50, FonPered);

    txTransparentBlt (txDC(), 0, 0, 100, 70, TimeGame);

    }

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void DrawTime      (int timeStart)
    {
    int  time           = GetTickCount();

    char Temporary [50] = "";

    sprintf    (Temporary, "%d", (time-timeStart)/1000);
    txSetColor (TX_YELLOW);
    txDrawText (0, 25, 100, 70, Temporary);
    }

