#include <null-sdk.h>

namespace commands {
    struct help_t : utils::console::i_command {
    public:
        bool execute(const std::vector<std::string>&) override {
            for(const auto& command : registered_commands) {
                std::cout << command->name() << " " << command->description() << std::endl;
            }

            return true;
        }

        std::string name() override { return "/help"; }
        std::string description() override { return "{ displays information about registered commands }"; }
    } help{ };

    struct test_t : utils::console::i_command {
    public:
        bool execute(const std::vector<std::string>& args) override {
            std::cout << "args: ";
            for(std::string_view arg : args) std::cout << "[" << arg << "] ";
            std::cout << std::endl;

            return true;
        }

        std::string name() override { return "/test"; }
        std::string description() override { return "{ test command }"; }
    } test{ };
}

int main() {
    while(true) {
        std::string line{ };
        std::getline(std::cin, line);
        utils::console::i_command::handle(line);
    }
}