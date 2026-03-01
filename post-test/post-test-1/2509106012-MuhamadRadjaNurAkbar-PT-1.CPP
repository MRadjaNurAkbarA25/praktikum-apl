#include <iostream>
using namespace std;

int main() {
    double detik, menit, jam;
    int pilihan;
    int kesempatan = 3;
    string usr = "radja", pw = "012", username, password;

    cout << "Selamat datang di Time Flies! Konversi satuan waktu ke satuan lain!\n\n";
    while (kesempatan > 0) {
        cout << "Silahkan login untuk melanjutkan\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (username == usr && password == pw) {
            cout << "Login berhasil!\n";
            break;
        } else {
            kesempatan--;
            cout << "Username dan password salah!\n\n";
            cout << "Sisa kesempatan login: " << kesempatan << endl; 
        }
    } if (kesempatan <= 0) {
        cout << "Kesempatan login telah habis, coba lagi nanti!\n";
        return 0;
    }

    while(true) {
        cout << "=== PROGRAM KONVERSI WAKTU ===\n\n";
        cout << "Pilih menu konversi waktu!\n";
        cout << "1. Jam     --> Menit & Detik\n";
        cout << "2. Menit   --> Jam & Detik\n";
        cout << "3. Detik   --> Jam & Menit\n";
        cout << "4. Keluar\n";
        cout << "Pilihanmu: ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Input tidak valid!\n\n";
            continue;
        }
        switch(pilihan) {
            case 1: {
                cout << "Masukkan jam: ";
                cin >> jam;
                if (jam < 0) {
                    cout << "Nilai tidak boleh negatif!\n\n";
                    break;
                }
                menit = jam * 60;
                detik = jam * 3600;
                cout << jam << " " << "Jam = " << menit << " " << "Menit = " << detik << " " << "Detik\n\n";
                break;
            }
            case 2: {
                cout << "Masukkan menit: ";
                cin >> menit;
                if (menit < 0) {
                    cout << "Nilai tidak boleh negatif!\n\n";
                    break;
                }
                jam = menit / 60.0;
                detik = menit * 60;
                cout << menit << " " << "Menit = " << jam << " " << "Jam = " << detik << " " << "Detik\n\n";
                break;
            }
            case 3: {
                cout << "Masukkan detik: ";
                cin >> detik;
                if (detik < 0) {
                    cout << "Nilai tidak boleh negatif!\n\n";
                    break;
                }
                jam = detik / 3600.0;
                menit = detik / 60.0;
                cout << detik << " " << "Detik = " << jam << " " << "Jam = " << menit << " " << "Menit\n\n";
                break;
            }
            case 4: {
                cout << "Kamu menekan tombol keluar!\n";
                return 0;
            }
            default: {
                cout << "Pilihan tidak valid!\n\n";
                break;
            }
        }
    }
    return 0;
}