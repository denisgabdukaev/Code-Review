#include "HeaderTask01.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        //FIX_ME: некорректные имена переменных 
        //int N, Z;
        int NumArtifacts;
        int MinRequiredWeight;

        //FIX_ME: некорректное имя файла
        //ifstream f1("археолог.txt");
        std::ifstream ArtifactInput("археолог.txt");

        //FIX_ME: отсутствие проверки наличия файла
        if (!ArtifactInput.is_open())
        {
            throw std::runtime_error("Ошибка: Не удалось открыть файл 'археолог.txt'");
        }

        // Чтение первой строки целиком для проверки на недопустимые символы
        std::string FirstLine;
        if (!std::getline(ArtifactInput, FirstLine))
        {
            throw std::runtime_error("Ошибка: Файл пуст или не удалось прочитать первую строку");
        }

        // Проверка первой строки на недопустимые символы
        if (ContainsInvalidChars(FirstLine))
        {
            throw std::runtime_error("Ошибка: Первая строка содержит недопустимые символы (разрешены только цифры, пробелы и знак минуса)");
        }

        // Парсинг первой строки
        std::stringstream FirstStream(FirstLine);
        if (!(FirstStream >> NumArtifacts >> MinRequiredWeight))
        {
            throw std::runtime_error("Ошибка: Не удалось прочитать N и Z из первой строки файла");
        }

        // Чтение второй строки (веса)
        std::string SecondLine;
        if (!std::getline(ArtifactInput, SecondLine))
        {
            throw std::runtime_error("Ошибка: Не удалось прочитать вторую строку с весами артефактов");
        }

        // Проверка второй строки на недопустимые символы
        if (ContainsInvalidChars(SecondLine))
        {
            throw std::runtime_error("Ошибка: Вторая строка (веса) содержит недопустимые символы");
        }

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

        // Парсинг второй строки (веса)
        std::stringstream SecondStream(SecondLine);
        for (int Index = 1; Index <= NumArtifacts; Index++)
        {
            if (!(SecondStream >> ArtifactWeights[Index])) //считывание весов
            {
                throw std::runtime_error("Ошибка: Недостаточно данных о весах артефактов (ожидалось " +
                    std::to_string(NumArtifacts) + " значений)");
            }
        }

        // Проверка, что не осталось лишних данных во второй строке
        int ExtraValue;
        if (SecondStream >> ExtraValue)
        {
            throw std::runtime_error("Ошибка: Во второй строке больше значений весов, чем указано в N");
        }

        // Чтение третьей строки (налоги)
        std::string ThirdLine;
        if (!std::getline(ArtifactInput, ThirdLine))
        {
            throw std::runtime_error("Ошибка: Не удалось прочитать третью строку с налогами артефактов");
        }

        // Проверка третьей строки на недопустимые символы
        if (ContainsInvalidChars(ThirdLine))
        {
            throw std::runtime_error("Ошибка: Третья строка (налоги) содержит недопустимые символы");
        }

        // Парсинг третьей строки (налоги)
        std::stringstream ThirdStream(ThirdLine);
        for (int Index = 1; Index <= NumArtifacts; Index++)
        {
            if (!(ThirdStream >> ArtifactTaxes[Index])) //считывание налогов
            {
                throw std::runtime_error("Ошибка: Недостаточно данных о налогах артефактов (ожидалось " +
                    std::to_string(NumArtifacts) + " значений)");
            }
        }

        // Проверка, что не осталось лишних данных в третьей строке
        if (ThirdStream >> ExtraValue)
        {
            throw std::runtime_error("Ошибка: В третьей строке больше значений налогов, чем указано в N");
        }

        // Проверка, что в файле нет лишних строк
        std::string ExtraLine;
        if (std::getline(ArtifactInput, ExtraLine))
        {
            // Пропускаем пустые строки в конце
            bool bIsEmpty = true;
            for (char Character : ExtraLine)
            {
                if (!isspace(static_cast<unsigned char>(Character)))
                {
                    bIsEmpty = false;
                    break;
                }
            }
            if (!bIsEmpty)
            {
                throw std::runtime_error("Ошибка: Файл содержит лишние данные после третьей строки");
            }
        }

        //FIX_ME: некорректное имя переменной 
        //int maxWeight = 0;
        int MaxWeight = 0;

        for (int Index = 1; Index <= NumArtifacts; Index++)
        {
            MaxWeight += ArtifactWeights[Index]; //нахождение макс веса для массива
        }

        // Проверка возможности набрать минимальный вес
        if (MaxWeight <= MinRequiredWeight)
        {
            throw std::runtime_error("Ошибка: Невозможно набрать требуемый минимальный вес даже при использовании всех артефактов");
        }

        //FIX_ME: некорректное имя вектора, использование одного и того же числа вместо константы (INT_MAX)
        //std::vector<std::vector<int>> dp(NumArtifacts + 1, std::vector<int>(MaxWeight + 1, 10000000));
        std::vector<std::vector<int>> DPTable(NumArtifacts + 1, std::vector<int>(MaxWeight + 1, INT_MAX));

        DPTable[0][0] = 0;

        for (int ArtifactIndex = 1; ArtifactIndex <= NumArtifacts; ArtifactIndex++)
        {
            //FIX_ME: нестандартное имя переменной в цикле 
            //for (int s = 0; s <= MaxWeight; s++) 
            for (int CurrentWeight = 0; CurrentWeight <= MaxWeight; CurrentWeight++)
            {
                DPTable[ArtifactIndex][CurrentWeight] = DPTable[ArtifactIndex - 1][CurrentWeight];
                if (CurrentWeight >= ArtifactWeights[ArtifactIndex] &&
                    DPTable[ArtifactIndex - 1][CurrentWeight - ArtifactWeights[ArtifactIndex]] != INT_MAX)
                {
                    DPTable[ArtifactIndex][CurrentWeight] = std::min(
                        DPTable[ArtifactIndex][CurrentWeight],
                        DPTable[ArtifactIndex - 1][CurrentWeight - ArtifactWeights[ArtifactIndex]] + ArtifactTaxes[ArtifactIndex]
                    );
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
        for (int CurrentWeight = MinRequiredWeight + 1; CurrentWeight <= MaxWeight; CurrentWeight++)
        {
            if (DPTable[NumArtifacts][CurrentWeight] < MinTax)
            {
                MinTax = DPTable[NumArtifacts][CurrentWeight];
                BestWeight = CurrentWeight;
            }
        }

        // Проверка, что решение найдено
        if (BestWeight == -1 || MinTax == INT_MAX)
        {
            throw std::runtime_error("Ошибка: Не удалось найти подходящее подмножество артефактов");
        }

        std::cout << "Минимальный налог: " << MinTax << std::endl;
        std::cout << "Суммарный вес: " << BestWeight << std::endl;
        std::cout << "Необходимо взять артефакты с номерами: ";

        FindAnswer(DPTable, NumArtifacts, BestWeight, ArtifactWeights, ArtifactTaxes);

        std::cout << std::endl;
        ArtifactInput.close(); // Закрываем файл
    }
    catch (const std::runtime_error& Exception)
    {
        // Обработка ошибок времени выполнения
        std::cerr << Exception.what() << std::endl;
        return 1;
    }
    catch (const std::exception& Exception)
    {
        // Обработка любых других исключений
        std::cerr << "Неизвестная ошибка: " << Exception.what() << std::endl;
        return 2;
    }

    return 0;
}