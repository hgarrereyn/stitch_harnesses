ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies required for header-only usage of Bullet headers

# Install prefix
ENV PREFIX=/fuzz/install

# Copy Bullet headers into install prefix (manual install)
# The source tree is mounted at /fuzz/src
RUN set -eux; \
    mkdir -p "$PREFIX/include/bullet" "$PREFIX/lib"; \
    cp -R /fuzz/src/lib/haxebullet/bullet/LinearMath "$PREFIX/include/bullet/"; \
    cp -R /fuzz/src/lib/haxebullet/bullet/BulletCollision "$PREFIX/include/bullet/"; \
    cp -R /fuzz/src/lib/haxebullet/bullet/BulletDynamics "$PREFIX/include/bullet/"; \
    cp -R /fuzz/src/lib/haxebullet/bullet/BulletSoftBody "$PREFIX/include/bullet/"; \
    cp /fuzz/src/lib/haxebullet/bullet/btBulletCollisionCommon.h "$PREFIX/include/bullet/"; \
    cp /fuzz/src/lib/haxebullet/bullet/btBulletDynamicsCommon.h "$PREFIX/include/bullet/"; \
    cp /fuzz/src/lib/haxebullet/bullet/btCustomArray.h "$PREFIX/include/bullet/";

# Nothing to build/link here; headers are sufficient for our test program and codegen
