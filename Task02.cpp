//Черепашка.На квадратной доске расставлены целые неотрицательные числа, каждое из которых 
//не превосходит 100. Черепашка, находящаяся в левом нижнем углу, мечтает по пасть в правый 
//верхний.При этом она может переползать только в клетку справа или сверху и хочет, чтобы 
//сумма всех чисел, оказавшихся у нее на пути, была бы минимальной.Определить эту сумму.
//Ввод и вывод организовать при помощи текстовых файлов.Формат входных данных :
//в первой строке входного файла записано число N - размер доски(1 < N < 80).Далее следует N
//строк, каждая из которых содержит N целых чисел, представляющих доску.В выходной файл
//нужно вывести единственное число : минимальную сумму.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

//FIX_ME: глобальное использование std
//using namespace std;

//FIX_ME: некорректное расположение скобок
//int main() {
int main() 
{
    setlocale(LC_ALL, "ru");
    //FIX_ME: некорректные имена файлов
    //ifstream input("input.txt");
    //ofstream output("output.txt");
    std::ifstream InputFile("input.txt");
    std::ofstream OutputFile("output.txt");

    //FIX_ME: некорректное имя переменной 
    //int N;
    int MatrixSize;
    InputFile >> MatrixSize;
    //FIX_ME: некорректное расположение скобок
    //if (MatrixSize <= 1 || MatrixSize >= 80) {
    if (MatrixSize <= 1 || MatrixSize >= 80) 
    {
        std::cerr << "Некорректный размер доски: " << MatrixSize << ". Должно быть 1 < N < 80" << std::endl;
        InputFile.close();
        OutputFile.close();
        return 1;
    }

    //FIX_ME: некорректное имя вектора
    //vector<vector<int>> board(MatrixSize, vector<int>(MatrixSize));
    std::vector<std::vector<int>> GameBoard(MatrixSize, std::vector<int>(MatrixSize));

    //FIX_ME: некорректное расположение скобок
    //for (int i = 0; i < MatrixSize; ++i) {
    //     for (int j = 0; j < MatrixSize; ++j) {
    //        InputFile >> board[i][j];
    //    }
    //}
    for (int i = 0; i < MatrixSize; ++i) 
    {
        for (int j = 0; j < MatrixSize; ++j)
        {
            InputFile >> GameBoard[i][j];
        }
    }

    //FIX_ME: некорректное имя вектора
    //vector<vector<int>> dp(MatrixSize, vector<int>(MatrixSize, 0));
    std::vector<std::vector<int>> DPTable(MatrixSize, std::vector<int>(MatrixSize, 0));

    DPTable[MatrixSize - 1][0] = GameBoard[MatrixSize - 1][0];

    //FIX_ME: некорректное расположение скобок
    //for (int i = MatrixSize - 2; i >= 0; i--) {
    for (int i = MatrixSize - 2; i >= 0; i--) 
    {
    DPTable[i][0] = DPTable[i + 1][0] + GameBoard[i][0];
    }

    //FIX_ME: некорректное расположение скобок
    //for (int j = 1; j < MatrixSize; j++) {
    for (int j = 1; j < MatrixSize; j++) 
    {
        DPTable[MatrixSize - 1][j] = DPTable[MatrixSize - 1][j - 1] + GameBoard[MatrixSize - 1][j];
    }
    //FIX_ME: некорректное расположение скобок
    //for (int i = MatrixSize - 2; i >= 0; i--) {
    //    for (int j = 1; j < MatrixSize; ++j) {
    //        DPTable[i][j] = min(DPTable[i + 1][j], DPTable[i][j - 1]) + GameBoard[i][j];
    //    }
    //}
    for (int i = MatrixSize - 2; i >= 0; i--) 
    {
        for (int j = 1; j < MatrixSize; ++j) 
        {
            DPTable[i][j] = std::min(DPTable[i + 1][j], DPTable[i][j - 1]) + GameBoard[i][j];
        }
    }

    OutputFile << DPTable[0][MatrixSize - 1];
    std::cout << "Значение " << DPTable[0][MatrixSize - 1] << " записано в файл";
}