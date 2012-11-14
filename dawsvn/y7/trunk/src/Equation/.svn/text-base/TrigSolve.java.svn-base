package Equation;
import java.util.StringTokenizer;
import java.math.*;
import Equation.Equation;

public class TrigSolve
{
	StringTokenizer token;
	String value;
	double ans;
	String pass;
	String solve;
	int count;
	
	//
	public TrigSolve(String equation)
	{
		token = new StringTokenizer(equation);
		value = null;
		ans = 0;
		pass = "";
		solve = "";
		count = 0;
		//int mode = 0; next iteration
	}
	public double sin(String equation)
	{
		Equation sinsolve = new Equation();
		value = token.nextToken();
		while(token.hasMoreTokens())
		{
			if(value.equals("sin("))
			{
				value = token.nextToken();
				while(count >= 0)
				{
					//System.out.println(value);					
					if(value.equals("(") || value.equals("cbrt(")|| value.equals("ln(") || value.equals("abs(") || value.equals("log(") || value.equals("sqrt(") || value.equals("e^(") || value.equals("sin(") || value.equals("cos(") || value.equals("tan(")){count++;}
					else if(value.equals(")")){count--;}
					if(count >= 0)
						pass = pass + " " + value;
					value = token.nextToken();
				}
				pass = pass + " =";
				//System.out.println("this is the pass : " + pass);
				ans = sinsolve.solving(pass);
				//System.out.println("This is the answer: " + ans);
				ans = Math.sin(ans);
				solve = solve + " " + ans;
				//System.out.println(solve);
			}
			else //if(value != "sin(")
			{
				solve = solve + " " + value;
				value = token.nextToken();
			}
		}
		//System.out.println("this is the answer: " + ans);
		//System.out.println("this is the new answer: " + ans);
		solve = solve + " =";
		//ans = sinsolve.solving(solve);
		//System.out.println("This is the answer: " + ans);
		return ans;
	}
	public double cos(String equation)
	{
		Equation cossolve = new Equation();
		value = token.nextToken();
		while(token.hasMoreTokens())
		{
			if(value.equals("cos("))
			{
				value = token.nextToken();
				while(count >= 0)
				{
					//System.out.println(value);					
					if(value.equals("(") || value.equals("cbrt(")|| value.equals("ln(") || value.equals("abs(") || value.equals("log(") || value.equals("sqrt(") || value.equals("e^(") || value.equals("sin(") || value.equals("cos(") || value.equals("tan(")){count++;}
					else if(value.equals(")")){count--;}
					if(count >= 0)
						pass = pass + " " + value;
					value = token.nextToken();
				}
				pass = pass + " =";
				//System.out.println("this is the pass : " + pass);
				ans = cossolve.solving(pass);
				//System.out.println("This is the answer: " + ans);
				ans = Math.cos(ans);
				solve = solve + " " + ans;
				//System.out.println(solve);
			}
			else //if(value != "sin(")
			{
				solve = solve + " " + value;
				value = token.nextToken();
			}
		}
		//System.out.println("this is the answer: " + ans);
		//System.out.println("this is the new answer: " + ans);
		solve = solve + " =";
		//ans = sinsolve.solving(solve);
		//System.out.println("This is the answer: " + ans);
		return ans;
	}
	public double tan(String equation)
	{
		Equation tansolve = new Equation();
		value = token.nextToken();
		while(token.hasMoreTokens())
		{
			if(value.equals("tan("))
			{
				value = token.nextToken();
				while(count >= 0)
				{
					//System.out.println(value);					
					if(value.equals("(") || value.equals("cbrt(")|| value.equals("ln(") || value.equals("abs(") || value.equals("log(") || value.equals("sqrt(") || value.equals("e^(") || value.equals("sin(") || value.equals("cos(") || value.equals("tan(")){count++;}
					else if(value.equals(")")){count--;}
					if(count >= 0)
						pass = pass + " " + value;
					value = token.nextToken();
				}
				pass = pass + " =";
				//System.out.println("this is the pass : " + pass);
				ans = tansolve.solving(pass);
				//System.out.println("This is the answer: " + ans);
				ans = Math.tan(ans);
				solve = solve + " " + ans;
				//System.out.println(solve);
			}
			else //if(value != "sin(")
			{
				solve = solve + " " + value;
				value = token.nextToken();
			}
		}
		//System.out.println("this is the answer: " + ans);
		//System.out.println("this is the new answer: " + ans);
		solve = solve + " =";
		//ans = sinsolve.solving(solve);
		//System.out.println("This is the answer: " + ans);
		return ans;
	}
}
			
		