#include "logic.h" // Mengimport struct dan fungsi yang telah dideklarasi
#include <iostream>

using namespace std;

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
