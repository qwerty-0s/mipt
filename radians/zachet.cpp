#include<iostream>
#include<vector>
#include <fstream>

template <typename T>
T max (T a, T b)
{
    if (a>=b)
    {
        return a;
    }
    else 
    {
        return b;
    }
}

class Animal {
public:
    virtual void make_sound()
    {
        std::cout<<"animal makes sound"<<std::endl;
    }

};

class Dog : public Animal{
public:
    void make_sound() override
    {
        std::cout<<"dog barks"<<std::endl;
    }
};

constexpr int Factorial(int n) {
    return (n <= 1) ? 1 : (n * Factorial(n - 1));
}

int devide(int a, int b)
{
    if (b == 0)
    {
        throw std::invalid_argument("b == 0");
    }
    return a/b;
}

int increase (int& a)
{
    a++;
    return a;
}

int main()
{   

    std::cout << max(3,7) <<std::endl;
    Dog bob;
    bob.make_sound();

    constexpr int n = 10;
    std::cout << "Factorial of " << n << " is " << Factorial(n) << std::endl;

    std::vector<int> v = {1,2,3,4,5};
    v.pop_back();

    for (auto it = v.begin(); it != v.end(); ++it)
    {
        std::cout << *it << " ";
    }

    std::string s = "Hello, World!";
    s += " Welcome to C++17.";
    std::cout << v.size() << std::endl;

    try
    {
        int a = devide(1,0);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "deviding by zero " << e.what() << std::endl;
    }
    int k=4;
    int* arr = new int[k];

    int* i = arr; 

    for (int j=0; j<5; j++){
        arr[j] = j;
    }

    while (i!=&arr[5]){

        std::cout << *i << " ";
        i++;

    }

    std::cout<<std::endl;

    int x = 2;
    int& link_x = x;
    increase(x);
    link_x++;
    std::cout<<x <<std::endl;

    int* p = new int;
    *p = 5;
    std::cout<<*p<<std::endl;
    delete p;

    enum class Color { RED, GREEN, BLUE };
    Color color = Color::RED;

    std::ofstream outfile("example.txt");

    if (!outfile) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    outfile << "This is a test file." << std::endl;
    outfile.close();


}