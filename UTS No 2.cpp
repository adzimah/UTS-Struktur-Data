#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip> // For std::setw

using namespace std;

struct Peralatan {
    string kode;
    string nama;
    int jumlah;
    string kondisi;
};

void tampilkanDaftarPeralatan(vector<Peralatan>& inventaris) {
    if (inventaris.empty()) {
        cout << "Tidak ada data peralatan untuk ditampilkan.\n";
        return;
    }

    // Urutkan berdasarkan kode peralatan
    sort(inventaris.begin(), inventaris.end(),
         [](const Peralatan& a, const Peralatan& b) { return a.kode < b.kode; });

    cout << "\nDaftar Peralatan:\n";
    cout << "========================================================\n";
    cout << "| " << setw(10) << left << "Kode" 
         << " | " << setw(20) << left << "Nama" 
         << " | " << setw(7) << left << "Jumlah" 
         << " | " << setw(15) << left << "Kondisi" << " |\n";
    cout << "========================================================\n";

    for (const auto& peralatan : inventaris) {
        cout << "| " << setw(10) << left << peralatan.kode 
             << " | " << setw(20) << left << peralatan.nama 
             << " | " << setw(7) << left << peralatan.jumlah 
             << " | " << setw(15) << left << peralatan.kondisi << " |\n";
    }
    cout << "========================================================\n";
}

void tambahPeralatan(vector<Peralatan>& inventaris) {
    char tambahLagi;

    do {
        Peralatan peralatan;
        cout << "Masukkan kode peralatan: ";
        cin >> peralatan.kode;
        cout << "Nama peralatan: ";
        cin.ignore();
        getline(cin, peralatan.nama);
        cout << "Jumlah: ";
        cin >> peralatan.jumlah;
        cout << "Kondisi: ";
        cin.ignore();
        getline(cin, peralatan.kondisi);

        inventaris.push_back(peralatan);
        cout << "Data peralatan berhasil ditambahkan.\n";
        
        cout << "Apakah Anda ingin menambah data lagi? (y/t): ";
        cin >> tambahLagi;

    } while (tambahLagi == 'y' || tambahLagi == 'Y');

    // Tampilkan daftar setelah menambah data
    tampilkanDaftarPeralatan(inventaris);
}

void ubahPeralatan(vector<Peralatan>& inventaris) {
    string kode;
    cout << "Masukkan kode peralatan yang ingin diubah: ";
    cin >> kode;

    for (auto& peralatan : inventaris) {
        if (peralatan.kode == kode) {
            cout << "Masukkan nama baru: ";
            cin.ignore();
            getline(cin, peralatan.nama);
            cout << "Masukkan jumlah baru: ";
            cin >> peralatan.jumlah;
            cout << "Masukkan kondisi baru: ";
            cin.ignore();
            getline(cin, peralatan.kondisi);
            cout << "Data peralatan berhasil diubah.\n";
            return;
        }
    }
    cout << "Peralatan dengan kode " << kode << " tidak ditemukan.\n";
}

void hapusPeralatan(vector<Peralatan>& inventaris) {
    string kode;
    cout << "Masukkan kode peralatan yang ingin dihapus: ";
    cin >> kode;

    auto it = remove_if(inventaris.begin(), inventaris.end(),
                        [&kode](const Peralatan& peralatan) { return peralatan.kode == kode; });

    if (it != inventaris.end()) {
        inventaris.erase(it, inventaris.end());
        cout << "Data peralatan berhasil dihapus.\n";
    } else {
        cout << "Peralatan dengan kode " << kode << " tidak ditemukan.\n";
    }
}

void simpanData(const vector<Peralatan>& inventaris, const string& namaFile) {
    ofstream file(namaFile);

    if (file.is_open()) {
        for (const auto& peralatan : inventaris) {
            file << peralatan.kode << "|" << peralatan.nama << "|" 
                 << peralatan.jumlah << "|" << peralatan.kondisi << "\n";
        }
        cout << "Data peralatan berhasil disimpan ke file.\n";
    } else {
        cout << "Tidak dapat membuka file untuk menyimpan data.\n";
    }
}

void bacaData(vector<Peralatan>& inventaris, const string& namaFile) {
    ifstream file(namaFile);
    inventaris.clear();

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Peralatan peralatan;
            size_t pos = 0;

            pos = line.find('|');
            peralatan.kode = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find('|');
            peralatan.nama = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find('|');
            peralatan.jumlah = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            peralatan.kondisi = line;

            inventaris.push_back(peralatan);
        }
        cout << "Data peralatan berhasil dibaca dari file.\n";
    } else {
        cout << "Tidak dapat membuka file untuk membaca data.\n";
    }
}

void tampilkanLaporan(vector<Peralatan>& inventaris) {
    if (inventaris.empty()) {
        cout << "Tidak ada data peralatan untuk ditampilkan.\n";
        return;
    }

    // Urutkan berdasarkan kode peralatan
    sort(inventaris.begin(), inventaris.end(),
         [](const Peralatan& a, const Peralatan& b) { return a.kode < b.kode; });

    cout << "\nLaporan Inventaris Peralatan:\n";
    cout << "========================================================\n";
    cout << "| " << setw(10) << left << "Kode" 
         << " | " << setw(20) << left << "Nama" 
         << " | " << setw(7) << left << "Jumlah" 
         << " | " << setw(15) << left << "Kondisi" << " |\n";
    cout << "========================================================\n";

    for (const auto& peralatan : inventaris) {
        cout << "| " << setw(10) << left << peralatan.kode 
             << " | " << setw(20) << left << peralatan.nama 
             << " | " << setw(7) << left << peralatan.jumlah 
             << " | " << setw(15) << left << peralatan.kondisi << " |\n";
    }
    cout << "========================================================\n";
}

int main() {
    vector<Peralatan> inventaris;
    string namaFile = "inventaris.txt";
    int pilihan;

    bacaData(inventaris, namaFile);

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Peralatan\n";
        cout << "2. Ubah Peralatan\n";
        cout << "3. Hapus Peralatan\n";
        cout << "4. Simpan Data ke File\n";
        cout << "5. Laporan Inventaris\n";
        cout << "6. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPeralatan(inventaris);
                break;
            case 2:
                ubahPeralatan(inventaris);
                break;
            case 3:
                hapusPeralatan(inventaris);
                break;
            case 4:
                simpanData(inventaris, namaFile);
                break;
            case 5:
                tampilkanLaporan(inventaris);
                break;
            case 6:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}
