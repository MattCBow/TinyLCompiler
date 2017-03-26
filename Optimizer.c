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

Instruction *childI(Instruction *parent){
	printf("%p ---> ", (void *) parent);
	PrintInstruction(stdout,parent);
	Instruction *child;
	int source;
	for(child=parent; child; child=child->prev){
		source = -1;
		switch (parent->opcode) {
		case LOADI:				// 1 Constant => 1 Register
			switch (child->opcode){
			default:
				if(parent->opcode == child->opcode)source = 0;
				break;
			}
			break;
		case LOADAI: 			// 1 Variable => 1 Register
		case OUTPUTAI:		// 1 Variable => 1 Constant
			switch (child->opcode) {
			case STOREAI:		// 1 Register => 1 Variable
				if(parent->field2==child->field3) source = 1;
				break;
			default:
				break;
			}
			break;
		case STOREAI:			// 1 Register => 1 Variable
			switch (child->opcode) {
			case LOADI: 		// 1 Constant => 1 Register
				if(parent->field1==child->field2) source = 1;
				break;
			case LOADAI: 		// 1 Variable => 1 Register
			case ADD:				// 2 Registers => 1 Register
			case SUB:
			case MUL:
			case DIV:
				if(parent->field1==child->field3) source = 1;
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
				if(parent->field1==child->field2) source = 2;
				if(parent->field2==child->field2) source = 2;
				break;
			case LOADAI: 		// 1 Variable => 1 Register
			case ADD:				// 2 Registers => 1 Register
			case SUB:
			case MUL:
			case DIV:
				if(parent->field1==child->field3) source = 2;
				if(parent->field2==child->field3) source = 2;
				break;
			default:
				break;
			}
			break;

		}
		if(source == 0){
			return(NULL);
		}
		if(source == 1){
			parent = child;
			parent->next=childI(child);
			return(parent);
		}
		if(source == 2){
			// HOLD parent
			OpCode opcode;
			int field1, field2, field3;
			opcode = parent->opcode;
			field3 = parent->field3;
			field2 = parent->field2;
			field1 = parent->field1;
			parent->opcode = STOREAI;
			parent->field3 = 0;
			parent->field2 = 0;
			if(parent->field1==child->field2) parent->field1 = field2;
			if(parent->field2==child->field2) parent->field1 = field1;
			// FIND child_2
			Instruction *child_1, *child_2;
			child_1=childI(child);
			child_2 = childI(parent);
			// RESET parent
			parent->opcode = opcode;
			parent->field1 = field1;
			parent->field2 = field2;
			parent->field3 = field3;
			// Merge child_1 and child_2
			parent = child;
			while(child){
				printf("%p MERGE ", (void *) child);
				PrintInstruction(stdout, child);
				if(child_1){
					child->next=child_1;
					child_1=child_1->next;
				}
				if(child_2){
					child->next=child_2;
					child_2=child_2->next;
				}
				child->next=NULL;
				child=child->next;
			}
			return(parent);
		}
	}
	return(NULL);
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

	if (head) PrintInstructionList(stdout, head);
	printf("\n\n");

	head = out;
	out = childI(out);
	head->next = out;
	printf("\n\n");

	for(out = head; out; out=out->next){
		printf("%p ---> ", (void *) out);
		PrintInstruction(stdout,out);
	}

	//for(head=out;out->next;out=out->next) out->next->prev = out;


	return EXIT_SUCCESS;
}
