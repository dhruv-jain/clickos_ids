import sys
import struct
from scapy.all import *
data = "Yang-test1"
packet = IP(src='192.168.1.95',dst='10.0.2.20')/TCP(dport=80)/data
send(packet, inter = 1, count = 1) 
data = "Yilang-test2"
packet = IP(src='192.168.1.95',dst='10.0.2.20')/TCP(dport=80)/data
send(packet, inter = 1, count = 1) 
data = "Dhruv-test3"
packet = IP(src='192.168.1.95',dst='10.0.2.20')/TCP(dport=80)/data
send(packet, inter = 1, count = 1) 
data = "Anukul-test4"
packet = IP(src='192.168.1.95',dst='10.0.2.20')/TCP(dport=80)/data
send(packet, inter = 1, count = 1) 
