#ifndef TP3_STRUCTURES_HEADER
#define TP3_STRUCTURES_HEADER

#include <iostream>
#include <vector>


/* Common Structures */
class Point {
public:
	long x,y;
	Point() {this->x = 0; this->y = 0;}
	Point(int x, int y) { this->x = x; this->y = y;}
	Point copy() {return Point(this->x, this->y);}

	Point operator+(Point const& p2) const {return Point(this->x + p2.x, this->y + p2.y);}
	Point operator-(Point const& p2) const {return Point(this->x - p2.x, this->y - p2.y);}
	Point operator*(int k) const {return Point(this->x * k, this->y * k);}
	Point operator/(int k) const {return Point(this->x / k, this->y / k);}
	Point operator-() const {return Point(-this->x, -this->y);}

	Point& operator+=(Point const& p2) {this->x += p2.x; this->y += p2.y; return *this;}
	Point& operator-=(Point const& p2) {this->x -= p2.x; this->y -= p2.y; return *this;}
	Point& operator*=(int k) {this->x *= k; this->y *= k; return *this;}
	Point& operator/=(int k) {this->x /= k; this->y /= k; return *this;}
	void pr() const {printf("(%ld, %ld)\n", this->x, this->y);}
};

int distance(Point const& p1, Point const& p2);

#endif /* TP3_STRUCTURES_HEADER */
