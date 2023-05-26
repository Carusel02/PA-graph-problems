/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */

#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;


int main() {
    ifstream fin("magazin.in");
    ofstream fout("magazin.out");

    int N, Q;
    fin >> N >> Q;

    for(int i = 0; i < N - 1; ++i) {
        int x;
        fin >> x;
    }
    for(int i = 0; i < Q; ++i) {
        int d, e;
        fin >> d >> e;
        fout << 0 << '\n';
    }





    return 0;
}
