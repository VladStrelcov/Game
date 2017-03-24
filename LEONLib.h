struct Hero
    {
    int x,  y;
    int vx, vy;
    int SizeImageX, SizeImageY;
    };

void Button          (int up, int down, int right, int left, int stop, int crax, Hero* hero);

void Physics         (Hero* hero);

void Logic           (Hero* hero,  Hero* hero2, int *vx, int *vy);

int  Touching        (Hero* hero, Hero* hero2, char BoxAnswer[],
                      HDC *FonPered, HDC *FonSer, HDC *FonZad, char PeredName[], char SerName[], char ZadName[]);

int  UpdateTime      (Hero* hero, int *timeStart, char BoxAnswer[],
                      HDC *FonPered, HDC *FonSer, HDC *FonZad, const char PeredName[], const char SerName[], const char ZadName[]);

void LeftRightWindow (int Left, int Right, int *xmap, int *ymap);

//=====================================================================================================================================

void Button (int up, int down, int right, int left, int stop, int crax, Hero* hero, Hero* Sausage)
    {

    if (GetAsyncKeyState (up))    ((*hero).vy)--;
    if (GetAsyncKeyState (down))  ((*hero).vy)++;
    if (GetAsyncKeyState (left))  ((*hero).vx)--;
    if (GetAsyncKeyState (right)) ((*hero).vx)++;
    if (GetAsyncKeyState (stop))  ((*hero).vx) = ((*hero).vy) = 0;

    if (GetAsyncKeyState (crax))
       {
       (*hero).x = (*Sausage).x;
       (*hero).y = (*Sausage).y;
       }
    }

void Physics (Hero* hero)
    {

    (*hero).x = ROUND ((*hero).x + (*hero).vx * Fast);
    (*hero).y = ROUND ((*hero).y + (*hero).vy * Fast);

    if ((*hero).y >= WinY - 50)
        {
        (*hero).vy = -(*hero).vy;
        }

    if ((*hero).x >= WinX - 50)
        {
        (*hero).vx = -(*hero).vx;
        }

    if ((*hero).x <= 50)
        {
        (*hero).vx = -(*hero).vx;
        }

    if ((*hero).y <= 50)
        {
        (*hero).vy = -(*hero).vy;
        }

    }

void Logic ( Hero* hero,  Hero* hero2)
    {

    (*hero).vx = -((*hero).x - (*hero2).x) / 15;
    (*hero).vy = -((*hero).y - (*hero2).y) / 15;

    }

int   Touching (Hero* hero, Hero* hero2, char BoxAnswer[],
                HDC *FonPered, HDC *FonSer, HDC *FonZad, const char PeredName[], const char SerName[], const char ZadName[])
    {

    double Distance = sqrt ( ((*hero).x - (*hero2).x) * ((*hero).x - (*hero2).x) + ((*hero).y - (*hero2).y) * ((*hero).y - (*hero2).y));

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

            (*hero2).x  = rand()/65;
            (*hero2).y  = rand()/65;

            return Continue;
            }
        else
            {
            return Stop;
            }

        }

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

                    (*hero).x  = rand()/65;
                    (*hero).y  = rand()/65;

                    return Continue;
                    }
                else
                    {
                    return Stop;
                    }

                }
    return Continue;
    }

void LeftRightWindow (int Left, int Right, int *xmap, int *ymap)
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




