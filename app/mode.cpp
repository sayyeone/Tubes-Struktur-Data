#include "../include/dosen.h"
#include "../include/mahasiswa.h"
#include "../include/relasi.h"

void injectData(List_dosen &LD, List_mahasiswa &LM, address_relasi &firstRel);
void manualMode(List_dosen &LD, List_mahasiswa &LM, address_relasi &firstRel);


void pilihMode(List_dosen &LD, List_mahasiswa &LM, address_relasi &firstRel) {
    int pilihan;
    
    cout << "Pilih Mode Operasi:" << endl;
    cout << "1. Mode Inject (Data Otomatis)" << endl;
    cout << "2. Mode Manual (Input User)" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;
    
    switch(pilihan) {
        case 1:
            injectData(LD, LM, firstRel);
            cin.ignore();
            cout << endl << "Tekan ENTER untuk masuk ke menu...";
            cin.get();
            manualMode(LD, LM, firstRel);
            break;
        case 2:
            cout << endl << "Mode Manual dipilih. Silakan input data secara manual." << endl;
            cin.ignore();
            cout << "Tekan ENTER untuk melanjutkan...";
            cin.get();
            manualMode(LD, LM, firstRel);
            break;
        case 0:
            cout << endl << "Terima kasih telah menggunakan sistem ini!" << endl;
            break;
        default:
            cout << endl << "Pilihan tidak valid!" << endl;
            cin.ignore();
            cout << "Tekan ENTER untuk mengulang...";
            cin.get();
            pilihMode(LD, LM, firstRel);
    }
}