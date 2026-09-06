# syntax=docker/dockerfile:1
FROM ubuntu:24.04

LABEL org.devoldschool.conker.diff-watch="1"

ARG DEBIAN_FRONTEND=noninteractive
ARG ASM_DIFFER_REV=c80ea4e3d16ecc8f4c21923633f3f9b1fb534c53
ARG ASM_PROCESSOR_REV=f3b2f85a5bc7e8ae2030ea5a83ea8aa0bcbede03
ARG MIPS_TO_C_REV=09e0e72337804a713e2c3b8d522abe85838470ea
ARG N64SPLAT_REV=3376e8c1b542d68016d74c685a9b3c64d4e488a1
ARG MUPEN64PLUS_CORE_REV=b0d68c20f49b8f833afa21450e0e8874c87c13c4
ARG MUPEN64PLUS_UI_CONSOLE_REV=1a68327fddda71f1acbad8a63ef04288b1887d19
ARG MUPEN64PLUS_RSP_HLE_REV=2798e65d6fc89d89aace0b0d779af6406809b940
ARG IDO_RECOMP_VERSION=v1.2
ARG IDO_RECOMP_SHA256=ab5c741561f80913d58c8b074771f23941a3edd312505a8ebed6d1dfeb65e506

COPY toolchain/python-constraints.txt /tmp/python-constraints.txt

RUN apt-get update \
    && apt-get install --yes --no-install-recommends \
        bash \
        binutils-dev \
        binutils-mips-linux-gnu \
        build-essential \
        ca-certificates \
        curl \
        file \
        git \
        less \
        libpng-dev \
        libsdl2-dev \
        make \
        pkg-config \
        python3 \
        python3-pip \
        wget \
        zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

# Pin this dependency: newer releases have emitted pseudo-instructions that
# GNU MIPS as does not accept for this project class of build.
RUN python3 -m pip install --break-system-packages spimdisasm==1.33.0

# The original compiler was statically recompiled for modern Linux by the
# decompals project. Pin both release and digest so a rebuild cannot silently
# change the C code generator.
RUN curl --fail --location --output /tmp/ido.tar.gz \
        "https://github.com/decompals/ido-static-recomp/releases/download/${IDO_RECOMP_VERSION}/ido-5.3-recomp-linux.tar.gz" \
    && echo "${IDO_RECOMP_SHA256}  /tmp/ido.tar.gz" | sha256sum --check \
    && mkdir -p /opt/ido \
    && tar --extract --gzip --file /tmp/ido.tar.gz --directory /opt/ido \
    && rm /tmp/ido.tar.gz \
    && chmod --recursive a+rx /opt/ido

# These tools are fetched from their upstream repositories at immutable
# revisions recorded in toolchain/tools.lock.json. They are not project source.
RUN git clone https://github.com/simonlindholm/asm-differ.git /opt/tools/asm-differ \
    && git -C /opt/tools/asm-differ checkout --detach "$ASM_DIFFER_REV" \
    && git clone https://github.com/simonlindholm/asm-processor.git /opt/tools/asm-processor \
    && git -C /opt/tools/asm-processor checkout --detach "$ASM_PROCESSOR_REV" \
    && git clone https://github.com/matt-kempster/mips_to_c.git /opt/tools/mips_to_c \
    && git -C /opt/tools/mips_to_c checkout --detach "$MIPS_TO_C_REV" \
    && git clone https://github.com/ethteck/n64splat.git /opt/tools/n64splat \
    && git -C /opt/tools/n64splat checkout --detach "$N64SPLAT_REV" \
    && python3 -m pip install --break-system-packages \
        /opt/tools/asm-differ \
        /opt/tools/mips_to_c \
        /opt/tools/n64splat \
    && python3 -m pip install --break-system-packages \
        --constraint /tmp/python-constraints.txt \
        --requirement /opt/tools/n64splat/requirements.txt

# Runtime tracing uses a debugger-enabled interpreter build. The console and
# HLE RSP are pinned independently because Mupen64Plus ships them as separate
# modules. OSD, Vulkan, dynarec assembly and the other plugins are unnecessary
# for the headless debugger contract exposed by ./conker mupen.
RUN git clone https://github.com/mupen64plus/mupen64plus-core.git /tmp/mupen64plus-core \
    && git -C /tmp/mupen64plus-core checkout --detach "$MUPEN64PLUS_CORE_REV" \
    && git clone https://github.com/mupen64plus/mupen64plus-ui-console.git /tmp/mupen64plus-ui-console \
    && git -C /tmp/mupen64plus-ui-console checkout --detach "$MUPEN64PLUS_UI_CONSOLE_REV" \
    && git clone https://github.com/mupen64plus/mupen64plus-rsp-hle.git /tmp/mupen64plus-rsp-hle \
    && git -C /tmp/mupen64plus-rsp-hle checkout --detach "$MUPEN64PLUS_RSP_HLE_REV" \
    && make --directory /tmp/mupen64plus-core/projects/unix --jobs "$(nproc)" \
        PREFIX=/opt/mupen64plus DEBUG=1 DEBUGGER=1 NO_ASM=1 OSD=0 VULKAN=0 all \
    && make --directory /tmp/mupen64plus-core/projects/unix \
        PREFIX=/opt/mupen64plus DEBUG=1 DEBUGGER=1 NO_ASM=1 OSD=0 VULKAN=0 install \
    && make --directory /tmp/mupen64plus-ui-console/projects/unix --jobs "$(nproc)" \
        PREFIX=/opt/mupen64plus COREDIR=/opt/mupen64plus/lib/ \
        PLUGINDIR=/opt/mupen64plus/lib/mupen64plus DEBUG=1 all \
    && make --directory /tmp/mupen64plus-ui-console/projects/unix \
        PREFIX=/opt/mupen64plus COREDIR=/opt/mupen64plus/lib/ \
        PLUGINDIR=/opt/mupen64plus/lib/mupen64plus DEBUG=1 install \
    && make --directory /tmp/mupen64plus-rsp-hle/projects/unix --jobs "$(nproc)" \
        PREFIX=/opt/mupen64plus APIDIR=/opt/mupen64plus/include/mupen64plus \
        PLUGINDIR=/opt/mupen64plus/lib/mupen64plus DEBUG=1 all \
    && make --directory /tmp/mupen64plus-rsp-hle/projects/unix \
        PREFIX=/opt/mupen64plus APIDIR=/opt/mupen64plus/include/mupen64plus \
        PLUGINDIR=/opt/mupen64plus/lib/mupen64plus DEBUG=1 install \
    && rm -rf /tmp/mupen64plus-core /tmp/mupen64plus-ui-console \
        /tmp/mupen64plus-rsp-hle

COPY --chmod=0755 toolchain/mupen64plus-debug.sh /usr/local/bin/conker-mupen64plus

WORKDIR /workspace
CMD ["/bin/bash"]
