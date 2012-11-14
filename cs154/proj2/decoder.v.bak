module decoder(reset, op, func, aluop, memwr, memtoreg, memrd, alusrc, btype, regdst, regwr, jal, stall);
input[5:0] op, func;
input stall;
output memwr, memtoreg, memrd, alusrc, regdst, regwr;
output[2:0] aluop;
output[1:0] btype;
output jal;
input reset;
reg memwr, memtoreg, memrd, alusrc, regdst, regwr;
reg[2:0] aluop;
reg[1:0] btype;
reg jal;
always@(op or func or reset)
begin
	if(reset==1 || stall == 1)
	begin
		aluop<=3'b000;
			memwr<=0;
			memtoreg<=0;
			memrd<=0;
			alusrc<=0;
			btype<=2'b00;
			regdst<=0;
			regwr<=0;
			jal<=0;
	end
	else
	casex({op, func})
		12'b000000001100:
		begin
			aluop<=3'b000;
			memwr<=0;
			memtoreg<=0;
			memrd<=0;
			alusrc<=0;
			btype<=2'b00;
			regdst<=1;
			regwr<=1;
			jal<=0;
		end
		12'b100000xxxxxx:
		begin
			aluop<=3'b000;
			memwr<=0;
			memtoreg<=0;
			memrd<=0;
			alusrc<=1;
			btype<=2'b00;
			regdst<=0;
			regwr<=1;
			jal<=0;
		end
		12'b000000011100:
		begin
			aluop<=001;
			memwr<=0;
			memtoreg<=0;
			memrd<=0;
			alusrc<=0;
			btype<=2'b00;
			regdst<=1;
			regwr<=1;
			jal<=0;
		end
		12'b000000100101:
		begin
			aluop<=3'b011;
			memwr<=0;
			memtoreg<=0;
			memrd<=0;
			alusrc<=0;
			btype<=2'b00;
			regdst<=1;
			regwr<=1;
			jal<=0;
		end
		12'b100111xxxxxx:
		begin
			aluop<=3'b011;
			memwr<=0;
			memtoreg<=0;
			memrd<=0;
			alusrc<=1;
			btype<=2'b00;
			regdst<=0;
			regwr<=1;
			jal<=0;
		end
		12'b001000xxxxxx:
		begin
			aluop<=3'b000;
			memwr<=0;
			memtoreg<=1;
			memrd<=1;
			alusrc<=1;
			btype<=2'b00;
			regdst<=0;
			regwr<=1;
			jal<=0;
		end
		12'b001010xxxxxx:
		begin
			aluop<=3'b000;
			memwr<=1;
			memtoreg<=0;
			memrd<=0;
			alusrc<=1;
			btype<=2'b00;
			regdst<=1;
			regwr<=0;
			jal<=0;
		end
		12'b001100xxxxxx:
		begin
			aluop<=3'b000;
			memwr<=0;
			memtoreg<=0;
			memrd<=0;
			alusrc<=1;
			btype<=2'b11;
			regdst<=0;
			regwr<=1;
			jal<=1;
		end
		12'b110001xxxxxx:
		begin
			aluop<=3'b011;
			memwr<=0;
			memtoreg<=0;
			memrd<=0;
			alusrc<=1;
			btype<=2'b10;
			regdst<=1'bx;
			regwr<=0;
			jal<=0;
		end
		12'b111101xxxxxx:
		begin
			aluop<=3'b000;
			memwr<=0;
			memtoreg<=0;
			memrd<=0;
			alusrc<=1;
			btype<=2'b11;
			regdst<=0;
			regwr<=1;
			jal<=0;
		end
		12'b000000001000:
		begin
			aluop<=3'bxxx;
			memwr<=0;
			memtoreg<=0;
			memrd<=1'bx;
			alusrc<=1'bx;
			btype<=2'b01;
			regdst<=1'bx;
			regwr<=0;
			jal<=0;
		end
		
	endcase
end
endmodule
