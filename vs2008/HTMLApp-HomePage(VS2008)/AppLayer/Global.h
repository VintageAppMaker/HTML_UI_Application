
#ifndef _GLOBAL_H_KJS_
#define _GLOBAL_H_KJS_

#include "Define.h"

/**********************************************
        ==>> �Լ� ������ ���� <<==
***********************************************/

typedef void  (*RXModelCallBack)(char*, char*);	             // �𵨸�...
typedef void  (*RXMsgCallBack)(char*, int, int);     // ��� ���� (�޽���, Max, Min);
typedef void  (*RXAuthCallBack)();              //���� ������ ���� ��Ŷ

typedef enum {
	    ADS_BILLOK = 0, // 0 : �������� OK
	    ADS_INFOOK = 2, // 2 : ������ ���� ���� ����
		ADS_DNOK,       // 3 : ADSLoader download �Ϸ� ����
	    ADS_DNREQ,      // 4 : ADSLoader download ��û
		ADS_REFUND,     // 5 : ȯ��ó��..
	    ADS_SVROK,      // 6 : ADS_DNOK�� ���� ���� (ACK)
		ADS_SVRNO,      // 7 : ADS_DNOK�� ���� ���� (NACK)
	//  ADS_SUPER_YES,  // 7 : ���������� �ܸ���ȣ ���� �߰�
		ADS_INFODEL,     // 8 : �������� ����
		ADS_NOCNT,       // 9 :  ����������
        ADS_EXIT = 100,  // 100 : �δ� ����
        ADS_DESTROY,
} STATE;

typedef enum{
	DRV_TYPE_1 = 1,		// Serial
	DRV_TYPE_2,		// MCCI
	DRV_TYPE_3,		// MCCI + HSP
	DRV_TYPE_4,		// HSP
	DRV_TYPE_5,		// LG
	DRV_TYPE_6,		// SKY
	DRV_TYPE_7,		// CURITEL
	DRV_TYPE_8,		// KTF
}DRIVERTYPE;
#pragma pack(push, 1)

/**********************************************
			==>> ������ ���� <<==
***********************************************/
typedef struct tagSIODS{
    char    content_type;    // ����Ʈ Ÿ��
    char	game_type;       // ���� Ÿ��
    WORD    cp_id;           // CP ID
    WORD    game_id;         // GAME ID
    WORD    game_ver;        // GAME Version
    WORD    width;           // game width  128
    WORD    height;          // game height 96
    WORD    dls_port;        // dls port
    char    dls_url[64];     // dls Url
    WORD    svs_port;        // svs port
    char    svs_url[64];     // svs Url
    char    gamename[16];    // �����̸�
    char    returnurl[64];   // ����URL
    DWORD   filesize;        // ����Ʈ���ϻ�����
    char    nColor;          // �÷���(��Ʈ��) 2001.11.22 �߰�
} SIODS;


/****************************************************
        ==>> ������ ������ ���� <<==
****************************************************/
typedef struct tagCNTHEADER {
    BYTE    BCC;
    BYTE    Version;
    DWORD   P_NUMBER;
    WORD    CID;
    WORD    GID;
    WORD    VER;
} CNTHEADER;


typedef struct tagOWNERINFO {
        DWORD  PhoneNumber;        // �ܸ����ȣ(���ڰ����� �ѱ�)
        BYTE   MasterID[3];        // "ADS"
        BYTE   Limited;            // ������ �ڵ�
        DWORD  DownloadTime;       // �ٿ�ε� �ð�
        BYTE   UserID[16];         // Unitel User ID
} OWNERINFO;

typedef struct tagADSHEADER{
    OWNERINFO   oi;
    char        reserved[8];     //�� �̰� �־�� �ϴ��� �𸣰ڴ�.. �Ѥ�;
    SIODS       siods;
} MBINHEADER;

typedef struct tagMIDDLEHEADER {
    CNTHEADER   cHdr;
    DWORD       nIconSize;
    DWORD       nFileSize;
} MIDDLEHEADER;


/**********************************************
			==>> �ܸ��� ���� <<==
***********************************************/
typedef struct tagSIOINFO{
	    WORD	Ver;				// SIO version
	    WORD	Width;				// Width
        WORD	Height;				// Height
        WORD	Color;				// Color
        long    Memsize;			// ���� �޸� ������
        long    Rom;				// Rom Address
        long    Ram;				// Ram Address
        long    MWB;				// MWB Size
        long    WorkMem;			// Work �޸�
        BYTE    Sound;				// Sound Type
        WORD    CanDown;			// �ٿ���� ī��Ʈ ��
        WORD    wExtensionMode;		// Ȯ������ ���� ���
        WORD    wFreePicMateCnt;	// ���尡�� �̹��� ����
        WORD    wFreeSndCnt;		// ���尡�� ��ε� ����
        WORD    wFreeNRBCnt;		// ���尡�� �뷡�� ����
        WORD    wFreeMyIconCnt;		// ������ ������ ���尡�ɰ���
		DWORD	GMTTime;			// �ð�
} SIOIF;


/**********************************************
			==>> ��������(FACK) <<==
***********************************************/

typedef struct tagMIMEINFO{
	    BYTE    ContentType;
        BYTE    SVSIP[64];
        WORD    SVSPort;
        BYTE    ContentName[30];
        BYTE    ReturnUrl[64];
        WORD    RunLcdWidth;
        WORD    RunLcdHeight;
        BYTE    ContentColorBit;
        BYTE    ContentSoundType;
        WORD    NewContentVersion;
}MIMEINFO;


/**********************************************
			==>> ������Ŷ(FACK) <<==
***********************************************/
typedef struct tagAUTHPACKET {
    DWORD  FileSize;           // 2002.08.13 ��Ŷ�������
    BYTE   Pack_state;         // Packet ����(�ٿ�ε强��: 0, �ٿ�ε����: 1, ��������: 2)
    DWORD  PhoneNumber;        // �ܸ����ȣ(���ڰ����� �ѱ�)
    WORD   CP_ID;              // CP ���̵�
    WORD   GameID;             // GAME ���̵�
    DWORD  SEQ_ID;             // ������ ó���� UNIQ ��
    WORD   ver;                // ������ ����
    BYTE   Judgement_Day[12];  // ������ ��ȿ�Ⱓ(�б���) 
    BYTE   Reserved[3];        // Reserved
//	MIMEINFO minfo;
//    char   iconDta[2048];
} AUTHPACKET;
#pragma pack(pop)

typedef int  (__stdcall *CNT_DECODING)(CNTHEADER*, BYTE*, DWORD);
typedef int  (__stdcall *CNT_EXTRACT) (CNTHEADER*, BYTE*, char*);
typedef int  (__stdcall *CNT_ENCODING)(CNTHEADER*, BYTE*, BYTE*, DWORD);
typedef int  (__stdcall *CNT_COMPRESS)(CNTHEADER*, char*, BYTE*, DWORD);
//typedef int  (__stdcall* CNT_CHECKADS)(char*, MBINHEADER&);
typedef void (__stdcall *CNT_DEBUG)(void);
#endif
