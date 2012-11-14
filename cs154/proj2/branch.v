module branch(btype, zero, out, out2, out3);
	input [1:0] btype;
	input zero;
	output out, out2, out3;
	reg out, out2, out3;

	always@(btype or zero)
	begin
	if(btype == 2'b11)
		begin
		out3<=0;
		out2 <= 1;
		out <= 1'bx;
		end
	else if(btype == 2'b10)
	begin
		if(zero == 1)
			begin
			out <= 1;
			out2 <= 0;
			out3<=0;
			end
		else
			begin
			out <= 0;
			out2 <= 0;
			out3<=0;
			end
	end
	else if(btype == 2'b00)
		begin
		out <= 0;
		out2 <= 0;
		out3<= 0;
		end
	else if(btype == 2'b01)
		begin
		out<=0;
		out2<=0;
		out3<=1;
		end;
		
		//if({zero,btype}==3'bx11) assign out=jump;
		//if({zero,btype}==3'b110) assign out=jump;
		//if({zero,btype}==3'b010) assign out<=next;
		//if({zero,btype}==3'bx00) assign out<=next;
	end
endmodule
	

