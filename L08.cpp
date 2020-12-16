#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

#define Zadanie8B

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
int main()
{
    int n;
    double x, e;
    cout << "x -> ";
    cin >> x;
    cout << "n -> ";
    cin >> n;
    cout << "e -> ";
    cin >> e;
    cout<<pierwiastek(n, x, e);
}
#endif // Zadanie8B

#ifdef Zadanie8C

#endif

