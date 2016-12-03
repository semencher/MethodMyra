#ifndef FUNCTIONSMETHMYRA_H
#define FUNCTIONSMETHMYRA_H

#include <QString>

#include <QVector>

#include <QDebug>

#include <fstream>

#include <iostream>

class ErrorMethodMyra
{
    QString message;

public:
    ErrorMethodMyra()
    {
        message = "";
    }
    void SetMessage(const QString & tMessage)
    {
        message = tMessage;
    }
    QString GetMessage()
    {
        return message;
    }
};

struct Element
{
    QString state;
    QString output;
};

struct Data
{
    Element ** table;
    QVector<QString> states;
    QVector<QString> inputs;
};

void parse(Data * data, const QString & nameFile);

QVector<int> GetArrDC(const QString & interval);

bool NextVector(QString & vector, QVector<int> arr);

#endif  // FUNCTIONSMETHMYRA_H
