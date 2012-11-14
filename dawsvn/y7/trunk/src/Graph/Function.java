package Graph;

import Equation.Equation;

public class Function {

	String mainEquation;
	
	public Function()
	{
		mainEquation = null;
	}
	
	public Function(String equation)
	{
		mainEquation = equation;	
	}
	
	public Double equation(Double x)
	{
		String numberX = Double.toString(x);
		
		Equation test = new Equation();
		
		String newString = mainEquation.replaceAll("X", numberX);
		
		//HandlerMain.handle(newString + " =");
		
		return  test.solving(newString);		
	}
	
	public String getDefinition() 
	{
		return mainEquation.replaceAll("=", " ");	
	}
}

