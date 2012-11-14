package Graph;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Label;
import java.awt.TextField;
import java.awt.image.BufferedImage;
import Graph.Function;




public class Graph {

	private static final long serialVersionUID = 1L;

	TextField functionInput;
	Label message;
	int width = GUIMain.GUI.width;
	int height = GUIMain.GUI.height;
	BufferedImage Graph = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
	Graphics p = Graph.getGraphics();
	double Xmax=10;
    double Xmin=-10.0;
    double Xscl=1.0;
    double Ymin=-10.0;
    double Ymax=10.0;
    double Yscl=1.0;
    boolean axes=true;
    boolean Expr=true;
    
    public double getXmax() {
		return Xmax;
	}

	public void setXmax(double xmax) {
		Xmax = xmax;
	}

	public void setXmin(double xmin) {
		Xmin = xmin;
	}

	public void setXscl(double xscl) {
		Xscl = xscl;
	}

	public void setYmax(double ymax) {
		Ymax = ymax;
	}

	public void setYmin(double ymin) {
		Ymin = ymin;
	}

	public void setYscl(double yscl) {
		Yscl = yscl;
	}

	public void setAxes(boolean axes) {
		this.axes = axes;
	}

	public void setExpr(boolean expr) {
		Expr = expr;
	}


	private Function funct;

	//Constructor
	public Graph()
	{
		//setBackground(Color.white);	
		funct = new Function();
		funct = null;   

	}	

	public void setFunction(Function input)
	{
		this.funct =  input;
		draw ();
	}

	public void clearFunction()
	{
		this.funct = null;
		draw ();
	}
	
	public BufferedImage draw ()
	{
		
		paint (p);
		return Graph;

	}

	public void paint(Graphics g) {
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, width, height);
		g.setColor(Color.black);
		if (funct == null) {
			g.drawString("No function is available.", 20, 30);
		}
		else {
			if(Expr)	
				g.drawString("y = " + funct.getDefinition(), 5, 15);
			drawAxes(g);
			drawFunction(g);
		}
	}

	public void drawAxes(Graphics g) {

		g.setColor(Color.blue);
		if(axes)
		{	
			
			int totalX = (int) (Xmax + ((-1)*Xmin));
			int totalY = (int) (Ymax + ((-1)*Ymin));
			
			//Draws the X-Axis
			g.drawLine(0, (int) ((Ymax/totalY)*(height)), width, (int) ((Ymax/totalY)*(height)));
			//Draws the Y_Axis
			g.drawLine((int) (((-1)*Xmin/totalX)*width), 0, (int) (((-1)*Xmin/totalX)*width), height);
		
	      int a1, b1;   
	      int a2, b2; 
	      
	      
	      //Draws ticks on positive X-Axis
	      
	      for(int s = 0; s <= Xmax; s+= Xscl)
	      {  
	    	  a1 = (int)( (((Xscl + s) + (-1)*Xmin) / totalX) * width );
	    	  b1 = (int)( (Ymax + .2) / totalY * height );
	    	  a2 = (int)( ((Xscl + s) + (-1)*Xmin) / totalX * width );
    		  b2 = (int)( (Ymax - .2) / totalY * height );
      
    	  
      
      			g.drawLine(a1,b1,a2,b2);
     	      }
      
	      //Draws the ticks on negative X-Axis
	      
	      double min = (-1.0)*Xmin;
	      	
    	     for(int s = 0; s <= min; s+= Xscl)
   	     {  
    		  a1 = (int)(( ( ((-1.0)*Xscl) - s) + min) / totalX * width );
    		  b1 = (int)( (Ymax + .2) / totalY * height );
    		  a2 = (int)(( (((-1.0)*Xscl) - s) + min) / totalX  * width );
    		  b2 = (int)( (Ymax - .2) / totalY * height );
      
    	  
      
      		g.drawLine(a1,b1,a2,b2);
   	     }
    	     
    	 //Draw the ticks on the negative Y-Axis    
      
	      	
       double miny = (-1.0)*Ymin;
       
   	   for(int s = 0; s <= miny; s+= Yscl)
   	   {  
   	 	  a1 = (int)( (((.2) + (-1.0)*Xmin) / totalX)  * width );
   	 	  b1 = (int)( (((Yscl) + s) + Ymax) / totalY * height );
   	 	  a2 = (int)( ((-.2) + (-1.0)*Xmin) / totalX  * width );
   	 	  b2 = (int)( (((Yscl) + s) + Ymax) / totalY * height );
      
    	 
      
      		g.drawLine(a1,b1,a2,b2);
   	   }
      
   	   //Draws the ticks on the positive Y-Axis
   	   
  	    for(int s = 0; s <= Ymax; s+= Yscl)
  	    {  
  	  	  a1 = (int)( ((.2) + (-1)*Xmin) / totalX  * width );
  	  	  b1 = (int)( (Ymax - (Yscl + s)) / totalY * height );
  	  	  a2 = (int)( ((-.2) + (-1)*Xmin) / totalX  * width );
  	  	  b2 = (int)( (Ymax - (Yscl + s)) / totalY * height );
      
    	
      
      		g.drawLine(a1,b1,a2,b2);
 	     }
		}



	}

	void drawFunction(Graphics g) {

		// Just plot 301 points with lines between them. 
		double x, y;          
		double prevx, prevy;  
		double dx;  
		int totalX = (int) (Xmax + ((-1)*Xmin));

		dx  = totalX / 300.0;

		g.setColor(Color.red);

		x = Xmin;
		y = funct.equation(x);

		/* Compute each of the other 300 points, and draw a line segment
          between each consecutive pair of points.  Note that if the function
          is undefined at one of the points in a pair, then the line 
          segment is not drawn.  */

		for (int i = 1; i <= 300; i++) {

			prevx = x;           // Save the coords of the previous point.
			prevy = y;

			x += dx;            // Get the coords of the next point.
			y = funct.equation(x);

			if ( (! Double.isNaN(y)) && (! Double.isNaN(prevy)) ) {
				// Draw a line segment between the two points.
				putLine(g, prevx, prevy, x, y);
			}

		}  

	}  

	void putLine(Graphics g, double x1, double y1, double x2, double y2) {

		int a1, b1;   
		int a2, b2;   
		
		int totalX = (int) (Xmax + ((-1)*Xmin));
		
		
		int totalY = (int) (Ymax + ((-1)*Ymin));

		   a1 = (int)( (x1 + (-1)*Xmin) / totalX * width );
	       b1 = (int)( (Ymax - y1) / totalY * height );
	       a2 = (int)( (x2 + (-1)*Xmin) / totalX * width );
	       b2 = (int)( (Ymax - y2) / totalY * height );
       
         
		g.drawLine(a1,b1,a2,b2);

	}  

}






