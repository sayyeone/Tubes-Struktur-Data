#include "../include/dosen.h"

void createList(List_dosen &L) {
    first(L) = NULL;
    last(L) = NULL;
}

address_dosen alokasi_dosen(string nama, string nip, string keahlian) {
    address_dosen P = new elmlist_dosen;
    info(P).nama = nama;
    info(P).nip = nip;
    info(P).keahlian = keahlian;
    next(P) = NULL;
    prev(P) = NULL;
    return P;
}

void dealokasi_dosen(address_dosen &P) {
    delete P;
    P = NULL;
}

void insertLast(List_dosen &L, address_dosen P) {
    if(first(L) == NULL) {
        first(L) = P;
        last(L) = P;
    } else {
        prev(P) = last(L);
        next(last(L)) = P;
        last(L) = P;
    }
}

void deleteFirst(List_dosen &L, address_dosen &P) {
    if(first(L) != NULL) {
        P = first(L);
        if(first(L) == last(L)) {
            first(L) = NULL;
            last(L) = NULL;
        } else {
            first(L) = next(P);
            prev(first(L)) = NULL;
            next(P) = NULL;
        }
    }
}


void deleteAfter(List_dosen &L, address_dosen Prec, address_dosen &P) {
    if(Prec != NULL && next(Prec) != NULL) {
        P = next(Prec);
        if(P == last(L)) {
            last(L) = Prec;
            next(Prec) = NULL;
        } else {
            next(Prec) = next(P);
            prev(next(P)) = Prec;
        }
        next(P) = NULL;
        prev(P) = NULL;
    }
}

address_dosen findElmDosen(List_dosen L, string nama) {
    address_dosen P = first(L);
    while(P != NULL) {
        if(info(P).nama == nama) {
            return P;
        }
        P = next(P);
    }
    return NULL;
}

address_dosen findElmDosenByNIP(List_dosen L, string nip) {
    address_dosen P = first(L);
    while(P != NULL) {
        if(info(P).nip == nip) {
            return P;
        }
        P = next(P);
    }
    return NULL;
}

void printInfo(List_dosen L) {
    cout << endl << "=== List Dosen ===" << endl;
    int no = 1;
    address_dosen P = first(L);
    if(P != NULL) {
        while(P != NULL) {
            cout << no << ". " << info(P).nama << " (NIP: " << info(P).nip << ") - " << info(P).keahlian << endl;
            P = next(P);
            no++;
        }
    } else {
        cout << "List Dosen Kosong" << endl;
    }
}