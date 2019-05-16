#ifndef COINITEM_H
#define COINITEM_H
#include "enumhandler.h"
#include <QString>
class CoinItem
{
public:
    QString name;       // Название монеты
    QString value;      // Номинал
    Era era;            // Эра, в которой была выпущена монета
    int year;           // Год, в который была выпущена монета
    int century;        // Век, в который была выпущена монета
    bool isRare;        // Раритетна ли монета
    int number;         // Количество монет
    Country country;    // Страна монеты
    QString qualities;  // Особые качества
};

#endif // COINITEM_H
