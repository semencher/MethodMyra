#include <QCoreApplication>

#include "functionsmethmyra.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try
    {
    Data * data = new Data;
    QString beginState = parse(data, "s27.kiss2");

    Show(data);
    DeleteDC(data, beginState);
    Show(data);

    QVector<int> Ri;
    QVector<int> newRi;
    GetR1(Ri, data);
    Show(data);
    int size = data->states.size();
    for (int i = 0; i < size; i++)
    {
        std::cout << Ri[i] << " ";
    }
    std::cout << "\n";
    newRi = GetRi(Ri, data);

    while(newRi != Ri)
    {
        Ri = newRi;
        for (int i = 0; i < size; i++)
        {
            std::cout << newRi[i] << " ";
        }
        std::cout << "\n";
        newRi = GetRi(Ri, data);
    }

    NewFSM(data, Ri);
    Show(data);
    out(data, "fileOut.txt");

    }
    catch(ErrorMethodMyra e)
    {
        qDebug() << e.GetMessage();
    }
    return 0;
}
