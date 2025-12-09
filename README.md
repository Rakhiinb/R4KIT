# R4KIT — Sistem Booking Tiket Pesawat dengan Fitur Gacha Kursi

## Deskripsi Program

R4KIT adalah program pemesanan tiket pesawat yang dilengkapi fitur pemilihan kursi secara acak (gacha). Program ini mengelola data penerbangan, data kursi, dan data pemesanan menggunakan struct dan penyimpanan file dengan fstream.

Fitur utama meliputi pencarian penerbangan, filter penerbangan, gacha kursi dengan algoritma Fisher–Yates Shuffle, serta pembatalan tiket yang menggunakan deduplication untuk menjaga data tetap bersih. Program ini dibuat sebagai tugas akhir untuk mendemonstrasikan penggunaan minimal tiga algoritma dalam satu aplikasi.

Tujuan program ini adalah membuat sistem booking sederhana yang interaktif, menjaga integritas data, dan menerapkan konsep algoritma, struktur data, dan file handling.

## Algoritma yang Digunakan

### 1. Searching Algorithm

Algoritma pencarian digunakan untuk menemukan penerbangan berdasarkan:

-   Kota Tujuan
-   Maskapai

Jenis pencarian yang digunakan adalah Linear Search.
Algoritma ini bekerja dengan membandingkan satu per satu elemen dalam array hingga ditemukan kecocokan.

### 2. Filtering Algorithm

Algoritma filtering digunakan untuk menyaring daftar penerbangan berdasarkan:

-   Waktu keberangkatan (pagi/siang/malam)

Algoritma bekerja dengan mengecek setiap elemen apakah memenuhi syarat tertentu. Elemen yang memenuhi syarat akan dimasukkan ke daftar hasil filter.

### 3. Shuffling Algorithm (Fisher–Yates Shuffle)

Algoritma ini digunakan pada fitur Gacha Kursi.
Langkah kerja Fisher–Yates:

-   Ambil seluruh daftar kursi yang masih kosong.
-   Lakukan proses pengacakan (shuffle) dari indeks terakhir ke indeks pertama.
-   Tukar posisi elemen dengan indeks acak setiap iterasi.
-   Ambil kursi pertama dari hasil shuffle sebagai kursi terpilih.

Algoritma ini memastikan hasil acak yang adil dan tidak bias.

### 4. Deduplication Algorithm

Digunakan pada proses pembatalan tiket.
Setelah pembatalan dilakukan:

-   Data booking dihapus
-   Kursi dikembalikan menjadi "kosong"
-   Deduplication memastikan tidak ada entri ganda pada daftar booking

Algoritma ini bekerja dengan memeriksa setiap elemen dan hanya menyimpan data yang unik ke dalam daftar baru.

## Potongan Kode Penting
    int cariPenerbangan(const Penerbangan data[], int n, string keyword)
    {
        for (int i = 0; i < n; i++)
        {
            // Cari berdasarkan kota tujuan, kode penerbangan, atau maskapai
            if (data[i].tujuan == keyword ||
                data[i].id == keyword ||
                data[i].maskapai == keyword)
            {
                return i;
            }
        }
        return -1; // Jika tidak ketemu
    }



## Pembagian Tugas Anggota

| Nama                       | NPM          | Tugas |
| -------------------------- | ------------ | ----- |
| Rakhi Nathan Bertantra     | 140810250060 | Searching algorithm, integrasi Qt ke Code |
| Muhamad Irsyad Azharul Haq | 140810250078 | Filtering algorithm, Shuffling Algorithm |
| Atika Shafira              | 140810250093 | Deduplication algorithm |

## Cara Menjalankan Program

1. Prasyarat:
    - Install Qt Creator (Open Source version).
    - Pastikan Kit MinGW 64-bit terinstall.
2. Langkah-langkah:
    - Buka Qt Creator.
    - Pilih menu File > Open File or Project.
    - Pilih file R4KIT.pro.
    - Klik Configure Project jika diminta.
    - Tekan tombol Run (Segitiga Hijau) atau Ctrl+R.
3. Ikuti menu interaktif untuk melakukan:
    - Pencarian penerbangan
    - Filter penerbangan
    - Pemesanan
    - Gacha kursi

## Struktur Folder

    PROJEK-ALPROG-A-RAKIT-MENUJU-FKUI/
    ├── R4KIT.pro           # File Konfigurasi Project Qt
    ├── main.cpp            # Entry Point Aplikasi
    ├── data_commons.h      # Definisi Struct & Konstanta Global
    ├── logic.h             # Header Fungsi Algoritma
    ├── logic.cpp           # Implementasi Algoritma
    ├── logic_tester.cpp    # Testing Algoritma
    ├── mainwindow.h        # Header GUI
    ├── mainwindow.cpp      # Logika Interaksi GUI (Tombol & Tabel)
    ├── mainwindow.ui       # Desain Tampilan (XML Qt Designer)
    ├── flights.txt         # Data Penerbangan
    ├── bookings.txt        # Data Penumpang
    └── README.md           # Dokumentasi Project
