#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

void MeniuPrincipal(int nr_butoane);
void MeniuStart();
void MeniuInfo();
void MeniuGrafic(char s[]);

int scrH = getmaxheight();
int scrW = getmaxwidth();

const double epsilon = 0.0001;
const int infinit = 999999;

bool minim, maxim;
bool apasat_as = false;
//facem doua stive, una pentru operatori si una pentru operanzi
struct nod1
{
    double info;
    nod1 *urm;
};

struct nod2
{
    char info;
    nod2 *urm;
};

struct operanzi
{
    int lungime;
    nod1 *prim;
};

struct operatori
{
    int lungime;
    nod2 *prim;
};

void initializare1(operanzi &Opd)
{
    Opd.lungime = 0;
    Opd.prim = NULL;
}

void initializare2(operatori &Op)
{
    Op.lungime = 0;
    Op.prim = NULL;
}

bool esteVida1(operanzi Opd)
{
    return Opd.prim == 0;
}

bool esteVida2(operatori Op)
{
    return Op.prim == 0;
}

double top1(operanzi &Opd)
{
    return Opd.prim->info;
}

char top2(operatori &Op)
{
    return Op.prim->info;
}

void push1(operanzi &Opd, double x)
{
    nod1 *a = new nod1;
    a->info = x;
    a->urm = NULL;
    if (esteVida1(Opd))
    {
        Opd.lungime = 1;
        Opd.prim = a;
    }
    else
    {
        Opd.lungime++;
        a->urm = Opd.prim;
        Opd.prim = a;
    }
}

void push2(operatori &Op, char c)
{
    nod2 *a = new nod2;
    a->info = c;
    a->urm = NULL;
    if (esteVida2(Op))
    {
        Op.lungime = 1;
        Op.prim = a;
    }
    else
    {
        Op.lungime++;
        a->urm = Op.prim;
        Op.prim = a;
    }
}

void pop1(operanzi &Opd)
{
    if (!esteVida1(Opd))
    {
        nod1 *a = Opd.prim->urm;
        delete Opd.prim;
        Opd.prim = a;
        Opd.lungime--;
    }
}

void pop2(operatori &Op)
{
    if (!esteVida2(Op))
    {
        nod2 *a = Op.prim->urm;
        delete Op.prim;
        Op.prim = a;
        Op.lungime--;
    }
}

int prioritate(char c)
{
    if( c == '(' || c == ')') return 0;
    if( c == '+' || c == '-') return 1;
    if( c == '*' || c == '/') return 2;
    if( c == '^') return 3;
    if( c == '#' || c == '=' || c == '<' ||  c == '>') return 4;
    if( c == 'a' || c == 'r' || c == 'l' || c == 's' || c == 'c') return 5;
}
//trebuie definit un epsilon=0.0001 si un infinit = 999999
double logaritm( double x)
{
    //if(x > epsilon && x < infinit)
    return log(x);
}

double inmultire(double a, double b)
{
    return a*b;
}

double radical(double a)
{
    //if(a > epsilon)
    return sqrt(a);
}

double putere(double a, double b)
{
    return pow(a, b);
}

double impartire( double a, double b)
{
    // if(abs(b) > epsilon)
    return a/b;
    // else
    //     return infinit;
}

int egal(double a, double b)
{
    if(a == b)
        return 1;
    return 0;
}

int diferit( double a, double b)
{
    if(a == b)
        return 0;
    return 1;
}

int maiMic(double a, double b)
{
    if( a < b)
        return 1;
    return 0;
}

int maiMare(double a, double b)
{
    if(a > b)
        return 1;
    return 0;
}

double adunare(double a, double b)
{
    return a+b;
}

double scadere(double a, double b)
{
    return a-b;
}

double sinus(double a)
{
    //if( a <=1 && a>= -1)
    return sin(a);
}

double cosinus(double a)
{
    //if( a <=1 && a>= -1)
    return cos(a);
}

double modul(double a)
{
    // if(a >= infinit)
    //     return infinit;
    // else
    return abs(a);
}

int esteOperator(char c)
{
    switch(c)
    {
    case '(':
    {
        return 1;
        break;
    }
    case ')':
    {
        return 1;
        break;
    }
    case '+':
    {
        return 1;
        break;
    }
    case '-':
    {
        return 1;
        break;
    }
    case '*':
    {
        return 1;
        break;
    }
    case '/':
    {
        return 1;
        break;
    }
    case 'a':
    {
        return 1;
        break;
    }
    case 's':
    {
        return 1;
        break;
    }
    case 'c':
    {
        return 1;
        break;
    }
    case 'r':
    {
        return 1;
        break;
    }
    case 'l':
    {
        return 1;
        break;
    }
    case '^':
    {
        return 1;
        break;
    }
    }
    return 0;
}

void afiseazaStiva1(operanzi Opd)
{
    while(!esteVida1(Opd))
    {
        cout<< Opd.prim->info << " ";
        Opd.prim = Opd.prim->urm;
    }
    cout<< endl;
}
void afiseazaStiva2(operatori Op)
{
    while(!esteVida2(Op))
    {
        cout<< Op.prim->info << " ";
        Op.prim = Op.prim->urm;
    }
    cout<< endl;
}
int esteNumar(char c)
{
    if(c >= '0' && c <= '9')
        return c - '0';
    return -1;
}

double functie(char s[100], double x)
{
    operatori Op;
    initializare2(Op);
    push2(Op,'(');
    operanzi Opd;
    initializare1(Opd);
    int i = 0;
    while(Op.lungime && i < strlen(s))
    {
        if(esteOperator(s[i]))
        {
            if(s[i] == '(')
                push2(Op,s[i]);
            if(s[i]==')')
            {
                nod2 *t = new nod2;
                t = Op.prim;
                while(t && t->info != '(')
                {
                    double a = top1(Opd);
                    pop1(Opd);
                    switch(t->info)
                    {
                    case'+':
                    {
                        Opd.prim->info = adunare(Opd.prim->info, a);
                        break;
                    }
                    case'-':
                    {
                        Opd.prim->info = scadere(Opd.prim->info, a);
                        break;
                    }
                    case'*':
                    {
                        Opd.prim->info = inmultire(Opd.prim->info, a);
                        break;
                    }
                    case'/':
                    {
                        Opd.prim->info = impartire(Opd.prim->info, a);
                        break;
                    }
                    case'^':
                    {
                        Opd.prim->info = putere(Opd.prim->info, a);
                        break;
                    }
                    case'a':{
                            a = modul(a);
                        push1(Opd, a);
                        break;
                    }
                case'l':
                    {
                        a = logaritm(a);
                        push1(Opd, a);
                        break;
                    }
                case'r':
                    {
                        a = radical(a);
                        push1(Opd, a);
                        break;
                    }
                case's':
                    {
                        a = sinus(a);
                        push1(Opd, a);
                        break;
                    }
                case'c':{
                        a = cosinus(a);
                    push1(Opd, a);
                    break;
                }
            }
            pop2(Op);
            t = Op.prim;
        }
        pop2(Op);
    }

    if(s[i] != '(' && s[i] != ')')
    {
        bool ok=1;
        if(prioritate(Op.prim->info) < prioritate(s[i]))
        {
            if(s[i] == '-' && s[i-1] == '(')
                ok = 0;
            if(ok == 1)
                push2(Op,s[i]);
        }
        else
        {
            double a = top1(Opd);
            pop1(Opd);
            switch(Op.prim->info)
            {
            case'+':
                {
                    Opd.prim->info = adunare(Opd.prim->info, a);
                    break;
                }
            case'-':
                {
                    Opd.prim->info = scadere(Opd.prim->info, a);
                    break;
                }
            case'*':
                {
                    Opd.prim->info = inmultire(Opd.prim->info, a);
                    break;
                }
            case'/':
                {
                    Opd.prim->info = impartire(Opd.prim->info, a);
                    break;
                }
            case'^':
                {
                    Opd.prim->info = putere(Opd.prim->info, a);
                    break;
                }
            case'a':{
                    a = modul(a);
                push1(Opd, a);
                break;
            }
        case'l':
            {
                a = logaritm(a);
                push1(Opd, a);
                break;
            }
        case'r':
            {
                a = radical(a);
                push1(Opd, a);
                break;
            }
        case's':
            {
                a = sinus(a);
                push1(Opd, a);
                break;
            }
        case'c':{
                a = cosinus(a);
            push1(Opd, a);
            break;
        }

    }
    pop2(Op);
    push2(Op,s[i]);
}
}
}
else
{
    if(s[i] == 'x') push1(Opd,x);
    if(s[i] == 'e') push1(Opd,2.718);
    if(s[i] == 'p') push1(Opd,3.14);
    if(esteNumar(s[i]) != -1)
    {
        bool ok=1;
        if(i > 1 && s[i-1] == '-' && s[i-2] == '(')
            ok=0;
        int j = i, contor_pozitie = -1, k;
        double a = 0, b;
        while((esteNumar(s[j]) != -1 || s[j] == '.') && j < strlen(s))
        {
            if(esteNumar(s[j]) != -1)
                a = a*10 + esteNumar(s[j]);
            else
            {
                j++;
                k = 0;
                b = 0;
                contor_pozitie++;
                while(esteNumar(s[j]) != -1)
                {
                    b = b*10 + esteNumar(s[j]);
                    k++;
                    j++;
                    contor_pozitie++;
                }
                b = b/pow(10,k);
                a = a+b;
                j--;
                contor_pozitie--;
            }
            j++;
            contor_pozitie++;
        }
        if(ok)
            push1(Opd, a);
        else
        {
            a = 0-a;
            push1(Opd, a);
        }
        i = i + contor_pozitie;
    }
}
i++;
}
if(Op.lungime)
{
    if(Op.lungime == 1 && Op.prim->info == '(')
        pop2(Op);
    else
    {
        nod2 *t = new nod2;
        t = Op.prim;
        while(t && t->info != '(')
        {
            double a = top1(Opd);
            pop1(Opd);
            switch(t->info)
            {
            case'+':
                {
                    Opd.prim->info = adunare(Opd.prim->info, a);
                    break;
                }
            case'-':
                {
                    Opd.prim->info = scadere(Opd.prim->info, a);
                    break;
                }
            case'*':
                {
                    Opd.prim->info = inmultire(Opd.prim->info, a);
                    break;
                }
            case'/':
                {
                    Opd.prim->info = impartire(Opd.prim->info, a);
                    break;
                }
            case'^':
                {
                    Opd.prim->info = putere(Opd.prim->info, a);
                    break;
                }
            case'a':{
                    a = modul(a);
                push1(Opd, a);
                break;
            }
        case'l':
            {
                a = logaritm(a);
                push1(Opd, a);
                break;
            }
        case'r':
            {
                a = radical(a);
                push1(Opd, a);
                break;
            }
        case's':
            {
                a = sinus(a);
                push1(Opd, a);
                break;
            }
        case'c':{
                a = cosinus(a);
            push1(Opd, a);
            break;
        }
    }
    pop2(Op);
    t = Op.prim;
}
pop2(Op);
}
}
return top1(Opd);
}

//converteste nr din int in char
void number(char s[],int n, int &k)
{
    if(n % 10 == 0)
        s[k++] = '0';
    if(n % 10 == 1)
        s[k++] = '1';
    if(n % 10 == 2)
        s[k++] = '2';
    if(n % 10 == 3)
        s[k++] = '3';
    if(n % 10 == 4)
        s[k++] = '4';
    if(n % 10 == 5)
        s[k++] = '5';
    if(n % 10 == 6)
        s[k++] = '6';
    if(n % 10 == 7)
        s[k++] = '7';
    if(n % 10 == 8)
        s[k++] = '8';
    if(n % 10 == 9)
        s[k++] = '9';
}

void converter(int n, char s[])
{
    int k = 0, semn = 1;
    if(n == 0)
        s[k++] = 0;
    if(n < 0)
    {
        semn = 0;
        n *= -1;
    }

    while(n > 0)
    {
        number(s, n, k);
        n /= 10;
    }
    int i = 0;
    if(!semn)
        s[k++] ='-';
    s[k] = NULL;
    k--;
    while(i < k)
    {
        char c = s[i];
        s[i] = s[k];
        s[k] = c;
        i++;
        k--;
    }
}

struct punct_GF
{
    double x, y;
    int viz;
};

///plasam pixelul la fiecare pozitie de pe graficul lui f
void pixel(punct_GF P, int color)
{
    putpixel(P.x, P.y, color);
}

void linie(punct_GF A, punct_GF B)
{
    line(A.x, A.y, B.x, B.y);
}

double minx, maxx;
double miny, maxy;

void Pct_globale(char c[],punct_GF O, double zoom, double start, double endd)
{
    minx = miny = 1e9;
    maxy = maxx = -1e9;
    //zoom = 7.5;
    double x, y;
    if(start == 0 && endd == 2 * scrW)
        start = -scrW;
    for(double i = -scrW; i <= 2 * scrW; i += 0.1)
    {
        x = i - O.x;
        y = -zoom * functie(c, x / zoom) + O.y;
        if(x > maxx)
            maxx = i;
        if(x < minx)
            minx = i;
        if(y > maxy)
            maxy = y;
        if(y < miny)
            miny = y;
    }
}

///zoom = 1.7

void Asimptota_y(char c[], punct_GF O, double zoom, double start, double endd)
{
    double y1,y2;
    y1 = maxy;
    y2 = miny;
    setcolor(GREEN);
    ///maxim
    //cout << y2 << "  |  " << y1 << "\n";
    if(apasat_as == true && y2 > 1)
    {
        //cout << "\n start:" << start <<"\n" << "\n end:" << endd <<"\n" ;
        //cout << "\n y2:" << y2 <<"\n";
        double x, y;
        double i = 0.1;
        x = scrW + i - O.x;
        y = -zoom * functie(c, x / zoom) + O.y;
        while(y <= 0 && y >= scrH)
        {
            i+= 0.1;
            x = scrW + i - O.x;
            y = -zoom * functie(c, x / zoom) + O.y;
        }
        if(y > y2)
            line(0,y2,scrW,y2);
    }
    ///minim
    if(apasat_as == true && y1 < scrH - 1)
    {
        double x, y;

        double i = 0.1;
        x = scrW + i - O.x;
        y = -zoom * functie(c, x / zoom) + O.y;
        while(y <= 0 && y >= scrH)
        {
            i+= 0.1;
            x = scrW + i - O.x;
            y = -zoom * functie(c, x / zoom) + O.y;
        }
        if(y < y1)
            line(0,y1,scrW,y1);

    }
    setcolor(WHITE);
}

int start[100], endd[100], lstart, lend;

void grafic(char c[], punct_GF O, double zoom, int div)
{
    ///O - originea graficului
    ///zoom - zoomul graficului
    //cout << miny << " ";
    ///desenam axele
    ///Ox
    punct_GF A, B;
    A.x = 0;
    A.y = O.y;
    B.x = scrW;
    B.y = O.y;
    linie(A, B);
    ///Oy
    A.x = O.x;
    A.y = 0;
    B.x = O.x;
    B.y = scrH;
    linie(A, B);
    settextstyle(COMPLEX_FONT, 0, 4);
    outtextxy(O.x + 4, O.y + scrH / 128 + 1, "0");
    ///punem "scara" din unitate in unitate
    ///Ox la dreapta
    for(int i = 0; O.x + i * zoom <= scrW; i++)
    {
        A.x = B.x = O.x + i * zoom;
        A.y = O.y - scrH / 128;
        B.y = O.y + scrH / 128;
        if(zoom >= 32.768)
        {
            char s[10];
            converter(i, s);
            //outtextxy(O.x + i * zoom, scrH / 2 + 25, s);
            //settextstyle(4, 0, 1);
            outtextxy(A.x - 3, A.y + 15, s);
            linie(A, B);
        }
        else
        {
            //int div = (int)zoom;
            //div = 2;
            if(i % div == 0)
            {
                if(div <= 7)
                {
                    char s[10];
                    converter(i, s);
                    //outtextxy(O.x + i * zoom, scrH / 2 + 25, s);
                    //settextstyle(4, 0, 1);
                    outtextxy(A.x - 3, A.y + 15, s);
                }
                linie(A, B);
            }
        }
    }
    ///Ox la stg
    for(int i = -1; O.x + i * zoom >= 0; i--)
    {
        A.x = B.x = O.x + i * zoom;
        A.y = O.y - scrH / 128;
        B.y = O.y + scrH / 128;
        if(zoom >= 32.768)
        {
            char s[10];
            converter(i, s);
            //outtextxy(O.x + i * zoom, scrH / 2 + 25, s);
            outtextxy(A.x - 7, A.y + 15, s);//15 daca font == 4
            linie(A, B);
        }
        else
        {
            //int div = (int)zoom;
            //div = 2;
            if(i % div == 0)
            {
                if(div <= 7)
                {
                    char s[10];
                    converter(-i, s);
                    //outtextxy(O.x + i * zoom, scrH / 2 + 25, s);
                    outtextxy(A.x - 7, A.y + 15, s);//15 daca font == 4
                }
                linie(A, B);
            }
        }
    }
    ///Oy in jos
    for(int i = 0; O.y + i * zoom <= scrH; i++)
    {
        A.x = O.x - scrH / 128;
        A.y = B.y = O.y + i * zoom;
        B.x = O.x + scrH / 128;
        if(zoom >= 32.768)
        {
            char s[10];
            converter(-i, s);
            //outtextxy(O.x + i * zoom, scrH / 2 + 25, s);
            outtextxy(A.x + 25, A.y - 7, s);
            linie(A, B);
        }
        else
        {
            //int div = (int)zoom;
            //div = 2;
            if(i % div == 0)
            {
                if(div <= 7)
                {
                    char s[10];
                    converter(-i, s);
                    //outtextxy(O.x + i * zoom, scrH / 2 + 25, s);
                    outtextxy(A.x + 25, A.y - 7, s);
                }
                linie(A, B);
            }
        }
    }
    ///Oy in sus
    for(int i = -1; O.y + i * zoom >= 0; i--)
    {
        A.x = O.x - scrH / 128;
        A.y = B.y = O.y + i * zoom;
        B.x = O.x + scrH / 128;
        if(zoom >= 32.768)
        {
            char s[10];
            converter(-i, s);
            //outtextxy(O.x + i * zoom, scrH / 2 + 25, s);
            outtextxy(A.x + 25, A.y - 7, s);
            linie(A, B);
        }
        else
        {
            //int div = (int)zoom;
            //div = 2;
            if(i % div == 0)
            {
                if(div <= 7)
                {
                    char s[10];
                    converter(-i, s);
                    //outtextxy(O.x + i * zoom, scrH / 2 + 25, s);
                    outtextxy(A.x + 25, A.y - 7, s);
                }
                //cout << zoom << " ";
                linie(A, B);
            }
        }
    }
    ///desenam graficul
    double x, y;
    start[++lstart] = 0;
    punct_GF P;
    punct_GF Lp;
    Lp.viz = 0;
    //cout << "primul y:" << -zoom * functie(c, 0 - O.x) + O.y <<"\n";
    for(double i = 0; i <= scrW; i += 0.1)
    {
        double xd, yd, xs, ys;
        ///calculam x in functie de pozitia in grafic
        x = i - O.x;
        y = -zoom * functie(c, x / zoom) + O.y;
        ///punem linia la (x,y)
        if(y >= 0 && y <= scrH)
        {
            setcolor(CYAN);
            if(Lp.viz == 0)
            {
                Lp.viz = 1;
                Lp.x = i;
                Lp.y = y;
                xd = i + 0.1 - O.x;
                yd = -zoom * functie(c, xd / zoom) + O.y;
                xd = i + 0.1;
                xs = i - 0.1 - O.x;
                ys = -zoom * functie(c, xs / zoom) + O.y;
                xs = i - 0.1;
                if(apasat_as  == true && (ys != Lp.y || isnan(ys) == true))
                {

                    setcolor(GREEN);
                    punct_GF AS1, AS2;
                    AS1.x = Lp.x + 0.1;
                    AS1.y = 0;
                    AS2.x = Lp.x + 0.1;
                    AS2.y = scrH;
                    linie(AS1,AS2);
                }
                if(minim == 1 && yd < Lp.y && (ys < Lp.y || isnan(ys) == true))
                {
                    setcolor(YELLOW);
                    if(maxy > 1 && maxy < scrH - 1)
                        circle(Lp.x, maxy, 20);
                    //cout << "S-a gasit punct de minim in primul if: " << ys << " " << maxy << " " << yd << "\n";
                }
                if(apasat_as  == true && yd > Lp.y && (ys > Lp.y || isnan(ys) == true))
                {
                    setcolor(GREEN);
                    punct_GF AS1, AS2;
                    AS1.x = Lp.x - 0.1;
                    AS1.y = 0;
                    AS2.x = Lp.x - 0.1;
                    AS2.y = scrH;
                    linie(AS1,AS2);
                }
                if(maxim == 1 && yd > Lp.y && (ys > Lp.y || isnan(ys) == true))
                {
                    setcolor(YELLOW);
                    if(miny > 1 && miny < scrH - 1)
                        circle(Lp.x, miny, 20);
                    //cout << "S-a gasit punct de maxim in primul if: " << ys<< " " << miny << " " << yd << "\n";
                }
            }
            else
            {
                P.x = i;
                P.y = y;
                if(abs(P.x - Lp.x) > 1 && apasat_as  == true)
                {
                    endd[++lend] = i;
                    setcolor(GREEN);
                    punct_GF AS1, AS2;
                    AS1.x = Lp.x / 2 + P.x / 2 ;
                    AS1.y = 0;
                    AS2.x = Lp.x / 2 + P.x / 2 ;
                    AS2.y = scrH;
                    linie(AS1,AS2);
                    setcolor(CYAN);
                    start[++lstart] = i;
                }
                if(abs(P.x - Lp.x) < 1)
                {
                    linie(Lp, P);
                    setcolor(YELLOW);
                    if(minim == 1)
                    {
                        xd = i + 0.1 - O.x;
                        yd = -zoom * functie(c, xd / zoom) + O.y;
                        xd = i + 0.1;
                        if(Lp.y < P.y && yd < P.y)
                        {
                            circle(P.x, P.y, 20);
                            //cout << "S-a gasit punct de maxim in al 2 lea if: " << Lp.y << " " << P.y << " " << yd << "\n";
                        }
                    }
                    if(maxim == 1)
                    {
                        xd = i + 0.1 - O.x;
                        yd = -zoom * functie(c, xd / zoom) + O.y;
                        xd = i + 0.1;
                        if(Lp.y > P.y && yd > P.y && Lp.y != P.y && yd != P.y)
                        {
                            circle(P.x, P.y, 20);
                            //cout << "S-a gasit punct de minim in al 2 lea if: " << Lp.y << " " << P.y << " " << yd << "\n";
                        }
                    }
                }
                Lp.x = P.x;
                Lp.y = P.y;
            }
        }
    }
    double xd, yd, xs, ys;
    xs = scrW + 0.1 - O.x;
    ys = -zoom * functie(c, xs / zoom) + O.y;
    if(apasat_as  == true && (ys != P.y || isnan(ys) == true))
    {

        setcolor(GREEN);
        punct_GF AS1, AS2;
        AS1.x = P.x + 0.1;
        AS1.y = 0;
        AS2.x = P.x + 0.1;
        AS2.y = scrH;
        //cout << "linie?!?!!?!?";
        linie(AS1,AS2);
    }
    setcolor(WHITE);
    if(lstart > lend)
        endd[++lend] = scrW;
}

bool esteSemn(char c)
{
    if (c == '-')return true;
    if (c == '+')return true;
    if (c == '*')return true;
    if (c == '^')return true;
    if (c == '/')return true;
    if (c == '=')return true;
    return false;
}

bool verfif_numar(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

bool Check_input(char s[])
{
    int p = 0;
    int huh = 0;
    for (int i = 0; s[i] != NULL; i++)
    {
        if (esteOperator(s[i]) == false && verfif_numar(s[i]) == false && s[i] != 'x')
            return false;
        if (verfif_numar(s[i - 1]) == 1 || s[i] == 'x')
            huh++;
    }
    if (esteSemn(s[0]) && !(s[0] == '-' || s[0] == '+'))
        return false;
    if (huh == 0)return false;
    for (int i = 1; s[i] != NULL; i++)
    {
        ///aparitii x sau cifre
        ///2 semne consecutive
        if (esteSemn(s[i - 1]) == true && esteSemn(s[i]) == true)
            return false;
        ///paranteze corecte
        if (s[i - 1] == '(')
            p++;
        else if (s[i - 1] == ')')
            p--;
        if (p < 0)
            return false;
        //verificarea ultimului elemen
        if (s[i + 1] == ')' && s[i + 2] == NULL && (esteSemn(s[i]) || s[i] =='r' || s[i] =='a' || s[i] == 's' || s[i] == 'c' || s[i] == 'l'))
            return false;
    }
    return true;
}

struct punct
{
    int x,y;
};

struct dreptunghi
{
    punct LU, RD; //left-up, right-down
};

struct buton
{
    int culoare;
    dreptunghi D;
    char text[20];
} B[25];

bool apartine(punct P, dreptunghi D)
{
    return D.LU.x <= P.x && P.x <=D.RD.x && D.LU.y <= P.y && P.y <=D.RD.y;
}

int butonAles(int i1, int i2)
{
    punct p;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN, p.x, p.y);
        for(int i=i1; i<=i2; i++)
        {
            if(apartine(p, B[i].D))
                return i;
        }
    }
    return 0;
}
void DesenareMeniuPrincipal(int nr_butoane)
{
    cleardevice();
    readimagefile("fundal.jpg", 0,0,scrW,scrH);
    setcolor(WHITE);
    int i;
    for(i=1 ; i<=nr_butoane; i++)
    {
        B[i].D.LU.x = scrW/4+80;
        B[i].D.LU.y = scrH/3+150*i;
        B[i].D.RD.x = 3*scrW/4-20;
        B[i].D.RD.y = B[i].D.LU.y + 150;
        switch(i)
        {
        case 1:
            {
                strcpy(B[i].text, "START");
                break;
            }
        case 2:
            {
                strcpy(B[i].text, "INFO");
                break;
            }
        case 3:
            {
                strcpy(B[i].text, "EXIT");
                break;
            }
        }
        //setfillstyle(SOLID_FILL, CYAN);
        rectangle(B[i].D.LU.x, B[i].D.LU.y, B[i].D.RD.x, B[i].D.RD.y);
        settextstyle(COMPLEX_FONT, 0, 10);
        outtextxy(B[i].D.LU.x+(B[i].D.RD.x- B[i].D.LU.x -textwidth(B[i].text))/2, B[i].D.LU.y+13, B[i].text);
    }
}
void MeniuPrincipal(int nr_butoane)
{
    DesenareMeniuPrincipal(nr_butoane);
    int butonul_apasat;
    do
    {
        butonul_apasat = butonAles(1,3);
        switch(butonul_apasat)
        {
        case 1:
            {
                cout<< "start"<<endl;
                MeniuStart();
                DesenareMeniuPrincipal(nr_butoane);
                break;
            }
        case 2:
            {
                cout<< "info"<<endl;
                MeniuInfo();
                DesenareMeniuPrincipal(nr_butoane);
                break;
            }
        case 3:
            {
                cout<< "iesire"<<endl;
                return;
            }
        }
    }
    while(true);
}

void DesenareMeniuStart()
{
    cleardevice();
    readimagefile("fundal_start.jpg", 0,0,scrW,scrH);
    setcolor(WHITE);
    settextstyle(COMPLEX_FONT, 0, 8);
    outtextxy(10,10,"BACK");
    B[4].D.LU.x = 10;
    B[4].D.LU.y = 10;
    B[4].D.RD.x = 210;
    B[4].D.RD.y = 90;
    rectangle(B[4].D.LU.x, B[4].D.LU.y, B[4].D.RD.x, B[4].D.RD.y);
    //desenam butonul de next
    B[5].D.LU.x = scrW-210;
    B[5].D.LU.y = 10;
    B[5].D.RD.x = scrW-10;
    B[5].D.RD.y = 90;
    outtextxy(scrW-210, 10, "NEXT");
    rectangle(B[5].D.LU.x, B[5].D.LU.y, B[5].D.RD.x, B[5].D.RD.y);
    //desenam butonul de info
    B[6].D.LU.x = 10;
    B[6].D.LU.y = scrH-90;
    B[6].D.RD.x = 210;
    B[6].D.RD.y = scrH-10;
    outtextxy(10, scrH-90, "INFO");
    rectangle(B[6].D.LU.x, B[6].D.LU.y, B[6].D.RD.x, B[6].D.RD.y);
    int textboxW = 3.0/4*scrW, textboxH = 80;
    B[7].D.LU.x = 1.0/8 * scrW;
    B[7].D.LU.y = scrH/2 - textboxH/2;
    B[7].D.RD.x = B[7].D.LU.x + textboxW - 1;
    B[7].D.RD.y = B[7].D.LU.y + textboxH - 1;
    rectangle(B[7].D.LU.x, B[7].D.LU.y, B[7].D.RD.x, B[7].D.RD.y);
    settextstyle(COMPLEX_FONT, 0, 7);
    outtextxy(10, scrH/2 - textboxH/2 + 7, "F(x)=");
}

void MeniuStart()
{
    DesenareMeniuStart();
    int butonul_apasat;
    char sir[256] {}, c;
    int k=0;
    do
    {
        butonul_apasat = butonAles(4,7);
        if(butonul_apasat)
            cout<< butonul_apasat <<endl;
        switch(butonul_apasat)
        {
        case 4:
            {
                cout<<"meniu"<<endl;
                return;
            }
        case 5:
            {
                cout<<"grafic"<<endl;
                MeniuGrafic(sir);
                DesenareMeniuStart();
                settextstyle(COMPLEX_FONT, 0, 4);
                outtextxy(B[7].D.LU.x + 10, B[7].D.LU.y + (B[7].D.RD.y - B[7].D.LU.y + 1)/2 - textheight(sir)/2, sir);
                break;
            }
        case 6:
            {
                cout<<"info"<<endl;
                MeniuInfo();
                DesenareMeniuStart();
                settextstyle(COMPLEX_FONT, 0, 4);
                outtextxy(B[7].D.LU.x + 10, B[7].D.LU.y + (B[7].D.RD.y - B[7].D.LU.y + 1)/2 - textheight(sir)/2, sir);
                break;
            }
        case 7:
            {
                c=' ';
                do
                {
                    if(kbhit())
                    {
                        c = getch();
                        if(c == 13)
                            break;
                        else if(c == 8)
                        {
                            if(k > 0)
                                sir[--k] = NULL;
                        }
                        else
                        {
                            sir[k] = c;
                            k++;
                        }
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(B[7].D.LU.x + 1, B[7].D.LU.y + 1, B[7].D.RD.x - 1, B[7].D.RD.y - 1);
                        settextstyle(COMPLEX_FONT, 0, 4);
                        outtextxy(B[7].D.LU.x + 10, B[7].D.LU.y + (B[7].D.RD.y - B[7].D.LU.y + 1)/2 - textheight(sir)/2, sir);
                    }
                }
                while(c);
                break;
            }
        }
    }
    while(true);
}

void MeniuInfo()
{
    cleardevice();
    setcolor(WHITE);
    settextstyle(COMPLEX_FONT, 0, 8);
    outtextxy(10,10,"BACK");
    B[8].D.LU.x = 10;
    B[8].D.LU.y = 10;
    B[8].D.RD.x = 210;
    B[8].D.RD.y = 90;
    rectangle(B[8].D.LU.x, B[8].D.LU.y, B[8].D.RD.x, B[8].D.RD.y);
    settextstyle(COMPLEX_FONT, 0, 4);
    outtextxy(150, 300, "Pentru a folosi anumite functii matematice este nevoie de o sintaxa speciala:");
    outtextxy(200, 420, "- radical = 'r'");
    outtextxy(200, 460, "- logaritm = 'l'");
    outtextxy(200, 500, "- ridicare la putere = '^'");
    outtextxy(200, 540, "- sinus = 's'");
    outtextxy(200, 580, "- cosinus = 'c'");
    outtextxy(200, 620, "- modul = 'a'");
    outtextxy(150, 700, "Dupa ce ati introdus functia de la tastatura este necesara apasarea butonului ENTER");
    int butonul_apasat;
    do
    {
        butonul_apasat = butonAles(8,8);
        cout<<"butonul apasat e"<<butonul_apasat<<endl;
        if(butonul_apasat != 0)
        {
            return;
        }
    }
    while(true);
}

void DesenareMeniuGrafic(bool apasat_min, bool apasat_max, bool apasat_as)
{
    cleardevice();
    setcolor(WHITE);
    settextstyle(COMPLEX_FONT, 0, 8);
    outtextxy(10,10,"BACK");
    B[9].D.LU.x = 10;
    B[9].D.LU.y = 10;
    B[9].D.RD.x = 210;
    B[9].D.RD.y = 90;
    rectangle(B[9].D.LU.x, B[9].D.LU.y, B[9].D.RD.x, B[9].D.RD.y);

    B[10].D.LU.x = 10;
    B[10].D.LU.y = scrH-60;
    B[10].D.RD.x = 60;
    B[10].D.RD.y = scrH-10;
    rectangle(B[10].D.LU.x, B[10].D.LU.y, B[10].D.RD.x, B[10].D.RD.y);
    line(20, scrH-35, 50, scrH-35);

    B[11].D.LU.x = 70;
    B[11].D.LU.y = scrH-60;
    B[11].D.RD.x = 120;
    B[11].D.RD.y = scrH-10;
    rectangle(B[11].D.LU.x, B[11].D.LU.y, B[11].D.RD.x, B[11].D.RD.y);
    line(80, scrH-35, 110, scrH-35);
    line(95, scrH-50, 95, scrH-20);

    settextstyle(COMPLEX_FONT, 0, 4);
    outtextxy(scrW-240, scrH-50, "ASIMPTOTE");
    B[12].D.LU.x = scrW-250;
    B[12].D.LU.y = scrH-60;
    B[12].D.RD.x = scrW-10;
    B[12].D.RD.y = scrH-10;
    rectangle(B[12].D.LU.x, B[12].D.LU.y, B[12].D.RD.x, B[12].D.RD.y);
    setfillstyle(SOLID_FILL, apasat_as ? GREEN : RED);
    rectangle(scrW-50, scrH-50, scrW-20, scrH-20);
    floodfill(scrW-40,scrH-40,WHITE);

    outtextxy(scrW-370, scrH-50, "MAX");
    B[13].D.LU.x = scrW-380;
    B[13].D.LU.y = scrH-60;
    B[13].D.RD.x = scrW-260;
    B[13].D.RD.y = scrH-10;
    rectangle(B[13].D.LU.x, B[13].D.LU.y, B[13].D.RD.x, B[13].D.RD.y);
    setfillstyle(SOLID_FILL, apasat_max ? GREEN : RED);
    rectangle(scrW-300, scrH-50, scrW-270, scrH-20);
    floodfill(scrW-290,scrH-40,WHITE);

    outtextxy(scrW-500, scrH-50, "MIN");
    B[14].D.LU.x = scrW-510;
    B[14].D.LU.y = scrH-60;
    B[14].D.RD.x = scrW-390;
    B[14].D.RD.y = scrH-10;
    rectangle(B[14].D.LU.x, B[14].D.LU.y, B[14].D.RD.x, B[14].D.RD.y);
    setfillstyle(SOLID_FILL, apasat_min ? GREEN : RED);
    rectangle(scrW-430, scrH-50, scrW-400, scrH-20);
    floodfill(scrW-420, scrH-40, WHITE);
}

void MeniuGrafic(char s[])
{
    double zoom = 100;
    double div = 1;
    int ok = 1;
    start[0] = -scrW;
    endd[0] = 2 * scrW;
    //cout <<s << " "<<  Check_input(s);
    //cout<< functie(s,0);
    DesenareMeniuGrafic(minim, maxim, apasat_as);
    punct_GF O;
    O.x = scrW / 2;
    O.y = scrH / 2;
    grafic(s, O, zoom, div);
    for(int i = 0; i <= lstart; i++)
    {
        //cout << "start de " << i << " : " << start[i] <<"\n";
        //cout << "end de " << i << " : " << endd[i] <<"\n";
        Pct_globale(s,O, zoom, start[i], endd[i]);
        Asimptota_y(s,O,zoom, start[i], endd[i]);
    }
    lstart = 0;
    lend = 0;
    ///input
    int butonul_apasat;
    while(true)
    {
        butonul_apasat = butonAles(9,14);
        if(butonul_apasat != 0)
        {
            ///il procesam
            switch(butonul_apasat)
            {
            case 9:
                return;
            case 10:///zoom out
                {
                    zoom*=0.8;//cout << zoom << " ";
                    //cout << zoom << " ";
                    if(zoom > 1.7)
                    {
                        ok++;
                        if(ok % 4 == 0)
                            div += 2;
                    }
                    else
                    {
                        //ok--;
                        MessageBox(0,"Maximul de zoom", "Zoom maxim",MB_ICONINFORMATION);
                    }
                    //cout << ok << " ";
                }
                break;
            case 11:///zoom in
                {
                    zoom/=0.8;
                    if(ok % 4 == 0)
                        div -= 2;
                    ok--;
                    //cout << ok << " ";
                }
                break;
            case 12:
                apasat_as = !apasat_as;
                break;
            case 13:///pct maxim
                maxim = !maxim;
                break;
            case 14:///pct minim
                minim = !minim;
                break;
            }
            ///refacem graficul
            DesenareMeniuGrafic(minim, maxim, apasat_as);
            for(int i = 0; i <= lstart; i++)
            {
                Pct_globale(s,O, zoom, start[i], endd[i]);
                Asimptota_y(s,O,zoom, start[i], endd[i]);
                //cout << "start de " << i << " : " << start[i] <<"\n";
                //cout << "end de " << i << " : " << endd[i] <<"\n";
            }
            lstart = 0;
            lend = 0;
            grafic(s, O, zoom, div);
        }
    }

}
int main()
{
    initwindow(scrW,scrH);
    MeniuPrincipal(3);
    return 0;

}
//-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
