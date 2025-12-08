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

string konversiWaktu(string jam) {
    int angkaJam = stoi(jam.substr(0, 2));

    if (angkaJam >= 5 && angkaJam <= 11)
        return "pagi";
    else if (angkaJam >= 12 && angkaJam <= 17)
        return "siang";
    else
        return "malam";
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
int filterPenerbangan(Penerbangan data[], int n, Penerbangan hasil[], string waktuInput, int hargaMax) {
    int jumlahHasil = 0;

    for (int i = 0; i < n; i++) {
        string kategori = konversiWaktu(data[i].jam);

        if (kategori == waktuInput && data[i].harga <= hargaMax) {
            hasil[jumlahHasil].kode = data[i].kode;
            hasil[jumlahHasil].maskapai = data[i].maskapai;
            hasil[jumlahHasil].tujuan = data[i].tujuan;
            hasil[jumlahHasil].jam = data[i].jam;
            hasil[jumlahHasil].harga = data[i].harga;
            jumlahHasil++;
        }
    }

    return jumlahHasil;
}
// 3. Gacha or shuffle (Fisher–Yates Shuffle)
int gachaKursi(Penerbangan &p)
{
    int kosong[TOTAL_KURSI];
    int totalKosong = 0;

    for (int i = 0; i < TOTAL_KURSI; i++)
        if (p.kursi[i] == "-")
            kosong[totalKosong++] = i;

    if (totalKosong == 0)
        return -1;

    for (int i = totalKosong - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = kosong[i];
        kosong[i] = kosong[j];
        kosong[j] = temp;
    }
    int hasil = kosong[0];

    p.kursi[hasil] = "BOOKED";
    p.jumlahTerisi++;

    return hasil + 1;
}



