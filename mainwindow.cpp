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
    // Ini aman dinyalakan asalkan jumlahData > 0 (nanti pas logic udh ada)
    tampilkanKeTabel(daftarPenerbangan, jumlahData);

    ui->groupBooking->setEnabled(false); // Matikan form kanan
    ui->btnSimpan->setEnabled(false);    // Matikan tombol simpan
    
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

