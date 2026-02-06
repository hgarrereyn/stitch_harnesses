#include <CGAL/Simple_cartesian.h>
#include <CGAL/convex_hull_2.h>
#include <vector>
#include <iostream>

int main() {
    typedef CGAL::Simple_cartesian<double> K;
    typedef K::Point_2 Point_2;

    std::vector<Point_2> points;
    points.push_back(Point_2(0, 0));
    points.push_back(Point_2(1, 0));
    points.push_back(Point_2(0, 1));
    points.push_back(Point_2(0.2, 0.2));
    points.push_back(Point_2(0.8, 0.1));

    std::vector<Point_2> result;
    CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(result));

    std::cout << "Hull size: " << result.size() << "\n";
    for(const auto& p : result) {
        std::cout << p << "\n";
    }
    return 0;
}
