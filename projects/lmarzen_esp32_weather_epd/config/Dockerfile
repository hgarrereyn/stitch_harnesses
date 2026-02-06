ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx INSTALL_PREFIX=/fuzz/install

# Compile core source and create descriptor text definitions
RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/include ${INSTALL_PREFIX}/lib; \
    cd /fuzz/src/platformio/lib/pollutant-concentration-to-aqi; \
    "$CC" -O2 -fPIC -I. -c aqi.c -o aqi.o; \
    cat > aqi_text.c <<'EOF'
const char *AUSTRALIA_AQI_TXT[6] = {
  "Very Good","Good","Fair","Poor","Very Poor","Hazardous"
};
const char *CANADA_AQHI_TXT[4] = {
  "Low","Moderate","High","Very High"
};
const char *CHINA_AQI_TXT[6] = {
  "Excellent","Good","Lightly Polluted","Moderately Polluted","Heavily Polluted","Severely Polluted"
};
const char *EUROPEAN_UNION_CAQI_TXT[5] = {
  "Very Low","Low","Medium","High","Very High"
};
const char *HONG_KONG_AQHI_TXT[5] = {
  "Low","Moderate","High","Very High","Hazardous"
};
const char *INDIA_AQI_TXT[6] = {
  "Good","Satisfactory","Moderate","Poor","Very Poor","Severe"
};
const char *SINGAPORE_PSI_TXT[5] = {
  "Good","Moderate","Unhealthy","Very Unhealthy","Hazardous"
};
const char *SOUTH_KOREA_CAI_TXT[4] = {
  "Good","Medium","Unhealthy","Very Unhealthy"
};
const char *UNITED_KINGDOM_DAQI_TXT[4] = {
  "Low","Moderate","High","Very High"
};
const char *UNITED_STATES_AQI_TXT[6] = {
  "Good","Moderate","Unhealthy for Sensitive Groups","Unhealthy","Very Unhealthy","Hazardous"
};
EOF

# Build static library and install
RUN set -eux; \
    cd /fuzz/src/platformio/lib/pollutant-concentration-to-aqi; \
    "$CC" -O2 -fPIC -c aqi_text.c -o aqi_text.o; \
    ar rcs libaqi.a aqi.o aqi_text.o; \
    cp -v libaqi.a ${INSTALL_PREFIX}/lib/; \
    cp -v aqi.h ${INSTALL_PREFIX}/include/
