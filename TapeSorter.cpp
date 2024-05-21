#include "TapeSorter.h"

// Разделение исходной ленты на временные (осуществляется по заданному объёму памяти)
// Возвращает количество временных лент
size_t TapeSorter::splitInputTape(Tape& inputTape, const std::string& outputTempTapeFilesName, const int& memorySize) 
{
    if (memorySize <= 0)
    {
        std::cerr << "Error: The amount of memory must be a positive number " << std::endl;
        std::exit(1);
    }
    int countOfTmpTapes = 0;
    std::string numberInString;
    while (!inputTape.eot())
    {
        ++countOfTmpTapes;
        int currentSize = 0;
        // Создание объектов временных лент
        Tape tmpTape(outputTempTapeFilesName + std::to_string(countOfTmpTapes) + ".txt");
        while (currentSize < memorySize && !inputTape.eot())
        {
            int element = inputTape.read();
            tmpTape.write(element);
            if (!inputTape.eot())
            {
                ++currentSize;
                inputTape.forward();
                tmpTape.forward();
                continue;
            }
            if (inputTape.eot())
            {
                ++currentSize;
                break;
            }
        }
        // Запись в файл
        tmpTape.writeToFile();
    }
    return countOfTmpTapes;
}

// Сортировка каждой из временных лент и запись в файлы
void TapeSorter::sortTmpTapes(const size_t& countOfTmpTapes, const std::string& outputTempTapeFilesName) 
{
    try 
    {
        for (int i = 0; i < countOfTmpTapes; ++i) 
        {
            Tape oldTape(outputTempTapeFilesName + std::to_string(i + 1) + ".txt");
            oldTape.readFromFile();
            Tape& newTape = oldTape;
            std::sort(newTape.tape.begin(), newTape.tape.end());
            oldTape.tape = newTape.tape;
            oldTape.writeToFile();
        }
    }
    catch (const std::exception&) 
    {
        throw;
    }
}

// Общая сортировка и составление выходной ленты
void TapeSorter::sortToResultTape(Tape& outputTape, const size_t& countOfTmpTapes, const std::string& outputTempTapeFilesName) 
{
    std::vector<Tape> tmpTapes;
    std::unordered_map<int, int> firstElements;
    // Сборка всех временных лент
    for (int i = 0; i < countOfTmpTapes; ++i) 
    {
        Tape tmpTape(outputTempTapeFilesName + std::to_string(i + 1) + ".txt");
        tmpTape.readFromFile();
        tmpTapes.push_back(tmpTape);
        tmpTape.currentPosition_ = 0;
        try
        {
            firstElements.emplace(i, tmpTape.read());
        }
        catch (const std::exception&)
        {
            throw;
        }
    }

    std::ofstream resultFile(outputTape.filename_);
    std::cout << "Process of sorting...\n";

    // Проход последовательно по элементам, начиная с первых в каждой ленте
    while (true) {
        int minIndex = -1;
        int minFirstElem;
        for (const auto& elem : firstElements) 
        {
            if (minIndex == -1) {
                minIndex = elem.first;
                minFirstElem = elem.second;
            }
            else 
            {
                if (elem.second < minFirstElem) // Выбор минамального и запись индекса его ленты
                {
                    minIndex = elem.first;
                    minFirstElem = elem.second;
                }
            }
        }

        if (minIndex == -1) // Проверка
        {
            resultFile.close();
            break;
        }

        outputTape.write(minFirstElem);  // Запись очередного полученного минимального элемента
        outputTape.forward();
        Tape& tape = tmpTapes[minIndex];

        try 
        {
            tape.deleteFirstElement();  // Удаление записанного элемента и сдвиг дальше,                                  
            if (!tape.eot())            //если лента не закончилась
            {                           // Если закончилась - удаление ленты 
                firstElements[minIndex] = tape.read();
            }
            else
            {
                firstElements.erase(minIndex);
            }
        }
        catch (const std::exception&) {
            resultFile.close();
            throw;
        }
    }
    outputTape.writeToFile();               // Запись в итоговый файл
    std::cout << "Sorting is finished\n";
}
