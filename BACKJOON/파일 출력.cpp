#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

int main(void)
{
    srand(time(NULL));
    ofstream out("test.txt");
    for (int i = 0; i < 100000; i++) {
        out << (rand() % 100000) + 1 << " ";
    }
    out.close();
    return 0;
}