#pragma once // Защита от множественного включения

#include <cstdint>
#include "real_utils.h"
#include <stdexcept>

namespace rational {

	class Rational {
	private:
		int64_t num; // Числитель (целое число)
		int64_t den; // Знаменатель (натуральное число)

		// Приведение к виду несократимой дроби
		void normalize();

	public:
		// Конструкторы
		Rational(); // Ноль, т. е. 0/1
		explicit Rational(int64_t n); // целое число n / 1
		Rational(int64_t n, int64_t d); // дробь n/d при d != 0

		// Возвращение числа по частям (числителю и знаменателю)
		int64_t numerator() const { return num; }
		int64_t denominator() const { return den; }

		// Проверка чётности числителя (для определения допустимости взять данное число показателем корня с отрицательным основанием)
		bool numeratorIsEven() const;
		bool numeratorIsOdd() const;

		// Проверка чётности знаменателя (для определения допустимости взять данное число показателем степени с отрицательным основанием)
		bool denominatorIsEven() const;
		bool denominatorIsOdd() const;

		// Преобразование в тип long double (если необходимо для вычислений)
		long double toLongDouble() const;

		// Операторы сравнения
		bool operator==(const Rational& other) const;
		bool operator!=(const Rational& other) const;
		bool operator>(const Rational& other) const;
		bool operator>=(const Rational& other) const;
		bool operator<(const Rational& other) const;
		bool operator<=(const Rational& other) const;

		// Арифметические операторы (дружественные)
		friend Rational operator+(const Rational& r1, const Rational& r2);
		friend long double operator+(long double p, const Rational& r);
		friend long double operator+(const Rational& r, long double p);

		friend Rational operator-(const Rational& r1, const Rational& r2);
		friend long double operator-(long double p, const Rational& r);
		friend long double operator-(const Rational& r, long double p);

		friend Rational operator*(const Rational& r1, const Rational& r2);
		friend long double operator*(long double p, const Rational& r);
		friend long double operator*(const Rational& r, long double p);

		friend Rational operator/(const Rational& r1, const Rational& r2);
		friend long double operator/(long double p, const Rational& r);
		friend long double operator/(const Rational& r, long double p);

		// Составные операторы присваивания
		Rational& operator+=(const Rational& other);
		Rational& operator-=(const Rational& other);
		Rational& operator*=(const Rational& other);
		Rational& operator/=(const Rational& other);

		// Унарный минус
		Rational operator-() const;
	};

	// Экспонента
	long double exp(const Rational& r);

	// Логарифмы
	long double log(long double p, const Rational& r);
	long double log(const Rational& r, long double p);
	long double ln(const Rational& r);
	long double log(const Rational& r); // Интерпретация логарифма без указанного основания как натурального
	long double lg(const Rational& r);
	long double lb(const Rational& r);
	long double log(const Rational& r1, const Rational& r2);

	// Возведение в степень
	long double sq(const Rational& r);
	long double cb(const Rational& r);
	long double pow(const Rational& r, int p);
	long double pow(const Rational& r, int64_t p);
	long double pow(const Rational& r1, const Rational& r2);
	long double pow(long double p, const Rational& r);
	long double pow(const Rational& r, long double p);

	// Извлечение корня

	long double sqrt(const Rational& r);
	long double cbrt(const Rational& r);
	long double rt(const Rational& r1, const Rational& r2);
	long double rt(long double p, const Rational& r);
	long double rt(const Rational& r, long double p);

	// Тригонометрические функции
	long double sin(const Rational& r);
	long double cos(const Rational& r);
	long double tg(const Rational& r);
	long double ctg(const Rational& r);
	long double sec(const Rational& r);
	long double cosec(const Rational& r);

	// Обратные тригонометрические функции
	long double arcsin(const Rational& r);
	long double arccos(const Rational& r);
	long double arctg(const Rational& r);
	long double arcctg(const Rational& r);
	long double arcsec(const Rational& r);
	long double arccosec(const Rational& r);

	// Гиперболические функции
	long double sh(const Rational& r);
	long double ch(const Rational& r);
	long double th(const Rational& r);
	long double cth(const Rational& r);
	long double sch(const Rational& r);
	long double csch(const Rational& r);

}