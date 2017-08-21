module add(
input wire [3:0] a,b,
output wire [3:0] sum,
output overflow);

reg [3:0] sa,sb,ssum;
reg carry;

reg [4:0] t;

always @(a,b)
begin
        sa=a;
        sb=b;

        if(sa[3] ==0 & sb[3] == 0)
        begin
                t[3:0] = a[2:0]+b[2:0];
                ssum = {sa[3], t[2:0]};
                carry = t[3];
        end

        else if((sa[3] == 1 & sb[3]==0)| (sa[3]==0 & sb[3]==1))
        begin
                t[3:0]=sa+sb;
                carry=0;
                ssum=t;
        end

        else
        begin
                t=sa+sb;
                carry=~t[3];
                ssum={t[4],t[2:0]};
        end
end

assign sum=ssum;
assign overflow=carry;

endmodule

