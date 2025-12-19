#include <iostream>
#include <vector>
#include <fstream>

class Animal {

public:
    virtual void make_sound()
    {
        std::cout<<"animal makes sound";
    }

};

class Dog : public Animal{
public:
    void make_sound () override
    {
        std::cout<<"dog barks";
    }
};

int main()
{
    Dog bob = Dog();
    bob.make_sound();
    int* arr = new int[100];

    for (int i=0; i<10; i++)
    {
        arr[i] = i; 
    }

    for (int i = 0; i < 10; i++)
    {
        std::cout<<arr[i]<<std::endl;
    }

}