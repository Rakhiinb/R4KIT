#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data_commons.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // --- DAFTAR SLOT (Fungsi Tombol) ---
    void on_btnCari_clicked();
    void on_tabelPenerbangan_cellClicked(int row, int column);
    void on_btnGacha_clicked();
    void on_btnSimpan_clicked();

private:
    Ui::MainWindow *ui;

    // --- MEMORI UTAMA ---
    Penerbangan daftarPenerbangan[MAX_PENERBANGAN]; 
    int jumlahData = 0;

    // --- MEMORI SEMENTARA (State) ---
    std::string kodePesawatTerpilih; // Kode pesawat yg lagi diklik
    int nomorKursiDapat = -1;      
    
    void tampilkanKeTabel(Penerbangan data[], int n);
};
#endif 