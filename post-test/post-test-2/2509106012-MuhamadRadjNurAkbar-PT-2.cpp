#include <iostream>
//#include "tabulate/table.hpp";
using namespace std;
//using namespace tabulate;

struct Penduduk {
    string nik;
    string nama;
    string alamat;
    string noTelp;
};

struct User {
    string usr;
    string pw;
    string role;
    Penduduk dataDiri;
};

struct Surat {
    string idSurat;
    string nikPemohon;
    string jenisSurat;
    string keperluan;
    string status;
    string keterangan;
};

int main() {
    Penduduk dataPenduduk[100];
    User dataUser[100];
    Surat dataSurat[100];
    int jumlahPenduduk = 0;
    int jumlahUser = 2;
    int jumlahSurat = 0;
    int totalSurat = 0;
    int indexUser = -1;
    int pilihan;

    dataPenduduk[0] = {"001", "radja", "gg bersatu", "08111"};
    dataPenduduk[1] = {"002", "amat", "gg bersama", "08112"};
    jumlahPenduduk = 2;

    dataUser[0] = {"r", "012", "admin", dataPenduduk[0]};
    dataUser[1] = {"a", "011", "user", dataPenduduk[1]}; 

    cout << "Selamat datang di Website Balai Kota!\n\n";

    while (true) {
        cout << "Silahkan login untuk melanjutkan\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih: ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Input tidak valid!\n\n";
            continue;
        }
        switch (pilihan) {
            case 1: {
                int kesempatan = 3;
                string username, password;
                string roleUser = "";
                bool loginSukses = false;

                while (kesempatan > 0 && !loginSukses) {
                    cout << "Silahkan login untuk melanjutkan\n";
                    cout << "Username: "; 
                    cin >> username;
                    cout << "Password: "; 
                    cin >> password;
                    bool ditemukan = false;

                    for (int i = 0; i < jumlahUser; i++) {
                        if (username == dataUser[i].usr && password == dataUser[i].pw ) {
                            loginSukses = true;
                            roleUser = dataUser[i].role;
                            indexUser = i;
                            ditemukan = true;
                            cout << "\nLogin berhasil! Selamat datang, " << username << "!\n\n";
                            break;
                        }
                    }
                    if (!ditemukan) {
                        kesempatan--;
                        cout << "\nUsername dan password salah!\n";
                        cout << "Sisa kesempatan login: " << kesempatan << "\n"; 
                    }
                    
                }
                if (!loginSukses) {
                    cout << "Kesempatan login telah habis, coba lagi nanti!\n";
                    return 0;
                }
                break;
            } // case 1
            case 2 : {
                if (jumlahUser >= 100) {
                    cout << "Database penuh! tidak bisa register";
                    break;
                }
                string usernameBaru, passwordBaru, namaCari;
                cout << "Masukkan username baru: ";
                cin.ignore();
                getline(cin, usernameBaru);
                if (usernameBaru == "") {
                    cout << "Username tidak boleh kosong!\n";
                    break;
                }
                bool available = false;
                for (int i = 0; i < jumlahUser; i++) {
                    if (usernameBaru == dataUser[i].usr) {
                        available = true;
                        break;
                    }
                }
                if (available) {
                    cout << "Username sudah digunakan!\n";
                    break;
                }
                cout << "Masukkan password baru: ";
                getline(cin, passwordBaru);
                if (passwordBaru.length() < 3) {
                    cout << "Panjang password minimal 3 karakter!\n";
                    break;
                }
                cout << "Masukkan nama lengkap: ";
                getline(cin, namaCari);

                int hasilCari[100];
                int jumlahHasil = 0;
                for (int i = 0; i < jumlahPenduduk; i++) {
                    if (dataPenduduk[i].nama == namaCari) {
                        bool punyaAkun = false;
                        for (int j = 0; j < jumlahUser; j++) {
                            if (dataUser[j].dataDiri.nik == dataPenduduk[i].nik) {
                                punyaAkun = true;
                                break;
                            }
                        }
                        if (!punyaAkun) {
                            hasilCari[jumlahHasil] = i;
                            jumlahHasil++;
                        }
                    }
                }
                if (jumlahHasil == 0) {
                    cout << "Nama tidak ditemukan atau nama sudah punya akun!";
                    break;
                }
                int indexPenduduk = -1;
                if (jumlahHasil == 1) {
                    indexPenduduk = hasilCari[0];
                } else {
                    cout << "Ditemukan " << jumlahHasil << " penduduk dengan nama sama: \n";
                    for (int i = 0; i < jumlahHasil; i++) {
                        cout << i + 1 << ". " << dataPenduduk[hasilCari[i]].nama
                        << " - " << dataPenduduk[hasilCari[i]].alamat << "\n";
                    }
                    int pilihPenduduk;
                    cout << "Pilih nomor: ";
                    cin >> pilihPenduduk;
                    if (pilihPenduduk < 1 || pilihPenduduk > jumlahHasil) {
                        cout << "Pilihan tidak valid!\n";
                        break;
                    }
                    indexPenduduk = hasilCari[pilihPenduduk-1];
                }

                dataUser[jumlahUser] = {usernameBaru, passwordBaru, "user", dataPenduduk[indexPenduduk]};
                jumlahUser++;
                cout << "Registrasi berhasil!\n";
                cout << "Nik kamu: " << dataPenduduk[indexPenduduk].nik << "\n";
                break;
            } // case 2
            case 3 : {
                cout << "Kamu menekan tombol keluar!";
                return 0;
            }
            default : {
                cout << "Pilihan tidak valid!";
                break;
            }

        } // switch 1

    } // while menu 1
} // main