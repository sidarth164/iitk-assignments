# include <LEDA/geo/circle.h>
# include <LEDA/geo/point.h>
# include <iostream>
# include <time.h>
using namespace std ;
using leda :: circle ;
using leda :: point ;
double a,b,c;
int confirmer(double pts[][2], int n,circle c)
{
    point e;
    int i;
    for(i=0;i<n;i++)
    {
        a=pts[i][0];
        b=pts[i][1];
        e = point(a,b);
        if(c.outside(e))
            return 0;
    }
    return 1;
}
int main()
{
    clock_t start,end;
    double time_taken;
        int n,i,j,k;
        cin>>n;
        circle c,cmin;
        point p1,p2,p3;
        double pts[n][2],amax=1000.000000,rmin=1000000000.000000;
        for(i=0;i<n;i++)
        {
            cin>>pts[i][0];//(double)rand()/(double)(RAND_MAX/amax);
            cin>>pts[i][1];//=(double)rand()/(double)(RAND_MAX/amax);
        }
        start=clock();
        for(i=0;i<n-1;i++)
        {
            for(j=i+1;j<n;j++)
            {
                a=(pts[i][0]+pts[j][0])/2;
                b=(pts[i][1]+pts[j][0])/2;
                p1=point(a,b);
                a=pts[i][0];
                b=pts[i][1];
                p2=point(a,b);
                c=circle(p1,p2);
                if(confirmer(pts,n,c))
                {
                    if(rmin>c.radius())
                    {
                        rmin=c.radius();
                        cmin=c;
                    }
                }
            }
        }
        for(i=0;i<n-2;i++)
        {
            for(j=i+1;j<n-1;j++)
            {
                for(k=j+1;k<n;k++)
                {
                    a=pts[i][0];
                    b=pts[i][1];
                    p1=point(a,b);
                    a=pts[j][0];
                    b=pts[j][1];
                    p2=point(a,b);
                    a=pts[k][0];
                    b=pts[k][1];
                    p3=point(a,b);
                    c=circle(p1,p2,p3);
                    if(confirmer(pts,n,c))
                    {
                        if(rmin>c.radius())
                        {
                            rmin=c.radius();
                            cmin=c;
                        }
                    }
                }
            }
        }
        printf("%lf,%lf\n",cmin.center().xcoord(),cmin.center().ycoord());
        printf("%lf\n",rmin);
        end=clock();
        time_taken=((double)(end-start)/ CLOCKS_PER_SEC);
        //cout<<n<<" "<<time_taken<<endl;
        return 0;
}
