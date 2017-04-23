#!/usr/bin/python3
import sys

if __name__ == "__main__":

	fin = sys.stdin

	X = int(fin.readline().strip())
	Y = int(fin.readline().strip())
	Z = int(fin.readline().strip())
	N = int(fin.readline().strip())
	v = [ [x, y, z] for x in range(0, X + 1) for y in range(0, Y + 1) for z in range(0, Z + 1) if (x + y + z != N)]
	print(v)
