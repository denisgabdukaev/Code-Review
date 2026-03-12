#include "HeaderTask01.h"
#include <locale>
#include <limits>

int main()
{
    setlocale(LC_ALL, "ru");

    try
    {
        FStack Stack;
        int Choice;
        int Value;

        while (true)
        {
            std::cout << "\nМеню:\n";
            std::cout << "1. Добавить элемент в стек\n";
            std::cout << "2. Удалить элемент из стека\n";
            std::cout << "3. Вывести элементы стека\n";
            std::cout << "4. Очистить стек\n";
            std::cout << "5. Выйти\n";
            std::cout << "Введите ваш выбор: ";

            if (!ReadInteger(Choice))
            {
                std::cout << "Ошибка ввода! Пожалуйста, введите число." << std::endl;
                continue;
            }

            switch (Choice)
            {
            case 1:
                std::cout << "Введите число для добавления в стек: ";
                if (!ReadInteger(Value))
                {
                    std::cout << "Ошибка ввода! Пожалуйста, введите число." << std::endl;
                    break;
                }

                try
                {
                    AddElementAndPrintAddress(Stack, Value);
                }
                catch (const FStackException& Exception)
                {
                    std::cout << "Ошибка при добавлении элемента: " << Exception.what() << std::endl;
                }
                break;

            case 2:
                try
                {
                    Stack.Pop();
                }
                catch (const FStackException& Exception)
                {
                    std::cout << Exception.what() << std::endl;
                }
                break;

            case 3:
                Stack.Print();
                break;

            case 4:
                Stack.ClearStack();
                break;

            case 5:
                std::cout << "Выход из программы." << std::endl;
                return 0;

            default:
                std::cout << "Неверный выбор! Пожалуйста, попробуйте снова." << std::endl;
            }
        }
    }
    catch (const FStackException& Exception)
    {
        std::cerr << "Критическая ошибка стека: " << Exception.what() << std::endl;
        return 1;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Неизвестная ошибка: " << Exception.what() << std::endl;
        return 2;
    }

    return 0;
}