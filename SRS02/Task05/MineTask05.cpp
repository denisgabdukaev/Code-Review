#include "HeaderTask05.h"
#include <locale>

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        int Size1, Size2, Size3;
        std::vector<int> Vector;
        std::deque<int> Deque;
        std::list<int> List;

        // Ввод размеров контейнеров
        std::cout << "=== Ввод размеров контейнеров ===" << std::endl;
        std::cout << "Все размеры должны быть >= 2 и четными." << std::endl;

        // Ввод для вектора
        while (true)
        {
            try
            {
                Size1 = ReadInteger("Введите размерность вектора n1: ");

                if (IsValidSize(Size1))
                {
                    break;
                }

                std::cout << "Некорректный размер. Попробуйте снова." << std::endl;
            }
            catch (const FContainerException& Exception)
            {
                std::cout << "Ошибка: " << Exception.what() << std::endl;
            }
        }

        // Ввод для дека
        while (true)
        {
            try
            {
                Size2 = ReadInteger("Введите размерность дека n2: ");

                if (IsValidSize(Size2))
                {
                    break;
                }

                std::cout << "Некорректный размер. Попробуйте снова." << std::endl;
            }
            catch (const FContainerException& Exception)
            {
                std::cout << "Ошибка: " << Exception.what() << std::endl;
            }
        }

        // Ввод для списка
        while (true)
        {
            try
            {
                Size3 = ReadInteger("Введите размерность списка n3: ");

                if (IsValidSize(Size3))
                {
                    break;
                }

                std::cout << "Некорректный размер. Попробуйте снова." << std::endl;
            }
            catch (const FContainerException& Exception)
            {
                std::cout << "Ошибка: " << Exception.what() << std::endl;
            }
        }

        // Заполнение контейнеров
        std::cout << "\n=== Заполнение вектора ===" << std::endl;
        InputContainer(Vector, Size1);

        std::cout << "\n=== Заполнение дека ===" << std::endl;
        InputContainer(Deque, Size2);

        std::cout << "\n=== Заполнение списка ===" << std::endl;
        InputContainer(List, Size3);

        // Вывод исходных контейнеров
        std::cout << "\n=== Исходное содержимое контейнеров ===" << std::endl;

        std::cout << "Вектор: ";
        PrintContainer(Vector);

        std::cout << "Дек: ";
        PrintContainer(Deque);

        std::cout << "Список: ";
        PrintContainer(List);

        // Обмен средних элементов
        SwapMiddleElements(Vector);
        SwapMiddleElements(Deque);
        SwapMiddleElements(List);

        // Вывод измененных контейнеров
        std::cout << "\n=== Измененное содержимое контейнеров ===" << std::endl;

        std::cout << "Вектор: ";
        PrintContainer(Vector);

        std::cout << "Дек: ";
        PrintContainer(Deque);

        std::cout << "Список: ";
        PrintContainer(List);
    }
    catch (const FContainerException& Exception)
    {
        std::cerr << "Ошибка контейнера: " << Exception.what() << std::endl;
        return 1;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Неизвестная ошибка: " << Exception.what() << std::endl;
        return 2;
    }

    std::cout << "      /\\     /\\  " << std::endl;
    std::cout << "     {  `---'  } " << std::endl;
    std::cout << "     {  O   O  } " << std::endl;
    std::cout << "     ~~>  V  <~~ " << std::endl;

    return 0;
}