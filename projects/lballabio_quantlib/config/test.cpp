#include <ql/quantlib.hpp>
#include <iostream>

int main() {
    using namespace QuantLib;
    Date d1(1, January, 2020);
    Date d2 = d1 + Period(1, Years);
    Actual365Fixed dc;
    double yf = dc.yearFraction(d1, d2);
    std::cout << "Year fraction between " << d1 << " and " << d2 << " is " << yf << "\n";
    Handle<Quote> q(ext::make_shared<SimpleQuote>(100.0));
    std::cout << "SimpleQuote value: " << q->value() << "\n";
    return 0;
}
