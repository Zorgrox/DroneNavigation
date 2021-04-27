# Start with the base image
FROM  csci3081base as builder
# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    libssl-dev \
    zlib1g-dev \
    rsync \
    doxygen \
    graphviz \
    git
# Setup Dirs
RUN mkdir -p /home/user/repo
COPY . /home/user/repo/project
# Setup DEP_DIR
ARG DEP_DIR
WORKDIR /home/user/repo
RUN git init .
RUN mkdir -p config
RUN echo DEP_DIR=${DEP_DIR} >> config/settings
# Build
WORKDIR /home/user/repo/project
RUN make -j
WORKDIR /home/user/repo/project/docs
RUN doxygen Doxyfile

FROM  csci3081base as sim
RUN mkdir -p /sim
ENV LD_LIBRARY_PATH $LD_LIBRARY_PATH:/sim/lib/
COPY --from=builder /usr/lib/x86_64-linux-gnu/libssl.so.1.1 /usr/lib/x86_64-linux-gnu/libssl.so.1.1
COPY --from=builder /usr/lib/x86_64-linux-gnu/libcrypto.so.1.1 /usr/lib/x86_64-linux-gnu/libcrypto.so.1.1
COPY --from=builder /home/user/repo/project/web /sim/web
COPY --from=builder /home/user/repo/project/data /sim/data
COPY --from=builder /home/user/repo/project/docs/html /sim/web/docs
COPY --from=builder /home/user/repo-build/bin /sim/bin
COPY --from=builder /home/user/repo-build/lib /sim/lib
EXPOSE 8081
WORKDIR /sim
CMD while true; do ./bin/web-app 8081 web/ ; done