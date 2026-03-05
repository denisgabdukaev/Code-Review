#include "HeaderTask04.h"

//FIX_ME: некорректное расположение скобок
//int main() {
int main()
{
    setlocale(LC_ALL, "RU");

    try
    {
        //FIX_ME: некорректное название переменной
        //string s;
        std::string InputString;

        std::cout << "Введите выражение:" << std::endl;
        std::cin >> InputString;

        // Проверка на пустую строку
        if (InputString.empty())
        {
            throw std::runtime_error("Ошибка: Введена пустая строка");
        }

        // Проверка на наличие пробелов с использованием рекурсивной функции (без циклов)
        if (CheckForSpaces(InputString, 0))
        {
            throw std::runtime_error("Ошибка: Строка содержит пробелы, что запрещено условием");
        }

        //FIX_ME: некорректное название переменной
        //int ind = 0;
        int StartIndex = 0;

        //FIX_ME: некорректное название переменной, переменная должна объявляться на отдельной строке 
        //int res = primer(InputString, ind, delen(InputString, ind, recnum(InputString, ind)));
        int Result;
        Result = ParseAdditionAndSubtraction(InputString, StartIndex,
            ParseMultiplicationAndDivision(InputString, StartIndex,
                ParseNumber(InputString, StartIndex)));

        // Проверка, что вся строка обработана
        if (StartIndex < static_cast<int>(InputString.length()))
        {
            throw std::runtime_error("Ошибка: Некорректное выражение - не все символы были обработаны");
        }

        std::cout << "Результат: " << Result << std::endl;
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