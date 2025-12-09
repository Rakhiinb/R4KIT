#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
 ui->setupUi(this);

    // --- LOAD DATA ---
    loadDataPenerbangan(daftarPenerbangan, jumlahData);

    // --- TAMPILKAN TABEL ---
    tampilkanKeTabel(daftarPenerbangan, jumlahData);

    ui->groupBooking->setEnabled(false); 
    ui->btnSimpan->setEnabled(false);   
    
    // Atur Lebar Kolom
    ui->tabelPenerbangan->setColumnWidth(0, 60);  // Kode
    ui->tabelPenerbangan->setColumnWidth(1, 100); // Kota Tujuan
    ui->tabelPenerbangan->setColumnWidth(2, 150); // Maskapai
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Menampilkan tabel
void MainWindow::tampilkanKeTabel(Penerbangan data[], int n){
    qDebug() << "--- TABEL DITAMPILKAN ---";
    ui->tabelPenerbangan->setRowCount(0); // Bersihkan tabel

    for(int i=0; i<n;i++){
        ui->tabelPenerbangan->insertRow(i); // Tambah baris

        ui->tabelPenerbangan->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(data[i].kode)));
        ui->tabelPenerbangan->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(data[i].tujuan)));
        ui->tabelPenerbangan->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(data[i].maskapai)));
        ui->tabelPenerbangan->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(data[i].jam)));
        ui->tabelPenerbangan->setItem(i, 4, new QTableWidgetItem(QString::number(data[i].harga)));
        ui->tabelPenerbangan->setItem(i, 5, new QTableWidgetItem(QString::number(data[i].jumlahTerisi) + "/50"));
    }
}


// --- TOMBOL 1: CARI ---
void MainWindow::on_btnCari_clicked()
{
    qDebug() << "--- TOMBOL CARI DIKLIK --- ";
    QString keywordQt = ui->inputCari->text();
    std::string keyword = keywordQt.toStdString();

    // Sesuai index, Semua Waktu = 0, Pagi = 1, dst.
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
    // Jaga jaga jika klik tabel kosong
    if(ui->tabelPenerbangan->item(row, 0) == nullptr) return;

    // Ambil data dari kolom tabel
    QString kode = ui->tabelPenerbangan->item(row, 0)->text(); // Kolom 0 = Kode
    QString maskapai = ui->tabelPenerbangan->item(row, 2)->text(); // Kolom 2 = Maskapai

    kodePesawatTerpilih = kode.toStdString(); 

    ui->lblInfoPesawat->setText("Booking: " + maskapai + " (" + kode + ")");
    ui->groupBooking->setEnabled(true);
    ui->lblHasilKursi->setText("-");
    ui->btnSimpan->setEnabled(false);
}

// --- TOMBOL 2: GACHA ---
void MainWindow::on_btnGacha_clicked()
{
   // Validasi Input Nama
    QString nama = ui->inputNama->text();
    if (nama.isEmpty()) {
        QMessageBox::critical(this, "Error", "Isi nama penumpang dulu!");
        return;
    }

    // Panggil Logic Gacha
    nomorKursiDapat = gachaKursi(kodePesawatTerpilih);

    // Cek Hasil
    if (nomorKursiDapat == -1) {
        // Kalau penuh
        ui->lblHasilKursi->setText("FULL");
        QMessageBox::critical(this, "Full", "Maaf, Pesawat Penuh!");
        ui->btnSimpan->setEnabled(false);
    } else {
        // Kalau dapat
        ui->lblHasilKursi->setText(QString::number(nomorKursiDapat));
        ui->btnSimpan->setEnabled(true); // Bisa simpan
    }
}

// --- TOMBOL 3: SIMPAN ---
void MainWindow::on_btnSimpan_clicked()
{
    // Bungkus Data ke Struct Penumpang
    Penumpang p;
    p.nama = ui->inputNama->text().toStdString();
    p.kodePenerbangan = kodePesawatTerpilih;
    p.nomorKursi = nomorKursiDapat;

    // Panggil Logic Simpan (Menulis ke bookings.txt)
    simpanPenumpang(p); 

    QMessageBox::information(this, "Sukses", "Tiket berhasil diamankan!");
    
    // RESET TAMPILAN
    ui->groupBooking->setEnabled(false); // Matikan form kanan
    ui->inputNama->clear();              // Hapus nama
    ui->lblHasilKursi->setText("-");     // Reset label angka
    ui->tabelPenerbangan->clearSelection(); // Lepas seleksi tabel

    // UPDATE REAL-TIME, Jumlah Terisi
    loadDataPenerbangan(daftarPenerbangan, jumlahData);
    
    // Tampilkan ulang tabelnya dengan data terbaru
    tampilkanKeTabel(daftarPenerbangan, jumlahData);
}
