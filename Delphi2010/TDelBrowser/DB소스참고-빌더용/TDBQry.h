/***********************************************************
       작성일: 2000/10/23
       작성자: 박성완
       목적:   Query String 처리를 위한 클래스 
       기능:   지저분한 문자열 처리
***********************************************************/
#ifndef PSW_SNAKE_qryDB
#define PSW_SNAKE_qryDB
#include <Classes.hpp>
#include <Controls.hpp>
#include <comobj.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TDBQry : public TStringList
{
public:
    TDBQry& operator <<(AnsiString qry);
    TDBQry& operator <<(char* qry);
    TDBQry& operator <<(int value);
    
    // 라인으로 붙이기
    TDBQry& operator <(AnsiString qry);
    TDBQry& operator <(char* qry);
    TDBQry& operator <(int value);

    TDBQry();
protected:
private:
};
//---------------------------------------------------------------------------
#endif
