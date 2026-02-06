ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library: install headers into /fuzz/install/include preserving layout
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN apt-get update && apt-get install -y --no-install-recommends rsync && rm -rf /var/lib/apt/lists/*

# Copy all .h headers from the repository's content directory
RUN mkdir -p /fuzz/install/include \
    && rsync -a --include '*/' --include '*.h' --exclude '*' /fuzz/src/content/ /fuzz/install/include/

# Provide a small prelude to satisfy common KACTL macros/typedefs when compiling headers standalone
RUN mkdir -p /fuzz/install/include && cat >/fuzz/install/include/kactl_prelude.hpp <<'EOF'
#pragma once
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
EOF

# No library to build; headers are ready under /fuzz/install/include
