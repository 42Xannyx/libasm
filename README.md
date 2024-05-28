# libasm - Assembly Yourself!

## Summary

The aim of this project is to get familiar with assembly language by implementing various standard library functions in assembly.

## Functions

- `ft_strdup`
- `ft_strcpy`
- `ft_read`
- `ft_write`
- `ft_strcmp`
- `ft_strlen`

### Bonus functions

- `ft_atoi_base`

## Getting Started

### Prerequisites

To build and run this project, you will need:

- Docker or Linux (Recommend Debian)

### Building & running the Docker Image

To build the Docker image, navigate to the directory containing the Dockerfile and run the following command:

```sh
docker build -t libasm .
```

To run the Docker container with live updates from your project directory, use the following command:

```sh
docker run -it -v $(pwd):/app libasm
```

This command will start a bash shell inside the container, with your project directory mounted to `/app` inside the container. Any changes you make to the files on your host system will be reflected inside the container.

## Building and Testing

Once inside the Docker container, you can build and test your assembly functions. Assuming you have a Makefile set up, you can use the following commands:

```sh
make
make test

make bonus
make test_bonus
```
