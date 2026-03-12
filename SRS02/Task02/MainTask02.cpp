#include "HeaderTask02.h"
#include <locale>
#include <limits>
#include <string>

int main()
{
    setlocale(LC_ALL, "ru");

    try
    {
        FQueue Queue;
        std::string InputString;
        int ElementCount;
        int Value;

        // Ввод количества элементов
        std::cout << "Введите количество элементов в очереди: ";
        std::cin >> InputString;

        if (!IsNumber(InputString))
        {
            throw FQueueException("Недопустимое значение для количества элементов");
        }

        ElementCount = std::stoi(InputString);

        if (ElementCount <= 0)
        {
            throw FQueueException("Количество элементов должно быть положительным числом");
        }

        // Ввод элементов очереди
        std::cout << "Введите элементы очереди: ";
        for (int i = 1; i <= ElementCount; ++i)
        {
            std::cin >> InputString;

            if (!IsNumber(InputString))
            {
                throw FQueueException("Недопустимое значение для элемента очереди");
            }

            Value = std::stoi(InputString);
            Queue.Push(Value);
        }

        // Вывод исходной очереди
        std::cout << "Изначальная очередь: ";
        Queue.Show();

        // Обработка четности головы
        Queue.ProcessEvenHead();

        // Вывод измененной очереди
        std::cout << "Измененная очередь: ";
        Queue.Show();

        // Вывод информации о начале очереди
        if (!Queue.IsEmpty())
        {
            try
            {
                std::cout << "Значение первого элемента: " << Queue.GetHeadValue() << std::endl;
            }
            catch (const FQueueException& Exception)
            {
                std::cout << "Ошибка при получении значения головы: " << Exception.what() << std::endl;
            }

            std::cout << "Новый адрес начала очереди (P1): " << Queue.GetHead() << std::endl;

            try
            {
                std::cout << "Значение последнего элемента: " << Queue.GetTailValue() << std::endl;
            }
            catch (const FQueueException& Exception)
            {
                std::cout << "Ошибка при получении значения хвоста: " << Exception.what() << std::endl;
            }

            std::cout << "Новый адрес конца очереди (P2): " << Queue.GetTail() << std::endl;
        }
        else
        {
            std::cout << "Очередь пуста" << std::endl;
            std::cout << "Новый адрес начала очереди (P1): nullptr" << std::endl;
            std::cout << "Новый адрес конца очереди (P2): nullptr" << std::endl;
        }
    }
    catch (const FQueueException& Exception)
    {
        std::cerr << "Ошибка: " << Exception.what() << std::endl;
        return 1;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Неизвестная ошибка: " << Exception.what() << std::endl;
        return 2;
    }

    return 0;
}