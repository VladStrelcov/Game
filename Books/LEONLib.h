
struct Hero
    {
    int x,  y;
    int vx, vy;
    int SizeImageX, SizeImageY;

    HDC Image;

    void Photo   ();
    void Physics ();
    void Button  (int up, int down, int right, int left, int stop, int crax, Hero* Sausage);
    };

struct Network
    {
    int x,  y;
    };

//=====================================================================================================================================

void Logic           (Hero* hero,  Hero* hero2);

int  Touching        (Hero* hero, Hero* hero2, char BoxAnswer[],
                      HDC *FonPered, HDC *FonSer, HDC *FonZad, const char PeredName[], const char SerName[], const char ZadName[]);

int  UpdateTime      (Hero* hero, int *timeStart, char BoxAnswer[],
                      HDC *FonPered, HDC *FonSer, HDC *FonZad, const char PeredName[], const char SerName[], const char ZadName[]);

void LeftRightWindow (int Left, int Right, int *xmap, int *ymap);

//=====================================================================================================================================

void Hero::Button (int up, int down, int right, int left, int stop, int crax, Hero* Sausage)
    {

    if (GetAsyncKeyState (up))    (vy)--;
    if (GetAsyncKeyState (down))  (vy)++;
    if (GetAsyncKeyState (left))  (vx)--;
    if (GetAsyncKeyState (right)) (vx)++;
    if (GetAsyncKeyState (stop))  (vx) = (vy) = 0;

    if (GetAsyncKeyState (crax))
       {
       x = (*Sausage).x;
       y = (*Sausage).y;
       }
    }

void Hero::Physics ()
    {

    x = ROUND (x + vx * Fast);
    y = ROUND (y + vy * Fast);

    if (y >= WinY - 50)
        {
        vy = -vy;
        }

    if (x >= WinX - 50)
        {
        vx = -vx;
        }

    if (x <= 50)
        {
        vx = -vx;
        }

    if (y <= 50)
        {
        vy = -vy;
        }

    }

void Hero::Photo ()
    {

    txTransparentBlt (txDC(), x, y, SizeImageX, SizeImageY, Image, 0, 0, TX_WHITE);

    }

void Logic ( Hero* hero,  Hero* hero2)
    {

    hero->vx = -(hero->x - hero2->x) / 15;
    hero->vy = -(hero->y - hero2->y) / 15;

    }

int  Touching (Hero* hero, Hero* hero2, char BoxAnswer[],
               HDC *FonPered, HDC *FonSer, HDC *FonZad, const char PeredName[], const char SerName[], const char ZadName[])
    {

    double Distance = sqrt ( (hero->x - hero2->x) * (hero->x - hero2->x) + (hero->y - hero2->y) * (hero->y - hero2->y));

    if (Distance <= 50)
        {

        int Answer = txMessageBox (BoxAnswer,"бнопня???", MB_YESNO);
        if (Answer == IDYES)
            {

            txDeleteDC (*FonPered);
            txDeleteDC (*FonSer);
            txDeleteDC (*FonZad);

            *FonPered = txLoadImage (PeredName);
            *FonSer   = txLoadImage (SerName);
            *FonZad   = txLoadImage (ZadName);

            hero2->x  = rand()/65;
            hero2->y  = rand()/65;

            return Continue;
            }
        else
            {
            return Stop;
            }

        }

    return Continue;
    }

int  UpdateTime (Hero* hero, int *timeStart, char BoxAnswer[],
                 HDC *FonPered, HDC *FonSer, HDC *FonZad, const char PeredName[], const char SerName[], const char ZadName[])
    {
    if ((GetTickCount() - *timeStart)/1000 > TimeGameFast)
                {
                int Answer = txMessageBox (BoxAnswer,"Game", MB_YESNO);
                if (Answer == IDYES)
                    {
                    *timeStart = GetTickCount();

                    txDeleteDC (*FonPered);
                    txDeleteDC (*FonSer);
                    txDeleteDC (*FonZad);

                    *FonPered = txLoadImage (PeredName);
                    *FonSer   = txLoadImage (SerName);
                    *FonZad   = txLoadImage (ZadName);

                    hero->x  = rand()/65;
                    hero->y  = rand()/65;

                    return Continue;
                    }
                else
                    {
                    return Stop;
                    }

                }
    return Continue;
    }

void LeftRightWindow (int Left, int Right, int *xmap, int */*ymap*/)
    {

    if (GetAsyncKeyState (Left))
        {
        (*xmap)--;
        }
    if (GetAsyncKeyState (Right))
        {
        (*xmap)++;
        }

    }

//=====================================================================================================================================




