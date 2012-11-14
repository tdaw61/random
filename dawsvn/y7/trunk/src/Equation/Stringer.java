/**
 * 
 */
package Equation;

import java.util.StringTokenizer;

/**
 * @author Taylor
 *
 */
public class Stringer {
	
	StringTokenizer token;
	String value;
	double ans;
	String pass;
	String solve;
	int count;
	

	public Stringer(String equation)
	{	
		token = new StringTokenizer(equation);
		value = null;
		ans = 0;
		pass = "";
		solve = "";
		count = 0;
	}
	
	public String make()
	{
		value = token.nextToken();
		while(count >= 0)
		{
			//System.out.println(value);					
			if(value.equals("(") || value.equals("sin(") || value.equals("cos(") || value.equals("tan(")){count++;}
			else if(value.equals(")")){count--;}
			if(count >= 0)
				pass = pass + " " + value;
			value = token.nextToken();
		}
		pass = pass + " =";
		return pass;
	}
}
