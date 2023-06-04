module;
#include <cassert>
#include <iostream>
#include <windows.h>
#include <vector>
#include <format>
#include <ranges>

#include <utils/fast_operators.h>
export module null.sdk:utils.win.console;

export namespace utils {
	namespace console {
		inline FILE* old_out{ }, * old_in{ };

		void attach() {
			if(!AllocConsole()) assert(!"cant alloc console.");

			freopen_s(&old_out, "CONOUT$", "w", stdout);
			freopen_s(&old_in, "CONIN$", "r", stdin);
		}

		void detach() {
			fclose(old_out);
			fclose(old_in);
			FreeConsole();
		}

		template <typename... args_t>
		void print(const std::string_view& text, args_t&&... args) {
			std::cout << std::vformat(text, std::make_format_args(args...));
		}

		//@note: so far, it does not work as it should, due to a different order of initialization of variables,
		//		 registered_commands is cleared after registering the command.
		//		 You can still add commands yourself after initializing variables in some method
		class i_command {
		public:
			static inline std::vector<i_command*> registered_commands{ };

		public:
			static bool handle(const std::string_view& str) {
				if(str.empty()) return false;

				for(const std::string_view& command : str | std::views::split(';') | std::views::transform([](const auto& splitted) { return std::string_view{ splitted }; })) {
					const std::vector<std::string_view> args{ command | std::views::split(' ') | std::views::transform([](const auto& arg) { return std::string_view{ arg }; }) | std::views::filter([](const std::string_view& arg) { return !arg.empty(); }) | std::ranges::to<std::vector>() };
					if(args.empty()) continue;

					if(auto finded{ std::ranges::find_if(registered_commands, [&](i_command* registered_command) { return registered_command->name() == args.front(); }) }; finded != registered_commands.end()) {
						return (*finded)->execute(args | std::views::drop(1) | std::ranges::to<std::vector>());
					}
				}

				return false;
			}

		public:
			i_command() { registered_commands.push_back(this); }

		public:
			virtual bool execute(const std::vector<std::string_view>& args) = 0;

			virtual std::string name() = 0;
			virtual std::string description() = 0;
		};
	}

	enum class e_dye {
		red = FOREGROUND_RED,
		blue = FOREGROUND_BLUE,
		green = FOREGROUND_GREEN,
		intensity = FOREGROUND_INTENSITY,

		on_background = 0x4,

		white = red | green | blue,
		cyan = blue | green | intensity,
		magenta = red | blue | intensity,
		yellow = red | green,

		restore = white,
	}; enum_create_bit_operators(e_dye, false);
	enum_create_cast_operator(e_dye, -);

	std::ostream& operator<<(std::ostream& os, const e_dye& dye) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), -dye); return os; }
}