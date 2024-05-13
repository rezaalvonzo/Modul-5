#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Mahasiswa {
    string nim;
    int nilai;
};

const int hashTableSize = 100;

class HashTable {
private:
    vector<list<Mahasiswa>> table;

    int hashFunction(const string& key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % hashTableSize;
    }

public:
    HashTable() {
        table.resize(hashTableSize);
    }

    void tambahData(const string& nim, int nilai) {
        Mahasiswa mahasiswa;
        mahasiswa.nim = nim;
        mahasiswa.nilai = nilai;
        int index = hashFunction(nim);
        table[index].push_back(mahasiswa);
    }

    void hapusData(const string& nim) {
        int index = hashFunction(nim);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it).nim == nim) {
                table[index].erase(it);
                break;
            }
        }
    }

    void cariByNIM(const string& nim) {
        int index = hashFunction(nim);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it).nim == nim) {
                cout << "Data ditemukan - NIM: " << (*it).nim << ", Nilai: " << (*it).nilai << endl;
                return;
            }
        }
        cout << "Data tidak ditemukan" << endl;
    }

    void cariByRange() {
        for (int i = 0; i < hashTableSize; ++i) {
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                if ((*it).nilai >= 80 && (*it).nilai <= 90) {
                    cout << "NIM: " << (*it).nim << ", Nilai: " << (*it).nilai << endl;
                }
            }
        }
    }
};

int main() {
    HashTable hashTable;
    int choice, nilai;
    string nim;

    do {
        cout << "\nMenu:\n";
        cout << "1. Menambah Data\n";
        cout << "2. Menghapus Data\n";
        cout << "3. Cari mahasiswa menggunakan NIM\n";
        cout << "4. Cari Nilai (80 - 90)\n";
        cout << "Masukkan Pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan NIM: ";
                cin >> nim;
                cout << "Masukkan Nilai: ";
                cin >> nilai;
                hashTable.tambahData(nim, nilai);
                break;
            case 2:
                cout << "Masukkan NIM untuk dihapus: ";
                cin >> nim;
                hashTable.hapusData(nim);
                break;
            case 3:
                cout << "Masukkan NIM yang ingin dicari: ";
                cin >> nim;
                hashTable.cariByNIM(nim);
                break;
            case 4:
                cout << "Mahasiswa dengan nilai antara 80 - 90:\n";
                hashTable.cariByRange();
                break;
            default:
                cout << "Pilihan tidak ada dalam Menu.\n";
        }
    } while (choice != 4);

    return 0;
}
