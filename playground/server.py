#!/usr/bin/python2.7/ -tt
from socket import *
import sys

#def get_port_number(file_path):
#    with open(file_path,'r') as f:
#        return int(f.read().strip())

def get_port_number(file_path):
    return int(sys.argv[1])


def recv_msg(s):
    max_buffer = 1024
    message = ''
    
    while True:
        message += s.recv(max_buffer)
        if message.endswith('\r\n\r\n'):
            return message


def main():
    address_counter = 0
    port_number = get_port_number("server_port")
    print "[Doron]: port_number =", port_number
    s = socket()
    s.connect(('localhost',port_number)) #connect to LB


    while True:
        msg_from_LB = recv_msg(s)
        print "[Doron]: rcved msg:", msg_from_LB
        address_counter += 1 #update counter / error occured
        
        #send_msg()


    print"file content:",port_number

main()

