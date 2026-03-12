#include "HeaderTask03.h"

// Конструктор
FLinkedList::FLinkedList() : Head(nullptr) {}

// Деструктор
FLinkedList::~FLinkedList()
{
    Clear();
}

//FIX_ME: некорректное имя функции
// Метод для вставки элемента с сохранением упорядоченности по убыванию
void FLinkedList::InsertSorted(int Value)
{
    // Создаем новый узел
    FNode* NewNode = new FNode(Value);

    //FIX_ME: некорректное расположение скобок
    // Если список пуст или новый элемент должен быть первым (больше текущей головы)
    if (Head == nullptr || Head->Data < Value)
    {
        NewNode->Next = Head;
        Head = NewNode;
    }
    else
    {
        // Ищем позицию для вставки (список упорядочен по убыванию)
        FNode* Current = Head;

        //FIX_ME: некорректное расположение скобок
        while (Current->Next != nullptr && Current->Next->Data > Value)
        {
            Current = Current->Next;
        }

        // Вставляем новый узел
        NewNode->Next = Current->Next;
        Current->Next = NewNode;
    }
}

// Метод для вывода списка
void FLinkedList::Print() const
{
    //FIX_ME: некорректное расположение скобок
    if (Head == nullptr)
    {
        std::cout << "Список пуст!" << std::endl;
        return;
    }

    FNode* Current = Head;

    //FIX_ME: некорректное расположение скобок
    while (Current != nullptr)
    {
        std::cout << Current->Data << " ";
        Current = Current->Next;
    }

    std::cout << std::endl;
}

// Метод для чтения данных из файла
void FLinkedList::ReadFromFile(const std::string& Filename)
{
    std::ifstream File(Filename); // Открываем файл для чтения

    //FIX_ME: отсутствие проверки наличия файла
    //FIX_ME: некорректное расположение скобок
    if (!File.is_open())
    {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    int N;
    File >> N; // Читаем количество элементов

    int Value;

    //FIX_ME: некорректное расположение скобок
    for (int i = 0; i < N; ++i)
    {
        File >> Value;
        InsertSorted(Value); // Вставляем элемент с сохранением упорядоченности
    }

    File.close(); // Закрываем файл
}

// Метод для очистки списка
void FLinkedList::Clear()
{
    //FIX_ME: некорректное расположение скобок
    while (Head != nullptr)
    {
        FNode* Temp = Head;
        Head = Head->Next;
        delete Temp;
    }
}

// Дружественная функция для чтения из файла
void ReadFromFile(FLinkedList& List, const std::string& Filename)
{
    List.ReadFromFile(Filename);
}