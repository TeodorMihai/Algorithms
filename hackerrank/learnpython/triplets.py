#!/usr/bin/python3
import sys

def modify(a):
	a.append(5)

def parseline():
	a = []
	for x in sys.stdin.readline().strip().split(' '):
		a.append(int(x))
	return a

def compare(v1, v2):
	
	points1 = 0
	points2 = 0

	for i in range(0 ,len(v1)):
		if v1[i] > v2[i]:
			points1 += 1
		elif v1[i] < v2[i]:
			points2 += 1
	return (points1, points2)

v1 = parseline()
v2 = parseline()
res = compare(v1, v2)
print("%d %d\n" % (res[0], res[1]))
