#!/usr/bin/python2.7 -tt
from socket import *
import sys

def get_port_number():
    return int(sys.argv[1])

def recv_msg(s):
    max_buffer = 1024
    message = ""
    
    while True:
        message += s.recv(max_buffer)
        if "\r\n\r\n" in message:
            return message

def send_error_msg(s):
    print "[Doron]: bad msg. sending error msg"
    error_msg = \
    """HTTP/1.1 404 Not Found\r
    Content-type: text/html\r
    Content-length: 113\r
    \r
    <html><head><title>Not Found</title></head><body>\r
    Sorry, the object you requested was not found.\r
    </body></html>\r\n\r\n"""
    s.send(error_msg)

def send_counter_msg(s, counter):
    counter_msg = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n"
    counter_msg += "Content-Length: "+str(len(str(counter)))+"\r\n\r\n"
    counter_msg += str(counter)+"\r\n\r\n"
    print "[Doron]: counter_msg is:\n"+counter_msg

    s.send(counter_msg)

def main():
    port_number = get_port_number()
    address_counter = 0
    print "[Doron]: port_number =", port_number
    s = socket()
    s.connect(('localhost',port_number)) #connect to LB

    while True:
        http_request = recv_msg(s)
        first_line = http_request.split("\r\n")[0]
        print "[Doron]: rcved http_request. first_line =", first_line
        first_line = http_request.split("\r\n")[0]

        if "GET" not in first_line:
            send_error_msg(s)
            continue
        
        address = first_line.split("GET")[1].split()[0]
        print "[Doron]: address =", address

        if address == "/counter":
            print "[Doron]: good message. address_counter =", address_counter
            address_counter += 1
            send_counter_msg(s, address_counter)
        else:
            send_error_msg(s)

main()
