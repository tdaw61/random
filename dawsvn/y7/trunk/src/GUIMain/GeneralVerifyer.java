/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package GUIMain;
import javax.swing.InputVerifier;
import javax.swing.JComponent;
import javax.swing.JTextField;

/**
 *
 * @author Kal
 */
public class GeneralVerifyer extends InputVerifier {

	@Override
	public boolean verify(JComponent input) {
		String in = ((JTextField)input).getText();
		if (in.isEmpty())
			return false;
		for (int x=0; x<in.length(); x++)
		{
			if (in.charAt(x)>57||in.charAt(x)<48)
			{
				if (in.charAt(x)!=46&&in.charAt(x)!=45)
					return false;
			}
		}
		return true;
	}

}
