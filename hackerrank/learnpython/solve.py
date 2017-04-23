#!/usr/bin/python3.4
def solveMeFirst(a,b):
    return a + b
  
def min(a,b):
	if a > b:
		return b
	else:
		return a

def fact(a):
	if a == 1:
		return a
	else:
		return a * fact(a - 1)

num1 = int(input())
num2 = int(input())
#res = solveMeFirst(num1,num2)
#print(min(num1, num2))
print(fact(num1))
