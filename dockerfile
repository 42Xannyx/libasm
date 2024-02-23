FROM debian:latest

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    make \
    nasm \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

CMD ["bash"]
