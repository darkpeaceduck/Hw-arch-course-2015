module shift_left1_8bit(in, out);
	input [7:0] in;
	output [7:0] out;
	supply0 zero;
	assign out[0] = zero;
	assign out[1] = in[0];
	assign out[2] = in[1];
	assign out[3] = in[2];
	assign out[4] = in[3];
	assign out[5] = in[4];
	assign out[6] = in[5];
	assign out[7] = in[6];
endmodule

