import java.io.*;
import java.util.*;


public class interp 
{
 public static void main(String args[])
  {
    try{
    Stack stack = new Stack();
    String strLine;
    //int[] vars = new int[45];
    Vector<Object> vars = new Vector<Object>();
    String[] keywords = new String[22];
    keywords[0] = "seq";
    keywords[1] = "Assign";
    keywords[2] = "While";
    keywords[3] = "Out";
    keywords[4] = "Num";
    keywords[5] = "Bool";
    keywords[6] = "Str";
    keywords[7] = "NotUnit";
    keywords[8] = "Not";
    keywords[9] = "BinOp";
    keywords[10] = "Add";
    keywords[11] = "Sub";
    keywords[12] = "Mul";
    keywords[13] = "Div";
    keywords[14] = "And";
    keywords[15] = "Or";
    keywords[16] = "Equal";
    keywords[17] = "Lte";
    keywords[18] = "If";
    keywords[19] = "In";
    keywords[20] = "Block";
    keywords[21] = "VarBind"; 
    int op = 0;
    FileInputStream fstream = new FileInputStream("ast.txt");
    DataInputStream in = new DataInputStream(fstream);
    BufferedReader br = new BufferedReader(new InputStreamReader(in));

    //print out the ast
    strLine = br.readLine();
    in.close();
    System.out.println (strLine);
    //tokenize ast
    StringTokenizer st = new StringTokenizer("strLine");
    System.out.println(st.nextToken());
    String compare = st.nextToken();
    String key;
    //for loop to compare to see if the token is a operand that needs to be pushed to the stack
    for(int i = 0; i < 23; i++)
    {
      
      if (compare.equals(keywords[i]))
	{
		op = i;
		break;
	}
      else if (!((compare.equals(")")) || (compare.equals("(")) || (compare.equals(","))))
	{
    		vars.add(compare);
	}         
		
    }
    switch (op)
    {
	case 1: 
		{
			stack.push(01);
		}
    	case 2:
		{
			stack.push(02);
		}
	case 3:
		{
			stack.push(03);
		}
	case 4:
		{
			stack.push(04);
		}
	case 5:
		{
			stack.push(05);
		}
	case 6:
		{
			stack.push(06);
		}

    	default:
		break;
    }

    //****************** INTERPRETER ********************//
    
	int oper = 1;
   //(int) oper = stack.firstElement();
   switch(oper)
   {
	case 1:
		{
			//add
			Object x = vars.firstElement();
			vars.removeElementAt(1);
			Object y = vars.firstElement();
			//if(y.isdigit());
			vars.removeElementAt(1);
			//int ans = x + y;
			//vars.add(ans);
		}
	default:
		break;
    }



    }catch (Exception e){System.err.println("Error: " + e.getMessage());}
    
  }

  








}
