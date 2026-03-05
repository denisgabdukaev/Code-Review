#include "HeaderTask03.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        int Base;
        int DigitCount;

        // Ввод основания системы счисления
        std::cout << "Введите основание системы счисления K (2-10): ";
        if (!(std::cin >> Base))
        {
            throw std::runtime_error("Ошибка: Не удалось прочитать основание системы счисления");
        }

        // Ввод количества разрядов
        std::cout << "Введите количество разрядов N (1 < N < 20): ";
        if (!(std::cin >> DigitCount))
        {
            throw std::runtime_error("Ошибка: Не удалось прочитать количество разрядов");
        }

        // Проверка корректности входных данных
        std::string ErrorMessage;
        if (!ValidateInput(Base, DigitCount, ErrorMessage))
        {
            throw std::runtime_error(ErrorMessage);
        }

        // Вычисление результата
        double Result = CountValidNumbers(Base, DigitCount);

        // Вывод результата
        std::cout << "Количество допустимых чисел: " << Result << std::endl;
    }
    catch (const std::runtime_error& Exception)
    {
        std::cerr << Exception.what() << std::endl;
        return 1;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Неизвестная ошибка: " << Exception.what() << std::endl;
        return 2;
    }

    return 0;
}