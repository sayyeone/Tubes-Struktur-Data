#include "../include/mahasiswa.h"

void createList(List_mahasiswa &L) {
    first(L) = NULL;
}

address_mahasiswa alokasi_mahasiswa(string nama, string nim, string judul_ta) {
    address_mahasiswa P = new elmlist_mahasiswa;
    info(P).nama = nama;
    info(P).nim = nim;
    info(P).judul_ta = judul_ta;
    next(P) = NULL;
    return P;
}

void dealokasi_mahasiswa(address_mahasiswa &P) {
    delete P;
    P = NULL;
}

void insertFirst(List_mahasiswa &L, address_mahasiswa P) {
    if(first(L) == NULL) {
        first(L) = P;
    } else {
        next(P) = first(L);
        first(L) = P;
    }
}

void deleteFirst(List_mahasiswa &L, address_mahasiswa &P) {
    if(first(L) != NULL) {
        P = first(L);
        first(L) = next(P);
        next(P) = NULL;
    }
}

void deleteLast(List_mahasiswa &L, address_mahasiswa &P) {
    if(first(L) != NULL) {
        if(next(first(L)) == NULL) {
            P = first(L);
            first(L) = NULL;
        } else {
            address_mahasiswa Q = first(L);
            while(next(next(Q)) != NULL) {
                Q = next(Q);
            }
            P = next(Q);
            next(Q) = NULL;
        }
    }
}

void deleteAfter(address_mahasiswa Prec, address_mahasiswa &P) {
    if(Prec != NULL && next(Prec) != NULL) {
        P = next(Prec);
        next(Prec) = next(P);
        next(P) = NULL;
    }
}

address_mahasiswa findElmMahasiswa(List_mahasiswa L, string nama) {
    address_mahasiswa P = first(L);
    while(P != NULL) {
        if(info(P).nama == nama) {
            return P;
        }
        P = next(P);
    }
    return NULL;
}

address_mahasiswa findElmMahasiswaByNIM(List_mahasiswa L, string nim) {
    address_mahasiswa P = first(L);
    while(P != NULL) {
        if(info(P).nim == nim) {
            return P;
        }
        P = next(P);
    }
    return NULL;
}

void printInfo(List_mahasiswa L) {
    cout << endl << "=== List Mahasiswa ===" << endl;
    int no = 1;
    address_mahasiswa P = first(L);
    if(P != NULL) {
        while(P != NULL) {
            cout << no << ". " << info(P).nama << " (NIM: " << info(P).nim << ")" << endl;
            cout << "   Judul TA: " << info(P).judul_ta << endl;
            P = next(P);
            no++;
        }
    } else {
        cout << "List Mahasiswa Kosong" << endl;
    }
}