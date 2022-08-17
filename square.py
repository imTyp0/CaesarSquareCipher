from math import sqrt, ceil
from re import findall
from sys import argv

def cipher(mode):
	uInput = input('Enter string to encode/decode:\n>').replace(' ', '')
	nearestSquare = ceil(sqrt(len(uInput)))**2
	paddedInput = uInput + '='*(nearestSquare-len(uInput))
	sepInput = findall('.'*int(sqrt(nearestSquare)), paddedInput)
	output = []

	for i in range(int(sqrt(nearestSquare))):
		for bit in sepInput:
			output.append(bit[i])
	
	if '-d' in mode:
		output = filter(lambda x: x if x != '=' else '', output)

	return ''.join(output)

args = argv[1:]
if args == [] or ("-e" not in args and "-d" not in args):
	print('Invalid arguments. Try -e or -d.')
else:
	print(cipher(args[0]))
