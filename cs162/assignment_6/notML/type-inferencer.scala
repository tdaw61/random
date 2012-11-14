import java.io._
import scala.io._
import cs162.notML.syntax._

//---------- TYPE INFERENCER ENTRY POINT ----------

object notML {
        import cs162.notML.typeInferencer._
        import SemanticHelpers._
        import Infer._

        def main(args:Array[String]) {
                val ast = ParseL.getAST(Source.fromFile(args(0)).mkString)

                if (args.length == 1 || args(1) != "--printast")
                        println(find(eval(inject(ast))))

                        else PrettyPrint.writeDot(ast, "ast.dot")
        }
}

package cs162.notML.typeInferencer {

        //---------- TYPE INFERENCER SEMANTIC DOMAINS ----------

        // abstract machine configuration
case class Config(t:Term, env:Env)

// environment: Var -> Type
case class Env(env:Map[Var, Type] = Map()) {
        def apply(x:Var): Type = env get x match {
        case Some(typ) => typ
        case None => throw illTyped("free variable")
        }
        def +(tup:Tuple2[Var, Type]): Env = Env(env + tup)
}

// environment companion object
object Env {
        implicit def env2map(e:Env): Map[Var, Type] = e.env
        implicit def map2env(m:Map[Var, Type]): Env = Env(m)
}

// exception to be thrown when a program is ill-typed
case class illTyped(msg:String) extends Exception(msg)

//---------- SEMANTIC HELPER FUNCTIONS ----------

object SemanticHelpers {
        // lift program to initial configuration
        def inject(prog:Program): Config = { Config(prog.t, Env()) }

        // union two types. unlike the semantics this actually performs the
        // type unification using the union-find data structure; hence it
        // returns Unit instead of Bool and throws an illTyped exception if
        // the unification fails
        //
        // NOTE: the find() function should use path compression, but this
        // union() function should NOT use union-by-rank; when unioning a
        // type variable T with something else, T always sets its parent to
        // that other type
        //
        def union(type1:Type, type2:Type): Boolean = // FILL ME IN
        {
                        if (type1.equals(type2))
                        {
                                return true;
                        }
                        if (type1.isInstanceOf[TVar])
                        {
                                type1.asInstanceOf[TVar].a match
                                {
                                case None => //Ta
                                {
                                        val x=varsIn(type2);
                                        if (x.contains(type1.asInstanceOf[TVar]))
                                        {
                                                find(type1).asInstanceOf[TVar].parent=Option(find(type2));
                                                return true;
                                        }
                                }
                                case Some(AL) =>
                                {
                                        if (type2.isInstanceOf[NumT]||type2.isInstanceOf[StrT]||type2.isInstanceOf[TVar])
                                                return false;
                                }
                                }
                        }
                        if (type2.isInstanceOf[TVar])
                        {
                                type2.asInstanceOf[TVar].a match
                                {
                                case None => //Ta
                                {
                                        val x=varsIn(type1);
                                        if (x.contains(type2.asInstanceOf[TVar]))
                                        {
                                                find(type1).asInstanceOf[TVar].parent=Option(find(type2));
                                                return true;
                                        }
                                }
                                case Some(AL) =>
                                {
                                        if (type1.isInstanceOf[NumT]||type1.isInstanceOf[StrT]||type1.isInstanceOf[TVar])
                                                return false;
                                }
                                }
                        }
                        if (type1.isInstanceOf[ListT]&&type2.isInstanceOf[ListT])
                        {
                                if( union(type1.asInstanceOf[ListT].typ, type2.asInstanceOf[ListT].typ))
                                {
                                        find(type1).asInstanceOf[TVar].parent=Option(find(type2));
                                        return true;
                                }
                                else
                                        return false;
                        }
                        if (type1.isInstanceOf[FunT]&&type2.isInstanceOf[FunT])
                        {
                                var a = type1.asInstanceOf[FunT];
                                var b = type2.asInstanceOf[FunT];
                                if (union (a.typ, b.typ))
                                {
                                        find(type1).asInstanceOf[TVar].parent=Option(find(type2));
                                        return true;
                                }
                                for (i <- 0 to a.typs.length)
                                {
                                        if( union (a.typs(i), b.typs(i)))
                                        {
                                                find(type1).asInstanceOf[TVar].parent=Option(find(type2));
                                                return true;
                                        }
                                }
                                return false;
                        }
                        return false;
        }
        // return a type's set representative; this function should use path
        // compression to optimize performance
        def find(typ:Type): Type = // FILL ME IN
        {
                        val x = typ.asInstanceOf[TVar];
                        x.parent match {
                        case None => x.parent=Option(x);
                        case Some(p) =>
                        {
                                if (p == x) return x;
                                else
                                {
                                        x.parent = Option(find(p.asInstanceOf[Type]));
                                        return x.parent.get;
                                }
                        }
                        }
                        x
        }

        // return all the type variables in a type
        def varsIn(typ:Type): Set[TVar] = // FILL ME IN
        {
                        if (typ.isInstanceOf[NumT]||typ.isInstanceOf[StrT]||typ.isInstanceOf[BoolT]||typ.isInstanceOf[UnitT])
                                return Set[TVar]();
                        if (typ.isInstanceOf[TVar])
                                return Set[TVar]()+(typ.asInstanceOf[TVar]);
                        if (typ.isInstanceOf[ListT])
                                return (varsIn(typ.asInstanceOf[ListT].typ));
                        if (typ.isInstanceOf[FunT])
                        {
                                var s = Set[TVar]();
                                s= s + (varsIn(typ.asInstanceOf[FunT].typ)).asInstanceOf[TVar];
                                for (i <- 0 to typ.asInstanceOf[FunT].typs.length)
                                {
                                        s = s + varsIn(typ.asInstanceOf[FunT].typs(i)).asInstanceOf[TVar];
                                }
                                return s;
                        }
                        return Set[TVar]();
        }       
}

//---------- TYPE INFERENCER ----------

object Infer {
        import SemanticHelpers._

        def eval(config:Config): Type = {
                        val env = config.env

                        // since we'll be making lots of recursive calls where the
                        // environment doesn't change, we'll define an inner function that
                        // will leave env as a free variable
                        def evalTo(t:Term): Type = t match {
                        case Seq(t1, t2) => {
                                evalTo(t1)
                                evalTo(t2)
                        }
                        case Assign(x, e) => {
                                val t1 = evalTo(x);
                                val t2 = evalTo(e);
                                if (!t1.equals(t2))
                                        throw illTyped("expression and variable type dont match");
                                union (env(x), t2);
                                UnitT()
                        }
                        case w @ While(e, t) =>  {
                                val t1 = (evalTo(e));
                                if (!t1.equals(BoolT()))
                                        throw illTyped("guard is not boolean");
                                evalTo(t); //verify if well typed
                                union (t1, BoolT());
                                UnitT();
                        }
                        case Out(e) => {
                                evalTo(e); //verify if well typed       
                                UnitT()
                        }
                        case HAssign(e1, e2) =>{
                                val t1 = evalTo(e1);
                                val t2 = evalTo(e2);
                                if (!e1.isInstanceOf[ListT])
                                        throw illTyped("assignment is not to list");
                                union (t1, ListT(TVar()));
                                if (!e1.asInstanceOf[ListT].typ.equals(t2))
                                        throw illTyped("list type and val dont match");
                                union (t2, TVar());
                                UnitT();
                        }
                        case TAssign(e1, e2) =>{
                                val t1 = evalTo(e1);
                                val t2 = evalTo(e2);
                                if (!t1.isInstanceOf[ListT]|| !t2.isInstanceOf[ListT])
                                {
                                        throw illTyped("not a list");
                                }
                                union (t1, ListT(TVar()));
                                if (!t1.asInstanceOf[ListT].typ.equals(t2.asInstanceOf[ListT].typ))
                                        throw illTyped("not the same type");
                                union (t2, ListT(TVar()));
                                UnitT();
                        }

                        case Num(n) => NumT()
                        case Bool(b) => BoolT()
                        case Str(str) => StrT()
                        case NotUnit() => UnitT()
                        case x:Var => env(x)
                        case Not(e) =>
                        {
                                val t = evalTo(e);
                                if (!t.equals(BoolT()))
                                        throw illTyped("not a boolean");
                                union (t, BoolT());
                                BoolT();
                        }
                        case BinOp(bop, e1, e2) => bop match {
                        case Equal => {
                                val t1 = evalTo(e1);
                                val t2 = evalTo(e2);
                                if (!t1.equals(BoolT()) || !t2.equals(BoolT()))
                                        throw illTyped("not a boolean");
                                union (t1, BoolT());
                                union (t2, BoolT());
                                BoolT()
                        }
                        case _ => (evalTo(e1), evalTo(e2)) match {
                        case (BoolT(), BoolT()) => bop match {
                        case And => {
                                if (!evalTo(e1).equals(BoolT()))
                                        throw illTyped("not a boolean");
                                if (!evalTo(e2).equals(BoolT()))
                                        throw illTyped("not a boolean");
                                union(evalTo(e1), BoolT()); union(evalTo(e2), BoolT()); BoolT()}
                        case Or  => {
                                if (!evalTo(e1).equals(BoolT()))
                                        throw illTyped("not a boolean");
                                if (!evalTo(e2).equals(BoolT()))
                                        throw illTyped("not a boolean");
                                union(evalTo(e1), BoolT()); union(evalTo(e2), BoolT()); BoolT()}
                        }
                        case (NumT(), NumT()) => bop match {
                        case Add => {
                                if (!evalTo(e1).equals(TVar(AL)))
                                        throw illTyped("not a number/string");
                                if (!evalTo(e2).equals(TVar(AL)))
                                        throw illTyped("not a number/string");
                                union(evalTo(e1), TVar(AL)); union(evalTo(e2), TVar(AL)); NumT()}
                        case Sub => {
                                if (!evalTo(e1).equals(NumT()))
                                        throw illTyped("not a number");
                                if (!evalTo(e2).equals(NumT()))
                                        throw illTyped("not a number");
                                union(evalTo(e1), NumT()); union(evalTo(e2), TVar(AL)); NumT()}
                        case Mul => {
                                if (!evalTo(e1).equals(NumT()))
                                        throw illTyped("not a number");
                                if (!evalTo(e2).equals(NumT()))
                                        throw illTyped("not a number");
                                union(evalTo(e1), NumT()); union(evalTo(e2), TVar(AL)); NumT()}
                        case Div => {
                                if (!evalTo(e1).equals(NumT()))
                                        throw illTyped("not a number");
                                if (!evalTo(e2).equals(NumT()))
                                        throw illTyped("not a number");
                                union(evalTo(e1), NumT()); union(evalTo(e2), TVar(AL)); NumT()}
                        case Lte => { if (!evalTo(e1).equals(TVar(AL)))
                                throw illTyped("not a number/string");
                        if (!evalTo(e2).equals(TVar(AL)))
                                throw illTyped("not a number/string");
                        union(evalTo(e1), TVar(AL)); union(evalTo(e2), TVar(AL)); BoolT()}
                        }
                        case (StrT(), StrT()) => bop match {
                        case Add => {
                                if (!evalTo(e1).equals(TVar(AL)))
                                        throw illTyped("not a number/string");
                                if (!evalTo(e2).equals(TVar(AL)))
                                        throw illTyped("not a number/string");
                                union(evalTo(e1), TVar(AL)); union(evalTo(e2), TVar(AL)); StrT()}
                        case Lte => { if (!evalTo(e1).equals(TVar(AL)))
                                throw illTyped("not a number/string");
                        if (!evalTo(e2).equals(TVar(AL)))
                                throw illTyped("not a number/string");
                        union(evalTo(e1), TVar(AL)); union(evalTo(e2), TVar(AL)); BoolT()}
                        }
                        case (v, a) => bop match
                        {
                        case Cons =>
                        {
                                val t1 = evalTo(e1);
                                if (!t1.equals(BoolT()))
                                        throw illTyped("guard not a boolean");
                                union(t1, BoolT());
                                val t2 = evalTo(e2);
                                if (!t2.equals(ListT(t1)))
                                {
                                        throw illTyped("not a list of  correct type");
                                }
                                union (t2, ListT(t1));
                                t2;
                        }
                        }
                        }
                        }
                        case If(e, b1, b2) =>
                        {
                                val t1 = evalTo(e);
                                val t2 = evalTo(b1);
                                val t3 = evalTo(b2);
                                union (t1, BoolT());
                                if (!t2.equals(t3))
                                        throw illTyped("if statement branches have different types");
                                union (t2, t3);
                                t3;
                        }
                        case In(typ) => typ match {
                        case NumT() => {scala.Console.readLine(); NumT()}
                        case StrT() => {scala.Console.readLine(); StrT()}
                        }
                        case Call(ef, es) => {
                                if (!evalTo(ef).isInstanceOf[FunT])
                                        throw illTyped("call is not function type");
                                union (evalTo(ef), FunT(List(TVar()), TVar()));

                                for (i <-0 to es.length)
                                {
                                        if (!ef.asInstanceOf[FunT].typs(i).equals(evalTo(es(i))))
                                                throw illTyped("param/argument mismatch");
                                        union (TVar(), evalTo(es(i)));
                                }
                                TVar();
                        }
                        case NotList(es) =>
                        {
                                if ( es.size == 0)
                                        ListT(TVar());
                                else
                                {
                                        var t = evalTo(es(0));
                                        for (i <- 1 to es.size)
                                        {
                                                union (t, evalTo(es(i)));
                                        }
                                        ListT(t);
                                }
                        }
                        case Head(e) =>
                        {
                                val t1=evalTo(e);
                                if (!t1.isInstanceOf[ListT])
                                {
                                        throw illTyped("is not a list");
                                }
                                val lt = t1.asInstanceOf[ListT].typ;
                                union (t1, lt);
                                lt
                        }
                        case Tail(e) =>
                        {
                                val t1=evalTo(e);
                                if (!t1.isInstanceOf[ListT])
                                {
                                        throw illTyped("is not a list");
                                }
                                val lt = t1.asInstanceOf[ListT].typ;
                                union (t1, lt);
                                lt
                        }
                        case Block(vbs, t) => {
                                val dummies = for ( VarBind(x,_) <- vbs ) yield (x, UnitT())
                                val newEnv = dummies.foldLeft( env )(
                                                (env, xv) => env + (xv._1 -> evalTo(xv._1) )) //mapping var to type

                                                for ( VarBind(x, e) <- vbs )
                                                {
                                                        if (!newEnv(x).equals( eval(Config(e, newEnv))))
                                                                throw illTyped("bound var not the same type");
                                                        union (TVar(), eval(Config(e, newEnv)));
                                                }

                                eval(Config(t, newEnv)); //verify well typed?
                                //evalTo(t);
                        }
                        case f:Fun =>
                        {
                                UnitT();
                        }
                        }


                        evalTo(config.t)
        }
}

} 
