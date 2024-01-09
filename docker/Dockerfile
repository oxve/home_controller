FROM debian:bookworm-slim

ENV WORKDIR=/home_controller/home_controller

RUN apt-get update \
    && apt-get install -yq \
        # ESP32 toolchain dependencies
        cmake \
        ninja-build \
        ccache \
        libffi-dev \
        libssl-dev \
        dfu-util \
        libusb-1.0-0 \
        python3.11 \
        python3.11-venv \
        # Other
        curl \
        git \
    && apt-get purge -yq -h \
    && apt-get autoremove -yq --purge \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*


## Set up toolchains
ENV TOOLCHAIN_DIR=/toolchain

ENV ESP_IDF_SDK_DIR=${TOOLCHAIN_DIR}/esp32_sdk
RUN mkdir -p ${ESP_IDF_SDK_DIR}

## Download ESP-IDF
# https://github.com/espressif/esp-idf/blob/release/v5.2/README.md
ENV ESP_IDF_REPO=https://github.com/espressif/esp-idf.git
ENV ESP_IDF_VERSION=v5.1.2
RUN git clone -b ${ESP_IDF_VERSION} --recursive ${ESP_IDF_REPO} ${ESP_IDF_SDK_DIR}

# Expose tool locations
ENV IDF_PATH=${ESP_IDF_SDK_DIR}
ENV PATH=${PATH}:${ESP_IDF_SDK_DIR}/tools

# Install ESP-IDF dependencies
RUN ${ESP_IDF_SDK_DIR}/install.sh

## Additional components. Must be cloned into /components dir.
# Clone sensors lib
ENV ESP_COMPONENTS_DIR=/components/esp-idf-lib
ENV ESP_COMPONENTS_REPO=https://github.com/UncleRus/esp-idf-lib.git
ENV ESP_COMPONENTS_VERSION=0.9.4
RUN git clone -b ${ESP_COMPONENTS_VERSION} ${ESP_COMPONENTS_REPO} ${ESP_COMPONENTS_DIR}

WORKDIR $WORKDIR


ENTRYPOINT [ "./idf-env.sh" ]

## Let's build!
CMD python3 ${ESP_IDF_SDK_DIR}/tools/idf.py all
