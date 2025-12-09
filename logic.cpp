#include "logic.h" // Mengimport struct dan fungsi yang telah dideklarasi
#include <iostream>
#include <ctime> // buat acha (Fisher–Yates Shuffle)
#include <fstream> // Buat ifstream dll

using namespace std;

// Gacha Algorithm helper
bool cekKursiTerisi(string kodePesawat, int noKursi) {
    ifstream file("bookings.txt");
    if (!file.is_open()) return false; // Belum ada yang booking

    string nama, kode;
    int kursi;
    
    // Baca file booking satu per satu
    while (file >> nama >> kode >> kursi) {
        // Kalau ketemu kode pesawat SAMA dan kursi SAMA -> berarti TERISI
        if (kode == kodePesawat && kursi == noKursi) {
            return true; 
        }
    }
    file.close();
    return false;
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

// 2. Filtering Algorithm
void filterWaktu(const Penerbangan sumber[], int nSumber, 
                 Penerbangan hasil[], int &nHasil, 
                 int kategoriWaktu) {
    
    nHasil = 0;

    for (int i = 0; i < nSumber; i++) {
        // 0 = Semua Waktu
        if (kategoriWaktu == 0) {
            hasil[nHasil] = sumber[i];
            nHasil++;
            continue; // Lanjut ke data berikutnya
        }

        // Ambil 2 angka depan lalu ubah jadi integer.
        int jamInt = std::stoi(sumber[i].jam.substr(0, 2)); 
        bool lolos = false;

        // 1 = PAGI (00:00 sampai 10:59)
        if (kategoriWaktu == 1) { 
            if (jamInt >= 0 && jamInt < 11) lolos = true;
        }
        // 2 = SIANG (11:00 sampai 17:59)
        else if (kategoriWaktu == 2) { 
            if (jamInt >= 11 && jamInt < 18) lolos = true;
        }
        // 3 = MALAM (18:00 sampai 23:59)
        else if (kategoriWaktu == 3) { 
            if (jamInt >= 18 && jamInt <= 23) lolos = true;
        }

        if (lolos) {
            hasil[nHasil] = sumber[i];
            nHasil++;
        }
        
    }
}

// 3. Gacha or shuffle (Fisher–Yates Shuffle)
int gachaKursi(string kodePesawat) {
    // Cek apakah pesawat sudah penuh (50 orang)
    if (jumlahBooking(kodePesawat) >= TOTAL_KURSI) {
        return -1;
    }

    // Siapkan array kursi 1 sampai 50
    int kolamKursi[TOTAL_KURSI];
    for (int i = 0; i < TOTAL_KURSI; i++) {
        kolamKursi[i] = i + 1;
    }

    // Fisher-Yates Algorithm
    for (int i = TOTAL_KURSI - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Pilih index acak
        
        // Swap
        int temp = kolamKursi[i];
        kolamKursi[i] = kolamKursi[j];
        kolamKursi[j] = temp;
    }

    // Cek kursi terisi atau tidak
    for (int i = 0; i < TOTAL_KURSI; i++) {
        int calonKursi = kolamKursi[i];
        
        if (!cekKursiTerisi(kodePesawat, calonKursi)) {
            return calonKursi; 
        }
    }

    return -1; 
}