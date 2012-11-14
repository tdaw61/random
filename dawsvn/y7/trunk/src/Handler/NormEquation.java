package Handler;

import java.util.StringTokenizer;
import java.util.Vector;

public class NormEquation extends EquationObject {

	private String equation;
	private String equationType;
	
	public NormEquation(String equation1)
	{
		super();
		equation = equation1;
		equationType = "Polynomial";
	}
	@Override
	public String getEquationType() {
		// TODO Auto-generated method stub
		return equationType;
	}

	@Override
	public Vector<String> tokenizeEquation() {
		StringTokenizer tokenizeIt = new StringTokenizer(equation);
		Vector<String> equation1 = new Vector<String>();

		//tokenize equation and put it into a vector
		while(tokenizeIt.hasMoreTokens())
		{
			equation1.add(tokenizeIt.nextToken());
		}
		return equation1;
	}

	@Override
	public String getEquation() {
		// TODO Auto-generated method stub
		return equation;
	}

}
