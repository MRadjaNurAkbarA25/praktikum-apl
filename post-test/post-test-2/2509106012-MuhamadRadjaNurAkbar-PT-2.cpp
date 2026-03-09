#include <iostream>
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

int main() {
    Penduduk dataPenduduk[100];
    User dataUser[100];
    Surat dataSurat[100];
    int jumlahPenduduk = 2;
    int jumlahUser = 2;
    int jumlahSurat = 2;
    int totalSurat = 2;
    int totalPenduduk = 2;
    int indexUser = -1;
    int pilihan;

    dataPenduduk[0] = {"PDK1", "radja", "gg bersatu", "08111"};
    dataPenduduk[1] = {"PDK2", "amat", "gg bersama", "08112"};

    dataUser[0] = {"r", "012", "admin", dataPenduduk[0]};
    dataUser[1] = {"a", "011", "user", dataPenduduk[1]}; 

    dataSurat[0] = {"SRT1", "PDK2", "Surat Keterangan Tidak Mampu", "Keperluan Pendidikan", "diproses", "Dalam pengecekkan"};
    dataSurat[1] = {"SRT2", "PDK2", "Surat Keterangan Tidak Mampu", "Keperluan usaha", "menunggu", "-"};

    while (true) {
        cout << "Selamat datang di Website Balai Kota!\n\n";
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

                cin.ignore();
                while (kesempatan > 0 && !loginSukses) {
                    cout << "Silahkan login untuk melanjutkan\n";
                    cout << "Username: ";
                    getline(cin, username);
                    cout << "Password: ";
                    getline(cin, password);
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
                if (roleUser == "admin") {
                    while (true) {
                        cout << "\nPilih menu field: \n";
                        cout << "1. Data Penduduk\n";
                        cout << "2. Data akun\n";
                        cout << "3. Data surat\n";
                        cout << "4. Log-out\n";
                        cout << "Pilih: ";
                        if (!(cin >> pilihan)) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "Input tidak valid!\n\n";
                            continue;
                        }
                        switch(pilihan) {
                            case 1 : {
                                while (true) {
                                cout << "\nPilih menu penduduk: \n";
                                cout << "1. Lihat daftar penduduk\n";
                                cout << "2. Tambah penduduk\n";
                                cout << "3. Edit data penduduk\n";
                                cout << "4. Hapus penduduk\n";
                                cout << "5. Kembali\n";
                                cout << "Pilih: ";
                                if (!(cin >> pilihan)) {
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    cout << "Input tidak valid!\n\n";
                                    continue;
                                }
                                switch(pilihan) {
                                    case 1 : {
                                        for (int i = 0; i < jumlahPenduduk; i++) {
                                            cout << i + 1 << ". NIK: " << dataPenduduk[i].nik <<
                                            ", Nama: " << dataPenduduk[i].nama <<
                                            ", Alamat: " << dataPenduduk[i].alamat <<
                                            ", Nomor Telepon: " << dataPenduduk[i].noTelp << "\n";
                                        }
                                        cout << "\nTekan Enter untuk kembali...";
                                        cin.ignore();
                                        cin.get(); 
                                        break;
                                    }
                                    case 2 : {
                                        if (jumlahPenduduk >= 100) {
                                            cout << "Database penuh! tidak bisa tambah penduduk";
                                            break;
                                        }
                                        string namaBaru, alamatBaru, noTelpBaru;
                                        cout << "Masukkan nama: ";
                                        cin.ignore();
                                        getline(cin, namaBaru);
                                        if (namaBaru == "") {
                                            cout << "Tidak boleh kosong!";
                                            break;
                                        }
                                        cout << "Masukkan alamat: ";
                                        getline(cin, alamatBaru);
                                        if (alamatBaru == "") {
                                            cout << "Tidak boleh kosong!";
                                            break;
                                        }
                                        cout << "Masukkan nomor telepon: ";
                                        getline(cin, noTelpBaru);

                                        bool valid = true;
                                        for (int i = 0; i < noTelpBaru.length(); i++) {
                                            if (!isdigit(noTelpBaru[i])) {
                                                valid = false;
                                                break;
                                            }
                                        }
                                        if (!valid) {
                                            cout << "No telepon hanya boleh berisi angka!";
                                            break;
                                        }
                                        bool telpAda = false;
                                        for (int i = 0; i < jumlahPenduduk; i++) {
                                            if (dataPenduduk[i].noTelp == noTelpBaru) {
                                                telpAda = true;
                                                break;
                                            }
                                        }
                                        if (telpAda) {
                                            cout << "Nomor telepon sudah digunakan!\n";
                                            break;
                                        }
                                        string nikBaru = "PDK" + to_string(++totalPenduduk);
                                        dataPenduduk[jumlahPenduduk] = {nikBaru, namaBaru, alamatBaru, noTelpBaru};
                                        jumlahPenduduk++;
                                        cout << "Berhasil ditambahkan!";
                                        break;
                                    }
                                    case 3 : {
                                        cin.ignore();
                                        string cariNIK;
                                        cout << "Masukkan NIK dari data penduduk yang ingin diubah: ";
                                        getline(cin, cariNIK);

                                        int indexCari = -1;
                                        for (int i = 0; i < jumlahPenduduk; i++) {
                                            if (dataPenduduk[i].nik == cariNIK) {
                                                indexCari = i;
                                                break;
                                            }
                                        }
                                        if (indexCari == -1) {
                                            cout << "NIK tidak ditemukan!";
                                            break;
                                        }
                                        cout << "NIK: " << dataPenduduk[indexCari].nik <<
                                            ", " << "Nama: " << dataPenduduk[indexCari].nama << ", " <<
                                            "Alamat: " << dataPenduduk[indexCari].alamat << ", " <<
                                            "Nomor Telepon: " << dataPenduduk[indexCari].noTelp << "\n";
                                        cout << "\nPilih perubahan: \n";
                                        cout << "1. Ubah nama penduduk\n";
                                        cout << "2. Ubah alamat penduduk\n";
                                        cout << "3. Ubah no telepon penduduk\n";
                                        cout << "4. Kembali\n";
                                        cout << "Pilih: ";
                                        if (!(cin >> pilihan)) {
                                            cin.clear();
                                            cin.ignore(100, '\n');
                                            cout << "Input tidak valid!\n\n";
                                            break;
                                        }
                                        switch (pilihan) {
                                            case 1 : {
                                                string namaGanti;
                                                cout << "Nama baru: ";
                                                cin.ignore();
                                                getline(cin, namaGanti);
                                                if (namaGanti == "") {
                                                    cout << "Tidak boleh kosong!";
                                                    break;
                                                }
                                                dataPenduduk[indexCari].nama = namaGanti;
                                                for (int i = 0; i < jumlahUser; i++) {
                                                    if (dataUser[i].dataDiri.nik == dataPenduduk[indexCari].nik) {
                                                        dataUser[i].dataDiri.nama = namaGanti;
                                                        break;
                                                    }
                                                }
                                                cout << "Berhasil diubah!";
                                                break;
                                            }
                                            case 2 : {
                                                string alamatGanti;
                                                cout << "Alamat baru: ";
                                                cin.ignore();
                                                getline(cin, alamatGanti);
                                                if (alamatGanti == "") {
                                                    cout << "Tidak boleh kosong!";
                                                    break;
                                                }
                                                dataPenduduk[indexCari].alamat = alamatGanti;
                                                for (int i = 0; i < jumlahUser; i++) {
                                                    if (dataUser[i].dataDiri.nik == dataPenduduk[indexCari].nik) {
                                                        dataUser[i].dataDiri.alamat = alamatGanti;
                                                        break;
                                                    }
                                                }
                                                cout << "Berhasil diubah!";
                                                break;
                                            }
                                            case 3 : {
                                                string telpGanti;
                                                cout << "No telepon baru: ";
                                                cin.ignore();
                                                getline(cin, telpGanti);

                                                bool valid = true;
                                                for (int i = 0; i < telpGanti.length(); i++) {
                                                    if (!isdigit(telpGanti[i])) {
                                                        valid = false;
                                                        break;
                                                    }
                                                }
                                                if (!valid) {
                                                    cout << "No telepon hanya boleh berisi angka!";
                                                    break;
                                                }

                                                bool telpAda = false;
                                                for (int i = 0; i < jumlahPenduduk; i++) {
                                                    if (dataPenduduk[i].noTelp == telpGanti) {
                                                        telpAda = true;
                                                        break;
                                                    }
                                                }
                                                if (telpAda) {
                                                    cout << "Nomor telepon sudah digunakan!\n";
                                                    break;
                                                }
                                                dataPenduduk[indexCari].noTelp = telpGanti;
                                                for (int i = 0; i < jumlahUser; i++) {
                                                    if (dataUser[i].dataDiri.nik == dataPenduduk[indexCari].nik) {
                                                        dataUser[i].dataDiri.noTelp = telpGanti;
                                                        break;
                                                    }
                                                }
                                                cout << "Berhasil diubah!";
                                                break;
                                            }
                                            case 4 : {
                                                break;
                                            }
                                            default : {
                                                cout << "Pilihan tidak valid!\n\n";
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    case 4 : {
                                        cin.ignore();
                                        string cariNIK;
                                        cout << "Masukkan NIK dari data penduduk yang ingin dihapus: ";
                                        getline(cin, cariNIK);

                                        int indexCari = -1;
                                        for (int i = 0; i < jumlahPenduduk; i++) {
                                            if (dataPenduduk[i].nik == cariNIK) {
                                                indexCari = i;
                                                break;
                                            }
                                        }
                                        if (indexCari == -1) {
                                            cout << "NIK tidak ditemukan!";
                                            break;
                                        }

                                        bool adaAdmin = false;
                                        for (int i = 0; i < jumlahUser; i++) {
                                            if (dataUser[i].dataDiri.nik == dataPenduduk[indexCari].nik &&
                                            dataUser[i].role == "admin") {
                                                adaAdmin = true;
                                                break;
                                            }
                                        }
                                        if (adaAdmin) {
                                            cout << "Tidak bisa hapus penduduk dengan akun admin!\n";
                                            break;
                                        }
                                        cout << "NIK: " << dataPenduduk[indexCari].nik <<
                                            ", " << "Nama: " << dataPenduduk[indexCari].nama << ", " <<
                                            "Alamat: " << dataPenduduk[indexCari].alamat << ", " <<
                                            "Nomor Telepon: " << dataPenduduk[indexCari].noTelp << "\n";
                                        cout << "Konfirmasi hapus? (y/n): ";
                                        char konfirmasi;
                                        cin >> konfirmasi;

                                        if (konfirmasi != 'y') {
                                            cout << "Batal dihapus!";
                                            break;
                                        }

                                        string nikHapus = dataPenduduk[indexCari].nik;
                                        for (int i = indexCari; i < jumlahPenduduk - 1; i++) {
                                            dataPenduduk[i] = dataPenduduk[i+1];
                                        }
                                        jumlahPenduduk--;

                                        for (int i = 0; i < jumlahUser; i++) {
                                            if (dataUser[i].dataDiri.nik == nikHapus) {
                                                for (int j = i; j < jumlahUser - 1; j++) {
                                                    dataUser[j] = dataUser[j+1];
                                                }
                                                jumlahUser--;
                                                break;
                                            }
                                        }
                                        for (int i = 0; i < jumlahSurat; i++) {
                                            if (dataSurat[i].nikPemohon == nikHapus) {
                                                for (int j = i; j < jumlahSurat - 1; j++) {
                                                    dataSurat[j] = dataSurat[j+1];
                                                }
                                                jumlahSurat--;
                                                i--;
                                            }
                                        }
                                        cout << "Berhasil dihapus!";
                                        break;
                                    }
                                    case 5 : {
                                        break;
                                    }
                                    default : {
                                        cout << "Pilihan tidak valid!\n";
                                        break;
                                    }
                                } 
                                if (pilihan == 5) break; 
                                } 
                                break;
                            } 
                            case 2 : {
                                while (true) {
                                    cout << "\nPilih menu akun: \n";
                                    cout << "1. Lihat daftar akun\n";
                                    cout << "2. Hapus akun\n";
                                    cout << "3. Kembali\n";
                                    cout << "Pilih: ";
                                    if (!(cin >> pilihan)) {
                                        cin.clear();
                                        cin.ignore(100, '\n');
                                        cout << "Input tidak valid!\n\n";
                                        continue;
                                    }
                                    switch(pilihan) {
                                        case 1 : {
                                            for (int i = 0; i < jumlahUser; i++) {
                                                cout << i + 1 << ". " << "Username: " << dataUser[i].usr << ", " <<
                                                "Role: " << dataUser[i].role << ", " << "NIK: " << dataUser[i].dataDiri.nik <<
                                                ", " << "Nama: " << dataUser[i].dataDiri.nama << "\n";
                                            }
                                            break;
                                        }
                                        case 2 : {
                                            cin.ignore();
                                            string cariUser;
                                            cout << "Masukkan username dari akun yang ingin dihapus: ";
                                            getline(cin, cariUser);

                                            int indexCari = -1;
                                            for (int i = 0; i < jumlahUser; i++) {
                                                if (dataUser[i].usr == cariUser) {
                                                    indexCari = i;
                                                    break;
                                                }
                                            }
                                            if (indexCari == -1) {
                                                cout << "Username tidak ditemukan!";
                                                break;
                                            }

                                            if (indexCari == indexUser) {
                                            cout << "Tidak bisa menghapus akun yang sedang login!\n";
                                            break;
                                            }
                                            cout << "Username: " << dataUser[indexCari].usr
                                                << ", Role: " << dataUser[indexCari].role
                                                << ", NIK: " << dataUser[indexCari].dataDiri.nik
                                                << ", Nama: " << dataUser[indexCari].dataDiri.nama;
                                            
                                            cout << "Konfirmasi hapus? (y/n): ";
                                            char konfirmasi;
                                            cin >> konfirmasi;
                                            if (konfirmasi != 'y') {
                                                cout << "Batal dihapus!\n";
                                                break;
                                            }

                                            for (int i = indexCari; i < jumlahUser - 1; i++) {
                                                dataUser[i] = dataUser[i + 1];
                                            }
                                            jumlahUser--;
                                            if (indexCari < indexUser) {
                                                indexUser--;
                                            }
                                            cout << "Berhasil dihapus!\n";
                                            break;
                                        }
                                        case 3 : {
                                            break;
                                        }
                                        default : {
                                            cout << "Pilihan tidak valid!\n";
                                            break;
                                        }
                                    }
                                    if (pilihan == 3) break;
                                }
                                break;
                            }
                            case 3 : {
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

                                while (true) {
                                    cout << "Pilih menu surat: \n";
                                    cout << "1. Lihat daftar surat\n";
                                    cout << "2. Update surat\n";
                                    cout << "3. Hapus surat\n";
                                    cout << "4. Kembali \n";
                                    cout << "Pilih: ";
                                    if (!(cin >> pilihan)) {
                                        cin.clear();
                                        cin.ignore(100, '\n');
                                        cout << "Input tidak valid!\n\n";
                                        continue;
                                    }

                                    switch (pilihan) {
                                        case 1 : {
                                            if (jumlahSurat == 0) {
                                                cout << "Belum ada surat!\n";
                                                break;
                                            }

                                            for (int i = 0; i < jumlahSurat; i++) {
                                                cout << i + 1 << ". ID surat: " << dataSurat[i].idSurat
                                                << ", NIK Pemohon: " << dataSurat[i].nikPemohon
                                                << ", Jenis Surat: " << dataSurat[i].jenisSurat
                                                << ", Keperluan: " << dataSurat[i].keperluan
                                                << ", Status: " << dataSurat[i].status
                                                << ", Keterangan: " << dataSurat[i].keterangan << "\n";
                                            }
                                            break;
                                        }
                                        case 2 : {
                                            cin.ignore();
                                            string cariID;
                                            cout << "Masukkan ID dari surat yang ingin diupdate: ";
                                            getline(cin, cariID);

                                            int indexCari = -1;
                                            for (int i = 0; i < jumlahSurat; i++) {
                                                if (dataSurat[i].idSurat == cariID) {
                                                    indexCari = i;
                                                    break;
                                                }
                                            }
                                            if (indexCari == -1) {
                                                cout << "ID surat tidak ditemukan!\n";
                                                break;
                                            }
                                            cout << "ID surat: " << dataSurat[indexCari].idSurat
                                                << ", NIK Pemohon: " << dataSurat[indexCari].nikPemohon
                                                << ", Jenis Surat: " << dataSurat[indexCari].jenisSurat
                                                << ", Keperluan: " << dataSurat[indexCari].keperluan
                                                << ", Status: " << dataSurat[indexCari].status
                                                << ", Keterangan: " << dataSurat[indexCari].keterangan << "\n";
                                            
                                            cout << "\nPilih perubahan: \n";
                                            cout << "1. Ubah status\n";
                                            cout << "2. Ubah keterangan\n";
                                            cout << "3. Kembali\n";
                                            cout << "Pilih: ";
                                            if (!(cin >> pilihan)) {
                                                cin.clear();
                                                cin.ignore(100, '\n');
                                                cout << "Input tidak valid!\n\n";
                                                break;
                                            }

                                            switch(pilihan) {
                                                case 1: {
                                                    int pilihStatus;
                                                    cout << "Pilih status: \n";
                                                    for (int i = 0; i < 4; i++) {
                                                        cout << i + 1 << ". " << daftarStatus[i] << "\n";
                                                    }
                                                    cout << "Pilih: ";
                                                    cin >> pilihStatus;
                                                    if (pilihStatus < 1 || pilihStatus > 4) {
                                                        cout << "Pilihan tidak valid!\n";
                                                        break;
                                                    }
                                                    dataSurat[indexCari].status = daftarStatus[pilihStatus-1];
                                                    cout << "Status berhasil diubah!\n";
                                                    break;
                                                }
                                                case 2: {
                                                    cin.ignore();
                                                    string isiKtrgn;
                                                    cout << "Isi keterangan surat: ";
                                                    getline(cin, isiKtrgn);
                                                    if (isiKtrgn == "") {
                                                        dataSurat[indexCari].keterangan = "-";
                                                        cout << "Keterangan dikosongkan!\n";
                                                        break;
                                                    }
                                                    if (isiKtrgn.length() > 50) {
                                                        cout << "Tidak boleh lebih dari 50 karakter!\n";
                                                        break;
                                                    }
                                                    dataSurat[indexCari].keterangan = isiKtrgn;
                                                    cout << "Keterangan berhasil diubah!\n";
                                                    break;
                                                }
                                                case 3: {
                                                    break;
                                                }
                                                default: {
                                                    cout << "Pilihan tidak valid!\n";
                                                    break;
                                                }
                                            } 
                                            break; 
                                        } 
                                        case 3 : {
                                            cin.ignore();
                                            string cariID;
                                            cout << "Masukkan ID dari surat yang ingin dihapus: ";
                                            getline(cin, cariID);

                                            int indexCari = -1;
                                            for (int i = 0; i < jumlahSurat; i++) {
                                                if (dataSurat[i].idSurat == cariID) {
                                                    indexCari = i;
                                                    break;
                                                }
                                            }
                                            if (indexCari == -1) {
                                                cout << "ID surat tidak ditemukan!\n";
                                                break;
                                            }
                                            cout << "ID surat: " << dataSurat[indexCari].idSurat
                                                << ", Jenis: " << dataSurat[indexCari].jenisSurat
                                                << ", Status: " << dataSurat[indexCari].status << "\n";
                                            cout << "Konfirmasi hapus? (y/n): ";
                                            char konfirmasi;
                                            cin >> konfirmasi;
                                            if (konfirmasi != 'y') {
                                                cout << "Batal dihapus!\n";
                                                break;
                                            }
                                            for (int i = indexCari; i < jumlahSurat - 1; i++) {
                                                dataSurat[i] = dataSurat[i+1];
                                            }
                                            jumlahSurat--;
                                            cout << "Berhasil dihapus!\n";
                                            break;
                                        }
                                        case 4 : {
                                            break;
                                        }
                                        default : {
                                            cout << "Pilihan tidak valid!\n";
                                            break;
                                        }
                                    } 
                                    if (pilihan == 4) break; 
                                } 
                                pilihan = 0;
                                break; 
                            } 
                                
                            case 4 : {
                                cout << "Logout berhasil!\n";
                                indexUser = -1;
                                break;
                            }
                            default : {
                                cout << "Pilihan tidak valid!\n";
                                break;
                            }
                        } 
                        if (pilihan == 4) break; 
                    } 
                } else {
                    while (true) {
                        cout << "\nPilih menu: \n";
                        cout << "1. Data sendiri\n";
                        cout << "2. Ganti password\n";
                        cout << "3. Surat menyurat\n";
                        cout << "4. Log-out\n";
                        cout << "Pilih: ";
                        if (!(cin >> pilihan)) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "Input tidak valid!\n\n";
                            continue;
                        }
                        switch (pilihan) {
                            case 1: {
                                cout << "Data diri kamu\n";
                                cout << "NIK: " << dataUser[indexUser].dataDiri.nik << "\n";
                                cout << "Nama: " << dataUser[indexUser].dataDiri.nama << "\n";
                                cout << "Alamat: " << dataUser[indexUser].dataDiri.alamat << "\n";
                                cout << "Nomor Telepon: " << dataUser[indexUser].dataDiri.noTelp << "\n";
                                break;
                            }
                            case 2: {
                                string passwordTempo, gantiPassword, konfirmasi;
                                cout << "Masukkan password sekarang untuk mengganti password: \n";
                                cin.ignore();
                                getline(cin, passwordTempo);
                                if (passwordTempo == "") {
                                    cout << "Tidak boleh kosong!\n";
                                    break;
                                }
                                if (dataUser[indexUser].pw == passwordTempo) {
                                    cout << "Masukkan password baru: ";
                                    getline(cin, gantiPassword);
                                    if (gantiPassword.length() < 3) {
                                        cout << "Panjang password minimal 3 karakter!\n";
                                        break;
                                    }
                                    cout << "Konfirmasi password baru: ";
                                    getline(cin, konfirmasi);
                                    if (gantiPassword == konfirmasi) {
                                        dataUser[indexUser].pw = gantiPassword;
                                        cout << "Password berhasil diubah!\n"; 
                                        break;
                                    } else {
                                        cout << "Password salah!\n";
                                        break;
                                    }
                                } else {
                                    cout << "Password salah!\n";
                                    break;
                                }
                            }
                            case 3: {
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

                                while (true) {
                                cout << "Pilih menu surat: \n";
                                cout << "1. Liat surat sendiri\n";
                                cout << "2. Buat surat\n";
                                cout << "3. Edit surat\n";
                                cout << "4. Hapus surat\n";
                                cout << "5. Kembali\n";
                                cout << "Pilih: ";
                                if (!(cin >> pilihan)) {
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    cout << "Input tidak valid!\n\n";
                                    continue;
                                }
                                switch(pilihan) {
                                    case 1: {
                                        bool adaSurat = false;
                                        for (int i = 0; i < jumlahSurat; i++) {
                                            if (dataSurat[i].nikPemohon == dataUser[indexUser].dataDiri.nik) {
                                                if (!adaSurat) {
                                                    cout << "Daftar surat: \n";
                                                    adaSurat = true;
                                                }
                                                cout << i + 1 << ". ID: " << dataSurat[i].idSurat
                                                << ", Jenis: " << dataSurat[i].jenisSurat
                                                << ", Keperluan: " << dataSurat[i].keperluan
                                                << ", Status: " << dataSurat[i].status
                                                << ", Keterangan: " << dataSurat[i].keterangan << "\n";
                                            }
                                        }
                                        if (!adaSurat) {
                                            cout << "Kamu belum punya surat!";
                                        }
                                        break;
                                    }
                                    case 2: {
                                        if (jumlahSurat >= 100) {
                                            cout << "Database penuh! Tidak bisa tambah surat!\n";
                                            break;
                                        }
                                        cout << "Buat surat: ";
                                        int pilihJenis, pilihKeperluan;
                                        string jenisBaru, keperluanBaru;
                                        cout << "Pilih jenis: \n";
                                        for (int i = 0; i < 4; i++) {
                                            cout << i + 1 << ". " << daftarJenis[i] << "\n";
                                        }
                                        cout << "Pilih: ";
                                        cin >> pilihJenis;
                                        if (pilihJenis < 1 || pilihJenis > 4) {
                                            cout << "Pilihan tidak valid!\n";
                                            break;
                                        }
                                        jenisBaru = daftarJenis[pilihJenis-1];

                                        cout << "Pilih keperluan: \n";
                                        for (int i = 0; i < 4; i++) {
                                            cout << i + 1 << ". " << daftarKeperluan[i] << "\n";
                                        }
                                        cout << "Pilih: ";
                                        cin >> pilihKeperluan;
                                        if (pilihKeperluan < 1 || pilihKeperluan > 4) {
                                            cout << "Pilihan tidak valid!\n";
                                            break;
                                        }
                                        keperluanBaru = daftarKeperluan[pilihKeperluan-1];
                                        string nikPemohonSementara = dataUser[indexUser].dataDiri.nik;
                                        string idBaru = "SRT" + to_string(++totalSurat);
                                        dataSurat[jumlahSurat] = {idBaru, nikPemohonSementara, jenisBaru, keperluanBaru, "menunggu", "-"};
                                        jumlahSurat++;
                                        cout << "Surat berhasil ditambahkan!\n";
                                        break;
                                    }
                                    case 3: {
                                        string cariID;
                                        cout << "Masukkan ID surat yang ingin diubah: \n";
                                        cin.ignore();
                                        getline(cin, cariID);

                                        int indexCari = -1;
                                        for (int i = 0; i < jumlahSurat; i++) {
                                            if (dataSurat[i].idSurat == cariID && 
                                            dataSurat[i].nikPemohon == dataUser[indexUser].dataDiri.nik) {
                                                indexCari = i;
                                                break;
                                            }
                                        }
                                        if (indexCari == -1) {
                                            cout << "Surat tidak ditemukan!\n";
                                            break;
                                        }
                                        if (dataSurat[indexCari].status != "menunggu") {
                                            cout << "Surat tidak bisa diedit!";
                                            break;
                                        }

                                        cout << "Pilih perubahan: \n";
                                        cout << "1. Jenis surat\n";
                                        cout << "2. Keperluan surat\n";
                                        cout << "3. Kembali\n";
                                        cout << "Pilih: ";
                                        if (!(cin >> pilihan)) {
                                            cin.clear();
                                            cin.ignore(100, '\n');
                                            cout << "Input tidak valid!\n\n";
                                            break;
                                        }
                                        switch(pilihan) {
                                            case 1: {
                                                int gantiJenis;
                                                cout << "Pilih jenis: \n";
                                                for (int i = 0; i < 4; i++) {
                                                    cout << i + 1 << ". " << daftarJenis[i] << "\n";
                                                }
                                                cout << "Pilih: ";
                                                cin >> gantiJenis;
                                                if (gantiJenis < 1 || gantiJenis > 4) {
                                                    cout << "Pilihan tidak valid!\n";
                                                    break;
                                                }
                                                dataSurat[indexCari].jenisSurat = daftarJenis[gantiJenis-1];
                                                cout << "Jenis surat berhasil diubah!\n";
                                                break;
                                            }
                                            case 2: {
                                                int gantiKeperluan;
                                                cout << "Pilih keperluan: \n";
                                                for (int i = 0; i < 4; i++) {
                                                    cout << i + 1 << ". " << daftarKeperluan[i] << "\n";
                                                }
                                                cout << "Pilih: ";
                                                cin >> gantiKeperluan;
                                                if (gantiKeperluan < 1 || gantiKeperluan > 4) {
                                                    cout << "Pilihan tidak valid!\n";
                                                    break;
                                                }
                                                dataSurat[indexCari].keperluan = daftarKeperluan[gantiKeperluan-1];
                                                cout << "Keperluan surat berhasil diubah!\n";
                                                break;
                                            }
                                            case 3: {
                                                break;
                                            }
                                            default: {
                                                cout << "Pilihan tidak valid!\n";
                                                break;
                                            }
                                        } 
                                        break; 
                                    }
                                    case 4: {
                                        string cariID;
                                        cout << "Masukkan ID surat yang ingin dihapus: \n";
                                        cin.ignore();
                                        getline(cin, cariID);

                                        int indexCari = -1;
                                        for (int i = 0; i < jumlahSurat; i++) {
                                            if (dataSurat[i].idSurat == cariID && 
                                            dataSurat[i].nikPemohon == dataUser[indexUser].dataDiri.nik) {
                                                indexCari = i;
                                                break;
                                            }
                                        }
                                        if (indexCari == -1) {
                                            cout << "Surat tidak ditemukan!\n";
                                            break;
                                        }
                                        if (dataSurat[indexCari].status != "menunggu") {
                                            cout << "Surat tidak bisa dihapus!\n";
                                            break;
                                        }
                                        cout << "Yakin ingin hapus surat? (y/n): ";
                                        char konfirmasi;
                                        cin >> konfirmasi;
                                        if (konfirmasi != 'y') {
                                            cout << "Batal dihapus!";
                                            break;
                                        }
                                        for (int i = indexCari; i < jumlahSurat - 1; i++) {
                                            dataSurat[i] = dataSurat[i+1];
                                        }
                                        jumlahSurat--;
                                        cout << "Surat berhasil dihapus!\n";
                                        break;
                                    }
                                    case 5: {
                                        break;
                                    }
                                    default: {
                                        cout << "Pilihan tidak valid!\n";
                                        break;
                                    }
                                } 
                                if (pilihan == 5) break;
                                } 
                                pilihan = 0;
                                break; 
                            } 
                            case 4: {
                                cout << "Logout berhasil!\n";
                                indexUser = -1;
                                break;
                            }
                            default: {
                                cout << "Pilihan tidak valid!\n";
                                break;
                            }
                        } 
                        if (pilihan == 4) break; 
                    } 
                } 
                break;
            } 
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
                    cout << "Tidak boleh kosong!\n";
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
                        cout << i + 1 << ". " << dataPenduduk[hasilCari[i]].nama << 
                        " - " << dataPenduduk[hasilCari[i]].nik << "\n";
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

        } 

    } 
} 