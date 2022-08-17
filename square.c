#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char* cipher(char outputBuffer[], char mode[]){
	// getting input
	char uInput[MAX] = {0};
	fgets(uInput, MAX, stdin);
	uInput[strcspn(uInput, "\n")] = 0x0;

	// getting the nearest square from the length of the plain text
	int nearestSquare =  pow(ceil(sqrt(strlen(uInput))), 2);
	
	// padding the plain text with '=' until length reaches the nearest square (doesn't affect cipher text)
	char paddedInput[MAX] = {0};
	strcpy(paddedInput, uInput);	
	for (int i = 0; i < nearestSquare - strlen(uInput); i++){
		strcat(paddedInput, "=");
	}

	// doing the cipher (encoding == decoding)
	char cipherOutput[MAX] = {0};
	int chunkSize = (int) sqrt(nearestSquare);
	char* chunk = calloc(chunkSize + 1, 1);
	for (int i = 0; i < chunkSize; i++){
		for (int j = 0; j < strlen(paddedInput); j += chunkSize){
			sprintf(chunk, "%.*s", chunkSize, &paddedInput[j]);	
			cipherOutput[strcspn(cipherOutput, "\0")] = chunk[i];
		}
	}
	free(chunk);

	// removing the '=' if there are
	if (strcmp(mode, "-d") == 0){
		int len = strlen(cipherOutput);
		for (int i = 0; i < len; i++){
			if (cipherOutput[i] == 61){
				for (int j = i; j < len; j++){
					cipherOutput[j] = cipherOutput[j + 1];
				}
				len--;
				i--;		
			}
		}
	}

	strcpy(outputBuffer, cipherOutput);
	return outputBuffer;
}

int main(int argc, char* argv[]){
	if (argv[1] == NULL || (strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-d") != 0)){
		puts("Wrong arguments. Try -e or -d.");
	}
	else{
		char outputBuffer[MAX] = {0};
		char mode[3] = {0};
		strcpy(mode, argv[1]);

		fputs("Enter string to encode/decode:\n>", stdout);
		cipher(outputBuffer, mode);
		printf("%s", outputBuffer);
	}
	
	return 0;
}