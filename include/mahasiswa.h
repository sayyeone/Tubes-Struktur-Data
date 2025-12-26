#ifndef MAHASISWA_H_INCLUDED
#define MAHASISWA_H_INCLUDED

#include <iostream>
using namespace std;

#define first(L) L.first
#define next(P) P->next
#define info(P) P->info

struct mahasiswa {
    string nama;
    string nim;
    string judul_ta;
};

typedef mahasiswa infotype_mahasiswa;
typedef struct elmlist_mahasiswa *address_mahasiswa;

struct elmlist_mahasiswa {
    infotype_mahasiswa info;
    address_mahasiswa next;
};

struct List_mahasiswa {
    address_mahasiswa first;
};

void createList(List_mahasiswa &L);
address_mahasiswa alokasi_mahasiswa(string nama, string nim, string judul_ta);
void dealokasi_mahasiswa(address_mahasiswa &P);

void insertFirst(List_mahasiswa &L, address_mahasiswa P);
void deleteFirst(List_mahasiswa &L, address_mahasiswa &P);
void deleteLast(List_mahasiswa &L, address_mahasiswa &P);
void deleteAfter(address_mahasiswa Prec, address_mahasiswa &P);

address_mahasiswa findElmMahasiswa(List_mahasiswa L, string nama);
address_mahasiswa findElmMahasiswaByNIM(List_mahasiswa L, string nim);
void printInfo(List_mahasiswa L);

#endif