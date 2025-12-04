#ifndef LOGIC_H // Mencegah double
#define LOGIC_H

#include "data_commons.h" // Mengimport struct
#include <string>

// LOAD DATA
int inputData(Penerbangan data[], std::string filename);

// SEARCHING
int cariPenerbangan(Penerbangan data[], int n, std::string keyword);

// KONVERSI
string konversiWaktu(string jam); 

// FILTERING
void filterPenerbangan(Penerbangan data[], int n, std::string tujuan);

// SHUFFLE + GACHA
int gachaKursi(Penerbangan &p);

// BOOKING
void booking(Penerbangan &p, Penumpang penumpang[], int &totalPenumpang);

// CANCEL / DEDUP
void cancelBooking(Penumpang penumpang[], int &totalPenumpang);

// Kalo ada lagi tambahin aja (icad)

#endif