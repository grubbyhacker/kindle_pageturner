#!/usr/bin/python
import threading
import socket
import socketserver
from subprocess import call

FORWARD_COMMAND = "/mnt/us/extensions/pageturn/bin/pageforward.sh"
BACKWARD_COMMAND = "/mnt/us/extensions/pageturn/bin/pageback.sh"

class ThreadedUDPRequestHandler(
        socketserver.BaseRequestHandler):

    def handle(self):
        data = self.request[0].strip().decode("utf-8")
        port = self.client_address[1]
        socket = self.request[1]
        client_address = (self.client_address[0])
        cur_thread = threading.current_thread()
        print("thread %s" %cur_thread.name)
        print("received call from client address :%s" %client_address)
        print("received data from port [%s]: %s" %(port, data))

        if data.upper() == 'F':
            print('Page Forward')
            call(FORWARD_COMMAND)
        elif data.upper() == "B":
            print('Page Backward')
            call(BACKWARD_COMMAND)

        socket.sendto(data.upper(), self.client_address)

class ThreadedUDPServer(
socketserver.ThreadingMixIn,
socketserver.UDPServer):
    pass

if __name__ == "__main__":

    # Unfortunately if you use 127.0.0.1 then the service will
    # not respond to non local connections. The following hack
    # retrieves this reliably.
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(("8.8.8.8", 80)) # Google DNS
    host = s.getsockname()[0]

    print("Using ip address: %s" %host)

    server = ThreadedUDPServer((host, 8000),
                ThreadedUDPRequestHandler)
    ip, port = server.server_address
    server.serve_forever()
    server_thread = threading.Thread(target=server.serve_forever)
    server_thread.daemon = True
    server_thread.start()
    server.shutdown()
