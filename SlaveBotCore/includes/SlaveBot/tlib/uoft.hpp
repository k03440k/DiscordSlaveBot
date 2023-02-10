#pragma once

#include <cmath>
#include <chrono>
#include <iostream>

#include "../utils/Utils.hpp"

namespace sb
{
	namespace tlib
	{
		namespace uoft
		{
			const Utils::byte_t TIME_BASE = 60;
			using time_t = float;

			using second_t = unsigned int;
			using minute_t = time_t;
			using hour_t = time_t;

			class Second;
			class Minute;
			class Hour;

			//base class for time_t system
			class TimeBase
			{
			public:
				static const Utils::byte_t to_divide_seconds() noexcept { return 0; }
				static const std::string get_name() noexcept {return std::string("time_base");}

				second_t time_in_seconds = 0;
				time_t time = time_in_seconds / pow(TIME_BASE, to_multuiply_seconds);

				~TimeBase() = default;
#pragma region operators
				/*
				* @return time_t of unit that has
				*/
				friend std::ostream& operator<<(std::ostream& out, const TimeBase& time_t);
				friend std::ostream& operator<<(std::ostream& out, TimeBase&& time_t);
				/*
				* takes unit of time_t
				*/
				friend std::istream& operator>>(std::istream& in, TimeBase& time_t);
				
#pragma region unary
				friend const TimeBase& operator++(TimeBase& toadd) noexcept;
				friend const TimeBase& operator++(TimeBase& toadd, int) noexcept;

				friend const TimeBase& operator--(TimeBase& toadd) noexcept;
				friend const TimeBase& operator--(TimeBase& toadd, int) noexcept;
#pragma endregion
#pragma region binary
				const TimeBase& operator+=(const TimeBase& other) noexcept;
				const TimeBase& operator-=(const TimeBase& other) noexcept;
				const TimeBase& operator*=(const TimeBase& other) noexcept;
				const TimeBase& operator/=(const TimeBase& other) noexcept;
				const TimeBase& operator%=(const TimeBase& other) noexcept;

				const TimeBase& operator=(const TimeBase& other) noexcept;
				const TimeBase& operator=(TimeBase&& other) noexcept;
				/*
				* @return first(left operand) TimeBase type
				*/
				template<class _time>
				const friend _time operator+(const _time& left, const TimeBase& right) noexcept;
				/*
				* @return first(left operand) TimeBase type
				*/
				template<class _time>
				const friend _time operator-(const _time& left, const TimeBase& right) noexcept;
				/*
				* @return first(left operand) TimeBase type
				*/
				template<class _time>
				const friend _time operator*(const _time& left, const TimeBase& right) noexcept;
				/*
				* @return first(left operand) TimeBase type
				*/
				template<class _time>
				const friend _time operator/(const _time& left, const TimeBase& right) noexcept;
				/*
				* @return first(left operand) TimeBase type
				*/
				template<class _time>
				const friend _time operator%(const _time& left, const TimeBase& right) noexcept;
#pragma endregion
#pragma region true or false
				const bool operator==(const TimeBase& other) const noexcept;
				const bool operator!=(const TimeBase& other) const noexcept;
				const bool operator>=(const TimeBase& other) const noexcept;
				const bool operator<=(const TimeBase& other) const noexcept;
				const bool operator<(const TimeBase& other) const noexcept;
				const bool operator>(const TimeBase& other) const noexcept;
#pragma endregion	
#pragma endregion				
			protected:
				template<class T>
				friend class timer;
				TimeBase(const TimeBase& _copy, const Utils::byte_t& to_mult_sec = 0) noexcept;
				TimeBase(const time_t& time_unit, const Utils::byte_t& to_mult_sec = 0) noexcept;
				TimeBase(TimeBase&& _copy, const Utils::byte_t& to_mult_sec = 0) noexcept;

				Utils::byte_t to_multuiply_seconds = to_divide_seconds();
			};
			//max seconds: 4'294'967'295
			class Second : public TimeBase
			{
			public:
				Second(const second_t& seconds = 0) noexcept;
				Second(const TimeBase& _copy) noexcept;
				Second(TimeBase&& _copy) noexcept;

				~Second() = default;

				static const std::string get_name() noexcept { return std::string("second"); }
				static const Utils::byte_t to_divide_seconds() noexcept { return 0; }
			};
			//max minutes: 65'535
			class Minute : public TimeBase
			{
			public:
				Minute(const minute_t& minutes = 0) noexcept;
				Minute(const TimeBase& _copy) noexcept;
				Minute(TimeBase&& _copy) noexcept;

				~Minute() = default;

				static const std::string get_name() noexcept { return std::string("minute"); }
				static const Utils::byte_t to_divide_seconds() noexcept { return 1; }
			};
			//max hours: 255
			class Hour : public TimeBase
			{
			public:
				Hour(const hour_t& hours = 0) noexcept;
				Hour(const TimeBase& _copy) noexcept;
				Hour(TimeBase&& _copy) noexcept;

				~Hour() = default;

				static const std::string get_name() noexcept { return std::string("hour"); }
				static const Utils::byte_t to_divide_seconds() noexcept { return 2; }
			};

#pragma region operator realization
			template<class _time>
			const _time operator+(const _time& left, const TimeBase& right) noexcept
			{
				_time sum = _time();
				sum.time_in_seconds = left.time_in_seconds + right.time_in_seconds;
				sum.time = sum.time_in_seconds / pow(TIME_BASE, left.to_multuiply_seconds);
				return sum;
			}
			template<class _time>
			const _time operator-(const _time& left, const TimeBase& right) noexcept
			{
				_time retail = _time();//р≥зниц€
				retail.time_in_seconds = left.time_in_seconds - right.time_in_seconds;
				retail.time = retail.time_in_seconds / pow(TIME_BASE, left.to_multuiply_seconds);
				return retail;
			}
			template<class _time>
			const _time operator*(const _time& left, const TimeBase& right) noexcept
			{
				_time product = _time();//добуток
				product.time_in_seconds = left.time_in_seconds * right.time_in_seconds;
				product.time = product.time_in_seconds / pow(TIME_BASE, product.to_multuiply_seconds);
				return product;
			}
			template<class _time>
			const _time operator/(const _time& left, const TimeBase& right) noexcept
			{
				_time fraction = _time();//частка
				fraction.time_in_seconds = left.time_in_seconds / right.time_in_seconds;
				fraction.time = fraction.time_in_seconds / pow(TIME_BASE, fraction.to_multuiply_seconds);
				return fraction;
			}
			template<class _time>
			const _time operator%(const _time& left, const TimeBase& right) noexcept
			{
				_time fraction = _time();//частка
				fraction.time_in_seconds = left.time_in_seconds % right.time_in_seconds;
				fraction.time = fraction.time_in_seconds / pow(TIME_BASE, fraction.to_multuiply_seconds);
				return fraction;
			}
#pragma endregion
		}
	}
}