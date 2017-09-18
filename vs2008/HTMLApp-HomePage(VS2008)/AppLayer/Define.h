#ifndef __DEFINE_H__
#define __DEFINE_H__

#define COMPILE_MODE_MTEST      1       // 개발용 페이지
#define COMPILE_MODE_LOADER     2       // 상용 페이지

// COMPILE MODE 설정
#define COMPILE_MODE	COMPILE_MODE_MTEST

#if (COMPILE_MODE==COMPILE_MODE_LOADER)

	#define PLIST_FTP_IP	 "211.174.177.156"
    #define PLIST_FTP_PORT   21
    #define PLIST_FTP_ID	 "Loaderserialdll"
    #define PLIST_FTP_PW	 "Loaderserialdll"

   	#define LIB_FTP_IP		 "211.174.177.156"
    #define LIB_FTP_PORT 	 21
    #define LIB_FTP_ID       "Loaderdmdll"
    #define LIB_FTP_PW       "Loaderdmdll"

    #define CONTENT_FTP_IP	 m_sSrvIP.c_str()   // pList에서 가져온 정보를 이용한다.
    #define CONTENT_FTP_PORT 21
    #define CONTENT_FTP_ID   "mbinrom"
    #define CONTENT_FTP_PW   "romdirmbin"

    #define WEB_LAST_PATH	 "LOADER"
    
    #define AUTH_SKIP_IP	 "0.0.0.0"

#else

	#define PLIST_FTP_IP	 "211.174.177.143"
    #define PLIST_FTP_PORT   21
    #define PLIST_FTP_ID	 "Loaderserialdll"
    #define PLIST_FTP_PW	 "Loaderserialdll"

   	#define LIB_FTP_IP		 "211.174.177.143"
    #define LIB_FTP_PORT 	 21
    #define LIB_FTP_ID       "Loaderdmdll"
    #define LIB_FTP_PW       "Loaderdmdll"

    #define CONTENT_FTP_IP	 m_sSrvIP.c_str()   // pList에서 가져온 정보를 이용한다.
    #define CONTENT_FTP_PORT 21
    #define CONTENT_FTP_ID   "mbinrom"
    #define CONTENT_FTP_PW   "romdirmbin"

    #define WEB_LAST_PATH	 "MTEST"

	#define AUTH_SKIP_IP	 "211.174.177.143"
	
#endif


#endif  // END : #ifndef __DEFINE_H__
