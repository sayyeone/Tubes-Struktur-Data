# Doubly Linked List untuk Data Dosen - Dokumentasi Lengkap

## Definisi Doubly Linked List (DLL)

Doubly Linked List adalah struktur data linear di mana setiap node memiliki **dua pointer**: satu menunjuk ke node **berikutnya** (next) dan satu menunjuk ke node **sebelumnya** (prev). Berbeda dengan Single Linked List, DLL memungkinkan traversal dua arah (maju dan mundur).

## Struktur Data

### Struktur Dosen (Info)
```cpp
struct dosen {
    string nama;
    string nip;
    string keahlian;
};
```

### Struktur Node (Element List)
```cpp
struct elmlist_dosen {
    infotype_dosen info;  // Data dosen
    address_dosen next;   // Pointer ke node berikutnya
    address_dosen prev;   // Pointer ke node sebelumnya
};
```

Setiap Node memiliki tiga bagian:
```
┌──────┬──────┬──────┐
│ prev │ info │ next │
└──────┴──────┴──────┘
```
- `prev`: pointer ke node sebelumnya
- `info`: menyimpan data dosen (nama, nip, keahlian)
- `next`: pointer ke node berikutnya

### Struktur List
```cpp
struct List_dosen {
    address_dosen first;  // Pointer ke node pertama
    address_dosen last;   // Pointer ke node terakhir
};
```

---

## 1. createList() - Inisialisasi List

### Kode
```cpp
void createList(List_dosen &L) {
    first(L) = NULL;
    last(L) = NULL;
}
```

### Visualisasi
```
List L
┌───────┬──────┐
│ first │ last │
├───────┼──────┤
│ NULL  │ NULL │
└───────┴──────┘

List kosong, tidak ada node
```

### Penjelasan
Fungsi ini menginisialisasi list kosong dengan mengatur pointer `first` dan `last` menjadi `NULL`. Ini adalah langkah awal sebelum menggunakan doubly linked list. Berbeda dengan single linked list yang hanya memiliki pointer `first`, DLL memiliki dua pointer untuk memudahkan operasi dari kedua ujung list.

---

## 2. alokasi_dosen() - Membuat Node Baru

### Kode
```cpp
address_dosen alokasi_dosen(string nama, string nip, string keahlian) {
    address_dosen P = new elmlist_dosen;
    info(P).nama = nama;
    info(P).nip = nip;
    info(P).keahlian = keahlian;
    next(P) = NULL;
    prev(P) = NULL;
    return P;
}
```

### Visualisasi: Alokasi Node untuk Dosen "Dr. Budi"

#### STEP 1: address_dosen P = new elmlist_dosen;

**Kode:**
```cpp
address_dosen P = new elmlist_dosen;
```

**Visualisasi:**
```
      P
      ↓
┌──────┬────────────────────┬──────┐
│ prev │       info         │ next │
├──────┼────────────────────┼──────┤
│  ??  │   ??  │  ??  │ ??  │  ??  │
└──────┴────────────────────┴──────┘
```

**Penjelasan:**
Alokasi memori baru di heap untuk node dosen. Pointer `P` dibuat untuk menunjuk ke alamat memori yang baru dialokasikan. Isi dari node masih berupa nilai acak (sampah memori) karena belum diinisialisasi.

#### STEP 2: info(P).nama = nama;

**Kode:**
```cpp
info(P).nama = "Dr. Budi";
info(P).nip = "1234567890";
info(P).keahlian = "Algoritma";
```

**Visualisasi:**
```
      P
      ↓
┌──────┬─────────────────────────────────┬──────┐
│ prev │           info                  │ next │
├──────┼─────────────────────────────────┼──────┤
│  ??  │ Dr. Budi│1234567890│Algoritma   │  ??  │
└──────┴─────────────────────────────────┴──────┘
```

**Penjelasan:**
Mengisi bagian `info` dari node dengan data dosen yang diterima dari parameter fungsi. Sekarang bagian `info` sudah memiliki nilai yang valid, tetapi pointer `prev` dan `next` masih berisi nilai acak.

#### STEP 3: next(P) = NULL; prev(P) = NULL;

**Kode:**
```cpp
next(P) = NULL;
prev(P) = NULL;
```

**Visualisasi:**
```
      P
      ↓
┌──────┬─────────────────────────────────┬──────┐
│ prev │           info                  │ next │
├──────┼─────────────────────────────────┼──────┤
│ NULL │ Dr. Budi│1234567890│Algoritma   │ NULL │
└──────┴─────────────────────────────────┴──────┘
```

**Penjelasan:**
Menginisialisasi pointer `prev` dan `next` menjadi `NULL`. Ini menandakan bahwa node ini belum terhubung dengan node lain dalam list. Node siap untuk dimasukkan ke dalam list.

---

## 3. insertLast() - Menambah Node di Akhir List

### Kode
```cpp
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
```

### Kasus 1: Insert ke List Kosong

#### Kondisi Awal
```
List L
┌───────┬──────┐
│ first │ last │
├───────┼──────┤
│ NULL  │ NULL │
└───────┴──────┘

Node P (Dr. Budi)
┌──────┬─────────────────────────────────┬──────┐
│ NULL │ Dr. Budi│1234567890│Algoritma   │ NULL │
└──────┴─────────────────────────────────┴──────┘
```

#### STEP 1: if(first(L) == NULL)

**Kode:**
```cpp
if(first(L) == NULL) {  // true
```

**Penjelasan:**
Cek apakah list kosong. Karena `first(L) == NULL`, maka list kosong dan kita masuk ke blok if.

#### STEP 2: first(L) = P;

**Kode:**
```cpp
first(L) = P;
```

**Visualisasi:**
```
List L
┌───────┬──────┐
│ first │ last │
├───────┼──────┤
│   •───┼─NULL │
└───┼───┴──────┘
    │
    ↓
┌──────┬─────────────────────────────────┬──────┐
│ NULL │ Dr. Budi│1234567890│Algoritma   │ NULL │
└──────┴─────────────────────────────────┴──────┘
```

**Penjelasan:**
Pointer `first` dari list sekarang menunjuk ke node baru. Node ini menjadi elemen pertama dalam list.

#### STEP 3: last(L) = P;

**Kode:**
```cpp
last(L) = P;
```

**Visualisasi:**
```
List L
┌───────┬──────┐
│ first │ last │
├───────┼──────┤
│   •───┼──•───┤
└───┼───┴──┼───┘
    │      │
    └──┐ ┌─┘
       ↓ ↓
┌──────┬─────────────────────────────────┬──────┐
│ NULL │ Dr. Budi│1234567890│Algoritma   │ NULL │
└──────┴─────────────────────────────────┴──────┘
```

**Penjelasan:**
Pointer `last` juga menunjuk ke node yang sama. Karena hanya ada satu node, maka `first` dan `last` menunjuk ke node yang sama.

---

### Kasus 2: Insert ke List yang Sudah Ada Isi

#### Kondisi Awal
List sudah memiliki 1 elemen: Dr. Budi
```
List L
┌───────┬──────┐
│ first │ last │
├───────┼──────┤
│   •───┼──•───┤
└───┼───┴──┼───┘
    │      │
    └──┐ ┌─┘
       ↓ ↓
┌──────┬─────────────────────────────────┬──────┐
│ NULL │ Dr. Budi│1234567890│Algoritma   │ NULL │
└──────┴─────────────────────────────────┴──────┘

Node P baru (Dr. Ani)
┌──────┬─────────────────────────────────┬──────┐
│ NULL │ Dr. Ani │0987654321│Database    │ NULL │
└──────┴─────────────────────────────────┴──────┘
```

#### STEP 1: if(first(L) == NULL)

**Kode:**
```cpp
if(first(L) == NULL) {  // false, masuk ke else
```

**Penjelasan:**
Cek apakah list kosong. Karena `first(L)` tidak `NULL`, maka list sudah ada isi dan kita masuk ke blok else.

#### STEP 2: prev(P) = last(L);

**Kode:**
```cpp
prev(P) = last(L);
```

**Visualisasi:**
```
List L
┌───────┬──────┐
│ first │ last │
├───────┼──────┤
│   •───┼──•───┤
└───┼───┴──┼───┘
    │      │
    └──┐ ┌─┘
       ↓ ↓
┌──────┬─────────────────────────────────┬──────┐
│ NULL │ Dr. Budi│1234567890│Algoritma   │ NULL │
└──────┴─────────────────────────────────┴──────┘
   ↑
   │
┌──┼───┬─────────────────────────────────┬──────┐
│  •   │ Dr. Ani │0987654321│Database    │ NULL │
└──────┴─────────────────────────────────┴──────┘
```

**Penjelasan:**
Pointer `prev` dari node baru (Dr. Ani) sekarang menunjuk ke node terakhir yang ada (Dr. Budi). Ini membuat hubungan dari node baru ke node sebelumnya.

#### STEP 3: next(last(L)) = P;

**Kode:**
```cpp
next(last(L)) = P;
```

**Visualisasi:**
```
List L
┌───────┬──────┐
│ first │ last │
├───────┼──────┤
│   •───┼──•───┤
└───┼───┴──┼───┘
    │      │
    └──┐ ┌─┘
       ↓ ↓
┌──────┬─────────────────────────────────┬──────┐
│ NULL │ Dr. Budi│1234567890│Algoritma   │  •───┼──┐
└──────┴─────────────────────────────────┴──────┘  │
   ↑                                                │
   │                                                ↓
┌──┼───┬─────────────────────────────────┬──────┐
│  •   │ Dr. Ani │0987654321│Database    │ NULL │
└──────┴─────────────────────────────────┴──────┘
```

**Penjelasan:**
Pointer `next` dari node terakhir yang lama (Dr. Budi) sekarang menunjuk ke node baru (Dr. Ani). Sekarang kedua node sudah terhubung dua arah: Dr. Budi ↔ Dr. Ani.

#### STEP 4: last(L) = P;

**Kode:**
```cpp
last(L) = P;
```

**Visualisasi Hasil Akhir:**
```
List L
┌───────┬──────┐
│ first │ last │
├───────┼──────┤
│   •───┼──────┼──•───┐
└───┼───┴──────┴──┼───┘
    │              │
    ↓              ↓
┌──────┬─────────────────────────────────┬──────┐
│ NULL │ Dr. Budi│1234567890│Algoritma   │  •───┼──┐
└──────┴─────────────────────────────────┴──────┘  │
   ↑                                                │
   │                                                ↓
┌──┼───┬─────────────────────────────────┬──────┐
│  •   │ Dr. Ani │0987654321│Database    │ NULL │
└──────┴─────────────────────────────────┴──────┘
```

**Penjelasan:**
Update pointer `last` agar menunjuk ke node baru. Sekarang Dr. Ani adalah node terakhir dalam list. Operasi insertLast selesai, list memiliki 2 elemen yang terhubung dua arah.

---

### Simulasi Lengkap: Insert 3 Dosen Berturut-turut

#### Insert 1: Dr. Budi (List Kosong)
```
SEBELUM:
List L: first = NULL, last = NULL

PROSES:
insertLast(L, Dr. Budi)
→ List kosong, masuk if
→ first(L) = P; last(L) = P;

SESUDAH:
     first & last
         ↓
    ┌────────┐
    │Dr. Budi│
    └────────┘
    NULL ← → NULL
```

#### Insert 2: Dr. Ani
```
SEBELUM:
     first & last
         ↓
    ┌────────┐
    │Dr. Budi│
    └────────┘

PROSES:
insertLast(L, Dr. Ani)
→ List tidak kosong, masuk else
→ prev(Dr. Ani) = last(L) = Dr. Budi
→ next(Dr. Budi) = Dr. Ani
→ last(L) = Dr. Ani

SESUDAH:
     first              last
       ↓                 ↓
    ┌────────┐      ┌────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │
    └────────┘      └────────┘
    NULL                   NULL
```

#### Insert 3: Dr. Citra
```
SEBELUM:
     first              last
       ↓                 ↓
    ┌────────┐      ┌────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │
    └────────┘      └────────┘

PROSES:
insertLast(L, Dr. Citra)
→ List tidak kosong, masuk else
→ prev(Dr. Citra) = last(L) = Dr. Ani
→ next(Dr. Ani) = Dr. Citra
→ last(L) = Dr. Citra

SESUDAH:
     first                          last
       ↓                             ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
    NULL                                    NULL
```

---

## 4. deleteFirst() - Menghapus Node Pertama

### Kode
```cpp
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
```

### Kasus 1: Delete dari List dengan 1 Elemen

#### Kondisi Awal
```
List L
     first & last
         ↓
    ┌────────┐
    │Dr. Budi│
    └────────┘
    NULL       NULL
```

#### STEP 1: if(first(L) != NULL)

**Kode:**
```cpp
if(first(L) != NULL) {  // true, list ada isi
```

**Penjelasan:**
Cek apakah list tidak kosong. Karena `first(L)` tidak `NULL`, maka list ada isi dan operasi delete bisa dilakukan.

#### STEP 2: P = first(L);

**Kode:**
```cpp
P = first(L);
```

**Visualisasi:**
```
List L
     first & last
         ↓
         P
         ↓
    ┌────────┐
    │Dr. Budi│
    └────────┘
```

**Penjelasan:**
Menyimpan alamat node yang akan dihapus ke pointer parameter `P`. Ini penting agar node bisa diakses di luar fungsi untuk dealokasi.

#### STEP 3: if(first(L) == last(L))

**Kode:**
```cpp
if(first(L) == last(L)) {  // true, hanya 1 node
```

**Penjelasan:**
Cek apakah hanya ada 1 node dalam list. Jika `first` dan `last` menunjuk ke node yang sama, maka list hanya memiliki 1 elemen.

#### STEP 4: first(L) = NULL; last(L) = NULL;

**Kode:**
```cpp
first(L) = NULL;
last(L) = NULL;
```

**Visualisasi:**
```
List L
┌───────┬──────┐
│ first │ last │
├───────┼──────┤
│ NULL  │ NULL │
└───────┴──────┘

         P
         ↓
    ┌────────┐
    │Dr. Budi│  (Node masih ada, siap untuk didealokasi)
    └────────┘
    NULL       NULL
```

**Penjelasan:**
Karena hanya ada 1 node, setelah dihapus list menjadi kosong. Pointer `first` dan `last` diset ke `NULL`. Node Dr. Budi masih ada di memori dan pointer `P` menyimpan alamatnya untuk dealokasi nanti.

---

### Kasus 2: Delete dari List dengan Lebih dari 1 Elemen

#### Kondisi Awal
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
    NULL                                    NULL
```

#### STEP 1: if(first(L) != NULL)

**Kode:**
```cpp
if(first(L) != NULL) {  // true
```

**Penjelasan:**
List tidak kosong, lanjutkan operasi delete.

#### STEP 2: P = first(L);

**Kode:**
```cpp
P = first(L);
```

**Visualisasi:**
```
List L
     first                          last
       ↓                             ↓
       P
       ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
```

**Penjelasan:**
Simpan alamat node pertama (Dr. Budi) ke pointer `P`.

#### STEP 3: if(first(L) == last(L))

**Kode:**
```cpp
if(first(L) == last(L)) {  // false, masuk ke else
```

**Penjelasan:**
List memiliki lebih dari 1 node, masuk ke blok else.

#### STEP 4: first(L) = next(P);

**Kode:**
```cpp
first(L) = next(P);
```

**Visualisasi:**
```
List L
                first              last
                  ↓                 ↓
       P
       ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
```

**Penjelasan:**
Pindahkan pointer `first` ke node berikutnya (Dr. Ani). Sekarang Dr. Ani menjadi node pertama dalam list.

#### STEP 5: prev(first(L)) = NULL;

**Kode:**
```cpp
prev(first(L)) = NULL;
```

**Visualisasi:**
```
List L
                first              last
                  ↓                 ↓
       P
       ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│   X  │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
                    NULL                    NULL
```

**Penjelasan:**
Set pointer `prev` dari node pertama yang baru (Dr. Ani) menjadi `NULL`. Ini memutus hubungan dari Dr. Ani ke Dr. Budi.

#### STEP 6: next(P) = NULL;

**Kode:**
```cpp
next(P) = NULL;
```

**Visualisasi Hasil Akhir:**
```
List L
                first              last
                  ↓                 ↓
                ┌────────┐      ┌─────────┐
                │Dr. Ani │ ←──→ │Dr.Citra│
                └────────┘      └─────────┘
                NULL                    NULL

       P (siap didealokasi)
       ↓
    ┌────────┐
    │Dr. Budi│
    └────────┘
    NULL       NULL
```

**Penjelasan:**
Set pointer `next` dari node yang dihapus (Dr. Budi) menjadi `NULL`. Sekarang node Dr. Budi benar-benar terpisah dari list dan siap untuk didealokasi. List sekarang dimulai dari Dr. Ani.

---

## 5. deleteLast() - Menghapus Node Terakhir

### Kode
```cpp
void deleteLast(List_dosen &L, address_dosen &P) {
    if(first(L) != NULL) {
        P = last(L);
        if(first(L) == last(L)) {
            first(L) = NULL;
            last(L) = NULL;
        } else {
            last(L) = prev(P);
            next(last(L)) = NULL;
            prev(P) = NULL;
        }
    }
}
```

### Visualisasi: Delete Last dari List dengan 3 Elemen

#### Kondisi Awal
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
    NULL                                    NULL
```

#### STEP 1: P = last(L);

**Kode:**
```cpp
P = last(L);
```

**Visualisasi:**
```
List L
     first                          last
       ↓                             ↓
                                     P
                                     ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
```

**Penjelasan:**
Simpan alamat node terakhir (Dr. Citra) ke pointer `P`.

#### STEP 2: last(L) = prev(P);

**Kode:**
```cpp
last(L) = prev(P);
```

**Visualisasi:**
```
List L
     first              last
       ↓                 ↓
                                     P
                                     ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
```

**Penjelasan:**
Pindahkan pointer `last` ke node sebelumnya (Dr. Ani). Sekarang Dr. Ani menjadi node terakhir.

#### STEP 3: next(last(L)) = NULL;

**Kode:**
```cpp
next(last(L)) = NULL;
```

**Visualisasi:**
```
List L
     first              last
       ↓                 ↓
                                     P
                                     ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │  X   │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
                            NULL
```

**Penjelasan:**
Set pointer `next` dari node terakhir yang baru (Dr. Ani) menjadi `NULL`. Ini memutus hubungan dari Dr. Ani ke Dr. Citra.

#### STEP 4: prev(P) = NULL;

**Kode:**
```cpp
prev(P) = NULL;
```

**Visualisasi Hasil Akhir:**
```
List L
     first              last
       ↓                 ↓
    ┌────────┐      ┌────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │
    └────────┘      └────────┘
    NULL                    NULL

                         P (siap didealokasi)
                         ↓
                      ┌─────────┐
                      │Dr.Citra│
                      └─────────┘
                      NULL       NULL
```

**Penjelasan:**
Set pointer `prev` dari node yang dihapus (Dr. Citra) menjadi `NULL`. Node Dr. Citra sekarang terpisah dari list dan siap untuk didealokasi.

---

## 6. deleteAfter() - Menghapus Node Setelah Node Tertentu

### Kode
```cpp
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
```

### Kasus 1: Delete Node Tengah

#### Kondisi Awal
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
       ↑
     Prec (akan hapus node setelah ini, yaitu Dr. Ani)
```

#### STEP 1: P = next(Prec);

**Kode:**
```cpp
P = next(Prec);
```

**Visualisasi:**
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
       ↑               ↑
     Prec              P (node yang akan dihapus)
```

**Penjelasan:**
Simpan alamat node yang akan dihapus (Dr. Ani) ke pointer `P`.

#### STEP 2: if(P == last(L))

**Kode:**
```cpp
if(P == last(L)) {  // false, Dr. Ani bukan node terakhir
```

**Penjelasan:**
Cek apakah node yang akan dihapus adalah node terakhir. Karena Dr. Ani bukan node terakhir (Dr. Citra yang terakhir), maka masuk ke blok else.

#### STEP 3: next(Prec) = next(P);

**Kode:**
```cpp
next(Prec) = next(P);
```

**Visualisasi:**
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐                      ┌─────────┐
    │Dr. Budi│ ────────────────────→│Dr.Citra│
    └────────┘                      └─────────┘
       ↑                                ↑
     Prec                               │
                                        │
                  ┌────────┐            │
                  │Dr. Ani │────────────┘
                  └────────┘
                     ↑
                     P
```

**Penjelasan:**
Hubungkan pointer `next` dari Prec (Dr. Budi) langsung ke node setelah P (Dr. Citra). Ini melewati node P (Dr. Ani).

#### STEP 4: prev(next(P)) = Prec;

**Kode:**
```cpp
prev(next(P)) = Prec;
```

**Visualisasi:**
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐                      ┌─────────┐
    │Dr. Budi│ ←───────────────────→│Dr.Citra│
    └────────┘                      └─────────┘
       ↑                                
     Prec                               
                                        
                  ┌────────┐            
                  │Dr. Ani │
                  └────────┘
                     ↑
                     P
```

**Penjelasan:**
Hubungkan pointer `prev` dari node setelah P (Dr. Citra) ke Prec (Dr. Budi). Sekarang Dr. Budi dan Dr. Citra terhubung dua arah, melewati Dr. Ani.

#### STEP 5: next(P) = NULL; prev(P) = NULL;

**Kode:**
```cpp
next(P) = NULL;
prev(P) = NULL;
```

**Visualisasi Hasil Akhir:**
```
List L
     first              last
       ↓                 ↓
    ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr.Citra│
    └────────┘      └─────────┘
    NULL                    NULL

       P (siap didealokasi)
       ↓
    ┌────────┐
    │Dr. Ani │
    └────────┘
    NULL       NULL
```

**Penjelasan:**
Set kedua pointer dari node yang dihapus menjadi `NULL`. Node Dr. Ani sekarang terpisah sepenuhnya dari list dan siap untuk didealokasi.

---

### Kasus 2: Delete Node Terakhir dengan deleteAfter()

#### Kondisi Awal
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
                       ↑
                     Prec (akan hapus Dr. Citra)
```

#### STEP 1: P = next(Prec);

**Kode:**
```cpp
P = next(Prec);
```

**Visualisasi:**
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
                       ↑                ↑
                     Prec               P
```

#### STEP 2: if(P == last(L))

**Kode:**
```cpp
if(P == last(L)) {  // true, Dr. Citra adalah node terakhir
```

**Penjelasan:**
Karena node yang akan dihapus adalah node terakhir, masuk ke blok if.

#### STEP 3: last(L) = Prec;

**Kode:**
```cpp
last(L) = Prec;
```

**Visualisasi:**
```
List L
     first              last
       ↓                 ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
                                        ↑
                                        P
```

**Penjelasan:**
Update pointer `last` agar menunjuk ke Prec (Dr. Ani). Sekarang Dr. Ani menjadi node terakhir.

#### STEP 4: next(Prec) = NULL;

**Kode:**
```cpp
next(Prec) = NULL;
```

**Visualisasi Hasil Akhir:**
```
List L
     first              last
       ↓                 ↓
    ┌────────┐      ┌────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │
    └────────┘      └────────┘
    NULL                    NULL

                         P (siap didealokasi)
                         ↓
                      ┌─────────┐
                      │Dr.Citra│
                      └─────────┘
                      NULL       NULL
```

**Penjelasan:**
Set pointer `next` dari Prec menjadi `NULL`. Node Dr. Citra terpisah dari list. Fungsi tidak perlu set `prev(P)` karena itu dilakukan di luar blok if.

---

## 7. findElmDosen() - Mencari Dosen Berdasarkan Nama

### Kode
```cpp
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
```

### Visualisasi: Mencari "Dr. Ani"

#### Kondisi List
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
```

#### Iterasi 1: Cek Dr. Budi

**Kode:**
```cpp
address_dosen P = first(L);
```

**Visualisasi:**
```
     P
     ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘

if(info(P).nama == "Dr. Ani")  // "Dr. Budi" == "Dr. Ani"? false
P = next(P);  // pindah ke node berikutnya
```

#### Iterasi 2: Cek Dr. Ani

**Visualisasi:**
```
                       P
                       ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘

if(info(P).nama == "Dr. Ani")  // "Dr. Ani" == "Dr. Ani"? TRUE!
return P;  // DITEMUKAN! Return alamat node Dr. Ani
```

**Hasil:**
```
findElmDosen(L, "Dr. Ani") → return alamat node Dr. Ani
```

### Contoh: Mencari Dosen yang Tidak Ada

**Mencari "Dr. Dedi":**

```
Iterasi 1: P → Dr. Budi → "Dr. Budi" != "Dr. Dedi" → lanjut
Iterasi 2: P → Dr. Ani → "Dr. Ani" != "Dr. Dedi" → lanjut
Iterasi 3: P → Dr. Citra → "Dr. Citra" != "Dr. Dedi" → lanjut
Iterasi 4: P → NULL → keluar dari loop

return NULL;  // TIDAK DITEMUKAN
```

**Penjelasan:**
Fungsi melakukan traversal dari awal sampai akhir list, membandingkan nama pada setiap node. Jika ditemukan, langsung return alamat node tersebut. Jika sampai akhir tidak ditemukan, return `NULL`.

---

## 8. findElmDosenByNIP() - Mencari Dosen Berdasarkan NIP

### Kode
```cpp
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
```

### Penjelasan
Fungsi ini identik dengan `findElmDosen()`, tetapi mencari berdasarkan NIP bukan nama. Traversal dilakukan dari `first` sampai `last`, membandingkan field `nip` pada setiap node. Return alamat node jika ditemukan, atau `NULL` jika tidak ada.

---

## 9. printInfo() - Menampilkan Semua Dosen

### Kode
```cpp
void printInfo(List_dosen L) {
    cout << endl << "=== List Dosen ===" << endl;
    int no = 1;
    address_dosen P = first(L);
    if(P != NULL) {
        while(P != NULL) {
            cout << no << ". " << info(P).nama << " (NIP: " 
                 << info(P).nip << ") - " << info(P).keahlian << endl;
            P = next(P);
            no++;
        }
    } else {
        cout << "List Dosen Kosong" << endl;
    }
}
```

### Visualisasi: Traversal untuk Print

#### Kondisi List
```
List L
     first                          last
       ↓                             ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    │1234567 │      │0987654 │      │1111111 │
    │Algoritm│      │Database│      │Jaringan│
    └────────┘      └────────┘      └─────────┘
```

#### Iterasi 1: Print Dr. Budi

**Kode:**
```cpp
address_dosen P = first(L);
int no = 1;
```

**Visualisasi:**
```
     P
     ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘

cout << no << ". " << info(P).nama ...
Output: "1. Dr. Budi (NIP: 1234567) - Algoritma"
P = next(P);
no++;
```

#### Iterasi 2: Print Dr. Ani

**Visualisasi:**
```
                       P
                       ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘

cout << no << ". " << info(P).nama ...
Output: "2. Dr. Ani (NIP: 0987654) - Database"
P = next(P);
no++;
```

#### Iterasi 3: Print Dr. Citra

**Visualisasi:**
```
                                        P
                                        ↓
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘

cout << no << ". " << info(P).nama ...
Output: "3. Dr. Citra (NIP: 1111111) - Jaringan"
P = next(P);  // P = NULL
```

#### Iterasi 4: Selesai

**Visualisasi:**
```
    ┌────────┐      ┌────────┐      ┌─────────┐
    │Dr. Budi│ ←──→ │Dr. Ani │ ←──→ │Dr.Citra│
    └────────┘      └────────┘      └─────────┘
                                            ↓
                                            P = NULL
Loop berhenti

Output lengkap:
=== List Dosen ===
1. Dr. Budi (NIP: 1234567) - Algoritma
2. Dr. Ani (NIP: 0987654) - Database
3. Dr. Citra (NIP: 1111111) - Jaringan
```

---

## 10. dealokasi_dosen() - Menghapus Node dari Memori

### Kode
```cpp
void dealokasi_dosen(address_dosen &P) {
    delete P;
    P = NULL;
}
```

### Visualisasi: Dealokasi Node

#### STEP 1: Node sebelum dealokasi

**Kondisi:**
```
       P
       ↓
    ┌────────┐
    │Dr. Budi│
    └────────┘
    NULL       NULL
```

**Penjelasan:**
Node masih ada di memori, pointer `P` menyimpan alamatnya.

#### STEP 2: delete P;

**Kode:**
```cpp
delete P;
```

**Visualisasi:**
```
       P
       ↓
    ╔════════╗
    ║   XX   ║  (Memori dikembalikan ke sistem)
    ╚════════╝
```

**Penjelasan:**
Operasi `delete` menghapus node dari memori dan mengembalikan memori ke sistem operasi. Pointer `P` masih menyimpan alamat, tetapi alamat tersebut sudah tidak valid (dangling pointer).

#### STEP 3: P = NULL;

**Kode:**
```cpp
P = NULL;
```

**Visualisasi:**
```
    P = NULL
    
    (Node sudah benar-benar tidak ada)
```

**Penjelasan:**
Set pointer `P` menjadi `NULL` untuk menghindari dangling pointer. Sekarang `P` aman dan tidak menunjuk ke memori yang tidak valid.

---
