#include "Tape.h"

Tape::Tape(const std::string& filename) : filename_(filename) {}
Tape::~Tape() = default;

bool isNumber(const std::string& str);
bool isFileHasCorrectFormat(std::string filename);

// Загрузка конфигурации лент из файла
TapeConfig loadTapeConfig(const std::string& filename)
{
    TapeConfig config;
    std::ifstream file(filename);
    // Проверка на пустоту файла
    if (file.peek() == EOF)
    {
        std::cerr << "Error: File " << filename << " is empty\n" << std::endl;
        std::exit(1);
    }
    // Проверка на корректность файла
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open configuration file " << filename << std::endl;
        std::exit(1);
    }
    if (!isFileHasCorrectFormat(filename))
    {
        std::cerr << "Error: Coonfiguration file " << filename << " has uncorrect format" << std::endl;
        std::exit(1);
    }
    file >> config.delay_write >> config.delay_read >> config.delay_rewind >> config.delay_forward >> config.delay_backward;
    file.close();
    return config;
}

void Tape::setConfig(const std::string& config_filename)
{
    config_ = loadTapeConfig(config_filename);
}

void Tape::delay(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool Tape::eot() const
{
    return currentPosition_ >= tape.size() || currentPosition_ < 0;
}

int& Tape::read() 
{
    delay(config_.delay_read);
    return tape[currentPosition_];
}

void Tape::write(const int& elem) 
{
    delay(config_.delay_write);
    if (currentPosition_ >= tape.size()) 
    {
        tape.push_back(elem);
    }
    else 
    {
        tape[currentPosition_] = elem;
    }
}

void Tape::deleteFirstElement()
{
    try
    {       
        tape.erase(tape.begin());       
    }
    catch (const std::exception&) 
    {
        throw;
    }
}

// Движение ленты вперёд (к следующему элементу) 
void Tape::forward() 
{
    delay(config_.delay_forward);
    currentPosition_++;
}

// Движение ленты назад (к предыдущему элементу)
void Tape::backward() 
{
    delay(config_.delay_backward);
    currentPosition_--;
}

// Чтение целой ленты из файла
void Tape::readFromFile()   
{
    std::fstream file_(filename_);
    // Проверка на корректность файла
    if (file_.peek() == EOF)
    {
        std::cerr << "Error: File " << filename_ << " is empty\n" << std::endl;
        std::exit(1);
    }
    if (!file_.is_open())
    {
        std::cerr << "Error: Could not open file " << filename_ << std::endl;
        std::exit(1);
    }
    if (!isFileHasCorrectFormat(filename_))
    {
        std::cerr << "Error: File " << filename_ << " has uncorrect format\n" << std::endl;
        std::exit(1);
    }
    if (file_.peek() == std::fstream::traits_type::eof()) 
    {
        file_.clear();
        return;
    }
    file_.seekg(std::ios::beg);   // Установка позиции на начало файла
    // Считывание элементов и добавление их в ленту
    int element;
    while (!file_.eof()) 
    {
        file_ >> element;
        tape.push_back(element);
    }
    file_.clear();
    file_.close();
}

void Tape::writeToFile() 
{
    std::ofstream file_(filename_);
    if (tape.size() >= 2)
    {
        for (size_t i = 0; i < tape.size() - 1; ++i)
        {
            file_ << tape[i] << " ";
        }
    }
    file_ << tape.back();
    file_.close();
}

bool isFileHasCorrectFormat(std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    bool valid = true;

    while (getline(file, line)) // Проверка на то, что строки содержат только числа с пробелами
    {
        std::stringstream ss(line);
        std::string number;
        while (getline(ss, number, ' ')) 
        {
            if (!isNumber(number)) 
            {
                valid = false;
                break;
            }
        }
        if (!valid) 
        {
            break;
        }
    }
    file.close();
    return valid;
}

bool isNumber(const std::string& str) 
{
    // Проверка на то, что строка не пустая
    if (str.empty()) 
    {
        return false;
    }

    // Проверка на то, что первый символ - цифра или знак минуса
    if (!isdigit(str[0]) && str[0] != '-') 
    {
        return false;
    }

    // Проверка на то, что все остальные символы - цифры
    for (size_t i = 1; i < str.size(); ++i) 
    {
        if (!isdigit(str[i])) 
        {
            return false;
        }
    }

    return true;
}
