package Handler;

import java.util.StringTokenizer;
import java.util.Vector;

public class TrigEquation extends EquationObject {
		private String equation = "";
		private String equationType = "";
		private String trigType = "";
		
		public TrigEquation(String equation1)
		{
			super();
			equation = equation1;
			equationType = "Polynomial";
			boolean type1 = false;
			boolean type2 = false;
			boolean type3 = false;
			
			Vector<String> equationVector = tokenizeEquation();
			
			for(int ctr = 0; ctr < equationVector.size(); ctr++)
			{
				if(equationVector.elementAt(ctr).startsWith("sin"))
					type1 = true;
				if(equationVector.elementAt(ctr).startsWith("cos"))
					type2 = true;
				if(equationVector.elementAt(ctr).startsWith("tan"))
					type3 = true;
			}
			
			if((type1 && type2) || (type2 && type3) || (type1 && type3))
				trigType = "mixed";
			else if (type1)
				trigType = "sin";
			else if (type2)
				trigType = "cos";
			else if (type3)
				trigType = "tan";
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
		public String getEquationType() 
		{
			return equationType;
		}
		
		public String getTrigType()
		{
			return trigType;
		}

		@Override
		public String getEquation() {
			// TODO Auto-generated method stub
			return equation;
		}

}
