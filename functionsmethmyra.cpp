#include "functionsmethmyra.h"

void parsePrivate(Data * data, const QString nameFile);

void parse(Data * data, const QString & nameFile)
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
    if (file.eof())
    {
        throw e;
    }
    sym = file.get();

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
    sym = file.get();

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
