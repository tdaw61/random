module branch(btype, zero, out);
	input [1:0] btype;
	input zero;
	output out;
	reg out;

	always@(btype or zero)
	begin
	if(btype == 2'b11)
		out <= 1;
	else if(btype == 2'b10)
	begin
		if(zero == 1)
			out <= 1;
		else
			out <= 0;
	end
	else if(btype == 2'b00)
		out <= 0;
		
		//if({zero,btype}==3'bx11) assign out=jump;
		//if({zero,btype}==3'b110) assign out=jump;
		//if({zero,btype}==3'b010) assign out<=next;
		//if({zero,btype}==3'bx00) assign out<=next;
	end
endmodule
	

