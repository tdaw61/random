import socket, sys, time
from socket import socket, AF_INET, SOCK_DGRAM

#command line argument stuff

servAddr = sys.argv[1]
servPort = sys.argv[2]
pps =      sys.argv[3]
payload =  sys.argv[4]
sec =      sys.argv[5]


name = "tdaw"
data = "tdaw."
count = 0
#account for name and .
while(count < int(payload) - 5):
    data = data + "x"
    count = count + 1
empty = ""
#print data
sock = socket(AF_INET,SOCK_DGRAM)
start_time = time.time()
#print start_time
curr_time = time.time()
packets = 0
#print start_time - curr_time
while((curr_time - start_time) < float(sec)):
    sock.sendto(data,(servAddr, int(servPort)))
    time.sleep(1/float(pps))
    curr_time = time.time()
    #print curr_time
    #print data
    #diff = curr_time - start_time
    #print "difference " + str(diff)
    #print "sec" + sec
    packets = packets + 1
print str(packets)
    #print str(len(data))



    
