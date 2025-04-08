#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <app.hpp>
#include <exception>
#include <span>

auto main(int argc, char** argv) -> int {
	try {
		auto fileLogger = spdlog::basic_logger_mt("logger", "app.log");
		spdlog::set_default_logger(fileLogger);
		spdlog::info("application started");

		// skip the first argument.
		auto args = std::span{argv, static_cast<std::size_t>(argc)}.subspan(1);
		while (!args.empty()) {
			auto const arg = std::string_view{args.front()};
			if (arg == "-x" || arg == "--force-x11") {
				glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
			}
			args = args.subspan(1);
		}
		lvk::App{}.run();
	} catch (std::exception const& e) {
		spdlog::error("PANIC: {}", e.what());
		return EXIT_FAILURE;
	} catch (...) {
		spdlog::error("PANIC!");
		return EXIT_FAILURE;
	}
}
