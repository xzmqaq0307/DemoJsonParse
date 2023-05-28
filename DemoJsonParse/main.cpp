#include <variant>
#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>
#include <regex>
#include <charconv>
#include <optional>

struct JSONObject;

using JSONDict = std::unordered_map<std::string, JSONObject>;
using JSONList = std::vector<JSONObject>;

struct JSONObject {
    std::variant
        <std::nullptr_t,
        bool,
        int,
        double,
        std::string,
        JSONList,
        JSONDict>
        inner;

    void do_print() const {
        
    }

    template<class T>
    bool is() const {
        return std::holds_alternative<T>(inner);
    }

    template<class T>
    T const& get() const {
        return std::get<T>(inner);
    }

    template<class T>
    std::optional<T> try_parse_num(std::string_view str)
    {

    }
};