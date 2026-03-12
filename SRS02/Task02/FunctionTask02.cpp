#include "HeaderTask02.h"
#include <limits>

// Конструктор
FQueue::FQueue() : Head(nullptr), Tail(nullptr) {}

// Деструктор
FQueue::~FQueue()
{
    Clear();
}

//FIX_ME: некорректное имя функции
//void Queue::push(int value)

// Добавление элемента в очередь
void FQueue::Push(int InValue)
{
    try
    {
        FNode* NewNode = new FNode(InValue);

        if (IsEmpty())
        {
            Head = Tail = NewNode;
        }
        else
        {
            Tail->Next = NewNode;
            Tail = NewNode;
        }

        std::cout << "Элемент " << InValue << " добавлен в очередь." << std::endl;
    }
    catch (const std::bad_alloc& Exception)
    {
        throw FQueueException("Ошибка выделения памяти при добавлении элемента");
    }
}

// Извлечение элемента из очереди
bool FQueue::Pop(int& OutValue)
{
    if (IsEmpty())
    {
        return false;
    }

    FNode* Temp = Head;
    OutValue = Head->Data;
    Head = Head->Next;

    if (Head == nullptr)
    {
        Tail = nullptr; // Очередь стала пустой
    }

    delete Temp;
    return true;
}

// Вывод элементов очереди
void FQueue::Show() const
{
    if (IsEmpty())
    {
        std::cout << "Очередь пустая" << std::endl;
        return;
    }

    FNode* Current = Head;
    while (Current != nullptr)
    {
        std::cout << Current->Data << " ";
        Current = Current->Next;
    }
    std::cout << std::endl;
}

// Обработка четности головы
void FQueue::ProcessEvenHead()
{
    int Value;
    std::cout << "Извлеченные элементы: ";

    while (!IsEmpty() && (Head->Data % 2 != 0))
    {
        if (Pop(Value))
        {
            std::cout << Value << " ";
        }
    }
    std::cout << std::endl;
}

// Получение указателя на начало очереди
FNode* FQueue::GetHead() const
{
    return Head;
}

// Получение указателя на конец очереди
FNode* FQueue::GetTail() const
{
    return Tail;
}

// Получение значения начала очереди
int FQueue::GetHeadValue() const
{
    if (IsEmpty())
    {
        throw FQueueException("Очередь пуста - нет значения головы");
    }
    return Head->Data;
}

// Получение значения конца очереди
int FQueue::GetTailValue() const
{
    if (IsEmpty())
    {
        throw FQueueException("Очередь пуста - нет значения хвоста");
    }
    return Tail->Data;
}

// Проверка пустоты очереди
bool FQueue::IsEmpty() const
{
    return Head == nullptr;
}

// Очистка очереди
void FQueue::Clear()
{
    int Dummy;
    while (Pop(Dummy)) {}
    std::cout << "Очередь очищена." << std::endl;
}

// Проверка, является ли строка числом
bool IsNumber(const std::string& InString)
{
    if (InString.empty())
    {
        return false;
    }

    int StartIndex = (InString[0] == '-' || InString[0] == '+') ? 1 : 0;

    // Проверка, что строка не состоит только из знака
    if (StartIndex >= static_cast<int>(InString.length()))
    {
        return false;
    }

    for (int i = StartIndex; i < static_cast<int>(InString.length()); ++i)
    {
        if (!isdigit(static_cast<unsigned char>(InString[i])))
        {
            return false;
        }
    }

    return true;
}

// Проверка корректности входных данных
bool ReadInteger(int& OutValue)
{
    std::cin >> OutValue;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}