package Handler;

/* the start of the handling. a string is passed and the handler invokes the respective type of calculator problem
*/
import java.awt.Image;
import java.util.StringTokenizer;
import java.util.Vector;

import Equation.Equation;
/**
 * 
 * @author Sebastian Mazilu y7
 *
 */
public class HandlerMain {
	/**
	 * The main method which takes the String determines what it is and passes it on to the solve class
	 * 
	 * @param equation The entire generated equation the user generated
	 * @return the answer to the user generated equation or the equation itself if invalid
	 */
	public static String handle(String equation)
	{	
		equation = addParenthesis(equation);
		equation = addNegative(equation);
		
		if(isGraph(equation))
		{
			if (equation.equals("Y =   X "))
			{
				
				return(" 1 * X = ");
			}
			
			if (invalidGraph(equation))
				return "Invalid Graph";
			
			Vector<String> equationVector = tokenizeEquation(equation);
			boolean trigeq = false;
			EquationObject tEquation;
			
			for(int ctr = 0; ctr < equationVector.size(); ctr++)
			{
				if(isTrig(equationVector.elementAt(ctr)))
				{
					trigeq = true;
					break;
				}
			}
			
			if(trigeq)
			{
				tEquation = new TrigEquation(equation);
			}
				
			else 
			{
				tEquation = new PolynomialEquation(equation);
			}
			return trimVar(tEquation.getEquation()) + " = ";
				
		}
		
		else if (invalidData(equation))
		{
			return("Invalid Data");
		}
		
		else if (clearAll(equation))
		{
			return "";
		}
		
		else if (clearLast(equation))
		{
			return "";
		}
		
		else if (onlyNumber(equation))
		{
			return equation;
		}

		else if(handleSet(equation))
		{	
			//pass to set value
		}
		
		else if(handleGraphData(equation))
		{
			//pass to graph questions
		}

		//else it must be a solve
		else if(handleEquation(equation))
		{
			Vector<String> equationVector = tokenizeEquation(equation);
			boolean trigeq = false;
			EquationObject tEquation;
			
			for(int ctr = 0; ctr < equationVector.size(); ctr++)
			{
				if(isTrig(equationVector.elementAt(ctr)))
				{
					trigeq = true;
					break;
				}
			}
			
			if(trigeq)
			{
				tEquation = new TrigEquation(equation);
			}
				
			else 
			{
				tEquation = new NormEquation(equation);
			}
					
					
			
			
			Equation e = new Equation();
			try {return (e.solving(tEquation.getEquation() + " =")) + "";}
			catch(Exception exc)
			{
				return "Invalid Entry";
			}
		}
		return "";
	}
	
	private static boolean invalidGraph(String equation)
	{
		Vector<String> equation1 = tokenizeEquation(equation);
		boolean endLoop = false;
		
		for(int ctr = 2; ctr < equation1.size(); ctr ++)
		{
			
			if(ctr != equation1.size() - 1)
			{
				if(isNumber(equation1.elementAt(ctr))&&isVariable(equation1.elementAt(ctr+1)))
				{
					endLoop = true;
					break;
				}
				if(isVariable(equation1.elementAt(ctr))&&isNumber(equation1.elementAt(ctr+1)))
				{
					endLoop = true;
					break;
				}
				if(isNumber(equation1.elementAt(ctr)) && isNumber(equation1.elementAt(ctr+1)))
				{
					endLoop = true;
					break;
					
				}
				
				if(isVariable(equation1.elementAt(ctr)) && isVariable(equation1.elementAt(ctr+1)))
				{
					endLoop = true;
					break;
				}
				
				if(isSymbol(equation1.elementAt(ctr)) && isSymbol(equation1.elementAt(ctr+1)))
				{

					endLoop = true;
					break;
				}
				//problem with this method part because its reading - as with space.
				if(isSymbol(equation1.elementAt(0)))
				{
					endLoop = true;
					break;
				}
				if(isSymbol(equation1.elementAt(equation1.size() - 1)))
				{
					endLoop = true;
					break;
				} 
				
			}
			else 
			{
				if(equation1.size() == 1 && !isNumber(equation1.elementAt(2)))
				{
					endLoop = true;
					break;
				}
				if(isSymbol(equation1.elementAt(ctr)))
				{
					endLoop = true;
					break;
				}
				if(isTrig((equation1.elementAt(equation1.size() - 1))) && equation1.size() != 1) 
				{
					if(!(equation1.elementAt(equation1.size() - 1).endsWith(")")))
					{
						endLoop = true;
						break;
					}
				}
				
			}
		}
		
		return endLoop;
		
		
	}
		
	private static boolean isGraph(String equation)
	{
		if(equation.startsWith("Y =")||equation.startsWith(" Y ="))
			return true;
		return false;
	}
	private static boolean clearLast(String equation)
	{
		if (equation.equals("CLEAR"))
			return true;
		return false;
	}
	
	private static boolean clearAll(String equation)
	{
		if (equation.equals("CLEARALL"))
			return true;
		return false;
	}
	
	private static boolean handleSet(String equation)
	{
		boolean endLoop = false;
		Vector<String> equation1 = tokenizeEquation(equation);

		//Check to see if it is a set equation
		for(int ctr = 0; ctr < equation1.size(); ctr++)
		{
			if(equation1.elementAt(ctr).equals("=") && ctr != equation1.size() - 1)
			{
				endLoop = true;
				break;
			}
		}
		return endLoop;


	}
	
	private static boolean handleEquation(String equation)
	{	
		boolean endLoop = false;
		Vector<String> equation1 = tokenizeEquation(equation);

		//Check to see if it is a solve equation
		for(int ctr = 0; ctr < equation1.size(); ctr++)
		{
			if(!(equation1.elementAt(ctr).equals("=")))
			{
				endLoop = true;
				break;
			}
		}
		return endLoop;
	}

	private static boolean handleGraphData(String equation)
	{
		//later iteration
		return false;
	}

	private static boolean invalidData(String equation)
	{
		Vector<String> equation1 = tokenizeEquation(equation);
		boolean endLoop = false;

		//Check to see if it is invalid data
		for(int ctr = 0; ctr < equation1.size(); ctr++)
		{
			if(ctr != equation1.size() - 1)
			{
				if(isNumber(equation1.elementAt(ctr)) && isNumber(equation1.elementAt(ctr+1)))
				{
					endLoop = true;
					break;
					
				}
				
				if(isSymbol(equation1.elementAt(ctr)) && isSymbol(equation1.elementAt(ctr+1)))
				{

					endLoop = true;
					break;
				}
				//problem with this method part because its reading - as with space.
				if(isSymbol(equation1.elementAt(0)))
				{
					endLoop = true;
					break;
				}
				if(isSymbol(equation1.elementAt(equation1.size() - 1)))
				{
					endLoop = true;
					break;
				} 
				
			}
			else 
			{
				if(equation1.size() == 1 && !isNumber(equation1.elementAt(0)))
				{
					endLoop = true;
					break;
				}
				if(isSymbol(equation1.elementAt(ctr)))
				{
					endLoop = true;
					break;
				}
				if(isTrig((equation1.elementAt(equation1.size() - 1))) && equation1.size() != 1) 
				{
					if(!(equation1.elementAt(equation1.size() - 1).endsWith(")")))
					{
						endLoop = true;
						break;
					}
				}
			}
		}
		return endLoop;
		
	}

	private static Vector<String> tokenizeEquation(String equation)
	{	
		StringTokenizer tokenizeIt = new StringTokenizer(equation);
		Vector<String> equation1 = new Vector<String>();

		//tokenize equation and put it into a vector
		while(tokenizeIt.hasMoreTokens())
		{
			equation1.add(tokenizeIt.nextToken());
		}
		return equation1;
	}

	private static boolean onlyNumber(String equation)
	{
		Vector<String> equation1 = tokenizeEquation(equation);
		
		if((equation1.size() == 1) && (isNumber(equation1.elementAt(0)) && !(isTrig(equation1.elementAt(0)))))
		{
			return true;
		}
		return false;
	}
	
	private static boolean isNumber(String str)
	{
            try 
            {
            	Double.parseDouble(str);
            }
            catch(NumberFormatException e)
            {
            	return false;
            }
            		
        	return true;
	}
	
	private static boolean isSymbol(String str)
	{
		if(str.equals("+") || str.equals("*") || str.equals("-") || str.equals("/"))
			return true;
		return false;
	}
	
	private static boolean isTrig(String str)
	{
		for (int i = 0; i < str.length(); i++) 
	   	{
            		//If we find a trig identity character we return false.
            		if ((str.startsWith("tan")
            				||str.startsWith("cos")
            				||str.startsWith("tan")))
             			return true;
		}
		
		return false;
	}
	
	private static boolean isVariable(String str)
	{
		if(str.equals("X"))
			return true;
		return false;
	}
	
	private static String trimVar(String str)
	{
		Vector<String> equation1 = tokenizeEquation(str);
		String equation = "";
		
		for(int ctr = 2; ctr < equation1.size(); ctr ++ )
		{
			equation = equation + " " + equation1.elementAt(ctr);
		}
		return equation;
	}
	private static int countOpenParenthesis(String str)
	{
		int numberOfP = 0;
		Vector<String> equation1 = tokenizeEquation(str);
		
		for(int ctr = 0; ctr < equation1.size(); ctr++)
		{
			if(equation1.elementAt(ctr).contains("("))
				numberOfP++;
		}
		
		return numberOfP;
	}
	private static int countClosedParenthesis(String str)
	{
		int numberOfP = 0;
		Vector<String> equation1 = tokenizeEquation(str);
		
		for(int ctr = 0; ctr < equation1.size(); ctr++)
		{
			if(equation1.elementAt(ctr).contains(")"))
				numberOfP++;
		}
		
		return numberOfP;
	}

	private static String addParenthesis(String str)
	{
		String equation = str;
		int pDifference;
		pDifference = countOpenParenthesis(str)-countClosedParenthesis(str);
		
		for(int ctr = 0; ctr < pDifference; ctr++)
		{
			equation = equation + " ) ";
		}
		
		return equation;
	}
	private static String addNegative(String str)
	{
		Vector<String> equation1 = tokenizeEquation(str);
		String equation = "";
		if(str.contains("- X"))
		{
			for(int ctr = 0; ctr < equation1.size(); ctr++)
			{
				if(equation1.elementAt(ctr).contains("-")&&(equation1.elementAt(ctr+1).contains("X")))
				{
					equation = equation + " -1 * X ";
					ctr++;
				}
				else
					equation = equation + " " + equation1.elementAt(ctr);
			}
			return equation;
		}
		else if(str.contains("- sin"))
		{
			for(int ctr = 0; ctr < equation1.size(); ctr++)
			{
				if(equation1.elementAt(ctr).contains("-")&&(equation1.elementAt(ctr+1).contains("sin")))
				{
					equation = equation + " -1 * sin( ";
					ctr++;
				}
				else
					equation = equation + " " + equation1.elementAt(ctr);
			}
			return equation;
		}
		else if(str.contains("- cos"))
		{
			for(int ctr = 0; ctr < equation1.size(); ctr++)
			{
				if(equation1.elementAt(ctr).contains("-")&&(equation1.elementAt(ctr+1).contains("cos")))
				{
					equation = equation + " -1 * cos( ";
					ctr++;
				}
				else
					equation = equation + " " + equation1.elementAt(ctr);
			}
			return equation;
		}
		else if(str.contains("- tan"))
		{
			for(int ctr = 0; ctr < equation1.size(); ctr++)
			{
				if(equation1.elementAt(ctr).contains("-")&&(equation1.elementAt(ctr+1).contains("tan")))
				{
					equation = equation + " -1 * tan( ";
					ctr++;
				}
				else
					equation = equation + " " + equation1.elementAt(ctr);
			}
			return equation;	
		}
		return str;
		
	}
}//end of class handler