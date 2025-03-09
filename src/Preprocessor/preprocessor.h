#ifndef PREPROCESSOR
#define PREPROCESSOR

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Estructuras básicas para representar argumentos y mnemónicos
struct MnemonicArgument {
  std::string const_;  // Si no se usa, queda vacío
  int index_ = -1;     // Valor negativo indica que no se está usando un índice
};

struct Mnemonic {
  std::string mnemonic_;
  std::vector<MnemonicArgument> args_;
};

class TranslationMap {
 public:
  // El constructor recibe un string con el formato deseado
  TranslationMap(const std::string& definition_str) { parse(definition_str); }
  void Translate(const std::string& line, std::ostream& output) const;
  void TranslateProgram(const std::string& program) const {
    std::ifstream input_p{program};
    std::ofstream output_p{program + ".pre"};
    std::string line{""};
    while (std::getline(input_p, line)) {
      Translate(line, output_p);
    }
  }

 private:
  // Mapa interno: nombre de instrucción -> definición
  std::map<std::string, std::vector<Mnemonic>> translations;
  // Método de parsing del string de configuración
  void parse(const std::string& input);
  // Función auxiliar para dividir una cadena por un delimitador
  static std::vector<std::string> split(const std::string& s, char delimiter);
  // Función para eliminar espacios en blanco
  static std::string trim(const std::string& s);
};

#endif
