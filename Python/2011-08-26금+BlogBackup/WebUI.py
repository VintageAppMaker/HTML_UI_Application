# -*- coding: cp949 -*-
import  wx.lib.iewin as  iewin
import wx 
import os
import time
from PageApp import *

class WebUI(wx.Frame): 
    def __init__(self, parent, id, title, 
        pos = wx.DefaultPosition, size = wx.DefaultSize, 
        style = wx.DEFAULT_FRAME_STYLE ): 
        wx.Frame.__init__(self, parent, id, title, pos, size, style) 
       
        pnlMain = wx.Panel (self, -1, style= 0 )
        sizer = wx.BoxSizer (wx.VERTICAL) 
       
        self.ie = iewin.IEHtmlWindow(pnlMain, -1, style = wx.EXPAND) 
        sizer.Add (self.ie, 1, wx.GROW|wx.ALIGN_CENTER_VERTICAL|wx.ALL, 0 ) 
        pnlMain.SetSizer (sizer); pnlMain.SetAutoLayout(1); pnlMain.Layout(); 
        
        # ���� ������� �� Ŀ�ǵ� ���� ���ڿ�
        self.dir = os.getcwd()
        self.cmdString = 'app:://'
        self.registedpage = False

        #Event�� ���δ�.
        self.ie.AddEventSink(self)
        
        self.ie.Navigate ("file://%s\\main.html" % self.dir) 

    # URL �̵���  
    def BeforeNavigate2(self, this, pDisp, URL, Flags, TargetFrameName,
                        PostData, Headers, Cancel):

        self.WriteURL(URL[0].encode('euc-kr'))
        
        # Ŀ�ǵ� ���ڿ� �м�
        if URL[0].encode('euc-kr').find(self.cmdString) == 0:
            self.CurPage.OnCMDRequest( self, URL[0].encode('euc-kr').replace(self.cmdString, '').split('|') )
            Cancel[0] =True
                
        # ��ϵ� HTML ó�� 
        for i in REGISTED_HTML_PAGE:
            str = self.MakeCheckURL( i.GetPageName() )
            if URL[0].encode('euc-kr') == str:
                self.registedpage = True
                self.CurPage = i 
    
    def NewWindow3(self, this, pDisp, Cancel, Flags, urlContext, URL):
        self.WriteURL( 'NewWindow3: %s\n' % URL )

   
    # ������ �� �о���. 
    def DocumentComplete(self, this, pDisp, URL):
        self.current = URL[0]
        if self.registedpage is True:
            self.CurPage.OnStart(self, URL[0])
        
        self.registedpage = False

    # ���� ���ڿ��� �����.
    def MakeCheckURL(self, str):
        return ("%s\\%s" % ( self.dir, str ) )

    # Element�� ���� �����´�.
    def GetElement(self, name):
        return self.ie.document.getElementById(name).innerHTML 
    
    # Element�� ���� �����Ѵ�.
    def SetElement(self, name, str):
        self.ie.document.getElementById(name).innerHTML = str 

    # URL Log�� �����Ѵ�.
    def WriteURL(self, str):
        f = open ("urllog.txt", "a")
        f.write(str + "\r\n")
        f.close()
           

class MyApp(wx.App):    
    def OnInit(self): 
        #wx.InitAllImageHandlers() 
        frame = WebUI( None, -1, "HTML Application", wx.DefaultPosition, [693,590] ) 
        frame.Show(True)       
        return True 

if __name__ == "__main__":
    app = MyApp(False) 
    app.MainLoop() 

