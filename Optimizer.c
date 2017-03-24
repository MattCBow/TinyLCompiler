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
	Instruction *child;
	for(child=parent; child; child=child->prev){
		switch (parent->opcode) {
		case LOADI:				// 1 Constant => 1 Register
			switch (child->opcode) {
			default:
				return(NULL);
			break;
		case LOADAI: 			// 1 Variable => 1 Register
		case OUTPUTAI:		// 1 Variable => 1 Constant
			switch (child->opcode) {
			case STOREAI:		// 1 Register => 1 Variable
				if(parent->feild2==child->field3){
					child->next = childI(child);
					return(child);
				}
				break;
			}
			break;
		case STOREAI:			// 1 Register => 1 Variable
			switch (child->opcode) {
			case LOADI: 		// 1 Constant => 1 Register
				if(parent->feild1==child->feild2){
					child->next=childI(child);
					return(child);
				}
				break;
			case LOADAI: 		// 1 Variable => 1 Register
			case ADD:				// 2 Registers => 1 Register
			case SUB:
			case MUL:
			case DIV:
				if(parent->feild1==child->feild3){
					child->next=childI(child);
					return(child);
				}
				break;
			}
			break;
		case ADD:
		case SUB:
		case MUL:
		case DIV:					// 2 Registers => 1 Register
			switch (child->opcode) {
			case LOADI: 		// 1 Constant => 1 Register
				if(parent->feild1==child->feild2 || parent->feild2==child->feild2){
					// SET child_1
					Instruction *child_1, *child_2;
					child_1=childI(child);
					// HOLD parent
					OpCode opcode;
					int feild1, feild2, feild3, find_feild;
					opcode = parent->opcode;
					feild1 = parent->field1;
					feild2 = parent->field2;
					feild3 = parent->field3;
					if(parent->feild1==child->feild2) find_feild = feild2;
					if(parent->feild2==child->feild2) find_feild = feild1;
					// REPLACE parent
					parent->opcode = STOREAI;
					parent->feild1 = find_feild;
					parent->field2 = 0;
					parent->field3 = 0;
					// FIND child_2
					child_2 = childI(parent);
					// RESET parent
					parent->opcode = opcode;
					parent->field1 = feild1;
					parent->field2 = feild2;
					parent->field3 = feild3;
					// Connect child_1 and child_2
					for(child=child_1; child_1->next; child_1=child_1->next);
					child_1->next=child_2;
					// return
					return(child);
				}
				break;
			case LOADAI: 		// 1 Variable => 1 Register
			case ADD:				// 2 Registers => 1 Register
			case SUB:
			case MUL:
			case DIV:
				if(parent->feild1==child->feild3 || parent->feild2==child->feild3){
					// SET child_1
					Instruction *child_1, *child_2;
					child_1=childI(child);
					// HOLD parent
					OpCode opcode;
					int feild1, feild2, feild3, find_feild;
					opcode = parent->opcode;
					feild1 = parent->field1;
					feild2 = parent->field2;
					feild3 = parent->field3;
					if(parent->feild1==child->feild2) find_feild = feild2;
					if(parent->feild2==child->feild2) find_feild = feild1;
					// REPLACE parent
					parent->opcode = STOREAI;
					parent->feild1 = find_feild;
					parent->field2 = 0;
					parent->field3 = 0;
					// FIND child_2
					child_2 = childI(parent);
					// RESET parent
					parent->opcode = opcode;
					parent->field1 = feild1;
					parent->field2 = feild2;
					parent->field3 = feild3;
					// Connect child_1 and child_2
					for(child=child_1; child_1->next; child_1=child_1->next);
					child_1->next=child_2;
					// return
					return(child);
				}
				break;
			break;
		}
	}
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
	for(out=head; out->opcode==OUTPUTAI; out=out->next);
	out->next = childI(out);
	for(head=out;out->next;out=out->next) out->next->prev = out;


	if (head)
		PrintInstructionList(stdout, head);

	return EXIT_SUCCESS;
}
