#include "HeaderTask04.h"
#include <limits>

// Конструктор узла
FNode::FNode(int Value) : Data(Value), Previous(nullptr), Next(nullptr) {}

// Конструктор списка
FDoubleList::FDoubleList() : First(nullptr) {}

// Деструктор списка
FDoubleList::~FDoubleList()
{
    try
    {
        Clear();
    }
    catch (...)
    {
        // Игнорируем исключения в деструкторе
    }
}

// Проверка пустоты списка
bool FDoubleList::IsEmpty() const
{
    return First == nullptr;
}

//FIX_ME: некорректное имя метода
// Добавление элемента в конец списка
void FDoubleList::AddElement(int Value)
{
    //FIX_ME: отсутствие проверки выделения памяти
    FNode* NewNode = nullptr;

    try
    {
        NewNode = new FNode(Value);
    }
    catch (const std::bad_alloc&)
    {
        throw FListException("Ошибка выделения памяти при добавлении элемента");
    }

    //FIX_ME: некорректное расположение скобок
    if (First == nullptr)
    {
        First = NewNode;
    }
    else
    {
        FNode* Current = First;

        //FIX_ME: некорректное расположение скобок
        while (Current->Next != nullptr)
        {
            Current = Current->Next;
        }

        Current->Next = NewNode;
        NewNode->Previous = Current;
    }
}

//FIX_ME: некорректное имя метода
// Удаление указанного узла
void FDoubleList::DeleteElement(FNode* NodeToDelete)
{
    //FIX_ME: некорректное расположение скобок
    if (NodeToDelete == nullptr)
    {
        throw FListException("Попытка удалить несуществующий узел");
    }

    FNode* Prev = NodeToDelete->Previous;
    FNode* Next = NodeToDelete->Next;

    //FIX_ME: некорректное расположение скобок
    if (Prev != nullptr)
    {
        Prev->Next = Next;
    }
    else
    {
        First = Next;
    }

    //FIX_ME: некорректное расположение скобок
    if (Next != nullptr)
    {
        Next->Previous = Prev;
    }

    delete NodeToDelete;
}

//FIX_ME: некорректное имя метода
// Вывод списка на экран
void FDoubleList::Print() const
{
    //FIX_ME: использование cout без префикса std::
    if (IsEmpty())
    {
        std::cout << "Список пуст!" << std::endl;
        return;
    }

    FNode* Current = First;
    std::cout << "Список: ";

    //FIX_ME: некорректное расположение скобок
    while (Current != nullptr)
    {
        std::cout << Current->Data << " ";

        if (std::cout.fail())
        {
            throw FListException("Ошибка при выводе данных");
        }

        Current = Current->Next;
    }

    std::cout << std::endl;
}

//FIX_ME: некорректное имя метода
// Запись в файл в обратном порядке и удаление элементов
void FDoubleList::WriteToFileAndClear(const std::string& FileName)
{
    //FIX_ME: отсутствие проверки открытия файла
    std::ofstream File(FileName);

    //FIX_ME: некорректное расположение скобок
    if (!File.is_open())
    {
        throw FListException("Ошибка открытия файла для записи: " + FileName);
    }

    if (IsEmpty())
    {
        File.close();
        std::cout << "Список пуст. Создан пустой файл." << std::endl;
        return;
    }

    bool bFirstElement = true;
    FNode* Current = First;

    // Находим последний элемент
    //FIX_ME: некорректное расположение скобок
    while (Current != nullptr && Current->Next != nullptr)
    {
        Current = Current->Next;
    }

    // Записываем и удаляем элементы с конца
    //FIX_ME: некорректное расположение скобок
    while (Current != nullptr)
    {
        //FIX_ME: использование File без префикса std::
        if (bFirstElement)
        {
            File << Current->Data;
            bFirstElement = false;
        }
        else
        {
            File << " " << Current->Data;
        }

        // Проверка ошибок записи
        if (File.fail())
        {
            throw FListException("Ошибка при записи в файл");
        }

        FNode* Previous = Current->Previous;
        DeleteElement(Current);
        Current = Previous;
    }

    File.close();

    if (File.fail())
    {
        throw FListException("Ошибка при закрытии файла");
    }

    std::cout << "Данные записаны в файл и список очищен." << std::endl;
}

//FIX_ME: некорректное имя метода
// Очистка всего списка
void FDoubleList::Clear()
{
    FNode* Current = First;

    //FIX_ME: некорректное расположение скобок
    while (Current != nullptr)
    {
        FNode* Next = Current->Next;
        delete Current;
        Current = Next;
    }

    First = nullptr;
}

//FIX_ME: некорректное имя функции
// Функция для ввода числа с проверкой
int InputNumber()
{
    std::string Input;

    //FIX_ME: использование while с cin без обработки ошибок
    while (true)
    {
        std::cout << "Введите число (или '-1' для завершения): ";

        if (!(std::cin >> Input))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw FListException("Ошибка чтения ввода");
        }

        //FIX_ME: некорректное расположение скобок
        if (Input == "-1")
        {
            return -1;
        }

        bool bIsValid = true;
        int Sign = 1;
        size_t StartIndex = 0;

        //FIX_ME: некорректное расположение скобок
        if (Input.empty())
        {
            bIsValid = false;
        }
        else if (Input[0] == '-')
        {
            Sign = -1;
            StartIndex = 1;

            //FIX_ME: некорректное расположение скобок
            if (Input.size() == 1)
            {
                bIsValid = false;
            }
        }

        //FIX_ME: некорректное расположение скобок
        for (size_t i = StartIndex; i < Input.size(); ++i)
        {
            //FIX_ME: использование isdigit без приведения типа
            if (!isdigit(static_cast<unsigned char>(Input[i])))
            {
                bIsValid = false;
                break;
            }
        }

        //FIX_ME: некорректное расположение скобок
        if (bIsValid)
        {
            int Number = 0;

            //FIX_ME: некорректное расположение скобок
            for (size_t i = StartIndex; i < Input.size(); ++i)
            {
                // Проверка на переполнение
                if (Number > (std::numeric_limits<int>::max() - (Input[i] - '0')) / 10)
                {
                    throw FListException("Число превышает допустимый диапазон");
                }
                Number = Number * 10 + (Input[i] - '0');
            }

            return Number * Sign;
        }
        else
        {
            std::cout << "Некорректный ввод! Используйте цифры и знак '-' в начале." << std::endl;
        }
    }
}

//FIX_ME: некорректное имя функции
// Функция для вывода содержимого файла
void PrintFileContent(const std::string& FileName)
{
    //FIX_ME: отсутствие проверки открытия файла
    std::ifstream File(FileName);

    //FIX_ME: некорректное расположение скобок
    if (!File.is_open())
    {
        throw FListException("Ошибка при открытии файла для чтения: " + FileName);
    }

    std::cout << "\n=== Содержимое файла ===" << std::endl;
    std::string Line;
    bool bHasContent = false;

    //FIX_ME: некорректное расположение скобок
    while (std::getline(File, Line))
    {
        std::cout << Line << std::endl;
        bHasContent = true;

        if (std::cout.fail())
        {
            throw FListException("Ошибка при выводе содержимого файла");
        }
    }

    if (!bHasContent)
    {
        std::cout << "(файл пуст)" << std::endl;
    }

    File.close();
}