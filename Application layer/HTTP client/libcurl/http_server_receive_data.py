from http.server import HTTPServer, BaseHTTPRequestHandler

class Server(BaseHTTPRequestHandler):
  def do_POST(self): #do_GET is a built-in method and can't be renamed
    if self.path == "/":
      self.send_response(200)
      content_length = int(self.headers['Content-Length']) # <--- Gets the size of data
      received_data = self.rfile.read(content_length)
      print("POST request,\nPath: %s,\nHeaders:%s,\nData: %s" % (str(self.path), str(self.headers), received_data.decode('utf-8')))
      self.end_headers()

# http = HTTPServer(("localhost", 8000), Server)
http = HTTPServer(("localhost", 8000), Server)
http.serve_forever()