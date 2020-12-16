#include <iostream>
#include <time.h>
using namespace std;

#define Zadanie8A

#ifdef Zadanie8A
#define RND_ZZ (double)rand() / RAND_MAX
void mc(double a, double b, double c, double xp, double xk)
{
    int n = 1000;
    double y, x, min=1000, min2=1000;
    srand(time(NULL)); 
    for (int i = 0; i < n; i++)
    {
        x = xp + RND_ZZ * (xk - xp);
        y = (a * x * x) + (b * x) + c;
        if (min > y)
        {
            min = y;
            min2 = x;
        }
    }
    cout << "y(min) = " << min << "  dla x = " << min2 << endl;

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


