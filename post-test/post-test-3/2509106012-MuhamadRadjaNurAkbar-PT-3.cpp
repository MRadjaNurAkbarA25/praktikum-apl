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

bool konfirmasi(string pesan) {
    char jawaban;
    cout << pesan << " (y/n): ";
    cin >> jawaban;
    return jawaban == 'y';
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

bool login(User dataUser[], int jumlahUser, int kesempatan, int &indexUser) {
    if (kesempatan == 0) {
        cout << "Kesempatan habis!\n";
        return false;
    }
    string username, password;
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    for (int i = 0; i < jumlahUser; i++) {
        if (username == dataUser[i].usr && password == dataUser[i].pw) {
            indexUser = i;
            cout << "Login berhasil! Selamata datang, " << username << "!\n";
            return true;
        }
    }
    cout << "Salah! Sisa kesempatan: " << kesempatan - 1 << "\n";
    return login(dataUser, jumlahUser, kesempatan - 1, indexUser); 
}

bool usernameAda (User data[], int jumlah, string username) {
    for (int i=0; i < jumlah; i++) {
        if (data[i].usr == username) return true;
    }
    return false;
}

int cariPendudukDariNama (Penduduk data[], int jumlah, string nama, int hasilCari[]) {
    int jumlahHasil = 0;
    for (int i=0; i < jumlah; i++) {
        if (data[i].nama == nama) {
            hasilCari[jumlahHasil] = i;
            jumlahHasil++;
        }
    }
    return jumlahHasil;
}

bool punyaAkun (User dataUser[], int jumlahUser, string nik) {
    for (int i=0; i < jumlahUser; i++) {
        if (dataUser[i].dataDiri.nik == nik) return true;
    }
    return false;
}

void registarsi(User dataUser[], int &jumlahUser, Penduduk dataPenduduk[], int jumlahPenduduk) {
    string usernameBaru = inputStr("Username: ");
    if (usernameAda(dataUser, jumlahUser, usernameBaru)) {
        cout << "Username sudah digunakan!\n";
        return;
    }

    string passwordBaru = inputStr("Password: ");
    if (passwordBaru.length() < 3) {
        cout << "Minimal berjumlah 3 karakter!\n";
        return;
    }

    string namaCari = inputStr("Nama lengkap: ");
    int hasilCari[100];
    int jumlahHasil = cariPendudukDariNama(dataPenduduk, jumlahPenduduk, namaCari, hasilCari);

    int filter[100];
    int jumlahFilter = 0;
    for (int i=0; i < jumlahHasil; i++) {
        if (!punyaAkun(dataUser, jumlahUser, dataPenduduk[hasilCari[i]].nik)) {
            filter[jumlahFilter++] = hasilCari[i];
        }
    }

    if (jumlahFilter == 0) {
        cout << "Nama tidak ditemukan atau nama sudah punya akun!\n";
        return;
    }

    int indexPenduduk;
    if (jumlahFilter == 1) {
        indexPenduduk = filter[0];
    } else {
        Table table;
        table.add_row({"No", "Nama", "Alamat", "NIK"});
        for (int i = 0; i < jumlahFilter; i++) {
            table.add_row({
                to_string(i+1),
                dataPenduduk[filter[i]].nama,
                dataPenduduk[filter[i]].alamat,
                dataPenduduk[filter[i]].nik
            });
            table.column(0).format().width(4); // No
            table.column(1).format().width(16); //Nama
            table.column(2).format().width(16); // Alamat
            table.column(3).format().width(6); // NIK
        }
        cout << table << "\n";

        int pilih;
        cout << "Pilih nomor: ";
        while (!(cin >> pilih) || pilih < 1 || pilih > jumlahFilter) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Tidak valid!\n Pilih: ";
        }
        indexPenduduk = filter[pilih-1];
    }

    dataUser[jumlahUser++] = {usernameBaru, passwordBaru, "user", dataPenduduk[indexPenduduk]};
    cout << "Registrasi berhasil!\n";
    cout << "NIK kamu: " << dataPenduduk[indexPenduduk].nik << "\n";
}

bool telpAda(Penduduk data[], int jumlah, string telepon) {
    for (int i=0; i < jumlah; i++) {
        if (data[i].noTelp == telepon) return true;
    }
    return false;
}

void tambahPenduduk(Penduduk data[], int &jumlah, int &totalPenduduk) {
    string namaBaru, alamatBaru, noTelpBaru;
    namaBaru = inputStr("Nama penduduk: ");
    alamatBaru = inputStr("Alamat penduduk: ");
    noTelpBaru = hanyaAngka("No telepon penduduk: ");
    if (telpAda(data, jumlah, noTelpBaru )) {
        cout << "No telepon sudah digunakan!\n";
        return;
    }
    string nikBaru = "PDK" + to_string(++totalPenduduk);
    data[jumlah++] = {nikBaru, namaBaru, alamatBaru, noTelpBaru};
    cout << "Berhasil ditambahkan!\n";
}

void editPenduduk(Penduduk dataPenduduk[], int jumlahPenduduk, User dataUser[], int jumlahUser) {
    string cariNIK;
    cout << "Masukkan NIK dari data penduduk yang ingin diubah: ";
    getline(cin, cariNIK);
    int cariIndex = cariPenduduk(dataPenduduk, jumlahPenduduk, cariNIK);
    if (cariIndex == -1) {
        cout << "NIK tidak ditemukan!\n";
        return;
    }
    cout << "Data ditemukan: \n";
    Table table;
    table.add_row({"NIK", "Nama", "Alamat", "No Telp"});
    table.add_row({
    dataPenduduk[cariIndex].nik,
    dataPenduduk[cariIndex].nama,
    dataPenduduk[cariIndex].alamat,
    dataPenduduk[cariIndex].noTelp
    });
    table.column(0).format().width(6); // NIK
    table.column(1).format().width(16); // Nama
    table.column(2).format().width(16); // Alamat
    table.column(3).format().width(13); // No Telp
    string opsiUbahPenduduk[] = {"Ubah nama penduduk", "Ubah alamat penduduk", "Ubah no telepon penduduk", "Kembali"};
    int pilihan = tampilMenu("Pilih perubahan\n", opsiUbahPenduduk, 4 );
    switch (pilihan) {
        case 1: {
            string namaGanti = inputStr("Nama baru: ");
            dataPenduduk[cariIndex].nama = namaGanti;
            for (int i=0; i < jumlahUser; i++) {
                if (dataUser[i].dataDiri.nik == dataPenduduk[cariIndex].nik) {
                    dataUser[i].dataDiri.nama = namaGanti;
                    break;
                }
            }
            cout << "Berhasil diubah!\n";
            break;
        }
        case 2: {
            string alamatGanti = inputStr("Alamat baru: ");
            dataPenduduk[cariIndex].alamat = alamatGanti;
            for (int i=0; i < jumlahUser; i++) {
                if (dataUser[i].dataDiri.nik == dataPenduduk[cariIndex].nik) {
                    dataUser[i].dataDiri.alamat = alamatGanti;
                    break;
                }
            }
            cout << "Berhasil diubah!\n";
            break;
        }
        case 3: {
            string noTelpGanti = hanyaAngka("No telepon baru: ");
            if (telpAda(dataPenduduk, jumlahPenduduk, noTelpGanti)) {
                cout << "Nomor telepon sudah digunakan!\n";
                return;
            }
            dataPenduduk[cariIndex].noTelp = noTelpGanti;
            for (int i=0; i < jumlahUser; i++) {
                if (dataUser[i].dataDiri.nik == dataPenduduk[cariIndex].nik) {
                    dataUser[i].dataDiri.noTelp = noTelpGanti;
                    break;
                }
            }
            cout << "Berhasil diubah!\n";
            break;
        }
        case 4: {
            break;
        }
    }
}

void hapusPendudukAdmin(Penduduk dataPenduduk[], int &jumlahPenduduk, User dataUser[], int &jumlahUser, Surat dataSurat[], int &jumlahSurat, int &indexUser) {
    string cariNIK;
    cout << "Masukkan NIK dari data penduduk yang ingin diubah: ";
    getline(cin, cariNIK);
    int cariIndex = cariPenduduk(dataPenduduk, jumlahPenduduk, cariNIK);
    if (cariIndex == -1) {
        cout << "NIK tidak ditemukan!\n";
        return;
    }
    bool adaAdmin = false;
    for (int i = 0; i < jumlahUser; i++) {
        if (dataUser[i].dataDiri.nik == dataPenduduk[cariIndex].nik &&
        dataUser[i].role == "admin") {
            adaAdmin = true;
            break;
        }
    }
    if (adaAdmin) {
        cout << "Tidak bisa hapus penduduk dengan akun admin!\n";
        return;
    }
    cout << "Data ditemukan: \n";
    Table table;
    table.add_row({"NIK", "Nama", "Alamat", "No Telp"});
    table.add_row({
    dataPenduduk[cariIndex].nik,
    dataPenduduk[cariIndex].nama,
    dataPenduduk[cariIndex].alamat,
    dataPenduduk[cariIndex].noTelp
    });
    table.column(0).format().width(6); // NIK
    table.column(1).format().width(16); // Nama
    table.column(2).format().width(16); // Alamat
    table.column(3).format().width(13); // No Telp

    if (!konfirmasi("Yakin ingin hapus?")) {
        cout << "Batal!\n";
        return;
    }
    string nikHapus = dataPenduduk[cariIndex].nik;
    hapus(dataPenduduk, jumlahPenduduk, cariIndex);

    for (int i=0; i < jumlahUser; i++) {
        if (dataUser[i].dataDiri.nik == nikHapus) {
            if (i<indexUser) indexUser--;
            hapus(dataUser, jumlahUser, i);
            break;
        }
    }

    for (int i=0; i < jumlahSurat; i++) {
        if (dataSurat[i].nikPemohon == nikHapus) {
            hapus(dataSurat, jumlahSurat, i);
            i--;
        }
    }
    cout << "Berhasil dihapus!\n";
}

void hapusAkun(User data[], int &jumlah, int &indexUser) {
    string inputUser;
    cout << "Masukkan username dari akun yang ingin dihapus: ";
    getline(cin, inputUser);
    int cariIndex = cariUser(data, jumlah, inputUser);
    if (cariIndex == -1) {
        cout << "Username tidak ditemukan!\n";
        return;
    }
    if (data[cariIndex].role == "admin") {
        cout << "Tidak bisa hapus akun admin!\n";
        return;
    }
    cout << "Data ditemukan: \n";
    Table table;
    table.add_row({"Username", "Role", "NIK", "Nama"});
    table.add_row({
    data[cariIndex].usr,
    data[cariIndex].role,
    data[cariIndex].dataDiri.nik,
    data[cariIndex].dataDiri.nama
    });
    table.column(0).format().width(16); // Username
    table.column(1).format().width(5); // Role
    table.column(2).format().width(6); // NIK
    table.column(3).format().width(16); // Nama
    if (!konfirmasi("Yakin ingin hapus?")) {
        cout << "Batal hapus!\n";
        return;
    }

    hapus(data, jumlah, cariIndex);
    if (cariIndex < indexUser) {
        indexUser--;
    }
    cout << "Berhasil dihapus!\n";
}



int main() {
    string menuUtama[] = {"Login", "Register", "Keluar"};
    int pilihan = tampilMenu("Menu Utama", menuUtama, 3);
}