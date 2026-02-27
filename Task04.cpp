//Во всех заданиях данной подгруппы предполагается, что исходные строки, определяющие выражения, 
//не содержат пробелов.При выполнении заданий не следует использовать оператор цикла.
//Вывести значение целочисленного выражения, заданного в виде строки S.Выражение
//определяется следующим образом :
//<выражение> :: = <цифра> | (<выражение><знак><выражение>)
//< знак > :: = +| − | *

#include <iostream>
#include <string>

//FIX_ME: глобальное использование std
//using namespace std;

//FIX_ME: Некорректное название функции и переменных, некорректное расположение скобок
//int recnum(const string& stroka, int& ind) {
int ParseNumber(const std::string& InExpression, int& OutIndex) {

    //FIX_ME: не использование скобок при if
    //if (ind >= stroka.length() || !isdigit(stroka[ind]))
    //    return 0;
    if (OutIndex >= InExpression.length() || !isdigit(InExpression[OutIndex])) 
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
    if (OutIndex >= InExpression.length())
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
    if (OutIndex >= InExpression.length())
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

//FIX_ME: некорректное расположение скобок
//int main() {
int main() 
{
    setlocale(LC_ALL, "RU");

    //FIX_ME: некорректное название переменной
    //string s;
    std::string InputString;

    std::cout << "Введите выражение:" << std::endl;
    std::cin >> InputString;
    
    //FIX_ME: некорректное название переменной
    //int ind = 0;
    int StartIndex = 0;

    //FIX_ME: некорректное название переменной, переменная должна объявляться на отдельной строке 
    //int res = primer(InputString, ind, delen(InputString, ind, recnum(InputString, ind)));
    int Result;
    Result = ParseAdditionAndSubtraction(InputString, StartIndex,
                ParseMultiplicationAndDivision(InputString, StartIndex,
                    ParseNumber(InputString, StartIndex)));

    std::cout << "Результат: " << Result << std::endl;

    return 0;
}
