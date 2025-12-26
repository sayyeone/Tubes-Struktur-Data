#include "../include/dosen.h"
#include "../include/mahasiswa.h"
#include "../include/relasi.h"


void pause() {
    cout << endl << "Tekan ENTER untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void menuTambahDosen(List_dosen &LD) {
    string nama, nip, keahlian;
    
    cout << endl << "=== TAMBAH DATA DOSEN ===" << endl;
    cin.ignore();
    cout << "Nama Dosen: ";
    getline(cin, nama);
    cout << "NIP: ";
    getline(cin, nip);
    cout << "Keahlian: ";
    getline(cin, keahlian);
    
    address_dosen P = alokasi_dosen(nama, nip, keahlian);
    insertLast(LD, P);
    
    cout << endl << ">>> Data dosen berhasil ditambahkan! <<<" << endl;
}

void menuTambahMahasiswa(List_mahasiswa &LM) {
    string nama, nim, judul_ta;
    
    cout << endl << "=== TAMBAH DATA MAHASISWA ===" << endl;
    cin.ignore();
    cout << "Nama Mahasiswa: ";
    getline(cin, nama);
    cout << "NIM: ";
    getline(cin, nim);
    cout << "Judul Tugas Akhir: ";
    getline(cin, judul_ta);
    
    address_mahasiswa P = alokasi_mahasiswa(nama, nim, judul_ta);
    insertFirst(LM, P);
    
    cout << endl << ">>> Data mahasiswa berhasil ditambahkan! <<<" << endl;
}

void menuHubungkanRelasi(List_dosen LD, List_mahasiswa LM, address_relasi &firstRel) {
    string nip, nim;
    
    cout << endl << "=== HUBUNGKAN DOSEN DAN MAHASISWA ===" << endl;
    cin.ignore();
    cout << "Masukkan NIP Dosen: ";
    getline(cin, nip);
    cout << "Masukkan NIM Mahasiswa: ";
    getline(cin, nim);
    
    address_dosen D = findElmDosenByNIP(LD, nip);
    address_mahasiswa M = findElmMahasiswaByNIM(LM, nim);
    
    if(D == NULL) {
        cout << endl << ">>> Dosen dengan NIP tersebut tidak ditemukan! <<<" << endl;
        return;
    }
    
    if(M == NULL) {
        cout << endl << ">>> Mahasiswa dengan NIM tersebut tidak ditemukan! <<<" << endl;
        return;
    }
    
    int jumlahPembimbing = countDosenPembimbing(M, firstRel);
    if(jumlahPembimbing >= 2) {
        cout << endl << ">>> Mahasiswa sudah memiliki 2 dosen pembimbing! <<<" << endl;
        return;
    }
    
    address_relasi cek = findRelasiDosenMahasiswa(D, M, firstRel);
    if(cek != NULL) {
        cout << endl << ">>> Relasi sudah ada! <<<" << endl;
        return;
    }
    
    connect(D, M, firstRel);
    cout << endl << ">>> Relasi berhasil dibuat! <<<" << endl;
}

void menuHapusDosen(List_dosen &LD, address_relasi &firstRel) {
    string nip;
    
    cout << endl << "=== HAPUS DATA DOSEN ===" << endl;
    cin.ignore();
    cout << "Masukkan NIP Dosen yang akan dihapus: ";
    getline(cin, nip);
    
    address_dosen D = findElmDosenByNIP(LD, nip);
    
    if(D == NULL) {
        cout << endl << ">>> Dosen dengan NIP tersebut tidak ditemukan! <<<" << endl;
        return;
    }
    
    deleteAllRelasiDosen(D, firstRel);
    
    address_dosen P = first(LD);
    if(P == D) {
        deleteFirst(LD, P);
    } else {
        address_dosen Prec = first(LD);
        while(next(Prec) != D) {
            Prec = next(Prec);
        }
        deleteAfter(LD, Prec, P);
    }
    
    dealokasi_dosen(P);
    cout << endl << ">>> Data dosen dan relasinya berhasil dihapus! <<<" << endl;
}

void menuHapusMahasiswa(List_mahasiswa &LM, address_relasi &firstRel) {
    string nim;
    
    cout << endl << "=== HAPUS DATA MAHASISWA ===" << endl;
    cin.ignore();
    cout << "Masukkan NIM Mahasiswa yang akan dihapus: ";
    getline(cin, nim);
    
    address_mahasiswa M = findElmMahasiswaByNIM(LM, nim);
    
    if(M == NULL) {
        cout << endl << ">>> Mahasiswa dengan NIM tersebut tidak ditemukan! <<<" << endl;
        return;
    }
    
    deleteAllRelasiMahasiswa(M, firstRel);
    
    address_mahasiswa P = first(LM);
    if(P == M) {
        deleteFirst(LM, P);
    } else {
        address_mahasiswa Prec = first(LM);
        while(next(Prec) != M) {
            Prec = next(Prec);
        }
        deleteAfter(Prec, P);
    }
    
    dealokasi_mahasiswa(P);
    cout << endl << ">>> Data mahasiswa dan relasinya berhasil dihapus! <<<" << endl;
}

void menuCariDosen(List_dosen LD) {
    string nama;
    
    cout << endl << "=== CARI DATA DOSEN ===" << endl;
    cin.ignore();
    cout << "Masukkan nama dosen: ";
    getline(cin, nama);
    
    address_dosen D = findElmDosen(LD, nama);
    
    if(D == NULL) {
        cout << endl << ">>> Dosen tidak ditemukan! <<<" << endl;
    } else {
        cout << endl << ">>> Data ditemukan! <<<" << endl;
        cout << "Nama: " << info(D).nama << endl;
        cout << "NIP: " << info(D).nip << endl;
        cout << "Keahlian: " << info(D).keahlian << endl;
    }
}

void menuCariMahasiswa(List_mahasiswa LM) {
    string nama;
    
    cout << endl << "=== CARI DATA MAHASISWA ===" << endl;
    cin.ignore();
    cout << "Masukkan nama mahasiswa: ";
    getline(cin, nama);
    
    address_mahasiswa M = findElmMahasiswa(LM, nama);
    
    if(M == NULL) {
        cout << endl << ">>> Mahasiswa tidak ditemukan! <<<" << endl;
    } else {
        cout << endl << ">>> Data ditemukan! <<<" << endl;
        cout << "Nama: " << info(M).nama << endl;
        cout << "NIM: " << info(M).nim << endl;
        cout << "Judul TA: " << info(M).judul_ta << endl;
    }
}

void menuTampilMahasiswaByDosen(List_dosen LD, address_relasi firstRel) {
    string nip;
    
    cout << endl << "=== TAMPIL MAHASISWA BY DOSEN ===" << endl;
    cin.ignore();
    cout << "Masukkan NIP Dosen: ";
    getline(cin, nip);
    
    address_dosen D = findElmDosenByNIP(LD, nip);
    
    if(D == NULL) {
        cout << endl << ">>> Dosen dengan NIP tersebut tidak ditemukan! <<<" << endl;
        return;
    }
    
    showAllMahasiswaByDosen(D, firstRel);
}

void menuTampilDosenByMahasiswa(List_mahasiswa LM, address_relasi firstRel) {
    string nim;
    
    cout << endl << "=== TAMPIL DOSEN BY MAHASISWA ===" << endl;
    cin.ignore();
    cout << "Masukkan NIM Mahasiswa: ";
    getline(cin, nim);
    
    address_mahasiswa M = findElmMahasiswaByNIM(LM, nim);
    
    if(M == NULL) {
        cout << endl << ">>> Mahasiswa dengan NIM tersebut tidak ditemukan! <<<" << endl;
        return;
    }
    
    showAllDosenByMahasiswa(M, firstRel);
}

void menuHapusRelasiTertentu(List_dosen LD, List_mahasiswa LM, address_relasi &firstRel) {
    string nip, nim;
    
    cout << endl << "=== HAPUS RELASI TERTENTU ===" << endl;
    cin.ignore();
    cout << "Masukkan NIP Dosen: ";
    getline(cin, nip);
    cout << "Masukkan NIM Mahasiswa: ";
    getline(cin, nim);
    
    address_dosen D = findElmDosenByNIP(LD, nip);
    address_mahasiswa M = findElmMahasiswaByNIM(LM, nim);
    
    if(D == NULL) {
        cout << endl << ">>> Dosen dengan NIP tersebut tidak ditemukan! <<<" << endl;
        return;
    }
    
    if(M == NULL) {
        cout << endl << ">>> Mahasiswa dengan NIM tersebut tidak ditemukan! <<<" << endl;
        return;
    }
    
    disconnect(D, M, firstRel);
    cout << endl << ">>> Relasi berhasil dihapus! <<<" << endl;
}

void manualMode(List_dosen &LD, List_mahasiswa &LM, address_relasi &firstRel) {
    int pilihan;
    
    do {
        cout << "1.  Tambah Data Dosen" << endl;
        cout << "2.  Tambah Data Mahasiswa" << endl;
        cout << "3.  Hubungkan Dosen dan Mahasiswa" << endl;
        cout << "4.  Hapus Data Dosen" << endl;
        cout << "5.  Hapus Data Mahasiswa" << endl;
        cout << "6.  Hapus Relasi Tertentu" << endl;
        cout << "7.  Tampilkan Semua Dosen" << endl;
        cout << "8.  Tampilkan Semua Mahasiswa" << endl;
        cout << "9.  Tampilkan Semua Data (Mhs + Dosen)" << endl;
        cout << "10. Cari Data Dosen" << endl;
        cout << "11. Cari Data Mahasiswa" << endl;
        cout << "12. Tampil Mahasiswa by Dosen" << endl;
        cout << "13. Tampil Dosen by Mahasiswa" << endl;
        cout << "14. Statistik Bimbingan Dosen" << endl;
        cout << "0.  Kembali ke Menu Utama" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                menuTambahDosen(LD);
                pause();
                break;
            case 2:
                menuTambahMahasiswa(LM);
                pause();
                break;
            case 3:
                menuHubungkanRelasi(LD, LM, firstRel);
                pause();
                break;
            case 4:
                menuHapusDosen(LD, firstRel);
                pause();
                break;
            case 5:
                menuHapusMahasiswa(LM, firstRel);
                pause();
                break;
            case 6:
                menuHapusRelasiTertentu(LD, LM, firstRel);
                pause();
                break;
            case 7:
                printInfo(LD);
                pause();
                break;
            case 8:
                printInfo(LM);
                pause();
                break;
            case 9:
                showAllData(LM, firstRel);
                pause();
                break;
            case 10:
                menuCariDosen(LD);
                pause();
                break;
            case 11:
                menuCariMahasiswa(LM);
                pause();
                break;
            case 12:
                menuTampilMahasiswaByDosen(LD, firstRel);
                pause();
                break;
            case 13:
                menuTampilDosenByMahasiswa(LM, firstRel);
                pause();
                break;
            case 14:
                findDosenMaxMinBimbingan(LD, firstRel);
                pause();
                break;
            case 0:
                cout << endl << "Kembali ke menu utama..." << endl;
                break;
            default:
                cout << endl << "Pilihan tidak valid!" << endl;
                pause();
        }
    } while(pilihan != 0);
}