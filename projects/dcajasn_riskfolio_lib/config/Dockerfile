ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        python3-dev pybind11-dev binutils ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Set compilers to fuzzing wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Prepare directories
RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/riskfolio

# Create minimal C++ implementation (no Python/pybind symbols)
RUN cat > /fuzz/build/minimal_functions.cpp <<'EOF'
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/KroneckerProduct>
#include <Spectra/SymEigsSolver.h>
#include <numeric>
#include <tuple>

using namespace Eigen;
using namespace Spectra;

// Old straightforward version of duplication matrix (diag=true)
Eigen::SparseMatrix<double> cpp_duplication_matrix(const int &n, const bool &diag) {
    (void)diag; // only diag=true supported in this minimal implementation
    Eigen::SparseMatrix<double> out(n*n, (n*(n+1))/2);
    for (int j = 0; j < n; ++j) {
        for (int i = j; i < n; ++i) {
            Eigen::SparseMatrix<double> u(1, (n*(n+1))/2);
            u.insert(0, j*n+i-((j+1)*j)/2) = 1.0;
            Eigen::MatrixXd T0 = Eigen::MatrixXd::Zero(n, n);
            T0(i,j) = 1.0;
            T0(j,i) = 1.0;
            Eigen::SparseMatrix<double> T(n * n, 1);
            T = (T0.reshaped(n * n, 1)).sparseView();
            out += T * u;
        }
    }
    return out;
}

// Top-k eigenpairs for symmetric matrix using Spectra
std::tuple<Eigen::VectorXd, Eigen::MatrixXd> cpp_k_eigh(Eigen::MatrixXd M, const int &k) {
    DenseSymMatProd<double> op(M);
    SymEigsSolver<DenseSymMatProd<double>> eigs(op, k, std::min<int>(2*k+1, (int)M.rows()));
    eigs.init();
    eigs.compute(SortRule::LargestAlge);
    Eigen::VectorXd eigen_values;
    Eigen::MatrixXd eigen_vectors;
    if(eigs.info() == CompInfo::Successful){
        eigen_values = eigs.eigenvalues();
        eigen_vectors = eigs.eigenvectors();
    } else {
        eigen_values = Eigen::VectorXd::Zero(k);
        eigen_vectors = Eigen::MatrixXd::Zero(M.rows(), k);
    }
    return std::make_tuple(eigen_values, eigen_vectors);
}

// Pairwise Euclidean distances of rows
static inline Eigen::MatrixXd cpp_pdist(Eigen::MatrixXd& X) {
    int n = X.rows();
    Eigen::MatrixXd distances(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            distances(i, j) = (X.row(i) - X.row(j)).norm();
            distances(j, i) = distances(i, j);
        }
    }
    return distances;
}

// Distance correlation for matrix of variables (columns)
Eigen::MatrixXd cpp_dcorr_matrix(Eigen::MatrixXd Y){
    int n = Y.cols();
    Eigen::MatrixXd corr = Eigen::MatrixXd::Ones(n,n);
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            Eigen::MatrixXd Xi = Y.col(i);
            Eigen::MatrixXd Xj = Y.col(j);
            Eigen::MatrixXd a = cpp_pdist(Xi);
            Eigen::MatrixXd b = cpp_pdist(Xj);
            int m = a.rows();
            Eigen::MatrixXd A = a - (a.colwise().mean()).replicate(m, 1) - (a.rowwise().mean()).replicate(1, m) + a.mean() * Eigen::MatrixXd::Ones(m,m);
            Eigen::MatrixXd B = b - (b.colwise().mean()).replicate(m, 1) - (b.rowwise().mean()).replicate(1, m) + b.mean() * Eigen::MatrixXd::Ones(m,m);
            double dcov2_xy = (A.array() * B.array()).sum() / (m * m);
            double dcov2_xx = (A.array() * A.array()).sum() / (m * m);
            double dcov2_yy = (B.array() * B.array()).sum() / (m * m);
            double value = std::sqrt(dcov2_xy) / std::sqrt(std::sqrt(dcov2_xx) * std::sqrt(dcov2_yy));
            corr(i, j) = value;
            corr(j, i) = value;
        }
    }
    return corr;
}
EOF

# Public header for the minimal C++ API
RUN cat > /fuzz/install/include/riskfolio/functions.hpp <<'EOF'
#pragma once
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/KroneckerProduct>
#include <tuple>

Eigen::SparseMatrix<double> cpp_duplication_matrix(const int &n, const bool &diag = true);
std::tuple<Eigen::VectorXd, Eigen::MatrixXd> cpp_k_eigh(Eigen::MatrixXd M, const int &k);
Eigen::MatrixXd cpp_dcorr_matrix(Eigen::MatrixXd Y);
EOF

# Compile and archive static library
RUN $CXX -std=c++17 -O2 -fPIC \
      -I/fuzz/src/lib/eigen-3.4.0 \
      -I/fuzz/src/lib/spectra-1.0.1/include \
      -c /fuzz/build/minimal_functions.cpp -o /fuzz/build/minimal_functions.o && \
    ar rcs /fuzz/install/lib/libriskfolio_cpp.a /fuzz/build/minimal_functions.o && \
    rm -f /fuzz/build/minimal_functions.o

# Install Eigen and Spectra headers for external builds
RUN cp -r /fuzz/src/lib/eigen-3.4.0/Eigen /fuzz/install/include/ && \
    mkdir -p /fuzz/install/include/unsupported/Eigen && \
    cp -r /fuzz/src/lib/eigen-3.4.0/unsupported/Eigen/* /fuzz/install/include/unsupported/Eigen/ && \
    mkdir -p /fuzz/install/include/Spectra && \
    cp -r /fuzz/src/lib/spectra-1.0.1/include/Spectra/* /fuzz/install/include/Spectra/
