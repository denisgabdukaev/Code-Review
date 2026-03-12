#include "HeaderTask05.h"

//FIX_ME: некорректное расположение скобок

// Проверка корректности размера контейнера
bool IsValidSize(int InSize)
{
    return (InSize >= 2 && InSize % 2 == 0);
}

// Выбор способа ввода
EInputMethod SelectInputMethod()
{
    int Choice;

    std::cout << "Выберите способ заполнения контейнера:" << std::endl;
    std::cout << "1) Ввод с клавиатуры" << std::endl;
    std::cout << "2) Ввод с помощью рандомайзера" << std::endl;
    std::cout << "3) Ввод данных из текстового файла" << std::endl;

    while (true)
    {
        Choice = ReadInteger("Ваш выбор (1-3): ");

        if (Choice >= 1 && Choice <= 3)
        {
            return static_cast<EInputMethod>(Choice);
        }

        std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3." << std::endl;
    }
}

// Ввод числа с проверкой
int ReadInteger(const std::string& InPrompt)
{
    int Value;

    while (true)
    {
        std::cout << InPrompt;

        if (std::cin >> Value)
        {
            return Value;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Пожалуйста, введите целое число." << std::endl;
        }
    }
}

// Чтение данных из файла
void ReadValuesFromFile(int* OutValues, int InExpectedCount, const char* InFileName)
{
    std::ifstream File(InFileName, std::ios::in);

    if (!File.is_open())
    {
        throw FContainerException("Ошибка: Не удалось открыть файл '" + std::string(InFileName) + "'");
    }

    for (int Index = 0; Index < InExpectedCount; ++Index)
    {
        File >> OutValues[Index];

        if (File.fail())
        {
            File.close();
            throw FContainerException("Ошибка: Недостаточно данных в файле или некорректный формат.");
        }
    }

    File.close();
}

// Пользовательская функция swap
void SwapValues(int& InOutA, int& InOutB)
{
    int Temp = InOutA;
    InOutA = InOutB;
    InOutB = Temp;
}

// Ввод данных в контейнер
template <typename ContainerType>
void InputContainer(ContainerType& OutContainer, int InSize)
{
    // Проверка корректности размера
    if (!IsValidSize(InSize))
    {
        throw FContainerException("Ошибка: Недопустимый размер контейнера. Требуется >= 2 и четное число.");
    }

    EInputMethod Method = SelectInputMethod();
    int Value;

    switch (Method)
    {
    case EInputMethod::Keyboard:
    {
        // Ввод с клавиатуры
        for (int Index = 0; Index < InSize; ++Index)
        {
            std::string Prompt = "Введите " + std::to_string(Index + 1) + "-й элемент: ";
            Value = ReadInteger(Prompt);
            OutContainer.insert(OutContainer.end(), Value);
        }
        break;
    }

    case EInputMethod::Random:
    {
        // Ввод случайными числами
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (int Index = 0; Index < InSize; ++Index)
        {
            Value = std::rand() % 101 - 50; // от -50 до 50
            OutContainer.insert(OutContainer.end(), Value);
        }
        std::cout << "Сгенерировано " << InSize << " случайных чисел." << std::endl;
        break;
    }

    case EInputMethod::File:
    {
        // Ввод из файла
        int* Buffer = new int[InSize];

        try
        {
            ReadValuesFromFile(Buffer, InSize, "a.txt");
            for (int Index = 0; Index < InSize; ++Index)
            {
                OutContainer.insert(OutContainer.end(), Buffer[Index]);
            }
        }
        catch (...)
        {
            delete[] Buffer;
            throw;
        }

        delete[] Buffer;
        break;
    }

    default:
        throw FContainerException("Ошибка: Неверный выбор способа ввода.");
    }
}

// Вывод содержимого контейнера
template <typename ContainerType>
void PrintContainer(const ContainerType& InContainer)
{
    if (InContainer.empty())
    {
        std::cout << "(контейнер пуст)";
        return;
    }

    // Вывод в прямом порядке с использованием итератора
    for (auto Iter = InContainer.begin(); Iter != InContainer.end(); ++Iter)
    {
        std::cout << *Iter << " ";

        if (std::cout.fail())
        {
            throw FContainerException("Ошибка при выводе данных.");
        }
    }
    std::cout << std::endl;

    // Вывод в обратном порядке с использованием обратных итераторов (rbegin/rend)
    std::cout << "В обратном порядке: ";
    for (auto ReverseIter = InContainer.rbegin(); ReverseIter != InContainer.rend(); ++ReverseIter)
    {
        std::cout << *ReverseIter << " ";
    }
    std::cout << std::endl;
}

// Обмен значений двух средних элементов
template <typename ContainerType>
void SwapMiddleElements(ContainerType& InOutContainer)
{
    // Проверка размера контейнера
    if (InOutContainer.size() < 2)
    {
        throw FContainerException("Ошибка: Контейнер содержит менее двух элементов.");
    }

    if (InOutContainer.size() % 2 != 0)
    {
        throw FContainerException("Ошибка: Контейнер имеет нечетное количество элементов.");
    }

    auto Iter = InOutContainer.begin();
    size_t Size = InOutContainer.size();

    // Достигаем первого среднего элемента
    for (size_t Index = 0; Index < Size / 2 - 1; ++Index)
    {
        ++Iter;
    }

    auto FirstMiddle = Iter;   // Первый средний элемент
    ++Iter;                    // Переходим ко второму
    auto SecondMiddle = Iter;  // Второй средний элемент

    // Используем алгоритм swap (не функцию-член контейнера)
    SwapValues(*FirstMiddle, *SecondMiddle);
}

// Явное инстанцирование шаблонов для используемых типов
template void InputContainer<std::vector<int>>(std::vector<int>& OutContainer, int InSize);
template void InputContainer<std::deque<int>>(std::deque<int>& OutContainer, int InSize);
template void InputContainer<std::list<int>>(std::list<int>& OutContainer, int InSize);

template void PrintContainer<std::vector<int>>(const std::vector<int>& InContainer);
template void PrintContainer<std::deque<int>>(const std::deque<int>& InContainer);
template void PrintContainer<std::list<int>>(const std::list<int>& InContainer);

template void SwapMiddleElements<std::vector<int>>(std::vector<int>& InOutContainer);
template void SwapMiddleElements<std::deque<int>>(std::deque<int>& InOutContainer);
template void SwapMiddleElements<std::list<int>>(std::list<int>& InOutContainer);