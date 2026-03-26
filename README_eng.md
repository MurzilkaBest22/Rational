DESCRIPTION
Rational is a C++ library that implements rational numbers as irreducible fractions (numerator/denominator). It provides arithmetic operations and mathematical functions for rational arguments.

FEATURES
Rational class with constructors from integers or numerator/denominator pairs.
Reduction to irreducible form (Euclidean algorithm).
Operators: +, -, *, /, compound assignments, comparisons.
Method toLongDouble() for conversion to long double.
Mathematical functions: ln, lg, lb, pow, sqrt, cbrt, trigonometric, hyperbolic, and inverse trigonometric functions.
Domain checking (e.g., for logarithms, even‑root arguments).

INSTALLATION AND BUILD
The library consists of rational.h and rational.cpp. To use it in your project:
Copy the Rational folder into your project.
Add rational.cpp to your source files.
Include the header:

#include "Rational/rational.h"

Use the namespace rational.
If you prefer a static library, compile rational.cpp into Rational.lib and link it.

DEPENDENCIES
RealUtils (for convenient function names).

LICENSE
MIT License. See the LICENSE file.

AUTHOR
Mikhail D. Sychev
Email: murzilkabest@icloud.com
Telegram: @Murz1k22
