module spilt(instr, op, a, b, c, d, func);
	input[31:0] instr;
	output[4:0] a, b, c;
	output[5:0] op, func;
	output[15:0] d;
	assign a=instr[25:21];
	assign b=instr[20:16];
	assign c=instr[15:11];
	assign d=instr[15:0];
	assign func=instr[5:0];
	assign op=instr[31:26];
endmodule
