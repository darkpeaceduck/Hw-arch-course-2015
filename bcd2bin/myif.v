module myif(condition, case_true, case_false, out);
	input condition;
	input case_false;
	input case_true;
	output out;
	assign out = (condition & case_true) || (!condition & case_false);
endmodule
