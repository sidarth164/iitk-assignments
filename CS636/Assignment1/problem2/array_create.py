#!/usr/bin/python

import sys
import random as r

n=2**int(sys.argv[1])
for i in range(n):
	print(r.randint(1,100))
