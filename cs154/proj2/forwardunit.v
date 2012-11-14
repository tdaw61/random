module forwardunit(op1, rd1, op2, rs2, rt2, rt1, fwRs, fwRt, regwr);
	input[5:0] op1, op2;
	input[4:0] rd1, rs2, rt2, rt1;
	input regwr;
	output fwRs, fwRt;
	reg fwRs, fwRt;
	always@(op2 or rs2 or rt2 or rd1 or op1 or rt1)
	begin
		
		if(op2==6'b000000 || op2==6'b001010)//add, slt, sub, sw
		begin
			if(op1==6'b000000)//add,sub,slt,slti
			begin
				if(rt2==rd1)
					fwRt<=1;
				else
					fwRt<=0;
				if(rs2==rd1)
					fwRs<=1;
				else
					fwRs<=0;
			end
			if(op1==6'b001000 || op1==6'b100111 || op1==6'b100000)//lw, stli, addi
			begin
				if(rt2==rt1)
					fwRt<=1;
				else
					fwRt<=0;
				if(rs2==rt1)
					fwRs<=1;
				else
					fwRs<=0;
			end
		end
		
		
		if(op2==6'b100000 || op2==6'b100111 || op2==6'b001000) //addi, slti, lw
		begin
			if(op1==6'b000000)//add,sub,slt,slti
			begin
				if(rs2==rd1)
					fwRs<=1;
				else
					fwRs<=0;
			end
			if(op1==6'b001000 || op1==6'b100111 || op1==6'b100000)//lw, stli, addi
			begin
				if(rs2==rt1)
					fwRs<=1;
				else
					fwRs<=0;
			end
		end
		
		if(op1==6'b001010 || op1==6'b110001 || op1==6'b001100)
		begin
			fwRs<=0;
			fwRt<=0;
		end
		if(regwr == 0)
		begin	
			fwRs<=0;
			fwRt<=0;
		end
		
	end
endmodule
		

		
					
			