#ifndef TAPESORTER_H
#define TAPESORTER_H

#include "Tape.h"

class TapeSorter
{
private:
public:

    size_t splitInputTape(Tape& inputTape, const std::string& outputTempTapeFilesName, const int& countElementsInTempTape);
    void sortTmpTapes(const size_t& tempTapesCount, const std::string& outputTempTapeFilesName);
    void sortToResultTape(Tape& outputTape, const size_t& tempTapesCount, const std::string& outputTempTapeFilesName);

public:
    TapeSorter() = default;
    ~TapeSorter() = default;

};


#endif // TAPESORTER_H
