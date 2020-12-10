#include <iostream>
#include <random>
#include <ctime>
#include <map>
#include <utility>
#include <algorithm>

std::map<double, double> y;

double used_f(double c, double d)
{
    double f = 0;
    std::map<double, double> ::iterator it = y.begin();
    for (it; it != y.end(); it++)
    {
        double x = it->first;
        double t = it->second;
        double y = c * x + d;
        f += pow((y - t), 2);
    }
    return f;
}

double Fib_f(int i)
{
    if (i <= 1)
        return 1.;
    else
        return Fib_f(i - 2) + Fib_f(i - 1);
}

double Fibonacci(double a, double b, double c)
{
    const double eps = 0.1;
    int N = 20;
    auto l = a + Fib_f(N - 2) * (b - a) / Fib_f(N);
    auto r = a + Fib_f(N - 1) * (b - a) / Fib_f(N);
    for (int i = 1; i < N; i++)
    {
        if (used_f(c, l) > used_f(c, r))
        {
            a = l;
            l = r;
            r = a + Fib_f(N - i - 1) * (b - a) / Fib_f(N - i);
        }
        else
        {
            b = r;
            r = l;
            l = a + Fib_f(N - i - 2) * (b - a) / Fib_f(N - i);
        }
    }
    return (a + b) / 2;
}

double dichotomy(double a, double b, double d)
{
    const double eps = 0.1;
    const double delta = 0.01;
    double Xleft, Xright, Yleft, Yright;
    do
    {
        Xleft = 0.5 * (b + a) - delta;
        Xright = 0.5 * (b + a) + delta;
        Yleft = used_f(d, Xleft);
        Yright = used_f(d, Xright);
        if (Yleft > Yright)
            a = Xleft;
        else
            b = Xright;
    } while ((b - a) > eps);
    return (a + b) / 2;
}

int main()
{
    double a = -5, b = 5;
    double c = 1000, d = 0;
    int N = 20;
    double A = 2000;
    double count = (b - a) / N;
    std::map<double, double> f;

    for (auto x = a; x < b; x += count)
    {
        std::mt19937 gen(time(0));
        std::uniform_real_distribution<double> urd(-0.5, 0.5);
        double e = urd(gen);
        auto t = c * x + d + A*e;
        auto t0 = c * x + d;
        y.insert(std::make_pair(x, t));
        f.insert(std::make_pair(x, t0));
    }

    std::map<double, double> ::iterator it0 = f.begin();
    std::cout << "Without noise: " << std::endl;
    for (it0; it0 != f.end(); it0++)
        std::cout << it0->first << " " << it0->second << std::endl;

    std::cout << std::endl << "With noise: " << std::endl;
    std::map<double, double> ::iterator it = y.begin();
    for (it; it != y.end(); it++)  
        std::cout << it->first << " " << it->second << std::endl;

    c = Fibonacci(a, b, c);
    d = dichotomy(a, b, d);
    std::cout << std::endl << "c = " << c << std::endl << "d = " << d << std::endl;
    
    return 0;
}
