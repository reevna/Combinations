#include <iostream>
#include <boost/timer.hpp>


using namespace std;

enum Direction
{
    LEFT_TO_RIGHT,
    RIGHT_TO_LEFT
};

// поиск позиции наибольшшего мобильного в массиве а
int SearchArr(int a[], int n, int mobile)
{
    for (int i = 0; i < n; i++)
        if (a[i] == mobile)
            return i + 1;
}

// найти наибольшее мобильное
int GetMobile(int a[], Direction dir[], int n)
{
    int mobile_prev = 0, mobile = 0;
    for (int i = 0; i < n; i++)
    {
        // direction 0 = RIGHT TO LEFT. 
        if (dir[a[i] - 1] == Direction::RIGHT_TO_LEFT && i != 0
            && a[i] > a[i - 1] && a[i] > mobile_prev)
        {
            mobile = a[i];
            mobile_prev = mobile;
        }

        // direction 1 = LEFT TO RIGHT. 
        if (dir[a[i] - 1] == Direction::LEFT_TO_RIGHT && i != n - 1
            && a[i] > a[i + 1] && a[i] > mobile_prev)
        {
            mobile = a[i];
            mobile_prev = mobile;
        }
    }

    if (mobile == 0 && mobile_prev == 0)
        return 0;
    else
        return mobile;
}

// одна перестановка
void GetNextPermutation(int a[], Direction dir[], int n)
{
    int mobile = GetMobile(a, dir, n);
    int pos = SearchArr(a, n, mobile);

    // перестановка элементов в соответствии с направлением 
    if (dir[a[pos - 1] - 1] == Direction::RIGHT_TO_LEFT)
        swap(a[pos - 1], a[pos - 2]);
    else if (dir[a[pos - 1] - 1] == Direction::LEFT_TO_RIGHT)
        swap(a[pos], a[pos - 1]);

    // изменение направленяи для элементов больших, чем наибольшее мобильное
    for (int i = 0; i < n; i++)
    {
        if (a[i] > mobile)
        {
            if (dir[a[i] - 1] == Direction::LEFT_TO_RIGHT)
                dir[a[i] - 1] = Direction::RIGHT_TO_LEFT;
            else if (dir[a[i] - 1] == Direction::RIGHT_TO_LEFT)
                dir[a[i] - 1] = Direction::LEFT_TO_RIGHT;
        }
    }
    /*
    *    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    */

}

int Fact(int n)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
        res = res * i;
    return res;
}

int main()
{
    const int n = 15;
    int a[n];
    Direction dir[n];

    boost::timer t;
    t.restart();

    // установить элементы с 1 до  n
    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
        //  cout << a[i] << " ";
    }
    //  cout << endl;

      // изначально все направления установлены в RIGHT TO LEFT
    for (int i = 0; i < n; i++)
        dir[i] = Direction::RIGHT_TO_LEFT;

    // перестановки по порядку
    for (int i = 1; i < Fact(n); i++)
        GetNextPermutation(a, dir, n);

    double duration = t.elapsed();
    cout << duration << endl;

    return 0;
}
//для 10 -  0.366
// для 15 - 195.97 