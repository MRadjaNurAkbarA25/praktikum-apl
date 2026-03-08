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
    User users[5];
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
                    cout << "Username: ", cin >> username;
                    cout << "Password: ", cin >> password;

                    for (int i = 0; i < jumlahUser; i++) {
                        if (username == users[i].usr && password == users[i].pw ) {
                            loginSukses = true;
                            roleUser = users[i].role;
                            cout << "\nLogin berhasil! Selamat datang, " << username << "!\n\n";
                            break;
                        }
                    }
                    
                }
            } // case 1
        } // switch 1

    } // while menu 1
} // main