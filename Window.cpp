#include "Window.h"

/*
	为了防止循环引用
	还是直接把main里的函数拿过来了
*/


void out_string1(int x, int y, std::string str)
{
	char buff[100];
	strcpy_s(buff, str.c_str());
	outtextxy(x, y, buff);
}

void Window::show()
{
	/*
		图片是70 130
	*/

	putimage(this->x + 130, this->y + 70, &this->img);

	std::string temp = "";
	std::string str = this->des;

	int count = 0;
	int now = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] & 0x80)
		{
			count += 2;
			temp += str[i];
			temp += str[++i];
		}
		else
		{
			count += 1;
			temp += str[i];
		}
		if (count >= this->maxLength)
		{
			count = 0;
			out_string1(180 + 20, 180 + 240 + 20 + now * 25, temp);
			now++;
			temp = "";
		}
	}
	if (count != 0)
	{
		count = 0;
		out_string1(180 + 20, 180 + 240 + 20 + now * 25, temp);
		now++;
		temp = "";
	}
}