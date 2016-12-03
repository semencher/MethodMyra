#include "functionsmethmyra.h"

QString beginState = "";

void parsePrivate(Data * data, const QString nameFile);

QString parse(Data * data, const QString & nameFile)
{
    std::ifstream file;
    std::string nameFileStd = nameFile.toStdString();
    file.open(nameFileStd, std::ios::in);

    if (!file)
    {
        ErrorMethodMyra e;
        e.SetMessage("Unable to open file!");
        throw e;
    }

    int icount=0;
    int ocount=0;
    int pcount=0;

    ErrorMethodMyra e;
    e.SetMessage("Error of data!");

    char sym;
    while(sym != '.')
    {
        if (file.eof())
        {
            throw e;
        }
        sym = file.get();
    }

    while (sym == '.')
    {
        if (file.eof())
        {
            throw e;
        }
        sym = file.get();
        if (file.eof())
        {
            throw e;
        }
        switch (sym)
        {
            case 'i':
                if (file.eof())
                {
                    throw e;
                }
                file >> icount;
                if (icount<=0)
                    throw e;
                while(sym != '.' && sym != '1' && sym != '0' && sym != '-')
                {
                    if (file.eof())
                    {
                        throw e;
                    }
                    sym = file.get();
                }
                continue;
            case 'o':
                if (file.eof())
                {
                    throw e;
                }
                file >> ocount;
                if (ocount<=0)
                    throw e;
                while(sym != '.' && sym != '1' && sym != '0' && sym != '-')
                {
                    if (file.eof())
                    {
                        throw e;
                    }
                    sym = file.get();
                }
                continue;
            case 'p':
                if (file.eof())
                {
                    throw e;
                }
                file >> pcount;
                if (pcount<=0)
                    throw e;
                while(sym != '.' && sym != '1' && sym != '0' && sym != '-')
                {
                    if (file.eof())
                    {
                        throw e;
                    }
                    sym = file.get();
                }
                continue;
            case 's':
                int tmp;
                if (file.eof())
                {
                    throw e;
                }
                file >> tmp;
                while(sym != '.' && sym != '1' && sym != '0' && sym != '-')
                {
                    if (file.eof())
                    {
                        throw e;
                    }
                    sym = file.get();
                }
                continue;
            default:
                {
                   throw e;
                }
        }
    }

    QString input = "";
    QString output = "";
    QString iState = "";
    QString oState = "";

    QString beginState = "";

    for (int i = 0; i < pcount; i++)
    {
        for (int j = 0; j < icount; j++)
        {
            if (sym == '1' || sym == '0' || sym == '-')
            {
                input = input + sym;
            }
            else
            {
                throw e;
            }
            if (file.eof())
            {
                throw e;
            }
            sym = file.get();
        }
        while(sym == ' ')
        {
            if (file.eof())
            {
                throw e;
            }
            sym = file.get();
        }

        while(sym != ' ')
        {
            iState = iState + sym;
            if (file.eof())
            {
                throw e;
            }
            sym = file.get();
        }
        if (beginState == "")
        {
            beginState = iState;
        }

        while(sym == ' ')
        {
            if (file.eof())
            {
                throw e;
            }
            sym = file.get();
        }

        while(sym != ' ')
        {
            oState = oState + sym;
            if (file.eof())
            {
                throw e;
            }
            sym = file.get();
        }

        while(sym == ' ')
        {
            if (file.eof())
            {
                throw e;
            }
            sym = file.get();
        }

        for (int k = 0; k < ocount; k++)
        {
            if (sym == '1' || sym == '0' || sym == '-')
            {
                output = output + sym;
            }
            else
            {
                throw e;
            }
            if (file.eof())
            {
                throw e;
            }
            sym = file.get();
        }
        if (i < pcount - 1)
        {
            while(sym != '1' && sym != '0' && sym != '-')
            {
                if (file.eof())
                {
                    throw e;
                }
                sym = file.get();
            }
        }
        QVector<int> arr = GetArrDC(input);
        if (arr.size() == 0)
        {
            if (!data->inputs.contains(input))
            {
                data->inputs.push_back(input);
            }
            if (!data->states.contains(iState))
            {
                data->states.push_back(iState);
            }
            if (!data->states.contains(oState))
            {
                data->states.push_back(oState);
            }
        }
        else
        {
            while(NextVector(input, arr))
            {
                if (!data->inputs.contains(input))
                {
                    data->inputs.push_back(input);
                }
                if (!data->states.contains(iState))
                {
                    data->states.push_back(iState);
                }
                if (!data->states.contains(oState))
                {
                    data->states.push_back(oState);
                }
            }
        }
        input = "";
        output = "";
        iState = "";
        oState = "";
    }
    file.close();
    parsePrivate(data, nameFile);
    return beginState;
}

void parsePrivate(Data * data, const QString nameFile)
{
    std::ifstream file;
    std::string nameFileStd = nameFile.toStdString();
    file.open(nameFileStd, std::ios::in);

    if (!file)
    {
        ErrorMethodMyra e;
        e.SetMessage("Unable to open file!");
        throw e;
    }

    data->table = new Element *[data->inputs.size()];
    int sizeInputs = data->inputs.size();
    int sizeStates = data->states.size();
    for (int i = 0; i < sizeInputs; i++)
    {
        data->table[i] = new Element[sizeStates];
    }

    int icount = 0;
    int ocount = 0;
    int pcount = 0;

    char sym;
    while(sym != '.')
    {
        sym = file.get();
    }

    while (sym == '.')
    {
        sym = file.get();
        switch (sym)
        {
            case 'i':
                file >> icount;
                while(sym != '.' && sym != '1' && sym != '0' && sym != '-')
                {
                    sym = file.get();
                }
                continue;
            case 'o':
                file >> ocount;
                while(sym != '.' && sym != '1' && sym != '0' && sym != '-')
                {
                    sym = file.get();
                }
                continue;
            case 'p':
                file >> pcount;
                while(sym != '.' && sym != '1' && sym != '0' && sym != '-')
                {
                    sym = file.get();
                }
                continue;
            case 's':
                int tmp;
                file >> tmp;
                while(sym != '.' && sym != '1' && sym != '0' && sym != '-')
                {
                    sym = file.get();
                }
                continue;
        }
    }

    QString input = "";
    QString output = "";
    QString iState = "";
    QString oState = "";

    for (int i = 0; i < pcount; i++)
    {
        for (int j = 0; j < icount; j++)
        {
            if (sym == '1' || sym == '0' || sym == '-')
            {
                input = input + sym;
            }
            sym = file.get();
        }
        while(sym == ' ')
        {
            sym = file.get();
        }

        while(sym != ' ')
        {
            iState = iState + sym;
            sym = file.get();
        }

        while(sym == ' ')
        {
            sym = file.get();
        }

        while(sym != ' ')
        {
            oState = oState + sym;
            sym = file.get();
        }

        while(sym == ' ')
        {
            sym = file.get();
        }

        for (int k = 0; k < ocount; k++)
        {
            if (sym == '1' || sym == '0' || sym == '-')
            {
                output = output + sym;
            }
            sym = file.get();
        }
        if (i < pcount - 1)
        {
            while(sym != '1' && sym != '0' && sym != '-')
            {
                sym = file.get();
            }
        }
        QVector<int> arr = GetArrDC(input);
        if (arr.size() == 0)
        {
            data->table[data->inputs.indexOf(input)][data->states.indexOf(iState)].state
                    = oState;
            data->table[data->inputs.indexOf(input)][data->states.indexOf(iState)].output
                    = output;
        }
        else
        {
            while(NextVector(input, arr))
            {
                data->table[data->inputs.indexOf(input)][data->states.indexOf(iState)].state
                        = oState;
                data->table[data->inputs.indexOf(input)][data->states.indexOf(iState)].output
                        = output;
            }
        }
        input = "";
        output = "";
        iState = "";
        oState = "";
    }
    file.close();
}

QVector<int> GetArrDC(const QString & interval)
{
    QVector<int> arr;
    int size = interval.size();
    for (int i = 0; i < size; i++)
    {
        if (interval[i] == '-')
        {
            arr.push_front(i);
        }
    }
    return arr;
}

bool NextVector(QString & vector, QVector<int> arr)
{
    if(arr.size() == 0)
        return false;
    else
    {
        int size = arr.size();
        if (vector[arr[0]] == '-')
        {
            for(int i = 0; i < size; i++)
            {
                vector.replace(arr[i], 1, "0");
            }
            return true;
        }
        for (int i = 0; i < size; i++)
        {
            if (vector[arr[i]] == '0')
            {
                vector.replace(arr[i], 1, '1');
                for (int j = i - 1; j >= 0; j--)
                {
                    vector.replace(arr[j], 1, "0");
                }
                return true;
            }
        }
        return false;
    }
}

void Show(Data * data)
{
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

void GetR1(QVector<int> & R1, Data * data)
{
    int size = data->states.size();
    for (int i = 0; i < size; i++)
    {
        R1.push_back(1);
    }

    int index = 1;

    for (int i = 1; i < size; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (compareForR1(data, i, j))
            {
                R1[i] = R1[j];
                break;
            }
            else
            {
                if (j == 0)
                {
                    index++;
                    R1[i] = index;
                }
            }
        }
    }
}

bool compareForR1(Data * data, int i, int j)
{
    int size = data->inputs.size();
    for (int k = 0; k < size; k++)
    {
        if (data->table[k][i].output != "" && data->table[k][j].output != "")
        {
            if (data->table[k][i].output != data->table[k][j].output)
                return false;
        }
    }
    return true;
}

QVector<int> GetRi(QVector<int> & Ri, Data * data)
{
    QVector<int> newRi;
    int size = data->states.size();
    for (int i = 0; i < size; i++)
    {
        newRi.push_back(0);
    }
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        if (Ri[i] > index)
            index = Ri[i];
    }
    int newIndex = index;

    bool firstInput = true;
    for (int i = 1; i <= index; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (Ri[j] == i)
            {
                if (firstInput)
                {
                    newRi[j] = i;
                    firstInput = false;
                    continue;
                }
                for (int k = j - 1; k >= 0; k--)
                {
                    if (Ri[k] == i)
                    {
                        if (compareForRi(data, j, k, Ri))
                        {
                            newRi[j] = newRi[k];
                            break;
                        }
                    }
                    if (k == 0)
                    {
                        newIndex++;
                        newRi[j] = newIndex;
                    }
                }
            }
        }
        firstInput = true;
    }
    return newRi;
}

bool compareForRi(Data * data, int i, int j, QVector<int> Ri)
{
    int size = data->inputs.size();
    for (int k = 0; k < size; k++)
    {
        if (data->table[k][i].output != "" && data->table[k][j].output != "")
        {
            QString stateI = data->table[k][i].state;
            QString stateJ = data->table[k][j].state;
            if (Ri[data->states.indexOf(stateI)] != Ri[data->states.indexOf(stateJ)])
                return false;
        }
    }
    return true;
}

void DeleteDC(Data * data, const QString & beginState)
{
    Data * newData = new Data;

    QVector<QString> reachState;
    reachState.push_back(beginState);

    int sizeInput = data->inputs.size();

    int oldSize = 0;
    while(reachState.size() != oldSize)
    {
        oldSize = reachState.size();
        for (int i = 0; i < oldSize; i++)
        {
            int index = data->states.indexOf(reachState[i]);
            for (int j = 0; j < sizeInput; j++)
            {
                if (data->table[j][index].state != "" && !reachState.contains(data->table[j][index].state))
                {
                    reachState.push_back(data->table[j][index].state);
                }
            }
        }
    }

    int size = data->states.size();
    for (int i = 0; i < size; i++)
    {
        if (reachState.contains(data->states[i]))
        {
            newData->states.push_back(data->states[i]);
        }
    }
    newData->table = new Element *[sizeInput];
    int newSize = newData->states.size();
    for (int i = 0; i < sizeInput; i++)
    {
        newData->table[i] = new Element[newSize];
    }
    for (int i = 0; i < sizeInput; i++)
    {
        int k = 0;
        for (int j = 0; j < size; j++)
        {
            if (newData->states.contains(data->states[j]))
            {
                newData->table[i][k] = data->table[i][j];
                k++;
            }
        }
    }
    for (int i = 0; i < sizeInput; i++)
    {
        delete []data->table[i];
    }
    delete []data->table;
    data->states = newData->states;
    data->table = newData->table;
}
