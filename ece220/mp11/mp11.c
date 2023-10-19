/*									tab:8
 *
 * mp11.c - skeleton code generation for ECE190 compiler MP (F08 MP5)
 *
 * "Copyright (c) 2008-2018 by Steven S. Lumetta."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Steve Lumetta
 * Version:	    3
 * Creation Date:   Wed Oct 15 10:16:14 2008
 * Filename:	    mp11.c
 * History:
 *	SL	3	Tue Apr 03 23:23:23 2018
 *		Changed MP5 to MP11 and 190 to 220 for ECE220.
 *	SL	2	Tue Oct 21 14:28:10 2008
 *		Extracted from gold version.
 *	SL	1	Wed Oct 15 10:16:14 2008
 *		First written.
 */


#include <stdio.h>

#include "ece220_label.h"
#include "ece220_parse.h"
#include "ece220_symtab.h"


/*
 * PARAMETERS AND CONSTANTS
 */

typedef enum {
    BR_NEVER, BR_P, BR_Z, BR_ZP, BR_N, BR_NP, BR_NZ, BR_ALWAYS, NUM_BR
} br_type_t;


/*
 * HELPER FUNCTION PROTOTYPES--see function headers for further information
 */

static void gen_long_branch (br_type_t type, ece220_label_t* label);

static void gen_statement (ast220_t* ast);
static void gen_for_statement (ast220_t* ast);
static void gen_if_statement (ast220_t* ast);
static void gen_return_statement (ast220_t* ast);
static void gen_pop_stack (ast220_t* ast);
static void gen_debug_marker (ast220_t* ast);

static void gen_expression (ast220_t* ast);
static void gen_push_int (ast220_t* ast);
static void gen_push_str (ast220_t* ast);
static void gen_push_variable (ast220_t* ast);
static void gen_func_call (ast220_t* ast);
static void gen_get_address (ast220_t* ast);
static void gen_op_assign (ast220_t* ast);
static void gen_op_pre_incr (ast220_t* ast);
static void gen_op_pre_decr (ast220_t* ast);
static void gen_op_post_incr (ast220_t* ast);
static void gen_op_post_decr (ast220_t* ast);
static void gen_op_add (ast220_t* ast);
static void gen_op_sub (ast220_t* ast);
static void gen_op_mult (ast220_t* ast);
static void gen_op_div (ast220_t* ast);
static void gen_op_mod (ast220_t* ast);
static void gen_op_negate (ast220_t* ast);
static void gen_op_log_not (ast220_t* ast);
static void gen_op_log_or (ast220_t* ast);
static void gen_op_log_and (ast220_t* ast);
static void gen_comparison (ast220_t* ast, const char* false_cond);
static void gen_op_cmp_ne (ast220_t* ast);
static void gen_op_cmp_less (ast220_t* ast);
static void gen_op_cmp_le (ast220_t* ast);
static void gen_op_cmp_eq (ast220_t* ast);
static void gen_op_cmp_ge (ast220_t* ast);
static void gen_op_cmp_greater (ast220_t* ast);


/*
 * FILE SCOPE VARIABLES
 * 
 * N.B.  You will need to have a file scope variable to implement one
 * of the statements.  Define it here.
 *
 * static int foo;  <-- a file scope variable ("static" means only this file)
 *
 */

static ece220_label_t* v; //v is a file scope statement to implement statement


/* 
 * INTERFACE FUNCTIONS -- called from other files; the one function listed
 * here is the equivalent of "main" for students working on this MP
 */

/* 
 * MP11_generate_code
 *   DESCRIPTION: perform LC-3 code generation (print to stdout)
 *   INPUTS: prog -- the main subroutine of the program (a list of
 *                   statements)
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
void 
MP11_generate_code (ast220_t* prog)
{
    v=label_create(); //file_scope
    ast220_t*n=prog;//prog linked list
    while(n!=NULL){
        gen_statement(n);
        n=n->next;
    }
    printf("%s\n", label_value(v));   
}

/*
 * HELPER FUNCTIONS (used only within this file)
 */

/* 
 * gen_long_branch
 *   DESCRIPTION: generate LC-3 assembly code for a branch without offset
 *                limitations
 *   INPUTS: type -- the type of branch to be performed
 *           label -- the branch target label
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_long_branch (br_type_t type, ece220_label_t* label)
{
    static const char* const br_names[NUM_BR] = {
        "; ", "BRp", "BRz", "BRzp", "BRn", "BRnp", "BRnz", "BRnzp"
    }; 
    br_type_t neg_type;
    ece220_label_t* target_label;
    ece220_label_t* false_label;

    neg_type = (type ^ 7);
    target_label = label_create ();
    false_label = label_create ();
    printf ("\t%s %s\n", br_names[neg_type], label_value (false_label));
    printf ("\tLD R3,%s\n\tJMP R3\n", label_value (target_label));
    printf ("%s\n", label_value (target_label));
    printf ("\t.FILL %s\n", label_value (label));
    printf ("%s\n", label_value (false_label));
}
// BR nz label1
// LD R3 label1
//JMP R3
// label1
// .FILL label
// label2
/* 
 * gen_statement
 *   DESCRIPTION: generate LC-3 assembly code for an arbitrary statement
 *   INPUTS: ast -- the AST node corresponding to the statement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_statement (ast220_t* ast)
{
    switch (ast->type) {
        case AST220_FOR_STMT:     gen_for_statement (ast);    break;
        case AST220_IF_STMT:      gen_if_statement (ast);     break;
        case AST220_RETURN_STMT:  gen_return_statement (ast); break;
        case AST220_POP_STACK:    gen_pop_stack (ast);        break;
        case AST220_DEBUG_MARKER: gen_debug_marker (ast);     break;
	default: fputs ("BAD STATEMENT TYPE\n", stderr);      break;
    }
}

/* 
 * gen_for_statement
 *   DESCRIPTION: generate LC-3 assembly code for an for loop
 *   INPUTS: ast -- the AST node corresponding to the for loop
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_for_statement (ast220_t* ast)
{
    //for 
    //initialize->labelbegin) test -> check -> 
    ece220_label_t* loop_begin=label_create();
    ece220_label_t* loop_end=label_create();
    if(ast->left!=NULL){
         gen_statement(ast->left);
    }
    //test begin after and set label first
    printf("%s\n",label_value(loop_begin));
    gen_expression(ast->test);
    printf("\tLDR R1, R6,#0\n\tADD R6,R6,#1\n\tADD R1,R1,#0\n");
    gen_long_branch(BR_Z,loop_end); //judge R1
    ast220_t* loop= ast->middle;
    while(loop!=NULL){ //loop body
        gen_statement(loop);
        loop=loop->next;
    }
    if(ast->right!=NULL){ //update 
        gen_statement(ast->right);
    }
    gen_long_branch(BR_ALWAYS,loop_begin); //jump
    printf("%s\n",label_value(loop_end)); //end

}

/* 
 * gen_if_statement
 *   DESCRIPTION: generate LC-3 assembly code for an if statement
 *   INPUTS: ast -- the AST node corresponding to the if statement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_if_statement (ast220_t* ast)
{
    ece220_label_t* case1=label_create();
    ece220_label_t* case2=label_create();
    ece220_label_t* end=label_create();
    //test
    gen_statement(ast->test);
    printf("\tLDR R1, R6,#0\n\tADD R6,R6,#1\n\tADD R1,R1,#0\n");//test R0
    gen_long_branch(BR_Z,case2); //judge R1
    printf("%s\n",label_value(case1));
    ast220_t* cur = ast->left;
    while (cur) {
		gen_statement(cur);				// 
		cur = cur->next;                //linked list loop cur
	}
    if (ast->right) {
		gen_long_branch(BR_ALWAYS, end);				// jump to end
	}
    printf("%s\n",label_value(case2));
    
    if (ast->right) {
		cur = ast->right;
		while (cur) {
			gen_statement(cur);			// Tested false
			cur= cur->next;
		}
    }
    gen_long_branch(BR_ALWAYS,end); // jump to end
    printf("%s",label_value(end));//end of if



}

/* 
 * gen_return_statement
 *   DESCRIPTION: generate LC-3 assembly code for a return statement
 *   INPUTS: ast -- the AST node corresponding to the return statement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_return_statement (ast220_t* ast)
{
    gen_expression(ast->left);
    printf("\tLDR R0,R6,#0\n\tADD R6,R6,#1\n\tSTR R0,R5,#3\n");//stack teardown and load to r5+3
    gen_long_branch(BR_ALWAYS,v);
    
}

/* 
 * gen_pop_stack
 *   DESCRIPTION: generate LC-3 assembly code to pop and discard a value
 *                from the stack
 *   INPUTS: ast -- the AST node corresponding to the pop stack statement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_pop_stack (ast220_t* ast)
{
    gen_expression(ast->left);
    printf("\tADD R6,R6,#1\n");
}

/* 
 * gen_debug_marker
 *   DESCRIPTION: generate LC-3 assembly code for a debug marker used to
 *                help debug LC-3 code generation; the marker is simply
 *                a comment in the assembly code that can be used to
 *                identify pieces of code generated by the compiler
 *   INPUTS: ast -- the AST node corresponding to the debug marker
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints an LC-3 assembly comment
 */
static void 
gen_debug_marker (ast220_t* ast)
{
    printf ("; --------------- DEBUG(%d) ---------------\n", ast->value);
}

/* 
 * gen_expression
 *   DESCRIPTION: generate LC-3 assembly code to calculate an arbitrary
 *                expression and push the result onto the stack
 *   INPUTS: ast -- the AST node corresponding to the expression
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_expression (ast220_t* ast)
{
    switch (ast->type) {
        case AST220_PUSH_INT:     gen_push_int (ast);       break;
        case AST220_PUSH_STR:     gen_push_str (ast);       break;
        case AST220_VARIABLE:     gen_push_variable (ast);  break;
        case AST220_FUNC_CALL:    gen_func_call (ast);      break;
	case AST220_GET_ADDRESS:  gen_get_address (ast);    break;
	case AST220_OP_ASSIGN:    gen_op_assign (ast);      break;
	case AST220_OP_PRE_INCR:  gen_op_pre_incr (ast);    break;
	case AST220_OP_PRE_DECR:  gen_op_pre_decr (ast);    break;
	case AST220_OP_POST_INCR: gen_op_post_incr (ast);   break;
	case AST220_OP_POST_DECR: gen_op_post_decr (ast);   break;
	case AST220_OP_ADD:       gen_op_add (ast);         break;
	case AST220_OP_SUB:       gen_op_sub (ast);         break;
	case AST220_OP_MULT:      gen_op_mult (ast);        break;
	case AST220_OP_DIV:       gen_op_div (ast);         break;
	case AST220_OP_MOD:       gen_op_mod (ast);         break;
	case AST220_OP_NEGATE:    gen_op_negate (ast);      break;
	case AST220_OP_LOG_NOT:   gen_op_log_not (ast);     break;
	case AST220_OP_LOG_OR:    gen_op_log_or (ast);      break;
	case AST220_OP_LOG_AND:   gen_op_log_and (ast);     break;
	case AST220_CMP_NE:       gen_op_cmp_ne (ast);      break;
	case AST220_CMP_LESS:     gen_op_cmp_less (ast);    break;
	case AST220_CMP_LE:       gen_op_cmp_le (ast);      break;
	case AST220_CMP_EQ:       gen_op_cmp_eq (ast);      break;
	case AST220_CMP_GE:       gen_op_cmp_ge (ast);      break;
	case AST220_CMP_GREATER:  gen_op_cmp_greater (ast); break;
	default: fputs ("BAD EXPRESSION TYPE\n", stderr);   break;
    }
}

/* 
 * gen_push_int
 *   DESCRIPTION: generate LC-3 assembly code to push a constant integer
 *                expression onto the stack
 *   INPUTS: ast -- the AST node corresponding to the integer
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_push_int (ast220_t* ast)
{
    ece220_label_t* falselabel=label_create();
    ece220_label_t* newlabel=label_create();
    printf("\tLD R0,%s\n",label_value(falselabel));
    printf("\t ADD R6,R6,#-1\n");
    printf("\tSTR R0,R6,#0\n");  //store to stack
    printf("\tBRnzp %s\n",label_value(newlabel));
    printf("%s\n",label_value(falselabel));
    printf("\t.FILL #%d\n", ast->value); // fill the value
    printf("%s\n",label_value(newlabel));
}      

/* 
 * gen_push_str
 *   DESCRIPTION: generate LC-3 assembly code to push a constant string
 *                expression onto the stack
 *   INPUTS: ast -- the AST node corresponding to the string
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_push_str (ast220_t* ast)
{
    ece220_label_t* falselabel=label_create();
    ece220_label_t* newlabel=label_create();
    printf("\tLEA R0,%s\n",label_value(falselabel));
    printf("\t ADD R6,R6,#-1\n");
    printf("\tSTR R0,R6,#0\n");
    printf("\tBRnzp %s\n",label_value(newlabel));
    printf("%s\n",label_value(falselabel));
    printf("\t.STRINGZ %s\n", ast->name); //store name
    printf("%s\n",label_value(newlabel));
}

/* 
 * gen_push_variable
 *   DESCRIPTION: generate LC-3 assembly code to push a variable's value
 *                onto the stack
 *   INPUTS: ast -- the AST node corresponding to the variable reference
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_push_variable (ast220_t* ast)
{
    symtab_entry_t* a= symtab_lookup(ast->name);
    int c=a->offset;					
	if (ast->left==NULL) {
		printf("\tLDR R0,R%d,#%d\n\tADD R6,R6,#-1\n\tSTR R0,R6,#0\n", 				
			5 - a->is_global, c);// var->is indicate the type
	} else {
		gen_expression(ast->left);								
		printf("\tLDR R1,R6,#0\n\tADD R6,R6,#1\n\tADD R0,R%d,#%d\n\tADD R1,R1,R0\n\tLDR R0,R1,#0\n\tADD R6,R6,#-1\n\tSTR R0,R6,#0\n", 
			5 - a->is_global, c);
	}
    
}

/* 
 * gen_func_call
 *   DESCRIPTION: generate LC-3 assembly code to perform a function call,
 *                remove the arguments from the stack, and leave the
 *                return value on top of the stack
 *   INPUTS: ast -- the AST node corresponding to the function call
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_func_call (ast220_t* ast)
{
    ece220_label_t* v;
    v=label_create();       //ld R3 v  JSRR R3  BRnzp end 
    ece220_label_t*n;       //v .Fill subroutine
    n=label_create();       //
    //first push argument
    ast220_t* argu=ast;
    int count=0;
    while(argu!=NULL){
        gen_expression(argu);
        count++;
        argu=argu->next;
    }
    printf("\tLD R3, %s\n\tJSRR R3\n\tBRnzp %s\n%s\n\t.FILL",label_value(v),label_value(n),label_value(v));
    switch ((ast->fnum)) //different subroutine
    {
    case AST220_PRINTF:
        printf("PRINTF\n");
        break;
    case AST220_RAND:
        printf("RAND\n");
        break;
    case AST220_SCANF:
         printf("SCANF\n");
         break;
    case AST220_SRAND:
         printf("SCRAND\n");
         break;
    default:
        break;
    }
    printf("%s\n\tLDR R0,R6,#0\n\tADD R6,R6,#1\n",label_value(n));
    printf("\tADD R6,R6,#%d\n",count);//pop argument
    printf("\tADD R6, R6,#-1\n");
    printf("\tSTR R0,R6,#0\n");  
}

/* 
 * gen_get_address
 *   DESCRIPTION: generate LC-3 assembly code to push the address of
 *                a variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to the variable reference
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_get_address (ast220_t* ast)
{
   symtab_entry_t* var = symtab_lookup(ast->left->name);				// variable
	if (NULL==ast->left->left) {
		printf("\tADD R0,R%d,#%d\n\tADD R6,R6,#-1\n",5 - var->is_global, var->offset);
        printf("\tSTR R0,R6,#0\n");
	} else {
		gen_expression(ast->left->left);	// array offset
		printf("\tLDR R1,R6,#0\n\tADD R6,R6,#1\n\tADD R0,R%d,#%d\n\tADD R0,R1,R0\n\tADD R6,R6,#-1\n", 5 - var->is_global, var->offset);
        printf("\tSTR R0,R6,#0\n");
	}
}

/* 
 * gen_op_assign
 *   DESCRIPTION: generate LC-3 assembly code to perform an assignment,
 *                leaving the value assigned on the stack (assignments
 *                are also expressions, with value equal to that of the
 *                value assigned)
 *   INPUTS: ast -- the AST node corresponding to the assignment
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_assign (ast220_t* ast)
{
    symtab_entry_t* var = symtab_lookup(ast->left->name);				
	gen_expression(ast->right);									
	if (NULL==ast->left->left) {										
		printf("\tADD R0,R%d,#%d\n\tLDR R1,R6,#0\n", 5 - var->is_global, var->offset);
        printf("\tSTR R1,R0,#0\n");
	} else {											
		gen_expression(ast->left->left);							
		printf("\tLDR R1,R6,#0\n\tADD R6,R6,#1\n\tADD R0,R%d,#%d\n\tADD R0,R1,R0\n\tLDR R1,R6,#0\n", 5 - var->is_global, var->offset);
	    printf("\tSTR R1,R0,#0\n");
    }   
}

/* 
 * gen_op_pre_incr
 *   DESCRIPTION: generate LC-3 assembly code to for a pre-increment 
 *                expression, which increments a variable and pushes
 *                the new value of the variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to pre-increment
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_pre_incr (ast220_t* ast)
{   //get the value and add 1
    symtab_entry_t* var = symtab_lookup(ast->left->name);				
	printf("\tADD R0,R%d,#%d\n", 5 - var->is_global, var->offset);		
    printf("\tLDR R1,R0,#0\n\tADD R1,R1,#1\n\tSTR R1,R0,#0\n\tADD R6,R6,#-1\n\tSTR R1,R6,#0\n");

}

/* 
 * gen_op_pre_decr
 *   DESCRIPTION: generate LC-3 assembly code to for a pre-decrement 
 *                expression, which decrements a variable and pushes
 *                the new value of the variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to pre-decrement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_pre_decr (ast220_t* ast)
{
    //get the value and minus 1
    symtab_entry_t* var = symtab_lookup(ast->left->name);				
	printf("\tADD R0,R%d,#%d\n", 5 - var->is_global, var->offset);		
    printf("\tLDR R1,R0,#0\n\tADD R1,R1,#1\n\tSTR R1,R0,#0\n\tADD R6,R6,#-1\n\tSTR R1,R6,#0\n");

}

/* 
 * gen_op_post_incr
 *   DESCRIPTION: generate LC-3 assembly code to for a post-increment 
 *                expression, which increments a variable and pushes
 *                the original value of the variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to post-increment
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_post_incr (ast220_t* ast)
{
    symtab_entry_t* var = symtab_lookup(ast->left->name);				
	printf("\tADD R0,R%d,#%d\n", 5 - var->is_global, var->offset);
    printf("\tLDR R1,R0,#0\n\tADD R3,R1,#1\n\tSTR R3,R0,#0\n\tADD R6,R6,#-1\n\tSTR R1,R6,#0\n"); //R1 minus 1
}

/* 
 * gen_op_post_decr
 *   DESCRIPTION: generate LC-3 assembly code to for a post-decrement 
 *                expression, which decrements a variable and pushes
 *                the original value of the variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to post-decrement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_post_decr (ast220_t* ast)
{
   symtab_entry_t* var = symtab_lookup(ast->left->name);				
	printf("\tADD R0,R%d,#%d\n", 5 - var->is_global, var->offset);
    printf("\tLDR R1,R0,#0\n\tADD R3,R1,#-1\n\tSTR R3,R0,#0\n\tADD R6,R6,#-1\n\tSTR R1,R6,#0\n"); //R1 minus 1
}

/* 
 * gen_op_add
 *   DESCRIPTION: generate LC-3 assembly code to calculate the sum of two
 *                expressions, leaving the sum on the stack
 *   INPUTS: ast -- the AST node corresponding to the add operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_add (ast220_t* ast)
{
    gen_expression(ast->left);
    gen_expression(ast->right);
    printf ("\tLDR R1,R6,#0\n\tLDR R0,R6,#1\n\tADD R6,R6,#2\n"); //R1 and R0 store the value then pop then out
    printf ("\tADD R1,R1,R0\n");
    printf ("\tADD R6,R6,#-1\n\tSTR R1,R6,#0\n");

}

/* 
 * gen_op_sub
 *   DESCRIPTION: generate LC-3 assembly code to calculate the difference 
 *                of two expressions, leaving the difference on the stack
 *   INPUTS: ast -- the AST node corresponding to the subtraction operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_sub (ast220_t* ast)
{
    gen_expression(ast->left);
    gen_expression(ast->right);
    printf("\t\tLDR R0,R6,#1\n");
    printf ("\tLDR R1,R6,#0\n\tADD R6,R6,#2\n"); //R1 and R0 store the value then pop then out
    printf("\tNOT R0,R0\n\tADD R0,R0#1\n");
    printf ("\tADD R1,R1,R0\n");
    printf ("\tADD R6,R6,#-1\n\tSTR R1,R6,#0\n");
}

/* 
 * gen_op_mult
 *   DESCRIPTION: generate LC-3 assembly code to calculate the product 
 *                of two expressions (using the MULTIPLY subroutine in
 *                the LC-3 library), leaving the product on the stack
 *   INPUTS: ast -- the AST node corresponding to the multiplication operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_mult (ast220_t* ast)
{
    ece220_label_t* v;
    v=label_create();       
    ece220_label_t*n;       
    n=label_create(); 
    gen_expression(ast->left);
    gen_expression(ast->right);
    printf("\t\tLDR R0,R6,#1\n");
    printf ("\tLDR R1,R6,#0\n\tADD R6,R6,#2\n");
    //subroutine store result in R0
    printf("\tLD R3, %s\n\tJSRR R3\n\tBRnzp %s\n%s\n\t.FILL MULTIPLY\n",label_value(v),label_value(n),label_value(v));
    printf("\tADD R6,R6,#-1\n\tSTR R0,R6,#0\n");
    
}

/* 
 * gen_op_div
 *   DESCRIPTION: generate LC-3 assembly code to calculate the quotient 
 *                of two expressions (using the DIVIDE subroutine in
 *                the LC-3 library), leaving the quotient on the stack
 *   INPUTS: ast -- the AST node corresponding to the division operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_div (ast220_t* ast)
{
    ece220_label_t* v;
    v=label_create();       
    ece220_label_t*n;       
    n=label_create(); 
    gen_expression(ast->left);
    gen_expression(ast->right);
    printf("\t\tLDR R0,R6,#1\n");
    printf ("\tLDR R1,R6,#0\n\tADD R6,R6,#2\n");
    //subroutine store result in R0
    printf("\tLD R3, %s\n\tJSRR R3\n\tBRnzp %s\n%s\n\t.FILL DIVIDE\n",label_value(v),label_value(n),label_value(v));
    printf("\tADD R6,R6,#-1\n\tSTR R0,R6,#0\n");
}

/* 
 * gen_op_mod
 *   DESCRIPTION: generate LC-3 assembly code to calculate the modulus 
 *                of one expression relative to a second expression (using 
 *                the MODULUS subroutine in the LC-3 library), leaving 
 *                the result on the stack
 *   INPUTS: ast -- the AST node corresponding to the division operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_mod (ast220_t* ast)
{
    ece220_label_t* v;
    v=label_create();       
    ece220_label_t*n;       
    n=label_create(); 
    gen_expression(ast->left);
    gen_expression(ast->right);
    printf("\t\tLDR R0,R6,#1\n");
    printf ("\tLDR R1,R6,#0\n\tADD R6,R6,#2\n");
    //subroutine store result in R0
    printf("\tLD R3, %s\n\tJSRR R3\n\tBRnzp %s\n%s\n\t.FILL MODULUS\n",label_value(v),label_value(n),label_value(v));
    printf("\tADD R6,R6,#-1\n\tSTR R0,R6,#0\n");
}

/* 
 * gen_op_negate
 *   DESCRIPTION: generate LC-3 assembly code to negate the value of an
 *                expression, leaving the result on the stack
 *   INPUTS: ast -- the AST node corresponding to the negation operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_negate (ast220_t* ast)
{
    gen_expression(ast->left);
    printf("\tLDR R0,R6,#0\n");
    printf("\tNOT R0,R0\n\tADD R0,R0,#1\n\tSTR R0,R6,#0\n");
}

/* 
 * gen_op_log_not
 *   DESCRIPTION: generate LC-3 assembly code to perform a logical NOT
 *                operation on an expression, leaving the result (0 or 1)
 *                on the stack
 *   INPUTS: ast -- the AST node corresponding to the logical NOT operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_log_not (ast220_t* ast)
{
    ece220_label_t* case1 = label_create();
	gen_expression(ast->left);									
	printf("\tAND R2,R2,#0\n\tLDR R0,R6,#0\n"); //load the stack  not 0 then it is true
    printf("\tADD R6,R6,#1\n\tADD R0,R0,#0\n\tBRnp %s\n\tADD R2,R2,#1\n", label_value(case1));								
	printf("%s\n", label_value(case1));
    printf("\tADD R6,R6,#-1\n\tSTR R2,R6,#0\n");
}

/* 
 * gen_op_log_or
 *   DESCRIPTION: generate LC-3 assembly code to perform a logical OR
 *                operation on two expressions, leaving the result (0 or 1)
 *                on the stack; the code generated must perform proper
 *                shortcutting, i.e., if the first expression is true
 *                the second is not evaluated (the code is not executed)
 *   INPUTS: ast -- the AST node corresponding to the logical OR operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_log_or (ast220_t* ast)
{//
    ece220_label_t* true_label = label_create(); //true lable
	ece220_label_t* false_label = label_create(); //false condition
	gen_expression(ast->left);									
	printf("\tLDR R1,R6,#0\n\tADD R6,R6,#1\n\tADD R1,R1,#0\n");
	gen_long_branch(BR_NP, false_label);	 // if R1 is true then the result is true							
	gen_expression(ast->right);									
	printf("\tLDR R1,R6,#0\n\tADD R6,R6,#1\n\tADD R1,R1,#0\n\tBRnp %s\n\tAND R2,R2,#0\n", label_value(false_label));	//R2 will not changed if it is true (np)			
    printf("\tBRnzp %s\n", label_value(true_label));
	printf("%s\n\tAND R2,R2,#0\n\tADD R2,R2,#1\n", label_value(false_label));
    printf("%s\n\tADD R6,R6,#-1\n\tSTR R2,R6,#0\n", label_value(true_label));

}

/* 
 * gen_op_log_and
 *   DESCRIPTION: generate LC-3 assembly code to perform a logical AND
 *                operation on two expressions, leaving the result (0 or 1)
 *                on the stack; the code generated must perform proper
 *                shortcutting, i.e., if the first expression is false
 *                the second is not evaluated (the code is not executed)
 *   INPUTS: ast -- the AST node corresponding to the logical AND operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_log_and (ast220_t* ast)
{
    ece220_label_t* labelf = label_create();
	ece220_label_t* labelt = label_create();
	gen_expression(ast->left);									
	printf("\tLDR R0,R6,#0\n\tADD R6,R6,#1\n\tADD R0,R0,#0\n");
	gen_long_branch(BR_Z, labelf);								// jump to false nedd to judge
	gen_expression(ast->right);
    printf("\tAND R2,R2,#0\n");   //initialize to 0
	printf("\tLDR R0,R6,#0\n\tADD R6,R6,#1\n\tADD R0,R0,#0\n\tBRz %s\n", label_value(labelf));  //if it is np then it is ture
    printf("\tADD R2,R2,#1\n\tBRnzp %s\n", label_value(labelt));
	printf("%s\n\tAND R2,R2,#0\n", label_value(labelf) );
    printf("%s\n\tADD R6,R6,#-1\n\tSTR R2,R6,#0\n",label_value(labelt));
}

/* 
 * gen_comparison
 *   DESCRIPTION: generate LC-3 assembly code for a comparison operator,
 *                leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the comparison
 *           false_cond -- a string representation of the condition codes 
 *                         for which the comparison is false (as calculated
 *                         by subtracting the second expression from the 
 *                         first)
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 *   KNOWN BUGS: ignores 2's complement overflow in making the comparison
 */
static void
gen_comparison (ast220_t* ast, const char* false_cond)
{
    ece220_label_t* false_label;

    false_label = label_create ();
    gen_expression (ast->left);
    gen_expression (ast->right);
    printf ("\tLDR R1,R6,#0\n\tLDR R0,R6,#1\n\tADD R6,R6,#2\n");
    printf ("\tAND R2,R2,#0\n\tNOT R1,R1\n\tADD R1,R1,#1\n\tADD R0,R0,R1\n");
    printf ("\tBR%s %s\n\tADD R2,R2,#1\n", false_cond,
	    label_value (false_label));
    printf ("%s\n", label_value (false_label));
    printf ("\tADD R6,R6,#-1\n\tSTR R2,R6,#0\n");
}

/* 
 * gen_op_cmp_ne
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is not equal to the value of a second 
 *                expression, leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the inequality operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_cmp_ne (ast220_t* ast)
{
    gen_comparison (ast, "z");
}

/* 
 * gen_op_cmp_less
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is less than the value of a second
 *                expression, leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the less-than operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_cmp_less (ast220_t* ast)
{
    gen_comparison (ast, "zp");
}

/* 
 * gen_op_cmp_le
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is less than or equal to the value 
 *                of a second expression, leaving the result (0 or 1) on 
 *                the stack
 *   INPUTS: ast -- the AST node corresponding to the less-or-equal-to 
 *                  operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_cmp_le (ast220_t* ast)
{
    gen_comparison (ast, "p");
}

/* 
 * gen_op_cmp_eq
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is equal to the value of a second 
 *                expression, leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the equality operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_cmp_eq (ast220_t* ast)
{
    gen_comparison (ast, "np");
}

/* 
 * gen_op_cmp_ge
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is greater than or equal to the value 
 *                of a second expression, leaving the result (0 or 1) on 
 *                the stack
 *   INPUTS: ast -- the AST node corresponding to the greater-or-equal-to 
 *                  operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_cmp_ge (ast220_t* ast)
{
    gen_comparison (ast, "n");
}

/* 
 * gen_op_cmp_greater
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is greater than the value of a second
 *                expression, leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the greater-than operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void 
gen_op_cmp_greater (ast220_t* ast)
{
    gen_comparison (ast, "nz");
}

