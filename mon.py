import os
import httplib
import json
import threading
import time
import subprocess

class FlowMonitor(object):
    lastByteCount = 0
    def __init__(self, server):
       self.server = server;
    def get(self, path):
        ret = self.rest_call({},'GET',path)

        global timer
        timer = threading.Timer(1.0, flowMonitor.get, ["/wm/core/switch/00:00:08:00:27:ea:68:0c/aggregate/jso\
n"])
        timer.start()
        info = json.loads(ret[2])
        global lastByteCount
        if FlowMonitor.lastByteCount == 0:
            FlowMonitor.lastByteCount = int(info['aggregate']['byte_count'])
        if int(info['aggregate']['byte_count']) > FlowMonitor.lastByteCount:
          bandwidth = int(info['aggregate']['byte_count']) - FlowMonitor.lastByteCount
          print("bandwidth : %d b/s" %(bandwidth))
          if bandwidth > 50:
            subprocess.call(["cd /root/tutorial/clickos/minios/ && xl create config1.xen && /root/tutorial/co\
smos/dist/bin/cosmos start click2 ids.click"],shell=True)
            os._exit(0)
          FlowMonitor.lastByteCount = int(info['aggregate']['byte_count'])
          #print FlowMonitor.lastByteCount                                                                    
        return info
    def set(self, data):
        ret = self.rest_call(data, 'POST')
        return ret[0] == 200
    def remove(self, objtype, data):
        ret = self.rest_call(data, 'DELETE')
        return ret[0] == 200

    def rest_call(self, data, action, path):
       # path = '/wm/staticflowpusher/json'                                                                   
        headers = {
            'Content-type': 'application/json',
            'Accept': 'application/json',
            }
        body = json.dumps(data)
        conn = httplib.HTTPConnection(self.server, 8080)
        conn.request(action, path, body, headers)
        response = conn.getresponse()
        ret = (response.status, response.reason, response.read())
        print ret
        conn.close()
        return ret

flowMonitor = FlowMonitor('127.0.0.1')

if __name__ == "__main__":
    #while 1 :                                                                                                
      timer = threading.Timer(1.0, flowMonitor.get, ["/wm/core/switch/00:00:08:00:27:ea:68:0c/aggregate/json"\
])
      timer.start()
