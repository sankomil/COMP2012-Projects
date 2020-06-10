#include <iostream>
#include "picture.h"
#include "picture_pair.h"

using namespace std;

void test_Picture01()
{
	Picture p1 {"a45.txt"};

	p1.draw();
}

void test_Picture02()
{
	Picture p {"a45.txt"};

	p.frame('#', -3);
	p.frame('#', 0);
	p.frame('#', 3);
	p.draw();
}

void test_Picture03()
{
	Picture p1 {"a45.txt"};
	Picture p2 {p1};

	p1.frame('#', 1);
	p1.draw();

	p2.draw();
}

void test_PicturePair01()
{
	Picture p1 {"a45.txt"};
	Picture p2 {"b23.txt"};

	Picture_Pair pp {&p1, &p2};
	pp.draw();
}

void test_PicturePair02()
{
	Picture p1 {"a45.txt"};
	Picture p2 {"b23.txt"};

	Picture_Pair pp1 {&p1, &p2};
	Picture_Pair pp2 {pp1};

	pp2.draw();
}

void test_PicturePair03()
{
	Picture p1 {"a45.txt"};
	Picture p2 {"b23.txt"};

	Picture_Pair pp1 {&p1, &p2};

	cout << boolalpha << (pp1.get_picture(0) == &p1) << endl;
	cout << boolalpha << (pp1.get_picture(1) == &p2) << endl;

	cout << boolalpha << (pp1.get_picture(-1) == nullptr) << endl;
	cout << boolalpha << (pp1.get_picture(3) == nullptr) << endl;
}

void test_PicturePair04()
{
	Picture p1 {"b23.txt"};
	Picture p2 {"a45.txt"};

	Picture_Pair pp {&p1, &p2};
	Picture p3 {pp};

	p3.frame('#', 2);
	p3.draw();
}

void test_PicturePair05()
{
	Picture p1 {"a45.txt"};
	Picture p2 {"b23.txt"};

	Picture_Pair pp1 = {&p1, nullptr};
	Picture_Pair pp2 = {nullptr, &p2};

	pp1.draw();
	pp2.draw();
}

void test_PicturePair06()
{
	Picture_Pair pp = {nullptr, nullptr};

	Picture p1 {pp};
	p1.draw();
}

void test_PicturePair07()
{
	Picture p1 {"a45.txt"};
	Picture p2 {"b23.txt"};

	Picture_Pair pp1 = {&p1, nullptr};
	Picture_Pair pp2 = {nullptr, &p2};

	Picture p3 = {pp1};
	Picture p4 = {pp2};

	p3.draw();
	p4.draw();
}

void test_Banner()
{
	Picture c {"c.txt"};
	Picture o {"o.txt"};
	Picture m {"m.txt"};
	Picture p {"p.txt"};

	Picture _2 {"2.txt"};
	Picture _0 {"0.txt"};
	Picture _1 {"1.txt"};

	Picture_Pair ppco {&c, &o};
	Picture_Pair ppmp {&m, &p};
	Picture co {ppco};
	Picture mp {ppmp};

	Picture_Pair pp20 {&_2, &_0};
	Picture_Pair pp12 {&_1, &_2};
	Picture _20 {pp20};
	Picture _12 {pp12};

	Picture_Pair ppcomp {&co, &mp};
	Picture comp {ppcomp};

	Picture_Pair pp2012 {&_20, &_12};
	Picture _2012 {pp2012};

	Picture_Pair ppcomp2012 {&comp, &_2012};
	ppcomp2012.draw();
}

int main(int argc, char **argv)
{
	cout << "test_Picture01" << endl;
	test_Picture01();
	cout << endl;

	cout << "test_Picture02" << endl;
	test_Picture02();
	cout << endl;

	cout << "test_Picture03" << endl;
	test_Picture03();
	cout << endl;

	cout << "test_PicturePair01" << endl;
	test_PicturePair01();
	cout << endl;

	cout << "test_PicturePair02" << endl;
	test_PicturePair02();
	cout << endl;

	cout << "test_PicturePair03" << endl;
	test_PicturePair03();
	cout << endl;

	cout << "test_PicturePair04" << endl;
	test_PicturePair04();
	cout << endl;

	cout << "test_PicturePair05" << endl;
	test_PicturePair05();
	cout << endl;

	cout << "test_PicturePair06" << endl;
	test_PicturePair06();
	cout << endl;

	cout << "test_PicturePair07" << endl;
	test_PicturePair07();
	cout << endl;

	cout << "test_Banner" << endl;
	test_Banner();
	cout << endl;

	return 0;
}
