const double Fast  = 0.4;
const int    WinX  = 1000, WinY  = 600;

//=============================================================================

void Button  (int up, int down, int right, int left, int stop, int *vx, int *vy);
void Physics (int *x, int *y, int *vx, int *vy);
void Logic   (int Dogx, int Dogy, int Catx, int Caty, int *vx, int *vy);

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

//=======================================================================================================================




