#include "logic.h" // Mengimport struct dan fungsi yang telah dideklarasi
#include <iostream>
#include <fstream>
#include <QDebug>
#include <string>

using namespace std;

// Menghitung jumlah kursi yang sudah dibooking dalam pesawat tertentu
int jumlahBooking(string kodePesawat)
{
    ifstream file("bookings.txt");
    if (!file.is_open())
        return 0;
    string nama, kode;
    int kursi;
    int count = 0;
    while (file >> nama >> kode >> kursi)
    {
        if (kode == kodePesawat)
        {
            count++;
        }
    }
    file.close();
    return count;
}

// Memperbarui data terbaru di file flights.txt
void loadDataPenerbangan(Penerbangan data[], int &jumlahData)
{
    ifstream file("flights.txt");
    jumlahData = 0;

    if (!file.is_open())
    {
        qDebug() << "File flights.txt Gagal Dibuka!";
        return;
    }

    qDebug() << "File Berhasil Dibuka!";
    int tempJumlahTerisi;

    while (file >> data[jumlahData].kode >> data[jumlahData].maskapai >> data[jumlahData].tujuan >> data[jumlahData].jam >> data[jumlahData].harga >> tempJumlahTerisi)
    { // Baca angka 0 di file txt

        data[jumlahData].jumlahTerisi = jumlahBooking(data[jumlahData].kode);

        jumlahData++;
        if (jumlahData >= MAX_PENERBANGAN)
            break;
    }
    file.close();
}

// 1. Searching Algorithm (Linear Search)
void cariPenerbangan(const Penerbangan data[], int n, string keyword, Penerbangan hasil[], int &nHasil)
{
    nHasil = 0;
    for (int i = 0; i < n; i++)
    {
        // Cari berdasarkan kota tujuan, kode penerbangan, atau maskapai
        if (data[i].tujuan == keyword ||
            data[i].kode == keyword ||
            data[i].maskapai == keyword)
        {
            hasil[nHasil] = data[i];
            nHasil++;
        }
    }
}

// 4. Deduplication Algorithm
void bersihkanDuplikatBooking() {
    Penumpang semua[MAX_BOOKING];
    Penumpang bersih[MAX_BOOKING];
    int nSemua = 0, nBersih = 0;

    // Baca Semua Data ke Array 
    ifstream fin("bookings.txt");
    if (!fin.is_open()) return;
    while (fin >> semua[nSemua].nama >> semua[nSemua].kodePenerbangan >> semua[nSemua].nomorKursi) {
        nSemua++;
        if (nSemua >= MAX_BOOKING) break;
    }
    fin.close();

    // Filter Duplikat
    for (int i = 0; i < nSemua; i++) {
        bool duplikat = false;
        for (int j = 0; j < nBersih; j++) {
            // Duplikat jika Kode Pesawat sama dan Nomor Kursi sama
            if (semua[i].kodePenerbangan == bersih[j].kodePenerbangan && 
                semua[i].nomorKursi == bersih[j].nomorKursi) {
                duplikat = true;
                break;
            }
        }
        // Jika bersih, simpan
        if (!duplikat) {
            bersih[nBersih] = semua[i];
            nBersih++;
        }
    }

    // Tulis Ulang File dengan Data Bersih
    ofstream fout("bookings.txt");
    for (int i = 0; i < nBersih; i++) {
        fout << bersih[i].nama << " " << bersih[i].kodePenerbangan << " " << bersih[i].nomorKursi << endl;
    }
    fout.close();
}

void simpanPenumpang(Penumpang p)
{
    // Tambahkan data baru
    ofstream file("bookings.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Gagal membuka bookings.txt\n";
        return;
    }
    file << p.nama << " " << p.kodePenerbangan << " " << p.nomorKursi << "\n";
    file.close();
    // Jalankan pembersihan
    bersihkanDuplikatBooking();
}
