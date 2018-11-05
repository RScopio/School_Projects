#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

//Ryan Scopio
//Recreates the wc command using pipes

typedef int bool;
#define true 1
#define false 0

int WhiteSpace(char);
struct CountObj WordCount(FILE *);
void error_exit(char *s);

struct CountObj
{
	int lines;
	int words;
	int chars;
};

struct Modifiers
{
	bool l;
	bool w;
	bool c;
};

int main(int argc, char **argv)
{
	bool hasMods = false;
	bool noFile;
	bool isParent = false;
	int fileCount = argc - 1;
	int j, i;
	int pd[2];
	pid_t pid;
	struct Modifiers mods = {false, false, false};
	struct CountObj total = {0, 0, 0};
	struct CountObj result;

	//find all modifiers (-l -w -c)
	for (j = 1; j < argc; j++)
	{
		if (argv[j][0] == '-')
		{
			fileCount--;
			hasMods = true;
			int modSize = sizeof(argv[j]) / sizeof(char);
			int i;
			for (i = 1; i < modSize; i++)
			{
				switch (argv[j][i])
				{
				case 'l':
					mods.l = true;
					break;
				case 'w':
					mods.w = true;
					break;
				case 'c':
					mods.c = true;
					break;
				default:
					break;
				}
			}
		}
	}

	//if no modifiers, all options are enabled
	if (hasMods == false)
	{
		mods.l = true;
		mods.w = true;
		mods.c = true;
	}

	if (fileCount == 0)
	{
		noFile = true;
	}
	else
	{
		noFile = false;
	}

	//create a process for each file & print the count of words, lines & characters
	if (pipe(pd) < 0)
		error_exit("Pipe failed");
	for (i = 1; i < argc || noFile == true; i++)
	{
		if (noFile == false && argv[i][0] == '-')
		{
			//don't try to open modifiers as files
			continue;
		}

		pid = fork();
		if (pid == (pid_t)0)
		{
			//This is the child process;

			FILE *fileRead;
			if (noFile == true)
			{
				fileRead = stdin; //read terminal input
			}
			else
			{
				fileRead = fopen(argv[i], "r"); //open file as read
			}

			if (fileRead == NULL)
			{
				printf("wc: %s: No such file or directory\n", argv[i]);
				return 1;
			}

			result = WordCount(fileRead);

			if (write(pd[1], &result, sizeof(struct CountObj)) == -1)
				error_exit("Write failed");

			close(pd[1]);
			return 0;
		}
		else if (pid < (pid_t)0)
		{
			//The fork failed
			error_exit("Fork failed");
		}
		else
		{
			//This is the parent process
			isParent = true;
			if (read(pd[0], &result, sizeof(struct CountObj)) == -1)
				error_exit("Read failed");

			if (mods.l == true)
				printf("%5d", result.lines);
			if (mods.w == true)
				printf("%5d", result.words);
			if (mods.c == true)
				printf("%5d", result.chars);
			if (noFile == false)
			{
				printf(" %s", argv[i]);
				printf(" process=%d", pid);
				printf("\n");
			}
			else
			{
				printf(" process=%d", pid);
				printf("\n");
				break;
			}

			if (fileCount > 1)
			{
				total.lines += result.lines;
				total.words += result.words;
				total.chars += result.chars;
			}
		}
	}

	close(pd[0]);

	if (isParent == true && fileCount > 1)
	{
		if (mods.l == true)
			printf("%5d", total.lines);
		if (mods.w == true)
			printf("%5d", total.words);
		if (mods.c == true)
			printf("%5d", total.chars);
		printf(" total");
		printf(" process=%d", getpid());
		printf("\n");
	}
	return 0;
}

//checks if a character is a whitespace
int WhiteSpace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == '\0' || c == EOF)
	{
		return 1;
	}
	return 0;
}

//counts the lines, words & characters of a file
struct CountObj WordCount(FILE *fileRead)
{
	char buffer[10000];
	int index = 0;
	while (!feof(fileRead)) //while not end of file
	{
		buffer[index] = fgetc(fileRead); //get char from fileRead
		index++;
	}
	fclose(fileRead);

	int lines = 0;
	int words = 0;

	if (buffer[0] != EOF)
	{
		lines++;
	}

	//if the first character is not a whitespace, add to word count
	if (WhiteSpace(buffer[0]) == 0)
	{
		words++;
	}

	char lastChar = buffer[0];
	int i;
	for (i = 0; i < index - 2; i++)
	{
		//if the current character is not whitespace and the last character was whitespace
		if (WhiteSpace(lastChar) == 1 && WhiteSpace(buffer[i]) == 0)
		{
			words++;
		}
		//if an endline character is reached
		if (buffer[i] == '\n')
		{
			lines++;
		}
		lastChar = buffer[i];
	}
	struct CountObj results = {lines, words, index - 1};
	return results;
}

void error_exit(char *s)
{
	fprintf(stderr, "\nERROR: %s - bye!\n", s);
	exit(1);
}
