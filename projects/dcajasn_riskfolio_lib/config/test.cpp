#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/KroneckerProduct>
#include <riskfolio/functions.hpp>

int main() {
    // Build a simple symmetric matrix and compute top-1 eigenvalue/vector
    Eigen::MatrixXd M(3,3);
    M << 2.0, -1.0, 0.0,
         -1.0, 2.0, -1.0,
          0.0, -1.0, 2.0;
    auto res = cpp_k_eigh(M, 1);
    const Eigen::VectorXd &vals = std::get<0>(res);
    const Eigen::MatrixXd &vecs = std::get<1>(res);
    std::cout << "Largest eigenvalue: " << (vals.size() > 0 ? vals(0) : 0.0) << "\n";
    std::cout << "First eigenvector first component: " << (vecs.size() > 0 ? vecs(0,0) : 0.0) << "\n";

    // Test duplication matrix shape via number of non-zeros
    auto D = cpp_duplication_matrix(3, true);
    std::cout << "D dims: " << D.rows() << "x" << D.cols() << " nnz=" << D.nonZeros() << "\n";

    // Distance correlation matrix for a tiny dataset
    Eigen::MatrixXd Y(4,2);
    Y << 1,2,
         2,3,
         3,5,
         4,8;
    auto C = cpp_dcorr_matrix(Y);
    std::cout << "dcorr diag: " << C(0,0) << ", " << C(1,1) << "\n";
    return 0;
}
