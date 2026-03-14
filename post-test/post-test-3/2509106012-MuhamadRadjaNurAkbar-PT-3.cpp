#include <iostream>
#include <tabulate/table.hpp>
#include <string>
using namespace tabulate;
using namespace std;

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

void clear() {
    system("cls || clear");
}

int tampilMenu(string judul, string opsi[], int jumlah) {
    int pilih;
    Table table;
    table.add_row({judul});
    for (int i=0; i < jumlah; i++) {
        table.add_row({to_string(i+1) + ". " + opsi[i]});
    }
    cout << table << "\n";
    cout << "Pilih: ";
    while (!(cin >> pilih) || pilih < 1 || pilih > jumlah) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Tidak valid!";
    }
    return pilih;
}

void tampilPenduduk(Penduduk data[], int jumlah) {
    Table table;
    table.add_row({"No", "NIK", "Nama", "Alamat", "No Telp"});
    for (int i=0; i < jumlah; i++) {
        table.add_row({
            to_string(i+1), 
            data[i].nik, 
            data[i].nama, 
            data[i].alamat, 
            data[i].noTelp});
    }
    table.column(0).format().width(4); // No
    table.column(1).format().width(6); // NIK
    table.column(2).format().width(16); // Nama
    table.column(3).format().width(16); // Alamat
    table.column(4).format().width(13); // No Telp

    cout << table << "\n";
}

void tampilAkun(User data[], int jumlah) {
    Table table;
    table.add_row({"No", "Username", "Role", "NIK", "Nama"});
    for (int i=0; i < jumlah; i++) {
        table.add_row({
            to_string(i+1), 
            data[i].usr, 
            data[i].role, 
            data[i].dataDiri.nik, 
            data[i].dataDiri.nama});
    }
    table.column(0).format().width(4); // No
    table.column(1).format().width(16); // Username
    table.column(2).format().width(5); // Role
    table.column(3).format().width(6); // NIK
    table.column(4).format().width(16); // Nama
    cout << table << "\n";
}

void tampilSurat(Surat data[], int jumlah) {
    Table table;
    table.add_row({"No", "ID Surat", "NIK Pemohon", "Jenis Surat", 
        "Keperluan", "Status", "Keterangan"});
    for (int i=0; i < jumlah; i++) {
        table.add_row({
            to_string(i+1), 
            data[i].idSurat, 
            data[i].nikPemohon, 
            data[i].jenisSurat, 
            data[i].keperluan,
            data[i].status,
            data[i].keterangan});
    }
    table.column(0).format().width(4); // No
    table.column(1).format().width(6); // ID Surat
    table.column(2).format().width(6); // NIK Pemohon
    table.column(3).format().width(17); // Jenis Surat
    table.column(4).format().width(11); // Keperluan
    table.column(5).format().width(8); // Status
    table.column(6).format().width(20); // Keterangan
    cout << table << "\n";
}

int cariPenduduk(Penduduk data[], int jumlah, string nik) {
    for (int i=0; i < jumlah; i++) {
        if (data[i].nik == nik) {
            return i;
        }
    }
    return -1;
}

int cariUser(User data[], int jumlah, string username) {
    for (int i=0; i < jumlah; i++) {
        if (data[i].usr == username) {
            return i;
        }
    }
    return -1;
}

int cariSuratAdmin(Surat data[], int jumlah, string idSurat) {
    for (int i=0; i < jumlah; i++) {
        if (data[i].idSurat == idSurat) {
            return i;
        }
    }
    return -1;
}

int cariSuratUser(Surat data[], int jumlah, string idSurat, string nik) {
    for (int i=0; i < jumlah; i++) {
        if (data[i].idSurat == idSurat && data[i].nikPemohon == nik) {
            return i;
        }
    }
    return -1;
}

void hapus(Penduduk data[], int &jumlah, int index) {
    for (int i= index; i < jumlah - 1; i++) {
        data[i] = data[i+1];
    }
    jumlah--;
}

void hapus(User data[], int &jumlah, int index) {
    for (int i= index; i < jumlah - 1; i++) {
        data[i] = data[i+1];
    }
    jumlah--;
}

void hapus(Surat data[], int &jumlah, int index) {
    for (int i= index; i < jumlah - 1; i++) {
        data[i] = data[i+1];
    }
    jumlah--;
}

string inputStr(string pesan) {
    string hasil;
    while (true) {
        cout << pesan;
        getline(cin, hasil);
        if (hasil != "") return hasil;
        cout << "Tidak boleh kosong!";
    }
}

string inputMax(string pesan, int maxLen) {
    string hasil;
    while (true) {
        cout << pesan;
        getline(cin, hasil);
        if (hasil == "") {
            cout << "Tidak boleh kosong!\n";
        } else if (hasil.length() > maxLen) {
            cout << "Tidak boleh lebih dari " << maxLen << " karakter!\n";
        } else {
            return hasil;
        }
    }
}

string hanyaAngka(string pesan) {
    string hasil;
    while (true) {
        cout << pesan;
        getline(cin, hasil);
        if (hasil == "") {
            cout << "Tidak boleh kosong!\n";
            continue;
        }
        bool valid = true;
        for (int i = 0; i < hasil.length(); i++) {
            if (!isdigit(hasil[i])) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "Hanya boleh angka!\n";
        } else {
            return hasil;
        }
    }
}

int main() {
    string menuUtama[] = {"Login", "Register", "Keluar"};
    int pilihan = tampilMenu("Menu Utama", menuUtama, 3);
}