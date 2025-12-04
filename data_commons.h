#ifndef DATA_COMMONS_H
#define DATA_COMMONS_H

#include <string>

const int MAX_PENERBANGAN = 100; // Maksimal penerbangan adalah 100
const int MAX_BOOKING = 500; // Maksimal yang dapat booking adalah 500 orang
const int TOTAL_KURSI = 50; // 1 Pesawat 50 kursi

struct Penerbangan
{
    std::string kode;
    std::string maskapai;
    std::string tujuan;
    std::string jam;
    std::string kursi[TOTAL_KURSI];
    int harga;
    int jumlahTerisi;
};

struct Penumpang
{
    std::string nama;
    std::string kodePenerbangan;
    int nomorKursi;
};

struct HasilFilter 
{
    std::string kode;
    std::string maskapai;
    std::string tujuan;
    std::string waktu;   
    int harga;
};

#endif

