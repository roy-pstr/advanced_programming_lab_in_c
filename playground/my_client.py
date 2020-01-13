#!/usr/bin/python2.7 -tt
from socket import *
import sys
import time

def recv_msg(s):
    response = ''
    while True:
        response += s.recv(1024)
        if response.count('\r\n\r\n') == 2:
            return response



s = socket()
port = int(sys.argv[1])

print "connecting to local host on port", port

s.connect(('localhost', port))

print "connected."

print "sending good message:"
s.send("GET /counter HTTP/1\r\n")
s.send("second line\r\n")
s.send("last line \r\n\r\n")
time.sleep(2)

print "recieving message..."

response = recv_msg(s)
print "recieved response:\n"+ response

print "reconnecting..."
s = socket()
s.connect(('localhost', port))
print "connected."


print "sending bad message:"
s.send("GET MAHALA HTTP/1\r\n")
s.send("second line\r\n")
s.send("third line\r\n")
s.send("last line \r\n\r\n")
time.sleep(2)

response = recv_msg(s)
print "recieved msg:\n" + response

time.sleep(2)
print "Done"
