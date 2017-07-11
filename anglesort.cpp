/* sort points clockwisely*/

struct points{
	int x,y;
	int getquad()const
	{
		if(x < xt && y >= yt)
		{
			return 1;
		}
		if(x >= xt && y> yt)
		{
			return 2;
		}
		if(x > xt && y <= yt)
		{
			return 3;
		}
		else return 4;
	}
	bool operator<(const points &ps)const
	{
		int quad1,quad2;
		quad1 = this->getquad();
		quad2 = ps.getquad();
		if(quad1 != quad2)
		{
			return quad1 < quad2;
		}
		int x1 = x-xt,y1 = y - yt;
		int x2 = ps.x- xt,y2 = ps.y - yt;
		int cp = x1*y2 - x2*y1;
		if(cp < 0)
			return true;
		else return false;
	}
}