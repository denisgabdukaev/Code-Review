#include "HeaderTask04.h"

bool CheckForSpaces(const std::string& InExpression, int InIndex)
{
    // Базовый случай: достигнут конец строки
    if (InIndex >= static_cast<int>(InExpression.length()))
    {
        return false;
    }

    // Если найден пробел, возвращаем true
    if (isspace(static_cast<unsigned char>(InExpression[InIndex])))
    {
        return true;
    }

    // Рекурсивно проверяем следующий символ
    return CheckForSpaces(InExpression, InIndex + 1);
}

//FIX_ME: Некорректное название функции и переменных, некорректное расположение скобок
//int recnum(const string& stroka, int& ind) {
int ParseNumber(const std::string& InExpression, int& OutIndex)
{
    //FIX_ME: не использование скобок при if
    //if (ind >= stroka.length() || !isdigit(stroka[ind]))
    //    return 0;
    if (OutIndex >= static_cast<int>(InExpression.length()) || !isdigit(InExpression[OutIndex]))
    {
        return 0;
    }

    //FIX_ME: некорректные имена переменных, переменная должна объявляться на отдельной строке 
    //int num = InExpression[OutIndex++] - '0'; // Преобразуем символ в число
    //int next = ParseNumber(InExpression, OutIndex); // Читаем следующие цифры
    int ParsedValue;
    ParsedValue = InExpression[OutIndex++] - '0'; // Преобразуем символ в число

    int RemainingValue;
    RemainingValue = ParseNumber(InExpression, OutIndex); // Читаем следующие цифры

    //FIX_ME: плохо читаемое выражение 
    //return RemainingValue == 0 ? ParsedValue : ParsedValue * 10 + RemainingValue; // Собираем многозначное число
    if (RemainingValue == 0)
    {
        return ParsedValue;
    }
    else
    {
        return ParsedValue * 10 + RemainingValue;
    }
}

//FIX_ME: Некорректное название функции и переменных, некорректное расположение скобок
//int delen(const string& stroka, int& ind, int left) {
int ParseMultiplicationAndDivision(const std::string& InExpression, int& OutIndex, int InLeftValue)
{
    //FIX_ME: не использование скобок при if
    //if (OutIndex >= InExpression.length()) return left;
    if (OutIndex >= static_cast<int>(InExpression.length()))
    {
        return InLeftValue;
    }

    //FIX_ME: некорректные имена переменных, переменная должна объявляться на отдельной строке 
    //char op = InExpression[OutIndex];
    char Operand;
    Operand = InExpression[OutIndex];

    //FIX_ME: не использование скобок при if
    //if (Operand != '*' && Operand != '/') return InLeftValue;
    if (Operand != '*' && Operand != '/')
    {
        return InLeftValue;
    }
    OutIndex++;

    //FIX_ME: некорректные имена переменных, переменная должна объявляться на отдельной строке 
    //int right = ParseNumber(InExpression, OutIndex);
    int RightValue;
    RightValue = ParseNumber(InExpression, OutIndex);

    //FIX_ME: не использование скобок при if, некорректное использование скобок 
    //if (Operand == '*') return ParseMultiplicationAndDivision(InExpression, OutIndex, InLeftValue * RightValue);
    //if (Operand == '/') {
    //    if (RightValue == 0) {
    //        cout << "Ошибка: деление на 0!" << endl;
    //        exit(1);
    //    }
    //    return ParseMultiplicationAndDivision(InExpression, OutIndex, InLeftValue / RightValue);
    //}
    if (Operand == '*')
    {
        return ParseMultiplicationAndDivision(InExpression, OutIndex, InLeftValue * RightValue);
    }
    else if (Operand == '/')
    {
        if (RightValue == 0)
        {
            std::cout << "Ошибка: деление на 0!" << std::endl;
            exit(1);
        }
        return ParseMultiplicationAndDivision(InExpression, OutIndex, InLeftValue / RightValue);
    }
    return InLeftValue;
}

//FIX_ME: Некорректное название функции и переменных, некорректное расположение скобок
//int primer(const string& stroka, int& ind, int left) {
int ParseAdditionAndSubtraction(const std::string& InExpression, int& OutIndex, int InLeftValue)
{
    //FIX_ME: не использование скобок при if
    //if (ind >= stroka.length()) return left;
    if (OutIndex >= static_cast<int>(InExpression.length()))
    {
        return InLeftValue;
    }

    //FIX_ME: некорректные имена переменных, переменная должна объявляться на отдельной строке 
    //char op = stroka[ind];
    char Operand;
    Operand = InExpression[OutIndex];

    //FIX_ME: не использование скобок при if
    //if (op != '+' && op != '-') return left;
    if (Operand != '+' && Operand != '-')
    {
        return InLeftValue;
    }
    OutIndex++;

    //FIX_ME: некорректные имена переменных, переменная должна объявляться на отдельной строке 
    //int right = ParseMultiplicationAndDivision(stroka, ind, ParseNumber(stroka, ind));
    int RightValue;
    RightValue = ParseMultiplicationAndDivision(InExpression, OutIndex, ParseNumber(InExpression, OutIndex));

    //FIX_ME: не использование скобок при if
    //if (op == '+') return primer(stroka, ind, left + right);
    //if (op == '-') return primer(stroka, ind, left - right);
    if (Operand == '+')
    {
        return ParseAdditionAndSubtraction(InExpression, OutIndex, InLeftValue + RightValue);
    }
    if (Operand == '-')
    {
        return ParseAdditionAndSubtraction(InExpression, OutIndex, InLeftValue - RightValue);
    }

    return InLeftValue;
}