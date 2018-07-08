module part4bit_8bit(in, out, part);
	input [7:0] in;
	input [7:0] out;
	input part;
	supply0 zero;
	myif if1(part, in[4], in[0], out[0]);
	myif if2(part, in[5], in[1], out[1]);
	myif if3(part, in[6], in[2], out[2]);
	myif if4(part, in[7], in[3], out[3]);
	assign out[4] = zero;
	assign out[5] = zero;
	assign out[6] = zero;
	assign out[7] = zero;
endmodule
