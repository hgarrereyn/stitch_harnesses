#include <iostream>
#include <string>
#include <hsql/SQLParser.h>

int main() {
    const std::string query = "SELECT 1;";
    hsql::SQLParserResult result;
    bool ok = hsql::SQLParser::parse(query, &result);
    std::cout << "parse_return=" << ok << " valid=" << result.isValid() << " statements=" << result.size() << "\n";
    if (result.isValid() && result.size() > 0) {
        const hsql::SQLStatement* stmt = result.getStatement(0);
        std::cout << "first_is_select=" << (stmt->isType(hsql::kStmtSelect) ? 1 : 0) << "\n";
    }
    return 0;
}
