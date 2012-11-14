module truncate(instr, out);
	input[15:0] instr;
	output[7:0] out;
	assign out=instr[7:0];
endmodule
