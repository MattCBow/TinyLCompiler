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

struct LLNode {
	int *element;			/* i_cur object */
	LLNode *next;			/* next node */
};

int main()
{
	LLNode *q_head, *q_cur;
	Instruction *i_head, i_cur;
	q_head = q_cur = i_head = i_cur = NULL;

	i_head = ReadInstructionList(stdin);
	if (!i_head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	for(i_cur=i_head; i_cur!=NULL; i_cur=i_cur->next;){

		if(i_cur->opcode==OUTPUTAI){
			LLNode new;
			new.element = i_cur;
			new.next = NULL;
			if(q_head) new.next = q_head;
			q_head = new;
		}

		for(q_cur=q_head; q_cur!=NULL; q_cur=q_cur->next;){
			switch(q_cur->opcode){

			case OUTPUTAI:
				switch(i_cur->opcode){
				case STOREAI:
					break;
				}
				break;

			case LOADAI:
				switch(i_cur->opcode){
				case LOADAI:
						break;
				}
				break;

			case STOREAI:
				switch(i_cur->opcode){
				case LOADI:
					break;
				case ADD:
				case SUB:
				case MUL:
				case DIV:
				case OUTPUTAI:
					break;
				}
				break;

			case ADD:
			case SUB:
			case MUL:
			case DIV:
				switch(i_cur->opcode){
				case LOADI:
					break;
				case LOADAI:
					break;
				case ADD:
				case SUB:
				case MUL:
				case DIV:
					break;
				}
			break;
		}


	}

	if (i_head)
		PrintInstructionList(stdout, i_head);

	return EXIT_SUCCESS;
}
