# -*- coding:utf-8 -*-

import sys
import os
basepath = os.path.dirname(__file__)
sys.path.append(basepath + "\\modules\\")
print("module search path added;" + basepath + "\\modules\\")

import configparser as cp
from serial import Serial as sl
import conf


def init():
    if not os.path.exists(basepath + "\\main.ini"):
        cfg = open(basepath + "\\main.ini", 'w')
        cfg.write("""#This is main configuration file.
[common]
#using Comport
port = com3
baudrate = 9600

[level]
stopbits = 1
bytesize =8
""")
    return conf.getConfigContents(common = ["port", "baudrate"],
                           level = ["stopbits", "bytesize"])
    

def openPort(cf):
    return sl(
  port=cf["common"]["port"],
  baudrate=int(cf["common"]["baudrate"], 10),
  bytesize=int(cf["level"]["bytesize"], 10),
  parity='N',
  stopbits=int(cf["level"]["stopbits"], 10),
  timeout=None,
  xonxoff=0,
  rtscts=0,
  writeTimeout=None,
  dsrdtr=None)

def main():
    cf = init()
    com = openPort(cf)

if __name__ == '__main__':
    main()
    
