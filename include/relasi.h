#ifndef RELASI_H_INCLUDED
#define RELASI_H_INCLUDED

#include <iostream>
#include "dosen.h"
#include "mahasiswa.h"
using namespace std;

#define nextDosen(P) P->nextDosen
#define nextMhs(P) P->nextMhs
#define dosen(P) P->dosen
#define mahasiswa(P) P->mahasiswa

typedef struct elmlist_relasi *address_relasi;

struct elmlist_relasi {
    address_dosen dosen;
    address_mahasiswa mahasiswa;
    address_relasi nextDosen;
    address_relasi nextMhs;
};

address_relasi alokasi_relasi(address_dosen D, address_mahasiswa M);
void dealokasi_relasi(address_relasi &R);

void connect(address_dosen D, address_mahasiswa M, address_relasi &firstRel);
void disconnect(address_dosen D, address_mahasiswa M, address_relasi &firstRel);

void deleteAllRelasiDosen(address_dosen D, address_relasi &firstRel);
void deleteAllRelasiMahasiswa(address_mahasiswa M, address_relasi &firstRel);

address_relasi findRelasiDosenMahasiswa(address_dosen D, address_mahasiswa M, address_relasi firstRel);
address_relasi findFirstRelasiDosen(address_dosen D, address_relasi firstRel);
address_relasi findFirstRelasiMahasiswa(address_mahasiswa M, address_relasi firstRel);

int countMahasiswaBimbingan(address_dosen D, address_relasi firstRel);
int countDosenPembimbing(address_mahasiswa M, address_relasi firstRel);

void showAllMahasiswaByDosen(address_dosen D, address_relasi firstRel);
void showAllDosenByMahasiswa(address_mahasiswa M, address_relasi firstRel);
void showAllData(List_mahasiswa LM, address_relasi firstRel);

void findDosenMaxMinBimbingan(List_dosen LD, address_relasi firstRel);

#endif