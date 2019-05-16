#ifndef NUMISMATISTHANDBOOK_H
#define NUMISMATISTHANDBOOK_H

#include <QMainWindow>
#include <coinitem.h>
#include "enumhandler.h"
#include <QDate>
#include <coinvaluevalidator.h>
#include <QMessageBox>
#include <QTextCodec>
#include <QListWidget>

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
    static constexpr int MAX_ITEMS_COUNT = 100; //максимальное количество элементов
    int currentItemIndex = -1;                  //индекс текущего элемента
    int itemsCount = 0;                         //количество элементов
    Ui::NumismatistHandbook *ui;
    CoinItem coins[MAX_ITEMS_COUNT];            //массив элементов
    QVector<QWidget*> allFormWidgets;           //массив всех элементов формы
    QValidator* coinValueValidator;             //валидатор для номинала монеты

    /*!
     * \brief Взять текущие значения полей из формы и создать на их основе элемент
     * \return - созданный элемент
     */
    CoinItem fromFormToItem();
    /*!
     * \brief Загрузить элемент в форму
     * \param item - данный элемент
     */
    void fromItemToForm(const CoinItem& item = CoinItem());
    /*!
     * \brief Удалить элемент их массива и формы
     * \param index - индекс удаляемого элемента
     */
    void deleteItemEverywhere(int index);
    /*!
     * \brief Вставить элемент в массив и форму
     * \param item - вставляемый элемент
     * \return - позиция нового элемента
     */
    int insertItemEverywhere(const CoinItem& item);

    /*!
     * \brief Метод, обновляющий форму
     */
    void updateForm();
private slots:
    /*!
     * \brief Слот, ответственный за включение/выключение поля количества монет
     */
    void rarityHandlerSlot();
    /*!
     * \brief Метод/слот загружает данные текущего элемента в форму
     */
    void loadDataToForm();
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
     * \brief Заполнение базы данных сэмплами
     */
    void fillSlot();
    /*!
     * \brief Обработка нажатия на кнопку "Создать"
     */
    void createItemSlot();
    /*!
     * \brief Обработка нажатия на кнопку "Удалить"
     */
    void deleteItemSlot();
    /*!
     * \brief Обработка изменения текущего элемента в QListWidget
     * \param currentRow - новая позиция
     */
    void rowChangedHandler(int currentRow = -1);
};

/*!
 * \brief Для массива виджетов установить их активность
 * \param widgets - массив указателей на виджеты
 * \param value - включен или нет
 */
void setWidgetsEnabled(const QVector<QWidget*>& widgets, bool value);

/*!
 * \brief Создать элемент QListWidget согласно условию задания
 * \param item - объект CoinItem, для которого создаётся QListWidget
 * \return - созданный элемент QListWidget
 */
QListWidgetItem* createWidgetItem(const CoinItem& item);

/*!
 * typename T - тип элементов массива
 * Для этого типа должны быть определены operator< и operator=
 */
template<typename T>
/*!
 * \brief Вставить элемент в массив в порядке возрастания
 * \param items - данный массив
 * \param size - фактический размер массив
 * \param itemToInsert - элемент для вставки
 * \return - положение вставленного символа
 */
int insertItemToArrayAscending(T items[], int& size, const T& itemToInsert);

/*!
 * typename T - тип элементов массива
 * Для этого типа должен быть определен operator=
 */
template<typename T>
/*!
 * \brief Удалить элемент из массива по индексу
 * \param items - данный массив
 * \param size - фактический размер массива
 * \param indexToDelete - индекс удаляемого элемента
 * \return - новая длина массива
 */
int deleteItemFromArray(T items[], int& size, int indexToDelete);

#endif // NUMISMATISTHANDBOOK_H
