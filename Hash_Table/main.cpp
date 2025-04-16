#include "HashTable.h"
#include <iostream>

using namespace std;

void testInsert(HashTable& ht);
void testRemove(HashTable& ht);
void testContains(const HashTable& ht);
void testPrintAll(const HashTable& ht);

int main() {
    HashTable ht;

    cout << "Insert Test" << endl;
    testInsert(ht);

    cout << "\nContains Test\n" << endl;
    testContains(ht);

    cout << "\nRemove Test\n" << endl;
    testRemove(ht);

    cout << "\nPrint All\n" << endl;
    testPrintAll(ht);

    return 0;
}

void testInsert(HashTable& ht) {
    const char* keys[] = { "abc", "123", "fkj", "abc", "x7y" };

    for (const char* key : keys) {
        bool success = ht.insert(key);
        cout << "Insert '" << key << "': "
            << (success ? "OK" : "FAIL (duplicate/full)") << endl;
    }
}

void testRemove(HashTable& ht) {
    const char* keys[] = { "123", "zzz", "abc" };

    for (const char* key : keys) {
        bool success = ht.remove(key);
        cout << "Remove '" << key << "': "
            << (success ? "OK" : "FAIL (not found)") << endl;
    }
}

void testContains(const HashTable& ht) {
    const char* keys[] = { "abc", "123", "fkj", "x7y", "zzz" };

    for (const char* key : keys) {
        bool exists = ht.contains(key);
        cout << "Key '" << key << "': "
            << (exists ? "FOUND" : "NOT FOUND") << endl;
    }
}

void testPrintAll(const HashTable& ht) {
    cout << "All Elements" << endl;
    ht.printAll();
    cout << "Total size: " << ht.size() << endl;
}