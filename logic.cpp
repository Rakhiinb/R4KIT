#include "logic.h" // Mengimport struct dan fungsi yang telah dideklarasi
#include <iostream>
#include <ctime> // buat acha (Fisher–Yates Shuffle)
#include <fstream> // Buat ifstream dll

using namespace std;

int inputData(Penerbangan data[], string filename){
    ifstream file("flights.txt");
    int n = 0;

    while (file >> data[n].kode >> data[n].maskapai >> data[n].tujuan
           >> data[n].jam >> data[n].harga >> data[n].jumlahTerisi)
    {
        for (int i = 0; i < TOTAL_KURSI; i++)
            data[n].kursi[i] = "-";

        n++;
    }

    file.close();
    return n;
}


// 1. Searching Algorithm (Linear Search)
int cariPenerbangan(const Penerbangan data[], int n, string keyword)
{
    for (int i = 0; i < n; i++)
    {
        // Cari berdasarkan kota tujuan, kode penerbangan, atau maskapai
        if (data[i].tujuan == keyword ||
            data[i].kode == keyword ||
            data[i].maskapai == keyword)
        {
            return i;
        }
    }
    return -1; // Jika tidak ketemu
}


// 2. FILTERING
void filterPenerbangan(Penerbangan data[], int n, string jamFilter, int maxHarga) {
    cout << "\n=== HASIL FILTER JAM: " << jamFilter 
         << " | HARGA <= " << maxHarga << " ===\n";

    bool ketemu = false;

    for (int i = 0; i < n; i++) {
        if (data[i].jam == jamFilter && data[i].harga <= maxHarga) {
            cout << data[i].kode << " | "
                 << data[i].maskapai << " | "
                 << data[i].tujuan << " | "
                 << data[i].jam << " | "
                 << data[i].harga << endl;
            ketemu = true;
        }
    }

    if (!ketemu)
        cout << "Data tidak ditemukan.\n";
}

// 3. Gacha or shuffle (Fisher–Yates Shuffle)
void gachaKursi(Penerbangan &p){
    srand(time(0));

    int kosong[TOTAL_KURSI];
    int totalKosong = 0;

    for (int i = 0; i < TOTAL_KURSI; i++)
        if (p.kursi[i] == "-")
            kosong[totalKosong++] = i;

    if (totalKosong == 0)
    {
        cout << "Kursi penuh!" << endl;
        return;
    }

    int acak = rand() % totalKosong;
    int hasil = kosong[acak];

    p.kursi[hasil] = "BOOKED";
    p.jumlahTerisi++;

    cout << "Kursi Anda: " << hasil + 1 << endl;
}


