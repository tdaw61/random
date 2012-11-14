package Graph;


import java.awt.Color;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

import Graph.Graph;
import Graph.Function;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.plaf.ScrollPaneUI;

		


public class Table extends JPanel
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	int width = GUIMain.GUI.width;
	int height = GUIMain.GUI.height;
    Function mainFunct;
    Graph mainGraph;
    ScrollPaneUI tablePane;
    JScrollPane scrollPane;
    double TblStart= 0;
    double TblDiff= 1;
    JPanel temp;
    BufferedImage Table = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
    Graphics p = Table.getGraphics();
    
    

	public void setTable(Function mainFunct) {
		this.mainFunct = mainFunct;
	}	
	
	public double getTblStart() {
		return TblStart;
	}

	public void setTblStart(double TblStart) {
		this.TblStart = TblStart;
    }
	
	public double getTblDiff() {
		return TblDiff;
	}

	public void setTblDiff(double TblDiff) {
		this.TblDiff = TblDiff;
		drawTable();
    }
	
	public void clearTable() {
		mainFunct = null;
		drawTable();
	}
	
	
	public BufferedImage drawTable () {
		paint (p);
		return Table;
	}
		
	public void paint(Graphics g) {
		
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, width, height);
		g.setColor(Color.black);
		
		if (mainFunct == null) 
			g.drawString("No function is available.", 20, 30);
		else
		{	
			g.drawString("X", 50, 20);
			g.drawString("Y",200, 20);
		
			double y;
			int position = 40;
			double x = TblStart;

			for(double i = 0; i <= 10; i++)
			{			
				y = mainFunct.equation(x);
				g.drawString( Double.toString(x), 45, position);
				g.drawString( Double.toString(y), 130, position);
				position +=15;
				x+=TblDiff;
			}	
			
			g.setColor(Color.blue);
			g.drawLine(100, 0 , 100, 222);
			g.drawLine(0, 25 , 331, 25);
			
		}	
		
			/*
			String [] columns = {"x", "y"};
			
			Object [][] data = new Object [11][11];
			double y;
			int position = 0;
			
			//g.translate(pf.getImageableX(), pf.getImageableY());

			for(double i = -5.0; i <= 5.0; i++)
			{			
				y = mainFunct.equation(i);
				data [position] [0] = i;
				data [position] [1] = y;
				position++;
				
			}
			
			JTable table = new JTable(data, columns);
			table.setPreferredScrollableViewportSize(new Dimension(331, 221));
		    table.setFillsViewportHeight(true);
		    table.paintAll(g);
		    */
	
      }
}



	



	



	


	

