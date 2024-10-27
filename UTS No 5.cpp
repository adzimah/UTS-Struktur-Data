#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <iomanip>

using namespace std;

struct Buku {
    string ISBN;
    string judul;
    string pengarang;
    int tahunTerbit;
};

stack<string> riwayatPeminjaman;

queue<string> antrianPeminjaman;

const int MAKS_BUKU = 100;
Buku* daftarBuku[MAKS_BUKU];
int jumlahBuku = 0;

void tambahBuku() {
    char tambahLagi;

    do {
        if (jumlahBuku < MAKS_BUKU) {
            Buku* bukuBaru = new Buku;
            cout << "Masukkan ISBN: ";
            cin >> bukuBaru->ISBN;
            cout << "Masukkan Judul: ";
            cin.ignore();
            getline(cin, bukuBaru->judul);
            cout << "Masukkan Pengarang: ";
            getline(cin, bukuBaru->pengarang);
            cout << "Masukkan Tahun Terbit: ";
            cin >> bukuBaru->tahunTerbit;

            daftarBuku[jumlahBuku++] = bukuBaru;
            cout << "Buku berhasil ditambahkan.\n";
        } else {
            cout << "Kapasitas perpustakaan penuh.\n";
            break;
        }

        cout << "Apakah Anda ingin menambah data buku lagi? (y/t): ";
        cin >> tambahLagi;

    } while (tambahLagi == 'y' || tambahLagi == 'Y');
}

void cariBuku(const string& ISBN) {
    for (int i = 0; i < jumlahBuku; ++i) {
        if (daftarBuku[i]->ISBN == ISBN) {
            cout << "Buku ditemukan:\n";
            cout << "ISBN: " << daftarBuku[i]->ISBN << "\n";
            cout << "Judul: " << daftarBuku[i]->judul << "\n";
            cout << "Pengarang: " << daftarBuku[i]->pengarang << "\n";
            cout << "Tahun Terbit: " << daftarBuku[i]->tahunTerbit << "\n";
            return;
        }
    }
    cout << "Buku dengan ISBN " << ISBN << " tidak ditemukan.\n";
}

void tampilkanBuku() {
    if (jumlahBuku == 0) {
        cout << "Tidak ada buku di perpustakaan.\n";
        return;
    }

    cout << "\nDaftar Buku:\n";
    cout << left << setw(15) << "ISBN" 
         << setw(30) << "Judul" 
         << setw(20) << "Pengarang" 
         << setw(10) << "Tahun" << endl;
    cout << string(75, '-') << endl;

    for (int i = 0; i < jumlahBuku; ++i) {
        cout << left << setw(15) << daftarBuku[i]->ISBN 
             << setw(30) << daftarBuku[i]->judul 
             << setw(20) << daftarBuku[i]->pengarang 
             << setw(10) << daftarBuku[i]->tahunTerbit << endl;
    }
}

void pinjamBuku() {
    string ISBN;
    cout << "Masukkan ISBN buku yang akan dipinjam: ";
    cin >> ISBN;

    for (int i = 0; i < jumlahBuku; ++i) {
        if (daftarBuku[i]->ISBN == ISBN) {
            antrianPeminjaman.push(ISBN);
            cout << "Buku dengan ISBN " << ISBN << " telah ditambahkan ke antrian peminjaman.\n";
            return;
        }
    }
    cout << "Buku dengan ISBN " << ISBN << " tidak ditemukan di perpustakaan.\n";
}

void kembalikanBuku() {
    if (antrianPeminjaman.empty()) {
        cout << "Tidak ada buku dalam antrian peminjaman.\n";
        return;
    }

    string ISBN = antrianPeminjaman.front();
    antrianPeminjaman.pop();
    riwayatPeminjaman.push(ISBN);
    cout << "Buku dengan ISBN " << ISBN << " telah dikembalikan dan ditambahkan ke riwayat peminjaman.\n";
}

void tampilkanRiwayat() {
    if (riwayatPeminjaman.empty()) {
        cout << "Belum ada riwayat peminjaman.\n";
        return;
    }

    cout << "\nRiwayat Peminjaman:\n";
    cout << left << setw(15) << "ISBN" << endl;
    cout << string(15, '-') << endl;

    stack<string> tempStack = riwayatPeminjaman;
    while (!tempStack.empty()) {
        cout << left << setw(15) << tempStack.top() << endl;
        tempStack.pop();
    }
}

void tampilkanDaftarSebelumPinjam() {
    cout << "\nDaftar Buku Tersedia untuk Dipinjam:\n";
    tampilkanBuku();
}

int main() {
    int pilihan;

    do {
        cout << "\nMenu Perpustakaan:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Cari Buku\n";
        cout << "3. Tampilkan Semua Buku\n";
        cout << "4. Pinjam Buku\n";
        cout << "5. Kembalikan Buku\n";
        cout << "6. Tampilkan Riwayat Peminjaman\n";
        cout << "7. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2: {
                string ISBN;
                cout << "Masukkan ISBN untuk mencari buku: ";
                cin >> ISBN;
                cariBuku(ISBN);
                break;
            }
            case 3:
                tampilkanBuku();
                break;
            case 4:
                tampilkanDaftarSebelumPinjam();
                pinjamBuku();
                break;
            case 5:
                kembalikanBuku();
                break;
            case 6:
                tampilkanRiwayat();
                break;
            case 7:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 7);

    for (int i = 0; i < jumlahBuku; ++i) {
        delete daftarBuku[i];
    }

    return 0;
}
