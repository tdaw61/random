package Equation;
import java.util.StringTokenizer;
import java.util.Stack;
import Equation.TrigSolve;
/**
 *
 * @author Taylor Y7
 *
 *
 */
public class Equation
{
                String line = null;
                String operator = null;
                String main = null;
                String fs = null;
                String top = null;
                String solve = "";
                String second = "";
                String work = "";
                String value = "";
                double ret = 0;
                double fn = 0;
                double sn = 0;
                double ans = 0;
                double num = 0;
               
                double something = 0;
                Stack<Double> numbers = new Stack<Double>();
                Stack<String> symbols = new Stack<String>();
                StringTokenizer token;
                boolean stop = false;
                boolean go;
               
				
	
/**
 *
 * @param equation equation is a string passed in from the Handler.
 *
 */
        public double solving(String equation)
        {      
                token = new StringTokenizer(equation);
                while(token.hasMoreTokens())
                {
                		
                        main = token.nextToken();
                        //System.out.println("this is the main: " + main);
                        //System.out.println("\n");
                       
                        
                        
                        if(main.equals("("))
                                symbols.push(main);
                        else if(main.equals("^("))
                        {
                        	
                        	value = token.nextToken();
                        	counting();
                        	symbols.push(value);
                        	fn = numbers.pop();
                        	Power pow = new Power(equation);
                        	ret = pow.solve(fn);
                        	//System.out.println("this is ret: " + ret);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                        }
                        else if(main.equals("cbrt("))
                        {
                        	
                        	value = token.nextToken();
                        	counting();
                        	symbols.push(value);
                        	Croot croot = new Croot(equation);
                        	ret = croot.solve();
                        	//System.out.println("this is ret: " + ret);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                        }
                        else if(main.equals("ln("))
                        {
                        	
                        	value = token.nextToken();
                        	counting();
                        	symbols.push(value);
                        	Ln ln = new Ln(equation);
                        	ret = ln.solve();
                        	//System.out.println("this is ret: " + ret);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                        }
                        else if(main.equals("abs("))
                        {
                        	value = token.nextToken();
                        	counting();
                        	symbols.push(value);
                        	Abs abs = new Abs(equation);
                        	ret = abs.solve();
                        	//System.out.println("this is ret: " + ret);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                        }
                        else if(main.equals("e^("))
                        {
                        	
                        	value = token.nextToken();
                        	counting();
                        	symbols.push(value);
                        	Euler Eu = new Euler(equation);
                        	ret = Eu.solve();
                        	//System.out.println("this is ret: " + ret);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                        }
                        else if(main.equals("log("))
                        {
                        	
                        	value = token.nextToken();
                        	counting();
                        	symbols.push(value);
                        	
                        	Log log = new Log(equation);
                        	ret = log.solve();
                        	//System.out.println("this is ret: " + ret);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                        }
                        else if(main.equals("sqrt("))
                        {
                        	
                        	value = token.nextToken();
                        	counting();
                        	symbols.push(value);
                        	
                        	Root ro = new Root(equation);
                        	ret = ro.solve();
                        	//System.out.println("this is ret: " + ret);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                        }
                        else if(main.equals("*"))
                        {
                                if(symbols.empty())
                                {
                                        symbols.push(main);
                                }
                                else if(symbols.peek().equals("("))
                                {
                                        symbols.push(main);
                                }
                                else if(symbols.peek().equals("/"))
                                {
                                        divide(token);
                                }
                                else if(symbols.peek().equals("*"))
                                {
                                        multiply(token);
                                }      
                                else if(symbols.peek().equals("+"))
                                {
                                        symbols.push(main);
                                     
                                }
                                else if(symbols.peek().equals("-"))
                                {
                                	 symbols.push(main);
                                	
                                }
                                       
                        }
                        else if (main.equals("/"))
                        {
                                if(symbols.empty())
                                {
                                        symbols.push(main);
                                }
                                else if(symbols.peek().equals("("))
                                {
                                        symbols.push(main);
                                }
                                else if(symbols.peek().equals("/"))
                                {
                                        divide(token);
                                }
                                else if(symbols.peek().equals("*"))
                                {
                                        multiply(token);
                                }      
                                else if(symbols.peek().equals("+"))
                                {
                                        symbols.push(main);
                                       
                                }
                                else if(symbols.peek().equals("-"))
                                {
                                        symbols.push(main);
                                        
                                }
                        }
                               
                        else if(main.equals("+") || main.equals("-"))
                        {
                               
                                if(symbols.empty())
                                {
                                        symbols.push(main);
                                }
                                else if(symbols.peek().equals("("))
                                {
                                        symbols.push(main);
                                }
                                else if(symbols.peek().equals("*"))
                                {
                                        multiply(token);
                                        
                                }
                                else if(symbols.peek().equals("/"))
                                {
                                        divide(token);
                                        
                                }
                                else if(symbols.peek().equals("+"))
                                {
                                        add(token);
                                       
                                }
                                else if(symbols.peek().equals("-"))
                                {
                                        subtract(token);
                                       
                                }
                        }              
                        else if(main.equals(")"))
                        {
                               
                                go = true;
                                while(go)
                                {
                                	//System.out.print("\n you are here");
                                		if(symbols.empty())
                                		{
                                			ans = numbers.peek();
                                			go = false;
                                		}
                                		else if(symbols.peek().equals("/"))
                                        {
                                                divagain(token);
                                                symbols.pop();
                                        }
                                        else if(symbols.peek().equals("*"))
                                        {
                                                multagain(token);
                                                symbols.pop();
                                        }
                                        else if(symbols.peek().equals("+"))
                                        {
                                                addagain(token);
                                                symbols.pop();
                                        }
                                        else if(symbols.peek().equals("-"))
                                        {
                                                subagain(token);   
                                                symbols.pop();
                                        }
                                        else if(symbols.peek().equals("("))
                                        {
                                        		ans = numbers.peek();
                                                symbols.pop();
                                                go = false;
                                        }
                                }      
                        }
                        else if(main.equals("sin(") || main.equals("-sin("))
                        {
                        	//int count = 0;
                        	value = token.nextToken();
            				counting();
							//System.out.println("This is the value after sin: " + value);
							symbols.push(value);
                        	TrigSolve sin = new TrigSolve(equation);
                        	ret = sin.sin(equation);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                     
                        }
                        else if(main.equals("cos(") || main.equals("-cos("))
                        {
                        	value = token.nextToken();
            				//int count = 0;
							counting();
							//System.out.println("This is the value after sin: " + value);
							symbols.push(value);
                        	TrigSolve cos = new TrigSolve(equation);
                        	ret = cos.cos(equation);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                     
                        }
                        else if(main.equals("tan(") || main.equals("-tan("))
                        {
                        	value = token.nextToken();
            				//int count = 0;
							counting();
							//System.out.println("This is the value after sin: " + value);
							symbols.push(value);
                        	TrigSolve tan = new TrigSolve(equation);
                        	ret = tan.tan(equation);
                        	numbers.push(ret);
                        	solve = builder(token);
                        	solving(solve);
                     
                        }
                        //this needs to be changed to be if the user presses the equal button.
                        else if(main.equals("="))
                        {
                        	if(symbols.empty())
                        		return numbers.peek();
                        	//System.out.println(equation);
                        	if(symbols.peek().equals("+"))
                        	{
                        		symbols.pop();
                        		addagain(token);
                        		solve = builder(token);
                        		solving(solve);
                        		
                        	}
                        	else if(symbols.peek().equals("-"))
                        	{
                        		symbols.pop();
                        		subagain(token);
                        		solve = builder(token);
                        		solving(solve);
                        		
                        	}
                        	else if(symbols.peek().equals("*"))
                        	{
                        		symbols.pop();
                        		multagain(token);
                        		solve = builder(token);
                        		solving(solve);
                        	}
                        	else if(symbols.peek().equals("/"))
                        	{
                        		symbols.pop();
                        		divagain(token);
                        		solve = builder(token);
                        		solving(solve);
                        	}
                        }

                        else
                        {   
                                num = Double.parseDouble(main);
                                numbers.push(num);
                        }
        if(stop)
        {
                System.exit(0);
        }
        //System.out.println("top number: " + numbers.peek());
  }//end while loop
    
  return numbers.peek();
 }//end of solving
 
 
 
        private void add(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn + sn;
                numbers.push(ans);
                symbols.pop();
                symbols.push(main);
                solve = builder(token);
                solving(solve);
        }
        private void subtract(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn - sn;
                numbers.push(ans);
                symbols.pop();
                symbols.push(main);
                solve = builder(token);
                solving(solve);
        }
        private void divide(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn / sn;
                numbers.push(ans);
                symbols.pop();
                symbols.push(main);
                solve = builder(token);
                solving(solve);
        }
        private void multiply(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn * sn;
                numbers.push(ans);
                symbols.pop();
                symbols.push(main);
                solve = builder(token);
                solving(solve);
        }
        private void addagain(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn + sn;
                numbers.push(ans);
                
        }
        private void subagain(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn - sn;
                numbers.push(ans);
               
        }
        private void divagain(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn / sn;
                numbers.push(ans);
               
        }
        private void multagain(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn * sn;
                numbers.push(ans);
                
                
        }
        //possibly make  a string return and then have an empty string for this class but then put the
        //trig class back into the solver using the string that it returns. 
        
        public String builder(StringTokenizer token)
        {
        	int ecount = 0;
        	second = "";
        	go = true;
            while(go)
            {
               if(numbers.empty())
               {
            	   //System.out.println("time to make a new line");
                    go = false;
               }
               else 
               {
                   if(symbols.empty()==false)
                   {
                	   if(symbols.peek().equals("("))
                		   second = symbols.pop() + " " + second;
                	   second = symbols.pop() + " " + second;
                   }
                   fn = numbers.pop();
                   second = fn + " " + second;   
                }
             }
            while(token.hasMoreTokens())
            {
            	//System.out.println(value);
            	value = token.nextToken();
            	if(value.equals("="))
            		ecount++;
            	second = second + " " + value;
            	//value = token.nextToken();
            }
            if(ecount==0)
            		second = second + " =";
            //System.out.println("this is the builder thing " + second);
            
            //solving(second);
            return second;
        }
        private void counting()
        {
        	value = token.nextToken();
			int count = 0;
			while(count >= 0)
			{
				if(value.equals("(") || value.equals("sin(") || value.equals("cos(") || value.equals("tan(")){count++;}
				else if(value.equals(")")){count--;}
				value = token.nextToken();
			}
			
        }
       
}