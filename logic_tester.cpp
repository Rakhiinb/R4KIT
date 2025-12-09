#include <iostream>
#include <string>
#include "logic.cpp" // Mengambil fungsi

using namespace std;

int main(){
    Penerbangan dataPalsu[5];
    dataPalsu[0].tujuan = "Bali";
    dataPalsu[1].tujuan = "Jakarta";

    // Tes searching algorithm
    int indeks = cariPenerbangan(dataPalsu,2,"Jakarta");
    cout << "Jakarta ada di indeks: " << indeks;

}