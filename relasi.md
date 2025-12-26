# Multi-Linked List (MLL) Relasi Dosen-Mahasiswa - Dokumentasi Lengkap

## 📖 Definisi Multi-Linked List (MLL)

Multi-Linked List adalah struktur data yang menghubungkan dua linked list menggunakan list relasi. Dalam kasus ini:
- **List Dosen**: Single Linked List
- **List Mahasiswa**: Single Linked List  
- **List Relasi**: Menghubungkan Dosen dengan Mahasiswa (Many-to-Many relationship)

### Prinsip Relasi Many-to-Many
- Satu dosen bisa membimbing banyak mahasiswa
- Satu mahasiswa bisa dibimbing oleh banyak dosen

---

## 🏗️ Struktur Data

### Struktur Node Relasi
```cpp
struct elmlist_relasi {
    address_dosen dosen;           // Pointer ke node dosen
    address_mahasiswa mahasiswa;   // Pointer ke node mahasiswa
    address_relasi nextDosen;      // Pointer ke relasi berikutnya (traversal dari dosen)
    address_relasi nextMhs;        // Pointer ke relasi berikutnya (traversal dari mahasiswa)
};
```

### Visualisasi Node Relasi
```
┌─────────┬───────────┬───────────┬─────────┐
│  dosen  │ mahasiswa │ nextDosen │ nextMhs │
└─────────┴───────────┴───────────┴─────────┘
    ↓           ↓           ↓           ↓
  [Dosen]   [Mahasiswa]   [Next]     [Next]
```

---

## 1. alokasi_relasi() - Membuat Node Relasi Baru

### Kode
```cpp
address_relasi alokasi_relasi(address_dosen D, address_mahasiswa M) {
    address_relasi R = new elmlist_relasi;
    dosen(R) = D;
    mahasiswa(R) = M;
    nextDosen(R) = NULL;
    nextMhs(R) = NULL;
    return R;
}
```

### Visualisasi: Membuat Relasi

#### STEP 1: address_relasi R = new elmlist_relasi;

**Kondisi Awal:**
```
D → [Dosen: Dr. Andi, NIP: 12345]
M → [Mahasiswa: Budi, NIM: 21001, TA: Sistem AI]
```

**Alokasi Memori:**
```cpp
address_relasi R = new elmlist_relasi;
```
```
                         R
                         ↓
                    ┌────┬────┬────┬────┐
                    │ ?? │ ?? │ ?? │ ?? │
                    └────┴────┴────┴────┘
                    (Memori baru dialokasi)
```

#### STEP 2: dosen(R) = D;

**Kode:**
```cpp
dosen(R) = D;
```

**Visualisasi:**
```
D → [Dosen: Dr. Andi, NIP: 12345]
     ↑
     │
     │              R
     │              ↓
     │         ┌────┬────┬────┬────┐
     └─────────┤  • │ ?? │ ?? │ ?? │
               └────┴────┴────┴────┘
```

#### STEP 3: mahasiswa(R) = M;

**Kode:**
```cpp
mahasiswa(R) = M;
```

**Visualisasi:**
```
D → [Dosen: Dr. Andi, NIP: 12345]
     ↑
     │
     │              R
     │              ↓
     │         ┌────┬────┬────┬────┐
     └─────────┤  • │  • │ ?? │ ?? │
               └────┴────┴────┴────┘
                     │
                     ↓
M → [Mahasiswa: Budi, NIM: 21001, TA: Sistem AI]
```

#### STEP 4: nextDosen(R) = NULL; nextMhs(R) = NULL;

**Kode:**
```cpp
nextDosen(R) = NULL;
nextMhs(R) = NULL;
```

**Visualisasi Hasil Akhir:**
```
D → [Dosen: Dr. Andi, NIP: 12345]
     ↑
     │
     │              R
     │              ↓
     │         ┌────┬────┬──────┬──────┐
     └─────────┤  • │  • │ NULL │ NULL │
               └────┴────┴──────┴──────┘
                     │
                     ↓
M → [Mahasiswa: Budi, NIM: 21001, TA: Sistem AI]
```

### Penjelasan
Fungsi ini membuat node relasi baru yang menghubungkan satu dosen dengan satu mahasiswa. Node relasi menyimpan pointer ke kedua entitas dan pointer untuk navigasi ke relasi berikutnya.

---

## 2. dealokasi_relasi() - Hapus Node Relasi

### Kode
```cpp
void dealokasi_relasi(address_relasi &R) {
    delete R;
    R = NULL;
}
```

### Visualisasi: Dealokasi

**Kondisi Awal:**
```
                         R
                         ↓
                    ┌────┬────┬──────┬──────┐
                    │  • │  • │ NULL │ NULL │
                    └────┴────┴──────┴──────┘
```

**STEP 1: delete R;**
```
                         R
                         ↓
                    ╔════╗════╗══════╗══════╗
                    ║ XX ║ XX ║  XX  ║  XX  ║
                    ╚════╩════╩══════╩══════╝
                    (Memori dikembalikan)
```

**STEP 2: R = NULL;**
```
R = NULL
(Pointer di-reset)
```

### Penjelasan
Fungsi ini menghapus node relasi dari memori dan mengatur pointer menjadi NULL untuk menghindari dangling pointer.

---

## 3. connect() - Menghubungkan Dosen dengan Mahasiswa

### Kode
```cpp
void connect(address_dosen D, address_mahasiswa M, address_relasi &firstRel) {
    address_relasi R = alokasi_relasi(D, M);
    
    if(firstRel == NULL) {
        firstRel = R;
    } else {
        nextDosen(R) = firstRel;
        firstRel = R;
    }
}
```

### Visualisasi Lengkap: Connect pada List Kosong

#### Kondisi Awal
```
List Dosen:
D1 → [Dr. Andi, NIP: 12345]

List Mahasiswa:
M1 → [Budi, NIM: 21001, TA: Sistem AI]

List Relasi:
firstRel = NULL
```

#### STEP 1: address_relasi R = alokasi_relasi(D1, M1);

**Kode:**
```cpp
address_relasi R = alokasi_relasi(D1, M1);
```

**Visualisasi:**
```
D1 → [Dr. Andi]
      ↑
      │         R
      │         ↓
      │    ┌────┬────┬──────┬──────┐
      └────┤  • │  • │ NULL │ NULL │
           └────┴────┴──────┴──────┘
                 │
                 ↓
M1 → [Budi, NIM: 21001]

firstRel = NULL
```

#### STEP 2: if(firstRel == NULL)

**Kode:**
```cpp
if(firstRel == NULL) {  // true
    firstRel = R;
}
```

**Visualisasi Hasil:**
```
                   firstRel
                      ↓
D1 → [Dr. Andi]      R
      ↑              ↓
      │         ┌────┬────┬──────┬──────┐
      └─────────┤  • │  • │ NULL │ NULL │
                └────┴────┴──────┴──────┘
                      │
                      ↓
M1 → [Budi, NIM: 21001]
```

---

### Visualisasi Lengkap: Connect pada List yang Sudah Ada Isi

#### Kondisi Awal
```
List Dosen:
D1 → [Dr. Andi, NIP: 12345]
D2 → [Dr. Siti, NIP: 12346]

List Mahasiswa:
M1 → [Budi, NIM: 21001, TA: Sistem AI]
M2 → [Ani, NIM: 21002, TA: Web App]

List Relasi (sudah ada: D1-M1):
                   firstRel
                      ↓
                     R1
                      ↓
D1 → [Dr. Andi]  ┌────┬────┬──────┬──────┐
      ↑          │  • │  • │ NULL │ NULL │
      └──────────┴────┴────┴──────┴──────┘
                      │
                      ↓
M1 → [Budi]
```

#### Operasi: connect(D2, M2, firstRel)

**STEP 1: address_relasi R = alokasi_relasi(D2, M2);**

```cpp
address_relasi R = alokasi_relasi(D2, M2);
```

**Visualisasi:**
```
                   firstRel
                      ↓
                     R1
                      ↓
D1 → [Dr. Andi]  ┌────┬────┬──────┬──────┐
      ↑          │  • │  • │ NULL │ NULL │
      └──────────┴────┴────┴──────┴──────┘
                      │
                      ↓
M1 → [Budi]


D2 → [Dr. Siti]      R (NEW)
      ↑              ↓
      │         ┌────┬────┬──────┬──────┐
      └─────────┤  • │  • │ NULL │ NULL │
                └────┴────┴──────┴──────┘
                      │
                      ↓
M2 → [Ani]
```

**STEP 2: nextDosen(R) = firstRel;**

```cpp
nextDosen(R) = firstRel;
```

**Visualisasi:**
```
                   firstRel
                      ↓
                     R1
                      ↓
D1 → [Dr. Andi]  ┌────┬────┬──────┬──────┐
      ↑          │  • │  • │ NULL │ NULL │
      └──────────┴────┴────┴──────┴──────┘
       ↑              │
       │              ↓
       │         M1 → [Budi]
       │
       │
D2 → [Dr. Siti]      R (NEW)
      ↑              ↓
      │         ┌────┬────┬──────┬──────┐
      └─────────┤  • │  • │  •   │ NULL │
                └────┴────┴──────┴──────┘
                      │     │
                      │     └─────┐
                      ↓           ↓
M2 → [Ani]                      [R1]
```

**STEP 3: firstRel = R;**

```cpp
firstRel = R;
```

**Visualisasi Hasil Akhir:**
```
                   firstRel
                      ↓
                      R (NEW - sekarang di depan)
                      ↓
D2 → [Dr. Siti]  ┌────┬────┬──────┬──────┐
      ↑          │  • │  • │  •   │ NULL │
      └──────────┴────┴────┴──────┴──────┘
                      │     │
                      │     └────────────┐
                      ↓                  ↓
M2 → [Ani]                             R1
                                        ↓
D1 → [Dr. Andi]                    ┌────┬────┬──────┬──────┐
      ↑                            │  • │  • │ NULL │ NULL │
      └────────────────────────────┴────┴────┴──────┴──────┘
                                        │
                                        ↓
M1 → [Budi]
```

### Penjelasan
Fungsi `connect()` menambahkan relasi baru di depan list relasi (insert di head). Jika list kosong, relasi baru menjadi firstRel. Jika sudah ada isi, relasi baru disisipkan di depan dengan mengubah pointer nextDosen.

---

## 4. disconnect() - Memutus Hubungan Dosen-Mahasiswa

### Kode
```cpp
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
```

### Visualisasi: Disconnect Relasi di Tengah

#### Kondisi Awal
```
List Relasi (3 relasi):

firstRel → R1 → R2 → R3 → NULL
           ↓    ↓    ↓
        D1-M1 D2-M2 D1-M2
```

**Detail:**
```
                   firstRel
                      ↓
                     R1
                      ↓
                 ┌────┬────┬──────┬──────┐
D1 → [Dr. Andi] │  • │  • │  •   │ NULL │
      ↑         └────┴────┴──────┴──────┘
      └─────────────────│  │
                        │  └────────────┐
                        ↓               ↓
M1 → [Budi]                           R2
                                       ↓
                                  ┌────┬────┬──────┬──────┐
D2 → [Dr. Siti]                   │  • │  • │  •   │ NULL │
      ↑                           └────┴────┴──────┴──────┘
      └───────────────────────────────────│  │
                                           │  └───────────┐
                                           ↓              ↓
M2 → [Ani]                                              R3
                                                         ↓
                                                    ┌────┬────┬──────┬──────┐
D1 → [Dr. Andi]                                     │  • │  • │ NULL │ NULL │
      ↑                                             └────┴────┴──────┴──────┘
      └─────────────────────────────────────────────────────│
                                                             ↓
M2 → [Ani]
```

#### Operasi: disconnect(D2, M2, firstRel) - Hapus R2

**STEP 1: address_relasi R = findRelasiDosenMahasiswa(D2, M2, firstRel);**

```cpp
// Mencari relasi D2-M2
// Ditemukan: R = R2
```

```
                   firstRel
                      ↓
                     R1 → R2 (TARGET!) → R3 → NULL
                          ↑
                          R
```

**STEP 2: if(R == firstRel) → false**

```cpp
// R2 bukan firstRel, masuk ke else
```

**STEP 3: Cari predecessor (node sebelum R2)**

```cpp
address_relasi P = firstRel;  // P = R1
while(nextDosen(P) != R) {     // nextDosen(R1) != R2? false, keluar
    P = nextDosen(P);
}
// P sekarang = R1 (predecessor dari R2)
```

**Visualisasi:**
```
                   firstRel
                      ↓
                     R1 → R2 → R3 → NULL
                     ↑    ↑
                     P    R
```

**STEP 4: nextDosen(P) = nextDosen(R);**

```cpp
nextDosen(P) = nextDosen(R);
// nextDosen(R1) = R3
```

**Visualisasi:**
```
                   firstRel
                      ↓
                     R1 ─────┐  R2 → R3 → NULL
                     ↑       │  ↑    ↑
                     P       │  R    │
                             └───────┘
                           (bypass R2)
```

**STEP 5: dealokasi_relasi(R);**

```cpp
delete R;
R = NULL;
```

**Visualisasi Hasil Akhir:**
```
                   firstRel
                      ↓
                     R1 → R3 → NULL
                     ↓    ↓
                  D1-M1 D1-M2

                  ╔════╗
                  ║ R2 ║ (DIHAPUS!)
                  ╚════╝
```

### Penjelasan
Fungsi `disconnect()` menghapus relasi antara dosen dan mahasiswa tertentu. Proses:
1. Cari relasi yang sesuai menggunakan `findRelasiDosenMahasiswa()`
2. Jika relasi ditemukan di head, geser firstRel
3. Jika di tengah/akhir, cari predecessor dan bypass node target
4. Hapus node relasi dari memori

---

## 5. deleteAllRelasiDosen() - Hapus Semua Relasi Dosen

### Kode
```cpp
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
```

### Visualisasi: Hapus Semua Relasi Dr. Andi (D1)

#### Kondisi Awal
```
List Relasi (5 relasi):
firstRel → R1 → R2 → R3 → R4 → R5 → NULL
           ↓    ↓    ↓    ↓    ↓
        D1-M1 D2-M2 D1-M2 D2-M3 D1-M3
         ✗           ✗           ✗
      (hapus)     (hapus)     (hapus)
```

**Detail Struktur:**
```
                   firstRel
                      ↓
                     R1 (D1-M1) → R2 (D2-M2) → R3 (D1-M2) → R4 (D2-M3) → R5 (D1-M3) → NULL
```

#### Operasi: deleteAllRelasiDosen(D1, firstRel)

**Iterasi 1: Cek R1 (D1-M1)**

```cpp
P = R1, Prec = NULL
if(dosen(P) == D1)  // TRUE! (R1 adalah relasi D1)
```

```
                   firstRel
                      ↓
Prec=NULL            R1 → R2 → R3 → R4 → R5 → NULL
                     ↑
                     P
```

```cpp
address_relasi temp = P;  // simpan R1
if(Prec == NULL) {        // TRUE (R1 di head)
    firstRel = nextDosen(P);  // firstRel = R2
    P = firstRel;             // P = R2
}
dealokasi_relasi(temp);   // hapus R1
```

**Hasil Iterasi 1:**
```
                   firstRel
                      ↓
╔════╗              R2 → R3 → R4 → R5 → NULL
║ R1 ║              ↑
╚════╝              P
(DIHAPUS)

Prec = NULL
```

**Iterasi 2: Cek R2 (D2-M2)**

```cpp
P = R2, Prec = NULL
if(dosen(P) == D2)  // FALSE (R2 bukan relasi D1)
```

```cpp
else {
    Prec = P;              // Prec = R2
    P = nextDosen(P);      // P = R3
}
```

**Hasil Iterasi 2:**
```
                   firstRel
                      ↓
                     R2 → R3 → R4 → R5 → NULL
                     ↑    ↑
                   Prec   P
```

**Iterasi 3: Cek R3 (D1-M2)**

```cpp
P = R3, Prec = R2
if(dosen(P) == D1)  // TRUE! (R3 adalah relasi D1)
```

```cpp
address_relasi temp = P;  // simpan R3
if(Prec == NULL) {        // FALSE
} else {                  // masuk sini
    nextDosen(Prec) = nextDosen(P);  // R2->next = R4
    P = nextDosen(Prec);             // P = R4
}
dealokasi_relasi(temp);   // hapus R3
```

**Hasil Iterasi 3:**
```
                   firstRel
                      ↓
                     R2 ─────┐ ╔════╗  R4 → R5 → NULL
                     ↑       │ ║ R3 ║  ↑
                   Prec      │ ╚════╝  P
                             └─────────┘
                              (bypass R3)
```

**Iterasi 4: Cek R4 (D2-M3)**

```cpp
P = R4, Prec = R2
if(dosen(P) == D2)  // FALSE (R4 bukan relasi D1)
```

```cpp
else {
    Prec = P;              // Prec = R4
    P = nextDosen(P);      // P = R5
}
```

**Hasil Iterasi 4:**
```
                   firstRel
                      ↓
                     R2 → R4 → R5 → NULL
                          ↑    ↑
                        Prec   P
```

**Iterasi 5: Cek R5 (D1-M3)**

```cpp
P = R5, Prec = R4
if(dosen(P) == D1)  // TRUE! (R5 adalah relasi D1)
```

```cpp
address_relasi temp = P;  // simpan R5
if(Prec == NULL) {        // FALSE
} else {                  // masuk sini
    nextDosen(Prec) = nextDosen(P);  // R4->next = NULL
    P = nextDosen(Prec);             // P = NULL
}
dealokasi_relasi(temp);   // hapus R5
```

**Hasil Iterasi 5:**
```
                   firstRel
                      ↓
                     R2 → R4 → NULL    ╔════╗
                          ↑            ║ R5 ║
                        Prec           ╚════╝
                                      (DIHAPUS)
P = NULL (loop berhenti)
```

**Hasil Akhir:**
```
                   firstRel
                      ↓
                     R2 → R4 → NULL
                     ↓    ↓
                  D2-M2 D2-M3

Relasi D1 (Dr. Andi) sudah dihapus semua!
- R1 (D1-M1) ✓ dihapus
- R3 (D1-M2) ✓ dihapus
- R5 (D1-M3) ✓ dihapus
```

### Penjelasan
Fungsi `deleteAllRelasiDosen()` menghapus semua relasi yang melibatkan dosen tertentu. Proses:
1. Traversal seluruh list relasi
2. Jika dosen pada relasi = dosen target, hapus relasi tersebut
3. Gunakan pointer Prec untuk menjaga koneksi list
4. Handle kasus delete di head (Prec=NULL) dan di tengah/akhir (Prec!=NULL)

---

## 6. deleteAllRelasiMahasiswa() - Hapus Semua Relasi Mahasiswa

### Kode
```cpp
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
```

### Visualisasi: Hapus Semua Relasi Ani (M2)

#### Kondisi Awal
```
List Relasi:
firstRel → R1 → R2 → R3 → R4 → NULL
           ↓    ↓    ↓    ↓
        D1-M1 D2-M2 D1-M2 D2-M3
                 ✗      ✗
              (hapus) (hapus)
```

#### Operasi: deleteAllRelasiMahasiswa(M2, firstRel)

**Proses mirip dengan deleteAllRelasiDosen(), bedanya:**
- Cek `mahasiswa(P) == M` bukan `dosen(P) == D`
- Yang dihapus: semua relasi dengan mahasiswa M2

**Hasil Akhir:**
```
                   firstRel
                      ↓
                     R1 → R4 → NULL
                     ↓    ↓
                  D1-M1 D2-M3

Relasi M2 (Ani) sudah dihapus semua!
- R2 (D2-M2) ✓ dihapus
- R3 (D1-M2) ✓ dihapus
```

### Penjelasan
Fungsi ini identik dengan `deleteAllRelasiDosen()`, hanya saja yang dicek adalah field mahasiswa bukan dosen. Digunakan saat ingin menghapus mahasiswa dari sistem.

---

## 7. findRelasiDosenMahasiswa() - Cari Relasi Spesifik

### Kode
```cpp
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
```

### Visualisasi: Mencari Relasi D2-M3

#### Kondisi List
```
List Relasi:
firstRel → R1 → R2 → R3 → R4 → NULL
           ↓    ↓    ↓    ↓
        D1-M1 D2-M2 D1-M3 D2-M3
                             ↑
                         (TARGET!)
```

#### Operasi: findRelasiDosenMahasiswa(D2, M3, firstRel)

**Iterasi 1: Cek R1 (D1-M1)**
```cpp
P = R1
if(dosen(P) == D2 && mahasiswa(P) == M3)  // FALSE
P = nextDosen(P);  // P = R2
```

**Iterasi 2: Cek R2 (D2-M2)**
```cpp
P = R2
if(dosen(P) == D2 && mahasiswa(P) == M3)  // FALSE (dosen cocok, mhs tidak)
P = nextDosen(P);  // P = R3
```

**Iterasi 3: Cek R3 (D1-M3)**
```cpp
P = R3
if(dosen(P) == D2 && mahasiswa(P) == M3)  // FALSE (mhs cocok, dosen tidak)
P = nextDosen(P);  // P = R4
```

**Iterasi 4: Cek R4 (D2-M3)**
```cpp
P = R4
if(dosen(P) == D2 && mahasiswa(P) == M3)  // TRUE! DITEMUKAN!
return P;  // return R4
```

**Hasil:**
```
                   firstRel
                      ↓
                     R1 → R2 → R3 → R4 → NULL
                                    ↑
                                    └─── RETURN (Ditemukan!)
```

### Penjelasan
Fungsi ini mencari relasi spesifik antara dosen D dan mahasiswa M. Menggunakan linear search dengan kondisi AND: dosen DAN mahasiswa harus cocok.

---

## 8. findFirstRelasiDosen() - Cari Relasi Pertama Dosen

### Kode
```cpp
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
```

### Visualisasi: Mencari Relasi Pertama Dr. Andi (D1)

#### Kondisi List
```
List Relasi:
firstRel → R1 → R2 → R3 → R4 → R5 → NULL
           ↓    ↓    ↓    ↓    ↓
        D2-M1 D1-M2 D2-M3 D1-M3 D1-M4
                 ↑
           (PERTAMA D1)
```

#### Operasi: findFirstRelasiDosen(D1, firstRel)

**Iterasi 1: Cek R1 (D2-M1)**
```cpp
P = R1
if(dosen(P) == D1)  // FALSE (D2 != D1)
P = nextDosen(P);   // P = R2
```

**Iterasi 2: Cek R2 (D1-M2)**
```cpp
P = R2
if(dosen(P) == D1)  // TRUE! DITEMUKAN!
return P;           // return R2 (relasi pertama D1)
```

**Hasil:**
```
                   firstRel
                      ↓
                     R1 → R2 → R3 → R4 → R5 → NULL
                          ↑
                          └─── RETURN (Relasi pertama D1)
```

### Penjelasan
Fungsi ini mencari relasi pertama yang melibatkan dosen D. Begitu ditemukan relasi yang cocok, langsung return tanpa mencari yang lain.

---

## 9. countMahasiswaBimbingan() - Hitung Jumlah Mahasiswa Bimbingan

### Kode
```cpp
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
```

### Visualisasi: Hitung Mahasiswa Bimbingan Dr. Andi (D1)

#### Kondisi List
```
List Relasi:
firstRel → R1 → R2 → R3 → R4 → R5 → NULL
           ↓    ↓    ↓    ↓    ↓
        D1-M1 D2-M2 D1-M2 D2-M3 D1-M3
         ✓           ✓           ✓
      (count)     (count)     (count)
```

#### Operasi: countMahasiswaBimbingan(D1, firstRel)

**Iterasi 1: R1 (D1-M1)**
```cpp
P = R1, count = 0
if(dosen(P) == D1)  // TRUE
count++;            // count = 1
P = nextDosen(P);
```

**Iterasi 2: R2 (D2-M2)**
```cpp
P = R2, count = 1
if(dosen(P) == D1)  // FALSE (D2 != D1)
P = nextDosen(P);   // count tetap 1
```

**Iterasi 3: R3 (D1-M2)**
```cpp
P = R3, count = 1
if(dosen(P) == D1)  // TRUE
count++;            // count = 2
P = nextDosen(P);
```

**Iterasi 4: R4 (D2-M3)**
```cpp
P = R4, count = 2
if(dosen(P) == D1)  // FALSE
P = nextDosen(P);   // count tetap 2
```

**Iterasi 5: R5 (D1-M3)**
```cpp
P = R5, count = 2
if(dosen(P) == D1)  // TRUE
count++;            // count = 3
P = nextDosen(P);   // P = NULL
```

**Hasil:**
```
return count;  // return 3

Dr. Andi (D1) membimbing 3 mahasiswa:
- M1 (Budi)
- M2 (Ani)
- M3 (Citra)
```

### Penjelasan
Fungsi ini menghitung berapa banyak mahasiswa yang dibimbing oleh dosen D dengan traversal seluruh list relasi dan increment counter setiap kali menemukan relasi dengan dosen D.

---

## 10. countDosenPembimbing() - Hitung Jumlah Dosen Pembimbing

### Kode
```cpp
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
```

### Visualisasi: Hitung Dosen Pembimbing Ani (M2)

#### Kondisi List
```
List Relasi:
firstRel → R1 → R2 → R3 → R4 → R5 → NULL
           ↓    ↓    ↓    ↓    ↓
        D1-M1 D2-M2 D1-M2 D2-M3 D3-M2
                 ✓      ✓           ✓
              (count) (count)   (count)
```

#### Operasi: countDosenPembimbing(M2, firstRel)

**Proses:**
- Iterasi 1 (R1): M1 != M2 → count = 0
- Iterasi 2 (R2): M2 == M2 → count = 1 ✓
- Iterasi 3 (R3): M2 == M2 → count = 2 ✓
- Iterasi 4 (R4): M3 != M2 → count = 2
- Iterasi 5 (R5): M2 == M2 → count = 3 ✓

**Hasil:**
```
return count;  // return 3

Ani (M2) dibimbing oleh 3 dosen:
- D2 (Dr. Siti)
- D1 (Dr. Andi)
- D3 (Dr. Budi)
```

### Penjelasan
Fungsi ini kebalikan dari `countMahasiswaBimbingan()`, menghitung berapa banyak dosen yang membimbing mahasiswa M.

---

## 11. showAllMahasiswaByDosen() - Tampilkan Mahasiswa Per Dosen

### Kode
```cpp
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
```

### Visualisasi Output: Mahasiswa Bimbingan Dr. Andi

#### Struktur Data
```
List Relasi:
firstRel → R1 → R2 → R3 → R4 → R5 → NULL
           ↓    ↓    ↓    ↓    ↓
        D1-M1 D2-M2 D1-M3 D2-M4 D1-M5
         ✓           ✓           ✓
      (print)     (print)     (print)
```

#### Output Console
```
=== Mahasiswa yang dibimbing oleh Dr. Andi ===
1. Budi (NIM: 21001)
   Judul TA: Sistem Rekomendasi Berbasis AI

2. Citra (NIM: 21003)
   Judul TA: Aplikasi Mobile Learning

3. Eko (NIM: 21005)
   Judul TA: Analisis Big Data untuk E-Commerce
```

### Penjelasan
Fungsi ini menampilkan semua mahasiswa yang dibimbing oleh dosen tertentu dengan format terstruktur. Menggunakan flag `found` untuk menangani kasus dosen yang tidak membimbing mahasiswa.

---

## 12. showAllData() - Tampilkan Semua Data Lengkap

### Kode
```cpp
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
```

### Visualisasi Output: Data Lengkap Sistem

#### Struktur Data
```
List Mahasiswa:
LM → M1 → M2 → M3 → NULL

List Relasi:
firstRel → R1 → R2 → R3 → R4 → NULL
           ↓    ↓    ↓    ↓
        D1-M1 D2-M1 D1-M2 D2-M3
```

#### Output Console
```
=== Data Seluruh Mahasiswa dan Dosen Pembimbingnya ===
1. Budi (NIM: 21001)
   Judul TA: Sistem Rekomendasi Berbasis AI
   Dosen Pembimbing:
   1. Dr. Andi (NIP: 12345)
   2. Dr. Siti (NIP: 12346)

2. Ani (NIM: 21002)
   Judul TA: Aplikasi E-Commerce Modern
   Dosen Pembimbing:
   1. Dr. Andi (NIP: 12345)

3. Citra (NIM: 21003)
   Judul TA: Sistem Informasi Perpustakaan
   Dosen Pembimbing:
   1. Dr. Siti (NIP: 12346)
```

### Penjelasan
Fungsi ini menampilkan seluruh data mahasiswa beserta dosen pembimbingnya. Menggunakan nested loop: outer loop untuk traversal mahasiswa, inner loop untuk mencari semua relasi mahasiswa tersebut.

---

## 13. findDosenMaxMinBimbingan() - Cari Dosen Maks/Min Bimbingan

### Kode
```cpp
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
```

### Visualisasi: Mencari Dosen Maks/Min

#### Kondisi Data
```
List Dosen:
LD → D1 → D2 → D3 → D4 → NULL

List Relasi (jumlah bimbingan per dosen):
D1: 5 mahasiswa (R1, R3, R5, R7, R9)
D2: 2 mahasiswa (R2, R4)
D3: 8 mahasiswa (R6, R8, R10, R11, R12, R13, R14, R15) ← MAX
D4: 1 mahasiswa (R16) ← MIN
```

#### Proses Algoritma

**Inisialisasi:**
```cpp
P = D1
dosenMax = D1, maxCount = 5
dosenMin = D1, minCount = 5
```

**Iterasi 1: Cek D2**
```cpp
P = D2
count = countMahasiswaBimbingan(D2, firstRel) = 2

if(count > maxCount)  // 2 > 5? FALSE
if(count < minCount)  // 2 < 5? TRUE
    minCount = 2
    dosenMin = D2
```

**Visualisasi:**
```
dosenMax = D1 (5 mahasiswa)
dosenMin = D2 (2 mahasiswa) ← UPDATE
```

**Iterasi 2: Cek D3**
```cpp
P = D3
count = countMahasiswaBimbingan(D3, firstRel) = 8

if(count > maxCount)  // 8 > 5? TRUE
    maxCount = 8
    dosenMax = D3
    
if(count < minCount)  // 8 < 2? FALSE
```

**Visualisasi:**
```
dosenMax = D3 (8 mahasiswa) ← UPDATE
dosenMin = D2 (2 mahasiswa)
```

**Iterasi 3: Cek D4**
```cpp
P = D4
count = countMahasiswaBimbingan(D4, firstRel) = 1

if(count > maxCount)  // 1 > 8? FALSE
if(count < minCount)  // 1 < 2? TRUE
    minCount = 1
    dosenMin = D4
```

**Visualisasi Final:**
```
dosenMax = D3 (8 mahasiswa)
dosenMin = D4 (1 mahasiswa) ← UPDATE
```

#### Output Console
```
=== Statistik Bimbingan Dosen ===
Dosen dengan bimbingan TERBANYAK:
- Dr. Citra (NIP: 12347)
  Jumlah mahasiswa: 8 orang

Dosen dengan bimbingan TERSEDIKIT:
- Dr. Dedi (NIP: 12348)
  Jumlah mahasiswa: 1 orang
```

### Penjelasan
Fungsi ini mencari dosen dengan bimbingan terbanyak dan tersedikit menggunakan algoritma min-max. Traversal list dosen sambil track nilai maksimum dan minimum.


---


**Made with ❤️**