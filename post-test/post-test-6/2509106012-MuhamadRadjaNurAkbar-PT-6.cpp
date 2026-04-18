#include <iostream>
#include <tabulate/table.hpp>
#include <string>
#include <cmath>
#include <algorithm>
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

    string daftarJenis[] {
        "Surat Keterangan Domisili",
        "Surat Keterangan Tidak Mampu",
        "Surat Pengantar KTP",
        "Surat Keterangan Kelahiran"
    };

    string daftarKeperluan[] {
        "Melamar pekerjaan",
        "Keperluan pendidikan",
        "Keperluan pernikahan",
        "Lainnya"
    };

        string daftarStatus[] {
        "menunggu",
        "diproses",
        "selesai",
        "ditolak"
    };


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
        cout << "Tidak valid!\n";
    }
    return pilih;
}

void tampilPenduduk(Penduduk * data, int jumlah) {
    Table table;
    table.add_row({"No", "NIK", "Nama", "Alamat", "No Telp"});
    for (int i=0; i < jumlah; i++) {
        table.add_row({
            to_string(i+1), 
            (data+i)->nik, 
            (data+i)->nama, 
            (data+i)->alamat, 
            (data+i)->noTelp});
    }
    table.column(0).format().width(4); // No
    table.column(1).format().width(6); // NIK
    table.column(2).format().width(16); // Nama
    table.column(3).format().width(16); // Alamat
    table.column(4).format().width(13); // No Telp

    cout << table << "\n";
}

void tampilAkun(User * data, int jumlah) {
    Table table;
    table.add_row({"No", "Username", "Role", "NIK", "Nama"});
    for (int i=0; i < jumlah; i++) {
        table.add_row({
            to_string(i+1), 
            (data+i)->usr, 
            (data+i)->role, 
            (data+i)->dataDiri.nik, 
            (data+i)->dataDiri.nama});
    }
    table.column(0).format().width(4); // No
    table.column(1).format().width(16); // Username
    table.column(2).format().width(5); // Role
    table.column(3).format().width(6); // NIK
    table.column(4).format().width(16); // Nama
    cout << table << "\n";
}

void tampilSurat(Surat * data, int jumlah) {
    Table table;
    table.add_row({"No", "ID Surat", "NIK Pemohon", "Jenis Surat", 
        "Keperluan", "Status", "Keterangan"});
    for (int i=0; i < jumlah; i++) {
        table.add_row({
            to_string(i+1), 
            (data+i)->idSurat, 
            (data+i)->nikPemohon, 
            (data+i)->jenisSurat, 
            (data+i)->keperluan,
            (data+i)->status,
            (data+i)->keterangan});
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

void tampilSuratByNIK(Surat data[], int jumlah, string nik) {
    Table table;
    table.add_row({"No", "ID Surat", "Jenis Surat", "Keperluan", "Status", "Keterangan"});
    int no = 1;
    bool ada = false;
    for (int i = 0; i < jumlah; i++) {
        if (data[i].nikPemohon == nik) {
            table.add_row({
                to_string(no++),
                data[i].idSurat,
                data[i].jenisSurat,
                data[i].keperluan,
                data[i].status,
                data[i].keterangan
            });
            ada = true;
        }
    }
    if (!ada) {
        cout << "Belum ada surat!\n";
        return;
    }
    table.column(0).format().width(4);
    table.column(1).format().width(6);
    table.column(2).format().width(17);
    table.column(3).format().width(11);
    table.column(4).format().width(8);
    table.column(5).format().width(20);
    cout << table << "\n";
}

int linearSearch(void* data, int jumlah, string kunci, int tipe) {
    if (tipe == 1) {
        Penduduk* arr = (Penduduk*)data;
        for (int i=0; i<jumlah; i++) {
            if ((arr+i)->nik == kunci) {
                return i;
            }
        }
    }
    else if (tipe == 2) {
        User* arr = (User*)data;
        for (int i=0; i<jumlah; i++) {
            if((arr+i)->usr == kunci) {
                return i;
            }
        }
    }
    else if (tipe == 3) {
        Surat* arr = (Surat*)data;
        for (int i=0; i<jumlah; i++) {
            if ((arr+i)->idSurat == kunci) {
                return i;
            }
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
        cout << "Tidak boleh kosong!\n";
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

string inputMin(string pesan, int minLen) {
    string hasil;
    while (true) {
        cout << pesan;
        getline(cin, hasil);
        if (hasil == "") {
            cout << "Tidak boleh kosong!\n";
        } else if (hasil.length() < minLen) {
            cout << "Tidak boleh kurang dari " << minLen << " karakter!\n";
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
            cout << "Login berhasil! Selamat datang, " << username << "!\n";
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

    string passwordBaru = inputMin("Password: ", 3);

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
        }
        table.column(0).format().width(4); // No
        table.column(1).format().width(16); //Nama
        table.column(2).format().width(16); // Alamat
        table.column(3).format().width(6); // NIK
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
    totalPenduduk++;
    string nikBaru = "PDK" + string(totalPenduduk < 10 ? "00" : totalPenduduk < 100 ? "0" : "") + to_string(totalPenduduk);
    data[jumlah++] = {nikBaru, namaBaru, alamatBaru, noTelpBaru};
    cout << "Berhasil ditambahkan!\n";
}

void editPenduduk(Penduduk dataPenduduk[], int jumlahPenduduk, User dataUser[], int jumlahUser) {
    string cariNIK;
    cout << "Masukkan NIK dari data penduduk yang ingin diubah: ";
    getline(cin, cariNIK);
    int cariIndex = linearSearch(dataPenduduk, jumlahPenduduk, cariNIK, 1);
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
    cout << table << "\n";
    string opsiUbahPenduduk[] = {"Ubah nama penduduk", "Ubah alamat penduduk", "Ubah no telepon penduduk", "Kembali"};
    int pilihan = tampilMenu("Pilih perubahan\n", opsiUbahPenduduk, 4 );
    cin.ignore();
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
    int cariIndex = linearSearch(dataPenduduk, jumlahPenduduk, cariNIK, 1);
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
    cout << table << "\n";
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
    int cariIndex = linearSearch(data, jumlah, inputUser, 2);
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
    cout << table << "\n";
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

string inputOpsional(string pesan, int maxLen) {
    string hasil;
    while (true) {
        cout << pesan;
        getline(cin, hasil);
        if (hasil.length()>maxLen) {
            cout << "Tidak boleh lebih dari " << maxLen << " karakter!\n";
        } else {
            return hasil;
        }
    }
}

void updateSuratAdmin(Surat data[], int jumlah) {
    string cariID;
    cout << "Masukkan ID surat dari surat yang ingin diubah:";
    getline(cin, cariID);
    int cariIndex = linearSearch(data, jumlah, cariID, 3);
    if (cariIndex == -1) {
        cout << "Surat tidak ditemukan!\n";
        return;
    }
    cout << "Data ditemukan: \n";
    Table table;
    table.add_row({"ID Surat", "NIK Pemohon", "Jenis Surat", 
        "Keperluan", "Status", "Keterangan"});
    table.add_row({
        data[cariIndex].idSurat,
        data[cariIndex].nikPemohon,
        data[cariIndex].jenisSurat,
        data[cariIndex].keperluan,
        data[cariIndex].status,
        data[cariIndex].keterangan
    });
    table.column(0).format().width(6); // ID Surat
    table.column(1).format().width(6); // NIK Pemohon
    table.column(2).format().width(17); // Jenis Surat
    table.column(3).format().width(11); // Keperluan
    table.column(4).format().width(8); // Status
    table.column(5).format().width(20); // Keterangan
    cout << table << "\n";
    string opsiUbahSurat[] = {"Ubah status", "Ubah keterangan", "Kembali"};
    int pilihan = tampilMenu("Pilih perubahan\n", opsiUbahSurat, 3);
    switch(pilihan) {
        case 1: {
            int pilihStatus = tampilMenu("Pilih status\n", daftarStatus, 4); // Tolong dicek lagi
            data[cariIndex].status = daftarStatus[pilihStatus-1];
            cout << "Status berhasil diganti!\n";
            break;
        }
        case 2: {
            cin.ignore();
            string isiKeterangan = inputOpsional("Isi keterangan surat (kosongkan untuk '-'): ", 50);
            if (isiKeterangan == "") {
                data[cariIndex].keterangan = "-";
                cout << "Keterangan dikosongkan\n";
                break;
            }
            data[cariIndex].keterangan = isiKeterangan;
            cout << "Keterangan berhasil diubah!\n";
            break;
        }
        case 3: {
            break;
        }
    }
}

void hapusSuratAdmin(Surat data[], int &jumlah) {
    string cariID;
    cout << "Masukkan ID surat dari surat yang ingin diubah:";
    getline(cin, cariID);
    int cariIndex = linearSearch(data, jumlah, cariID, 3);
    if (cariIndex == -1) {
        cout << "Surat tidak ditemukan!\n";
        return;
    }
    cout << "Data ditemukan: \n";
    Table table;
    table.add_row({"ID Surat", "NIK Pemohon", "Jenis Surat", 
        "Keperluan", "Status", "Keterangan"});
    table.add_row({
        data[cariIndex].idSurat,
        data[cariIndex].nikPemohon,
        data[cariIndex].jenisSurat,
        data[cariIndex].keperluan,
        data[cariIndex].status,
        data[cariIndex].keterangan
    });
    table.column(0).format().width(6); // ID Surat
    table.column(1).format().width(6); // NIK Pemohon
    table.column(2).format().width(17); // Jenis Surat
    table.column(3).format().width(11); // Keperluan
    table.column(4).format().width(8); // Status
    table.column(5).format().width(20); // Keterangan
    cout << table << "\n";
    if(!konfirmasi("Yakin ingin hapus?")) {
        cout << "Batal hapus!\n";
        return;
    }

    hapus(data, jumlah,cariIndex);
    cout << "Berhasil dihapus!\n";
}

void gantiPassword(User data[], int indexUser) {
    string passwordTempo = inputStr("Masukkan password sekarang untuk mengganti password");
    if (data[indexUser].pw == passwordTempo) {
        string passwordGanti = inputMin("Masukkan password baru: ", 3);
        string konfirmasi = inputStr("Konfirmasi password baru: ");
        if (passwordGanti == konfirmasi) {
            data[indexUser].pw = passwordGanti;
            cout << "Password berhasil diubah!\n"; 
            return;
        } else {
            cout << "Password salah!\n";
        }
    } else {
        cout << "Password salah!\n";
    }
}

// Dicek lagi fungsi buatSurat
void buatSurat(Surat dataSurat[], int &jumlahSurat, int &totalSurat, int indexUser, User dataUser[]) {
    int pilihJenis = tampilMenu("Pilih Jenis\n", daftarJenis, 4);
    string jenisBaru = daftarJenis[pilihJenis-1];
    int pilihKeperluan = tampilMenu("Pilih keperluan\n", daftarKeperluan, 4);
    string keperluanBaru = daftarKeperluan[pilihKeperluan-1];
    string nikPemohonBaru = dataUser[indexUser].dataDiri.nik;
    totalSurat++;
    string idBaru = "SRT" + string(totalSurat < 10 ? "00" : totalSurat < 100 ? "0" : "") + to_string(totalSurat);
    dataSurat[jumlahSurat] = {idBaru, nikPemohonBaru, jenisBaru, keperluanBaru, "menunggu", "-"};
    jumlahSurat++;
    cout << "Surat berhasil dibuat!\n";
}

bool statusMenunggu(Surat data[], int index) {
    return data[index].status == "menunggu";
}

void editSuratUser(Surat dataSurat[], int jumlahSurat, int indexUser, User dataUser[]) {
    string cariID;
    cout << "Masukkan ID surat dari surat yang ingin diubah: ";
    getline(cin, cariID);
    int cariIndex = cariSuratUser(dataSurat, jumlahSurat, cariID, dataUser[indexUser].dataDiri.nik);
    if (cariIndex == -1) {
        cout << "Surat tidak ditemukan!\n";
        return;
    }
    if (!statusMenunggu(dataSurat, cariIndex)) {
        cout << "Surat tidak bisa diedit/dihapus!\n";
        return;
    }
    cout << "Data ditemukan: \n";
    Table table;
    table.add_row({"ID Surat", "NIK Pemohon", "Jenis Surat", 
        "Keperluan", "Status", "Keterangan"});
    table.add_row({
        dataSurat[cariIndex].idSurat,
        dataSurat[cariIndex].nikPemohon,
        dataSurat[cariIndex].jenisSurat,
        dataSurat[cariIndex].keperluan,
        dataSurat[cariIndex].status,
        dataSurat[cariIndex].keterangan
    });
    table.column(0).format().width(6); // ID Surat
    table.column(1).format().width(6); // NIK Pemohon
    table.column(2).format().width(17); // Jenis Surat
    table.column(3).format().width(11); // Keperluan
    table.column(4).format().width(8); // Status
    table.column(5).format().width(20); // Keterangan
    cout << table << "\n";
    string opsiUbahSurat[] = {"Jenis surat", "Keperluan surat", "Kembali"};
    int pilihan = tampilMenu("Pilih perubahan\n", opsiUbahSurat, 3);
    switch(pilihan) {
        case 1: {
            int pilihJenis = tampilMenu("Pilih jenis\n", daftarJenis, 4);
            dataSurat[cariIndex].jenisSurat = daftarJenis[pilihJenis-1];
            cout << "Berhasil diubah!\n";
            break;
        }
        case 2: {
            int pilihKeperluan = tampilMenu("Pilih kepeluan", daftarKeperluan, 4);
            dataSurat[cariIndex].keperluan = daftarKeperluan[pilihKeperluan-1];
            cout << "Berhasil diubah!\n";
            break;
        }
        case 3: {
            break;
        }
    }     
}

void hapusSuratUser(Surat dataSurat[], int &jumlahSurat, int indexUser, User dataUser[]) {
    string cariID;
    cout << "Masukkan ID surat dari surat yang ingin diubah: ";
    getline(cin, cariID);
    int cariIndex = cariSuratUser(dataSurat, jumlahSurat, cariID, dataUser[indexUser].dataDiri.nik);
    if (cariIndex == -1) {
        cout << "Surat tidak ditemukan!\n";
        return;
    }
    if (!statusMenunggu(dataSurat, cariIndex)) {
        cout << "Surat tidak bisa diedit/dihapus!\n";
        return;
    }
    cout << "Data ditemukan: \n";
    Table table;
    table.add_row({"ID Surat", "NIK Pemohon", "Jenis Surat", 
        "Keperluan", "Status", "Keterangan"});
    table.add_row({
        dataSurat[cariIndex].idSurat,
        dataSurat[cariIndex].nikPemohon,
        dataSurat[cariIndex].jenisSurat,
        dataSurat[cariIndex].keperluan,
        dataSurat[cariIndex].status,
        dataSurat[cariIndex].keterangan
    });
    table.column(0).format().width(6); // ID Surat
    table.column(1).format().width(6); // NIK Pemohon
    table.column(2).format().width(17); // Jenis Surat
    table.column(3).format().width(11); // Keperluan
    table.column(4).format().width(8); // Status
    table.column(5).format().width(20); // Keterangan
    cout << table << "\n";
    if(!konfirmasi("Yakin ingin hapus?")) {
        cout << "Batal hapus!\n";
        return;
    }

    hapus(dataSurat, jumlahSurat, cariIndex);
    cout << "Berhasil dihapus!\n";
}

void bubbleSortNamaPenduduk(Penduduk* arr, int n) {
    bool swapped;

    for (int i=0; i<n-1; i++) {
        swapped = false;

        for (int j = 0; j < n-i-1; j++) {
            if ((arr+j)->nama < (arr+j+1)->nama) {
                swap(*(arr+j), *(arr+j+1));
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSortIdSurat (Surat* arr, int n) {
    for (int i=0; i<n-1; i++) {
        int indeksMin = i;

        for (int j=i+1; j<n; j++) {
            if ((arr+j)->idSurat < (arr+indeksMin)->idSurat) {
                indeksMin = j;
            }
        }

        if(indeksMin != i) {
            swap(*(arr+i), *(arr+indeksMin));
        }
    }
}

int prioritasStatus(string status) {
    if (status == "menunggu") return 1;
    if (status == "diproses") return 2;
    if (status == "selesai") return 3;
    if (status == "ditolak") return 4;
    return 5;
}

void insertionSortStatusSurat(Surat* arr, int n) {
    for (int i=1; i<n; i++) {
        Surat key = *(arr+i);
        int j = i - 1;

        while (j >= 0 && prioritasStatus((arr+j)->status) > prioritasStatus(key.status)) {
            *(arr+j+1) = *(arr+j);
            j--;
        }
        *(arr+j+1) = key;
    }
}

int jumpSearch(Penduduk* arr, int jumlah, string kunci) {
    int step = sqrt(jumlah);
    int prev = 0;

    while((arr+min(step, jumlah)-1)->nama > kunci) {
        prev = step;
        step += sqrt(jumlah);
        if (prev >= jumlah) {
            cout << "Penduduk tidak ditemukan!\n";
            return -1;
        }
    }
    while((arr+prev)->nama > kunci) {
        prev++;
        if (prev == min(step, jumlah)) {
            cout << "Penduduk tidak ditemukan!\n";
            return -1;
        }
    }
    if ((arr+prev)->nama == kunci) {
        return prev;
    }
    return -1;
}

int main() {
    Penduduk dataPenduduk[100];
    User dataUser[100];
    Surat dataSurat[100];
    int jumlahPenduduk = 7;
    int jumlahUser = 5;
    int jumlahSurat = 10;
    int totalSurat = 10;
    int totalPenduduk = 7;
    int indexUser = -1;

    dataPenduduk[0] = {"PDK004", "siti", "jl. mawar no.12", "08332"};
    dataPenduduk[1] = {"PDK007", "hendra", "jl. dahlia no.9", "08665"};
    dataPenduduk[2] = {"PDK002", "amat", "gg bersama", "08112"};
    dataPenduduk[3] = {"PDK005", "deni", "jl. melati no.3", "08443"};
    dataPenduduk[4] = {"PDK001", "radja", "gg bersatu", "08111"};
    dataPenduduk[5] = {"PDK006", "rina", "jl. kenanga no.7", "08554"};
    dataPenduduk[6] = {"PDK003", "budi", "jl. merdeka no.5", "08221"};

    dataUser[0] = {"s", "014", "user", dataPenduduk[0]};
    dataUser[1] = {"b", "013", "user", dataPenduduk[6]};
    dataUser[2] = {"a", "011", "user", dataPenduduk[2]};
    dataUser[3] = {"ri", "015", "user", dataPenduduk[5]};
    dataUser[4] = {"ra", "012", "admin", dataPenduduk[4]};

    dataSurat[0] = {"SRT005", "PDK003", "Surat Pengantar KTP", "Keperluan pendidikan", "diproses", "Menunggu TTD lurah"};
    dataSurat[1] = {"SRT009", "PDK004", "Surat Pengantar KTP", "Melamar pekerjaan", "diproses", "Menunggu TTD lurah"};
    dataSurat[2] = {"SRT003", "PDK003", "Surat Keterangan Domisili", "Melamar pekerjaan", "selesai", "Sudah diverifikasi"};
    dataSurat[3] = {"SRT007", "PDK002", "Surat Keterangan Kelahiran", "Keperluan pendidikan", "menunggu", "-"};
    dataSurat[4] = {"SRT001", "PDK002", "Surat Keterangan Tidak Mampu", "Keperluan pendidikan", "diproses", "Dalam pengecekkan"};
    dataSurat[5] = {"SRT008", "PDK003", "Surat Keterangan Domisili", "Keperluan pernikahan", "menunggu", "-"};
    dataSurat[6] = {"SRT010", "PDK006", "Surat Keterangan Kelahiran", "Keperluan pendidikan", "menunggu", "-"};
    dataSurat[7] = {"SRT004", "PDK004", "Surat Keterangan Domisili", "Melamar pekerjaan", "menunggu", "-"};
    dataSurat[8] = {"SRT006", "PDK004", "Surat Keterangan Tidak Mampu", "Keperluan pendidikan", "ditolak", "Data tidak sesuai"};
    dataSurat[9] = {"SRT002", "PDK002", "Surat Keterangan Tidak Mampu", "Keperluan usaha", "menunggu", "-"};
    
    while (true) {
        cout << "Selamat datang di Website Balai Kota!\n";
        string opsiAuth[] = {"Login", "Register", "Keluar"};
        int pilihan = tampilMenu("Silahkan login untuk lanjut\n", opsiAuth, 3);
        switch(pilihan) {
            case 1: {
                cin.ignore();
                if (!login(dataUser, jumlahUser, 3, indexUser)) {
                    cout << "Program berhenti!\n";
                    return 0;
                }

                if (dataUser[indexUser].role == "admin") {
                    while (true) {
                        string opsiAdmin[] = {"Data penduduk", "Data akun", "Data surat", "Log-out"};
                        int pilihanAdmin = tampilMenu("Menu Admin", opsiAdmin, 4);
                        switch(pilihanAdmin) {
                            case 1: {
                                while (true) {
                                    string opsiPenduduk[] = {"Lihat", "Tambah", "Edit", "Hapus", 
                                        "Urut Nama Penduduk (Desc)", "Cari Penduduk dari Nama", "Kembali"};
                                    int pilihanPenduduk = tampilMenu("Menu Penduduk", opsiPenduduk, 7);
                                    cin.ignore();
                                    switch(pilihanPenduduk) {
                                        case 1: tampilPenduduk(dataPenduduk, jumlahPenduduk); break;
                                        case 2: tambahPenduduk(dataPenduduk, jumlahPenduduk, totalPenduduk); break;
                                        case 3: editPenduduk(dataPenduduk, jumlahPenduduk, dataUser, jumlahUser); break;
                                        case 4: hapusPendudukAdmin(dataPenduduk, jumlahPenduduk, dataUser, jumlahUser, dataSurat, jumlahSurat, indexUser); break;
                                        case 5: {
                                            cout << "Daftar penduduk berdasarkan urutan nama (descending): " << "\n";
                                            Penduduk temp[100];
                                            for (int i=0; i<jumlahPenduduk; i++) {
                                                temp[i] = dataPenduduk[i];
                                            }
                                            bubbleSortNamaPenduduk(temp,jumlahPenduduk);
                                            tampilPenduduk(temp, jumlahPenduduk);
                                            break;
                                        }
                                        case 6: {
                                            Penduduk temp[100];
                                            for (int i=0; i<jumlahPenduduk; i++) {
                                                temp[i] = dataPenduduk[i];
                                            }
                                            bubbleSortNamaPenduduk(temp, jumlahPenduduk);
                                            cout << "\n=== Data setelah sorting ===\n";
                                            for (int i=0; i<jumlahPenduduk; i++) {
                                                cout << i << ". " << temp[i].nama << "\n";
                                            }
                                            cout << "============================\n\n";
                                            string cariNama;
                                            cout << "Masukkan nama penduduk: ";
                                            getline(cin, cariNama);
                                            int cariIndex = jumpSearch(temp, jumlahPenduduk, cariNama);

                                            if (cariIndex != -1) {
                                                cout << "Ditemukan!\n";
                                                Table table;
                                                table.add_row({"NIK", "Nama", "Alamat", "No Telp"});
                                                table.add_row({
                                                temp[cariIndex].nik,	
                                                temp[cariIndex].nama,
                                                temp[cariIndex].alamat,
                                                temp[cariIndex].noTelp
                                                });
                                                table.column(0).format().width(6); // NIK
                                                table.column(1).format().width(16); // Nama
                                                table.column(2).format().width(16); // Alamat
                                                table.column(3).format().width(13); // No Telp
                                                cout << table << "\n";
                                            } else {
                                                cout << "Tidak ditemukan!\n";
                                            }
                                            break;
                                        }
                                        case 7: break;
                                    }
                                    if (pilihanPenduduk == 7) break;
                                }
                                break;
                            }
                            case 2: {
                                while (true) {
                                    string opsiAkun [] = {"Lihat", "Hapus", "Kembali"};
                                    int pilihanAkun = tampilMenu("Menu Akun", opsiAkun, 3);
                                    cin.ignore();
                                    switch(pilihanAkun) {
                                        case 1: tampilAkun(dataUser, jumlahUser); break;
                                        case 2: hapusAkun(dataUser, jumlahUser, indexUser); break;
                                        case 3: break;
                                    }
                                    if (pilihanAkun == 3) break;
                                }
                                break;
                            }
                            case 3: {
                                while (true) {
                                    string opsiSurat[] = {"Lihat", "Update", "Hapus", "Urut ID Surat (Asc)", 
                                        "Urut Status Surat (Asc)", "Cari Surat","Kembali"};
                                    int pilihanSurat = tampilMenu("Menu Surat", opsiSurat, 7);
                                    cin.ignore();
                                    switch(pilihanSurat) {
                                        case 1: tampilSurat(dataSurat, jumlahSurat); break;
                                        case 2: updateSuratAdmin(dataSurat, jumlahSurat); break;
                                        case 3: hapusSuratAdmin(dataSurat, jumlahSurat); break;
                                        case 4: {
                                            cout << "Daftar surat berdasarkan ID surat (ascending)" << "\n";
                                            Surat temp[100];
                                            for (int i=0; i<jumlahSurat; i++) {
                                                temp[i] = dataSurat[i];
                                            }
                                            selectionSortIdSurat(temp, jumlahSurat);
                                            tampilSurat(temp, jumlahSurat);
                                            break;
                                        }
                                        case 5: {
                                            cout << "Daftar surat berdasarkan prioritas status: " << "\n" 
                                                << "menunggu->diproses->selesai->ditolak" << "\n";
                                            Surat temp[100];
                                            for (int i=0; i<jumlahSurat; i++) {
                                                temp[i] = dataSurat[i];
                                            }
                                            insertionSortStatusSurat(temp, jumlahSurat);
                                            tampilSurat(temp, jumlahSurat);
                                            break;
                                        }
                                        case 6: {
                                            string cariID;
                                            cout << "Masukkan ID surat dari surat yang ingin dicari:";
                                            getline(cin, cariID);
                                            int cariIndex = linearSearch(dataSurat, jumlahSurat, cariID, 3);
                                            if (cariIndex == -1) {
                                                cout << "Surat tidak ditemukan!\n";
                                                break;
                                            }
                                            cout << "Data ditemukan: \n";
                                            Table table;
                                            table.add_row({"ID Surat", "NIK Pemohon", "Jenis Surat", 
                                                "Keperluan", "Status", "Keterangan"});
                                            table.add_row({
                                                dataSurat[cariIndex].idSurat,
                                                dataSurat[cariIndex].nikPemohon,
                                                dataSurat[cariIndex].jenisSurat,
                                                dataSurat[cariIndex].keperluan,
                                                dataSurat[cariIndex].status,
                                                dataSurat[cariIndex].keterangan
                                            });
                                            table.column(0).format().width(6); // ID Surat
                                            table.column(1).format().width(6); // NIK Pemohon
                                            table.column(2).format().width(17); // Jenis Surat
                                            table.column(3).format().width(11); // Keperluan
                                            table.column(4).format().width(8); // Status
                                            table.column(5).format().width(20); // Keterangan
                                            cout << table << "\n";
                                            break;
                                        }
                                        case 7: break;
                                    }
                                    if (pilihanSurat == 7) break;
                                }
                                break;
                            }
                            case 4: {
                                cout << "Log-out berhasil!\n";
                                indexUser = -1;
                                break;
                            }
                        }
                        if (pilihanAdmin == 4) break;
                    }
                } else {
                    while (true) {
                        string opsiUser[] = {"Data Sendiri", "Ganti Password", "Surat Menyurat", "Log-out"};
                        int pilihanUser = tampilMenu("Menu User", opsiUser, 4);
                        switch(pilihanUser) {
                            case 1: {
                                cout << "NIK: " << dataUser[indexUser].dataDiri.nik << "\n";
                                cout << "Nama: " << dataUser[indexUser].dataDiri.nama << "\n";
                                cout << "Alamat: " << dataUser[indexUser].dataDiri.alamat << "\n";
                                cout << "No Telp: " << dataUser[indexUser].dataDiri.noTelp << "\n";
                                break;
                            }
                            case 2: gantiPassword(dataUser, indexUser); break;
                            case 3: {
                                while (true) {
                                    string opsiSuratUser[] = {"Lihat Surat", "Buat Surat", "Edit Surat", "Hapus Surat",
                                        "Urut Status Surat (Ascs)", "Cari surat","Kembali"};
                                    int pilihanSuratUser = tampilMenu("Menu surat", opsiSuratUser, 7);
                                    cin.ignore();
                                    switch(pilihanSuratUser) {
                                        case 1: tampilSuratByNIK(dataSurat, jumlahSurat, dataUser[indexUser].dataDiri.nik); break;
                                        case 2: buatSurat(dataSurat, jumlahSurat, totalSurat, indexUser, dataUser); break;
                                        case 3: editSuratUser(dataSurat, jumlahSurat, indexUser, dataUser); break;
                                        case 4: hapusSuratUser(dataSurat, jumlahSurat, indexUser, dataUser); break;
                                        case 5: {
                                            cout << "Daftar surat berdasarkan prioritas status: " << "\n" 
                                                << "menunggu->diproses->selesai->ditolak" << "\n";
                                            Surat temp[100];
                                            for (int i=0; i<jumlahSurat; i++) {
                                                temp[i] = dataSurat[i];
                                            }
                                            insertionSortStatusSurat(temp, jumlahSurat);
                                            tampilSuratByNIK(temp, jumlahSurat, dataUser[indexUser].dataDiri.nik);
                                            break;
                                        }
                                        case 6: {
                                            string cariID;
                                            cout << "Masukkan ID surat yang ingin dicari: ";
                                            getline(cin, cariID);
                                            int cariIndex = cariSuratUser(dataSurat, jumlahSurat, cariID, dataUser[indexUser].dataDiri.nik);
                                            if (cariIndex == -1) {
                                                cout << "Surat tidak ditemukan!\n";
                                                break;
                                            }
                                            cout << "Data ditemukan: \n";
                                            Table table;
                                            table.add_row({"ID Surat", "NIK Pemohon", "Jenis Surat", 
                                                "Keperluan", "Status", "Keterangan"});
                                            table.add_row({
                                                dataSurat[cariIndex].idSurat,
                                                dataSurat[cariIndex].nikPemohon,
                                                dataSurat[cariIndex].jenisSurat,
                                                dataSurat[cariIndex].keperluan,
                                                dataSurat[cariIndex].status,
                                                dataSurat[cariIndex].keterangan
                                            });
                                            table.column(0).format().width(6); // ID Surat
                                            table.column(1).format().width(6); // NIK Pemohon
                                            table.column(2).format().width(17); // Jenis Surat
                                            table.column(3).format().width(11); // Keperluan
                                            table.column(4).format().width(8); // Status
                                            table.column(5).format().width(20); // Keterangan
                                            cout << table << "\n";
                                            break;
                                        }
                                        case 7: break;
                                    }
                                    if (pilihanSuratUser == 7) break;
                                }
                                break;
                            }
                            case 4: {
                                cout << "Log-out berhasil!\n";
                                indexUser = -1;
                                break;
                            }
                        }
                        if (pilihanUser == 4) break;
                    }
                }
                break;
            }
            case 2: {
                cin.ignore();
                registarsi(dataUser, jumlahUser, dataPenduduk, jumlahPenduduk); break;
            }
            case 3: {
                return 0;
            }
        }
    }
}