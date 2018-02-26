`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:07:10 04/03/2017 
// Design Name: 
// Module Name:    alu4 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module alu4 (
			input clk,
	    input wire [1:0]  ALUctl,
	    input wire [3:0]  A,B,
	    output wire [3:0] ALUOut,
	    output wire       ZF,
	    output wire       CF,
	    output 	      SF
);
	
   reg [4:0] 		      actualOut;
	reg cf,zf,sf;
   assign ALUOut = actualOut;
   assign ZF = zf;
   assign CF = cf;
   assign SF = sf;
   reg [3:0] nb;
	always @(posedge clk) //reevaluate if these change
     case (ALUctl)
       0:actualOut = A & B;
       1:actualOut = A | B;
       2:begin 
			actualOut = $signed(A) + $signed(B);
			sf=($signed(actualOut) < 0);
			zf= ($signed(actualOut)==0);
			cf=($signed(actualOut) > 7 || $signed(actualOut) < -8);
			if(A[3]==0 & B[3]==0)
			actualOut[3:0]={A[3],actualOut[2:0]};
			
			else if(A[3]==1 &B[3]==1)
			actualOut[3:0]={actualOut[4],actualOut[2:0]};
			end
       3:begin 
			nb=~B+1;
			actualOut = $signed(A) + $signed(nb);
			sf=($signed(actualOut) < 0);
			zf= ($signed(actualOut)==0);
			cf=($signed(actualOut) > 7 || $signed(actualOut) < -8);
			if(A[3]==0 & nb[3]==0)
			actualOut[3:0]={A[3],actualOut[2:0]};
			
			else if(A[3]==1 &nb[3]==1)
			actualOut[3:0]={actualOut[4],actualOut[2:0]};
			end
       default: actualOut = 0;
     endcase
endmodule
