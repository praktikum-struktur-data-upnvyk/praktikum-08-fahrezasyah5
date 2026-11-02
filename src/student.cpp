// =============================================================================
// student.cpp — Implementasi Mahasiswa
// Pertemuan 8: Binary Search Tree
// =============================================================================
// FILE YANG BOLEH DIEDIT      : src/student.cpp  ← HANYA FILE INI
// FILE YANG TIDAK BOLEH DIEDIT: src/student.h, tests/checker.cpp, tests/report.h
//
// Dua fungsi lain, inorder() dan clear(), SUDAH DISEDIAKAN lengkap di bagian
// bawah file ini. Keduanya tidak dinilai — silakan dipakai untuk memeriksa
// hasil kerja Anda sendiri.
//
// -----------------------------------------------------------------------------
// NILAI DUPLIKAT DITOLAK
// -----------------------------------------------------------------------------
// Pada pertemuan ini sebuah nilai hanya boleh muncul SEKALI di dalam tree.
// Nilai yang sudah ada ditolak oleh `insert`. Dengan begitu aturan "kiri lebih
// kecil, kanan lebih besar" tidak pernah ambigu.
//
// =============================================================================

#include "student.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// =============================================================================
// SUDAH DISEDIAKAN — TIDAK DINILAI, TIDAK PERLU DIUBAH
// =============================================================================
void inorder(const Node* root) {
    if (root == nullptr) return;

    inorder(root->left);
    cout << root->data << ' ';
    inorder(root->right);
}

void clear(Node*& root) {
    if (root == nullptr) return;

    clear(root->left);
    clear(root->right);

    delete root;
    root = nullptr;
}
// =============================================================================

// =============================================================================
// SOAL 1a — insert                                                    20 poin
// =============================================================================
bool insert(Node*& root, int nilai) {
    if (root == nullptr) {
        root = new Node{nilai, nullptr, nullptr};
        return true;
    }
    if (nilai < root->data) {
        return insert(root->left, nilai);
    } else if (nilai > root->data) {
        return insert(root->right, nilai);
    } else {
        // Nilai duplikat ditolak
        return false;
    }
}

// =============================================================================
// SOAL 1b — cari                                                      15 poin
// =============================================================================
const Node* cari(const Node* root, int nilai) {
    if (root == nullptr || root->data == nilai) {
        return root;
    }
    if (nilai < root->data) {
        return cari(root->left, nilai);
    }
    return cari(root->right, nilai);
}

// =============================================================================
// SOAL 2a — minimum                                                   10 poin
// =============================================================================
const Node* minimum(const Node* root) {
    if (root == nullptr) return nullptr;
    if (root->left == nullptr) return root;
    return minimum(root->left);
}

// =============================================================================
// SOAL 2b — hapus                                                     30 poin
// =============================================================================
bool hapus(Node*& root, int nilai) {
    if (root == nullptr) return false;

    if (nilai < root->data) {
        return hapus(root->left, nilai);
    } else if (nilai > root->data) {
        return hapus(root->right, nilai);
    } else {
        // Node ditemukan
        // Keadaan 1 & 2: Tidak punya anak atau hanya punya 1 anak
        if (root->left == nullptr) {
            Node* temp = root;
            root = root->right;
            delete temp;
            return true;
        } else if (root->right == nullptr) {
            Node* temp = root;
            root = root->left;
            delete temp;
            return true;
        }

        // Keadaan 3: Punya 2 anak
        // Ambil nilai terkecil dari subtree kanan (inorder successor)
        const Node* succ = minimum(root->right);
        root->data = succ->data;
        // Hapus successor yang lama dari subtree kanan
        return hapus(root->right, succ->data);
    }
}

// =============================================================================
// SOAL 3 — termahalTerbeli                                             25 poin
// =============================================================================
const Node* termahalTerbeli(const Node* root, int uang) {
    const Node* terbaik = nullptr;
    const Node* curr = root;

    while (curr != nullptr) {
        if (curr->data == uang) {
            return curr; // Persis sama, langsung kembalikan karena ini yang paling maksimal yang pas
        } else if (curr->data < uang) {
            terbaik = curr;        // Masih terjangkau, simpan sebagai kandidat terbaik sementara
            curr = curr->right;    // Cari yang lebih mahal di sebelah kanan
        } else {
            curr = curr->left;     // Kemahalan, cari yang lebih murah di sebelah kiri
        }
    }

    return terbaik;
}

// =============================================================================
// MAIN() — program Anda sendiri. TIDAK dinilai, bebas diubah.
// =============================================================================
// Di bawah ini file ini menjadi program C++ biasa. Tekan Run di VS Code, atau
// jalankan lewat terminal:
//
//     g++ -std=c++17 src/student.cpp -o latihan
//     ./latihan
//
// SATU ATURAN YANG TIDAK BOLEH DILANGGAR
// --------------------------------------
// cin hanya boleh dipakai DI DALAM main() ini. JANGAN menaruh cin di dalam
// kelima fungsi yang dinilai. Saat menilai, checker memanggil fungsi-fungsi itu
// tanpa memberi masukan apa pun, jadi cin di sana akan membaca sampah — dan
// nilai Anda berubah-ubah setiap kali dinilai, dari kode yang sama persis.
// =============================================================================

#ifndef ADA_MAIN_LAIN

// -----------------------------------------------------------------------------
// Pembantu tampilan di bawah ini hanya merapikan keluaran. Boleh Anda ubah atau
// hapus.
// -----------------------------------------------------------------------------

// Menulis satu baris keterangan dengan lebar label yang seragam.
static ostream& baris(const string& label) {
    return cout << "    " << left << setw(22) << label << ": ";
}

static const char* benarSalah(bool nilai) {
    return nilai ? "true" : "false";
}

// Menampilkan isi node yang dikembalikan sebuah fungsi, atau "(tidak ada)" bila
// fungsinya mengembalikan nullptr.
static void tampilkanNode(const string& label, const Node* n) {
    baris(label);
    if (n == nullptr) cout << "(tidak ada)\n";
    else              cout << n->data << "\n";
}

// Menampilkan seluruh isi tree memakai inorder() yang sudah disediakan.
static void tampilkanIsi(const string& label, const Node* root) {
    baris(label);
    inorder(root);
    cout << "\n";
}

int main() {
    cout << "==========================================\n";
    cout << " Latihan — Binary Search Tree\n";
    cout << " (bagian ini tidak ikut dinilai)\n";
    cout << "==========================================\n";

    // -------------------------------------------------------------------------
    // Soal 1a — membangun tree dengan insert(), persis Kegiatan 5.1 pada modul.
    // -------------------------------------------------------------------------
    cout << "\n[1] Soal 1a — insert(): memasukkan 50, 30, 70, 20, 40, 60, 80\n";

    Node* root = nullptr;
    const int masuk[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; ++i) {
        insert(root, masuk[i]);
    }

    tampilkanIsi("inorder", root);
    cout << "\n";
    cout << "    Yang benar: 20 30 40 50 60 70 80\n";
    cout << "    Bentuk tree yang seharusnya terbentuk:\n";
    cout << "\n";
    cout << "              50\n";
    cout << "             /  \\\n";
    cout << "           30    70\n";
    cout << "          /  \\   / \\\n";
    cout << "         20  40 60   80\n";

    // -------------------------------------------------------------------------
    // Soal 1a — nilai duplikat harus ditolak.
    // -------------------------------------------------------------------------
    cout << "\n[2] Soal 1a — insert() menolak duplikat\n";
    baris("insert 55 (baru)") << benarSalah(insert(root, 55)) << "\n";
    baris("insert 40 (sudah ada)") << benarSalah(insert(root, 40)) << "\n";
    tampilkanIsi("inorder", root);
    cout << "\n    Yang benar: true, false, lalu 20 30 40 50 55 60 70 80\n";

    // -------------------------------------------------------------------------
    // Soal 1b — pencarian.
    // -------------------------------------------------------------------------
    cout << "\n[3] Soal 1b — cari()\n";
    tampilkanNode("cari 60 (ada)", cari(root, 60));
    tampilkanNode("cari 20 (paling kiri)", cari(root, 20));
    tampilkanNode("cari 25 (tidak ada)", cari(root, 25));
    tampilkanNode("cari pada tree kosong", cari(nullptr, 10));
    cout << "\n    Yang benar: 60, 20, (tidak ada), (tidak ada)\n";

    // -------------------------------------------------------------------------
    // Soal 2a — nilai terkecil, pada seluruh tree dan pada subtree.
    // -------------------------------------------------------------------------
    cout << "\n[4] Soal 2a — minimum()\n";
    tampilkanNode("minimum seluruh tree", minimum(root));
    if (root != nullptr) {
        tampilkanNode("minimum subtree kanan", minimum(root->right));
    }
    tampilkanNode("minimum tree kosong", minimum(nullptr));
    cout << "\n    Yang benar: 20, 55, (tidak ada)\n";

    // -------------------------------------------------------------------------
    // Soal 3 — soal cerita. Dipakai sebelum tree diubah oleh hapus().
    // -------------------------------------------------------------------------
    cout << "\n[5] Soal 3 — termahalTerbeli()\n";
    cout << "    Harga yang tersedia sekarang: ";
    inorder(root);
    cout << "\n";
    tampilkanNode("uang 65", termahalTerbeli(root, 65));
    tampilkanNode("uang 30 (pas)", termahalTerbeli(root, 30));
    tampilkanNode("uang 45", termahalTerbeli(root, 45));
    tampilkanNode("uang 99", termahalTerbeli(root, 99));
    tampilkanNode("uang 15 (kurang)", termahalTerbeli(root, 15));
    cout << "\n    Yang benar: 60, 30, 40, 80, (tidak ada)\n";

    // -------------------------------------------------------------------------
    // Soal 2b — ketiga keadaan penghapusan, satu per satu.
    // -------------------------------------------------------------------------
    cout << "\n[6] Soal 2b — hapus(), ketiga keadaannya\n";

    // Node 20 adalah daun: tidak punya cabang sama sekali.
    baris("hapus 20 (0 child)") << benarSalah(hapus(root, 20)) << "\n";
    tampilkanIsi("  inorder", root);

    // Node 60 sekarang hanya punya cabang kiri, yaitu 55.
    baris("hapus 60 (1 child)") << benarSalah(hapus(root, 60)) << "\n";
    tampilkanIsi("  inorder", root);

    // Node 50 adalah root dan punya dua cabang. Penggantinya nilai terkecil
    // pada cabang kanan, yaitu 55.
    baris("hapus 50 (2 child)") << benarSalah(hapus(root, 50)) << "\n";
    tampilkanIsi("  inorder", root);

    baris("hapus 25 (tidak ada)") << benarSalah(hapus(root, 25)) << "\n";
    tampilkanIsi("  inorder", root);

    cout << "\n    Yang benar, berurutan:\n";
    cout << "      true  -> 30 40 50 55 60 70 80\n";
    cout << "      true  -> 30 40 50 55 70 80\n";
    cout << "      true  -> 30 40 55 70 80\n";
    cout << "      false -> 30 40 55 70 80   (tidak berubah)\n";

    cout << "\n==========================================\n";
    cout << " Selesai. Silakan ubah bagian ini untuk\n";
    cout << " mencoba percobaan Anda sendiri.\n";
    cout << "==========================================\n";

    // Seluruh node dibebaskan sebelum program berakhir.
    clear(root);
    return 0;
}
#endif