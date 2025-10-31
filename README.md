# auxtypes

**auxtypes** é uma pequena biblioteca em C++17 que fornece **tipos auxiliares modernos** para facilitar o desenvolvimento de projetos complexos.  
Ela busca oferecer **segurança, clareza e performance**, complementando a STL com ferramentas práticas para **metaprogramação** e **containers otimizados**.

---

## ✨ Recursos

### 🔹 Metaprogramação
- `TypeList<Ts...>` – lista de tipos para manipulação em tempo de compilação  
- `TypeAt<N, List>` – obtém o tipo no índice `N`  
- `IndexOf<T, List>` – retorna o índice de um tipo em uma lista  
- `IsSpecOf<T, Template>` – verifica se um tipo é instância de um template  
- `Overloaded` – utilitário para `std::visit` e `std::variant`

### 🔹 Containers auxiliares
- `SmallVector<T, N>` – vetor com buffer interno otimizado (stack + heap sob demanda)  
- `FixedString<N>` – string de tamanho fixo, segura e rápida  
- `StaticMap<K, V, N>` – mapa leve em stack para pequenos conjuntos de pares

**mais recursos em breve...**

---

## 🚀 Exemplo de uso
```cpp
#include <iostream>
#include "auxtypes/metautils.hpp"
#include "auxtypes/containers.hpp"

int main() {
    using namespace auxtypes;

    SmallVector<int, 4> vec = {1,2,3};
    vec.push_back(4);
    vec.push_back(5);
    for (auto v : vec) std::cout << v << " "; // 1 2 3 4 5

    FixedString<10> fs("Hello");
    std::cout << "\n" << fs.c_str() << " (" << fs.size() << ")\n";

    StaticMap<int, const char*, 4> smap;
    smap.insert(1, "um");
    smap.insert(2, "dois");
    std::cout << "1 -> " << smap.at(1) << "\n";
}
```