#include <QCoreApplication>

#include "functionsmethmyra.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try
    {
    Data * data = new Data;
    parse(data, "bbsse.kiss2");

    Show(data);

    QVector<int> Ri;
    QVector<int> newRi;
    GetR1(Ri, data);
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


    }
    catch(ErrorMethodMyra e)
    {
        qDebug() << e.GetMessage();
    }
    return 0;
}
