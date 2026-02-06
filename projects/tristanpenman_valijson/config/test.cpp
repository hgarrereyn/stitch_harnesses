#include <iostream>
#include <string>

#include <valijson/schema.hpp>
#include <valijson/validator.hpp>
#include <valijson/validation_results.hpp>
#include <valijson/constraints/concrete_constraints.hpp>
#include <valijson/adapters/std_string_adapter.hpp>

int main() {
    // Build a simple schema: the root must be a string
    valijson::Schema schema;
    valijson::constraints::TypeConstraint typeConstraint;
    typeConstraint.addNamedType(valijson::constraints::TypeConstraint::kString);
    schema.addConstraint(typeConstraint);

    // Validate a simple string document using the StdStringAdapter
    std::string doc = "hello";
    valijson::adapters::StdStringAdapter adapter(doc);

    valijson::Validator validator;
    valijson::ValidationResults results;
    bool ok = validator.validate(schema, adapter, &results);

    std::cout << "Validation result: " << (ok ? "ok" : "fail") << std::endl;
    return ok ? 0 : 1;
}
