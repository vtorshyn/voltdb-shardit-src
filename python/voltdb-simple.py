#!/usr/bin/python

import json
import sys
import time
import threading
import urllib
import urllib2


def debug(what):
    print what

class VoltDBJSONClient(object):
    def __init__(self, host, port, api_version="1.0"):
	self.url="http://%s:%s/api/%s/" % (host, port, api_version)

    def buildRequest(self, procedure='@Statistics', params={}):
	jsonRequest = urllib.urlencode({
	    'Procedure' : procedure,
	    'Parameters' : params
	})
	#debug(jsonRequest)
	return jsonRequest

    def invokeRequest(self, request):
	try:
		response = urllib2.urlopen(self.url, request).read()
	except urllib2.URLError as e:
		return {'status' : -1, 'message' : e}
	jsonResponse = json.loads(response)
	return jsonResponse
	
class JSONClientThread(threading.Thread):

    def __init__(self, client, proc, params, transactions=10000):
	threading.Thread.__init__(self)
	self.client = client
	self.transactions = transactions
	self.proc = proc
	self.params = params

    def run(self):
	request = self.client.buildRequest(procedure=self.proc, params=self.params)
	for x in range(self.transactions):
	    response = self.client.invokeRequest(request)
	    if response['status'] <> 1:
		print "Error: %s" % (response)

def main():
    if len(sys.argv) < 4:
	print "%s <host> <threads count> <number of transactions> <volt procedure> <procedure params>" % (sys.argv[0], )
	exit(1)
    host = sys.argv[1]
    numThreads = int(sys.argv[2])
    numTransactions = int(sys.argv[3])
    proc = sys.argv[4]
    params = sys.argv[5]
    thread_list = []

    for x in range(numThreads):
	thread = JSONClientThread(VoltDBJSONClient(host, 8080), proc, params, numTransactions)
	thread.setDaemon(True)
	thread_list.append(thread)
    start = time.time()
    for thread in thread_list:
	thread.start()
    for thread in thread_list:
	if thread.isAlive():
	    thread.join()
    end = time.time()
    overall = end - start
    print "%s seconds (%s TPS)" % (overall, numThreads*numTransactions/overall)
if __name__ == "__main__":
    main()