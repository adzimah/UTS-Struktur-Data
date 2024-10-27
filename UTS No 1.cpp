#include <iostream>
#include <iomanip> // Untuk std::setw
#include <cstdlib>
#include <cstring>

#define MAX_MAHASISWA 10

struct Mahasiswa {
    char NIM[15];
    char nama[50];
    float IPK;
};

struct Mahasiswa *mahasiswa[MAX_MAHASISWA];
int jumlahMahasiswa = 0;

void tambahMahasiswa(const char NIM[], const char nama[], float IPK) {
    if (jumlahMahasiswa >= MAX_MAHASISWA) {
        std::cout << "Kapasitas penuh. Tidak dapat menambah mahasiswa baru.\n";
        return;
    }
    struct Mahasiswa *mhs = (struct Mahasiswa *)malloc(sizeof(struct Mahasiswa));
    strcpy(mhs->NIM, NIM);
    strcpy(mhs->nama, nama);
    mhs->IPK = IPK;
    mahasiswa[jumlahMahasiswa++] = mhs;
    std::cout << "Mahasiswa berhasil ditambahkan!\n";
}

void hapusMahasiswa(const char NIM[]) {
    int found = -1;
    for (int i = 0; i < jumlahMahasiswa; i++) {
        if (strcmp(mahasiswa[i]->NIM, NIM) == 0) {
            found = i;
            free(mahasiswa[i]);
            break;
        }
    }
    if (found == -1) {
        std::cout << "Mahasiswa dengan NIM " << NIM << " tidak ditemukan.\n";
        return;
    }
    for (int i = found; i < jumlahMahasiswa - 1; i++) {
        mahasiswa[i] = mahasiswa[i + 1];
    }
    jumlahMahasiswa--;
    std::cout << "Mahasiswa dengan NIM " << NIM << " berhasil dihapus.\n";
}

void tampilkanMahasiswa() {
    if (jumlahMahasiswa == 0) {
        std::cout << "Tidak ada data mahasiswa.\n";
        return;
    }
    std::cout << "\nDaftar Mahasiswa:\n";
    std::cout << "==============================================\n";
    std::cout << "| " << std::setw(10) << "NIM" 
              << " | " << std::setw(20) << "Nama" 
              << " | " << std::setw(5) << "IPK" << " |\n";
    std::cout << "==============================================\n";
    for (int i = 0; i < jumlahMahasiswa; i++) {
        std::cout << "| " << std::setw(10) << mahasiswa[i]->NIM 
                  << " | " << std::setw(20) << mahasiswa[i]->nama 
                  << " | " << std::setw(5) << std::fixed << std::setprecision(2) << mahasiswa[i]->IPK 
                  << " |\n";
    }
    std::cout << "==============================================\n";
}

void urutkanMahasiswaBerdasarkanIPK() {
    for (int i = 0; i < jumlahMahasiswa - 1; i++) {
        for (int j = i + 1; j < jumlahMahasiswa; j++) {
            if (mahasiswa[i]->IPK < mahasiswa[j]->IPK) {
                struct Mahasiswa *temp = mahasiswa[i];
                mahasiswa[i] = mahasiswa[j];
                mahasiswa[j] = temp;
            }
        }
    }
    std::cout << "Data mahasiswa telah diurutkan berdasarkan IPK.\n";
}

int main() {
    int pilihan;
    char NIM[15], nama[50];
    float IPK;

    while (1) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Tambah Mahasiswa\n";
        std::cout << "2. Hapus Mahasiswa\n";
        std::cout << "3. Tampilkan Mahasiswa\n";
        std::cout << "4. Urutkan Mahasiswa Berdasarkan IPK\n";
        std::cout << "5. Keluar\n";
        std::cout << "Pilih opsi: ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1:
                do {
                    std::cout << "Masukkan NIM: ";
                    std::cin >> NIM;
                    std::cout << "Masukkan Nama: ";
                    std::cin.ignore(); // Mengabaikan newline sebelumnya
                    std::cin.getline(nama, 50);
                    std::cout << "Masukkan IPK: ";
                    std::cin >> IPK;
                    tambahMahasiswa(NIM, nama, IPK);

                    char lagi;
                    std::cout << "Apakah Anda ingin menambah data mahasiswa lagi? (y/t): ";
                    std::cin >> lagi;
                    if (lagi == 't' || lagi == 'T') {
                        tampilkanMahasiswa();
                        break;
                    }
                } while (1);
                break;

            case 2:
                tampilkanMahasiswa(); 
                std::cout << "Masukkan NIM mahasiswa yang akan dihapus: ";
                std::cin >> NIM;
                hapusMahasiswa(NIM);
                tampilkanMahasiswa();
                break;

            case 3:
                tampilkanMahasiswa();
                break;

            case 4:
                urutkanMahasiswaBerdasarkanIPK();
                tampilkanMahasiswa();
                break;

            case 5:
                std::cout << "Keluar dari program.\n";
                for (int i = 0; i < jumlahMahasiswa; i++) {
                    free(mahasiswa[i]);
                }
                return 0;

            default:
                std::cout << "Pilihan tidak valid!\n";
        }
    }
}
