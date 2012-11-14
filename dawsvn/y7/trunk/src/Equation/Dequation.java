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
public class Dequation
{

                String line = null;
                String operator = null;
                String main = null;
                String fs = null;
                String top = null;
                String second = "";
                String work = "";
                String value = "";
                double fn = 0;
                double sn = 0;
                double ans = 0;
                double num = 0;
                double ret = 0;
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
                        System.out.println(main);
                        
                        if(main.equals("("))
                                symbols.push(main);
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
                                        symbols.push(main);
                                else if(symbols.peek().equals("-"))
                                        symbols.push(main);
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
                                        symbols.push(main);
                                else if(symbols.peek().equals("-"))
                                        symbols.push(main);
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
                                        if(symbols.peek().equals("/"))
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
                        	TrigSolve sin = new TrigSolve(equation);
                        	ret = sin.sin(equation);
                        	return sin.sin(equation);
                        }
                        else if(main.equals("cos(") || main.equals("-cos("))
                        {
                        	TrigSolve cos = new TrigSolve(equation);
                        	return cos.cos(equation);
                        }
                        else if(main.equals("tan(") || main.equals("-tan("))
                        {
                        	TrigSolve tan = new TrigSolve(equation);
                        	return tan.tan(equation);
                        }
                        //this needs to be changed to be if the user presses the equal button.
                        else if(main.equals("="))
                        {
                        	System.out.println(equation);
                        	if(symbols.peek().equals("+"))
                        	{
                        		addagain(token);
                        	}
                        	else if(symbols.peek().equals("-"))
                        	{
                        		subagain(token);
                        	}
                        	else if(symbols.peek().equals("*"))
                        	{
                        		subagain(token);
                        	}
                        	else if(symbols.peek().equals("/"))
                        	{
                        		subagain(token);
                        	}
                        }
                        	
		                               
		                           
                        		
                        /*
	                        	else if(symbols.empty() == false)
	                        	{
	                        		symbols.push(work);
			                        go = true;
			                        while(go)
			                        {
			                           if(numbers.empty())
			                           {
			                        	   System.out.println("holy fuck");
			                                go = false;
			                           }
			                           else 
			                           {
			                        	   fn = numbers.pop();
			                               second = fn + " " + second;
			                               if(symbols.empty()==false)
			                            	   second = symbols.pop() + " " + second;
	                                    }
			                         }
			                        second = second + " =";
			                        System.out.println(second);
			                        something = solving(second);
			                        
	                        	}
                        		*/
                        else
                        {   
                                num = Double.parseDouble(main);
                                numbers.push(num);
                        }
        if(stop)
        {
                System.exit(0);
        }

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
                builder(token);
        }
        private void subtract(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn - sn;
                numbers.push(ans);
                symbols.pop();
                symbols.push(main);
                builder(token);
        }
        private void divide(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn / sn;
                numbers.push(ans);
                symbols.pop();
                symbols.push(main);
                builder(token);
        }
        private void multiply(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn * sn;
                numbers.push(ans);
                symbols.pop();
                symbols.push(main);
                builder(token);
        }
        private void addagain(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn + sn;
                numbers.push(ans);
                builder(token);
              
        }
        private void subagain(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn - sn;
                numbers.push(ans);
                builder(token);
            
        }
        private void divagain(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn / sn;
                numbers.push(ans);
                builder(token);
                
        }
        private void multagain(StringTokenizer token)
        {
                sn = numbers.pop();
                fn = numbers.pop();
                ans = fn * sn;
                numbers.push(ans);
                builder(token);
                
        }
        private void builder(StringTokenizer token)
        {
        	second = "";
        	go = true;
            while(go)
            {
               if(numbers.empty())
               {
            	   System.out.println("holy fuck");
                    go = false;
               }
               else 
               {
                   if(symbols.empty()==false)
                	   if(symbols.peek().equals("("))
                		   second = symbols.pop() + " " + second;
                	   second = symbols.pop() + " " + second;
                   fn = numbers.pop();
                   second = fn + " " + second;
                	   
                }
             }
            while(token.hasMoreTokens())
            {
            	value = token.nextToken();
            	second = second + " " + value;
            	
            }
            System.out.println(second);
            solving(second);
        }
       
}