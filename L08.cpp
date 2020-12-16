#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

#define Zadanie8C

#ifdef Zadanie8A
#define RND_ZZ (double)rand() / RAND_MAX
void mc(double a, double b, double c, double xp, double xk)
{
    int n = 1000;
    double y, x, ymin=xk*100, xmin=xk*100;
    srand(time(NULL));
    if (a > 0) {
        for (int i = 0; i < n; i++)
        {
            x = xp + RND_ZZ * (xk - xp);
            y = (a * x * x) + (b * x) + c;
            if (ymin > y)
            {
                ymin = y;
                xmin = x;
            }
        }
        cout << "y(min) = " << ymin << "  dla x = " << xmin << endl;
    }
    else
        cout << "BLAD -> a<0";

}

int main()
{
    srand(time(NULL));
    double a, b, c, p, k;

    cout << "Podaj a -> ";
    cin >> a;
    cout << "Podaj b -> ";
    cin >> b;
    cout << "Podaj c-> ";
    cin >> c;
    cout << "Podaj wartosc poczatkowa przedzialu -> ";
    cin >> p;
    cout << "Podaj wartosc koncowa przedzialu -> ";
    cin >> k;

    mc(a, b, c, p, k);
}
#endif // Zadanie8A

#ifdef Zadanie8B
double pierwiastek(int n, double x, double e)
{
    double y=0, yk=0;
    y = x;
	if (n > 0 && x > 0)
	{
		do
		{
			yk = (1.0 / n) * ((n - 1.0) * y + (x / pow(y, n - 1.0)));
			if (e >= fabs(yk - y))
			{
				break;
			}
			y = yk;
		} while (true);
		return yk;
	}
	else
		return -1;
}
int main()
{
    int n;
    double x, e,wynik;
    cout << "x -> ";
    cin >> x;
    cout << "n -> ";
    cin >> n;
    cout << "e -> ";
    cin >> e;
	wynik = pierwiastek(n, x, e);
	if (wynik == -1)
		cout << "Wynik obarczony jest bledem z uwagi na niepoprawnosc wprowadzonych wartosci"<<endl;
	else
		cout << "Wynik = " << wynik;
    
}
#endif // Zadanie8B

#ifdef Zadanie8C
constexpr short ROZMIAR = 10;

void wypiszKanal(short tab[][ROZMIAR][3], short kanal)
{
	for (short wiersz = 0; wiersz < ROZMIAR; wiersz++)
	{
		for (short kolumna = 0; kolumna < ROZMIAR; kolumna++)
		{
			cout << tab[wiersz][kolumna][kanal] << "  ";
		}
		cout << endl;
	}
}

void main(void)
{
	clock_t start = clock();
	{
		
		short obraz[ROZMIAR][ROZMIAR][3] = {};
		srand(time(0));
		short pendzel[3] = {};
		double szansa = 0.1;
		double wspGamma = 0.45;

		//Generowanie koloru tła:
		for (short i = 0; i < 3; i++)
			pendzel[i] = rand() % 256;

		//Generowanie tła obrazu oraz zakłócenia:
		for (short wiersz = 0; wiersz < ROZMIAR; wiersz++)
		{
			for (short kolumna = 0; kolumna < ROZMIAR; kolumna++)
			{
				for (short kanal = 0; kanal < 3; kanal++)
				{
					short roznica = rand() % 3 - 1 + rand() % 3 - 1;
					obraz[wiersz][kolumna][kanal] = pendzel[kanal] + roznica;
					double test = (1.0 * rand() / RAND_MAX);
					if (test <= szansa) obraz[wiersz][kolumna][kanal] = rand() % 256;
				}
			}
		}



		// Wypisanie kanalow obrazu:
		cout << "OBRAZ ZASZUMIONY:\n";
		cout << "Kanal czerwony:\n";
		wypiszKanal(obraz, 0); cout << endl;
		cout << "Kanal zielony:\n";
		wypiszKanal(obraz, 1); cout << endl;
		cout << "Kanal niebieski:\n";
		wypiszKanal(obraz, 2); cout << endl;
		cout << "================================\n";

		//Usuwanie szumu (filtr VMF):
		for (short wiersz = 1; wiersz < ROZMIAR - 1; wiersz++)
		{
			for (short kolumna = 1; kolumna < ROZMIAR - 1; kolumna++)
			{
				int tabDist[9][9] = {};
				//wyznaczenie okna filtracji:
				for (short x = -1; x <= 0; x++)
					for (short y = -1; y <= 0; y++)
					{
						//liczenie dystansow kazdego piksela do kazdego piksela (w oknie)
						for (short i = -1; i <= 0; i++)
							for (short j = -1; j <= 0; j++)
							{
								int R1 = obraz[wiersz + x][kolumna + y][0];
								int R2 = obraz[wiersz + i][kolumna + j][0];
								int G1 = obraz[wiersz + x][kolumna + y][1];
								int G2 = obraz[wiersz + i][kolumna + j][1];
								int B1 = obraz[wiersz + x][kolumna + y][2];
								int B2 = obraz[wiersz + i][kolumna + j][2];
								int dR = R1 - R2, dG = G1 - G2, dB = B1 - B2;
								int dystans = (int)sqrt(dR * dR + dG * dG + dB * dB);
								short zrodlo = 3 * (x + 1) + (y + 1);
								short cel = 3 * (i + 1) + (j + 1);
								//tabDist[zrodlo][cel] = dystans;
							}
					}
				int sumy[9] = {};
				for (short pixZr = 0; pixZr < 9; pixZr++)
					for (short pixC = 0; pixC < 9; pixC++)
						sumy[pixZr] += tabDist[pixZr][pixC];

				int min = sumy[0];
				short szukIdx = 0;
				for (short idx = 1; idx < 9; idx++)
				{
					if (sumy[idx] < min)
					{
						min = sumy[idx];
						szukIdx = idx;
					}
				}
				short x = (szukIdx / 3) - 1;
				short y = (szukIdx % 3) - 1;
				for (short kanal = 0; kanal < 3; kanal++)
					obraz[wiersz][kolumna][kanal] = obraz[wiersz + x][kolumna + y][kanal];
			}
		}
		// Wypisanie kanalow obrazu:
		cout << "OBRAZ PO ODSZUMIANIU:\n";
		cout << "Kanal czerwony:\n";
		wypiszKanal(obraz, 0); cout << endl;
		cout << "Kanal zielony:\n";
		wypiszKanal(obraz, 1); cout << endl;
		cout << "Kanal niebieski:\n";
		wypiszKanal(obraz, 2); cout << endl;
		cout << "================================\n";

		//Korekcja gamma:
		for (short wiersz = 0; wiersz < ROZMIAR; wiersz++)
		{
			for (short kolumna = 0; kolumna < ROZMIAR; kolumna++)
			{
				for (short kanal = 0; kanal < 3; kanal++)
				{
					obraz[wiersz][kolumna][kanal] = (int)(255.0 * pow(obraz[wiersz][kolumna][kanal] / 255.0, wspGamma));
				}
			}
		}

		// Wypisanie kanalow obrazu:
		cout << "OBRAZ PO KOREKCJI GAMMA:\n";
		cout << "Kanal czerwony:\n";
		wypiszKanal(obraz, 0); cout << endl;
		cout << "Kanal zielony:\n";
		wypiszKanal(obraz, 1); cout << endl;
		cout << "Kanal niebieski:\n";
		wypiszKanal(obraz, 2); cout << endl;
		cout << "================================\n";
		
	}
	clock_t koniec = clock();
	clock_t cykl = koniec - start;
	double czas = (double)cykl / CLOCKS_PER_SEC;
	
	cout << endl << endl;

	//BEZ OPTYMALIZACJI



	clock_t start2 = clock();
	{

	short obraz[ROZMIAR][ROZMIAR][3] = {};
	srand(1);
	short pendzel[3] = {};
	double szansa = 0.1;
	double wspGamma = 0.45;

	//Generowanie koloru tła:
	for (short i = 0; i < 3; i++)
		pendzel[i] = rand() % 256;

	//Generowanie tła obrazu:
	for (short kolumna = 0; kolumna < ROZMIAR; kolumna++)
	{
		for (short wiersz = 0; wiersz < ROZMIAR; wiersz++)
		{
			for (short kanal = 0; kanal < 3; kanal++)
			{
				short roznica = rand() % 3 - 1 + rand() % 3 - 1;
				obraz[wiersz][kolumna][kanal] = pendzel[kanal] + roznica;
			}
		}
	}

	// Wypisanie kanalow obrazu:
	cout << "OBRAZ:\n";
	cout << "Kanal czerwony:\n";
	wypiszKanal(obraz, 0); cout << endl;
	cout << "Kanal zielony:\n";
	wypiszKanal(obraz, 1); cout << endl;
	cout << "Kanal niebieski:\n";
	wypiszKanal(obraz, 2); cout << endl;
	cout << "================================\n";

	//Generowanie zakłócenia:
	for (short kolumna = 0; kolumna < ROZMIAR; kolumna++)
	{
		for (short wiersz = 0; wiersz < ROZMIAR; wiersz++)
		{
			for (short kanal = 0; kanal < 3; kanal++)
			{
				double test = (1.0 * rand() / RAND_MAX);
				if (test <= szansa) obraz[wiersz][kolumna][kanal] = rand() % 256;
			}
		}
	}

	// Wypisanie kanalow obrazu:
	cout << "OBRAZ ZASZUMIONY:\n";
	cout << "Kanal czerwony:\n";
	wypiszKanal(obraz, 0); cout << endl;
	cout << "Kanal zielony:\n";
	wypiszKanal(obraz, 1); cout << endl;
	cout << "Kanal niebieski:\n";
	wypiszKanal(obraz, 2); cout << endl;
	cout << "================================\n";

	//Usuwanie szumu (filtr VMF):
	for (short kolumna = 1; kolumna < ROZMIAR - 1; kolumna++)
	{
		for (short wiersz = 1; wiersz < ROZMIAR - 1; wiersz++)
		{
			int tabDist[9][9] = {};
			//wyznaczenie okna filtracji:
			for (short x = -1; x <= 1; x++)
				for (short y = -1; y <= 1; y++)
				{
					//liczenie dystansow kazdego piksela do kazdego piksela (w oknie)
					for (short i = -1; i <= 1; i++)
						for (short j = -1; j <= 1; j++)
						{
							int R1 = obraz[wiersz + x][kolumna + y][0];
							int R2 = obraz[wiersz + i][kolumna + j][0];
							int G1 = obraz[wiersz + x][kolumna + y][1];
							int G2 = obraz[wiersz + i][kolumna + j][1];
							int B1 = obraz[wiersz + x][kolumna + y][2];
							int B2 = obraz[wiersz + i][kolumna + j][2];
							int dR = R1 - R2, dG = G1 - G2, dB = B1 - B2;
							int dystans = (int)sqrt(dR * dR + dG * dG + dB * dB);
							short zrodlo = 3 * (x + 1) + (y + 1);
							short cel = 3 * (i + 1) + (j + 1);
							tabDist[zrodlo][cel] = dystans;
						}
				}
			int sumy[9] = {};
			for (short pixZr = 0; pixZr < 9; pixZr++)
				for (short pixC = 0; pixC < 9; pixC++)
					sumy[pixZr] += tabDist[pixZr][pixC];

			int min = sumy[0];
			short szukIdx = 0;
			for (short idx = 1; idx < 9; idx++)
			{
				if (sumy[idx] < min)
				{
					min = sumy[idx];
					szukIdx = idx;
				}
			}
			short x = (szukIdx / 3) - 1;
			short y = (szukIdx % 3) - 1;
			for (short kanal = 0; kanal < 3; kanal++)
				obraz[wiersz][kolumna][kanal] = obraz[wiersz + x][kolumna + y][kanal];
		}
	}
	// Wypisanie kanalow obrazu:
	cout << "OBRAZ PO ODSZUMIANIU:\n";
	cout << "Kanal czerwony:\n";
	wypiszKanal(obraz, 0); cout << endl;
	cout << "Kanal zielony:\n";
	wypiszKanal(obraz, 1); cout << endl;
	cout << "Kanal niebieski:\n";
	wypiszKanal(obraz, 2); cout << endl;
	cout << "================================\n";

	//Korekcja gamma:
	for (short kolumna = 0; kolumna < ROZMIAR; kolumna++)
	{
		for (short wiersz = 0; wiersz < ROZMIAR; wiersz++)
		{
			for (short kanal = 0; kanal < 3; kanal++)
			{
				obraz[wiersz][kolumna][kanal] = (int)(255.0 * pow(obraz[wiersz][kolumna][kanal] / 255.0, wspGamma));
			}
		}
	}

	// Wypisanie kanalow obrazu:
	cout << "OBRAZ PO KOREKCJI GAMMA:\n";
	cout << "Kanal czerwony:\n";
	wypiszKanal(obraz, 0); cout << endl;
	cout << "Kanal zielony:\n";
	wypiszKanal(obraz, 1); cout << endl;
	cout << "Kanal niebieski:\n";
	wypiszKanal(obraz, 2); cout << endl;
	cout << "================================\n";
}
clock_t koniec2 = clock();
clock_t cykl2 = koniec2 - start2;
double czas2 = (double)cykl2 / CLOCKS_PER_SEC;
cout << endl << "CZAS WYKONANIA Z OPTYMALIZACJIA= " << czas << "    CZAS WYKONANIA BEZ OPTYMALIZACJI= "<< czas2 <<endl;
}

#endif

