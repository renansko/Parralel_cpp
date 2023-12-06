#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <omp.h>

struct Pokemon {
    std::string nome;
    int vida;
    int ataque;
    int defesa;
    int atqEsp;
    int defEsp;
    int velocidade;
};

int main() {
    std::ifstream arquivo("pokemon_data.txt");

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::vector<Pokemon> pokemons;

    std::string linha;
    std::getline(arquivo, linha);  
    // extrair arquivo
    while (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        Pokemon pokemon;
        std::getline(iss, pokemon.nome, ',');
        iss >> pokemon.vida >> pokemon.ataque >> pokemon.defesa >> pokemon.atqEsp >> pokemon.defEsp >> pokemon.velocidade;
        pokemons.push_back(pokemon);
    }

    arquivo.close();

    std::map<std::string, Pokemon> max_pokemons;

    #pragma omp parallel for
    for (size_t i = 0; i < pokemons.size(); ++i) { // Compare
        #pragma omp critical
        {
            if (pokemons[i].vida > max_pokemons["Vida"].vida) {
                max_pokemons["Vida"] = pokemons[i];
            }
            if (pokemons[i].ataque > max_pokemons["Ataque"].ataque) {
                max_pokemons["Ataque"] = pokemons[i];
            }
            if (pokemons[i].defesa > max_pokemons["Defesa"].defesa) {
                max_pokemons["Defesa"] = pokemons[i];
            }
            if (pokemons[i].atqEsp > max_pokemons["Atq Esp"].atqEsp) {
                max_pokemons["Atq Esp"] = pokemons[i];
            }
            if (pokemons[i].defEsp > max_pokemons["Def Esp"].defEsp) {
                max_pokemons["Def Esp"] = pokemons[i];
            }
            if (pokemons[i].velocidade > max_pokemons["Velocidade"].velocidade) {
                max_pokemons["Velocidade"] = pokemons[i];
            }
        }
    }

    // ImprimIr com maior valor auto
    for (const auto& max_pokemon : max_pokemons) {
        std::cout << "Atributo: " << max_pokemon.first << ", Pokemon: " << max_pokemon.second.nome << std::endl;
    }

