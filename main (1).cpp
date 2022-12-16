#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;

const int N = 20; // Liczebność zbioru.
const int iloscCiagow = 20;
int d[N];

// Procedura sortowania szybkiego
//-------------------------------

void Sortuj_szybko(int lewy, int prawy)
{
    int i,j,piwot;

    i = (lewy + prawy) / 2;
    piwot = d[i]; d[i] = d[prawy];
    for(j = i = lewy; i < prawy; i++)
        if(d[i] < piwot)
        {
            swap(d[i], d[j]);
            j++;
        }
    d[prawy] = d[j]; d[j] = piwot;
    if(lewy < j - 1)  Sortuj_szybko(lewy, j - 1);
    if(j + 1 < prawy) Sortuj_szybko(j + 1, prawy);
}

void Sortuj_Nieszybko(int* lista, int n) {
    int pos = 0;
    while (pos < n) {
        if (pos == 0 || lista[pos] >= lista[pos - 1]) {
            pos++;
        } else {
            swap(lista[pos], lista[pos - 1]);
            pos = pos - 1;
        }
    }
}
// Program główny
//---------------

int main()
{
    int i;
    int iloscciagowdopierwszego = 10;
    int iloscciagowdodrugiego = 10;
    int ciag1[N];
    int ciag[N];
    FILE *glownyplik;
    FILE *sortowaniePierwsze;
    FILE *sortowanieDrugie;

    glownyplik = fopen("generowaneciagi.txt","a+");
    srand((unsigned)time(NULL));

    for(int j = 0; j < iloscCiagow; j++) {
        for (i = 0; i < N; i++) {
            ciag1[i] = rand() % 100;
            fprintf(glownyplik, "%d ", ciag1[i]);
        }
        fprintf(glownyplik, "%s", "\n");
    }

// Sortujemy
    fseek(glownyplik,0,0);
    sortowaniePierwsze = fopen("SortowaniePierwsze.txt","a");
    sortowanieDrugie = fopen("SortowanieDrugie.txt","a");
    for(int j = 0; j < iloscciagowdopierwszego; j++) {
        for (i = 0; i < N; i++) {
            fscanf(glownyplik, "%d", &d[i]);
        }
        Sortuj_szybko(0, N - 1);
        for (i = 0; i < N; i++) {
            fprintf(sortowaniePierwsze, "%d ", d[i]);
        }
        fprintf(sortowaniePierwsze, "%s", "\n");
    }
    for(int j = 0; j < iloscciagowdodrugiego; j++) {
        for (i = 0; i < N; i++) {
            fscanf(glownyplik, "%d", &ciag[i]);
        }
        Sortuj_Nieszybko(ciag, N);
        for (i = 0; i < N; i++) {
            fprintf(sortowanieDrugie, "%d ", ciag[i]);
        }
        fprintf(sortowanieDrugie, "%s", "\n");
    }

    fclose(glownyplik);
    fclose(sortowaniePierwsze);
    fclose(sortowanieDrugie);
    return 0;
}
