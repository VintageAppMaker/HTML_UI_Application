/*
    ����  : HTML PAGE ���� �Լ�
    ����  : �ܺθ�⿡�� PAGE �ۼ��� UTIL API
    �ۼ���: �ڼ���
    �ۼ���: 2005.04.20

    ����  : 1) HTML ���¿��� API ������ ���� �Լ��� �����Ѵ�.
            2) �ǵ��� ��ü������ Layer ���·� �����Ѵ�.
            
           
*/


#ifndef __PSW_SNAKE_HTML_PAGE__
#define __PSW_SNAKE_HTML_PAGE__

extern  "C" 
{
    
    void   Write_MessageToPage (int nPage, char* msg);
    void   Write_ListToPage    (char* msg);
    void   Erase_MessageOnPage (int nPage);
    void   Erase_ListOnPage    ();
    
    char*  Read_ValueItem      (int nPage, char* Item); 
    int    Write_ValueItem     (int nPage, char* Item, char* msg);       
    
    int    AttachHTMLTextToBoard (int nPage);
    int    AddHTMLText           (char* msg);
    int    ClearHTMLText();

	int    ExcuteJScript(char* fnName, char* pParam);
      
}

#endif
