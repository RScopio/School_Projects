#include<stdio.h>
#include<string.h>
#define N sizeof(polynomial)

char data[28], checksum[28], polynomial[] = "10001000000100001";
int length, i, k;

void xor() {
	for (k = 1; k < N; k++)
	{
		checksum[k] = ((checksum[k] == polynomial[k]) ? '0' : '1');
	}
}

void crc() {
	for (i = 0; i < N; i++)
	{
		checksum[i] = data[i];
	}
	do {
		if (checksum[0] == '1') {
			xor ();
		}
		for (k = 0; k < N - 1; k++) {
			checksum[k] = checksum[k + 1];
		}
		checksum[k] = data[i++];
	} while (i <= length + N - 1);
}

int main()
{
	printf("\nEnter data : ");
	scanf("%s", data);
	printf("\n______");
	printf("\nGeneratng polynomial : %s", polynomial);
	length = strlen(data);
	for (i = length; i < length + N - 1; i++) {
		data[i] = '0';
	}
	printf("\n_____");
	printf("\nModified data is : %s", data);
	printf("\n_____");
	crc();
	printf("\nChecksum is : %s", checksum);
	for (i = length; i < length + N - 1; i++) {
		data[i] = checksum[i - length];
	}
	printf("\n_____");
	printf("\nFinal codeword is : %s", data);
	printf("\n_____");
	printf("\nTest error detection 0(yes) 1(no)? : ");
	scanf("%d", &i);
	if (i == 0)
	{
		do {
			printf("\nEnter the position where error is to be inserted : ");
			scanf("%d", &i);
		} while (i == 0 || i > length + N - 1);
		data[i - 1] = (data[i - 1] == '0') ? '1' : '0';
		printf("\n_____");
		printf("\nErroneous data : %s\n", data);
	}
	crc();
	for (i = 0; (i < N - 1) && (checksum[i] != '1'); i++);
	if (i < N - 1)
	{
		printf("\nError detected\n\n");
	}
	else
	{
		printf("\nNo error detected\n\n");
	}
	printf("\n_____\n");
	return 0;
}
