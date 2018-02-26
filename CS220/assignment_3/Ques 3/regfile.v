`timescale 1ns / 10ps
module regfile (
	input wire clk, w_enable,
	input wire [3:0] rr1, rr2,
	input wire [3:0] wr, wdata,
	output reg [3:0] out1, out2
);
	reg [3:0] r0;
	reg [3:0] r1;
	reg [3:0] r2;
	reg [3:0] r3;
	reg [3:0] r4;
	reg [3:0] r5;
	reg [3:0] r6;
	reg [3:0] r7;
	reg [3:0] r8;
	reg [3:0] r9;
	reg [3:0] r10;
	reg [3:0] r11;
	reg [3:0] r12;
	reg [3:0] r13;
	reg [3:0] r14;
	reg [3:0] r15;

	always @(posedge clk)
	begin
		case(rr1)
		0: out1 = r0;
		1: out1 = r1;
		2: out1 = r2;
		3: out1 = r3;
		4: out1 = r4;
		5: out1 = r5;
		6: out1 = r6;
		7: out1 = r7;
		8: out1 = r8;
		9: out1 = r9;
		10: out1 = r10;
		11: out1 = r11;
		12: out1 = r12;
		13: out1 = r13;
		14: out1 = r14;
		15: out1 = r15;
		default: out1 = r0;
		endcase
		case(rr2)
		0: out2 = r0;
		1: out2 = r1;
		2: out2 = r2;
		3: out2 = r3;
		4: out2 = r4;
		5: out2 = r5;
		6: out2 = r6;
		7: out2 = r7;
		8: out2 = r8;
		9: out2 = r9;
		10: out2 = r10;
		11: out2 = r11;
		12: out2 = r12;
		13: out2 = r13;
		14: out2 = r14;
		15: out2 = r15;
		default: out2 = r0;
		endcase
		if (w_enable == 1)
		begin
			case(wr)
			0: r0 = wdata;
			1: r1 = wdata;
			2: r2 = wdata;
			3: r3 = wdata;
			4: r4 = wdata;
			5: r5 = wdata;
			6: r6 = wdata;
			7: r7 = wdata;
			8: r8 = wdata;
			9: r9 = wdata;
			10: r10 = wdata;
			11: r11 = wdata;
			12: r12 = wdata;
			13: r13 = wdata;
			14: r14 = wdata;
			15: r15 = wdata;
			default: r0 = wdata;
			endcase
		end
	end
endmodule
