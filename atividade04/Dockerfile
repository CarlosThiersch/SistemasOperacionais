# Imagem base para a criação da nova imagem
FROM ubuntu:20.04

# Declara um ponto de montagem dentro do container que será persistente e compartilhado com o host ou outros containers
VOLUME teste_volume

# Cria um diretorio de trabalho
WORKDIR /teste_workspace

# Instalação dos pacotes necessários na imagem
RUN apt-get update && apt-get install -y \
    build-essential \
    libc6-dev-i386 \
    wget \
    curl

RUN apt-get update
RUN apt-get install python3 -y
RUN apt-get install python3-pip -y
RUN pip3 install --upgrade pip
RUN pip3 install tensorflow
RUN pip3 install pandas scikit-learn matplotlib seaborn jupyter pyyaml h5py auto-sklearn


# Copia os arquivos para dentro da imagem
COPY ExemploFreeRTOS /ExemploFreeRTOS

# Especifica quais portas poderão ser liberadas ao criar o container
EXPOSE 8982