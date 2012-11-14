module prehazard(regwr, borc, aluResult, rs, rt, a, b, data1, data2);
input regwr;	
input [4:0] borc, a, b;
input [7:0] aluResult, rs, rt;
output [7:0] data1, data2;
reg [7:0] data1, data2;

always @(regwr or borc or aluResult or rs or rt or a or b)
begin
	if(regwr==1)
	begin
		if(a==borc)
			 data1<=aluResult;
		else
			data1<=rs;
		if(b==borc)
			 data2<=aluResult;
		else
			 data2<=rs;
	end
else
begin
	 data1<=rs;
	 data2<=rt;
end
end
endmodule