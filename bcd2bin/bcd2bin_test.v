module bcd2bin_test;
    reg [7:0] in;
    wire [7:0] out;

    integer i, j;

    bcd2bin c(out, in);

    initial begin
        for (i = 0; i != 10; i = i + 1) begin
            for (j = 0; j != 10; j = j + 1) begin
                in[3:0] = j;
                in[7:4] = i;
                #1 $display("%d%d (%b) == %d (%b)", i, j, in, out, out);
            end
        end
    end
endmodule
