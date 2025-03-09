#include "preprocessor.h"

/**
 * @brief Función auxiliar para dividir una cadena por un delimitador
 */
std::vector<std::string> TranslationMap::split(const std::string& s,
                                               char delimiter) {
  std::vector<std::string> tokens;
  std::istringstream tokenStream(s);
  std::string token;
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(trim(token));
  }
  return tokens;
}

/**
 * @brief Función para eliminar espacios en blanco
 */
std::string TranslationMap::trim(const std::string& s) {
  const std::string whitespace = " \t";
  size_t start = s.find_first_not_of(whitespace);
  if (start == std::string::npos) return "";
  size_t end = s.find_last_not_of(whitespace);
  return s.substr(start, end - start + 1);
}

/**
 * @brief Método de parsing del string de configuración
 */
void TranslationMap::parse(const std::string& input) {
  std::istringstream iss(input);
  std::string line;
  std::string current_instr;
  int current_arg_count = 0;

  // Expresión regular para la línea de cabecera, p.ej: "jeqzr 2:"
  std::regex header_regex(R"((\w+)\s+(\d+):)");

  while (std::getline(iss, line)) {
    // Ignorar líneas vacías o de solo espacios
    if (line.find_first_not_of(" \t") == std::string::npos) continue;

    // Si la línea no está indentada, se trata de una cabecera de instrucción
    if (line[0] != ' ' && line[0] != '\t') {
      std::smatch match;
      if (std::regex_search(line, match, header_regex)) {
        current_instr = match[1];
        current_arg_count = std::stoi(match[2]);
        translations[current_instr] = std::vector<Mnemonic>{};
      } else {
        throw std::runtime_error("Formato de cabecera inválido: " + line);
      }
    } else {
      // Líneas indentadas: definición de mnemónico para la instrucción actual
      // Se asume que la línea tiene el formato: "<mnemonic> <argumentos>"
      std::istringstream line_stream{line};
      std::string mnemonic{};
      line_stream >> mnemonic;
      Mnemonic m{};
      m.mnemonic_ = mnemonic;

      // Leer el resto de la línea para obtener los argumentos
      std::string args_str;
      std::getline(line_stream, args_str);
      // Separamos los argumentos por comas
      auto tokens = split(args_str, ',');
      for (auto& token : tokens) {
        if (token.empty()) continue;

        MnemonicArgument arg;
        // Si el token empieza con '$', se trata de un argumento redirigido
        if (token[0] == '$') {
          try {
            arg.index_ = std::stoi(token.substr(1));
            if (arg.index_ >= current_arg_count)
              throw std::runtime_error("Índice superior la máximo");
          } catch (const std::exception& e) {
            throw std::runtime_error(
                "Índice inválido o mayor que el número de argumentos "
                "originales en token: " +
                token);
          }
        } else {
          // De lo contrario, es un valor constante
          arg.const_ = token;
        }
        m.args_.push_back(arg);
      }
      // Agregar el mnemónico a la definición de la instrucción actual
      translations[current_instr].push_back(m);
    }
  }
}

/**
 * @brief Método para traducir líneas
 */
void TranslationMap::Translate(const std::string& line,
                               std::ostream& output) const {
  if (line.find_first_not_of(" \t") == std::string::npos)
    return;  // Skip empty lines

  std::istringstream iss(line);
  std::string token;

  iss >> token;
  if (token[0] == ';') return;  // Skip commented lines

  while (token.back() == ':') {
    output << token << " ";
    if (!(iss >> token)) break;
    if (token[0] == ';') return;  // Skip if commented
  }
  if (token.empty() || token.back() == ',') {
    output << "\n";
    return;
  }

  std::string instruction = token;
  std::string rest_of_line;
  std::getline(iss, rest_of_line, ';');  // Discard anything after ;

  if (translations.find(instruction) == translations.end()) {
    output << instruction << rest_of_line << "\n";
    return;
  }

  // Split arguments
  std::vector<std::string> args = split(rest_of_line, ',');

  for (const auto& mnem : translations.at(instruction)) {
    output << mnem.mnemonic_;

    bool first = true;
    for (const auto& arg : mnem.args_) {
      output << (first ? " " : ", ");
      first = false;
      if (arg.index_ == -1) {
        output << arg.const_;
      } else if (arg.index_ < args.size()) {
        try {
          output << args[arg.index_];
        } catch (const std::exception& e) {
          throw std::runtime_error(
              "Error de sintaxis en instrucción " + instruction +
              ", compruebe el número de argumentos necesarios para esta");
        }
      }
    }
    output << "\n";
  }
}
