from http.server import HTTPServer, BaseHTTPRequestHandler

class Server(BaseHTTPRequestHandler):
    def do_GET(self): #do_GET is a built-in method and can't be renamed
        if self.path == "/":
            self.send_response(200)
            self.end_headers()   
            #A bytes-like object is required, not 'str'
            self.wfile.write(bytes("Hello World", "utf-8")) 
        elif self.path == "/test":
            self.send_response(200)
            self.end_headers()   
            #A bytes-like object is required, not 'str'
            self.wfile.write(bytes("test route", "utf-8"))     

http = HTTPServer(("localhost", 8000), Server)
http.serve_forever()