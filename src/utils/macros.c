int			redred(int	color)
{
	return (((int)color >> 16) & 0xFF);
}

int			greengreen(int color)
{
	return (((int)color >> 8) & 0xFF);
}

int			blueblue(int color)
{
	return ((int)color & 0xFF);
}

float		minn(float a, float b)
{
	return (((a)<(b))?(a):(b));
}