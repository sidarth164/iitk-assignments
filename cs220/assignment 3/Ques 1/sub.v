module sub(
input wire [3:0] a,b,
output wire [3:0] sum,
output overflow);

wire [3:0] negb;
assign negb[3] = ~b[3];
assign negb[2:0] = b[2:0];
add subtracting (.a(a),.b(negb),.sum(sum),.overflow(overflow));

endmodule
