#ifndef ENUMHADLER_H
#define ENUMHADLER_H

/*!
 * \brief Перечисление стран
 */
enum class Country
{
    RussianEmpire,
    USSR,
    Russia
};

/*!
 * \brief Перечисление эр
 */
enum class Era
{
    BeforeChrist,
    AfterChrist
};

/*!
 * \brief Функция для перевода элемента Country в соответствующий индекс интерфейсного перечисления
 * \param country - элемент Country
 * \return - соответствующий индекс
 */
int countryToIndex(Country country);

/*!
 * \brief Функция для перевода индекса из интерфейсного перечисления в соответствующий элемент Era
 * \param index - индекс из интерфейсного перечисления
 * \return - соответствующий элемент Era
 */
Era indexToEra(int index);

/*!
 * \brief Функция для перевода элемента Era в соответствующий индекс интерфейсного перечисления
 * \param era - элемент Era
 * \return - соответствующий индекс
 */
int eraToIndex(Era era);

/*!
 * \brief Функция для перевода индекса из интерфейсного перечисления в элемент Country
 * \param index - индекс интерфейского перечисления
 * \return - соответствующий элемент Country
 */
Country indexToCountry(int index);

#endif // ENUMHADLER_H
