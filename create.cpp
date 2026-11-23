
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdio>

using namespace std;

// Запись всех данных в файл
bool writeAll(int fd, const char* data, int size) {
    int written = 0;

    while (written < size) {
        ssize_t result = write(fd, data + written, size - written);

        if (result <= 0) {
            return false;
        }

        written += result;
    }

    return true;
}

// Создание текстового файла
bool createTextFile(const char* path, const char* text) {
    int fd = open(path, O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);

    if (fd == -1) {
        perror("open");
        return false;
    }

    int size = 0;

    while (text[size] != '\0') {
        size++;
    }

    bool result = writeAll(fd, text, size);

    if (close(fd) == -1) {
        perror("close");
        return false;
    }

    return result;
}

// Создание пустого файла
bool createEmptyFile(const char* path) {
    int fd = open(path, O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);

    if (fd == -1) {
        perror("open");
        return false;
    }

    return close(fd) == 0;
}

// Создание файла со случайными данными
bool createRandomFile(const char* path, int size) {
    int randomFd = open("/dev/urandom", O_RDONLY);

    if (randomFd == -1) {
        perror("open /dev/urandom");
        return false;
    }

    int fileFd = open(path, O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);

    if (fileFd == -1) {
        perror("open random file");
        close(randomFd);
        return false;
    }

    char buffer[128];
    int total = 0;
    bool success = true;

    while (total < size) {
        int need = size - total;

        if (need > 128) {
            need = 128;
        }

        ssize_t count = read(randomFd, buffer, need);

        if (count <= 0) {
            success = false;
            break;
        }

        if (!writeAll(fileFd, buffer, count)) {
            success = false;
            break;
        }

        total += count;
    }

    if (close(randomFd) == -1) success = false;
    if (close(fileFd) == -1) success = false;

    return success;
}

// Создание файла, заполненного нулями
bool createZeroFile(const char* path, int size) {
    int fd = open(path, O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);

    if (fd == -1) {
        perror("open zero file");
        return false;
    }

    char zeros[64] = {0};
    int total = 0;
    bool success = true;

    while (total < size) {
        int count = size - total;

        if (count > 64) {
            count = 64;
        }

        if (!writeAll(fd, zeros, count)) {
            success = false;
            break;
        }

        total += count;
    }

    if (close(fd) == -1) success = false;

    return success;
}

int main() {

    // Создание основного каталога
    if (mkdir("Lab1_Amira", S_IRWXU) == -1) {
        perror("mkdir Lab1_Amira");
        return 1;
    }

    // Создание вложенных каталогов
    if (mkdir("Lab1_Amira/Documents", S_IRWXU) == -1 ||
        mkdir("Lab1_Amira/Data", S_IRWXU) == -1 ||
        mkdir("Lab1_Amira/Archive", S_IRWXU) == -1) {
        perror("mkdir");
        return 1;
    }

    // Создание обычных файлов
    if (!createTextFile("Lab1_Amira/Documents/notes.txt",
                        "System programming\n") ||
        !createEmptyFile("Lab1_Amira/Documents/empty.txt") ||
        !createRandomFile("Lab1_Amira/Data/random.bin", 128) ||
        !createZeroFile("Lab1_Amira/Data/zeros.bin", 64)) {

        cerr << "Ошибка создания файлов!" << endl;
        return 1;
    }

    // Создание жесткой ссылки
    if (link("Lab1_Amira/Documents/notes.txt",
             "Lab1_Amira/Archive/notes_copy.txt") == -1) {
        perror("link");
        return 1;
    }

    // Создание символьной ссылки
    if (symlink("Documents", "Lab1_Amira/Documents_link") == -1) {
        perror("symlink");
        return 1;
    }

    cout << "Структура каталогов успешно создана!" << endl;

    return 0;
}
