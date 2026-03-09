#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <limits>
using namespace std;

const double PAJAK_RATE = 0.05;
const int MAX_LEMBUR = 20; // batas maksimal jam lembur

// Format angka rupiah dengan titik ribuan
string formatRupiah(double angka) {
    stringstream ss;
    ss << fixed << setprecision(0) << angka;
    string s = ss.str();
    string hasil;
    int count = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        hasil.insert(0, 1, s[i]);
        count++;
        if (count == 3 && i != 0) {
            hasil.insert(0, 1, '.');
            count = 0;
        }
    }
    return hasil;
}

// Input data karyawan
void inputData(string& nama, int& jamKerja, double& upahPerJam) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama Karyawan : ";
    getline(cin, nama);

    do {
        cout << "Masukkan Jumlah Jam Kerja : ";
        cin >> jamKerja;
        if (jamKerja < 0) cout << "Jam kerja tidak boleh negatif!\n";
    } while (jamKerja < 0);

    do {
        cout << "Masukkan Upah per Jam : ";
        cin >> upahPerJam;
        if (upahPerJam <= 0) cout << "Upah per jam harus lebih dari 0!\n";
    } while (upahPerJam <= 0);
}

// Hitung gaji pokok
void hitungGajiPokok(int jamKerja, double upahPerJam, double& gajiPokok) {
    gajiPokok = (jamKerja <= 40) ? jamKerja * upahPerJam : 40 * upahPerJam;
}

// Hitung lembur dengan batas maksimal
void hitungLembur(int jamKerja, double upahPerJam, double& gajiLembur) {
    if (jamKerja > 40) {
        int jamLembur = jamKerja - 40;
        if (jamLembur > MAX_LEMBUR) jamLembur = MAX_LEMBUR; // batasi lembur
        gajiLembur = jamLembur * (upahPerJam * 1.5);
    } else {
        gajiLembur = 0;
    }
}

// Hitung pajak
void hitungPajak(double totalGaji, double& pajak) {
    pajak = totalGaji * PAJAK_RATE;
}

// Buat slip gaji
string buatSlip(string nama, double gajiPokok, double gajiLembur, double pajak, double gajiBersih) {
    double persenLembur = (gajiPokok > 0) ? (gajiLembur / gajiPokok) * 100 : 0;

    stringstream slip;
    slip << "\n===== SLIP GAJI KARYAWAN =====\n";
    slip << "Nama            : " << nama << "\n";
    slip << "Gaji Pokok      : Rp " << formatRupiah(gajiPokok) << "\n";
    slip << "Gaji Lembur     : Rp " << formatRupiah(gajiLembur) 
         << " (" << fixed << setprecision(2) << persenLembur << "% dari gaji pokok)\n";
    slip << "Pajak (5%)      : Rp " << formatRupiah(pajak) << "\n";
    slip << "Gaji Bersih     : Rp " << formatRupiah(gajiBersih) << "\n";
    slip << "===============================\n";
    return slip.str();
}

int main() {
    vector<string> riwayat;
    int pilihan;

    do {
        cout << "\n=== MENU PROGRAM GAJI ===\n";
        cout << "1. Hitung Gaji Karyawan\n";
        cout << "2. Lihat Riwayat Perhitungan\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;

        if (pilihan == 1) {
            string nama;
            int jamKerja;
            double upahPerJam;
            double gajiPokok, gajiLembur, pajak, totalGaji, gajiBersih;

            inputData(nama, jamKerja, upahPerJam);

            hitungGajiPokok(jamKerja, upahPerJam, gajiPokok);
            hitungLembur(jamKerja, upahPerJam, gajiLembur);

            totalGaji = gajiPokok + gajiLembur;
            hitungPajak(totalGaji, pajak);
            gajiBersih = totalGaji - pajak;

            string slip = buatSlip(nama, gajiPokok, gajiLembur, pajak, gajiBersih);
            cout << slip;
            riwayat.push_back(slip);
        }
        else if (pilihan == 2) {
            if (riwayat.empty()) {
                cout << "\nBelum ada riwayat perhitungan.\n";
            }
            else {
                cout << "\n=== RIWAYAT PERHITUNGAN ===\n";
                for (size_t i = 0; i < riwayat.size(); i++) {
                    cout << "Slip #" << i + 1 << riwayat[i] << endl;
                }
            }
        }
        else if (pilihan == 3) {
            cout << "\nTerima kasih telah menggunakan program.\n";
        }
        else {
            cout << "\nPilihan tidak valid!\n";
        }

    } while (pilihan != 3);

    return 0;
}
