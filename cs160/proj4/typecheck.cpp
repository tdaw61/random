#include <iostream>
#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
#include "assert.h"


//for loop for iterating over containers (such as lists)
//creates an iterator of the appropriate type and does
//a for loop from begin to end
//you can WRITEME or not
//not necessary
#define forall(iterator,listptr) \


// check that the types are the same and then cast
// example DeclImpl* di = safeptrcast( DeclImpl, i ) 
// casts i to type DeclImpl*
//you can WRITEME or not
//not necessary
#define safeptrcast(ptrbasetype, ptr) \


// the default attribute propagation rule
//you can WRITEME or not
//not necessary
#define default_rule(X) \


#include <typeinfo>
#include <stdio.h>

/***********

  General

x   * There must be a root level function called Main.
x   * Main should have no arguments.
x   * No two same identifiers can be declared twice in the same scope. The parameter list of a function should be treated as declared variables for this purpose.
x   * No variable name may be used before it is declared in the current or lower scope. 
x   * No function call may be made before it is declared in the current or lower scope.
x   * No array may be indexed before it is declared in the current or lower scope.
x   * For any function call, its actual parameters must match the formal parameters of the declaration (in number and type).
x   * The return statement must match the type declared by the function.
x   * The return statement must must be the last statement of each function code block 

  Statements

x   * The types of left-hand side and right-hand side of an assign statement must match. This goes for all assignments:
	variable assignments, function calls, assigning to an element of an array, assigning a function call to an array element, and the optional assignments
	inside a for statement. If the assigned-to symbol is not a variable, throw a var_undef error; when assigning to the element of a non-existing array
	throw an array_undef error. 
x   * The type of the premise of an if statement or the requirement of a for statement must be boolean.
x   * The optional statements inside a for statement have to be assignments. You should only allow assigning an expression to a variable.

  Expressions

    * The operands of an expression must match the operator. The following list enumerate the operator types:
x         + For any Arithmetic Operator node, both its left and right child must be expressions of integer type.
		return type will be integer
x         + For any Conditional Operator node, both its left and right child must be expressions of boolean type.
		return type is boolean
x         + For any Equality Operator node, its left and right child must have the same type (intarrays are not permitted).
		return type is boolean
x         + For any Relational Operator node, the left and right child must both be integers.
		return type is boolean
x         + For Unary Operator not, child and return are both bool
x         + For Unary Operator minus, child and return are both integer
x         + For Absolute values, child can be only be of type integer
x         + For indexing an array,
                return type is integer
x   * Intarrays can only be indexed by integer expressions

  Also Need to 

    * Set the attribute m_scope to the correct scope for each ast node

*****/

// Returns true if the statement is of type Return
bool is_return(Stat* stat)
{
	return dynamic_cast<Return*>(stat) != NULL;
}

// Returns true if the statement is of type Assignment
bool is_assignment(Stat* stat)
{
	return dynamic_cast<Assignment*>(stat) != NULL;
}

// Returns true if the statement is of type None
bool is_none(Stat* stat)
{
	return dynamic_cast<None*>(stat) != NULL;
}

class Typecheck : public Visitor {
 private:
  FILE* m_errorfile;
  SymTab* m_st;

  // the set of recognized errors
  enum errortype 
  {
	no_main,
	main_args_err,
	dup_ident_name,
	var_undef,
	func_undef,
	array_undef,
	call_narg_mismatch,
	call_args_mismatch,
	call_type_mismatch,
	ret_type_mismatch,
	ret_misplaced_err,
	ret_missing_err,

	incompat_assign,
	if_pred_err,
	for_pred_err,
	for_assign_err,
	
	expr_type_err,
	array_index_error
  };

  // print the error to file and exit
  void t_error( errortype e, Attribute a ) 
  {
	fprintf(m_errorfile,"on line number %d, ", a.lineno );

	switch( e ) {
	case no_main: fprintf(m_errorfile,"error: no main\n"); break;
	case main_args_err: fprintf(m_errorfile,"error: Main function has arguments\n"); break;
	case dup_ident_name: fprintf(m_errorfile,"error: duplicate identifier name in same scope\n"); break;
	case var_undef: fprintf(m_errorfile,"error: undefined integer/boolean variable\n"); break;
	case func_undef: fprintf(m_errorfile,"error: call to an undefined function\n"); break;
	case array_undef: fprintf(m_errorfile,"error: indexing an undefined array\n"); break;
	case call_narg_mismatch: fprintf(m_errorfile,"error: function call has different number of args than the declaration\n"); break;
	case call_args_mismatch: fprintf(m_errorfile,"error: type mismatch in function call args\n"); break;
	case ret_type_mismatch: fprintf(m_errorfile, "error: type mismatch in return statement\n"); break;
	case ret_misplaced_err: fprintf(m_errorfile, "error: misplaced return statement\n"); break;
	case ret_missing_err: fprintf(m_errorfile, "error: missing return statement\n"); break;

	case incompat_assign: fprintf(m_errorfile,"error: types of right and left hand side do not match in assignment\n"); break;
	case if_pred_err: fprintf(m_errorfile,"error: predicate of if statement is not boolean\n"); break;
	case for_pred_err: fprintf(m_errorfile,"error: predicate of for statement is not boolean\n"); break;
	case for_assign_err: fprintf(m_errorfile, "error: statement inside a for statement is not a variable assignment\n"); break;

	case expr_type_err: fprintf(m_errorfile,"error: incompatible types used in expression\n"); break;
	case array_index_error: fprintf(m_errorfile, "error: intarray index not integer\n"); break;
	
	default: fprintf(m_errorfile,"error: no good reason\n"); break;
	}
	exit(1);
  }

  // NOTE
  // The following methods are here to help you get started
  // They are not called from anywhere unless if YOU call them, so it's up to you
  // to call them at the right places
  //
  // Feel free to add new functions to this list, rearrange them or even skip using them
  // This list is NOT complete, it doesn't cover anything you need to cover

  // check that there is one and only one main
  void check_for_one_main(ProgramImpl *p)
  {
      
      list<Func_ptr>::iterator iter;
      bool hasFound = false;
      string mainstr = "Main";
      
      for (iter = p->m_func_list->begin(); iter != p->m_func_list->end(); ++iter) {
          if (!hasFound){
              if (mainstr.compare((dynamic_cast<FuncImpl*>(*iter))->m_symname->spelling()) == 0)
                  hasFound = true;}
          else {
              if (mainstr.compare((dynamic_cast<FuncImpl*>(*iter))->m_symname->spelling()) == 0)
                  this->t_error(dup_ident_name, (*iter)->m_attribute); 
          }
      }
      
      list<Decl_ptr>::iterator iter;
      list<SymName_ptr>::iterator  iter2;
      
      for (iter = p->m_decl_list->begin(); iter != p->m_decl_list->end(); ++iter) {
          for(iter2 =(dynamic_cast<DeclImpl*>(*iter))->m_symname_list->begin(); iter2 != (dynamic_cast<DeclImpl*>(*iter))->m_symname_list->end(); ++iter2){
              (dynamic_cast<DeclImpl*>(*iter))->m_type->accept(this);
              s->m_arg_type.push_back((dynamic_cast<DeclImpl*>(*iter))->m_type->m_attribute.m_basetype);
          }
      }
       
      if (!hasFound)
          this->t_error(no_main,  p->m_attribute);

  }

  // create a symbol for the function and check there is none already existing
  void add_func_symbol(FuncImpl *p)
  {
      
      char *name; Symbol *s;
      
      name = strdup((p)->m_symname->spelling());
      
      s = new Symbol();
      s->m_basetype = bt_function;
      
      s->m_return_type = p->m_type->m_attribute.m_basetype;
      
      if (! m_st->insert(name, s))
          this->t_error(dup_ident_name,  p->m_attribute);


  }

  // add symbol table information for all the declarations following
  void add_decl_symbol(DeclImpl *p)
  {
      
      list<SymName_ptr>::iterator iter;
      char *name; Symbol *s;
      
      for (iter = p->m_symname_list->begin(); iter != p->m_symname_list->end(); ++iter) {
          name = strdup((*iter)->spelling());
          s = new Symbol();
          s->m_basetype = p->m_type->m_attribute.m_basetype;
          
          if (! m_st->insert(name, s))
              this->t_error(dup_ident_name,  p->m_attribute);
      }
  }

  // check that the return statement of a function has the appropriate type.
  // The type must not be intarray
  void check_return_type(FuncImpl *p) 
  {
      
      Basetype temp;
      list<Stat_ptr>::iterator iter;
      
      temp = p->m_type->m_attribute.m_basetype;
      
      iter = (dynamic_cast<Function_blockImpl*>(p->m_function_block))->m_stat_list->end();
      
      iter--;

      if ((dynamic_cast<Return*>(*iter))->m_expr->m_attribute.m_basetype != p->m_type->m_attribute.m_basetype)
          this->t_error(ret_type_mismatch,(dynamic_cast<Return*>(*iter))->m_expr->m_attribute);
  
  }

  // check that the only possible location of a return statement
  // is the last statement of the code block, and that the return
  // statement has to be there
  void check_return_location(Function_blockImpl *p)
  {
      list<Stat_ptr>::iterator iter;
      bool hasFound = false;
      
      for(iter = p->m_stat_list->begin(); iter != p->m_stat_list->end(); ++iter){
          if (hasFound){
              this->t_error(ret_misplaced_err, (*iter)->m_attribute);
          }
          else if(is_return(*iter)){
              hasFound = true;
          }
      }
      
      if(!hasFound){
          this->t_error(ret_missing_err, p->m_attribute);
      }

  }

  // check that the assigned-to variable exists and that the right-hand-side expression is valid
  // check that the return type of the expression matches the type of the variable
  void check_assignment( Assignment * p )
  {
      Symbol *s;
      
      s = m_st->lookup(p->m_symname->spelling());
      
      if(!s)
          this->t_error(var_undef, p->m_attribute);
      
      if(s->m_basetype - p->m_expr->m_attribute.m_basetype)
          this->t_error(incompat_assign, p->m_attribute);

  }

  // same as above, only applied to assigning to an array element
  void check_array_assignment( ArrayAssignment * p )
  {
      
      Symbol *s;
      
      s = m_st->lookup(p->m_symname->spelling());
      if(!s)
          this->t_error(var_undef, p->m_attribute);
      
      if(p->m_expr_1->m_attribute.m_basetype != bt_integer || p->m_expr_2->m_attribute.m_basetype != bt_integer)
          this->t_error(incompat_assign, p->m_attribute);

  }
  

  // create a symbol for the function and check there is none already existing
  // make sure all the expressions used as arguments are valid
  // check if the argument list matches the declared one (length and types)
  // make sure the variable assigned to matches the return type of the function
  void check_call(Call *p)
  {
      
      Symbol *s;
      
      s = m_st->lookup(p->m_symname->spelling());
      
      if(!s)
          this->t_error(var_undef, p->m_attribute);
      
      if(s->m_basetype - p->m_expr->m_attribute.m_basetype)
          this->t_error(incompat_assign, p->m_attribute);
      
      Symbol *s2;
      
      s2 = m_st->lookup( p->m_symname_1->spelling());
      
      if(!s2)
          this->t_error(var_undef, p->m_attribute);
      
      if(s->m_return_type != s2->m_basetype )
          this->t_error(incompat_assign, p->m_attribute);
      
      if(s->m_arg_type.size() != p->m_expr_list->size())
          this->t_error(call_narg_mismatch, p->m_attribute);
      
      list<Expr_ptr>::iterator iter;
      iter = p->m_expr_list->begin();
      
      for(int i =0; i < s->m_arg_type.size(); i++){
          if(s->m_arg_type[i] != (*iter)->m_attribute.m_basetype)
              this->t_error(call_args_mismatch, (*iter)->m_attribute);
          iter++;
      }

  }

  // the same as above, but for function calls on an array element
  void check_array_call(ArrayCall *p) 
  {

  }


  //for checking that this expressions type is boolean (used in if/else and for visits)
  void check_pred(Expr* pred)
  {
      if(pred.m_basetype != bt_boolean)
          this->t_error(incompat_assign, pred->m_attribute);

  }

  // a suggested helper method
  Basetype get_ident_type( Ident* p )
  {
      return (p->m_attribute.m_basetype);
  }

  // check that intarray index is integer and that variable is actually intarray
  void check_array_access(ArrayAccess *p)
  {
        
      Symbol *s;
      
      s = m_st->lookup(p->m_symname->spelling());
      if(!s)
          this->t_error(var_undef, p->m_attribute);
      
      if(p->m_attribute.m_basetype != 4)
          this->t_error(incompat_assign, p->m_attribute);
      
      if(p->m_expr->m_attribute.m_basetype != 1)
          this->t_error(incompat_assign, p->m_attribute);

  }

  //for checking boolean operations (and, or ...)
  void checkset_boolexpr(Expr* parent, Expr* child1, Expr* child2 )
  {
      if(child1->m_attribute.m_basetype != bt_boolean || child2->m_attribute.m_basetype != bt_boolean)
          this->t_error(incompat_assign, parent->m_attribute);
      
      
  }

  //for checking arithmetic expressions (plus, times, ...)
  void checkset_arithexpr(Expr* parent, Expr* child1, Expr* child2 )
  {
      if(child1->m_attribute.m_basetype != bt_integer || child2->m_attribute.m_basetype != bt_integer)
          this->t_error(incompat_assign, parent->m_attribute);
      

  }

  //for checking relational (less than , greater than, ...)
  void checkset_relationalexpr(Expr* parent, Expr* child1, Expr* child2 )
  {
      
      if(child1->m_attribute.m_basetype != bt_integer || child2->m_attribute.m_basetype != bt_integer)
          this->t_error(incompat_assign, parent->m_attribute);

  }

  //for checking equality ops (equal, not equal)
  void checkset_equalityexpr(Expr* parent, Expr* child1, Expr* child2 )
  {
      
      if(!(child1->m_attribute.m_basetype == bt_boolean && child2->m_attribute.m_basetype == bt_boolean) ||
          (child1->m_attribute.m_basetype != bt_integer && child2->m_attribute.m_basetype != bt_integer))
          this->t_error(incompat_assign, parent->m_attribute);

  }

  //for checking not
  void checkset_not(Expr* parent, Expr* child)
  {
      if(child->m_attribute.m_basetype != bt_boolean)
          this->t_error(incompat_assign, parent->m_attribute);

  }

  //for checking unary minus
  void checkset_uminus(Expr* parent, Expr* child)
  {
      if(child->m_attribute.m_basetype != bt_integer)
          this->t_error(incompat_assign, parent->m_attribute);

  }

  //for checking the absolute value operation
  void checkset_absolute(Expr* parent, Expr* child)
  {
      if(child->m_attribute.m_basetype != bt_integer)
          this->t_error(incompat_assign, parent->m_attribute);
  }

  // WRITEME
  // Add any other helper function my need

 public:

  // remember: for the entire AST to be visited, you need to call 'p -> visit_children(this);' in each visit method

  Typecheck(FILE* errorfile, SymTab* st) {
	m_errorfile = errorfile;
	m_st = st;
  }

  void visitProgramImpl(ProgramImpl * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      check_for_one_main(p);
      m_st -> dump(stdout);

  }
  void visitFuncImpl(FuncImpl * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      
      p->m_type->accept(this);
      add_func_symbol(p);
      
      m_st->open_scope();
      p -> visit_children(this);
      m_st->close_scope();
      
      check_return_type(p);

  }
  void visitNested_blockImpl(Nested_blockImpl * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);

  }
  void visitFunction_blockImpl(Function_blockImpl * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      check_return_location(p);

  } 
  void visitDeclImpl(DeclImpl * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      add_decl_symbol(p);

  }
  void visitAssignment(Assignment * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      check_assignment(p);

  }
  void visitArrayAssignment(ArrayAssignment * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      check_array_assignment(p);

  }
  void visitCall(Call * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      check_call(p);
      p -> visit_children(this);

  }
  void visitArrayCall(ArrayCall * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      check_array_call(p); 

  }
  void visitReturn(Return * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);

  }
  void visitIfNoElse(IfNoElse * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      check_if_pred(p->m_expr);

  }
  void visitIfWithElse(IfWithElse * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      check_if_pred(p->m_expr);

  }
  void visitForLoop(ForLoop * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);

      if(!is_assignment(p->m_stat_1))
          this->t_error(for_assign_err, p->m_attribute);
      
      if(!is_assignment(p->m_stat_2))
          this->t_error(for_assign_err, p->m_attribute);
      
      check_for_pred(p->m_expr);
      
  }
  void visitNone(None * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);

  }
  void visitTInteger(TInteger * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_integer;

  }
  void visitTBoolean(TBoolean * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_boolean;

  }
  void visitTIntArray(TIntArray * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_intarray;

  }
  void visitAnd(And * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      checkset_boolexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitDiv(Div * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_integer;
      checkset_arithexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitCompare(Compare * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_boolean;
      checkset_equalityexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitGt(Gt * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_boolean;
      checkset_relationalexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitGteq(Gteq * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_boolean;
      checkset_relationalexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitLt(Lt * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_boolean;
      checkset_relationalexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitLteq(Lteq * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_boolean;
      checkset_relationalexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitMinus(Minus * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_integer;
      checkset_arithexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitNoteq(Noteq * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_boolean;
      checkset_equalityexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitOr(Or * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_boolean;
      checkset_boolexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitPlus(Plus * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_integer;
      checkset_arithexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitTimes(Times * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_integer;
      checkset_arithexpr(p,p->m_expr_1, p->m_expr_2);

  }
  void visitNot(Not * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      checkset_not(p, p->m_expr);
      p -> m_attribute.m_basetype = bt_boolean;

  }
  void visitUminus(Uminus * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      checkset_uminus(p, p->m_expr);
      p -> m_attribute.m_basetype = bt_integer;

  }
  void visitMagnitude(Magnitude * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      checkset_absolute(p, p->m_expr);
      p -> m_attribute.m_basetype = bt_integer;

  }
  void visitIdent(Ident * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      Symbol *newSym;
      newSym = m_st->lookup( p->m_symname->spelling());
      if(!newSym)
          this->t_error(var_undef, p->m_attribute);
      
      p->m_attribute.m_basetype = newSym->m_basetype;

  }
  void visitArrayAccess(ArrayAccess * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);

  }
  void visitIntLit(IntLit * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_integer;

  }
  void visitBoolLit(BoolLit * p)
  {
      p -> m_attribute.m_scope = m_st->get_scope();
      p -> visit_children(this);
      
      p -> m_attribute.m_basetype = bt_boolean;

  }

  //special cases
  void visitSymName(SymName * p) {}
  void visitPrimitive(Primitive * p) {}


};

void dopass_typecheck(Program_ptr ast, SymTab* st)
{
    Typecheck* typecheck = new Typecheck(stderr, st); //create the visitor
    ast->accept(typecheck); //walk the tree with the visitor above
	delete typecheck;
}





