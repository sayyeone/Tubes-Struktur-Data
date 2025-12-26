#include "../include/relasi.h"

address_relasi alokasi_relasi(address_dosen D, address_mahasiswa M) {
    address_relasi R = new elmlist_relasi;
    dosen(R) = D;
    mahasiswa(R) = M;
    nextDosen(R) = NULL;
    nextMhs(R) = NULL;
    return R;
}

void dealokasi_relasi(address_relasi &R) {
    delete R;
    R = NULL;
}

void connect(address_dosen D, address_mahasiswa M, address_relasi &firstRel) {
    address_relasi R = alokasi_relasi(D, M);
    
    if(firstRel == NULL) {
        firstRel = R;
    } else {
        nextDosen(R) = firstRel;
        firstRel = R;
    }
}

void disconnect(address_dosen D, address_mahasiswa M, address_relasi &firstRel) {
    address_relasi R = findRelasiDosenMahasiswa(D, M, firstRel);
    
    if(R != NULL) {
        if(R == firstRel) {
            firstRel = nextDosen(R);
        } else {
            address_relasi P = firstRel;
            while(nextDosen(P) != R) {
                P = nextDosen(P);
            }
            nextDosen(P) = nextDosen(R);
        }
        dealokasi_relasi(R);
    }
}

void deleteAllRelasiDosen(address_dosen D, address_relasi &firstRel) {
    address_relasi P = firstRel;
    address_relasi Prec = NULL;
    
    while(P != NULL) {
        if(dosen(P) == D) {
            address_relasi temp = P;
            if(Prec == NULL) {
                firstRel = nextDosen(P);
                P = firstRel;
            } else {
                nextDosen(Prec) = nextDosen(P);
                P = nextDosen(Prec);
            }
            dealokasi_relasi(temp);
        } else {
            Prec = P;
            P = nextDosen(P);
        }
    }
}

void deleteAllRelasiMahasiswa(address_mahasiswa M, address_relasi &firstRel) {
    address_relasi P = firstRel;
    address_relasi Prec = NULL;
    
    while(P != NULL) {
        if(mahasiswa(P) == M) {
            address_relasi temp = P;
            if(Prec == NULL) {
                firstRel = nextDosen(P);
                P = firstRel;
            } else {
                nextDosen(Prec) = nextDosen(P);
                P = nextDosen(Prec);
            }
            dealokasi_relasi(temp);
        } else {
            Prec = P;
            P = nextDosen(P);
        }
    }
}

address_relasi findRelasiDosenMahasiswa(address_dosen D, address_mahasiswa M, address_relasi firstRel) {
    address_relasi P = firstRel;
    while(P != NULL) {
        if(dosen(P) == D && mahasiswa(P) == M) {
            return P;
        }
        P = nextDosen(P);
    }
    return NULL;
}

address_relasi findFirstRelasiDosen(address_dosen D, address_relasi firstRel) {
    address_relasi P = firstRel;
    while(P != NULL) {
        if(dosen(P) == D) {
            return P;
        }
        P = nextDosen(P);
    }
    return NULL;
}

address_relasi findFirstRelasiMahasiswa(address_mahasiswa M, address_relasi firstRel) {
    address_relasi P = firstRel;
    while(P != NULL) {
        if(mahasiswa(P) == M) {
            return P;
        }
        P = nextDosen(P);
    }
    return NULL;
}

int countMahasiswaBimbingan(address_dosen D, address_relasi firstRel) {
    int count = 0;
    address_relasi P = firstRel;
    while(P != NULL) {
        if(dosen(P) == D) {
            count++;
        }
        P = nextDosen(P);
    }
    return count;
}

int countDosenPembimbing(address_mahasiswa M, address_relasi firstRel) {
    int count = 0;
    address_relasi P = firstRel;
    while(P != NULL) {
        if(mahasiswa(P) == M) {
            count++;
        }
        P = nextDosen(P);
    }
    return count;
}

void showAllMahasiswaByDosen(address_dosen D, address_relasi firstRel) {
    cout << endl << "=== Mahasiswa yang dibimbing oleh " << info(D).nama << " ===" << endl;
    address_relasi P = firstRel;
    int no = 1;
    bool found = false;
    
    while(P != NULL) {
        if(dosen(P) == D) {
            cout << no << ". " << info(mahasiswa(P)).nama << " (NIM: " << info(mahasiswa(P)).nim << ")" << endl;
            cout << "   Judul TA: " << info(mahasiswa(P)).judul_ta << endl;
            no++;
            found = true;
        }
        P = nextDosen(P);
    }
    
    if(!found) {
        cout << "Tidak ada mahasiswa yang dibimbing" << endl;
    }
}

void showAllDosenByMahasiswa(address_mahasiswa M, address_relasi firstRel) {
    cout << endl << "=== Dosen pembimbing " << info(M).nama << " ===" << endl;
    address_relasi P = firstRel;
    int no = 1;
    bool found = false;
    
    while(P != NULL) {
        if(mahasiswa(P) == M) {
            cout << no << ". " << info(dosen(P)).nama << " (NIP: " << info(dosen(P)).nip << ")" << endl;
            cout << "   Keahlian: " << info(dosen(P)).keahlian << endl;
            no++;
            found = true;
        }
        P = nextDosen(P);
    }
    
    if(!found) {
        cout << "Tidak ada dosen pembimbing" << endl;
    }
}

void showAllData(List_mahasiswa LM, address_relasi firstRel) {
    cout << endl << "=== Data Seluruh Mahasiswa dan Dosen Pembimbingnya ===" << endl;
    address_mahasiswa PM = first(LM);
    int no = 1;
    
    if(PM != NULL) {
        while(PM != NULL) {
            cout << no << ". " << info(PM).nama << " (NIM: " << info(PM).nim << ")" << endl;
            cout << "   Judul TA: " << info(PM).judul_ta << endl;
            cout << "   Dosen Pembimbing:" << endl;
            
            address_relasi PR = firstRel;
            bool found = false;
            int noDosen = 1;
            
            while(PR != NULL) {
                if(mahasiswa(PR) == PM) {
                    cout << "   " << noDosen << ". " << info(dosen(PR)).nama << " (NIP: " << info(dosen(PR)).nip << ")" << endl;
                    noDosen++;
                    found = true;
                }
                PR = nextDosen(PR);
            }
            
            if(!found) {
                cout << "   Belum ada dosen pembimbing" << endl;
            }
            
            cout << endl;
            PM = next(PM);
            no++;
        }
    } else {
        cout << "Tidak ada data mahasiswa" << endl;
    }
}

void findDosenMaxMinBimbingan(List_dosen LD, address_relasi firstRel) {
    cout << endl << "=== Statistik Bimbingan Dosen ===" << endl;
    
    if(first(LD) == NULL) {
        cout << "Tidak ada data dosen" << endl;
        return;
    }
    
    address_dosen P = first(LD);
    address_dosen dosenMax = P;
    address_dosen dosenMin = P;
    int maxCount = countMahasiswaBimbingan(P, firstRel);
    int minCount = maxCount;
    
    P = next(P);
    while(P != NULL) {
        int count = countMahasiswaBimbingan(P, firstRel);
        
        if(count > maxCount) {
            maxCount = count;
            dosenMax = P;
        }
        
        if(count < minCount) {
            minCount = count;
            dosenMin = P;
        }
        
        P = next(P);
    }
    
    cout << "Dosen dengan bimbingan TERBANYAK:" << endl;
    cout << "- " << info(dosenMax).nama << " (NIP: " << info(dosenMax).nip << ")" << endl;
    cout << "  Jumlah mahasiswa: " << maxCount << " orang" << endl;
    
    cout << endl << "Dosen dengan bimbingan TERSEDIKIT:" << endl;
    cout << "- " << info(dosenMin).nama << " (NIP: " << info(dosenMin).nip << ")" << endl;
    cout << "  Jumlah mahasiswa: " << minCount << " orang" << endl;
}