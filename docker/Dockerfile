FROM debian:buster-slim

RUN apt-get update \
    && apt-get install -yq \
        bison \
        cmake \
        curl \
        git \
        gcc \
        make \
        flex \
        gperf \
        libncurses-dev \
        python2.7 \
        python-pip \
        python-serial \
    && apt-get purge -yq -h \
    && apt-get autoremove -yq --purge \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*


ENV TOOLCHAIN_DIR=/toolchain

ENV XTENSA_SDK_DIR=${TOOLCHAIN_DIR}/xtensa-lx106-elf
ENV ESP8266_SDK_DIR=${TOOLCHAIN_DIR}/esp8266_sdk

RUN mkdir -p ${XTENSA_SDK_DIR}
RUN mkdir -p ${ESP8266_SDK_DIR}


## Download ESP8266 SDK
# https://github.com/espressif/ESP8266_RTOS_SDK/blob/master/README.md
RUN git clone --recursive https://github.com/espressif/ESP8266_RTOS_SDK.git ${ESP8266_SDK_DIR}


## Install ESP8266 python dependencies
RUN python -m pip install -r ${ESP8266_SDK_DIR}/requirements.txt


## Download and extract xtensa SDK
ENV XTENSA_SDK=xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz
RUN curl -O https://dl.espressif.com/dl/${XTENSA_SDK} \
    && tar xvf ${XTENSA_SDK} -C ${TOOLCHAIN_DIR} \
    && rm ${XTENSA_SDK}


## Toolchain configuration
ENV IDF_PATH=${ESP8266_SDK_DIR}
ENV PATH=${PATH}:${XTENSA_SDK_DIR}/bin


## Let's build!
WORKDIR ${ESP8266_SDK_DIR}/examples/get-started/hello_world

# Copy sdk config to current dir.
COPY sdkconfig .

CMD make all