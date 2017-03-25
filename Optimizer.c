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

typedef enum {END, NEXT, SPLIT} Match;

Instruction *childI(Instruction *parent){
	PrintInstruction(stdout,parent);
	Instruction *child, *child_1, *child_2;
	for(child=parent; child; child=child->prev){

		Match match;

		switch (parent->opcode) {
		case LOADI:				// 1 Constant => 1 Register
			switch (child->opcode){
			default:
				if(parent->opcode==child->opcode) match = END;
				break;
			}
			break;
		case LOADAI: 			// 1 Variable => 1 Register
		case OUTPUTAI:		// 1 Variable => 1 Constant
			switch (child->opcode) {
			case STOREAI:		// 1 Register => 1 Variable
				printf('dick');
				if(parent->field2==child->field3) match=NEXT;
				break;
			default:
				break;
			}
			break;
		case STOREAI:			// 1 Register => 1 Variable
			switch (child->opcode) {
			case LOADI: 		// 1 Constant => 1 Register
				if(parent->field1==child->field2) match=NEXT;
				break;
			case LOADAI: 		// 1 Variable => 1 Register
			case ADD:				// 2 Registers => 1 Register
			case SUB:
			case MUL:
			case DIV:
				if(parent->field1==child->field3) match=NEXT;
				break;
			default:
				break;
			}
			break;
		case ADD:
		case SUB:
		case MUL:
		case DIV:					// 2 Registers => 1 Register
			switch (child->opcode) {
			case LOADI: 		// 1 Constant => 1 Register
				if(parent->field1==child->field2) match=SPLIT;
				if(parent->field2==child->field2) match=SPLIT;
				break;
			case LOADAI: 		// 1 Variable => 1 Register
			case ADD:				// 2 Registers => 1 Register
			case SUB:
			case MUL:
			case DIV:
				if(parent->field1==child->field3) match=SPLIT;
				if(parent->field2==child->field3)	match=SPLIT;
				break;
			default:
				break;
			}
			break;
		}

		switch(match){
		case END:
			return(NULL);
		case NEXT:
			printf('dunce');
			child_1 = childI(child);
			child->next = child_1;
			return(child);
		case SPLIT:
			// SET child_1
			child_1=childI(child);
			// HOLD parent
			OpCode opcode;
			int field1, field2, field3, find_field;
			opcode = parent->opcode;
			field1 = parent->field1;
			field2 = parent->field2;
			field3 = parent->field3;
			if(parent->field1==child->field2) find_field = field2;
			if(parent->field2==child->field2) find_field = field1;
			// REPLACE parent
			parent->opcode = STOREAI;
			parent->field1 = find_field;
			parent->field2 = 0;
			parent->field3 = 0;
			// FIND child_2
			//child_2 = childI(parent);
			// RESET parent
			parent->opcode = opcode;
			parent->field1 = field1;
			parent->field2 = field2;
			parent->field3 = field3;
			// Connect child_1 and child_2
			//for(child=child_1; child_1->next; child_1=child_1->next);
			//child_1->next=child_2;
			// return
			child->next=child_1;
			return(child);
		}
	}
	return(child);
}

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	Instruction *out;
	for(out=head; out->opcode!=OUTPUTAI; out=out->next);
	out->next = childI(out);
	//for(head=out;out->next;out=out->next) out->next->prev = out;
	printf("\n\n");
	if (out)
		PrintInstructionList(stdout, head);

	return EXIT_SUCCESS;
}
