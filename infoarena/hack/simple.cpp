#include<fstream>
#include<vector>
#include<algorithm>
#include<stack>
 
#define DIM 1000010
 
using namespace std;
 
ifstream fin("hack.in");
ofstream fout("hack.out");
 
int n, m;
 
int main() {
 
    fout << "50 50 1 1\n";
 
    for (int i = 1; i <= 50; i++) {
 
        if ((i + 2) % 4)
            fout << "1";
        else
            fout << "0";
 
    }
 
    fout << "\n";
 
    for (int i = 2; i < 50; i++) {
 
        for (int j = 1; j <= 50; j++) {
 
            fout << j % 2;
 
        }
 
        fout << "\n";
 
    }
 
    for (int i = 1; i <= 50; i++) {
 
        if (i % 4)
            fout << "1";
        else
            fout << "0";
 
    }
 
    return 0;
 
}