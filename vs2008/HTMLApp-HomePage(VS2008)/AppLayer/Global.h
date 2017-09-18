
#ifndef _GLOBAL_H_KJS_
#define _GLOBAL_H_KJS_

#include "Define.h"

/**********************************************
        ==>> 함수 포인터 정의 <<==
***********************************************/

typedef void  (*RXModelCallBack)(char*, char*);	             // 모델명...
typedef void  (*RXMsgCallBack)(char*, int, int);     // 통신 상태 (메시지, Max, Min);
typedef void  (*RXAuthCallBack)();              //인증 날리기 위한 패킷

typedef enum {
	    ADS_BILLOK = 0, // 0 : 빌링정보 OK
	    ADS_INFOOK = 2, // 2 : 웹에서 인증 파일 생성
		ADS_DNOK,       // 3 : ADSLoader download 완료 성공
	    ADS_DNREQ,      // 4 : ADSLoader download 요청
		ADS_REFUND,     // 5 : 환불처리..
	    ADS_SVROK,      // 6 : ADS_DNOK에 대한 응답 (ACK)
		ADS_SVRNO,      // 7 : ADS_DNOK에 대한 응답 (NACK)
	//  ADS_SUPER_YES,  // 7 : 인증서버에 단말번호 사면및 추가
		ADS_INFODEL,     // 8 : 인증파일 삭제
		ADS_NOCNT,       // 9 :  컨텐츠없음
        ADS_EXIT = 100,  // 100 : 로더 종료
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
			==>> 컨텐츠 정보 <<==
***********************************************/
typedef struct tagSIODS{
    char    content_type;    // 컨텐트 타입
    char	game_type;       // 게임 타입
    WORD    cp_id;           // CP ID
    WORD    game_id;         // GAME ID
    WORD    game_ver;        // GAME Version
    WORD    width;           // game width  128
    WORD    height;          // game height 96
    WORD    dls_port;        // dls port
    char    dls_url[64];     // dls Url
    WORD    svs_port;        // svs port
    char    svs_url[64];     // svs Url
    char    gamename[16];    // 게임이름
    char    returnurl[64];   // 리턴URL
    DWORD   filesize;        // 컨텐트파일사이즈
    char    nColor;          // 컬러수(비트수) 2001.11.22 추가
} SIODS;


/****************************************************
        ==>> 컨텐츠 권한자 정보 <<==
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
        DWORD  PhoneNumber;        // 단말기번호(숫자값으로 넘김)
        BYTE   MasterID[3];        // "ADS"
        BYTE   Limited;            // 제한자 코드
        DWORD  DownloadTime;       // 다운로드 시간
        BYTE   UserID[16];         // Unitel User ID
} OWNERINFO;

typedef struct tagADSHEADER{
    OWNERINFO   oi;
    char        reserved[8];     //왜 이게 있어야 하는지 모르겠다.. ㅡㅡ;
    SIODS       siods;
} MBINHEADER;

typedef struct tagMIDDLEHEADER {
    CNTHEADER   cHdr;
    DWORD       nIconSize;
    DWORD       nFileSize;
} MIDDLEHEADER;


/**********************************************
			==>> 단말기 정보 <<==
***********************************************/
typedef struct tagSIOINFO{
	    WORD	Ver;				// SIO version
	    WORD	Width;				// Width
        WORD	Height;				// Height
        WORD	Color;				// Color
        long    Memsize;			// 가능 메모리 사이즈
        long    Rom;				// Rom Address
        long    Ram;				// Ram Address
        long    MWB;				// MWB Size
        long    WorkMem;			// Work 메모리
        BYTE    Sound;				// Sound Type
        WORD    CanDown;			// 다운가능한 카운트 수
        WORD    wExtensionMode;		// 확장기능을 위한 모드
        WORD    wFreePicMateCnt;	// 저장가능 이미지 개수
        WORD    wFreeSndCnt;		// 저장가능 멜로디 개수
        WORD    wFreeNRBCnt;		// 저장가능 노래방 개수
        WORD    wFreeMyIconCnt;		// 나만의 아이콘 저장가능개수
		DWORD	GMTTime;			// 시간
} SIOIF;


/**********************************************
			==>> 마임정보(FACK) <<==
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
			==>> 인증패킷(FACK) <<==
***********************************************/
typedef struct tagAUTHPACKET {
    DWORD  FileSize;           // 2002.08.13 패킷내용수정
    BYTE   Pack_state;         // Packet 종류(다운로드성공: 0, 다운로드실패: 1, 정보파일: 2)
    DWORD  PhoneNumber;        // 단말기번호(숫자값으로 넘김)
    WORD   CP_ID;              // CP 아이디
    WORD   GameID;             // GAME 아이디
    DWORD  SEQ_ID;             // 유니텔 처리용 UNIQ 값
    WORD   ver;                // 컨텐츠 버전
    BYTE   Judgement_Day[12];  // 파일의 유효기간(분까지) 
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
