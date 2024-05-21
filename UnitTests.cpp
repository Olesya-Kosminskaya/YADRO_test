#include "TapeSorter.h"

 //Тест 1: Чтение из файла
void TEST1_READ_FROM_FILE()
{
    Tape inputTape("U_tests\\test1.txt");   
    inputTape.setConfig("tape_config.txt");
    int memorySize = 3; 
    inputTape.readFromFile();
    std::vector<int> test_vector = { 1, 3, 5, 7 };
    if (inputTape.tape == test_vector)
    {
        std::cout << "Test 1: OK" << std::endl;
    }
    else
    {
        std::cout << "Test 1: FAILED" << std::endl;
    }
}

//Тест 2: Чтение из файла с ошибкой (должно быть выведено сообщение об ошибке)
void TEST2_READ_FROM_FILE()
{
    Tape inputTape("U_tests\\test2.txt");
    inputTape.setConfig("tape_config.txt");
    int memorySize = 3;
    inputTape.readFromFile();
}

//Тест 3: Запись в файл
void TEST3_WRITE_TO_FILE()
{
    Tape inputTape("U_tests\\test1.txt");
    inputTape.setConfig("tape_config.txt");
    Tape outputTape("U_tests\\test3.txt");
    outputTape.setConfig("tape_config.txt");
    int memorySize = 3;
    inputTape.readFromFile();
    outputTape.tape = inputTape.tape;
    outputTape.writeToFile();
    outputTape.readFromFile();
    std::vector<int> test_vector = { 1, 3, 5, 7 };
    if (outputTape.tape == test_vector)
    {
        std::cout << "Test 3: OK" << std::endl;
    }
    else
    {
        std::cout << "Test 3: FAILED" << std::endl;
    }
}

// Тест 4: Сортировка отсортированной ленты
void TEST4_SORT_SORTED_TAPE()
{
    Tape inputTape("U_tests\\test4.txt");
    inputTape.setConfig("tape_config.txt");
    Tape outputTape("U_tests\\test4.txt");
    outputTape.setConfig("tape_config.txt");
    int memorySize = 3;
    inputTape.readFromFile();
    TapeSorter sorter;
    std::string tmpFilesName = "U_tests\\test4_temp_";
    int tmpTapesCount = sorter.splitInputTape(inputTape, tmpFilesName, memorySize);
    sorter.sortTmpTapes(tmpTapesCount, tmpFilesName);
    sorter.sortToResultTape(outputTape, tmpTapesCount, tmpFilesName);
    if (outputTape.tape == inputTape.tape)
    {
        std::cout << "Test 4: OK" << std::endl;
    }
    else
    {
        std::cout << "Test 4: FAILED" << std::endl;
    }
}

//Тест 5: Сортировка ленты с отрицательными значениями
void TEST5_SORT_NEGATIVE_TAPE()
{
    Tape inputTape("U_tests\\test5.txt");
    inputTape.setConfig("tape_config.txt");
    Tape outputTape("U_tests\\test5_out.txt");
    outputTape.setConfig("tape_config.txt");
    int memorySize = 3;
    inputTape.readFromFile();
    std::vector<int> test_vector = { -92, -37, -36, -8, -7, -6 , -5, -2, -1, -1 };
    TapeSorter sorter;
    std::string tmpFilesName = "U_tests\\tmp5\\test5_temp_";
    int tmpTapesCount = sorter.splitInputTape(inputTape, tmpFilesName, memorySize);
    sorter.sortTmpTapes(tmpTapesCount, tmpFilesName);
    sorter.sortToResultTape(outputTape, tmpTapesCount, tmpFilesName);
    if (outputTape.tape == test_vector)
    {
        std::cout << "Test 5: OK" << std::endl;
    }
    else
    {
        std::cout << "Test 5: FAILED" << std::endl;
    }
}

//Тест 6: Сортировка ленты с различными значениями
void TEST6_SORT_DIFFERENT_TAPE()
{
    Tape inputTape("U_tests\\test6.txt");
    inputTape.setConfig("tape_config.txt");
    Tape outputTape("U_tests\\test6_out.txt");
    outputTape.setConfig("tape_config.txt");
    int memorySize = 3;
    inputTape.readFromFile();
    std::vector<int> test_vector = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };
    TapeSorter sorter;
    std::string tmpFilesName = "U_tests\\tmp6\\test6_temp_";
    int tmpTapesCount = sorter.splitInputTape(inputTape, tmpFilesName, memorySize);
    sorter.sortTmpTapes(tmpTapesCount, tmpFilesName);
    sorter.sortToResultTape(outputTape, tmpTapesCount, tmpFilesName);
    if (outputTape.tape == test_vector)
    {
        std::cout << "Test 6: OK" << std::endl;
    }
    else
    {
        std::cout << "Test 6: FAILED" << std::endl;
    }
}

