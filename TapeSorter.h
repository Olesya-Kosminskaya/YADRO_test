#ifndef TAPESORTER_H
#define TAPESORTER_H

#include "Tape.h"

class TapeSorter
{
private:
public:

// Разделение исходной ленты на временные (осуществляется по заданному объёму памяти)    
    size_t splitInputTape(Tape& inputTape, const std::string& outputTempTapeFilesName, const int& countElementsInTempTape);
// Сортировка каждой из временных лент и запись в файлы
    void sortTmpTapes(const size_t& tempTapesCount, const std::string& outputTempTapeFilesName);
// Общая сортировка и составление выходной ленты
    void sortToResultTape(Tape& outputTape, const size_t& tempTapesCount, const std::string& outputTempTapeFilesName);

public:
    TapeSorter() = default;
    ~TapeSorter() = default;

};


#endif // TAPESORTER_H
