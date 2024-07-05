#include <iostream>
using namespace std;

int main()
{
    /*
    for(int i = 0; i < 20; i++)
    {
        cout << "uint16_t x" << i << "[256] = {};" << endl;
        cout << "x" << i << "[255] = 1;" << endl;
    }
    */
    int g[100] = {0};
    //g[100] = 6;
    cout << *(g+100);
}