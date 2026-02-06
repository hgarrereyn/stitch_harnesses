#include <modsecurity/modsecurity.h>
#include <modsecurity/rules_set.h>
#include <modsecurity/transaction.h>

using namespace modsecurity;

int main() {
    ModSecurity ms;
    RulesSet rules;
    const char *basic_rules = "SecRuleEngine On\nSecRule REQUEST_URI \"@contains test\" \"id:1,phase:2,deny,log\"\n";
    rules.load(basic_rules);

    Transaction t(&ms, &rules, nullptr);
    t.processConnection("127.0.0.1", 12345, "127.0.0.1", 80);
    t.processURI("/index?x=test", "GET", "HTTP/1.1");
    t.processRequestHeaders();
    t.processRequestBody();
    t.processResponseHeaders(200, std::string("HTTP/1.1"));
    t.processResponseBody();
    t.processLogging();

    ModSecurityIntervention it;
    (void)t.intervention(&it);
    return 0;
}
