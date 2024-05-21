#ifndef TAPECONFIG_H
#define TAPECONFIG_H

// Структура для формирования конфигурации лент
struct TapeConfig 
{
    int delay_write = 0;  // По умолчанию значения задержек - 0
    int delay_read = 0;
    int delay_rewind = 0;
    int delay_forward = 0;
    int delay_backward = 0;
};

#endif // TAPECONFIG_H