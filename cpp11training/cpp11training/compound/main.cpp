#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>

namespace {

class Meeting {
public:
    using Room = std::string;
    using Time = int;
    using Duration = int;

    Room room;
    Time from;
    Duration duration;

    std::string description;

    static auto readFrom(std::istream &in) {
		Meeting m;
        in >> m.room;
        in >> m.from;
        in >> m.duration;
        in >> m.description;
		if (in.good()) {
			return m;
		} else {
			throw std::invalid_argument("reading");
		}
    }

    auto to_string() const {
        return description + ": in '" + room + "'' from " + std::to_string(from) + " to " + std::to_string(from + duration);
    }
};

}

auto read(const char *path) {
    std::vector<Meeting> meetings;
    std::ifstream input(path);

    while(input.good()) {
		try {
			auto m = Meeting::readFrom(input);
			meetings.push_back(std::move(m));
		} catch(const std::invalid_argument &) {
			break;
		}
    }

    return meetings;
}

void print(const std::vector<Meeting> &meetings) {
    std::cout << meetings.size() << " meetings:" << std::endl;
    std::transform(begin(meetings), end(meetings),
                   std::ostream_iterator<std::string>(std::cout, "\n"),
                   std::mem_fn(&Meeting::to_string));
}

auto byRoom = [](auto meetings) {
	std::sort(begin(meetings), end(meetings),
			[](const auto &m1, const auto &m2) {
				return m1.room < m2.room;
				});
	print(meetings);
};

int main(int argc, char **args) {
    auto meetings = read(args[1]);
    print(meetings);
	std::string command;
	std::map<std::string, std::function<void()>> commands{ {
		{ "help", []{ std::cout << "help" << std::endl; } },
		{ "byroom", std::bind(byRoom, meetings) },
	} };

	while(std::cin >> command) {
		if (command == "quit") {
			return 0;
		}
		try {
			commands.at(command)();
		} catch(const std::out_of_range &e) {
			std::cerr << e.what() << std::endl;
		}
	}

    return 0;
}
