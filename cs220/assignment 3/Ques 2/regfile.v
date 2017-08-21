`timescale 1ns / 1ps

module regfile(clk,rota,rotb, rotc,rotd,rotary,sw,o1,o2);
output reg [3:0] o1; 
output reg [3:0] o2;
input wire clk, rota,rotb,rotc,rotd,rotary;
input wire [3:0] sw; 
reg [3:0] WR,WData,WEnable;
integer RR1,RR2;
reg [3:0] registers[0:15];
always @(rota or rotb or rotc or rotd or rotary)
begin
        if (rota)
        begin
                 RR1<=sw;
					  o1<=registers[RR1];
        end
        else if(rotb)
        begin
                RR2<=sw;
					 o2<=registers[RR2];
        end
		  else if(rotc)
        begin
                WR<=sw;
        end
		  else if(rotd)
        begin
                WData<=sw;
        end
		  
		  else if(rotary)
        begin
                WEnable<=sw;
        end
end


always @(posedge clk)
begin
	if(WEnable)
	begin
		registers[WR]=WData;
	end
end

endmodule
