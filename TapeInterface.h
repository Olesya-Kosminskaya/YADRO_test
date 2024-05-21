#ifndef TAPEINTERFACE_H
#define TAPEINTERFACE_H

class TapeInterface {     // Интерфейс для работы с устройством типа лента
public:
    virtual ~TapeInterface() = default;         // Деструктор (создающийся по умолчанию)
    virtual void write(const int& elem) = 0;    // Метод для чтения
    virtual int& read() = 0;                    // Метод для записи
    virtual void forward() = 0;                 // Метод для продвижения вперёд
    virtual void backward() = 0;                // Метод для продвижения назад
    virtual bool eot() const = 0;               // Метод для проверки на то, не был ли достигнут конец ленты
};

#endif // TAPEINTERFACE_H

