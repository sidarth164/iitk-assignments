# include <LEDA/geo/circle.h>
# include <LEDA/geo/point.h>
# include <iostream>
# include <time.h>
using namespace std ;
using leda :: circle ;
using leda :: point ;
double a,b,c;
circle CircleWithTwoBoundaryPoints(point *p, int k, point b0,point b1)
{
    a = (b0.xcoord()+b1.xcoord())/2;
    b = (b0.ycoord()+b1.ycoord())/2;
    point e=point(a,b);
    circle c1(e,b0);
    int i;
    for(i=0;i<=k;i++)
    {
        if(c1.outside(p[i]))
            c1=circle(b0,b1,p[i]);
    }
    return c1;
}
circle CircleWithSingleBoundaryPoint(point* p, int j,point b0)
{
    point temp;
    a =(p[0].xcoord()+b0.xcoord())/2;
    b =(p[0].ycoord()+b0.ycoord())/2;
    temp = point(a,b);
    circle d=circle(temp,b0);
    int i;
    for(i=1;i<=j;i++)
    {

        if( d.outside(p[i]))
            d=CircleWithTwoBoundaryPoints(p,i-1,b0,p[i]);
    }
    return d;
}
int main()
{
    clock_t start=clock(),end;
    double time_taken;
        int n,i;
        cin>>n;
        circle c;
        point p[n];
        point p1;
        //double amax=1000.000000;
        for(i=0;i<n;i++)
        {
            /*a=(double)rand()/(double)(RAND_MAX/amax);
              b=(double)rand()/(double)(RAND_MAX/amax);*/
            cin>>a>>b;
            p[i]=point(a,b);
        }
        a=(p[0].xcoord()+p[1].xcoord())/2;
        b=(p[0].ycoord()+p[1].ycoord())/2;
        p1=point(a,b);
        c=circle(p1,p[1]);
        for(i=2;i<n;i++)
        {
            if( c.outside(p[i]))
                c=CircleWithSingleBoundaryPoint(p, i-1, p[i]);
        }
        printf("%lf,%lf\n",c.center().xcoord(),c.center().ycoord());
        printf("%lf\n",c.radius());
        end=clock();
        time_taken=((double)(end-start)/ CLOCKS_PER_SEC);
        //cout<<n<<" "<<time_taken<<endl;
        //cout<<time_taken<<endl;
        return 0;
}