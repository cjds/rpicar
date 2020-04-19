#!/usr/bin/env python

from http.server import BaseHTTPRequestHandler, HTTPServer 
from os import curdir, sep
import os
import socketserver
import mmap

PORT_NUMBER = 8080

#This class will handles any incoming request from
#the browser 
class myHandler(BaseHTTPRequestHandler):
        
        #Handler for the GET requests
        def do_GET(self):
                dir_path = os.path.dirname(os.path.normpath(__file__))
                if self.path=="/":
                    self.path=os.path.join(dir_path, "index.html")
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

if __name__ == "__main__":
    try:
        #Create a web server and define the handler to manage the
        #incoming request
        server = HTTPServer(('', PORT_NUMBER), myHandler)
        print('Started httpserver on port ' , PORT_NUMBER)
        server.serve_forever()
    except KeyboardInterrupt:
        print('^C received, shutting down the web server')
        server.socket.close()
