#!/usr/bin/python3
import sys
if __name__ == "__main__":

	fin = open("data.in", "r")

	n = int(fin.readline().strip())
	v = [ int(x) for x in fin.readline().strip().split(' ')]
	t = tuple(v)
	print(hash(t))