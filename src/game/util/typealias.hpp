#include <type_traits>

enum Weapons_utilities {
    Espada = 0,
    Escudo = 1,
    Arco   = 2,
    Bomba  = 3,
    Pocion = 4,
    not_catched = -1
};

template<typename Base, typename T>
inline bool instanceof(const T) {
    return std::is_base_of<Base, T>::value;
}