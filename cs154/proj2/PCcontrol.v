module PCcontrol(op, resetPC);
input[5:0] op;
output resetPC;
reg resetPC;
always@(op)
begin
	if(op==6'b111101)
		resetPC<=1;
	else
		resetPC<=0;
end
endmodule
