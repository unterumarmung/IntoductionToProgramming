#ifndef NUMISMATISTHANDBOOK_H
#define NUMISMATISTHANDBOOK_H

#include <QMainWindow>
#include <coinitem.h>
namespace Ui {
class NumismatistHandbook;
}

class NumismatistHandbook : public QMainWindow
{
    Q_OBJECT

public:
    explicit NumismatistHandbook(QWidget *parent = nullptr);

    /*!
     * \brief Деструктор главного окна
     */
    ~NumismatistHandbook();



private:
    int currentItemIndex = 0;    // Индекс текущего элемента
    Ui::NumismatistHandbook *ui;
    CoinItem* coins;             // Указатель на динамический массив монет

private slots:
    /*!
     * \brief Слот, ответственный за включение/выключение поля количества монет
     */
    void rarityHandlerSlot();

    /*!
     * \brief Метод/слот загружает данные текущего элемента в форму
     */
    void loadDataToForm() const;

    /*!
     * \brief Слот ответственный за работу составного поля "Год выпуска"
     * \param index - индекс текущего элемента интерфейсного перечисления
     */
    void yearHandlerSlot(int index = 0);

    /*!
     * \brief Слот для загрузки данных из формы в объект
     */
    void saveDataSlot();

    /*!
     * \brief Слот обработки нажатия на кнопку выбора первой записи
     */
    void firstButtonSlot();

    /*!
     * \brief Слот обработки нажатия на кнопку выбора второй записи
     */
    void secondButtonSlot();
};


#endif // NUMISMATISTHANDBOOK_H
