#include "numismatisthandbook.h"
#include "ui_numismatisthandbook.h"


NumismatistHandbook::NumismatistHandbook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NumismatistHandbook)
{
    ui->setupUi(this);

    //установка соединения между сигналами и элементами, видимость которых не постоянна
    ui->rarityCheckBox->setTristate(false);
    connect(ui->rarityCheckBox, SIGNAL(stateChanged(int)), this, SLOT(rarityHandlerSlot()));
    connect(ui->eraComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(yearHandlerSlot(int)));

    //ставим минимум и максимум для года
    ui->yearSpinBox->setMinimum(1);
    ui->yearSpinBox->setMaximum(QDate::currentDate().year());

    //соединение сигналов с их обработчиками
    connect(ui->savePushButton,   &QAbstractButton::clicked, this, &NumismatistHandbook::saveDataSlot);
    connect(ui->listWidget,       &QListWidget::itemClicked, this, &NumismatistHandbook::loadDataToForm);
    connect(ui->fillPushButton,   &QAbstractButton::clicked, this, &NumismatistHandbook::fillSlot);
    connect(ui->createPushButton, &QAbstractButton::clicked, this, &NumismatistHandbook::createItemSlot);
    connect(ui->deletePushButton, &QAbstractButton::clicked, this, &NumismatistHandbook::deleteItemSlot);
    connect(ui->listWidget,       &QListWidget::currentRowChanged, this, &NumismatistHandbook::rowChangedHandler);

    coinValueValidator = new CoinValueValidator();
    ui->valueLineEdit->setValidator(coinValueValidator);

    //добавление всех элементов, которые должны включаться и выключаться
    allFormWidgets << ui->nameLabel        << ui->nameLineEdit
                   << ui->valueLabel       << ui->valueLineEdit
                   << ui->dateGroupBox     << ui->eraLabel
                   << ui->eraComboBox      << ui->yearLabel
                   << ui->yearSpinBox      << ui->eraLabel
                   << ui->eraComboBox      << ui->rarityCheckBox
                   << ui->numberLabel      << ui->numberSpinBox
                   << ui->countryLabel     << ui->countryComboBox
                   << ui->qualitiesLabel   << ui->qualitiesLineEdit
                   << ui->deletePushButton << ui->savePushButton;
    rowChangedHandler(-1);
}


NumismatistHandbook::~NumismatistHandbook()
{
    delete coinValueValidator;
    delete ui;
}


/////////////////////////////////////////////////////////////
///////////////          СЛОТЫ             //////////////////
/////////////////////////////////////////////////////////////

void NumismatistHandbook::loadDataToForm()
{
    CoinItem* currentItem = coins + currentItemIndex;
    fromItemToForm(*currentItem);
}

void NumismatistHandbook::rarityHandlerSlot()
{
    bool shouldBeEnabled = ui->rarityCheckBox->isChecked();

    ui->numberSpinBox->setEnabled(shouldBeEnabled);
    ui->numberLabel->setEnabled(shouldBeEnabled);
}

void NumismatistHandbook::yearHandlerSlot(int index)
{
    Era currentEra     = indexToEra(index);
    bool isBeforeCrist = currentEra == Era::BeforeChrist;
    bool isAfterCrist  = currentEra == Era::AfterChrist;

    ui->yearLabel->setEnabled(isAfterCrist);
    ui->yearSpinBox->setEnabled(isAfterCrist);

    ui->centuryLabel->setEnabled(isBeforeCrist);
    ui->centurySpinBox->setEnabled(isBeforeCrist);
}

void NumismatistHandbook::saveDataSlot()
{
    if (ui->valueLineEdit->hasAcceptableInput())
    { //номинал монеты соответствует шаблону
        //загружаем новые данные из формы
        CoinItem newItem = fromFormToItem();

        //включаем все виджеты формы
        setWidgetsEnabled(allFormWidgets, true);

        //удаляем текущий элемент из массива
        deleteItemFromArray(coins, itemsCount, currentItemIndex);
        //добавляем новый элемент в массив
        int newIndex = insertItemToArrayAscending(coins, itemsCount, newItem);

        //обновляем форму
        updateForm();

        //обновляем текущий индекс и выделяем новую строку текущего элемента
        currentItemIndex = newIndex;
        ui->listWidget->setCurrentRow(currentItemIndex);

        yearHandlerSlot(ui->eraComboBox->currentIndex());
        rarityHandlerSlot();
    }
    else
    {
        //сообщение о том, что номинал монеты не соответсвует нужному формату
        QMessageBox::warning(this, "Корректность номинала монеты", "Номинал монеты введён неверно");
    }
}

void NumismatistHandbook::fillSlot()
{
    //создание элементов
    QList<CoinItem> sampleList;
    CoinItem sample1(
    /* name      = */ "2 рубля 1725 года",
    /* value     = */ "2 рубля",
    /* era       = */ Era::AfterChrist,
    /* year      = */ 1725,
    /* century   = */ 0,
    /* isRare    = */ false,
    /* number    = */ 0,
    /* country   = */ Country::RussianEmpire,
    /* qualities = */ "Без особых качеств"
    );

    CoinItem sample2(
    /* name      = */ "Золотая монета царя Гороха",
    /* value     = */ "1 золотец",
    /* era       = */ Era::BeforeChrist,
    /* year      = */ 0,
    /* century   = */ 5,
    /* isRare    = */ true,
    /* number    = */ 3,
    /* country   = */ Country::RussianEmpire,
    /* qualities = */ "Есть сколы"
    );

    CoinItem sample3(
    /* name      = */ "Пробная монета",
    /* value     = */ "1000 рублей",
    /* era       = */ Era::AfterChrist,
    /* year      = */ 1995,
    /* century   = */ 0,
    /* isRare    = */ true,
    /* number    = */ 10,
    /* country   = */ Country::Russia,
    /* qualities = */ "Пробная монета Ленинградского монетного двора"
    );


    CoinItem sample4(
    /* name      = */ "Хрущёвский новодел",
    /* value     = */ "20 копеек",
    /* era       = */ Era::AfterChrist,
    /* year      = */ 1952,
    /* century   = */ 0,
    /* isRare    = */ false,
    /* number    = */ 0,
    /* country   = */ Country::USSR,
    /* qualities = */ "специальный чекан"
    );

    CoinItem sample5(
    /* name      = */ "Монетовидный жетон в память кончины Императора Александра III",
    /* value     = */ "1 жетон",
    /* era       = */ Era::AfterChrist,
    /* year      = */ 1894,
    /* century   = */ 0,
    /* isRare    = */ false,
    /* number    = */ 0,
    /* country   = */ Country::RussianEmpire,
    /* qualities = */ "Серебро"
    );

    CoinItem sample6(
    /* name      = */ "Золотая царская монета Павла I",
    /* value     = */ "5 рублей",
    /* era       = */ Era::AfterChrist,
    /* year      = */ 1801,
    /* century   = */ 0,
    /* isRare    = */ false,
    /* number    = */ 0,
    /* country   = */ Country::RussianEmpire,
    /* qualities = */ "Золото 5,99г"
    );

    CoinItem sample7(
    /* name      = */ "Серебрянная царская монета Петра I",
    /* value     = */ "1 рубль",
    /* era       = */ Era::AfterChrist,
    /* year      = */ 1725,
    /* century   = */ 0,
    /* isRare    = */ true,
    /* number    = */ 5,
    /* country   = */ Country::RussianEmpire,
    /* qualities = */ "Без букв"
    );

    CoinItem sample8(
    /* name      = */ "Пробная монета",
    /* value     = */ "3 копейки",
    /* era       = */ Era::AfterChrist,
    /* year      = */ 1991,
    /* century   = */ 0,
    /* isRare    = */ true,
    /* number    = */ 10,
    /* country   = */ Country::USSR,
    /* qualities = */ "Стоимость 600 000 рублей"
    );

    CoinItem sample9(
    /* name      = */ "Серебрянная царская монета Иоанна Антоновича",
    /* value     = */ "1 полтина",
    /* era       = */ Era::AfterChrist,
    /* year      = */ 1741,
    /* century   = */ 0,
    /* isRare    = */ true,
    /* number    = */ 2,
    /* country   = */ Country::RussianEmpire,
    /* qualities = */ "Сколоты края, стоимость 8 млн"
    );

    sampleList << sample1 << sample2 << sample3 << sample4 << sample5
               << sample6 << sample7 << sample8 << sample9;

    //вставка элементов в форму
    for (auto i = sampleList.begin(); i != sampleList.end(); ++i)
    {
        currentItemIndex = insertItemToArrayAscending(coins, itemsCount, *i);
    }

    updateForm();
    ui->listWidget->setCurrentRow(itemsCount - 1);
    ui->fillPushButton->setEnabled(false);
}

void NumismatistHandbook::createItemSlot()
{
    if (itemsCount < MAX_ITEMS_COUNT)
    {
        //создание нового элемента по умолчанию
        CoinItem newItem;

        //включаем все виджеты
        setWidgetsEnabled(allFormWidgets, true);

        //вставляем новый элемент в массив
        int newIndex = insertItemToArrayAscending(coins, itemsCount, newItem);

        //обновляем форму
        updateForm();

        //обновляем текущий индекс и выделяем новую строку текущего элемента
        currentItemIndex = newIndex;
        ui->listWidget->setCurrentRow(currentItemIndex);


    }
    else
    {
        //сообщение о том, что невозможно добавить новую запись
        QMessageBox::critical(this, "Создание новой записи", "Превышение допустимого количества элементов!\n"
                                                             "Чтобы добавить новую запись удалите любую существующую.");
    }
}

void NumismatistHandbook::deleteItemSlot()
{
    int currentIndex = ui->listWidget->currentRow();

    if (currentIndex != -1)
    { //выбран существующий элемент
        //удалить из массива
        deleteItemFromArray(coins, itemsCount, currentIndex);
    }

    //обновить форму
    updateForm();

    //выбор нового индекса
    int newIndex = currentIndex;
    if (currentIndex >= itemsCount)
         newIndex -= 1;

    ui->listWidget->setCurrentRow(newIndex);
}

void NumismatistHandbook::rowChangedHandler(int currentRow)
{
    if (itemsCount == 0)
    { //были удалены все элементы
        fromItemToForm(CoinItem());
        itemsCount = 0;

        setWidgetsEnabled(allFormWidgets, false);

        ui->fillPushButton->setEnabled(true);
    }
    else if (currentRow != -1)
    { //выбран существующий элемент

        setWidgetsEnabled(allFormWidgets, true);
        currentItemIndex = currentRow;
        fromItemToForm(coins[currentItemIndex]);
        ui->fillPushButton->setEnabled(false);

        yearHandlerSlot(ui->eraComboBox->currentIndex());
        rarityHandlerSlot();
    }
    else
    { //строка сбросилась
        fromItemToForm(CoinItem());
        setWidgetsEnabled(allFormWidgets, false);
        ui->fillPushButton->setEnabled(true);
    }
}

/////////////////////////////////////////////////////////////
///////////    Методы загрузки из/в форму     //////////////
////////////////////////////////////////////////////////////
CoinItem NumismatistHandbook::fromFormToItem()
{
    return CoinItem (
                /* name      = */ ui->nameLineEdit->text(),
                /* value     = */ ui->valueLineEdit->text(),
                /* era       = */ indexToEra(ui->eraComboBox->currentIndex()),
                /* year      = */ ui->yearSpinBox->value(),
                /* century   = */ ui->centurySpinBox->value(),
                /* isRare    = */ ui->rarityCheckBox->isChecked(),
                /* number    = */ ui->numberSpinBox->value(),
                /* country   = */ indexToCountry(ui->countryComboBox->currentIndex()),
                /* qualities = */ ui->qualitiesLineEdit->text()
    );
}

void NumismatistHandbook::fromItemToForm(const CoinItem &item)
{
    ui->nameLineEdit     ->setText(item.name);
    ui->valueLineEdit    ->setText(item.value);
    ui->eraComboBox      ->setCurrentIndex(eraToIndex(item.era));
    ui->yearSpinBox      ->setValue(item.year);
    ui->centurySpinBox   ->setValue(item.century);
    ui->rarityCheckBox   ->setChecked(item.isRare);
    ui->numberSpinBox    ->setValue(item.number);
    ui->countryComboBox  ->setCurrentIndex(countryToIndex(item.country));
    ui->qualitiesLineEdit->setText(item.qualities);
    rarityHandlerSlot();
}

/////////////////////////////////////////////////////////////
///////////       Работа с QListWidget        //////////////
////////////////////////////////////////////////////////////

QListWidgetItem* createWidgetItem(const CoinItem& item)
{
    QString label;

    (label += item.name) += "\t";
    if (item.era == Era::AfterChrist)
    {
        label += QString::number(item.year);
    }
    else
    {
        label += QString::number(item.century) += " в. до н. э.";
    }

    if (item.isRare)
    {
        (label += "\t") += QString::number(item.number) += " шт.";
    }
    return new QListWidgetItem(label);
}

void NumismatistHandbook::updateForm()
{
    //удаление всех элементов из формы
    for (int i = ui->listWidget->count() - 1; i != -1; i = ui->listWidget->count() - 1)
    {
        //удаление элемента из формы (takeItem) и из памяти (delete)
        delete ui->listWidget->takeItem(i);
    }

    //загрузка всех элементов в форму
    for (int i = 0; i < itemsCount; ++i)
    {
        QListWidgetItem* currentItem = createWidgetItem(coins[i]);
        ui->listWidget->insertItem(i, currentItem);
    }
}

/////////////////////////////////////////////////////////////
///////////         Работа с массивами        //////////////
////////////////////////////////////////////////////////////
template<typename T>
int insertItemToArrayAscending(T items[], int& size, const T& itemToInsert)
{
    //поиск позиции для вставки
    int newItemPosition;
    for (newItemPosition = 0; newItemPosition < size &&
       items[newItemPosition] < itemToInsert; newItemPosition++);

    //сдвиг элементов вправо
    int i = size - 1;
    for ( ; i >= newItemPosition; i--)
            items[i + 1] = items[i];

    //вставка нового элемента
    items[newItemPosition] = itemToInsert;
    size += 1;
    return newItemPosition;
}

template<typename T>
int deleteItemFromArray(T items[], int& size, int indexToDelete)
{
    for (int i = indexToDelete; i < size - 1; ++i)
    {
         items[i] = items[i + 1];
    }
    size -= 1;
    return size;
}

/////////////////////////////////////////////////////////////
///////////             Остальное             //////////////
////////////////////////////////////////////////////////////
void setWidgetsEnabled(const QVector<QWidget*>& widgets, bool value)
{
    for (auto i = widgets.begin(); i != widgets.end(); ++i)
        (*i)->setEnabled(value);
}
