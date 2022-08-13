from math import sqrt, ceil
from re import findall
from sys import argv

def encode():
	plainText = input('Enter string to encode:\n>').replace(' ', '')
	nearestSquare = ceil(sqrt(len(plainText)))**2
	paddedPlain = plainText + '='*(nearestSquare-len(plainText))
	sepPlain = findall('.'*int(sqrt(nearestSquare)), paddedPlain)
	cipherText = []

	for i in range(int(sqrt(nearestSquare))):
		for bit in sepPlain:
			cipherText.append(bit[i])
	return ''.join(cipherText)

def decode():
	cipherText = input('Enter string to decode:\n>')
	sepCipher = findall('.'*int(sqrt(len(cipherText))),cipherText)
	plainText = []
	for i in range(int(sqrt(len(cipherText)))):
		for bit in sepCipher:
			plainText.append(bit[i])
	return ''.join(plainText).replace('=', '')


args = argv[1:]
if '-e' in args:
	print(encode())
elif '-d' in args:
	print(decode())
else:
	print('Invalid arguments. Try -e or -d.')
