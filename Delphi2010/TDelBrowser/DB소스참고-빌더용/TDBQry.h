/***********************************************************
       �ۼ���: 2000/10/23
       �ۼ���: �ڼ���
       ����:   Query String ó���� ���� Ŭ���� 
       ���:   �������� ���ڿ� ó��
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
    
    // �������� ���̱�
    TDBQry& operator <(AnsiString qry);
    TDBQry& operator <(char* qry);
    TDBQry& operator <(int value);

    TDBQry();
protected:
private:
};
//---------------------------------------------------------------------------
#endif
