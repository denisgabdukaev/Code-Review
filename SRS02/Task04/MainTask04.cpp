#include "HeaderTask04.h"
#include <limits>

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        //FIX_ME: некорректное имя переменной
        FDoubleList MyList;

        std::cout << "=== Ввод чисел в список ===" << std::endl;

        //FIX_ME: некорректное расположение скобок
        while (true)
        {
            try
            {
                int Number = InputNumber();

                //FIX_ME: некорректное расположение скобок
                if (Number == -1)
                {
                    break;
                }

                MyList.AddElement(Number);
            }
            catch (const FListException& Exception)
            {
                std::cerr << "Ошибка ввода: " << Exception.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // Продолжаем ввод
            }
        }

        try
        {
            MyList.Print();
        }
        catch (const FListException& Exception)
        {
            std::cerr << "Ошибка при выводе списка: " << Exception.what() << std::endl;
        }

        std::cout << "\n=== Запись в файл ===" << std::endl;

        //FIX_ME: некорректное имя переменной
        std::string FileName;
        std::cout << "Введите имя файла: ";

        if (!(std::cin >> FileName))
        {
            throw FListException("Ошибка чтения имени файла");
        }

        try
        {
            MyList.WriteToFileAndClear(FileName);
            PrintFileContent(FileName);
        }
        catch (const FListException& Exception)
        {
            std::cerr << "Ошибка при работе с файлом: " << Exception.what() << std::endl;
            return 2;
        }
    }
    catch (const FListException& Exception)
    {
        std::cerr << "Критическая ошибка: " << Exception.what() << std::endl;
        return 1;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Неизвестная ошибка: " << Exception.what() << std::endl;
        return 3;
    }

    return 0;
}