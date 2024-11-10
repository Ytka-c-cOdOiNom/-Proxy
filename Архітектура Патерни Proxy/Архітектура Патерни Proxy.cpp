#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

// Клас для великого файлу (реальний об'єкт)
class LargeFile {
private:
    string fileName;
    string content;

public:
    LargeFile(const string& fileName) : fileName(fileName) {
        // Імітуємо завантаження великого файлу
        cout << "Завантаження файлу: " << fileName << endl;
        ifstream file(fileName);
        content = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        cout << "Файл завантажено." << endl;
    }

    void displayContent() const {
        cout << "Зміст файлу: " << content.substr(0, 100) << "..." << endl; // Виведення першої частини файлу
    }
};

// Клас Проксі
class Proxy {
private:
    LargeFile* realFile;
    string fileName;

public:
    Proxy(const string& fileName) : realFile(nullptr), fileName(fileName) {}

    ~Proxy() {
        delete realFile;
    }

    void displayContent() {
        // Якщо реальний об'єкт ще не завантажено, створюємо його
        if (!realFile) {
            realFile = new LargeFile(fileName);
        }
        realFile->displayContent();  // Викликаємо метод реального об'єкта
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створюємо проксі для доступу до великого файлу
    Proxy fileProxy("largefile.txt");

    // Тепер файл ще не завантажено, тільки коли будемо звертатися до нього
    fileProxy.displayContent();


}

