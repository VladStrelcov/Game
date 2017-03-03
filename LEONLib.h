const double Fast  = 0.4;
const int    WinX  = 1000, WinY  = 600;

//=============================================================================

void Button   (int up, int down, int right, int left, int stop, int *vx, int *vy);
void Physics  (int *x, int *y, int *vx, int *vy);
void Logic    (int Dogx, int Dogy, int Catx, int Caty, int *vx, int *vy);
void Touching (int x, int y, int x2, int y2, char BoxAnswer[],
               HDC *FonPered, HDC *FonSer, HDC *FonZad,
               char PeredName[], char SerName[], char ZadName[],
               int *RandX, int *RandY);

//=====================================================================================================================================

void Button (int up, int down, int right, int left, int stop, int *vx, int *vy)
    {

    if (GetAsyncKeyState (up))    (*vy)--;
    if (GetAsyncKeyState (down))  (*vy)++;
    if (GetAsyncKeyState (left))  (*vx)--;
    if (GetAsyncKeyState (right)) (*vx)++;
    if (GetAsyncKeyState (stop))  (*vx) = (*vy) = 0;

    }

void Physics(int *x, int *y, int *vx, int *vy)
    {

    *x = ROUND (*x + *vx * Fast);
    *y = ROUND (*y + *vy * Fast);

    if (*y >= WinY - 50)
        {
        *vy = -*vy;
        }

    if (*x >= WinX - 50)
        {
        *vx = -*vx;
        }

    if (*x <= 50)
        {
        *vx = -*vx;
        }

    if (*y <= 50)
        {
        *vy = -*vy;
        }

    }

void Logic (int Dogx, int Dogy, int Catx, int Caty, int *vx, int *vy)
    {

    *vx = -(Dogx - Catx) / 15;
    *vy = -(Dogy - Caty) / 15;

    }

void  Touching (int x, int y, int x2, int y2, char BoxAnswer[],
                HDC *FonPered, HDC *FonSer, HDC *FonZad,
                char PeredName[], char SerName[], char ZadName[],
                int *RandX, int *RandY)
    {

    double Distance = sqrt ((x-x2)*(x-x2)+(y-y2)*(y-y2));

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

            *RandX  = rand()/65;
            *RandY  = rand()/65;

            }

        }

    }

//=======================================================================================================================




