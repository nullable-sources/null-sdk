#pragma once
#include <chrono>
#include <deque>

namespace utils {
	class c_immediate_time_measurement {
	protected:
		std::chrono::steady_clock::time_point measurement_start{ };

	public:
		c_immediate_time_measurement() { }

	public:
		virtual std::chrono::nanoseconds representation() const { return std::chrono::steady_clock::now() - measurement_start; }
		
		virtual void begin() { measurement_start = std::chrono::steady_clock::now(); }
	};

	class c_retained_time_measurement : public c_immediate_time_measurement {
	protected:
		std::chrono::steady_clock::time_point last_update{ };

	public:
		c_retained_time_measurement() { }

	public:
		virtual std::chrono::nanoseconds representation() const override { return last_update - measurement_start; }

		virtual void begin() override { last_update = measurement_start = std::chrono::steady_clock::now(); }
		virtual void update() { last_update = std::chrono::steady_clock::now(); }
	};

	class c_segment_time_measurement : public c_retained_time_measurement {
	protected:
		std::chrono::nanoseconds delta{ };

	public:
		c_segment_time_measurement() { }

	public:
		virtual std::chrono::nanoseconds representation() const override { return delta; }

		virtual void update() override {
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
			delta = now - last_update;
			last_update = now;
		}
	};

	class c_cumulative_time_measurement : public c_segment_time_measurement {
	protected:
		int max_size{ };
		std::deque<std::chrono::nanoseconds> measurements{ };

	public:
		c_cumulative_time_measurement(const int& _max_size) : max_size(_max_size) { }

	public:
		virtual std::chrono::nanoseconds representation() const override { return delta / measurements.size(); }

		virtual void update() override {
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

			if(measurements.size() >= max_size) {
				delta -= measurements.front();
				measurements.pop_front();
			}

			delta += measurements.emplace_back(now - last_update);

			last_update = now;
		}
	};
}