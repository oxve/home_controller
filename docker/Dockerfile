# ESP8266 toolchain uses py2.7 which is only available up to buster
FROM debian:buster-slim

RUN apt-get update \
    && apt-get install -yq \
        # ESP8266 toolchain dependencies
        bison \
        cmake \
        gcc \
        make \
        flex \
        gperf \
        libncurses-dev \
        python2.7 \
        python-pip \
        python-serial \
        # Other
        curl \
        git \
    && apt-get purge -yq -h \
    && apt-get autoremove -yq --purge \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*


## Set up toolchains
ENV TOOLCHAIN_DIR=/toolchain

ENV XTENSA_SDK_DIR=${TOOLCHAIN_DIR}/xtensa-lx106-elf
ENV ESP8266_SDK_DIR=${TOOLCHAIN_DIR}/esp8266_sdk

RUN mkdir -p ${XTENSA_SDK_DIR}
RUN mkdir -p ${ESP8266_SDK_DIR}

## Download ESP8266 SDK
# https://github.com/espressif/ESP8266_RTOS_SDK/blob/master/README.md
RUN git clone --recursive https://github.com/espressif/ESP8266_RTOS_SDK.git ${ESP8266_SDK_DIR}

## Install ESP8266 tools and dependencies
RUN ${ESP8266_SDK_DIR}/install.sh
RUN python -m pip install -r ${ESP8266_SDK_DIR}/requirements.txt

## Download and extract xtensa SDK
# https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/linux-setup.html
ENV XTENSA_SDK=xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz
RUN curl -O https://dl.espressif.com/dl/${XTENSA_SDK} \
    && tar xvf ${XTENSA_SDK} -C ${TOOLCHAIN_DIR} \
    && rm ${XTENSA_SDK}

# Expose tool locations
ENV IDF_PATH=${ESP8266_SDK_DIR}
ENV PATH=${PATH}:${XTENSA_SDK_DIR}/bin
ENV PATH=${PATH}:${ESP8266_SDK_DIR}/tools


## Let's build!
WORKDIR /home_controller/home_controller

# Copy sdk config to current dir
COPY sdkconfig .

CMD idf.py flash monitor
