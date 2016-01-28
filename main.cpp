#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <iomanip>
#define SQR(x) ((x)*(x))


using namespace std;
struct Point{
	Point(long long _x, long long _y){
		x = _x;
		y = _y;
	}
	friend bool operator<(Point a, Point b);
	long long x;
	long long y;
};

bool operator<(Point a, Point b){
	return a.x < b.x;
}
typedef vector< Point > vpii;
struct foo{
	bool operator()(Point a, Point b){
		return a.y < b.y;
	}
};

long double dist(Point p1, Point p2){
	return sqrt(SQR(p1.x - p2.x) + SQR(p1.y - p2.y));
}

long double perim(Point p1, Point p2, Point p3){
	return dist(p1, p2) + dist(p2, p3) + dist(p3, p1);
}

long double min_perimetr(vpii::iterator a, vpii::iterator b){
	if (abs(a - b) < 3){
		return 1E100;
	}
	if (abs(a - b) == 3){
		return perim(*a, *(a + 1), *(a + 2));
	}
	vpii::iterator mid = a + abs(a - b) / 2;
	long double h = min(min_perimetr(a, mid), min_perimetr(mid, b));
	vpii temp;
	for (vpii::iterator i = a; i != b; i++){
		if (abs((*mid).x - (*i).x) <= h / 2){
			temp.push_back(*i);
		}
	}
	sort(temp.begin(), temp.end(), foo());
	long double answer = h;
	for (vpii::iterator i = temp.begin(); i != temp.end(); i++){
		vpii::iterator m = i + 1;
		for (vpii::iterator j = i + 1; j != temp.end(); j++){
			if (abs((*i).y - (*j).y) <= h / 2){
				for (vpii::iterator k = j + 1; k != temp.end(); k++){
					if (abs((*i).y - (*k).y) <= h / 2){
						answer = min(answer, perim(*j, *k, *i));
					}
					else{
						break;
					}
				}
			}
			else{
				break;
			}
		}
	}
	return answer;
}


vector<Point> a;

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		long long x, y;
		cin >> x >> y;
		a.push_back(Point(x, y));
	}
	sort(a.begin(), a.end());
	cout << fixed << setprecision(8) << min_perimetr(a.begin(), a.end()) << endl;;
	return 0;
}
