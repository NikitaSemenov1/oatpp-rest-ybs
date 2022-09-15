FROM lganzzzo/alpine-cmake:latest

RUN apk add postgresql-dev

ADD . /app

WORKDIR /app/utility

RUN ./install-oatpp-modules.sh Release

WORKDIR /app/build

RUN cmake ..
RUN make ./oatpp-rest-ybs-exe

EXPOSE 8000 8000

ENTRYPOINT ["./oatpp-rest-ybs-exe"]
