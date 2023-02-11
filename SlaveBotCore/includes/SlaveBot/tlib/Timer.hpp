#pragma once

#include <thread>
#include "uoft.hpp"

//fucking slave bot
namespace sb
{
	namespace tlib
	{
		/*
		* timer - it's simple class which represent timer.
		* you need to put some unit of time_t in constructor,
		* you can find it at SlaveBot::tlib::uoft namespace.
		*/
		template<class _time = uoft::Second>
		class timer
		{
		private:
			_time time_before_counting;
			bool started = false;
			_time _time_to_end;
			bool is_updating = false;
		public:
			/*
			* @param inheritor of SlaveBot::tlib::uoft::TimeBase
			*/
			timer(const _time& time_to_end = _time()) noexcept
			{
				this->_time_to_end = time_to_end;
				time_before_counting = time_to_end;
			}

			/*
			* starts the timer
			*/
			void start(const bool& _start = true) noexcept
			{
				if (_time_to_end == _time()) return;

				started = _start;
				while (!is_stopped())
				{
					is_updating = false;
					std::this_thread::sleep_for(std::chrono::seconds(1));
					is_updating = true;
					--_time_to_end.time_in_seconds;
				}
			}
			/*
			* @return true if it doen't working, else false
			*/
			const bool is_stopped() noexcept
			{
				if (_time_to_end == _time()) { started = false; is_updating = false; }
				return !started;
			}
			/*
			* @return elapsed time_t
			*/
			const _time elapsed_time() noexcept
			{
				return time_before_counting - _time_to_end;
			}
			/*
			* @return time_t to the end of timer
			*/
			const _time time_to_end() const noexcept
			{
				return _time_to_end;
			}
			/*
			* @return bool(when the --time_to_end.time_in_seconds then it will return true )
			*/
			const bool is_updated() const noexcept
			{
				return is_updating ? true : false;
			}
			void set_new_time(const _time& time_to_end = _time())
			{
				started = false;
				is_updating = false;
				this->_time_to_end = time_to_end;
				this->time_before_counting = time_to_end;
			}
			const _time get_start_time() const noexcept
			{
				return time_before_counting;
			}
			void clear()
			{
				started = false;
				is_updating = false;
				time_before_counting = _time(0);
				_time_to_end = _time(0);
			}
		};
	}
}