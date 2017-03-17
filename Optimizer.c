/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2017                              *
 *  Author: Ulrich Kremer                    *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	printf("Were doing something\n");
	Instruction *head;
	printf("Come on guy\n");``
	head = ReadInstructionList(stdin);
	printf("Don't be prick about it\n");
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	/* YOUR CODE GOES HERE */
	printf("Come on guy\n");


	if (head)
		printf("Don't be prick about it\n");
		PrintInstructionList(stdout, head);

	return EXIT_SUCCESS;
}
