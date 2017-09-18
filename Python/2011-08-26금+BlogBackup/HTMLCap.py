# -*- coding: cp949 -*-

#!/usr/bin/env python
from ctypes import *
import time
from ftplib import FTP
import time
import datetime

import win32com.client
import os


class HTMLCap():

    def __init__(self):
        # 만들어지 DLL의 호출관행이 CDLL이다. 
        self.pydll = cdll.LoadLibrary("HtmlCap.dll")

    # HTMLCap Test code
    def DoCapture(self, sURL, sFname):
        URL   = c_wchar_p( sURL )
        Fname = c_wchar_p( sFname)
    
        self.pydll.SavePage( URL, Fname )
        
    def Clear(self):
        self.pydll.Clear()
   

