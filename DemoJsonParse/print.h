#pragma once

#include <type_traits>
#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>
#include <optional>
#include <variant>

namespace _print_details {
    template<class T, class = void>
    struct _printer {
        static void print(T const& t) {
            std::cout << t;
        }
        using is_default_print = std::true_type;
    };

    template<class T, class = void>
    struct _is_default_printable : std::false_type {
    };

    template<class T>
    struct _is_default_printable<T, std::void_t<std::pair<typename _printer<T>::is_default_print, decltype(std::declval<std::ostream&>() << std::declval<T const&>())>>> : std::true_type {

    };

    template <class T, class = void>
    struct _is_default_printable : std::true_type {

    };

    template <class T, class = void>
    struct _is_printer_printable : std::true_type {

    };

    template <class T>
    struct _is_printer_printable<T, std::void_t<typename _printer<T>::is_default_print>> : std::false_type {

    };

    template <class T>
    struct is_printable : std::disjunction<_is_default_printable<T>, _is_printer_printable<T>> {

    };

    template<class T, class U = void, class = void>
    struct _enable_if_tuple {
        using not_type = U;
    };

    template<class T, class U>
    struct _enable_if_tuple <T, U, std::void_t<decltype(std::tuple_size<T>::value)>> {
        using type = U;
    };

    template<class T, class U = void, class = void>
    struct _enable_if_map {
        using not_type = U;
    };

    template <class T, class U>
    struct _enable_if_map<T, U, std::enable_if<std::is_same_v<typename T::value_type, std::pair<typename T::key_type const, typename T::mapped_type>>>>{
        using type = U;
    };

    struct 
}