#include <QCoreApplication>

#include "functionsmethmyra.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try
    {
    Data * data = new Data;
    parse(data, "file.txt");

    for (int i = 0; i < data->states.size(); i++)
    {
        std::cout << data->states[i].toStdString() << " ";
    }
    std::cout << "\n\n";
    for (int i = 0; i < data->inputs.size(); i++)
    {
        std::cout << data->inputs[i].toStdString() << " ";
        for (int j = 0; j < data->states.size(); j++)
        {
            std::cout << data->table[i][j].state.toStdString() << "/";
            std::cout << data->table[i][j].output.toStdString() << " ";
        }
        std::cout << "\n\n";
    }



    }
    catch(ErrorMethodMyra e)
    {
        qDebug() << e.GetMessage();
    }
    return 0;
}
