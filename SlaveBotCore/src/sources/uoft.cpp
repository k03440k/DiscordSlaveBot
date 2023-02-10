#include "../includes/SlaveBot/tlib/uoft.hpp"

namespace sb
{
	namespace tlib
	{
		namespace uoft
		{
			const TimeBase& TimeBase::operator=(const TimeBase& other) noexcept
			{
				if (*this == other) return *this;
				time_in_seconds = other.time_in_seconds;
				time = time_in_seconds / pow(TIME_BASE, to_multuiply_seconds);
				return *this;
			}
			const TimeBase& TimeBase::operator=(TimeBase&& other) noexcept
			{
				time_in_seconds = other.time_in_seconds;
				time = time_in_seconds / pow(TIME_BASE, to_multuiply_seconds);
				other.time = 0;
				other.time_in_seconds = 0;
				other.to_multuiply_seconds = 0;
				return *this;
			}

			std::ostream& operator<<(std::ostream& out, const TimeBase& time)
			{
				out << time.time;
				return out;
			}
			std::ostream& operator<<(std::ostream& out, TimeBase&& time)
			{
				out << time.time;
				time.time = 0;
				time.time_in_seconds = 0;
				time.to_multuiply_seconds = 0;
				return out;
			}
			std::istream& operator>>(std::istream& in, TimeBase& time)
			{
				in >> time.time;
				time.time_in_seconds = time.time * pow(TIME_BASE, time.to_multuiply_seconds);
				return in;
			}

			const TimeBase& TimeBase::operator+=(const TimeBase& other) noexcept
			{
				time_in_seconds += other.time_in_seconds;
				time = time_in_seconds / pow(TIME_BASE, other.to_multuiply_seconds);
				return *this;
			}
			const TimeBase& TimeBase::operator-=(const TimeBase& other) noexcept
			{
				time_in_seconds -= other.time_in_seconds;
				time = time_in_seconds / pow(TIME_BASE, other.to_multuiply_seconds);
				return *this;
			}
			const TimeBase& TimeBase::operator*=(const TimeBase& other) noexcept
			{
				time_in_seconds *= other.time_in_seconds;
				time = time_in_seconds / pow(TIME_BASE, other.to_multuiply_seconds);
				return *this;
			}
			const TimeBase& TimeBase::operator/=(const TimeBase& other) noexcept
			{
				time_in_seconds /= other.time_in_seconds;
				time = time_in_seconds / pow(TIME_BASE, other.to_multuiply_seconds);
				return *this;
			}
			const TimeBase& TimeBase::operator%=(const TimeBase& other) noexcept
			{
				time_in_seconds %= other.time_in_seconds;
				return *this;
			}

			const bool TimeBase::operator==(const TimeBase& other)const noexcept
			{
				return time_in_seconds == other.time_in_seconds;
			}
			const bool TimeBase::operator!=(const TimeBase& other)const noexcept
			{
				return time_in_seconds != other.time_in_seconds;
			}
			const bool TimeBase::operator>=(const TimeBase& other)const noexcept
			{
				return time_in_seconds >= other.time_in_seconds;
			}
			const bool TimeBase::operator<=(const TimeBase& other)const noexcept
			{
				return time_in_seconds <= other.time_in_seconds;
			}
			const bool TimeBase::operator<(const TimeBase& other)const noexcept
			{
				return time_in_seconds < other.time_in_seconds;
			}
			const bool TimeBase::operator>(const TimeBase& other) const noexcept
			{
				return time_in_seconds > other.time_in_seconds;
			}

			const TimeBase& operator++(TimeBase& toadd) noexcept
			{
				toadd.time++;
				toadd.time_in_seconds = toadd.time * pow(TIME_BASE, toadd.to_multuiply_seconds);
				return toadd;
			}
			const TimeBase& operator++(TimeBase& toadd, int) noexcept
			{
				TimeBase toadd1{ (time_t)toadd.time_in_seconds };
				toadd.time++;
				toadd.time_in_seconds = toadd.time * pow(TIME_BASE, toadd.to_multuiply_seconds);
				return toadd1;
			}
			const TimeBase& operator--(TimeBase& toadd) noexcept
			{
				toadd.time--;
				toadd.time_in_seconds = toadd.time * pow(TIME_BASE, toadd.to_multuiply_seconds);
				return toadd;
			}
			const TimeBase& operator--(TimeBase& toadd, int) noexcept
			{
				TimeBase toadd1{ (time_t)toadd.time_in_seconds };
				toadd.time--;
				toadd.time_in_seconds = toadd.time * pow(TIME_BASE, toadd.to_multuiply_seconds);
				return toadd1;
			}
			TimeBase::TimeBase(const time_t& time_unit, const Utils::byte_t& to_mult_sec) noexcept : time_in_seconds{ second_t(time_unit * pow(TIME_BASE, to_mult_sec)) }
			{
				if (time_unit < 0) throw std::exception("time cannot be negative");
				time = time_unit;
				time_in_seconds = time * pow(TIME_BASE, to_mult_sec);
				to_multuiply_seconds = to_mult_sec;
			}
			TimeBase::TimeBase(const TimeBase& _copy, const Utils::byte_t& to_mult_sec) noexcept
			{
				time_in_seconds = _copy.time_in_seconds;
				time = time_in_seconds / pow(TIME_BASE, (std::max(to_mult_sec,
																  _copy.to_multuiply_seconds) -
														 std::min(to_mult_sec,
																  _copy.to_multuiply_seconds)));
				to_multuiply_seconds = to_mult_sec;
			}
			TimeBase::TimeBase(TimeBase&& _copy, const Utils::byte_t& to_mult_sec) noexcept
			{
				//to_multuiply_seconds = _copy.to_multuiply_seconds;
				time_in_seconds = _copy.time_in_seconds;
				time = time_in_seconds / pow(TIME_BASE, (std::max(to_mult_sec,
																  _copy.to_multuiply_seconds) -
														 std::min(to_mult_sec,
																  _copy.to_multuiply_seconds)));
				_copy.time = 0;
				_copy.time_in_seconds = 0;
				to_multuiply_seconds = to_mult_sec;
			}

			Second::Second(const second_t& seconds) noexcept : TimeBase{ seconds, to_divide_seconds() }
			{
			}
			Second::Second(const TimeBase& _copy) noexcept : TimeBase{ _copy, to_divide_seconds() }
			{
			}
			Second::Second(TimeBase&& _copy) noexcept : TimeBase{ std::move(_copy), to_divide_seconds() }
			{
			}
			Minute::Minute(const minute_t& minutes) noexcept : TimeBase{ minutes, to_divide_seconds() }
			{
			}
			Minute::Minute(const TimeBase& _copy) noexcept : TimeBase{ _copy, to_divide_seconds() }
			{
			}
			Minute::Minute(TimeBase&& _copy) noexcept : TimeBase{ std::move(_copy), to_divide_seconds() }
			{
			}
			Hour::Hour(const hour_t& hours) noexcept : TimeBase{ hours, to_divide_seconds() }
			{
			}
			Hour::Hour(const TimeBase& _copy) noexcept : TimeBase{ _copy, to_divide_seconds() }
			{
			}
			Hour::Hour(TimeBase&& _copy) noexcept : TimeBase{ std::move(_copy), to_divide_seconds() }
			{
			}
		}
	}
}