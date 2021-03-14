#include <iostream>
using namespace std;

void create(int** arr1, int a, int s = 0, int b = 0) 
{
    int* arr2 = new int[a];
    for (int i = 0; i < a; i++)
    {
        arr2[i] = b * i + s;
    }
    *arr1 = arr2;
}

int* sort(int* arr2, int a) 
{
    for (int i = 1; i < a; i++)
        for (int j = i; j > 0 && arr2[j - 1] > arr2[j]; j--) {
            int tmp = arr2[j - 1];
            arr2[j - 1] = arr2[j];
            arr2[j] = tmp;
        }

    return arr2;
}

int* print(int* arr2, int a) {
    for (int i = 0; i < a; i++)
    {
        cout << arr2[i] << ' ';
    }
    return arr2;
}

void destroy(int** arr1) {
    if (*arr1 != nullptr)
    {
        delete[] * arr1;
        *arr1 = nullptr;
    }
}

int main()
{
    int a, s, b;
    cin >> a;
    cin >> s;
    cin >> b;
    int* arr3;
    create(&arr3, a, s, b);
    print(sort(arr3, a), a);
    destroy(&arr3);
}