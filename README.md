# Guía de Instalacion

* si se requiere instalar activemq-cpp-library ver la guía [aquí](https://github.com/petrubear/amqCppTest)
* descargar Apache Portable Runtime y APR-Utils de [aqui](https://apr.apache.org/download.cgi) y compilar siguiendo los pasos a continuación:

```sh
> tar xvfz apr-1.5.2.tar.gz
> cd apr-1.5.2
> ./configure
> make
> make install

> tar xvfz apr-util-1.5.4.tar.gz
> cd apr-util-1.5.4
> ./configure
> make
> make install
```

* instalar dependencias

```sh
brew install openssl automake cpputils
```

* clonar el proyecto  [fusemq-c](https://github.com/fusesource/fusemq-c) y compilar siguiendo los pasos a continuación:

```sh
> cd fusemqc-client
> ./autogen.sh
> ./configure --with-apr=/usr/local/apr/
> make
> make install
```
