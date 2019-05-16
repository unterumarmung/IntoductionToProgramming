#include "numismatisthandbook.h"
#include "ui_numismatisthandbook.h"
#include "enumhandler.h"
#include <QDate>
#include <coinvaluevalidator.h>
#include <QMessageBox>
#include <QTextCodec>

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

    //инициализация массива элементов
    coins = new CoinItem[2];
    coins[0] = CoinItem();
    coins[1] = CoinItem();

    //соединение сигналов кнопок управления с обработчиками их нажатий
    connect(ui->firstPushButton, &QAbstractButton::clicked, this, &NumismatistHandbook::firstButtonSlot);
    connect(ui->secondPushButton, &QAbstractButton::clicked, this, &NumismatistHandbook::secondButtonSlot);
    connect(ui->savePushButton, &QAbstractButton::clicked, this, &NumismatistHandbook::saveDataSlot);
    connect(ui->showPushButton, &QAbstractButton::clicked, this, &NumismatistHandbook::loadDataToForm);


    //первичная проверка видимости полей
    firstButtonSlot();
    rarityHandlerSlot();
    yearHandlerSlot();

    QValidator* coinValueValidator = new CoinValueValidator();
    ui->valueLineEdit->setValidator(coinValueValidator);
}


NumismatistHandbook::~NumismatistHandbook()
{
    delete ui;
}


void NumismatistHandbook::loadDataToForm() const
{
    CoinItem* currentItem = coins + currentItemIndex;

    ui->nameLineEdit->setText(currentItem->name);
    ui->valueLineEdit->setText(currentItem->value);
    ui->eraComboBox->setCurrentIndex(eraToIndex(currentItem->era));
    ui->yearSpinBox->setValue(currentItem->year);
    ui->centurySpinBox->setValue(currentItem->century);
    ui->rarityCheckBox->setChecked(currentItem->isRare);
    ui->numberSpinBox->setValue(currentItem->number);
    ui->countryComboBox->setCurrentIndex(countryToIndex(currentItem->country));
    ui->qualitiesLineEdit->setText(currentItem->qualities);
}


void NumismatistHandbook::rarityHandlerSlot()
{
    bool shouldBeEnabled = ui->rarityCheckBox->isChecked();

    ui->numberSpinBox->setEnabled(shouldBeEnabled);
    ui->numberLabel->setEnabled(shouldBeEnabled);
}


void NumismatistHandbook::yearHandlerSlot(int index)
{
    Era currentEra = indexToEra(index);
    bool isBeforeCrist = currentEra == Era::BeforeChrist;
    bool isAfterCrist = currentEra == Era::AfterChrist;

    ui->yearLabel->setEnabled(isAfterCrist);
    ui->yearSpinBox->setEnabled(isAfterCrist);

    ui->centuryLabel->setEnabled(isBeforeCrist);
    ui->centurySpinBox->setEnabled(isBeforeCrist);
}

void NumismatistHandbook::saveDataSlot()
{
    if (ui->valueLineEdit->hasAcceptableInput())
    { // Номинал монеты соответствует шаблону
        CoinItem* currentItem = coins + currentItemIndex;

        currentItem->name = ui->nameLineEdit->text();
        currentItem->value = (ui->valueLineEdit->text());
        currentItem->era = (indexToEra(ui->eraComboBox->currentIndex()));
        currentItem->year = (ui->yearSpinBox->value());
        currentItem->century = (ui->centurySpinBox->value());
        currentItem->isRare = (ui->rarityCheckBox->isChecked());
        currentItem->number = (ui->numberSpinBox->value());
        currentItem->qualities = (ui->qualitiesLineEdit->text());
    }
    else
    {
        QTextCodec* codec = QTextCodec::codecForName("utf-8");
        QMessageBox::warning(this, codec->toUnicode("Корректность номинала монеты"), codec->toUnicode("Номинал монеты введён неверно"));
    }
}


void NumismatistHandbook::firstButtonSlot()
{
    ui->secondPushButton->setEnabled(true);
    ui->firstPushButton->setEnabled(false);

    currentItemIndex = 0;
    loadDataToForm();
}


void NumismatistHandbook::secondButtonSlot()
{
    ui->secondPushButton->setEnabled(false);
    ui->firstPushButton->setEnabled(true);

    currentItemIndex = 1;
    loadDataToForm();
}

