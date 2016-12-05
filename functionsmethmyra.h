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

QString parse(Data * data, const QString & nameFile);

QVector<int> GetArrDC(const QString & interval);

bool NextVector(QString & vector, QVector<int> arr);

void Show(Data * data);

void GetR1(QVector<int> & R1, Data * data);

bool compareForR1(Data * data, int i, int j);

QVector<int> GetRi(QVector<int> & Ri, Data * data);

bool compareForRi(Data * data, int i, int j, QVector<int> Ri);

void DeleteDC(Data * data, const QString & beginState);

void out(Data * data, const QString & nameFile);

void NewFSM(Data * data, QVector<int> Ri);

void FullDefine(QVector<int> & R1, Data * data);

#endif  // FUNCTIONSMETHMYRA_H
