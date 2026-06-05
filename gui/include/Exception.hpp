#pragma once
#include <exception>
#include <string>

namespace zappy {
    class Exception : public std::exception {
        protected:
            std::string _msg;
        public:
            Exception() = delete;
            Exception(std::string msg) noexcept: _msg(msg) {};
            ~Exception() = default;

            const char *what() const noexcept override {
                return _msg.data();
            };
    };

    class ParserException : public Exception {
        public:
            ParserException() = delete;
            ParserException(std::string msg) noexcept: Exception(msg) {}
    };
}
