# -*- coding: utf-8 -*-
"""
Created on Sat Sep  3 19:51:54 2022

@author: Johan Lee
"""

import pyautogui
import webbrowser as web
import serial
import time


class Serial_Port():
   
    
    def __init__(self, puerto, baudrate, comunication):
        self.puerto = puerto
        self.baudrate = baudrate
        self.comunication = comunication
        
        
    def open_Serial_Port(self):
        self.serial__Port = serial.Serial(self.puerto, self.baudrate, timeout = 1)
        time.sleep(2)
        self.comunication = True
        

    def readline(self):
        data = self.serial__Port.readline()
        return data
    
    
    def write(self, message):
        self.serial__Port.write(message)
    

    def close_Serial_Port(self):
        self.serial__Port.close()

    def write_Phrase(self, phrase):
        for word in phrase:
            word = word.encode('ascii')
            time.sleep(.75)
            serial1.write(word)


def open_Whatsapp(url):
    web.open(url)
        

def write_Message_Whats (message):
    pyautogui.typewrite(message)
    pyautogui.press("enter")
    time.sleep(2)
        



        
com = '6'
baudrate = 1200


com = (input("Write the port number to use"))
baudrate = int(input("Write the baudrate to use"))



serial1 = Serial_Port('COM' + com, baudrate, False)
serial1.open_Serial_Port()



if serial1.comunication == True:
    serial1.write_Phrase('M')
    time.sleep(1)
    #serial1.write_Phrase('Q')
    #time.sleep(1)

 
open_Whatsapp("https://web.whatsapp.com/accept?code=EPCW3RmR9Cr0gQS21F0eZy")
time.sleep(15)



while (serial1.comunication == True):
    message_Atmel = serial1.readline()
    message_Atmel = message_Atmel.decode('utf-8')
    message_Atmel = message_Atmel.strip()
    print (message_Atmel)
    if ((message_Atmel == ' \n') or (message_Atmel == '\r') or (message_Atmel == '')):
        pass
    else: 
        write_Message_Whats(message_Atmel)




