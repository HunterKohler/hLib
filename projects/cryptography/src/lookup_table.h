#include <initializer_list>
#include <vector>
#include <functional>
#include <concepts>
#include <cstddef>

template <class Key, class Value, class Compare = std::equal_to<Key>>
    requires requires(Key key1, Key key2, Compare cmp) {
        { cmp(key1, key2) } -> std::convertible_to<bool>;
    }
class LookupTable {
    constexpr LookupTable() {}
    constexpr LookupTable(constexpr std::pair<Key, Value>& ...values) {
        for(const std::pair<Key, Value>& value: values) {
            table.push_back(value);
        }
    };

    // constexpr Value& operator[](const Key& key) {

    // }

  private:
    constexpr std::vector<std::pair<key_type, value_type>> table;
};

int main() {

}