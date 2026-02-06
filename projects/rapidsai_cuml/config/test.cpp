#include <iostream>
#include <cstddef>
#include <cuml/svm/svm_model.h>
#include <cuml/tree/flatnode.h>

int main() {
    // Use SVM model header-only structures
    ML::SVM::SvmModel<float> model{};
    model.n_support = 0;
    model.n_cols = 0;
    model.b = 0.0f;
    model.dual_coefs = nullptr;
    model.support_matrix = {};
    model.support_idx = nullptr;
    model.n_classes = 2;
    model.unique_labels = nullptr;

    // Use Decision Tree flat node utilities
    auto leaf = SparseTreeNode<float, int>::CreateLeafNode(42);
    bool is_leaf = leaf.IsLeaf();

    std::cout << "Model classes: " << model.n_classes << ", leaf? " << (is_leaf ? "yes" : "no") << "\n";
    return 0;
}
