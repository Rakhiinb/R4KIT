#ifndef LOGIC_H
#define LOGIC_H

#include "data_commons.h"
#include <string>

// Helper
int jumlahBooking(std::string kodePesawat);
bool cekKursiTerisi(std::string kodePesawat, int noKursi);

void loadDataPenerbangan(Penerbangan data[], int &jumlahData);
void simpanPenumpang(Penumpang p);

// Algorithms
void cariPenerbangan(const Penerbangan data[], int n, std::string keyword, Penerbangan hasil[], int &nHasil);
void filterWaktu(const Penerbangan sumber[], int nSumber, Penerbangan hasil[], int &nHasil, int kategoriWaktu);
int gachaKursi(std::string kodePesawat);
void bersihkanDuplikatBooking();
        
#endif