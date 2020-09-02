#!/usr/bin/env python3
# @author Carl Saldanha <cjds92@gmail.com>
# @brief Web server to help move the robot

from http.server import BaseHTTPRequestHandler, HTTPServer 
from os import curdir, sep
import contextlib
import os
import socket
import urllib.parse as urlparse
from urllib.parse import parse_qs

from functools import partialmethod

PORT_NUMBER = 8080
HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
SOCKET_PORT = 65432        # Port to listen on (non-privileged ports are > 1023)



def partialclass(cls, *args, **kwds):
    """
    Simple method to implement a partial around the init of a class
    """

    class NewCls(cls):
        __init__ = partialmethod(cls.__init__, *args, **kwds)

    return NewCls



#This class will handles any incoming request from
#the browser 
class myHandler(BaseHTTPRequestHandler):
        

        def __init__(self, socket_conn, *args, **kwargs):
            self.socket_conn = socket_conn
            super(BaseHTTPRequestHandler, self).__init__(*args, **kwargs)
        
        #Handler for the GET requests
        def do_GET(self):
            parsed_url = urlparse.urlparse(self.path)

            if(self.headers.get('content-length') is not None):
                data = self.rfile.read(self.headers.get('content-length')).decode('utf-8')
            dir_path = os.path.dirname(os.path.normpath(__file__))
            if self.path == "/":
                self.path=os.path.join(dir_path, "index.html")
            elif parsed_url.path == "/keybind":
                print(urlparse.parse_qs(parsed_url.query))
                print(parsed_url.path)
                print('sending data')
                self.socket_conn.sendall(bytearray("W\n", 'utf8'))
            else:
                self.path = os.path.join(dir_path, self.path[1:])
            try:
                #Check the file extension required and
                #set the right mime type
                sendReply = False
                if self.path.endswith(".html"):
                    mimetype='text/html'
                    sendReply = True
                if self.path.endswith(".jpg"):
                    mimetype='image/jpg'
                    sendReply = True
                if self.path.endswith(".gif"):
                    mimetype='image/gif'
                    sendReply = True
                if self.path.endswith(".js"):
                    mimetype='application/javascript'
                    sendReply = True
                if self.path.endswith(".css"):
                    mimetype='text/css'
                    sendReply = True

                if sendReply == True:
                    #Open the static file requested and send it
                    f = open(self.path, 'rb') 
                    self.send_response(200)
                    self.send_header('Content-type',mimetype)
                    self.end_headers()
                    self.wfile.write(f.read())
                    f.close()
                return
            except IOError:
                self.send_error(404,'File Not Found: %s' % self.path)

# Start a Socket server to push the data to C++
if __name__ == "__main__":
    try:
        print("Waiting for socket client to connect")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            print("Socket client connected")
            s.bind((HOST, SOCKET_PORT))
            s.listen()
            conn, addr = s.accept()
            with conn:
                server = HTTPServer(('', PORT_NUMBER), partialclass(myHandler, conn))
                print('Started httpserver on port ' , PORT_NUMBER)
                server.serve_forever()
    except KeyboardInterrupt:
        print('^C received, shutting down the web server')
