const double eps=1e-10;  
int dcmp(double x)  
{  
    if(fabs(x)<eps) return 0;  
    return x<0?-1:1;  
}  
  
struct Point  
{  
    double x,y;  
    Point(){}  
    Point(double x,double y):x(x),y(y){}  
};  
typedef Point Vector;  
Vector operator-(Point A,Point B)  
{  
    return Vector(A.x-B.x, A.y-B.y);  
}  
double Cross(Vector A,Vector B)  
{  
    return A.x*B.y-A.y*B.x;  
}  
bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2)  
{  
    double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1);  
    double c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);  
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;  
}  
  