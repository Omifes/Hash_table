#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 101;

    struct Node {
        const char* key;
        bool isDeleted;

        Node() : key(nullptr), isDeleted(false) {}
        Node(const char* k) : key(k), isDeleted(false) {}
    };

    Node* table_;
    int size_;

    int hashFunction(const char* key) const {
        unsigned int hash = 0;
        while (*key) {
            hash = (hash * 31 + *key++) % TABLE_SIZE;
        }
        return hash;
    }

    int findIndex(const char* key, bool forInsert = false) const {
        int index = hashFunction(key);
        int startIndex = index;
        int firstDeleted = -1;

        while (true) {
            if (table_[index].key == nullptr) {
                if (forInsert && firstDeleted != -1) {
                    return firstDeleted;
                }
                return index;
            }

            if (strcmp(table_[index].key, key) == 0 && !table_[index].isDeleted) {
                return index;
            }

            if (table_[index].isDeleted && firstDeleted == -1) {
                firstDeleted = index;
            }

            index = (index + 1) % TABLE_SIZE;

            if (index == startIndex) {
                return forInsert ? firstDeleted : -1;
            }
        }
    }

public:
    HashTable() : size_(0) {
        table_ = new Node[TABLE_SIZE];
    }

    ~HashTable() {
        delete[] table_;
    }

    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;

    bool insert(const char* key) {
        if (size_ >= TABLE_SIZE * 0.7) {
            return false;
        }

        int index = findIndex(key, true);
        if (index == -1) {
            return false;
        }

        if (table_[index].key != nullptr && strcmp(table_[index].key, key) == 0 && !table_[index].isDeleted) {
            return false;
        }

        table_[index].key = key;
        table_[index].isDeleted = false;
        size_++;
        return true;
    }

    bool remove(const char* key) {
        int index = findIndex(key);
        if (index == -1 || table_[index].key == nullptr || table_[index].isDeleted) {
            return false;
        }

        table_[index].isDeleted = true;
        size_--;
        return true;
    }

    bool contains(const char* key) const {
        int index = findIndex(key);
        return index != -1 && table_[index].key != nullptr && !table_[index].isDeleted;
    }

    void printByHash(int hashValue) const {
        if (hashValue < 0 || hashValue >= TABLE_SIZE) {
            cout << "Invalid hash value" << endl;
            return;
        }

        cout << "Elements with hash " << hashValue << ":" << endl;
        bool found = false;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (hashFunction(table_[i].key) == hashValue &&
                table_[i].key != nullptr && !table_[i].isDeleted) {
                cout << table_[i].key << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No elements found" << endl;
        }
    }

    void printAll() const {
        cout << "Hash table contents (" << size_ << " elements):" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table_[i].key != nullptr && !table_[i].isDeleted) {
                cout << "[" << i << "]: " << table_[i].key
                    << " (hash: " << hashFunction(table_[i].key) << ")" << endl;
            }
        }
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }
};

#endif // HASHTABLE_H