#include "coinitem.h"
#include <QTextCodec>

CoinItem::CoinItem() noexcept
    : name("Имя монеты"), value("1 номинал"), era(Era::AfterChrist), year(1999),
      century(0), isRare(false), number(0), country(Country::Russia), qualities()
{

}

void CoinItem::copy(const CoinItem &other) noexcept
{
    id        = other.id;
    name      = other.name;
    value     = other.value;
    era       = other.era;
    year      = other.year;
    century   = other.century;
    isRare    = other.isRare;
    number    = other.number;
    country   = other.country;
    qualities = other.qualities;
}

CoinItem::CoinItem(QString name, QString value, Era era, int year, int century, bool isRare, int number, Country country, QString qualities) noexcept
{
    this->name = name;
    this->value = value;
    this->era = era;
    this->year = year;
    this->century = century;
    this->isRare = isRare;
    this->number = number;
    this->country = country;
    this->qualities = qualities;
}

CoinItem::CoinItem(const CoinItem &other) noexcept
{
    copy(other);
}


CoinItem& CoinItem::operator=(const CoinItem &other) noexcept
{
    copy(other);
    return *this;
}

bool CoinItem::operator==(const CoinItem &other) const
{
    return name == other.name && value == other.value && era == other.era && year == other.year && century == other.century
            && isRare == other.isRare && number == other.number && country == other.country && qualities == other.qualities;
}

bool CoinItem::operator!=(const CoinItem &other) const
{
    return !((*this) == other);
}

bool CoinItem::operator<(const CoinItem &other) const
{
    bool isSmaller = false;

    if (!other.isRare && this->isRare)
    {
        isSmaller = true;
    }
    else if (other.isRare == this->isRare)
    {
        if (  (this->era == Era::AfterChrist && other.era == Era::AfterChrist && this->year < other.year)
           || (this->era == Era::BeforeChrist && other.era == Era::BeforeChrist && this->century > other.century)
           || (this->era == Era::BeforeChrist && other.era == Era::AfterChrist)
           )
            isSmaller = true;
        else if (this->year == other.year)
        {
            if (this->name < other.name)
                isSmaller = true;
        }
    }
    return isSmaller;
}
bool CoinItem::operator>=(const CoinItem &other) const
{
    return !(*this < other);
}

bool CoinItem::operator<=(const CoinItem &other) const
{
    return (*this < other) || *this == other;
}

bool CoinItem::operator>(const CoinItem &other) const
{
    return !(*this <= other);
}


QDataStream &operator<<(QDataStream &out, const CoinItem &data)
{
    out << data.id << data.name << data.value << (int)data.era << data.year
        << data.century << data.isRare << data.number << (int)data.country << data.qualities;
    return out;
}

QDataStream &operator>>(QDataStream &in, CoinItem &data)
{
    int era;
    int country;

    in >> data.id >> data.name >> data.value >> era >> data.year
        >> data.century >> data.isRare >> data.number >> country >> data.qualities;
    data.country = indexToCountry(country);
    data.era     = indexToEra(era);

    return in;
}
