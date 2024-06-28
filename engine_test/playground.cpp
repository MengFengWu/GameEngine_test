#include <iostream>
using namespace std;

struct dec
{
    int* list[100];
};

void load(struct dec* obj)
{
    *(obj->list[0]) = 5;
}

int main()
{
    struct dec test;
    load(&test);
    cout << *(test.list[0]);
}