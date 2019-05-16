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

    /*!
     * \brief Конструктор по умолчанию
     */
    CoinItem() noexcept;

    /*!
     * \brief Конструктор копирования
     * \param other - элемент копирования
     */
    CoinItem(const CoinItem& other) noexcept;

    /*!
     * \brief Параметризованный конструктор
     * \param name
     * \param value
     * \param era
     * \param year
     * \param century
     * \param isRare
     * \param number
     * \param country
     * \param qualities
     */
    CoinItem(QString name, QString value, Era era, int year, int century, bool isRare,
             int number, Country country, QString qualities) noexcept;
    /*!
     * \brief Оператор присваивания
     * \param other - элемент присваивания
     * \return - ссылка на текущий элемент
     */
    CoinItem& operator=(const CoinItem& other) noexcept;

    /*!
     * \brief Оператор сравнивает на полное равенство
     * \param other - элемент сравнивания
     * \return - результат сравнивания
     */
    bool operator==(const CoinItem& other) const;

    /*!
     * \brief Оператор сравнивает на неравенство
     * \param other - элемент сравнивания
     * \return - результат сравнивания
     */
    bool operator!=(const CoinItem& other) const;

    /*!
     * \brief Оператор < с учётом порядка сортировки
     * \param other - элемент сравнивания
     * \return - результат сравнивания
     */
    bool operator<(const CoinItem& other) const;

    /*!
     * \brief Оператор > с учётом порядка сортировки
     * \param other - элемент сравнивания
     * \return - результат сравнивания
     */
    bool operator>(const CoinItem& other) const;

    /*!
     * \brief Оператор <= с учётом порядка сортировки
     * \param other - элемент сравнивания
     * \return - результат сравнивания
     */
    bool operator<=(const CoinItem& other) const;

    /*!
     * \brief Оператор >= с учётом порядка сортировки
     * \param other - элемент сравнивания
     * \return - результат сравнивания
     */
    bool operator>=(const CoinItem& other) const;

private:
    /*!
     * \brief Функция, копирующая из other в текущий элемент
     * \param other - элемент копирования
     */
    void copy(const CoinItem& other) noexcept;
};

#endif // COINITEM_H
