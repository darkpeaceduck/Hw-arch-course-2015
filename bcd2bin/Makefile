default: bcd2bin

bcd2bin: bcd2bin_test.v full_adder.v  myif.v bcd2bin.v  half_adder.v  part4bit_8bit.v full_adder_8bit.v  shift_left1_8bit.v
	iverilog -o $@ $^

.PHONY: clean
clean:
	rm -f bcd2bin
