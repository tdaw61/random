import socket

UDP_IP = "zim.cs.ucsb.edu"
A_PORT = 31337
MESSAGE ="reset"
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(MESSAGE,(UDP_IP, A_PORT)
