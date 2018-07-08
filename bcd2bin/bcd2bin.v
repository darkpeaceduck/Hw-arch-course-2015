module bcd2bin(out, in);
    input [7:0] in;
    output [7:0] out;
    wire [7:0] digit1;
    wire [7:0] digit2;
    wire [7:0] digit2_sh1;
    wire [7:0] digit2_sh2;
    wire [7:0] digit2_sh3;
    wire [7:0] part_sum;
    supply0 zero;
    supply1 one;
    part4bit_8bit p1(in, digit1, zero);
    part4bit_8bit p2(in, digit2, one);
    shift_left1_8bit sh1(digit2, digit2_sh1);
    shift_left1_8bit sh2(digit2_sh1, digit2_sh2);
    shift_left1_8bit sh3(digit2_sh2, digit2_sh3);
    full_adder_8bit ad1(digit1, digit2_sh1, part_sum);
    full_adder_8bit ad2(part_sum, digit2_sh3, out);
endmodule
