
#!/bin/bash

# Создание основного каталога
mkdir Lab1_Amira

# Переход в основной каталог
cd Lab1_Amira

# Создание вложенных каталогов
mkdir Documents Data Archive

# Создание текстового файла
echo "System programming" > Documents/notes.txt

# Создание пустого файла
touch Documents/empty.txt

# Создание файла со случайными данными
head -c 128 /dev/urandom > Data/random.bin

# Создание файла, заполненного нулями
head -c 64 /dev/zero > Data/zeros.bin

# Создание жесткой ссылки
ln Documents/notes.txt Archive/notes_copy.txt

# Создание символьной ссылки
ln -s Documents Documents_link

echo "Структура каталогов успешно создана!"
