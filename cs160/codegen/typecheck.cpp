#include <iostream>
#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
#include "assert.h"


// for loop for iterating over containers (such as lists)
// creates an iterator of the appropriate type and does
// a for loop from begin to end
#define forall(iterator,listptr) \
	for(iterator = listptr->begin(); iterator != listptr->end(); iterator++) \

// the default attribute propagation rule
// sets the node's scope to the current scope (don't worry about this)
// and then visits the children of the node
#define set_scope_and_descend_into_children(X) \
	(X)->m_attribute.m_scope = m_st->get_scope(); \
	(X)->visit_children(this); \

#include <typeinfo>
#include <stdio.h>

/***********

  Typechecking is already partially complete, you only need to fill in the blanks.

  You should only add code where WRITEME labels are inserted. You can just search for WRITEME to find all the
  instances. Methods that have no WRITEME are already complete. You them as a template on how things should be
  done.

  Here's the list of what is already implemented:

x   * There must be a root level function called Main.
x   * Main should have no arguments.
x   * No two same identifiers can be declared twice in the same scope.
	The argument list of a function is treated as declared variables for this purpose.
x   * For any function call, its actual parameters must match the formal parameters of the declaration
	(in number and type)
x   * The return statement's expression must match the type declared by the function
	(Note: this check will always fail before you implement expression typechecking)

  Here's what you need to check:

x   * No variable name may be used before it is declared in the current or lower scope. Throw sym_name_undef
x   * No function call may be made before it is declared in the current or lower scope. Throw sym_name_undef
x   * No array may be indexed before it is declared in the current or lower scope. Throw sym_name_undef
x   * The types of left-hand side and right-hand side of an assign statement must match: either both be 
        of type boolean, or of type integer. This goes for all assignment statements, including calls.
	Remember that array elements are considered integers for typechecking purposes.
	Make sure you perform this check only after the left and right right hand side are individually correct.
	Throw incompat_assign
x   * The type of the premise of an if, if/else and while statements are all boolean.
	Throw if_pred_error or while_pred_error
x   * Intarrays can only be indexed by integer expressions
	Throw array_index_error
x   * The operands of an expression must match the operator. The following list enumerate the operator types:
	 + For any Arithmetic Operator node, both its left and right child must be expressions of integer type.
		return type will be integer
	 + For any Conditional Operator node, both its left and right child must be expressions of boolean type.
		return type is boolean
	 + For any Equality Operator node, its left and right child must have the same type.
	 	Intarrays are not permitted. Return type is boolean
	 + For any Relational Operator node, the left and right child must both be integers.
		return type is boolean
	 + For Unary Operator not, child and return are both bool
	 + For Unary Operator minus, child and return are both integer
	 + For Absolute values, child can be only be of type integer
      For all of the above, throw expr_type_err if the expected type of a subexpression does not match
	 + When accessing an array, the symbol under the SymName has to:
	 	1) exist (throw a sym_name_undef otherwise), and
		2) be of type intarray (throw a sym_type_mismatch otherwise)
		return type is integer
	 + For Idents, the symbol under the SymName has to:
	 	1) exist (throw a sym_name_undef otherwise), and
		2) be of type integer OR boolean (throw a sym_type_mismatch otherwise)
		return type is the the same as the variable's

  Be careful when throwing errors - always throw an error of the right type, using the m_attribute of the node you're visiting when performing the check. Sometimes you'll see errors being thrown at strange line numbers; that is okay, don't let that bother you as long as you follow the above principle.

*****/


class Typecheck : public Visitor {
 private:
  FILE* m_errorfile;
  SymTab* m_st;

  const char * bt_to_string(Basetype bt) {
	switch (bt) {
		case bt_undef: return "bt_undef";
		case bt_integer: return "bt_integer";
		case bt_boolean: return "bt_boolean";
		case bt_function: return "bt_function";
		case bt_intarray: return "bt_intarray";
		default:
			return "unknown";
	}
  }

  // the set of recognized errors
  enum errortype 
  {
	no_main,
	main_args_err,
	dup_ident_name,
	sym_name_undef,
	sym_type_mismatch,
	call_narg_mismatch,
	call_args_mismatch,
	ret_type_mismatch,

	incompat_assign,
	if_pred_err,
	while_pred_err,
	
	expr_type_err,
	array_index_error
  };

  // Throw errors using this method
  void t_error( errortype e, Attribute a ) 
  {
	fprintf(m_errorfile,"on line number %d, ", a.lineno );

	switch( e ) {
	case no_main: fprintf(m_errorfile,"error: no main\n"); break;
	case main_args_err: fprintf(m_errorfile,"error: Main function has arguments\n"); break;
	case dup_ident_name: fprintf(m_errorfile,"error: duplicate identifier name in same scope\n"); break;
	case sym_name_undef: fprintf(m_errorfile,"error: symbol by name undefined\n"); break;
	case sym_type_mismatch: fprintf(m_errorfile,"error: symbol by name defined, but of unexpected type\n"); break;
	case call_narg_mismatch: fprintf(m_errorfile,"error: function call has different number of args than the declaration\n"); break;
	case call_args_mismatch: fprintf(m_errorfile,"error: type mismatch in function call args\n"); break;
	case ret_type_mismatch: fprintf(m_errorfile, "error: type mismatch in return statement\n"); break;

	case incompat_assign: fprintf(m_errorfile,"error: types of right and left hand side do not match in assignment\n"); break;
	case if_pred_err: fprintf(m_errorfile,"error: predicate of if statement is not boolean\n"); break;
	case while_pred_err: fprintf(m_errorfile,"error: predicate of while statement is not boolean\n"); break;

	case expr_type_err: fprintf(m_errorfile,"error: incompatible types used in expression\n"); break;
	case array_index_error: fprintf(m_errorfile, "error: intarray index not integer\n"); break;
	
	default: fprintf(m_errorfile,"error: no good reason\n"); break;
	}
	exit(1);
  }

  // add symbol table information for all the symnames under the declaration
  void add_decl_symbol(Decl *p)
  {
	list<SymName_ptr>::iterator symname_iter;
	char* name;
	
	Basetype type = p -> m_type -> m_attribute.m_basetype;

	forall(symname_iter, p -> m_symname_list) {
		Symbol *s = new Symbol();
		s -> m_basetype = type;
		name = strdup((*symname_iter) -> spelling());
		if (! m_st -> insert(name, s))
			this -> t_error(dup_ident_name,  p -> m_attribute);
	}
  }

  // This method is a useful utility. You may implement and use it or choose not to.
  //
  // It is used to lookup a symbol by name, assuming that it has to be of certain type.
  //
  // accepted_type is a binary mask built from Basetype, defined in "attribute.hpp". Any bit set to 1
  // will allow that type. So, just calling this with (bt_boolean | bt_integer) will accept either type,
  // using bt_function should only accept a function etc.
  //
  // The usefulness of this method is in that if should throw a sym_name_undef if a symbol
  // is not found, or throw a sym_type_mismatch if the type is wrong.
  //
  // It returns the actual type of the symbol.
  Basetype get_ident_type(const char* name, char accepted_types, Attribute m_attribute)
  {
	  // WRITEME
	  return bt_undef;
  }

  /*HELPER FUNCTIONS*/
	//for checking boolean operations (and, or ...)
	void checkset_boolexpr(Expr* parent, Expr* child1, Expr* child2 )
	{
		parent->m_attribute.m_basetype=bt_boolean;
		if (child1->m_attribute.m_basetype!=bt_boolean || child2->m_attribute.m_basetype!=bt_boolean)
			this -> t_error(expr_type_err, child2->m_attribute);
	}

	//for checking arithmetic expressions (plus, times, ...)
	void checkset_arithexpr(Expr* parent, Expr* child1, Expr* child2 )
	{
		parent->m_attribute.m_basetype=bt_integer;
		if (child1->m_attribute.m_basetype!=bt_integer || child2->m_attribute.m_basetype!=bt_integer)
			this -> t_error(expr_type_err, child2->m_attribute);
	}

	//for checking relational (less than , greater than, ...)
	void checkset_relationalexpr(Expr* parent, Expr* child1, Expr* child2 )
	{
		parent->m_attribute.m_basetype=bt_boolean;
		if (child1->m_attribute.m_basetype!=bt_integer || child2->m_attribute.m_basetype!=bt_integer)
			this -> t_error(expr_type_err, child2->m_attribute);
	}

	//for checking equality ops (equal, not equal)
	void checkset_equalityexpr(Expr* parent, Expr* child1, Expr* child2 )
	{
		parent->m_attribute.m_basetype=bt_boolean;
		if (child1->m_attribute.m_basetype!=child2->m_attribute.m_basetype)
			this -> t_error(expr_type_err, child2->m_attribute);
	}

	//for checking not
	void checkset_not(Expr* parent, Expr* child)
	{
		parent->m_attribute.m_basetype=bt_boolean;
		if (child->m_attribute.m_basetype!=bt_boolean)
			this -> t_error(expr_type_err, child->m_attribute);
	}

	//for checking unary minus
	void checkset_uminus(Expr* parent, Expr* child)
	{
		parent->m_attribute.m_basetype=bt_integer;
		if (child->m_attribute.m_basetype!=bt_integer)
			this -> t_error(expr_type_err, child->m_attribute);
	}

	//for checking the absolute value operation
	void checkset_absolute(Expr* parent, Expr* child)
	{
		parent->m_attribute.m_basetype=bt_integer;
		if (child->m_attribute.m_basetype!=bt_integer)
			this -> t_error(expr_type_err, child->m_attribute);
	}


 public:

  Typecheck(FILE* errorfile, SymTab* st) {
	m_errorfile = errorfile;
	m_st = st;
  }

  void visitProgram(Program * p)
  {
	set_scope_and_descend_into_children(p);

	// ASSERT There's a single main
	Symbol *s = m_st -> lookup("Main");
	if(s == NULL) 
		this -> t_error(no_main, p -> m_attribute);

	// ASSERT There are no args for it
	if(s -> m_arg_type.size() > 0)
		this -> t_error(main_args_err,  p -> m_attribute);
  }

  void visitFunc(Func * p)
  {	
	p->m_attribute.m_scope = m_st->get_scope();
	
	// create a function symbol, check if it exists, store it in the symtab
	char *name = strdup(p -> m_symname -> spelling());

	Symbol *s = new Symbol();
	s -> m_basetype = bt_function;
	m_st -> open_scope();

	visit(p->m_type);
	visit(p->m_symname);
	visit_list(p->m_decl_list);
	
	// for each argument group, for each arg name, add the group's type to the arg list
	list<Decl_ptr>::iterator decl_iter;
	list<SymName_ptr>::iterator sym_iter;
	forall(decl_iter, p -> m_decl_list) {
		Decl *dip = *decl_iter;
		Basetype bt = dip -> m_type -> m_attribute.m_basetype;
		forall(sym_iter, dip -> m_symname_list) { 
			s -> m_arg_type.push_back(bt);
		}
	}

	// read in return type
	s -> m_return_type = p -> m_type -> m_attribute.m_basetype;

	// ASSERT no symbol by this name exists, and add it to the symtab
	if (! m_st -> insert_in_parent_scope(name, s))
		this -> t_error(dup_ident_name, p -> m_attribute);

	// descend into the implementation
	visit(p->m_function_block);
	m_st -> close_scope();

	// ASSERT the return statement returns the correct type
	if (p -> m_type -> m_attribute.m_basetype != p -> m_function_block -> m_return -> m_attribute.m_basetype)
		this -> t_error (ret_type_mismatch, p -> m_attribute);
  }

  void visitNested_block(Nested_block * p)
  {
	set_scope_and_descend_into_children(p);
  }

  void visitFunction_block(Function_block * p)
  {
	set_scope_and_descend_into_children(p);
  }

  void visitDecl(Decl * p)
  {
	set_scope_and_descend_into_children(p);
	add_decl_symbol(p);
  }

  void visitAssignment(Assignment * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	// ASSERT left hand side var exists, and is an int/boolean
	// ASSERT right hand side matches that type

	char* name =  strdup((p) -> m_symname -> spelling());
	if (!m_st->exist(name))
		this -> t_error(sym_name_undef, p->m_attribute);
	if (m_st->lookup(name)->m_basetype!=p->m_expr->m_attribute.m_basetype)
		this -> t_error(incompat_assign, p->m_attribute);
  }

  void visitArrayAssignment(ArrayAssignment * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME	
	// ASSERT array exists and is an array
	// ASSERT index is an integer
	// ASSERT right hand side is an integer

	char* name =  strdup((p) -> m_symname -> spelling());
	if (!m_st->exist(name))
		this -> t_error(sym_name_undef, p->m_attribute);
	//if (p->m_attribute.m_basetype!= bt_intarray)
	if (m_st->lookup(name)->m_basetype!=bt_intarray)
		this -> t_error(sym_type_mismatch, p->m_attribute);
	if (p->m_expr_1->m_attribute.m_basetype!=bt_integer)
		this -> t_error(array_index_error, p->m_attribute);
	if (p->m_expr_2->m_attribute.m_basetype!=bt_integer)
		{
			cout << p->m_expr_2->m_attribute.m_basetype ;
			this -> t_error(incompat_assign, p->m_attribute);
		}
	p->m_attribute.m_basetype = bt_integer;
       //p.set_size(p->m_expr_1->m_attribute.m_basetype;

  }

  // This method will throw an error unless:
  //   The SymName provided has an existing Symbol of type bt_function
  //   The expressions in the expr list and match the argument list of that function in number and type
  //   The return type is as expected.
  //
  // Use this method to check calls
  void check_call(Stat* t, SymName* symname, list<Expr_ptr>* exprList, Basetype return_type)
  {
	list<Expr_ptr>::iterator exprIterator;
	Symbol* f = m_st -> lookup(symname -> spelling());

	// ASSERT f is a function Symbol
	if (f == NULL || f -> m_basetype != bt_function)
		this -> t_error(sym_type_mismatch, t -> m_attribute);
	
	// ASSERT args match in count and types
	int count = 0;
	forall(exprIterator, exprList)
	{
		if (count >= f -> m_arg_type.size())
			this -> t_error(call_narg_mismatch, t -> m_attribute);
		if ((*exprIterator) -> m_attribute.m_basetype != f -> m_arg_type[count++])
			this -> t_error(call_args_mismatch, t -> m_attribute);
	}

	if (count != f -> m_arg_type.size())
		this -> t_error(call_narg_mismatch, t -> m_attribute);

	// ASSERT the return type of the function matches the variable's
	if (f -> m_return_type != return_type)
		this -> t_error(incompat_assign, t -> m_attribute);
  }

  void visitCall(Call * p)
  {
	set_scope_and_descend_into_children(p);

	// WRITEME
	// ASSERT left hand side var exists, is a variable, and get type

	char* name =  strdup((p) -> m_symname_1 -> spelling());
	if (!m_st->exist(name))
		this -> t_error(sym_name_undef, p->m_attribute);
	//Basetype assigned_to_type = p->m_attribute.m_basetype;
	//Basetype assigned_to_type = p->m_symname_1->m_attribute.m_basetype;
	Basetype assigned_to_type = m_st->lookup(name)->m_basetype;

	// ASSERT the parameters match, and the function return type matches
	// assuming that you have the type of the left hand side variable
	// in "assigned_to_type", you can just uncomment the following line

	check_call(p, p -> m_symname_2, p -> m_expr_list, assigned_to_type);
  }

  void visitArrayCall(ArrayCall * p)
  {
	set_scope_and_descend_into_children(p);

	// WRITEME
	// ASSERT the variable is an array
	char* name =  strdup((p) -> m_symname_1 -> spelling());
	if (!m_st->exist(name))
		this -> t_error(sym_name_undef, p->m_attribute);

	// WRITEME
	// ASSERT the index parameter is an integer

	if (p->m_expr_1->m_attribute.m_basetype!=bt_integer)
		this -> t_error(array_index_error, p->m_attribute);

	// ASSERT the call is ok and returns an integer
	check_call(p, p -> m_symname_2, p -> m_expr_list_2, bt_integer);
  }

  void visitReturn(Return * p)
  {
	set_scope_and_descend_into_children(p);
	p -> m_attribute.m_basetype = p -> m_expr -> m_attribute.m_basetype;
  }

  void visitIfNoElse(IfNoElse * p)
  {
	set_scope_and_descend_into_children(p);

	// WRITEME
	// ASSERT Expression of type boolean
	if (p->m_expr->m_attribute.m_basetype!=bt_boolean)
	 this -> t_error(if_pred_err, p->m_attribute);

  }

  void visitIfWithElse(IfWithElse * p)
  {
	set_scope_and_descend_into_children(p);

	// WRITEME
	// ASSERT Expression of type boolean
	if (p->m_expr->m_attribute.m_basetype!=bt_boolean)
		this -> t_error(if_pred_err, p->m_attribute);

  }

  void visitWhileLoop(WhileLoop * p)
  {
	set_scope_and_descend_into_children(p);

	// WRITEME
	// ASSERT Expression of type boolean
	if (p->m_expr->m_attribute.m_basetype!=bt_boolean)
		this -> t_error(while_pred_err, p->m_attribute);

  }

  void visitTInteger(TInteger * p)
  {
	set_scope_and_descend_into_children(p);
	// this corresponds to the terminal "integer", storing the type is helpful
	p -> m_attribute.m_basetype = bt_integer;
  }

  void visitTBoolean(TBoolean * p)
  {
	set_scope_and_descend_into_children(p);
	// this corresponds to the terminal "boolean", storing the type is helpful
	p -> m_attribute.m_basetype = bt_boolean;
  }

  void visitTIntArray(TIntArray * p)
  {
	set_scope_and_descend_into_children(p);
	// this corresponds to the terminal "intarray", storing the type is helpful
	p -> m_attribute.m_basetype = bt_intarray;
  }

  void visitAnd(And * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
		checkset_boolexpr(p, p->m_expr_1, p->m_expr_2);
  }

  void visitDiv(Div * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
		checkset_arithexpr(p, p->m_expr_1, p->m_expr_2);

  }

  void visitCompare(Compare * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_equalityexpr(p, p->m_expr_1, p->m_expr_2);

  }

  void visitGt(Gt * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_relationalexpr(p, p->m_expr_1, p->m_expr_2);

  }

  void visitGteq(Gteq * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_relationalexpr(p, p->m_expr_1, p->m_expr_2);

  }

  void visitLt(Lt * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_relationalexpr(p, p->m_expr_1, p->m_expr_2);

  }

  void visitLteq(Lteq * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_relationalexpr(p, p->m_expr_1, p->m_expr_2);

  }

  void visitMinus(Minus * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_arithexpr(p, p->m_expr_1, p->m_expr_2);

  }

  void visitNoteq(Noteq * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_equalityexpr(p, p->m_expr_1, p->m_expr_2);
  }

  void visitOr(Or * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_boolexpr(p, p->m_expr_1, p->m_expr_2);
  }

  void visitPlus(Plus * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_arithexpr(p, p->m_expr_1, p->m_expr_2);
  }

  void visitTimes(Times * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_arithexpr(p, p->m_expr_1, p->m_expr_2);
  }

  void visitNot(Not * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_not(p, p->m_expr);
  }

  void visitUminus(Uminus * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	checkset_uminus(p, p->m_expr);
  }

  void visitMagnitude(Magnitude * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
		checkset_absolute(p, p->m_expr);

  }

  void visitIdent(Ident * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	// ASSERT symbol under varname exists and is either an integer or a boolean
	if (!m_st->exist(strdup(p->m_symname->spelling())))
		this -> t_error(sym_name_undef, p-> m_attribute);				
	p->m_attribute.m_basetype = m_st->lookup(strdup(p->m_symname->spelling()))->m_basetype;
	if (p->m_attribute.m_basetype!=bt_integer && p->m_attribute.m_basetype!=bt_boolean)
		this -> t_error(sym_name_undef, p-> m_attribute);	
  }

  void visitArrayAccess(ArrayAccess * p)
  {
	set_scope_and_descend_into_children(p);
	// WRITEME
	// ASSERT the array symbol exists and is indeed an array
	char* name =  strdup((p) -> m_symname -> spelling());
	if (!m_st->exist(name))
		this -> t_error(sym_name_undef, p->m_attribute);
	if (m_st->lookup(name)->m_basetype!=bt_intarray)
		this -> t_error(sym_name_undef,p->m_attribute);
	if (p->m_expr->m_attribute.m_basetype!=bt_integer)
		this -> t_error(array_index_error, p->m_attribute);
	p -> m_attribute.m_basetype = bt_integer;

  }

  void visitIntLit(IntLit * p)
  {
	set_scope_and_descend_into_children(p);
	p -> m_attribute.m_basetype = bt_integer;
  }

  void visitBoolLit(BoolLit * p)
  {
	set_scope_and_descend_into_children(p);
	p -> m_attribute.m_basetype = bt_boolean;
  }

  void visitSymName(SymName * p) {}
  void visitPrimitive(Primitive * p) {}

};




