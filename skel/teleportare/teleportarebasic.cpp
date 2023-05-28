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
    ifstream fin("teleportare.in");
    ofstream fout("teleportare.out");

    /* read N (number of cars) and K (number of feribots) */
    int N, M, K;
    fin >> N >> M >> K;

    for(int i = 0; i < M; ++i) {
        int x, y, t;
        fin >> x >> y >> t;
    }

    for(int i = 0; i < K; ++i) {
        int x, y, p;
        fin >> x >> y >> p;
    }

    fout << 0;

    return 0;
}
