#include  <LEDA/geo/circle.h>
#include  <LEDA/geo/point.h>
#include <ctime>
#include  <iostream>
using  namespace  std;
using  leda::circle;
using  leda::point;
int n;

circle CircleWithTwoBoundaryPoints(point *p,int k,point b0, point b1){
	double a = (b1.xcoord() + b0.xcoord())/2;
	double b = (b1.ycoord() + b0.ycoord())/2;
	point x(a, b);
	circle m(x, b0);	
	for(int i = 0; i <= k; i++){
		if (m.outside(p[i])){
			m = circle(b1,b0,p[i]);
		}
	}
	return m;
}

circle CircleWithSingleBoundaryPoint(point *p,int j,point b0){
	double a = (p[0].xcoord() + b0.xcoord())/2;
	double b = (p[0].ycoord() + b0.ycoord())/2;
	point x(a, b);
	circle c1 = circle(x, p[0]);
	for(int i = 1; i <= j; i++){
		if (c1.outside(p[i])){
			c1 = CircleWithTwoBoundaryPoints(p,i-1,b0,p[i]);
		}
	}
	return c1;
}

int  main()
{	
	clock_t begin = clock();
	scanf("%d", &n);
	point p[n];
	circle c;
	for(int i = 0;  i < n; i++){
		double a,b;
		scanf ("%lf %lf", &a, &b);
		p[i] = point(a, b);
	}
	double a = (p[0].xcoord() + p[1].xcoord())/2;
	double b = (p[0].ycoord() + p[1].ycoord())/2;
	point x(a, b);
	c = circle(x, p[0]);
	for(int i = 2; i < n; i++){
		if (c.outside(p[i])){
			c = CircleWithSingleBoundaryPoint(p,i-1,p[i]);
		}
	}
	clock_t end = clock();
  	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	
	cout << n << " " << elapsed_secs << endl ;
	//point alpha = c.center();
	//cout << alpha.xcoord() << "," << alpha.ycoord() << endl ;
	//cout << c.radius() << endl ;
return  0;
}