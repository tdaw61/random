module forward(MEM/WB.Regwrite, MEM/WB.RegisterRd, clock, RS, RT, forwardA, forwardB)
input MEM/WB.Regwrite;
input MEM/WB.RegisterRd;
input RS;
input RT;
output forwardA;
output forwardB;
reg MEM/WB.Regwrite;
reg MEM/WB.RegisterRd;
reg RS;
reg RT;
reg forwardA;
reg forwardB;

always @(clock)
begin 
	if((MEM/WB.Regwrite != 0) && (MEM/WB.RegisterRd != 0) && (MEM/WB.RegisterRd == RS))
	begin 
		forwardA <= 2'b1;
    end 
    if((MEM/WB.Regwrite != 0) && (MEM/WB.RegisterRd != 0) && (MEM/WB.RegisterRd == RT))
	begin 
		forwardB <= 2'b1;
    end 
    if((
    else
	begin
		forwardA <= 2'b0;
		forwardB <= 2'b0;
	end
end 
endmodule 