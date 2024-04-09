#include<stdio.h>
#include<malloc.h>
#include "conio2.h"
#define POCZATEK_LEGENDY_X 1
#define POCZATEK_LEGENDY_Y 2
#define POCZATEK_MENU_X 50
#define POCZATEK_MENU_Y 10
#define POCZATEK_WYNIKU_X 1
#define POCZATEK_WYNIKU_Y 11
#define POCZATEK_PLANSZY_X 70
#define POCZATEK_PLANSZY_Y 2
#define POCZATEK_WYJSCIA_Z_PROGRAMU_X 50
#define POCZATEK_WYJSCIA_Z_PROGRAMU_Y 10
#define ZNAK_SRODKOWY 197
#define ZNAK_RAMKI 35
#define ROZMIAR_PLANSZY_NR1 9
#define ROZMIAR_PLANSZY_NR2 13
#define ROZMIAR_PLANSZY_NR3 19
#define ZNAK_ESTETYCZNY 196
#define ZNAK_BIALEGO_PIONKA 254
#define ZNAK_CZARNEGO_PIONKA 111
#define RAMKA 3
#define PUSTE_POLE 0
#define ODDECH 2
#define PIONEK 1
#define BIALY_PIONEK 1
#define CZARNY_PIONEK 2
#define BIALE 1
#define CZARNE 2
#define ZNAK_SPECJALNY 0
#define STRZALKA_W_GORE 72
#define STRZALKA_W_DOL 80
#define STRZALKA_W_LEWO 75
#define STRZALKA_W_PRAWO 77
#define ENTER 13
#define ESC 27
#define ROZPATRZONE 1
#define OKO 2

using namespace std;
struct wspolrzedne // w przypadku n rozmiar planszy
{
    int x, y;
};
struct pozycja // pozycja kursora na konsoli i na planszy
{
    wspolrzedne plansza;
    wspolrzedne konsola;
};
struct stan_gry // zbior informacji potrzebnych do zapisania i wczytania gry w jakimkolwiek jej momencie
{
   wspolrzedne n; // rozmiar planszy
   pozycja pozycja_kursora; // pozycja relatywna na planszy i absolutna na konsoli
   int** p; // plansza glowna
   int** p_kopia; // plansza uzywana przy cofaniu ruchow
   int** p_ko; //plansza do sprawdzania czy zostala naruszona zasada ko
   int czyja_kolej; // 1 - BIALE , 2 - CZARNE
   int zbite_suma[2], zbite_piony[2]; // 0 - BIALE , 1 - CZARNE
   bool czy_zapisano_ruch;
   bool czy_handicap;
};
wspolrzedne wybor_rozmiarow() // zwraca wymiary planszy i wyswietla menu wyboru
{
    char polecenie; // polecenie od gracza
    wspolrzedne n = {0,0};// rozmiar x i y planszy
    gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y);
    cputs("wybierz rozmiar planszy:\n");
    gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y+1);
    cputs("1: 9 x 9\n");
    gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y+2);
    cputs("2: 13 x 13\n");
    gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y+3);
    cputs("3: 19 x 19\n");
    gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y+4);
    cputs("4: rozmiar niestandardowy\n");
    polecenie=getch();
    if(polecenie == '1'){
        n={ROZMIAR_PLANSZY_NR1,ROZMIAR_PLANSZY_NR1};
    }
    else if(polecenie == '2'){
        n={ROZMIAR_PLANSZY_NR2,ROZMIAR_PLANSZY_NR2};
    }
    else if(polecenie == '3'){
        n={ROZMIAR_PLANSZY_NR3,ROZMIAR_PLANSZY_NR3};
    }
    else if(polecenie == '4')
    {
        int tmp = 0;
        clrscr();
        gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y);
        cputs("podaj ilosc kolumn i zatwierdz ENTERem");
        gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y+1);
        while(tmp != ENTER - 48)
        {
            tmp = getche() - 48;
            if(tmp != ENTER - 48)
            {
                n.x = n.x * 10 + tmp;
            }
        }
        tmp = '0';
        clrscr();
        gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y);
        cputs("podaj ilosc wierszy i zatwierdz ENTERem");
        gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y+1);
        while(tmp != ENTER - 48)
        {
            tmp = getche() - 48 ;
            if(tmp != ENTER - 48 )
            {
                n.y = n.y * 10 + tmp;
            }
        }
    }
    clrscr();
    return n;
}
int** p_tworzenie(wspolrzedne n) // tworzy dynamicznie plansze int + miejsce na obramowanie
{
    int **p = (int **) malloc( (n.y+2)*sizeof(int**));
    for(int i=0;i<n.y+2;i++)
    {
        p[i] = (int *) malloc( (n.x+2)*sizeof(int*));
    }
    return p;
}
void p_free(wspolrzedne n, int **p) // tworzy dynamicznie plansze int + miejsce na obramowanie
{
    for(int i=0;i<n.y+2;i++)
    {
        free(p[i]);
    }
    free(p);
}
void legenda()
{
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y);
    cputs("Kamil Cwynar 193377");
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y+1);
    cputs("q: zamkniecie programu");
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y+2);
    cputs("n: rozpoczecie nowej gry");
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y+3);
    cputs("ENTER: potwierdzenie wyboru i zakonczenie tury gracza\n");
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y+4);
    cputs("ESC: anulowanie obecnej akcji");
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y+5);
    cputs("i: polozenie kamienia na planszy");
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y+6);
    cputs("s: zapis stanu gry");
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y+7);
    cputs("l: wczytanie stanu gry");
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y+8);
    cputs("f: zakonczenie gry");
    gotoxy(POCZATEK_LEGENDY_X, POCZATEK_LEGENDY_Y+9);
    cputs("obecna pozycja kusora - ");
}
bool handicap_menu()
{
    char polecenie;
    gotoxy(POCZATEK_MENU_X,POCZATEK_MENU_Y);
    cputs("zastosowac zasady gry z handicapem?");
    gotoxy(POCZATEK_MENU_X,POCZATEK_MENU_Y+1);
    cputs("pierwszy gracz bedzie mial mozliwosc dodania dowolnej ilosci ");
    gotoxy(POCZATEK_MENU_X,POCZATEK_MENU_Y+2);
    cputs("pionow przed kliknieciem entera i rozpoczeciem gry");
    gotoxy(POCZATEK_MENU_X,POCZATEK_MENU_Y+3);
    cputs("1 - tak");
    gotoxy(POCZATEK_MENU_X,POCZATEK_MENU_Y+4);
    cputs("2 - nie");
    polecenie = getch();
    clrscr();
    if(polecenie == '1'){
        return true;
    }
    return false;
}
void wpisz_stan_logiczny_planszy(int** p, wspolrzedne n) // ustawia domyslne wartosci na planszy
{
    for(int i=0;i<n.x+2;i++)
    {
        p[0][i]=RAMKA;
        p[n.y+1][i]=RAMKA;
    }
    for(int i=1;i<n.y+1;i++)
    {
        p[i][0]=RAMKA;
        p[i][n.x+1]=RAMKA;
    }
    for(int i=1;i<n.y+1;i++)
    {
        for(int i2=1;i2<n.x+1;i2++)
        {
            p[i][i2]=PUSTE_POLE;
        }
    }
}
void wypisywanie_liczby(int wartosc) // wypisuje liczby gdy ta moze byc wieksza od 9
{
    int tmp = wartosc;
    char buffer[3];
    int i = 0;
    while(tmp>0)
    {
        buffer[i] = tmp%10;
        tmp/=10;
        i++;
    }
    while(i>0)
    {
        i--;
        putch(buffer[i]+'0');
    }
    cputs("  ");
}
void wyswietlanie_planszy(int** p, wspolrzedne n, int zbite_suma[2], int czyja_kolej)
{
    _setcursortype(_NOCURSOR);
    for(int i=0;i<n.y+2;i++)
    {
         gotoxy(POCZATEK_PLANSZY_X, POCZATEK_PLANSZY_Y+i);
         for(int i2=0;i2<n.x+2;i2++)
         {
             if(p[i][i2] == PUSTE_POLE) // puste pole
             {
                  putch(ZNAK_SRODKOWY);
             }
             else if(p[i][i2] == BIALY_PIONEK) // pole z bialym pionkiem
             {
                  putch(ZNAK_BIALEGO_PIONKA);
             }
             else if(p[i][i2] == CZARNY_PIONEK) // pole z czarnym pionkiem
             {
                  putch(ZNAK_CZARNEGO_PIONKA);
             }
             else if(p[i][i2] == RAMKA)
             {
                  putch(ZNAK_RAMKI);
             }
             if(i2 != n.x+1) putch(ZNAK_ESTETYCZNY);//znak na potrzeby estetyczne pomiedzy polami tablicy
         }
    }
    gotoxy(POCZATEK_WYNIKU_X, POCZATEK_WYNIKU_Y);
    cputs("ilosc zbitych pionkow: BIALE - ");
    wypisywanie_liczby(zbite_suma[BIALE]);
    cputs(" CZARNE - ");
    wypisywanie_liczby(zbite_suma[CZARNE]);
    gotoxy(POCZATEK_WYNIKU_X, POCZATEK_WYNIKU_Y+1);
    cputs("tura "); if(czyja_kolej == CZARNE) cputs("czarnych"); else cputs("bialych ");
    _setcursortype(_SOLIDCURSOR);
}
bool czy_kursor_poza_plansza(wspolrzedne n, wspolrzedne pozycja_kursora, wspolrzedne ruch) // sprawdza czy kursor nie wyjdzie poza obszar planszy po ruchu
{
    if(pozycja_kursora.x+ruch.x<POCZATEK_PLANSZY_X+1 || pozycja_kursora.x+ruch.x>(POCZATEK_PLANSZY_X+1)+2*n.x-1
    || pozycja_kursora.y+ruch.y<POCZATEK_PLANSZY_Y+1 || pozycja_kursora.y+ruch.y>(POCZATEK_PLANSZY_Y+1)+n.y-1)
    {
         return true;
    }
    return false;
}
pozycja ruch_kursora(wspolrzedne n, pozycja pozycja_kursora , char polecenie) // zmienia polozenie kursora na planszy
{
    wspolrzedne ruch;
    if(polecenie == STRZALKA_W_PRAWO){
        ruch = {2,0};     // 2, bo uwzgledniamy znak kosmetyczny pomiedzy kolumnami
    }
    else if(polecenie == STRZALKA_W_LEWO){
        ruch = {-2,0};
    }
    else if(polecenie == STRZALKA_W_DOL){
        ruch = {0,1};
    }
    else if(polecenie == STRZALKA_W_GORE){
        ruch = {0,-1};
    }
    if(czy_kursor_poza_plansza(n,pozycja_kursora.konsola,ruch)==false)
    {
        pozycja_kursora.konsola.x += ruch.x;
        pozycja_kursora.konsola.y += ruch.y;
        pozycja_kursora.plansza.x += (ruch.x/2);
        pozycja_kursora.plansza.y += ruch.y;
    }
    _setcursortype(_NOCURSOR);
    gotoxy(POCZATEK_LEGENDY_X + 26, POCZATEK_LEGENDY_Y + 8);
    wypisywanie_liczby(pozycja_kursora.plansza.x);
    wypisywanie_liczby(pozycja_kursora.plansza.y);
    gotoxy(pozycja_kursora.konsola.x,pozycja_kursora.konsola.y);
    _setcursortype(_SOLIDCURSOR);
    return pozycja_kursora;
}
int** kopia_planszy(int** p_kopia, int** p,wspolrzedne n) // kopiuje zawartosc logiczna planszy do innej planszy
{
    for(int i = 0; i < n.y + 2; i++)
    {
         for(int i2 = 0 ; i2 < n.x + 2 ; i2++)
         {
             p_kopia[i][i2] = p[i][i2];
         }
    }
    return p_kopia;
}
int zmiana_kolei(int czyja_kolej) //zmienia ktory kolor rozpatrujemy przy umieszczaniu pionkow, rozpatrywaniu ODDECHow grup itp
{
    if(czyja_kolej == CZARNE){
        return BIALE;
    }
    else{
        return CZARNE;
    }
}
stan_gry polecenie_ESC(stan_gry stan)
{
    if(stan.czy_zapisano_ruch == false)
    {
        stan.p=kopia_planszy(stan.p, stan.p_kopia, stan.n);
        stan.czy_zapisano_ruch = true;
        stan.zbite_suma[stan.czyja_kolej-1] -= stan.zbite_piony[stan.czyja_kolej-1];
        stan.zbite_piony[stan.czyja_kolej-1] = 0;
        stan.czyja_kolej = zmiana_kolei(stan.czyja_kolej);
        wyswietlanie_planszy(stan.p,stan.n,stan.zbite_suma,stan.czyja_kolej);
        gotoxy(stan.pozycja_kursora.konsola.x,stan.pozycja_kursora.konsola.y);
    }
    return stan;
}
void kolory_konsoli(int tlo_kolor, int tekst_kolor)
{
    textbackground(tlo_kolor);
    textcolor(tekst_kolor);
    clrscr();
}
bool sprawdzenie_pola(int** p, int** tab_ODDECHow, int wiersz, int kolumna, int pion_sojusznika)// sprawdza czy pole jest ODDECHem lub dolacza piona na danym polu do grupy
{
    if(tab_ODDECHow[wiersz][kolumna] != ROZPATRZONE) //sprawdzamy czy sprawdzane pole nie sprawdzalo juz swoich sasiadow
    {
        if(p[wiersz][kolumna] == PUSTE_POLE){
            tab_ODDECHow[wiersz][kolumna] = ODDECH;
        }
        else if(p[wiersz][kolumna] == pion_sojusznika){
            return true;
        }
    }
    return false;
}
void sprawdzenie_sasiadow_pola(int** p, int** tab_ODDECHow, int wiersz, int kolumna, int pion_sojusznika)//inicjalizuje sprawdzanie sasiednich pol pod wszgledem ODDECHow
{
    if(p[wiersz][kolumna]!=RAMKA)
    {
        tab_ODDECHow[wiersz][kolumna] = ROZPATRZONE;
        if(sprawdzenie_pola(p,tab_ODDECHow,wiersz-1,kolumna,pion_sojusznika)==true){
            sprawdzenie_sasiadow_pola(p,tab_ODDECHow,wiersz-1,kolumna,pion_sojusznika);
        }
        if(sprawdzenie_pola(p,tab_ODDECHow,wiersz+1,kolumna,pion_sojusznika)==true){
            sprawdzenie_sasiadow_pola(p,tab_ODDECHow,wiersz+1,kolumna,pion_sojusznika);
        }
        if(sprawdzenie_pola(p,tab_ODDECHow,wiersz,kolumna-1,pion_sojusznika)==true){
            sprawdzenie_sasiadow_pola(p,tab_ODDECHow,wiersz,kolumna-1,pion_sojusznika);
        }
        if(sprawdzenie_pola(p,tab_ODDECHow,wiersz,kolumna+1,pion_sojusznika)==true){
            sprawdzenie_sasiadow_pola(p,tab_ODDECHow,wiersz,kolumna+1,pion_sojusznika);
        }
    }
}
int licznik_ODDECHow(int** tab_ODDECHow, wspolrzedne n) //zwraca licznik ODDECHow i zeruje tab.ODDECHow
{
    int licznik=0;
    for(int i=1;i<n.y+1;i++){ // nie sprawdzamy pierwszych i ostatnich kolumn i wierszy, bo wiemy ze jest tam RAMKA
        for(int i2=1;i2<n.x+1;i2++){
            if(tab_ODDECHow[i][i2] == ODDECH){
                licznik++;
            }
        }
    }
    return licznik;
}
void czyszczenie_tablicy_ODDECHow(int** tab_ODDECHow, wspolrzedne n)
{
    for(int i=1;i<n.y+1;i++){ // nie sprawdzamy pierwszych i ostatnich kolumn i wierszy, bo wiemyy ze jest tam RAMKA
        for(int i2=1;i2<n.x+1;i2++){
            tab_ODDECHow[i][i2]=0;
        }
    }
}
void usuwanie_pionkow(int** tab, wspolrzedne n, int** p,int pion_sojusznika, int zbite_piony[2])
{
    for(int i=1;i<n.y+1;i++){ // nie sprawdzamy pierwszych i ostatnich kolumn i wierszy, bo wiemyy ze jest tam RAMKA
        for(int i2=1;i2<n.x+1;i2++){
            if(tab[i][i2] == PIONEK)
            {
                p[i][i2] = PUSTE_POLE;
                zbite_piony[pion_sojusznika]++;
            }
        }
    }
}
void zbijanie_strona(int** p, int** tab_ODDECHow, int wiersz, int kolumna, wspolrzedne n,int pion_sojusznika, int zbite_piony[2])
{
    if(p[wiersz][kolumna] == pion_sojusznika)
        {
            sprawdzenie_sasiadow_pola(p,tab_ODDECHow, wiersz,kolumna,pion_sojusznika);
            if(licznik_ODDECHow(tab_ODDECHow,n)==0){
                usuwanie_pionkow(tab_ODDECHow, n, p, pion_sojusznika-1, zbite_piony);
            }
        }
    czyszczenie_tablicy_ODDECHow(tab_ODDECHow,n);
}
void zbijanie(int** p, int** tab_ODDECHow, int wiersz, int kolumna, wspolrzedne n, int pion_sojusznika, int zbite_piony[2])
{
    zbijanie_strona(p,tab_ODDECHow,wiersz-1,kolumna,n,pion_sojusznika,zbite_piony);
    zbijanie_strona(p,tab_ODDECHow,wiersz+1,kolumna,n,pion_sojusznika,zbite_piony);
    zbijanie_strona(p,tab_ODDECHow,wiersz,kolumna-1,n,pion_sojusznika,zbite_piony);
    zbijanie_strona(p,tab_ODDECHow,wiersz,kolumna+1,n,pion_sojusznika,zbite_piony);
}
wspolrzedne znajdz_pionka(int** p, int** p_kopia, wspolrzedne n) // znajduje wspolrzedne zbitego pionka
{
    wspolrzedne wynik={0,0};
    for(int i=1;i<n.y+1;i++){ // nie sprawdzamy pierwszych i ostatnich kolumn i wierszy, bo wiemy ze jest tam RAMKA
        for(int i2=1;i2<n.x+1;i2++){
            if(p[i][i2] == PUSTE_POLE){
                if(p_kopia[i][i2] != PUSTE_POLE){
                     wynik = {i2, i};
                }
            }
        }
    }
    return wynik;
}
bool rozpatrzenie_zasady_ko(int** p, int** p_ko, wspolrzedne n)
{
    for(int i=0;i<n.y+2;i++){
        for(int i2=0;i2<n.x+2 ;i2++){
            if(p[i][i2] != p_ko[i][i2]){
                return false;
            }
         }
    }
    return true;
}
stan_gry rozpatrzenie_ruchu_samobojczego(int** tab_ODDECHow, stan_gry stan)
{
    stan.czyja_kolej = zmiana_kolei(stan.czyja_kolej);
    sprawdzenie_sasiadow_pola(stan.p,tab_ODDECHow,stan.pozycja_kursora.plansza.y,stan.pozycja_kursora.plansza.x,stan.czyja_kolej); // sprawdza czy ruch nie jest samobojczy
    if(licznik_ODDECHow(tab_ODDECHow,stan.n) == 0)
    {
        stan.p[stan.pozycja_kursora.plansza.y][stan.pozycja_kursora.plansza.x] = PUSTE_POLE;
        stan.czy_zapisano_ruch = true;
    }
    else
    {
        stan.czy_zapisano_ruch = false;
        stan.czyja_kolej = zmiana_kolei(stan.czyja_kolej);
    }
    czyszczenie_tablicy_ODDECHow(tab_ODDECHow,stan.n);
    return stan;
}
stan_gry handicap(stan_gry stan)
{
    char polecenie;
    while(polecenie != ENTER)
    {
        polecenie = getch();
        if(polecenie == ZNAK_SPECJALNY)
        {
            polecenie = getch();
            if(polecenie == STRZALKA_W_GORE || polecenie == STRZALKA_W_DOL || polecenie == STRZALKA_W_LEWO || polecenie == STRZALKA_W_PRAWO)// tu beda strzalki
            {
                stan.pozycja_kursora = ruch_kursora(stan.n, stan.pozycja_kursora, polecenie);
            }
        }
        else if(polecenie == 'i')
        {
            stan.p[stan.pozycja_kursora.plansza.y][stan.pozycja_kursora.plansza.x] = CZARNY_PIONEK;
            wyswietlanie_planszy(stan.p,stan.n,stan.zbite_suma,stan.czyja_kolej);
            gotoxy( stan.pozycja_kursora.konsola.x, stan.pozycja_kursora.konsola.y);
        }
    }
    stan.czyja_kolej = zmiana_kolei(stan.czyja_kolej);
    wyswietlanie_planszy(stan.p,stan.n,stan.zbite_suma,stan.czyja_kolej);
    gotoxy( stan.pozycja_kursora.konsola.x, stan.pozycja_kursora.konsola.y);
    return stan;
}
stan_gry ladowanie_stanu_z_pliku()
{
    clrscr();
    gotoxy(POCZATEK_MENU_X,POCZATEK_MENU_Y);
    cputs("podaj nazwe pliku i zatwierdz ENTERem - ");
    stan_gry stan;
    char nazwa_pliku[100];
    for(int i=0;i<100;i++)
        nazwa_pliku[i] = 0;
    char tmp = '0';
    int i = 0;
    while(tmp != ENTER)
    {
        tmp = getche();
        if(tmp != ENTER)
        {
            nazwa_pliku[i] = tmp;
        }
        i++;
    }
    FILE *f = fopen(nazwa_pliku,"r");// pointer do pliku
    fscanf(f,"%d",&stan.n.x);
    fscanf(f,"%d",&stan.n.y);
    fscanf(f,"%d",&stan.pozycja_kursora.konsola.x);
    fscanf(f,"%d",&stan.pozycja_kursora.konsola.y);
    fscanf(f,"%d",&stan.pozycja_kursora.plansza.x);
    fscanf(f,"%d",&stan.pozycja_kursora.plansza.y);
    stan.p = p_tworzenie(stan.n);
    for(int i=0;i<stan.n.y+2;i++)
    {
        for(int i2=0;i2<stan.n.x+2;i2++)
        {
            fscanf(f,"%d",&stan.p[i][i2]);
        }
    }
    stan.p_kopia = p_tworzenie(stan.n);
    for(int i=0;i<stan.n.y+2;i++)
    {
        for(int i2=0;i2<stan.n.x+2;i2++)
        {
            fscanf(f,"%d",&stan.p_kopia[i][i2]);
        }
    }
    stan.p_ko = p_tworzenie(stan.n);
    for(int i=0;i<stan.n.y+2;i++)
    {
        for(int i2=0;i2<stan.n.x+2;i2++)
        {
            fscanf(f,"%d",&stan.p_ko[i][i2]);
        }
    }
    fscanf(f,"%d",&stan.czyja_kolej);
    for(int i=0;i<2;i++)
    {
        fscanf(f,"%d",&stan.zbite_suma[i]);
    }
    for(int i=0;i<2;i++)
    {
        fscanf(f,"%d",&stan.zbite_piony[i]);
    }
    fscanf(f,"%d",&stan.czy_zapisano_ruch);
    fscanf(f,"%d",&stan.czy_handicap);
    fclose(f);
    return stan;
}
void zapisywanie_stanu_do_pliku(stan_gry stan)
{
    clrscr();
    gotoxy(POCZATEK_MENU_X,POCZATEK_MENU_Y);
    cputs("podaj nazwe pliku i zatwierdz ENTERem - ");
    char nazwa_pliku[100];
    for(int i = 0; i < 100; i++)
        nazwa_pliku[i] = 0;
    char tmp = '0';
    int i = 0;
    while(tmp != ENTER && i<100)
    {
        tmp = getche();
        if(tmp != ENTER)
        {
            nazwa_pliku[i] = tmp;
        }
        i++;
    }
    FILE *f = fopen(nazwa_pliku,"w");// pointer do pliku
    fprintf(f,"%d ",stan.n.x);
    fprintf(f,"%d ",stan.n.y);
    fprintf(f,"%d ",stan.pozycja_kursora.konsola.x);
    fprintf(f,"%d ",stan.pozycja_kursora.konsola.y);
    fprintf(f,"%d ",stan.pozycja_kursora.plansza.x);
    fprintf(f,"%d ",stan.pozycja_kursora.plansza.y);
    for(int i = 0; i < stan.n.y + 2; i++)
    {
        for(int i2=0;i2<stan.n.x+2;i2++)
        {
            fprintf(f,"%d ",stan.p[i][i2]);
        }
        fprintf(f,"\n");
    }
    for(int i=0;i<stan.n.y+2;i++)
    {
        for(int i2=0;i2<stan.n.x+2;i2++)
        {
            fprintf(f,"%d ",stan.p_kopia[i][i2]);
        }
        fprintf(f,"\n");
    }
    for(int i=0;i<stan.n.y+2;i++)
    {
        for(int i2=0;i2<stan.n.x+2;i2++)
        {
            fprintf(f,"%d ",stan.p_ko[i][i2]);
        }
        fprintf(f,"\n");
    }
    fprintf(f,"%d ",stan.czyja_kolej);
    for(int i=0;i<2;i++)
    {
        fprintf(f,"%d ",stan.zbite_suma[i]);
    }
    for(int i=0;i<2;i++)
    {
        fprintf(f,"%d ",stan.zbite_piony[i]);
    }
    fprintf(f,"%d ",stan.czy_zapisano_ruch);
    fprintf(f,"%d ",stan.czy_handicap);
    fclose(f);
}
void punktacja(stan_gry stan)
{
    int** tab_grup = p_tworzenie(stan.n); //tablica do sprawdzania ktore grupy byly sprawdzone
    for(int i=0;i<stan.n.y+1;i++){
        for(int i2=1;i2<stan.n.x+1;i2++){
            tab_grup[i][i2] = PUSTE_POLE;
        }
    }
    int punkty_suma[2] = {0,0}; // 0 - BIALE , 1 - CZARNE
    if(stan.czy_handicap == false){
        punkty_suma[BIALE-1] += 4;
    }
    //usuwanie_martwych_grup(stan.p, tab_grup, stan.n, stan.zbite_suma);
    punkty_suma[BIALE-1] += stan.zbite_suma[CZARNE-1];
    punkty_suma[CZARNE-1] += stan.zbite_suma[BIALE-1];
    //liczenie_teytoriow()
    clrscr();
    gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y);
    cputs("punkty bialych - ");
    wypisywanie_liczby(punkty_suma[BIALE-1]); cputs(",5");
    gotoxy(POCZATEK_MENU_X, POCZATEK_MENU_Y+1);
    cputs("punkty czarnych - ");
    wypisywanie_liczby(punkty_suma[CZARNE-1]);
    p_free(stan.n,tab_grup);
}
stan_gry poczatek_rozgrywki()
{
    _setcursortype(_NOCURSOR);
    stan_gry stan;
    stan.n = wybor_rozmiarow();
    stan.czy_handicap = handicap_menu();
    stan.p = p_tworzenie(stan.n);
    wpisz_stan_logiczny_planszy(stan.p,stan.n);
    stan.p_kopia = p_tworzenie(stan.n);
    stan.p_kopia=kopia_planszy(stan.p_kopia, stan.p, stan.n);
    stan.p_ko = p_tworzenie(stan.n);
    stan.p_ko=kopia_planszy(stan.p_ko, stan.p, stan.n);
    legenda();
    for(int i=0; i<2; i++)
    {
        stan.zbite_piony[i]=0;
        stan.zbite_suma[i]=0;
    }
    wyswietlanie_planszy(stan.p, stan.n, stan.zbite_suma, stan.czyja_kolej);
    _setcursortype(_SOLIDCURSOR);
    gotoxy(POCZATEK_PLANSZY_X+2,POCZATEK_PLANSZY_Y+1);
    stan.pozycja_kursora.konsola.x = POCZATEK_PLANSZY_X+2;
    stan.pozycja_kursora.konsola.y = POCZATEK_PLANSZY_Y+1;
    stan.pozycja_kursora.plansza.x = 1;
    stan.pozycja_kursora.plansza.y = 1;
    stan.czyja_kolej = CZARNE;
    stan.czy_zapisano_ruch = true;
    return stan;
}
int main()
{
    #ifndef __cplusplus
        Conio2_Init();
    #endif
    kolory_konsoli(BLACK,WHITE);
    settitle("Kamil, Cwynar, 193377");
    stan_gry stan = poczatek_rozgrywki();
    if(stan.czy_handicap == true){
        stan = handicap(stan);
    }
    int** tab_ODDECHow = p_tworzenie(stan.n);
    char polecenie;
    while(polecenie != 'q')
    {
        polecenie=NULL;
        polecenie=getch();//polecenie od gracza
        if(polecenie == 'n')
        {
            clrscr();
            stan=poczatek_rozgrywki();
        }
        else if(polecenie == 'i'){
            if(stan.p[stan.pozycja_kursora.plansza.y][stan.pozycja_kursora.plansza.x] == PUSTE_POLE && stan.czy_zapisano_ruch==true)
            {
                if(stan.czyja_kolej == CZARNE){
                        stan.p[stan.pozycja_kursora.plansza.y][stan.pozycja_kursora.plansza.x] = CZARNY_PIONEK;
                    }
                else{
                        stan.p[stan.pozycja_kursora.plansza.y][stan.pozycja_kursora.plansza.x] = BIALY_PIONEK;
                    }
                stan.czyja_kolej = zmiana_kolei(stan.czyja_kolej);
                zbijanie(stan.p, tab_ODDECHow, stan.pozycja_kursora.plansza.y, stan.pozycja_kursora.plansza.x, stan.n, stan.czyja_kolej, stan.zbite_piony); //sprrawdza czy pionki przeciwnika wokol maja ODDECHy
                stan.zbite_suma[stan.czyja_kolej-1] += stan.zbite_piony[stan.czyja_kolej - 1];
                stan = rozpatrzenie_ruchu_samobojczego(tab_ODDECHow, stan);
                if(rozpatrzenie_zasady_ko(stan.p, stan.p_ko, stan.n) == true)
                {
                    stan = polecenie_ESC(stan);
                }
                wyswietlanie_planszy(stan.p,stan.n,stan.zbite_suma,stan.czyja_kolej);
                gotoxy( stan.pozycja_kursora.konsola.x, stan.pozycja_kursora.konsola.y);
            }
        }
        else if(polecenie == ZNAK_SPECJALNY)
        {
            polecenie = getch();
            if(polecenie == STRZALKA_W_GORE || polecenie == STRZALKA_W_DOL || polecenie == STRZALKA_W_LEWO || polecenie == STRZALKA_W_PRAWO)// tu beda strzalki
            {
                stan.pozycja_kursora = ruch_kursora(stan.n, stan.pozycja_kursora, polecenie);
            }
        }
        else if(polecenie == ENTER){
            if(stan.czy_zapisano_ruch == false)
            {
                stan.p_ko = kopia_planszy(stan.p_ko, stan.p_kopia, stan.n);
                stan.p_kopia = kopia_planszy(stan.p_kopia, stan.p, stan.n);
                stan.czy_zapisano_ruch = true;
                stan.zbite_piony[stan.czyja_kolej-1] = 0;
            }
        }
        else if(polecenie == ESC)
        {
            stan = polecenie_ESC(stan);
        }
        else if(polecenie == 's')
        {
            zapisywanie_stanu_do_pliku(stan);
            clrscr();
            legenda();
            wyswietlanie_planszy(stan.p, stan.n, stan.zbite_suma, stan.czyja_kolej);
            gotoxy(stan.pozycja_kursora.konsola.x,stan.pozycja_kursora.konsola.y);
        }
        else if(polecenie == 'l')
        {
            p_free(stan.n,stan.p);
            p_free(stan.n,stan.p_kopia);
            p_free(stan.n,stan.p_ko);
            p_free(stan.n,tab_ODDECHow);
            stan = ladowanie_stanu_z_pliku();
            clrscr();
            legenda();
            wyswietlanie_planszy(stan.p, stan.n, stan.zbite_suma, stan.czyja_kolej);
            gotoxy(stan.pozycja_kursora.konsola.x,stan.pozycja_kursora.konsola.y);
        }
        else if(polecenie == 'f'){
            if(stan.czy_zapisano_ruch == true){
                punktacja(stan);
            }
        }
    }
    clrscr();
    p_free(stan.n,stan.p);
    p_free(stan.n,stan.p_kopia);
    p_free(stan.n,stan.p_ko);
    p_free(stan.n,tab_ODDECHow);
    gotoxy (POCZATEK_WYJSCIA_Z_PROGRAMU_X,POCZATEK_WYJSCIA_Z_PROGRAMU_Y);
    cputs("END OF THE GAME");
    return 0;
}
