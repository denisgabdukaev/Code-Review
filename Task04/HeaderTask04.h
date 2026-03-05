//Во всех заданиях данной подгруппы предполагается, что исходные строки, определяющие выражения, 
//не содержат пробелов.При выполнении заданий не следует использовать оператор цикла.
//Вывести значение целочисленного выражения, заданного в виде строки S.Выражение
//определяется следующим образом :
//<выражение> :: = <цифра> | (<выражение><знак><выражение>)
//< знак > :: = +| − | *

#ifndef HeaderTask04
#define HeaderTask04

#include <iostream>
#include <string>
#include <sstream>

//FIX_ME: глобальное использование std
//using namespace std;

int ParseNumber(const std::string& InExpression, int& OutIndex);
int ParseMultiplicationAndDivision(const std::string& InExpression, int& OutIndex, int InLeftValue);
int ParseAdditionAndSubtraction(const std::string& InExpression, int& OutIndex, int InLeftValue);
bool CheckForSpaces(const std::string& InExpression, int InIndex);

#endif // HeaderTask04