#include "../include/dosen.h"
#include "../include/mahasiswa.h"
#include "../include/relasi.h"

void injectData(List_dosen &LD, List_mahasiswa &LM, address_relasi &firstRel) {
    cout << endl << "=== MEMULAI INJECT DATA OTOMATIS ===" << endl;
    
    // Inject Data Dosen
    cout << "Menambahkan data dosen..." << endl;
    address_dosen D1 = alokasi_dosen("Dr. Budi Santoso", "198501012010121001", "Artificial Intelligence");
    address_dosen D2 = alokasi_dosen("Prof. Siti Nurhaliza", "197803152005012001", "Data Science");
    address_dosen D3 = alokasi_dosen("Dr. Ahmad Hidayat", "198209202008011002", "Software Engineering");
    address_dosen D4 = alokasi_dosen("Dr. Rina Kusuma", "199001052012012001", "Computer Networks");
    address_dosen D5 = alokasi_dosen("Dr. Joko Widodo", "198512102009121001", "Database Systems");
    
    insertLast(LD, D1);
    insertLast(LD, D2);
    insertLast(LD, D3);
    insertLast(LD, D4);
    insertLast(LD, D5);
    
    // Inject Data Mahasiswa
    cout << "Menambahkan data mahasiswa..." << endl;
    address_mahasiswa M1 = alokasi_mahasiswa("Andi Pratama", "1301210001", "Sistem Prediksi Cuaca Menggunakan Machine Learning");
    address_mahasiswa M2 = alokasi_mahasiswa("Budi Setiawan", "1301210002", "Aplikasi E-Commerce Berbasis Mobile");
    address_mahasiswa M3 = alokasi_mahasiswa("Citra Dewi", "1301210003", "Analisis Sentimen Media Sosial dengan Deep Learning");
    address_mahasiswa M4 = alokasi_mahasiswa("Deni Irawan", "1301210004", "Sistem Keamanan Jaringan IoT");
    address_mahasiswa M5 = alokasi_mahasiswa("Eka Putri", "1301210005", "Optimasi Query Database dengan Indexing");
    address_mahasiswa M6 = alokasi_mahasiswa("Fajar Nugroho", "1301210006", "Chatbot Customer Service Menggunakan NLP");
    address_mahasiswa M7 = alokasi_mahasiswa("Gita Sari", "1301210007", "Sistem Deteksi Penyakit Tanaman");
    address_mahasiswa M8 = alokasi_mahasiswa("Hendra Kusuma", "1301210008", "Aplikasi Monitoring Kesehatan Realtime");
    
    insertFirst(LM, M1);
    insertFirst(LM, M2);
    insertFirst(LM, M3);
    insertFirst(LM, M4);
    insertFirst(LM, M5);
    insertFirst(LM, M6);
    insertFirst(LM, M7);
    insertFirst(LM, M8);
    
    // Inject Relasi Dosen-Mahasiswa
    cout << "Menghubungkan dosen dan mahasiswa..." << endl;
    
    // M1: Andi - Dosen: D1 (Budi Santoso), D2 (Siti Nurhaliza)
    connect(D1, M1, firstRel);
    connect(D2, M1, firstRel);
    
    // M2: Budi - Dosen: D3 (Ahmad Hidayat)
    connect(D3, M2, firstRel);
    
    // M3: Citra - Dosen: D1 (Budi Santoso), D2 (Siti Nurhaliza)
    connect(D1, M3, firstRel);
    connect(D2, M3, firstRel);
    
    // M4: Deni - Dosen: D4 (Rina Kusuma)
    connect(D4, M4, firstRel);
    
    // M5: Eka - Dosen: D5 (Joko Widodo), D2 (Siti Nurhaliza)
    connect(D5, M5, firstRel);
    connect(D2, M5, firstRel);
    
    // M6: Fajar - Dosen: D1 (Budi Santoso)
    connect(D1, M6, firstRel);
    
    // M7: Gita - Dosen: D1 (Budi Santoso), D3 (Ahmad Hidayat)
    connect(D1, M7, firstRel);
    connect(D3, M7, firstRel);
    
    // M8: Hendra - Dosen: D4 (Rina Kusuma), D5 (Joko Widodo)
    connect(D4, M8, firstRel);
    connect(D5, M8, firstRel);
    
    cout << endl << ">>> DATA BERHASIL DI-INJECT <<<" << endl;
    cout << "Total Dosen: 5" << endl;
    cout << "Total Mahasiswa: 8" << endl;
    cout << "Total Relasi Bimbingan: 14" << endl;
}