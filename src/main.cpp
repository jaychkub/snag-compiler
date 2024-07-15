#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

enum struct tokenType
{
    KEYWORD,
    TYPE,
    IDENTIFIER,
    OPERATOR,
    NUMBER,
    SYMBOL,
    COMMENT
};

struct token
{
    tokenType type;
    std::string value = "";
};

std::vector<token> lexicalAnalysis(std::string& sourceCode)
{
    sourceCode.push_back(' ');
    std::vector<token> tokens;

    std::string token;
    for (int i = 0; i < sourceCode.length(); i++)
    {
        token.clear();

        // COMMENT
        if (sourceCode.at(i) == ':' && sourceCode.at(i + 1) == '-')
        {
            while (sourceCode.at(i) != '\n')
            {
                i++;
            }
        }

        // KEYWORD or IDENTIFIER
        if (std::isalpha(sourceCode.at(i)))
        {
            while (std::isalpha(sourceCode.at(i + 1)))
            {
                token.push_back(sourceCode.at(i));
                i++;
            }
            token.push_back(sourceCode.at(i));

            if (token == "return") tokens.push_back({.type = tokenType::KEYWORD, .value = token});
            else if (token == "int") tokens.push_back({.type = tokenType::TYPE, .value = token});
            else tokens.push_back({.type = tokenType::IDENTIFIER, .value = token});

        }
        // NUMBER
        else if (std::isdigit(sourceCode.at(i)))
        {
            while (std::isdigit(sourceCode.at(i + 1)))
            {
                token.push_back(sourceCode.at(i));
                i++;
            }
            token.push_back(sourceCode.at(i));

            tokens.push_back({.type = tokenType::NUMBER, .value = token});
        }
        else if (sourceCode.at(i) == ';') tokens.push_back({.type = tokenType::SYMBOL, .value = ";"});
        else if (sourceCode.at(i) == '=') tokens.push_back({.type = tokenType::OPERATOR, .value = "="});
        else if (std::isspace(sourceCode.at(i))) continue;
    }

    return tokens;
}

bool syntaxAnalysis(std::vector<token> tokens)
{
    return false;
}

int main(int argc, char* argv[])
{
    // if (argc != 2)
    // {
    //     std::cerr << "Error: Please specify a '.sgl' file" << std::endl;
    //     return 1;
    // }

    std::string filePath = "../test.sg";

    std::string sourceCode;
    {
        std::stringstream sourceCodeStream;
        std::fstream input(filePath, std::ios::in);
        sourceCodeStream << input.rdbuf();
        sourceCode = sourceCodeStream.str();
    }

    std::cout << sourceCode << std::endl;

    std::vector<token> tokens = lexicalAnalysis(sourceCode);

    std::cout << std::endl;
    // for (int i = 0; i < tokens.size() - 1; i++)
    // {
    //     std::cout << tokens[i].value << std::endl;
    // }

    if (syntaxAnalysis(tokens)) std::cout << "Syntax looks good" << std::endl;
    else std::cout << "Syntax looks bad" << std::endl;

    return 0;
}