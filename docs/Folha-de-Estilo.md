# Deadly Wish - Folha de Estilo
---
## Sumário:
  * [Nomes](#nomes)
  * [Indentação](#indentacao)
  * [Identação chaves e colchetes](#identação)
  * [Comentários](#comentarios)
  * [Referencias](#referencias)
---
## 1. Nomes<a name="nomes"></a>
### 1.1 Considerações gerais:  
Todos os nomes de variáveis, métodos, rotas, classes e funções devem ser em inglês. Comentários devem ser em português.
### 1.2 Nomes significativos:
Todos os nomes devem ser significativos, de forma que sejam auto explicativos.Exemplo:
```cpp
void Character::kill_character()
{...}
```
### 1.3 Nomes de variáveis
Os nome de variaveis devem ser snake case. Exemplo:
```cpp
int max_respawn_time = 10000;
```
### 1.4 Nomes de constantes
O nome das constantes devem estar em Upper with Underscore. Exemplo:
```cpp
#define PLAYER_MAX_LIFES = 5;
```
### 1.5 Nomes de metódos
O nome de metódos devem estar em Upper Camel Case, sendo que sua nomeclatura de estar associada a um verbo (ação). Exemplo:
```cpp
inline void Character::update_position(){...}
```
### 1.6 Nomes de classes
O nome de metódos devem estar em Upper Camel Case, sendo que sua nomeclatura de estar associada a um substantivo (entidade). Exemplo:
```cpp
class Knight : public Character {
  public:
      Knight(...);

  protected:
      void heavy_attack();
      void light_attack();
      void defense();
      void special();
};


class SpecialState : public CharacterState {
public:
  ...
};
```

## 2. Indentação<a name="indentacao"></a>
### 2.1 Espaço da indentação
A identação deve ser equivalente a 4 espaços do teclado. Exemplo:
```cpp
class Soldier : public Character {
  public:
      Soldier(...);
}
```
### 2.2 Espaço após vírgula e ponto e vígula
Sempre de espaço após virugalas ou ponto e vígula, para maior clareza na leitura do código. Exemplo:
```cpp
play_sound_effect("res/sound/fx/infiltrador_heavy.ogg", EFFECTS_VOLUME, 0);
}
```
### 2.3 Máximo de caracteres em uma linha
Uma linha deve conter no maximo 100 caracteres.

### 2.4 Espaçamento e fechamento de chaves
Deve-se espaçar antes de abrir chave e o fechamento deve ser feito na linha seguinte.Exemplo:
```cpp
class Soldier : public Character {
  public:
      Soldier(...);
}
```


## 4. Comentários<a name="comentarios"></a>

### 4.1 Geral
Todos os cometários devem ser na lingua inglesa e ser relevante para um maior entendimento do código. Comentários com conteúdo que já pode ser inferido devem ser descartados.


## 5. Referencias<a name="referencias"></a>
Folha de Estilo - NeonEdge, Disponivel em  https://github.com/tecnicas-de-programacao-2017-2-grupo-3/neon-edge/wiki/Folha-de-Estilo
Folha de Estilo - SIGS, Disponivel em https://github.com/fga-eps-mds/2017.1-SIGS/wiki/Folha-de-Estilo
