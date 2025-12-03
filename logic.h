#ifndef LOGIC_H // Mencegah double
#define LOGIC_H

#include "data_commons.h" // Mengimport struct
#include <string>

int jumlahBooking(std::string kodePesawat);
void loadDataPenerbangan(Penerbangan data[], int &jumlahData);
void cariPenerbangan(const Penerbangan data[], int n, std::string keyword, Penerbangan hasil[], int &nHasil);

#endif