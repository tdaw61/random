import java.io._
import java.util._
import scala.io._
import cs162.IMP.syntax._
import scala.collection.mutable.{Map => MMap}

//---------- INTERPRETER ENTRY POINT ----------

object IMP {
  import cs162.IMP.interpreter._
  import SemanticHelpers._
  import Interp._

  def main(args:Array[String]) {
    val ast = ParseL.getAST(Source.fromFile(args(0)).mkString)
    println(ast);
	//var s: Stack[Any] = new Stack()
    if (args.length == 1)
      eval(inject(ast))
    else if (args.length == 2 && args(1) == "--printast")
      PrettyPrint.writeDot(ast, "ast.dot")
    else
      println("usage: scala IMP <program file> [--printast]")
  }
}

package cs162.IMP.interpreter {

//---------- SEMANTIC DOMAINS ----------

// abstract machine configuration. note that the configuration does
// not include a Store as specified by the formal semantics; as
// explained below this is because we take advantage of Scala's impure
// nature in order to have a global, mutable store instead of
// threading it through the computation
case class Config(t:Term)

// store: Variable -> Value
//
// we're taking advantage of Scala's impure nature to have a global,
// mutable store instead of threading it through the computation,
// which is why we use a mutable MMap instead of an immutable Map
case class Store(store:MMap[Var, Value] = MMap()) {
  def apply(x:Var): Value = store get x match {
    case Some(v) => v
    case None => throw undefined("non-existent address")
  }
}

// language values
sealed abstract class Value
case class NumV(n:BigInt) extends Value { 
  override def toString = n.toString 
}
case class BoolV(b:Boolean) extends Value { 
  override def toString = b.toString 
}
case class StringV(str:String) extends Value { 
  override def toString = str
}
case class UnitV() extends Value { 
  override def toString = "unit" 
}

// companion objects for some of the above classes to provide implicit
// conversions
object Store { 
  implicit def store2map(s:Store): MMap[Var, Value] = s.store
  implicit def map2store(m:MMap[Var, Value]): Store = Store(m)
}

// exception to be thrown when a program exhibits undefined behavior
case class undefined(msg:String) extends Exception(msg)

//---------- SEMANTIC HELPER FUNCTIONS ----------

// Note that inject doesn't produce a Store as specified in the formal
// semantics. As described below, this is because we take advantage of
// Scala's impure nature in order to have a global, mutable store
// instead of threading it through the computation.

object SemanticHelpers {
  import Interp._

  // lift program to initial configuration
  def inject(prog:Program): Config = Config(prog.t)
}

//---------- INTERPRETER ----------

// the formal semantics is necessarily completely pure, meaning there
// is no mutable state. this implies that we need to thread the store
// through the computation as part of the abstract machine
// configuration, taking in one store and passing on a (potentially
// different) new store. The intent of the semantics is that the store
// behaves identically to having a single global, mutable store.
//
// our interpreter has to behave exactly the same as the formal
// semantics, but it doesn't have to be implemented exactly the same
// way (as long as it's guaranteed that the behavior is the
// same). since Scala supports mutable state, and since the semantics
// *acts* as if there's a single global, mutable store, our
// interpreter can simply use a global, mutable store instead of
// making it part of the machine configuration and threading it
// through the computation.

object Interp {
  import SemanticHelpers._

  // the global Store
  val gStore = Store()

  // the evaluation function [[.]] \in Config -> Value
  def eval(config:Config): Value = {
    
    // so we don't have to keep casting terms to Config, we'll define
    // an inner function that takes terms
    def evalTo(t:Term): Value = t match {
      case Seq(t1, t2) => {
	evalTo(t1)
	evalTo(t2)
      }
      case Assign(x, e) => gStore get x match {
	case Some(_) => { gStore(x) = evalTo(e); UnitV() }
	case _ => throw undefined("assigning to nonexistent variable")
      }
      case w @ While(e, t) => evalTo(e) match {
	case BoolV(true) => {
	  evalTo(t)
	  evalTo(w)
	}
	case BoolV(false) => UnitV()
	case _ => throw undefined("while guard not a bool")
      }
      case Out(e) => {
	println(evalTo(e))
	UnitV()
      }
      case Num(n) => NumV(n)
      case Bool(b) => BoolV(b)
      case Str(str) => StringV(str)
      case NotUnit() => UnitV()
      case x:Var => gStore(x)
      case Not(e) => evalTo(e) match {
	case BoolV(b) => BoolV(!b)
	case _ => throw undefined("negated expression not a bool")
      }
      case BinOp(bop, e1, e2) => bop match {
	case Equal => {
	  val v1 = evalTo(e1)
	  val v2 = evalTo(e2)
	  BoolV(v1 == v2)
	}
	case _ => (evalTo(e1), evalTo(e2)) match {
	  case (BoolV(b1), BoolV(b2)) => bop match {
	    case And => BoolV(b1 && b2)
	    case Or  => BoolV(b1 || b2)
	    case _   => throw undefined("illegal operation on bools")
	  }
	  case (NumV(n1), NumV(n2)) => bop match {
	    case Add => NumV(n1 + n2)
            case Sub => NumV(n1 - n2)
	    case Mul => NumV(n1 * n2)
	    case Div if n2 != 0 => NumV(n1 / n2)
	    case Lte => BoolV(n1 <= n2)
	    case _   => throw undefined("illegal operation on nums")
	  }
	  case (StringV(s1), StringV(s2)) => bop match {
	    case Ad => StringV(s1 + s2)
	    case Lte => BoolV(s1 <= s2)
	    case _   => throw undefined("illegal operation on strings")
	  }
	  case _ => throw undefined("illegal binary operation")
	}
      }
      case If(e, t1, t2) => evalTo(e) match {
	case BoolV(true)  => evalTo(t1)
	case BoolV(false) => evalTo(t2)
	case _ => throw undefined("if guard not a bool")
      }
      case In(typ) => typ match {
	case NumT => NumV(BigInt(scala.Console.readInt()))
	case StrT => StringV(scala.Console.readLine())
      }
      case Block(vbs, t) => {
	val xvs = for ( VarBind(x, e) <- vbs ) gStore(x) = evalTo(e)
	evalTo(t)
      }
    }

    evalTo(config.t)
  }
}

} // end package cs162.IMP.interpreter
