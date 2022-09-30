import sys

print("argc = %d" % len(sys.argv))
print("arg[0]: " + sys.argv[0])
if(len(sys.argv)>1):
	print("arg[1]: " + sys.argv[1])
if(len(sys.argv)>2):
	print("arg[2]: " + sys.argv[2])
