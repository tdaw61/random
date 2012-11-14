package Equation;
import Equation.Equation;
import java.io.*;

public class TestEquation
{
	public static void main(String args[]) throws IOException
	{
		
		Equation taylor = new Equation();
		double printer = 0;
		String testthis;
		testthis = "cbrt( 64 ) =";
		printer = taylor.solving(testthis);
		System.out.println(printer);
		//testthis = "3 - 2 * 4 - ( 4 * ( 3 + 2 / 3 - 4 ) - 4 ) + 3 / 2 =";
	}
}