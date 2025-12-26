#include "include/dosen.h"
#include "include/mahasiswa.h"
#include "include/relasi.h"

void pilihMode(List_dosen &LD, List_mahasiswa &LM, address_relasi &firstRel);

int main() {
    List_dosen LD;
    List_mahasiswa LM;
    address_relasi firstRel = NULL;
    
    createList(LD);
    createList(LM);
    
    pilihMode(LD, LM, firstRel);
    
    return 0;
}