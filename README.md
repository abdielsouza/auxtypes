# auxtypes

**auxtypes** é uma pequena biblioteca em C++17 que fornece **tipos auxiliares modernos** para facilitar o desenvolvimento de projetos complexos.  
Ela busca oferecer **segurança, clareza e performance**, complementando a STL com ferramentas práticas para **metaprogramação** e **containers otimizados**.

---

## ✨ Recursos

### 🔹 Metaprogramação
- `TypeList<Ts...>` – lista de tipos para manipulação em tempo de compilação.
- `TypeAt<N, List>` – obtém o tipo no índice `N`.
- `IndexOf<T, List>` – retorna o índice de um tipo em uma lista.
- `IsSpecOf<T, Template>` – verifica se um tipo é instância de um template.
- `Overloaded` – utilitário para `std::visit` e `std::variant`.

### 🔹 Containers auxiliares
- `SmallVector<T, N>` – vetor com buffer interno otimizado (stack + heap sob demanda).
- `FixedString<N>` – string de tamanho fixo, segura e rápida. É resolvida em tempo de compilação.
- `StaticMap<K, V, N>` – mapa leve em stack para pequenos conjuntos de pares.

### 🔹 Programação Funcional
- `FunctionRef<Ret, Ts...>` – Semelhante ao `std::function`, porém não é alocado na heap e não possui ownership.
**É uma view em memória que cobre uma função**, ideal para códigos que recebem callbacks temporárias.
- `Pipeable` – Oferece suporte a **composição de funções**, tornando funções em componentes que podem ser encadeados.
- `Lazy<T>` – Encapsula uma operação que só será executada quando for chamada.

### 🔹 Segurança de tipos e memória
- `NotNull<T>` – Permite limitar o comportamento de ponteiros para que não sejam nulos.
- `NonCopyable<T>` – Não permite realizar cópia de um objeto do tipo recebido.
- `NonMovable<T>` – Não permite mover em memória um objeto do tipo recebido.
- `NeitherCopyableOrMovable<T>` – Não permite nem copiar e nem mover em memória um objeto do tipo recebido.

### 🔹 Outros
- `OptionalRef<T>` – Oferece suporte a referências para `std::optional` da STL.
- `StrongType<T, Tag>` – Permite diferenciar dois ou mais tipos iguais que possuem diferenças semânticas.
- `Result<OkT, ErrT>` – Container que permite o retorno de um tipo de dado em caso de sucesso e outro tipo em caso de erro.

**mais recursos em breve...**

---

## 🚀 Exemplo de uso
```cpp
#include <iostream>
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

---

## Instalação
Para instalar a biblioteca na sua máquina, você pode fazer o seguinte:

```bash
git clone https://github.com/abdielsouza/auxtypes.git
cd auxtypes
xmake install
```

O projeto usa [**Xmake**](https://xmake.io) como build system e o prório Xmake gerencia a instalação da biblioteca para seu sistema operacional.