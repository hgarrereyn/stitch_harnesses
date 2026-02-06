ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN mkdir -p /fuzz/install/include /fuzz/install/lib /build

# Write header using printf to avoid Docker heredoc parsing issues
RUN bash -lc 'printf "%s\n" "#pragma once" > /fuzz/install/include/code_library.hpp && \
  printf "%s\n" "#include <bits/stdc++.h>" >> /fuzz/install/include/code_library.hpp && \
  printf "%s\n" "namespace shah {" >> /fuzz/install/include/code_library.hpp && \
  printf "%s\n" "inline long long extended_euclid(long long a,long long b,long long &x,long long &y){if(b==0){x=1;y=0;return a;}long long x1,y1;long long d=extended_euclid(b,a%b,x1,y1);x=y1;y=x1-y1*(a/b);return d;}" >> /fuzz/install/include/code_library.hpp && \
  printf "%s\n" "inline long long mod_inverse(long long a,long long m){long long x,y;long long g=extended_euclid(a,m,x,y);if(g!=1)return -1;return (x % m + m) % m;}" >> /fuzz/install/include/code_library.hpp && \
  printf "%s\n" "inline long long power_mod(long long x,long long n,long long mod){x%=mod; long long ans=1%mod; while(n>0){ if(n&1) ans=(__int128)ans*x%mod; x=(__int128)x*x%mod; n>>=1;} return ans;}" >> /fuzz/install/include/code_library.hpp && \
  printf "%s\n" "inline std::vector<int> z_function(const std::string &s){int n=(int)s.size(); std::vector<int> z(n); for(int i=1,l=0,r=0;i<n;++i){ if(i<=r) z[i]=std::min(r-i+1,z[i-l]); while(i+z[i]<n && s[z[i]]==s[i+z[i]]) ++z[i]; if(i+z[i]-1>r) l=i,r=i+z[i]-1;} return z;}" >> /fuzz/install/include/code_library.hpp && \
  printf "%s\n" "struct DSU{std::vector<int> par,rnk,sz; int c; explicit DSU(int n):par(n+1),rnk(n+1,0),sz(n+1,1),c(n){for(int i=1;i<=n;++i)par[i]=i;} int find(int i){return par[i]==i?i:par[i]=find(par[i]);} bool same(int i,int j){return find(i)==find(j);} int get_size(int i){return sz[find(i)];} int count()const{return c;} int merge(int i,int j){ if((i=find(i))==(j=find(j))) return -1; else --c; if(rnk[i]>rnk[j]) std::swap(i,j); par[i]=j; sz[j]+=sz[i]; if(rnk[i]==rnk[j]) rnk[j]++; return j; }};" >> /fuzz/install/include/code_library.hpp && \
  printf "%s\n" "} // namespace shah" >> /fuzz/install/include/code_library.hpp'

# Build a tiny static library for linking
RUN bash -lc 'printf "%s\n" "void __code_library_dummy(){}" > /build/dummy.c && \
  stitch_libafl_cc -c /build/dummy.c -o /build/dummy.o && \
  ar rcs /fuzz/install/lib/libcode_library.a /build/dummy.o'
