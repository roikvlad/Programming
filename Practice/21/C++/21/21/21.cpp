#include <iostream>
using namespace std;

double BMI(double weight, double height)
{
    double a = weight, b = height, k;
    k = (a / (b * b));
    return k;
}
void printBMI(double BMI)
{
    double i = BMI;
    if (i < 18.5)
    {
        cout << "Underweight\n";
    }
    else if (18.5 <= i and i < 25.0)
    {
        cout << "Normal\n";
    }
    else if (25.0 <= i and i < 30.0)
    {
        cout << "Overweight\n";
    }
    else if (30.0 <= i)
    {
        cout << "Obesity\n";
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");

    double  weight, height, z, k;
    cout << "Введите вес в килограммах и рост в сантиметрах\n";
    cin >> weight >> z;
    height = z / 100;
    BMI(weight, height);

    double BMI1 = BMI(weight, height);
    printBMI(BMI1);

    system("pause");
    return 0;
}
