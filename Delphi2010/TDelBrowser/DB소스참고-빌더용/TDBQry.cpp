/***********************************************************
       �ۼ���: 2000/09/01
       �ۼ���: �ڼ���
       ����:   Query ���ڿ� ó��
       ���:   ������ ���ڿ� ó��
***********************************************************/

#include "TDBQry.h"
//---------------------------------------------------------------------------
TDBQry :: TDBQry()
{
}

//---------------------------------------------------------------------------
TDBQry& TDBQry :: operator <<(String qry)
{
    String x = Strings[Count - 1];
    Strings[Count - 1] = x + qry;
    return *this;
}

//---------------------------------------------------------------------------
TDBQry& TDBQry :: operator <<(char* qry)
{
    Add(qry);
    return *this;
}

//---------------------------------------------------------------------------
TDBQry& TDBQry :: operator <<(int value)
{
    String x = Strings[Count - 1];
    Strings[Count - 1] = x + IntToStr(value);
    return *this;
}

//---------------------------------------------------------------------------
TDBQry& TDBQry :: operator <(String qry)
{
    String x = Strings[Count - 1];
    Strings[Count - 1] = x + qry;
    return *this;
}

//---------------------------------------------------------------------------
TDBQry& TDBQry :: operator <(char* qry)
{
    String x = Strings[Count - 1];
    Strings[Count - 1] = x + qry;
    return *this;
}

//---------------------------------------------------------------------------
TDBQry& TDBQry :: operator <(int value)
{
    String x = Strings[Count - 1];
    Strings[Count - 1] = x + IntToStr(value);
    return *this;
}


