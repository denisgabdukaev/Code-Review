#include "HeaderTask03.h"
#include <locale>

//FIX_ME: запрещается использование 
//using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    try
    {
        FLinkedList List; // Создаем список

        // Чтение данных из файла
        ReadFromFile(List, "InputFile.txt");

        // Вывод упорядоченного списка
        std::cout << "Упорядоченный список: ";
        List.Print();
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Ошибка: " << Exception.what() << std::endl;
        return 1;
    }

    return 0;
}