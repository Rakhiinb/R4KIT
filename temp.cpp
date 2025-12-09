#include "logic.h" // Mengimport struct dan fungsi yang telah dideklarasi
#include <iostream>
#include <fstream>
#include <QDebug>

using namespace std;

// Menghitung jumlah kursi yang sudah dibooking dalam pesawat tertentu
int jumlahBooking(string kodePesawat){
    ifstream file("bookings.txt");
    if(!file.is_open()) return 0;
    string nama, kode;
    int kursi;
    int count=0;
    while(file >> nama >> kode >> kursi){
        if(kode == kodePesawat){
            count++;
        }
    }
    file.close();
    return count;
}

// Memperbarui data terbaru di file flights.txt
void loadDataPenerbangan(Penerbangan data[], int &jumlahData) {
    ifstream file("flights.txt");
    jumlahData = 0;

    if (!file.is_open()) {
        qDebug() << "File flights.txt Gagal Dibuka!";
        return;
    }

    qDebug() << "File Berhasil Dibuka!";
    int tempJumlahTerisi; 

    while (file >> data[jumlahData].kode 
                >> data[jumlahData].maskapai 
                >> data[jumlahData].tujuan 
                >> data[jumlahData].jam 
                >> data[jumlahData].harga 
                >> tempJumlahTerisi) { // Baca angka 0 di file txt
        
        data[jumlahData].jumlahTerisi = jumlahBooking(data[jumlahData].kode);
        
        jumlahData++;
        if (jumlahData >= MAX_PENERBANGAN) break;
    }
    file.close();
}

// 1. Searching Algorithm (Linear Search)
void cariPenerbangan(const Penerbangan data[], int n, string keyword, Penerbangan hasil[], int &nHasil)
{
    nHasil=0;
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

#include <cstdlib> // WAJIB ADA: Buat rand()
#include <ctime>   // WAJIB ADA: Buat time()
// --- HELPER: CEK KURSI TERISI ---
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

// --- ALGORITMA UTAMA: FISHER-YATES SHUFFLE ---
int gachaKursi(string kodePesawat) {
    // 1. Cek dulu apakah pesawat sudah penuh (50 orang)?
    if (jumlahBooking(kodePesawat) >= TOTAL_KURSI) {
        return -1; // Kode error: Pesawat Penuh
    }

    // 2. Siapkan array kursi 1 sampai 50
    int kolamKursi[TOTAL_KURSI];
    for (int i = 0; i < TOTAL_KURSI; i++) {
        kolamKursi[i] = i + 1;
    }

    // 3. ACAK MANUAL (Fisher-Yates Algorithm)
    // Loop mundur dari belakang ke depan
    for (int i = TOTAL_KURSI - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Pilih index acak
        
        // Swap (Tukar posisi)
        int temp = kolamKursi[i];
        kolamKursi[i] = kolamKursi[j];
        kolamKursi[j] = temp;
    }

    // 4. Cari kursi pertama dari hasil acakan yang KOSONG
    // (Deduplication Logic: Cek ke file booking)
    for (int i = 0; i < TOTAL_KURSI; i++) {
        int calonKursi = kolamKursi[i];
        
        if (!cekKursiTerisi(kodePesawat, calonKursi)) {
            return calonKursi; // BERHASIL! Kembalikan nomor kursinya
        }
    }

    return -1; // Should not happen, tapi jaga-jaga
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



void bersihkanDuplikatBooking() {
    Penumpang semua[MAX_BOOKING];
    Penumpang bersih[MAX_BOOKING];
    int nSemua = 0, nBersih = 0;

    // A. Baca Semua Data ke RAM
    ifstream fin("bookings.txt");
    if (!fin.is_open()) return;
    while (fin >> semua[nSemua].nama >> semua[nSemua].kodePenerbangan >> semua[nSemua].nomorKursi) {
        nSemua++;
        if (nSemua >= MAX_BOOKING) break;
    }
    fin.close();

    // B. Filter Duplikat (Nested Loop Manual)
    for (int i = 0; i < nSemua; i++) {
        bool duplikat = false;
        for (int j = 0; j < nBersih; j++) {
            // Dianggap Duplikat jika: Kode Pesawat SAMA & Nomor Kursi SAMA
            if (semua[i].kodePenerbangan == bersih[j].kodePenerbangan && 
                semua[i].nomorKursi == bersih[j].nomorKursi) {
                duplikat = true;
                break;
            }
        }
        // Kalau bersih, simpan
        if (!duplikat) {
            bersih[nBersih] = semua[i];
            nBersih++;
        }
    }

    // C. Tulis Ulang File dengan Data Bersih
    ofstream fout("bookings.txt");
    for (int i = 0; i < nBersih; i++) {
        fout << bersih[i].nama << " " << bersih[i].kodePenerbangan << " " << bersih[i].nomorKursi << endl;
    }
    fout.close();
}

// Menyimpan Booking Baru
void simpanBooking(Penumpang p) {
    // 1. Tambahkan data baru di baris paling bawah
    ofstream file("bookings.txt", ios::app);
    if (file.is_open()) {
        file << p.nama << " " << p.kodePenerbangan << " " << p.nomorKursi << endl;
        file.close();
    }

    // 2. Langsung jalankan pembersihan (Jaga-jaga kalau ada error double input)
    bersihkanDuplikatBooking();
}

// --- TOMBOL 1: CARI ---
void MainWindow::on_btnCari_clicked()
{
    qDebug() << "--- TOMBOL CARI DIKLIK --- ";
    QString keywordQt = ui->inputCari->text();
    std::string keyword = keywordQt.toStdString();

    // Sesuai index, Semua Waktu = 0, Pagi =1, dst.
    int pilihanWaktu = ui->comboWaktu->currentIndex();

    Penerbangan hasilFilter[MAX_PENERBANGAN];
    int jumlahFilter = 0;

    Penerbangan hasilAkhir[MAX_PENERBANGAN];
    int jumlahAkhir = 0;

    // -- FILTERING --
    filterWaktu(daftarPenerbangan, jumlahData, hasilFilter, jumlahFilter, pilihanWaktu);

    // --- SEARCHING ---
    if (!keyword.empty()) {
        cariPenerbangan(hasilFilter, jumlahFilter, keyword, hasilAkhir, jumlahAkhir);
        if(jumlahAkhir>0){
            tampilkanKeTabel(hasilAkhir, jumlahAkhir);       
        } else {
            QMessageBox::warning(this, "Maaf", "Penerbangan tidak ditemukan!");
            // Tampilkan hasil filter waktu saja kalau search gagal
            tampilkanKeTabel(hasilFilter, jumlahFilter);
        }
    } else{
        tampilkanKeTabel(hasilFilter, jumlahFilter);
    }
}

// --- KLIK TABEL / PILIH PESAWAT ---
void MainWindow::on_tabelPenerbangan_cellClicked(int row, int column)
{
    // Cek biar gak crash kalau klik tabel kosong
    if(ui->tabelPenerbangan->item(row, 0) == nullptr) return;

    // Ambil data dari kolom tabel
    QString kode = ui->tabelPenerbangan->item(row, 0)->text(); // Kolom 0 = Kode
    QString maskapai = ui->tabelPenerbangan->item(row, 2)->text(); // Kolom 1 = Maskapai

    // Simpan ke memori (Sesuai variabel di mainwindow.h)
    kodePesawatTerpilih = kode.toStdString(); 

    // Update Tampilan Kanan
    ui->lblInfoPesawat->setText("Booking: " + maskapai + " (" + kode + ")");
    ui->groupBooking->setEnabled(true);
    ui->lblHasilKursi->setText("-");
    ui->btnSimpan->setEnabled(false);
}

// --- TOMBOL 2: GACHA ---
void MainWindow::on_btnGacha_clicked()
{
   // 1. Validasi Input Nama
    QString nama = ui->inputNama->text();
    if (nama.isEmpty()) {
        QMessageBox::critical(this, "Error", "Isi nama penumpang dulu!");
        return;
    }

    // 2. Setup Random Seed (Biar acakannya beda tiap detik)
    srand(time(0)); 

    // 3. Panggil Logic Gacha
    nomorKursiDapat = gachaKursi(kodePesawatTerpilih);

    // 4. Cek Hasil
    if (nomorKursiDapat == -1) {
        // Kalau penuh
        ui->lblHasilKursi->setText("FULL");
        QMessageBox::critical(this, "Full", "Maaf, Pesawat Penuh!");
        ui->btnSimpan->setEnabled(false);
    } else {
        // Kalau dapat
        ui->lblHasilKursi->setText(QString::number(nomorKursiDapat));
        ui->btnSimpan->setEnabled(true); // Nyalakan tombol simpan
    }
}

// --- TOMBOL 3: SIMPAN ---
void MainWindow::on_btnSimpan_clicked()
{
    // 1. Bungkus Data ke Struct Penumpang
    Penumpang p;
    p.nama = ui->inputNama->text().toStdString();
    p.kodePenerbangan = kodePesawatTerpilih;
    p.nomorKursi = nomorKursiDapat;

    // 2. Panggil Logic Simpan (Menulis ke bookings.txt)
    // Fungsi ini juga otomatis memanggil deduplication di logic.cpp
    simpanBooking(p); 

    // 3. Kasih Feedback ke User
    QMessageBox::information(this, "Sukses", "Tiket berhasil diamankan!");
    
    // 4. RESET TAMPILAN (Biar bersih)
    ui->groupBooking->setEnabled(false); // Matikan form kanan
    ui->inputNama->clear();              // Hapus nama
    ui->lblHasilKursi->setText("-");     // Reset label angka
    ui->tabelPenerbangan->clearSelection(); // Lepas seleksi tabel

    // 5. UPDATE REAL-TIME (PENTING!)
    // Kita panggil loadData lagi supaya program membaca ulang file booking
    // Hasilnya: Angka "Jumlah Terisi" di tabel akan nambah otomatis!
    loadDataPenerbangan(daftarPenerbangan, jumlahData);
    
    // Gambar ulang tabelnya dengan data terbaru
    tampilkanKeTabel(daftarPenerbangan, jumlahData);
}



