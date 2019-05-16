#include "coinsdatabase.h"

CoinsDatabase::CoinsDatabase()
{

}

int CoinsDatabase::count() const
{
    return db.count();
}

int CoinsDatabase::append(CoinItem &record)
{
    modified = true;

    record.id = maxId++; //присваиваем записи незанятый айди и увеличиваем число айди

    return insert(record);
}

int CoinsDatabase::insert(const CoinItem &record)
{
    db[record.id] = record;

    QMutableVectorIterator<quint32> i(ids);

    int index = 0; //Индекс вставки записи в браузер с учётом сортировки

    while (i.hasNext() && db[i.next()] < record)
        index++;

    if (ids.isEmpty())
    { //база пустая
        ids.append(record.id);
    }
    else if (db[i.value()] < record)
    {
        i.insert(record.id);
    }
    else
    {
        i.previous();
        i.insert(record.id);
    }

    return index;
}

void CoinsDatabase::remove(quint32 id)
{
    modified = true;
    db.remove(id); //удалить из БД
    ids.removeOne(id); //удалить из списка айдишников
}

int CoinsDatabase::update(const CoinItem &record)
{
    modified = true;

    //временно сохранить запись и удалить из базы данных

    CoinItem tmp = record;        //временная запись для хранения данных
    quint32 oldId = tmp.id;      //сохраняем id, чтобы оставить его прежним у новой записи
    remove(oldId);                //удаляем запись по id

    return insert(tmp);
}

CoinItem CoinsDatabase::record(quint32 id) const
{
    return db[id];
}

const QVector<CoinStruct> CoinsDatabase::records() const
{
    QVector<CoinStruct> vector;
    QVectorIterator<quint32> i(ids);

    while (i.hasNext())
    {
        vector.append(db[i.next()]);
    }

    return vector;
}

bool CoinsDatabase::save(const QString &filename)
{
    bool opened = false; //успешность открытия файла

    if (!filename.isEmpty())
    {
        QFile file(filename);
        opened = file.open(QIODevice::WriteOnly);
        modified = false;
        QDataStream output(&file);

        output << db << ids << maxId;

        file.close();
    }

    return opened;
}

bool CoinsDatabase::load(const QString &filename)
{
    bool opened = false; //успешность открытия файла

    if (!filename.isEmpty()) //если имя файла не пустое
    {
        //создаем файл
        QFile file(filename);

        //открываем файл только для чтения
        opened = file.open(QIODevice::ReadOnly);

        if (opened)
        { //если открыт успешно
            modified = false;

            QDataStream output(&file);

            output >> db >> ids >> maxId;

            file.close();
        }
    }

    return opened;
}

void CoinsDatabase::clear()
{
    modified = true;
    maxId    = 0;
    db.clear();
    ids.clear();
}

bool CoinsDatabase::isModified() const
{
    return modified;
}



