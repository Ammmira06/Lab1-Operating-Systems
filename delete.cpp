
#include <iostream>
#include <unistd.h>
#include <cstdio>

using namespace std;

// Удаление файла или ссылки
bool removeFile(const char* path) {
    if (unlink(path) == -1) {
        perror(path);
        return false;
    }

    cout << "Удален файл: " << path << endl;
    return true;
}

// Удаление пустого каталога
bool removeDirectory(const char* path) {
    if (rmdir(path) == -1) {
        perror(path);
        return false;
    }

    cout << "Удален каталог: " << path << endl;
    return true;
}

int main() {

    bool success = true;

    // Удаление файлов и ссылок
    if (!removeFile("Lab1_Amira/Documents/notes.txt"))
        success = false;

    if (!removeFile("Lab1_Amira/Documents/empty.txt"))
        success = false;

    if (!removeFile("Lab1_Amira/Data/random.bin"))
        success = false;

    if (!removeFile("Lab1_Amira/Data/zeros.bin"))
        success = false;

    if (!removeFile("Lab1_Amira/Archive/notes_copy.txt"))
        success = false;

    if (!removeFile("Lab1_Amira/Documents_link"))
        success = false;

    // Удаление пустых каталогов
    if (!removeDirectory("Lab1_Amira/Documents"))
        success = false;

    if (!removeDirectory("Lab1_Amira/Data"))
        success = false;

    if (!removeDirectory("Lab1_Amira/Archive"))
        success = false;

    if (!removeDirectory("Lab1_Amira"))
        success = false;

    if (success) {
        cout << "\nСтруктура успешно удалена!" << endl;
        return 0;
    }

    cerr << "\nПри удалении возникли ошибки!" << endl;
    return 1;
}
