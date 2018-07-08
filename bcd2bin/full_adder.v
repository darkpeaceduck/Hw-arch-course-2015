module full_adder(sum, carry, a, b, carry_in);
    input a, b, carry_in;
    output sum, carry;

    wire half_sum, carry1, carry2;

    assign carry = carry1 | carry2;
    half_adder add1(half_sum, carry1, a, b);
    half_adder add2(sum, carry2, half_sum, carry_in);
endmodule
