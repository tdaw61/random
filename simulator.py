import time, os


for i in range(5):
    os.system("python TrafficSimulator.py zim.cs.ucsb.edu 31337 " + str(50*(i+12)) + " 2000 20")
    time.sleep(4)
