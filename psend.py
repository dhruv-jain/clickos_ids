import sys
import struct
from scapy.all import *
data = "Yang"
packet = IP(src='192.168.1.96',dst='10.0.2.20')/TCP(dport=80)/data
send(packet, inter = 1, count =3) 
