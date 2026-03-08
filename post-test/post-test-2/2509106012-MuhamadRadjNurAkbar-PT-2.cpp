#include <iostream>
//#include "tabulate/table.hpp";
using namespace std;
//using namespace tabulate;

struct User {
    string usr;
    string pw;
    string role;
};

int main() {
    User users[100];
    int jumlahUser = 2;
    int pilihan;
    users[0] = {"r", "012", "admin"};
    users[1] = {"a", "001", "user"}; 

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
                        if (username == users[i].usr && password == users[i].pw ) {
                            loginSukses = true;
                            roleUser = users[i].role;
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
                string usernameBaru, passwordBaru;
                cout << "Masukkan username baru: ";
                cin.ignore();
                getline(cin, usernameBaru);
                if (usernameBaru == "") {
                    cout << "Username tidak boleh kosong!\n";
                    break;
                }
                bool available = false;
                for (int i = 0; i < jumlahUser; i++) {
                    if (usernameBaru == users[i].usr) {
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
                users[jumlahUser] = {usernameBaru, passwordBaru, "user"};
                jumlahUser++;
                cout << "Registrasi berhasil!\n";
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