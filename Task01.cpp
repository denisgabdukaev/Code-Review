//Археолог нашел N артефактов.Известны веса(сi) и налоговое бремя(di) находок.
//Нужно выбрать такое подмножество находок, чтобы их суммарный вес превысил Z кг, а их об
//щее налоговое бремя оказалось минимальным.Известно, что решение единственно.Укажите
//порядковые номера вещей, которые нужно взять.Исходный данные находятся в текстовом файле, 
//в первой строке указаны N и Z, а во второй строке значения весов(в кг), в третьей - величина
//налога по каждой находке.Вывести так же суммарный вес и общую ценность результата.

#include <iostream>
#include<fstream>
#include<vector>
#include <climits>  // для INT_MAX

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
void FindAnswer(const std::vector<std::vector<int>>& InDPTable,
    int CurrentIndex, int CurrentWeight, std::vector<int>& InWeights, std::vector<int>& InTaxes)
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
    if (InDPTable[CurrentIndex][CurrentWeight] == InDPTable[CurrentIndex - 1][CurrentWeight])
    {
        FindAnswer(InDPTable, CurrentIndex - 1, CurrentWeight, InWeights, InTaxes);
    }
    else
    {
        std::cout << "берем артефакт с индексом " << CurrentIndex << ", ";
        FindAnswer(InDPTable, CurrentIndex - 1, CurrentWeight - InWeights[CurrentIndex], InWeights, InTaxes);
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    
    //FIX_ME: некорректные имена переменных 
    //int N, Z;
    int NumArtifacts;
    int MinRequiredWeight;

    //FIX_ME: некорректное имя файла
    //ifstream f1("археолог.txt");
    std::ifstream ArtifactInput("археолог.txt");
    ArtifactInput >> NumArtifacts >> MinRequiredWeight;

    //FIX_ME: некорректные имена векторов
    //vector<int> weight(NumArtifacts + 1);
    //vector<int> nalog(NumArtifacts + 1);

    std::vector<int> ArtifactWeights(NumArtifacts + 1);
    std::vector<int> ArtifactTaxes(NumArtifacts + 1);
    
    //FIX_ME: некорректное расположение скобок
    //for (int i = 1; i <= NumArtifacts; i++) {
    //    ArtifactInput >> ArtifactWeights[i];//считывание весов и налогов
    //}
    //for (int i = 1; i <= NumArtifacts; i++) {
    //    ArtifactInput >> ArtifactTaxes[i];
    //}

    //int maxWeight = 0;
    //for (int i = 1; i <= NumArtifacts; i++) {
    //    maxWeight += ArtifactWeights[i];//нахождение макс веса для массива
    //}

    for (int i = 1; i <= NumArtifacts; i++)
    {
        ArtifactInput >> ArtifactWeights[i];//считывание весов и налогов
    }

    for (int i = 1; i <= NumArtifacts; i++)
    {
        ArtifactInput >> ArtifactTaxes[i];
    }

    //FIX_ME: некорректное имя переменной 
    //int maxWeight = 0;
    int MaxWeight = 0;

    for (int i = 1; i <= NumArtifacts; i++)
    {
        MaxWeight += ArtifactWeights[i];//нахождение макс веса для массива
    }

    //FIX_ME: некорректное имя вектора, использование одного и того же числа вместо константы (INT_MAX)
    //std::vector<std::vector<int>> dp(NumArtifacts + 1, std::vector<int>(MaxWeight + 1, 10000000));
    std::vector<std::vector<int>> DPTable(NumArtifacts + 1, std::vector<int>(MaxWeight + 1, INT_MAX));
    
    DPTable[0][0] = 0;

    for (int i = 1; i <= NumArtifacts; i++) 
    {
        //FIX_ME: нестандартное имя переменной в цикле 
        //for (int s = 0; s <= MaxWeight; s++) 
        for (int j = 0; j <= MaxWeight; j++)
        {
            DPTable[i][j] = DPTable[i - 1][j];
            if (j >= ArtifactWeights[i] && DPTable[i - 1][j - ArtifactWeights[i]] != INT_MAX)
            {
                DPTable[i][j] = std::min(DPTable[i][j], DPTable[i - 1][j - ArtifactWeights[i]] + ArtifactTaxes[i]);
            }
        }
    }

    //FIX_ME: некорректные имена переменных 
    //int minNalog = INT_MAX;
    //int bestWeight = -1;
    int MinTax = INT_MAX;
    int BestWeight = -1;

    //FIX_ME: нестандартное имя переменной в цикле, некорректное расположение скобок
    //for (int s = MinRequiredWeight +1 ; s <= MaxWeight; s++) {
    //    if (DPTable[NumArtifacts][s] < MinTax) {
    //        MinTax = DPTable[NumArtifacts][s];
    //        BestWeight = s;
    //    }
    //}
    for (int i = MinRequiredWeight + 1; i <= MaxWeight; i++)
    {
        if (DPTable[NumArtifacts][i] < MinTax)
        {
            MinTax = DPTable[NumArtifacts][i];
            BestWeight = i;
        }
    }

    std::cout << "Минимальный налог: " << MinTax << std::endl;
    std::cout << "Суммарный вес: " << BestWeight<< std::endl;

    FindAnswer(DPTable, NumArtifacts, BestWeight, ArtifactWeights,ArtifactTaxes);

    std::cout << std::endl;
    return 0;
}
