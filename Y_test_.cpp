#include "TapeSorter.h"

int main(int argc, char* argv[])
{
	if (argc != 3) 
	{
		std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
		return 1;
	}
	try 
	{
		// Создаются входная и выходная ленты
		Tape inputTape(argv[1]);
		Tape outputTape(argv[2]);

		// Задаются конфигурации лент
		inputTape.setConfig("tape_config.txt");
		outputTape.setConfig("tape_config.txt");

		// Размер оперативной памяти
		int memorySize = 3;

		// Входная лента читается из файла
		inputTape.readFromFile();
	
		// Создётся объекта TapeSorter для сортировки
		TapeSorter sorter;
		// Задаётся общая часть имени для временных файлов
		std::string tmpFilesName = "tmp\\output_temp_";

		// Разделение исходной ленты на временные (осуществляется по заданному объёму памяти)
		int tmpTapesCount = sorter.splitInputTape(inputTape, tmpFilesName, memorySize);

		// Сортировка данных
		sorter.sortTmpTapes(tmpTapesCount, tmpFilesName);
		sorter.sortToResultTape(outputTape, tmpTapesCount, tmpFilesName);

	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << std::endl;
		return -1;
	}

	return 0;
}
