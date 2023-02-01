#pragma once
#include <chrono>
#include <deque>

namespace utils {
	class c_time_measurement {
	protected:
		std::chrono::steady_clock::time_point measurement_start{ }, last_update{ };
		std::chrono::nanoseconds delta{ };

	public:
		c_time_measurement() { }

	public:
		template <typename representation_t, typename ratio_t>
		representation_t representation() const { return std::chrono::duration<representation_t, ratio_t>{ delta }.count(); }

		template <typename duration_t>
		duration_t::rep representation() const { return representation<duration_t::rep, duration_t::period>(); }

	public:
		virtual void begin() { last_update = measurement_start = std::chrono::steady_clock::now(); }
		virtual void update() {
			std::chrono::steady_clock::time_point now{ std::chrono::steady_clock::now() };
			delta = now - last_update;
			last_update = now;
		}
	};

	class c_cumulative_time_measurement : public c_time_measurement {
	protected:
		int max_size{ };
		std::deque<std::chrono::nanoseconds> measurements{ };

	public:
		c_cumulative_time_measurement(const int& _max_size) : max_size{ _max_size } { }

	public:
		template <typename representation_t, class ratio_t>
		representation_t representation() const { return std::chrono::duration<representation_t, ratio_t>{ delta / measurements.size() }.count(); }

		template <typename duration_t>
		duration_t::rep representation() const { return representation<duration_t::rep, duration_t::period>(); }

	public:
		virtual void update() override {
			std::chrono::steady_clock::time_point now{ std::chrono::steady_clock::now() };

			if(measurements.size() >= max_size) {
				delta -= measurements.front();
				measurements.pop_front();
			}

			delta += measurements.emplace_back(now - last_update);

			last_update = now;
		}
	};
}