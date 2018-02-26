`timescale 1ns / 1ps
module main( push1, push2, push3, clk, in, cf, ZF, SF, sf_e, e, rs, rw, d, c, b, a);

output reg sf_e; // 1 LCD access (0 strataFlash access)
output reg e; // enable (1)
output reg rs;        // Register Select (1 data bits for R/W)
output reg rw;        // Read/Write 1/0
output reg d;        // 4th data bits (to form a nibble)
output reg c;        // 3rd data bits (to form a nibble)
output reg b;        // 2nd data bits (to form a nibble)
output reg a;        // 1st data bits (to form a nibble)

input wire push1, push2, push3, clk;
input [3:0] in;
output wire cf;

reg [2:0] op;
reg [26:0] count = 0;
reg [5:0] code;
reg refresh;
wire carry1,carry2;
reg [3:0] x, y;
reg [3:0] sum;
reg [15:0] hexout;
wire [3:0] sum1,sum2,sum3,sum4;
reg carry;

always @(posedge clk)
        begin
                if (push1 == 1)
                        x = in;
                if (push2 == 1)
                        y = in;
					 if (push3 == 1)
								op = in[2:0];
        end

AND x_and_y (.a(x),.b(y),.c(sum1));
OR x_or_y (.a(x),.b(y),.c(sum2));
add x_add_y (.a(x),.b(y),.sum(sum3),.overflow(carry1));
sub x_sub_y (.a(x),.b(y),.sum(sum4),.overflow(carry2));

always @(posedge clk)
			begin
					if (op == 2'b00)
						sum = sum1;

					if (op == 2'b01)
						sum = sum2;				
					
					if (op == 2'b10)
						begin
						sum = sum3;
						if(sum[3:0]==8)carry = 1'b0;
						else carry = carry1;
						end
					if (op == 2'b11)
						begin
						sum = sum4;
						if(sum[2:0]==0 & carry2==0)sum[3] = 1'b0;
						if(sum[3:0]==8)carry = 1'b0;
						else carry = carry2;
						end
			end

output ZF,SF;
reg zf,sf;

always @(posedge clk)
			begin
					zf=0;
					sf=0;
					if(sum == 4'b0000 & carry == 0)
							zf=1;
					if(op == 2'b10 | op == 2'b11)
					if(sum[3] == 1)
							sf=1;
			end

assign ZF=zf;
assign SF=sf;

always @ (posedge clk) begin
count <= count + 1;
	
	if(op==2'b00 | op==2'b01)
	     case (sum[3:0])
					 0: hexout = 16'h2320;
                1: hexout = 16'h2321;
                2: hexout = 16'h2322;
                3: hexout = 16'h2323;
                4: hexout = 16'h2324;
                5: hexout = 16'h2325;
                6: hexout = 16'h2326;
                7: hexout = 16'h2327;
					 8: hexout = 16'h2328;
                9: hexout = 16'h2329;
                10: hexout = 16'h2421;
                11: hexout = 16'h2422;
                12: hexout = 16'h2423;
                13: hexout = 16'h2424;
                14: hexout = 16'h2425;
                15: hexout = 16'h2426;
			endcase
	
	else begin
    if(sf==0)    
		 case (sum[2:0])
                0: hexout = 16'h2320;
                1: hexout = 16'h2321;
                2: hexout = 16'h2322;
                3: hexout = 16'h2323;
                4: hexout = 16'h2324;
                5: hexout = 16'h2325;
                6: hexout = 16'h2326;
                7: hexout = 16'h2327;
                default: hexout = 0;
       endcase
	 else begin
		  if(sum[3:0]==8)hexout = 16'h2328;
		    else case (sum[2:0])
                0: hexout = 16'h2320;
                1: hexout = 16'h2321;
                2: hexout = 16'h2322;
                3: hexout = 16'h2323;
                4: hexout = 16'h2324;
                5: hexout = 16'h2325;
                6: hexout = 16'h2326;
                7: hexout = 16'h2327;
                default: hexout = 0;
        endcase
		  end
	end
        case (count[26:21])
                0: code <= 6'h03;
                1: code <= 6'h03;
                2: code <= 6'h03;
                3: code <= 6'h02;
                4: code <= 6'h02;
                5: code <= 6'h08;
                6: code <= 6'h00;
                7: code <= 6'h06;
                8: code <= 6'h00;
                9: code <= 6'h0C;
                10: code <= 6'h00;
                11: code <= 6'h01;

                12: code <= hexout[13:8]; // Sum upper nibble 
                13: code <= hexout[5:0]; // Sum lowwe nibble
                 
                default: code <= 6'h10; 
        endcase

        refresh <= count[ 20 ];
        sf_e <= 1;
        e <= refresh; 
        rs <= code[5];
        rw <= code[4]; 
        d <= code[3];
        c <= code[2]; 
        b <= code[1];
        a <= code[0]; 
end

assign cf = carry;

endmodule

