module full_adder_8bit(a, b, sum);
    output [7:0] sum;
    input [7:0] a, b;
    supply0 zero;
    wire [7:0] carry;

    full_adder fa0(sum[0], carry[0],  a[0], b[0], zero);
    full_adder fa1(sum[1], carry[1],  a[1], b[1], carry[0]);
    full_adder fa2(sum[2], carry[2],  a[2], b[2], carry[1]);
    full_adder fa3(sum[3], carry[3],  a[3], b[3], carry[2]);
    full_adder fa4(sum[4], carry[4],  a[4], b[4], carry[3]);
    full_adder fa5(sum[5], carry[5],  a[5], b[5], carry[4]);
    full_adder fa6(sum[6], carry[6],  a[6], b[6], carry[5]);
    full_adder fa7(sum[7], carry[7],  a[7], b[7], carry[6]);
endmodule
