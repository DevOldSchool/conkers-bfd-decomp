# Keep the CPU toolchain unchanged; add the pinned RSP assembler in a child image.
ARG BASE_IMAGE
FROM ${BASE_IMAGE}
ARG ARMIPS_REV
RUN apt-get update \
    && apt-get install --yes --no-install-recommends cmake g++ \
    && rm -rf /var/lib/apt/lists/*
# v0.11.0 relied on a transitive <limits> include removed in recent libstdc++.
# Supply the standard header explicitly without modifying assembler code.
RUN git clone https://github.com/Kingcom/armips.git /opt/armips-src \
    && git -C /opt/armips-src checkout --detach "$ARMIPS_REV" \
    && git -C /opt/armips-src submodule update --init --recursive \
    && cmake -S /opt/armips-src -B /opt/armips-build -DCMAKE_BUILD_TYPE=Release "-DCMAKE_CXX_FLAGS=-include limits" \
    && cmake --build /opt/armips-build --parallel 4 \
    && mkdir -p /opt/armips \
    && cp /opt/armips-build/armips /opt/armips/armips \
    && cp /opt/armips-src/LICENSE.txt /opt/armips/LICENSE.txt \
    && printf '%s\n' "$ARMIPS_REV" > /opt/armips/revision \
    && rm -rf /opt/armips-src /opt/armips-build
