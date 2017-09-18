from distutils.core import setup
import py2exe

setup(windows=['WebUI.py'],
      data_files=["HTMLCap.dll", "main.html"]
) 


