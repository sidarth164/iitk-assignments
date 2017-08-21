`timescale 1ns/10ps
module processor(input wire [2:0] opcode,
		 input wire [3:0] inp1, inp2,
		 input wire clk,
		 input wire reg_w_enable,
		 output wire SF, ZF, CF,
		 output wire [3:0] result,
		 output wire invalid_op
		 );
   wire [3:0] 		     out1, out2;
   assign invalid_op = (opcode != 3'b100) &&
		       (opcode != 3'b000) &&
		       (opcode != 3'b001) &&
		       (opcode != 3'b010) &&
		       (opcode != 3'b011);
   assign w_enable = !invalid_op && opcode[2] && reg_w_enable;
   regfile my_reg(.clk(clk), .w_enable(w_enable),
		  .rr1(inp1), .rr2(inp2),
		  .wr(inp1), .wdata(inp2),
		  .out1(out1), .out2(out2)
		  );
   alu4 my_alu(.ALUctl(opcode[1:0]),
	       .A(out1), .B(out2),
	       .ZF(ZF), .CF(CF), .SF(SF),
	       .ALUOut(result),.clk(clk)
	       );
endmodule
