module splitter(op, a,b,c,d, func, instr);
	output[5:0] op;
	output[5:0] func;
	output[4:0] a,b,c;
	output[15:0] d;
	input[31:0] instr;
	assign d = instr[15:0];
	assign a = instr[25:21];
	assign b = instr[20:16];
	assign c = instr[15:11];
	assign op = instr[31:26];
	assign func = instr[5:0];
endmodule
