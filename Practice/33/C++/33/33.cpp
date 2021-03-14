#include <iostream>
using namespace std;

int* one(int a, int s = 0, int b = 0) {
    int* arr = new int[a];
    for (int i = 0; i < a; i++)
    {
        arr[i] = b * i + s;
    }
    return arr;
}

int* sortirovka(int* arr, int a) {

    for (int i = 1; i < a; i++)
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            int tmp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = tmp;
        }
    return arr;
}

int* pechat(int* arr, int a) {
    for (int i = 0; i < a; i++)
    {
        cout << arr[i] << ' ';
    }
    return arr;
}

int main()
{
    int a1, s, b;
    cin >> a1;
    cin >> s;
    cin >> b;
    int* arr2 = one(a1, s, b);
    pechat(sortirovka(arr2, a1), a1);

    delete[] arr2;
}