/***********************************************************
       작성일: 2000/09/01
       작성자: 박성완
       목적:   Query 문자열 처리
       기능:   귀찮은 문자열 처리
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


