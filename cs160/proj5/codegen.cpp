#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
#include "assert.h"
#include <typeinfo>
#include <stdio.h>

class Codegen : public Visitor
{
	private:

	FILE * m_outputfile;
	SymTab *m_st;

	// basic size of a word (integers and booleans) in bytes
	static const int wordsize = 4;

	int label_count; //access with new_label

	// ********** Helper functions ********************************

	// this is used to get new unique labels (cleverly named label1, label2, ...)
	int new_label() { return label_count++; }

	// this mode is used for the code
	void set_text_mode() { fprintf( m_outputfile, ".text\n\n"); }
	
	// PART 1:
	// 1) get arithmetic expressions on integers working:
	//	  you wont really be able to run your code,
	//	  but you can visually inspect it to see that the correct
	//    chains of opcodes are being generated.
	// 2) get function calls working:
	//    if you want to see at least a very simple program compile
	//    and link successfully against gcc-produced code, you
	//    need to get at least this far
	// 3) get boolean operation working
	//    before we can implement any of the conditional control flow 
	//    stuff, we need to have booleans worked out.  
	// 4) control flow:
	//    we need a way to have if-elses and while loops in our language. 
	//
	// Hint: Symbols have an associated member variable called m_offset
	//    That offset can be used to figure out where in the activation 
	//    record you should look for a particuar variable

	///////////////////////////////////////////////////////////////////////////////
	//
	//  function_prologue
	//  function_epilogue
	//
	//  Together these two functions implement the callee-side of the calling
	//  convention.  A stack frame has the following layout:
	//
	//                          <- SP (before pre-call / after post-ret)
	//  high -----------------
	//       | actual arg n  |
	//       | ...           |
	//       | actual arg 1  |  <- SP (just before call / just after ret)
	//       -----------------
	//       |  Return Addr  |  <- SP (just after call / just before ret)
	//       =================
	//       | previous %ebp |
	//       -----------------
	//       | temporary 1   |
	//       | ...           |
	//       | temporary n   |  <- SP (after prologue / before epilogue)
	//  low  -----------------
	//
	//
	//			  ||		
	//			  ||
	//			 \  /
	//			  \/
	//
	//
	//  The caller is responsible for placing the actual arguments
	//  and the return address on the stack. Actually, the return address
	//  is put automatically on the stack as part of the x86 call instruction.
	//
	//  On function entry, the callee
	//
	//  (1) allocates space for the callee's temporaries on the stack
	//  
	//  (2) saves callee-saved registers (see below) - including the previous activation record pointer (%ebp)
	//
	//  (3) makes the activation record pointer (frame pointer - %ebp) point to the start of the temporary region
	//
	//  (4) possibly copies the actual arguments into the temporary variables to allow easier access
	//
	//  On function exit, the callee:
	//
	//  (1) pops the callee's activation record (temporary area) off the stack
	//  
	//  (2) restores the callee-saved registers, including the activation record of the caller (%ebp)	 
	//
	//  (3) jumps to the return address (using the x86 "ret" instruction, this automatically pops the 
	//	  return address off the stack. After the ret, remove the arguments from the stack
	//
	//	For more info on this convention, see http://unixwiz.net/techtips/win32-callconv-asm.html
	//
	//	This convention is called __cdecl
	//
	//////////////////////////////////////////////////////////////////////////////
  
  void emit_prologue(SymName *name, unsigned int size_locals, unsigned int num_args)
  {
		fprintf(m_outputfile, "%s:\n", strdup(name->spelling())); 
		fprintf(m_outputfile, "pushl %%ebp\n");
		fprintf(m_outputfile, "movl %%esp, %%ebp\n");
		fprintf(m_outputfile, "subl $%d, %%esp\n", size_locals); 

		for (int i=1; i<=num_args; i++)
		{
		       fprintf( m_outputfile, "movl %d(%%ebp), %%eax\n", (i * 4) + 4);
			fprintf(m_outputfile, "movl %%eax, -%d(%%ebp)\n", i * 4);
		}   
	
   }

  void emit_epilogue()
  {
		fprintf(m_outputfile, "movl %%ebp, %%esp\n");
		fprintf(m_outputfile, "popl %%ebp\n");

		fprintf(m_outputfile, "ret\n");
  }


////////////////////////////////////////////////////////////////////////////////

public:
  
  Codegen(FILE * outputfile, SymTab * st)
  {
	m_outputfile = outputfile;
	m_st = st;
	
	label_count = 0;
  }
  
  void visitProgram(Program * p)
  {
	//Functions list
		list<Func_ptr>::iterator iter;
		char *name;
		for (iter=p->m_func_list->begin(); iter!=p->m_func_list->end(); iter++)
		{
			Func* f = (Func*)(*iter);
			name =  strdup(f-> m_symname -> spelling());
			fprintf( m_outputfile, ".globl %s\n", name);
		}

		p->visit_children(this);
		fprintf(m_outputfile, "\n");
  }
  void visitFunc(Func * p)
  {
	int num_args=0;
		list<Decl_ptr>::iterator iter;
		for (iter=p->m_decl_list->begin(); iter!=p->m_decl_list->end(); iter++)
		{
			num_args += ((Decl *)(*iter))->m_symname_list->size();
		}

		emit_prologue(p->m_symname,m_st->scopesize(p->m_attribute.m_scope), num_args);


		p->visit_children(this);
		emit_epilogue();
  }
  void visitFunction_block(Function_block * p)
  {
	p->visit_children(this);
  }
  void visitNested_block(Nested_block * p)
  {
	p->visit_children(this);
  }
  void visitAssignment(Assignment * p)
  {
	p->m_symname->accept( this );
 	p->m_expr->accept( this );
	fprintf( m_outputfile, "popl %%eax\n");
	fprintf( m_outputfile, "movl %%eax, -%d(%%ebp)\n", (m_st->lookup( p -> m_attribute.m_scope, p->m_symname->spelling()))->get_offset() + 4);	
  }
  void visitArrayAssignment(ArrayAssignment * p)
  {
	p->visit_children(this); 
	fprintf(m_outputfile, "popl %%eax\n"); 
	Symbol *x = m_st->lookup(p->m_attribute.m_scope, p->m_symname->spelling()); 
	int xx=4+x->get_offset();
	fprintf(m_outputfile, "movl %%eax, \t%d(%%ebp)\n", (-xx+(-1)*4*((IntLit*)p->m_expr_1)->m_primitive->m_data)); 
  }
  void visitCall(Call * p)
  {
	int n = 0;
	list<Expr_ptr>::reverse_iterator iter;
	for(iter = p->m_expr_list->rbegin();iter != p->m_expr_list->rend();iter++)
	{
		n = n + wordsize;
		(*iter)->accept( this );
	}
	Symbol *x = m_st->lookup(p->m_attribute.m_scope, p->m_symname_1->spelling());
	fprintf(m_outputfile, "call %s\n", strdup(p->m_symname_2->spelling()));
	fprintf(m_outputfile, "addl $%d, %%esp\n",n);
	fprintf( m_outputfile, "movl %%eax, -%d(%%ebp)\n", (m_st->lookup(p->m_attribute.m_scope, p->m_symname_1->spelling()))->get_offset() + 4);
  }
  void visitArrayCall(ArrayCall *p)
  {
	int n = 0;
	list<Expr_ptr>::reverse_iterator iter;
	for(iter = p->m_expr_list_2->rbegin();iter != p->m_expr_list_2->rend();iter++)
	{
		n = n + wordsize;
		(*iter)->accept( this );
	}
	Symbol *x = m_st->lookup(p->m_attribute.m_scope, p->m_symname_1->spelling());
	fprintf(m_outputfile, "call %s\n", strdup(p->m_symname_2->spelling()));
	fprintf(m_outputfile, "addl $%d, %%esp\n",n);
	x = m_st->lookup(p->m_attribute.m_scope, p->m_symname_2->spelling());
	int xx=4+x->get_offset();
	fprintf(m_outputfile, "movl %%eax, \t%d(%%ebp)\n", (-xx+(-1)*4*((IntLit*)p->m_expr_1)->m_primitive->m_data));
  }
  void visitReturn(Return * p)
  {
	p->visit_children(this);
	fprintf(m_outputfile, "popl %%eax\n");
  }

  // control flow
  void visitIfNoElse(IfNoElse * p)
  {
//lattice
	int label = new_label();

	p->m_expr->accept( this );
	fprintf( m_outputfile, "popl %%eax\n");

	fprintf(m_outputfile, "movl $0, %%ebx\n");
	fprintf(m_outputfile, "cmp %%eax, %%ebx\n");
	fprintf(m_outputfile, "je skip_if_%d\n", label);

	p->m_nested_block->accept( this );

	fprintf(m_outputfile, "skip_if_%d:\n", label);  
   }
  void visitIfWithElse(IfWithElse * p)
  {
//lattice
	p->m_expr->accept(this);
	int end=new_label();
	int b=new_label();
	fprintf(m_outputfile, "popl %%ecx\n");
	fprintf(m_outputfile, "jecxz L%d\n", b);
	p->m_nested_block_1->accept(this);
	fprintf(m_outputfile, "jmp L%d\n", end);
	fprintf(m_outputfile, "L%d:\n", b);
	p->m_nested_block_2->accept(this);
	fprintf(m_outputfile, "L%d:\n", end);

  }
  void visitWhileLoop(WhileLoop * p)
  {
//lattice
	int label = new_label();
	fprintf(m_outputfile, "continue_%d:\n", label);
 	p->m_expr->accept( this );
	fprintf( m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "movl $0, %%ebx\n");
	fprintf(m_outputfile, "cmp %%eax, %%ebx\n");
	fprintf(m_outputfile, "je end_%d\n", label);
 	p->m_nested_block->accept( this );
	fprintf(m_outputfile, "jne continue_%d\n", label);
	fprintf(m_outputfile, "end_%d:\n", label);
  }

  // variable declarations (no code generation needed)
  void visitDecl(Decl * p)
  {
  }
  void visitTInteger(TInteger * p)
  {
  }
  void visitTBoolean(TBoolean * p)
  {
  }
  void visitTIntArray(TIntArray * p)
  {
  }

  // comparison operations
  void visitCompare(Compare * p)
  {
	p->visit_children(this);
	int j=new_label();
	int end=new_label();
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "cmpl %%eax, %%ebx\n");
	fprintf(m_outputfile, "je L%d\n", j);
	fprintf(m_outputfile, "pushl $0\n");
	fprintf(m_outputfile, "jmp L%d\n", end);
	fprintf(m_outputfile, "L%d:\n", j);
	fprintf(m_outputfile, "pushl $1\n");
	fprintf(m_outputfile, "L%d:\n", end);
  }
  void visitNoteq(Noteq * p)
  {
	p->visit_children(this);
	int j=new_label();
	int end=new_label();
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "cmpl %%eax, %%ebx\n");
	fprintf(m_outputfile, "jne L%d\n", j);
	fprintf(m_outputfile, "pushl $0\n");
	fprintf(m_outputfile, "jmp L%d\n",end);
	fprintf(m_outputfile, "L%d:\n", j);
	fprintf(m_outputfile, "pushl $1\n");
	fprintf(m_outputfile, "L%d:\n", end);
  }
  void visitGt(Gt * p)
  {
	p->visit_children(this);
	int j=new_label();
	int end=new_label();
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "cmpl %%eax, %%ebx\n");
	fprintf(m_outputfile, "jg L%d\n", j);
	fprintf(m_outputfile, "pushl $0\n");
	fprintf(m_outputfile, "jmp L%d\n",end);
	fprintf(m_outputfile, "L%d:\n", j);
	fprintf(m_outputfile, "pushl $1\n");
	fprintf(m_outputfile, "L%d:\n", end);
  }
  void visitGteq(Gteq * p)
  {
	p->visit_children(this);
	int j=new_label();
	int end=new_label();
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "cmpl %%eax, %%ebx\n");
	fprintf(m_outputfile, "jge L%d\n", j);
	fprintf(m_outputfile, "pushl $0\n");
	fprintf(m_outputfile, "jmp L%d\n",end);
	fprintf(m_outputfile, "L%d:\n", j);
	fprintf(m_outputfile, "pushl $1\n");
	fprintf(m_outputfile, "L%d:\n", end);
  }
  void visitLt(Lt * p)
  {
	p->visit_children(this);
	int j=new_label();
	int end=new_label();
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "cmp %%eax, %%ebx\n");
	fprintf(m_outputfile, "jl L%d\n", j);
	fprintf(m_outputfile, "pushl $0\n");
	fprintf(m_outputfile, "jmp L%d\n",end);
	fprintf(m_outputfile, "L%d:\n", j);
	fprintf(m_outputfile, "pushl $1\n");
	fprintf(m_outputfile, "L%d:\n", end);
	
  }
  void visitLteq(Lteq * p)
  {
	p->visit_children(this);
	int j=new_label();
	int end=new_label();
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "cmp %%eax, %%ebx\n");
	fprintf(m_outputfile, "jle L%d\n", j);
	fprintf(m_outputfile, "pushl $0\n");
	fprintf(m_outputfile, "jmp L%d\n",end);
	fprintf(m_outputfile, "L%d:\n", j);
	fprintf(m_outputfile, "pushl $1\n");
	fprintf(m_outputfile, "L%d:\n", end);
  }

  // arithmetic and logic operations
  void visitAnd(And * p)
  {
	p->visit_children(this);
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "and %%ebx, %%eax\n");
	fprintf(m_outputfile, "pushl %%eax\n");
  }
  void visitOr(Or * p)
  {
	p->visit_children(this);
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "or %%ebx, %%eax\n");
	fprintf(m_outputfile, "pushl %%eax\n");
  }
  void visitMinus(Minus * p)
  {
	p->visit_children(this);
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "subl %%ebx, %%eax\n");
	fprintf(m_outputfile, "pushl %%eax\n");
   }
   void visitPlus(Plus * p)
   {
	p->visit_children(this);
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "addl %%ebx, %%eax\n");
	fprintf(m_outputfile, "pushl %%eax\n");
   }
   void visitTimes(Times * p)
   {
	p->visit_children(this);
	fprintf(m_outputfile, "popl %%eax\n");
	fprintf(m_outputfile, "popl %%ebx\n");
	fprintf(m_outputfile, "imul %%ebx\n");
	fprintf(m_outputfile, "pushl %%eax\n");
    }
    void visitDiv(Div * p)
    {
		p->visit_children(this);
		fprintf(m_outputfile, "popl %%ebx\n");
		fprintf(m_outputfile, "popl %%eax\n");
		fprintf(m_outputfile, "mov $0, %%edx\n");
		fprintf(m_outputfile, "idiv %%ebx\n");
		fprintf(m_outputfile, "pushl %%eax\n");
	}
	void visitNot(Not * p)
	{
		p->visit_children(this);
		fprintf(m_outputfile, "popl %%eax\n");
		fprintf(m_outputfile, "not %%eax\n");
		fprintf(m_outputfile, "addl $2, %%eax\n");
		fprintf(m_outputfile, "pushl %%eax\n");
	}
	void visitUminus(Uminus * p)
	{
		p->visit_children(this);
		fprintf(m_outputfile, "popl %%eax\n");
		fprintf(m_outputfile, "neg %%eax\n");
		fprintf(m_outputfile, "pushl %%eax\n");
	}
	void visitMagnitude(Magnitude * p) 
	{
		p->visit_children(this);
		int z=new_label();
		fprintf(m_outputfile, "cmp $0, %%eax\n");
		fprintf(m_outputfile, "jge L");
		fprintf(m_outputfile, "%d\n", z);
		fprintf(m_outputfile, "popl %%eax\n");
		fprintf(m_outputfile, "push  $-1\n");
		fprintf(m_outputfile, "popl %%ebx\n");
		fprintf(m_outputfile, "imul %%ebx\n");
		fprintf(m_outputfile, "pushl %%eax\n");
		fprintf(m_outputfile, "L");
		fprintf(m_outputfile, "%d:\n", z);
	}

	// variable and constant access
	void visitIdent(Ident * p)
	{
		p->visit_children(this);
		p->m_symname->accept( this );
		fprintf( m_outputfile, "pushl -%d(%%ebp)\n", (m_st->lookup(p->m_attribute.m_scope, p->m_symname->spelling()))->get_offset() + 4);
  	}
	void visitIntLit(IntLit * p)
	{
		fprintf(m_outputfile, "pushl $%d\n", p -> m_primitive -> m_data);
	}
	void visitBoolLit(BoolLit * p)
	{
		fprintf(m_outputfile, "pushl $%d\n", p -> m_primitive -> m_data);
	}
	void visitArrayAccess(ArrayAccess * p)
	{
		p->visit_children(this);
		fprintf( m_outputfile, "popl %%eax\n");
		fprintf( m_outputfile, "imul $4, %%eax\n");
		fprintf( m_outputfile, "movl %%ebp, %%ebx\n");
		fprintf( m_outputfile, "subl $%d, %%ebp\n", (m_st->lookup(p->m_attribute.m_scope, p->m_symname->spelling()))->get_size() + (m_st->lookup(p->m_attribute.m_scope, p->m_symname->spelling()))->get_size());//here
		fprintf( m_outputfile, "addl %%eax, %%ebp\n");
		fprintf( m_outputfile, "pushl 0(%%ebp)\n");
		fprintf( m_outputfile, "movl %%ebx, %%ebp\n");
	}

	// special cases
	void visitSymName(SymName * p)
	{
	}
	void visitPrimitive(Primitive * p)
	{
		fprintf( m_outputfile, "pushl $%d\n", p->m_data);
	}
};

