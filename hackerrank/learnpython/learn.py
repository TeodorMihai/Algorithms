#!/usr/bin/python3
import sys

def getKey(item):
	return item

if __name__ == "__main__":

	fin = sys.stdin

	n = int(fin.readline().strip())
	v = []
	for i in range(0, n):
		line = fin.readline().strip().split(' ')
		
		if line[0] == "insert":
			v.insert(int(line[1]), int(line[2]))
		elif line[0] == "print":
			print(v)
		elif line[0] == "remove":
			v.remove(int(line[1]))
		elif line[0] == "append":
			v.append(int(line[1]))
		elif line[0] == "sort":
			v = sorted(v, key = lambda x : x)
		elif line[0] == "pop":
			v.pop()
		else: v.reverse()
