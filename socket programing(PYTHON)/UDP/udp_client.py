# The client program sets up its socket differently from the way a server does. Instead of binding to a port and listening, it uses connect() to attach #the socket directly to the remote address.

import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Connect the socket to the port where the server is listening
server_address = ('localhost', 10000)
# print(sys.stderr, 'connecting to %s port %s' % server_address)
# sock.connect(server_address)

# After the connection is established, data can be sent through the socket with sendall() and received with recv(), just as in the server.

try:

    # Send data
    message = 'sun kaisa h'.encode()
    print('sending ->%s' % message.decode())
    sock.sendto(message,server_address)

    # Receive response
    print('waiting to receive...')
    data, server = sock.recvfrom(1024)
    print('%s' % data.decode())

finally:
    print('\nclosing socket\n')
    sock.close()
    print("chat closed")

# When the entire message is sent and a copy received, the socket is closed to free up the port.
