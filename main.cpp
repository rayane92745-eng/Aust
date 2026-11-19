#include <iostream>
#include "src/lexer/lexer.hpp"

void runTest(const std::string& source) {
    std::cout << "Testing source: " << source << std::endl;
    Lexer lexer(source);
    auto tokens = lexer.scanTokens();

    for (const auto& token : tokens) {
        std::cout << "Token: [Type: " << static_cast<int>(token.type) 
                  << " | Lexeme: '" << token.lexeme << "' | Line: " << token.line << "]" << std::endl;
    }
    std::cout << "------------------------------------------" << std::endl;
}

int main() {
    std::cout << "--- Aust Language Lexer Test ---" << std::endl;

    runTest("var x = 10;");
    runTest("func calculate(a, b) { return a + b; }");

    return 0;
}
