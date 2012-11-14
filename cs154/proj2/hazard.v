module hazard(data1, data2, jsel, op, func, bsel, jrsel, stall, diff, stallin);
input [5:0] op;
input [5:0] func;
input [7:0] data1;
input [7:0] data2;
input stallin;
output jsel;
output bsel;
output jrsel;
output stall;
output diff;
reg jsel;
reg bsel;
reg jrsel;
reg stall;
reg diff;

always @ ( op or stall or func or data1 or data2) 
begin
	if(stallin == 1)
	begin
		bsel <= 0;
		stall <= 0;
		jrsel <= 0;
		jsel <= 0;
	end
	else	
	case(op)
	6'b110001:
	begin
		if((data1 - data2)!= 0)
			diff <= 1;
		else 	
			diff <= 0;
		if(diff==1)
		begin
			bsel <= 1;
			stall <= 1;
			jrsel <= 0;
			jsel <= 0;
		end
		else
		begin
			bsel <= 0;
			stall <= 0;
			jrsel <= 0;
			jsel <= 0;
		end
	end
	6'b001100:
	begin
		jsel <= 1;
		stall <= 1;
		jrsel <= 0;
		bsel <= 0;
	end
	6'b111101:
	begin
		jsel <= 1;
		stall <= 1;
		jrsel <= 0;
		bsel <= 0;
	end
	6'b000000:
	begin
		if(func == 6'b001000)
		begin 
			jrsel <=1;
			stall <=1;
			jsel <= 0;
			bsel <= 0;
		end
		else
		begin 
			jrsel <= 0;
			jsel <= 0;
			bsel <= 0;
			stall <= 0;
		end
	end
	
	default: 
	begin 
		jrsel <= 0;
		jsel <= 0;
		bsel <= 0;
		stall <= 0;
	end
	endcase
end
endmodule

	