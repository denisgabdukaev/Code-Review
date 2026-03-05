#include "HeaderTask01.h"

//FIX_ME: глобальное использование std
//using namespace std;

//FIX_ME: некорректное название функции, названия переменных
//void findAnswer(const std::vector<std::vector<int>>& dp, int k,int s, std::vector<int>& weight, std::vector<int>& nalog)
//{
//    if (k==0) {
//        return;
//    }
//    if (dp[k][s] == dp[k - 1][s]) {
//        findAnswer(dp, k - 1, s, weight,nalog);
//    }
//    else {
//        std::cout <<"берем артефакт с индексом " << k << ", ";
//        findAnswer(dp, k - 1, s - weight[k], weight,nalog);
//    }
//}
void FindAnswer(const std::vector<std::vector<int>>& OutDPTable,
    int CurrentIndex, int CurrentWeight, std::vector<int>& OutWeights, std::vector<int>& OutTaxes)
{
    if (CurrentIndex == 0) {
        return;
    }
    //FIX_ME: некорректное расположение скобок
    //if (InDPTable[CurrentIndex][CurrentWeight] == InDPTable[CurrentIndex - 1][CurrentWeight]) {
    //    FindAnswer(InDPTable, CurrentIndex - 1, CurrentWeight, InWeights, InTaxes);
    //}
    //else {
    //    std::cout << "берем артефакт с индексом " << CurrentIndex << ", ";
    //    FindAnswer(InDPTable, CurrentIndex - 1, CurrentWeight - InWeights[CurrentIndex], InWeights, InTaxes);
    //}
    if (OutDPTable[CurrentIndex][CurrentWeight] == OutDPTable[CurrentIndex - 1][CurrentWeight])
    {
        FindAnswer(OutDPTable, CurrentIndex - 1, CurrentWeight, OutWeights, OutTaxes);
    }
    else
    {
        std::cout << "берем артефакт с индексом " << CurrentIndex << ", ";
        FindAnswer(OutDPTable, CurrentIndex - 1, CurrentWeight - OutWeights[CurrentIndex], OutWeights, OutTaxes);
    }
}

bool ContainsInvalidChars(const std::string& InLine)
{
    for (char Character : InLine)
    {
        const bool bIsValid = isdigit(static_cast<unsigned char>(Character)) ||
            isspace(static_cast<unsigned char>(Character)) ||
            Character == '-' ||
            Character == '\n' ||
            Character == '\r';

        if (!bIsValid)
        {
            return true; // Найден недопустимый символ
        }
    }

    return false; // Все символы допустимы
}