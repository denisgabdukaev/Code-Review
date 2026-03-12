#include "HeaderTask01.h"

// Конструктор
FStack::FStack() : Top(nullptr) {}

// Деструктор
FStack::~FStack()
{
    ClearStack();
}

//FIX_ME: некорректное имя функции
//void push(int value) {

// для добавления элемента в стек
void FStack::Push(int Value)
{
    try
    {
        FNode* NewNode = new FNode(Value); // Создаем новый узел
        NewNode->NextData = Top;            // Новый узел указывает на текущую вершину
        Top = NewNode;                       // Обновляем вершину стека

        std::cout << "Элемент " << Value << " добавлен в стек." << std::endl;
    }
    catch (const std::bad_alloc& Exception)
    {
        throw FStackException("Ошибка выделения памяти при добавлении элемента");
    }
}

// Метод для удаления элемента из стека
void FStack::Pop()
{
    if (IsEmpty())
    {
        throw FStackException("Стек пуст! Невозможно удалить элемент.");
    }

    FNode* Temp = Top;
    Top = Top->NextData;

    std::cout << "Элемент " << Temp->Data << " удален из стека." << std::endl;
    delete Temp;
}

// Функция для вывода стека
void FStack::Print() const
{
    if (IsEmpty())
    {
        std::cout << "Стек пуст!" << std::endl;
        return;
    }

    FNode* Current = Top;
    std::cout << "Элементы стека: ";

    while (Current != nullptr)
    {
        std::cout << Current->Data << " ";
        Current = Current->NextData;
    }
    std::cout << std::endl;
}

// Получение головы стека
FNode* FStack::GetTop() const
{
    return Top;
}

// Очистка стека
void FStack::ClearStack()
{
    while (Top != nullptr)
    {
        FNode* Temp = Top;
        Top = Top->NextData;
        delete Temp;
    }
    std::cout << "Стек очищен." << std::endl;
}

// Проверка пустоты стека
bool FStack::IsEmpty() const
{
    return Top == nullptr;
}

// Добавление элемента и вывод адреса
void AddElementAndPrintAddress(FStack& Stack, int Value)
{
    try
    {
        Stack.Push(Value);
        std::cout << "Адрес новой вершины стека: " << Stack.GetTop() << std::endl;
    }
    catch (const FStackException& Exception)
    {
        throw; // Пробрасываем исключение дальше
    }
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