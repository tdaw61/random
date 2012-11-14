/**
 * 
 */
package Equation;

import java.util.StringTokenizer;

/**
 * @author Taylor
 *
 */
public class Abs {
		StringTokenizer token;
		String value;
		double ans;
		String pass;
		String solve;
		int count;
		
		public Abs(String equation)
		{
			token = new StringTokenizer(equation);
			value = null;
			ans = 0;
			pass = "";
			solve = "";
			count = 0;
		}
		/**
		 * @param fn
		 * @return
		 */
		public double solve() 
		{
			Equation abssolve = new Equation();
			value = token.nextToken();
			while(token.hasMoreTokens())
			{
				if(value.equals("abs("))
				{
					value = token.nextToken();
					while(count >= 0)
					{
						//System.out.println("value" + value);					
						if(value.equals("(") || value.equals("abs(") || value.equals("log(") || value.equals("sqrt(") || value.equals("e^(") || value.equals("sin(") || value.equals("cos(") || value.equals("tan(")){count++;}
						else if(value.equals(")")){count--;}
						if(count >= 0)
							pass = pass + " " + value;
						value = token.nextToken();
					}
					pass = pass + " =";
					ans = abssolve.solving(pass);
					//System.out.println("this is ans: " + ans);
					ans = Math.abs(ans);

				}
				else
				{
					value = token.nextToken();
				}
			}
			return ans;
		}
	
	
}
