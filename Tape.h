#ifndef TAPE_H
#define TAPE_H

#include "TapeInterface.h"
#include "TapeConfig.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <random>
#include <limits>
#include <thread>
#include <unordered_map>
#include <sstream>
#include <cctype>
#include <filesystem>

class Tape : public TapeInterface
{

public:
    std::string filename_;    // Имя файла, который содержит (или будет содержать) ленту
    TapeConfig config_;       // Конфигурация ленты
    int currentPosition_ = 0; // Текущая позиция головки
    std::vector<int> tape;    //

    void delay(int ms);       // Метод для задержки
    void readFromFile();      // Метод для чтения из файла
    void writeToFile();       // Метод для записи в файл

    Tape(const std::string& filename);
    ~Tape() override;

    void write(const int& elem) override;
    int& read() override;
    void forward() override;
    void backward() override;
    bool eot() const override;
    void deleteFirstElement(); // Метод для удаления первого элемента
    void setConfig(const std::string& config_filename); // Метод для установки конфигурации
};

#endif // TAPE_H