#!/usr/bin/python3
import sys
#for line in sys.stdin:
#	print("%s" % line)
def fun(a, b, c = 'c', d = 'nanana'):
	print("\n%s %lf %s %s" % (a, b, c, d))

def sum(v):
	s = 0
	for x in v:
		s += x
	return s


#fin = open("data.in", "r")
fin = sys.stdin
#for line in f:
#	print("%s" % line, end='', flush = True)

#fun(b = 2.022,  a = 'aaa', c = 'ddd')
n = int(fin.readline().strip())
v = []

for el in fin.readline().strip().split(' '):
	v.append(int(el))
v.reverse()

print("%d" % (sum(v)))