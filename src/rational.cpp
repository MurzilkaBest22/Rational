#include "real_utils.h"
#include "rational.h"

namespace rational {

	// Приведение к виду несократимой дроби
	void Rational::normalize() {
		if (den == 0) {
			throw std::domain_error("Rational: denominator cannot be zero");
		}
		// Приводим знаменатель к положительному
		if (den < 0) {
			num = -num;
			den = -den;
		}
		if (num == 0) {
			den = 1;
			return;
		}

		// Вычисление НОД (a) между модулем num и величиной den (положительной после приведения знаменателя в условном операторе)
		int64_t a = (num < 0) ? -num : num;
		int64_t b = den;
		while (b != 0) {
			int64_t t = a % b;
			a = b;
			b = t;
		}

		// Деление числителя и знаменателя на их НОД (a) для приведения к виду несократимой дроби
		num /= a;
		den /= a;
	}

	// Перегрузки конструктора
	Rational::Rational() : num(0), den(1) {}
	Rational::Rational(int64_t n) : num(n), den(1) {}
	Rational::Rational(int64_t n, int64_t d) : num(n), den(d) {
		normalize();
	}

	// Проверка чётности числителя
	bool Rational::numeratorIsEven() const {
		return num % 2 == 0;
	}
	bool Rational::numeratorIsOdd() const {
		return num % 2 == 1;
	}
	// Проверка чётности знаменателя
	bool Rational::denominatorIsEven() const {
		return den % 2 == 0;
	}
	bool Rational::denominatorIsOdd() const {
		return den % 2 == 1;
	}

	// Преобразование в тип long double
	long double Rational::toLongDouble() const {
		return static_cast<long double>(num) / static_cast<long double>(den);
	}

	// Операторы сравнения
	bool Rational::operator== (const Rational& other) const {
		return num == other.num && den == other.den; // Так как при инициализации оба числа приводятся к виду несократимой дроби
	}
	bool Rational::operator!= (const Rational& other) const {
		return num != other.num || den != other.den; // Так как при инициализации оба числа приводятся к виду несократимой дроби
	}
	bool Rational::operator> (const Rational& other) const {
		return static_cast<long double>(num) / static_cast<long double>(den) > static_cast<long double>(other.num) / static_cast<long double>(other.den);
	}
	bool Rational::operator>= (const Rational& other) const {
		return static_cast<long double>(num) / static_cast<long double>(den) >= static_cast<long double>(other.num) / static_cast<long double>(other.den);
	}
	bool Rational::operator< (const Rational& other) const {
		return static_cast<long double>(num) / static_cast<long double>(den) < static_cast<long double>(other.num) / static_cast<long double>(other.den);
	}
	bool Rational::operator<= (const Rational& other) const {
		return static_cast<long double>(num) / static_cast<long double>(den) <= static_cast<long double>(other.num) / static_cast<long double>(other.den);
	}

	// Арифметические операторы с возвращением объекта класса Rational
	Rational operator+(const Rational& r1, const Rational& r2) {
		return Rational(r1.num * r2.den + r2.num * r1.den, r1.den * r2.den); // Так как знаменатели натуральны
	}
	long double operator+(long double p, const Rational& r) {
		return p + r.toLongDouble();
	}
	long double operator+(const Rational& r, long double p) {
		return p + r.toLongDouble();
	}

	Rational operator-(const Rational& r1, const Rational& r2) {
		return Rational(r1.num * r2.den - r2.num * r1.den, r1.den * r2.den); // Так как знаменатели натуральны
	}
	long double operator-(long double p, const Rational& r) {
		return p - r.toLongDouble();
	}
	long double operator-(const Rational& r, long double p) {
		return r.toLongDouble() - p;
	}

	Rational operator*(const Rational& r1, const Rational& r2) {
		return Rational(r1.num * r2.num, r1.den * r2.den); // Так как знаменатели натуральны
	}
	long double operator*(long double p, const Rational& r) {
		return p * r.toLongDouble();
	}
	long double operator*(const Rational& r, long double p) {
		return p * r.toLongDouble();
	}

	Rational operator/(const Rational& r1, const Rational& r2) {
		// Проверка возможности провести деление
		if (r2.num == 0) {
			throw std::runtime_error("Division by zero in Rational::operator/");
		}
		return Rational(r1.num * r2.den, r1.den * r2.num); // Так как знаменатели натуральны
	}
	long double operator/(long double p, const Rational& r) {
		// Проверка возможности провести деление
		if (r.num == 0) {
			throw std::runtime_error("Division by zero in Rational::operator/");
		}
		return p / r.toLongDouble();
	}
	long double operator/(const Rational& r, long double p) {
		// Проверка возможности провести деление
		if (p == 0.0) {
			throw std::runtime_error("Division by zero in Rational::operator/");
		}
		return r.toLongDouble() / p;
	}

	// Составные операторы присваивания
	Rational& Rational::operator+=(const Rational& other) {
		num = num * other.den + den * other.num;
		den *= other.den;
		normalize();
		return *this;
	}
	Rational& Rational::operator-=(const Rational& other) {
		num = num * other.den - den * other.num;
		den *= other.den;
		normalize();
		return *this;
	}
	Rational& Rational::operator*=(const Rational& other) {
		num *= other.num;
		den *= other.den;
		normalize();
		return *this;
	}
	Rational& Rational::operator/=(const Rational& other) {
		// Проверка возможности провести деление
		if (other.num == 0) {
			throw std::runtime_error("Division by zero in Rational::operator/=");
		}
		num *= other.den;
		den *= other.num;
		normalize();
		return *this;
	}

	// Унарный минус
	Rational Rational::operator-() const {
		return Rational(-num, den);
	}

	// Экспонента
	long double exp(const Rational& r) {
		return std::exp(r.toLongDouble());
	}

	// Логарифмы
	long double log(long double p, const Rational& r) {
		if ((p <= 0.0) || (p == 1.0) || (r <= Rational(0, 1))) {
			throw std::domain_error("Exceeding the range of allowable values of the rational logarithm");
		}
		return ::log(p, r.toLongDouble());
	}
	long double log(const Rational& r, long double p) {
		if ((r <= Rational(0, 1)) || (r == Rational(1, 1)) || (p <= 0)) {
			throw std::domain_error("Exceeding the range of allowable values of the rational logarithm");
		}
		return ::log(r.toLongDouble(), p);
	}
	long double ln(const Rational& r) {
		if (r <= Rational(0, 1)) {
			throw std::domain_error("Exceeding the range of allowable values of the rational logarithm");
		}
		return ::ln(r.toLongDouble());
	}
	long double log(const Rational& r) {
		if (r <= Rational(0, 1)) {
			throw std::domain_error("Exceeding the range of allowable values of the rational logarithm");
		}
		return ::ln(r.toLongDouble());
	}
	long double lg(const Rational& r) {
		if (r <= Rational(0, 1)) {
			throw std::domain_error("Exceeding the range of allowable values of the rational logarithm");
		}
		return ::lg(r.toLongDouble());
	}
	long double lb(const Rational& r) {
		if (r <= Rational(0, 1)) {
			throw std::domain_error("Exceeding the range of allowable values of the rational logarithm");
		}
		return ::lb(r.toLongDouble());
	}
	long double log(const Rational& r1, const Rational& r2) {
		if ((r1 <= Rational(0, 1)) || (r1 == Rational(1, 1)) || (r2 <= Rational(0, 1))) {
			throw std::domain_error("Exceeding the range of allowable values of the rational logarithm");
		}
		return ::log(r1.toLongDouble(), r2.toLongDouble());
	}

	// Возведение в степень
	long double sq(const Rational& r) {
		return ::sq(r.toLongDouble());
	}
	long double cb(const Rational& r) {
		return ::cb(r.toLongDouble());
	}
	long double pow(const Rational& r, int p) {
		if ((r == Rational(0, 1)) && (p <= 0)) {
			throw std::domain_error("Exceeding the domain of allowable values of a rational power function");
		}
		return std::pow(r.toLongDouble(), p);
	}
	long double pow(const Rational& r, int64_t p) {
		if ((r == Rational(0, 1)) && (p <= 0)) {
			throw std::domain_error("Exceeding the domain of allowable values of a rational power function");
		}
		return std::pow(r.toLongDouble(), p);
	}
	long double pow(const Rational& r1, const Rational& r2) {
		if ((r1 == Rational(0, 1)) && (r2 <= Rational(0, 1))) {
			throw std::domain_error("Exceeding the domain of allowable values of a rational power function");
		}
		if ((r1 < Rational(0, 1)) && r2.denominatorIsEven()) {
			throw std::domain_error("Exceeding the domain of allowable values of a rational power function");
		}
		return std::pow(r1.toLongDouble(), r2.toLongDouble());
	}
	long double pow(long double p, const Rational& r) {
		if ((p == 0) && (r <= Rational(0, 1))) {
			throw std::domain_error("Exceeding the domain of allowable values of a rational power function");
		}
		if ((p < 0) && r.denominatorIsEven()) {
			throw std::domain_error("Exceeding the domain of allowable values of a rational power function");
		}
		return std::pow(p, r.toLongDouble());
	}
	long double pow(const Rational& r, long double p) {
		if (r <= Rational(0, 1)) {
			throw std::domain_error("Exceeding the domain of allowable values of a rational power function");
		}
		return std::pow(r.toLongDouble(), p);
	}

	// Извлечение корня

	long double sqrt(const Rational& r) {
		if (r < Rational(0, 1)) {
			throw std::domain_error("Exceeding the domain of valid values of the rational root function");
		}
		return std::sqrt(r.toLongDouble());
	}
	long double cbrt(const Rational& r) {
		return std::cbrt(r.toLongDouble());
	}
	long double rt(const Rational& r1, const Rational& r2) {
		if ((r1 == Rational(0, 1)) && (r2 <= Rational(0, 1))) {
			throw std::domain_error("Exceeding the domain of allowable values of the rational root function");
		}
		if ((r1 < Rational(0, 1)) && r2.numeratorIsEven()) {
			throw std::domain_error("Exceeding the domain of allowable values of the rational root function");
		}
		return ::rt(r1.toLongDouble(), r2.toLongDouble());
	}
	long double rt(long double p, const Rational& r) {
		if ((p == 0) && (r <= Rational(0, 1))) {
			throw std::domain_error("Exceeding the domain of allowable values of the rational root function");
		}
		if ((p < 0) && r.numeratorIsEven()) {
			throw std::domain_error("Exceeding the domain of allowable values of the rational root function");
		}
		return ::rt(p, r.toLongDouble());
	}
	long double rt(const Rational& r, long double p) {
		if (r <= Rational(0, 1)) {
			throw std::domain_error("Exceeding the domain of allowable values of the rational root function");
		}
		return ::rt(r.toLongDouble(), p);
	}

	// Тригонометрические функции
	long double sin(const Rational& r) {
		return std::sin(r.toLongDouble());
	}
	long double cos(const Rational& r) {
		return std::cos(r.toLongDouble());
	}
	long double tg(const Rational& r) {
		if (std::cos(r.toLongDouble()) == 0.0) {
			throw std::domain_error("Exceeding the domain of valid values of the rational tangent function");
		}
		return ::tg(r.toLongDouble());
	}
	long double ctg(const Rational& r) {
		if (std::sin(r.toLongDouble()) == 0.0) {
			throw std::domain_error("Exceeding the domain of valid values of the rational cotangent function");
		}
		return ::ctg(r.toLongDouble());
	}
	long double sec(const Rational& r) {
		if (std::cos(r.toLongDouble()) == 0.0) {
			throw std::domain_error("Exceeding the domain of valid values of the rational secant function");
		}
		return ::sec(r.toLongDouble());
	}
	long double cosec(const Rational& r) {
		if (std::sin(r.toLongDouble()) == 0.0) {
			throw std::domain_error("Exceeding the domain of valid values of the rational cosecant function");
		}
		return ::cosec(r.toLongDouble());
	}

	// Обратные тригонометрические функции
	long double arcsin(const Rational& r) {
		if ((r < Rational(-1, 1)) || (r > Rational(1, 1))) {
			throw std::domain_error("Exceeding the domain of valid values of the rational arcsine function");
		}
		return ::arcsin(r.toLongDouble());
	}
	long double arccos(const Rational& r) {
		if ((r < Rational(-1, 1)) || (r > Rational(1, 1))) {
			throw std::domain_error("Exceeding the domain of valid values of the rational arccosine function");
		}
		return ::arccos(r.toLongDouble());
	}
	long double arctg(const Rational& r) {
		return ::arctg(r.toLongDouble());
	}
	long double arcctg(const Rational& r) {
		return ::arcctg(r.toLongDouble());
	}
	long double arcsec(const Rational& r) {
		if ((r > Rational(-1, 1)) && (r < Rational(1, 1))) {
			throw std::domain_error("Exceeding the domain of valid values of the rational arcsecant function");
		}
		return ::arcsec(r.toLongDouble());
	}
	long double arccosec(const Rational& r) {
		if ((r > Rational(-1, 1)) && (r < Rational(1, 1))) {
			throw std::domain_error("Exceeding the domain of valid values of the rational arccosecant function");
		}
		return ::arccosec(r.toLongDouble());
	}

	// Гиперболические функции
	long double sh(const Rational& r) {
		return ::sh(r.toLongDouble());
	}
	long double ch(const Rational& r) {
		return ::ch(r.toLongDouble());
	}
	long double th(const Rational& r) {
		return ::th(r.toLongDouble());
	}
	long double cth(const Rational& r) {
		if (r == Rational(0, 1)) {
			throw std::domain_error("Exceeding the domain of valid values of the rational hyperbolic cotangent function");
		}
		return ::cth(r.toLongDouble());
	}
	long double sch(const Rational& r) {
		return ::sch(r.toLongDouble());
	}
	long double csch(const Rational& r) {
		if (r == Rational(0, 1)) {
			throw std::domain_error("Exceeding the domain of valid values of the rational hyperbolic cosecant function");
		}
		return ::csch(r.toLongDouble());
	}

}