# -*- coding: cp949 -*-
import os
import time
from urllib2 import urlopen
import re
from HTMLCap import *
import time

# 선조 클래스 
class PageApp: 
    def __init__(self): 
        self.pagename = ""

    def OnStart (self, page, url): 
        pass

    def OnCMDRequest(self, page, cmd):
        pass
    
    def GetPageName(self):
        return self.pagename
      
# Main Page
class MainPage(PageApp):
   
    def __init__(self):
        # 선조 클래스 호출 
        PageApp.__init__(self)
        self.pagename = "main.html" 

    def OnStart(self, page, url):
        self.hcap = HTMLCap()
  

    # Image 캡쳐하기  
    def GetImagesFromURL(self, page, user, start, last):
        
        page.SetElement('BOARD_1',  "") 
        page.SetElement('BOARD_2',  "" ) 

        str    = "<table><tr><td width = 30></td><td>"
        str    = str + "<table cellspacing = 0 style = 'font-size: 8pt; font-familly:굴림체;'width = 400><tr align = 'center'><td style =  'width = 80; background-color: #DFFF9A'>이미지(클릭!)</td><td style = 'background-color: #9FFF9A'>URL</td></tr><tr>"
        
        count = int(last) - int(start) + 1
        for i in range( count ):
            # 안정성을 위해서 Sleep을 2초  
            time.sleep(2)
            indx = i + int(start) 
            page.SetElement('BOARD_2',  "<br>&&nbsp&nbsp&nbsp&nbsp&nbsp%d Page를 작업 중입니다" % indx ) 
            
            sURL   =  "http://blog.naver.com/PostList.nhn?blogId=%s&currentPage=%d&categoryNo=0" %  (user, indx) 
            sFname = "%s_%d.jpeg" % (user,  indx )
            self.hcap.DoCapture(sURL, sFname)
            
            if os.path.isfile(sFname):
                str = str + "<tr style = 'background-color: #FFFFFF'><td style = 'background-color: #FFFFFF'><img src ='%s' alt = \"원본보기\" onclick = \"window.open('%s');\" border = 0></td><td>%s</td></tr><tr><td colspan=2 background=\"image/list_back.gif\"></td></tr>" %  ( "image/click.png", sFname, sFname) 
        
            else:
                str = str + "<tr style = 'background-color: #FFFFFF'><td style = 'background-color: #00FFFF'><img src ='%s' alt = \"원본보기\" onclick = \"alert('%s');\" border = 0></td><td style = 'background-color: #00FFFF'>없음(%s)</td></tr><tr><td colspan=2 background=\"image/list_back.gif\"></td></tr>" %  ( "image/burst.gif", "Capture 실패", sFname) 
        
        str = str + "</table></td></tr></table>"

        page.SetElement('BOARD_1',  str) 
        self.hcap.Clear() 
        

    def OnCMDRequest(self, page, cmd):
        if cmd[0] == "Search":
            # 쓰레드 처리해도 소용없어서 그냥 사용함
            self.GetImagesFromURL(page, cmd[1], cmd[2], cmd[3]) 
    
 
# page 등록하기 
REGISTED_HTML_PAGE = [MainPage()]
