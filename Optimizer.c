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
	Instruction *q_cur, *q_head, *q_tail;
	Instruction *i_cur, *i_head, *i_tail;
	Instruction *o_cur, *o_head, *o_tail;

	q_cur = q_head = q_tail NULL;
	i_cur = i_head = i_tail = NULL;
	o_cur = o_head = o_tail = NULL;

	i_head = ReadInstructionList(stdin);
	if (!i_head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	for(i_cur=i_head; i_cur->next; i_cur=i_cur->next);
	i_tail = i_cur;
	i_cur = i_head;




	for(i_cur=i_tail; i_cur!=i_head; i_cur=i_cur->prev){
		// Travese backwards through the instructions
		if(i_cur->opcode==OUTPUTAI){
			Intruction q_new;
			q_new = *i_cur;
			q_new.prev = NULL;
			q_new.next = q_head;
			q_head = &q_new;
			if(q_head->next) q_head->next->prev = q_head;
		}
		// Push all OUTPUTAIs to the queue
		for(q_cur=q_head; q_cur ; q_cur=q_cur->next;){
			// Search q_instrs if i.out = q.in
			switch (q_cur->opcode) {
			case OUTPUTAI:		// 1 Variable => 1 Constant
			case LOADAI: 			// 1 Variable => 1 Register
				switch (i_cur->opcode) {
				case STOREAI:		// 1 Register => 1 Variable
					if(q_cur->feild2==i_cur->field3){
						// Add i_cur to q_instrs
						Intruction q_new;
						q_new = *i_cur;
						q_new.prev = NULL;
						q_new.next = q_head;
						q_head = &q_new;
						if(q_head->next) q_head->next->prev = q_head;
						// Remove q_cur from q_instrs
						q_cur->prev->next = q_cur->next;
						if(q_cur->next) q_cur->next->prev = q_cur->prev;
						// Add q_cur to o_instrs
						q_cur->next = o_head;
						o_head = q_cur;
						if(o_head->next) o_head->next->prev = o_head;
						q_cur = NULL;
					}
					break;
				}
				break;
			case STOREAI:		// 1 Register => 1 Variable
				switch (i_cur->opcode) {
				case LOADI: 		// 1 Constant => 1 Register
					if(q_cur->feild1 == i_cur->feild2){
						// Remove q_cur from q_instrs
						if(q_cur->next) q_cur->next->prev = q_cur->prev;
						if(q_cur->prev){
							q_cur->prev->next = q_cur->prev;
						}else{
							q_head=q_cur->next;
						}
						// Add q_cur to o_instrs
						q_cur->next = o_head;
						o_head = q_cur;
						if(o_head->next) o_head->next->prev = o_head;
						q_cur = NULL;
						// Add i_cur to o_instrs
						Intruction o_new;
						o_new = *i_cur;
						o_new.prev = NULL;
						o_new.next = o_head;
						o_head = &o_new;
						if(o_head->next) o_head->next->prev = o_head;
					}
					break;
				case LOADAI: 		// 1 Variable => 1 Register
				case ADD:				// 2 Registers => 1 Register
				case SUB:
				case MUL:
				case DIV:
					// Check Field 3
					break;
				}


				break;
			case ADD:
			case SUB:
			case MUL:
			case DIV:				// 2 Registers => 1 Register
				// Search for second source register
			}


	}

	if (i_head)
		PrintInstructionList(stdout, i_head);

	return EXIT_SUCCESS;
}
