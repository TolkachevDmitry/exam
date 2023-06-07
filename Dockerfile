FROM ubuntu

LABEL author = "Tolkachev Dmitry"

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install qtbase5-dev -y 
RUN apt-get install qt5-qmake 
RUN apt-get install build-essential -y

WORKDIR /root/
RUN mkdir Tolkachev_221_353
WORKDIR /root/Tolkachev_221_353/
COPY *.cpp /root/Tolkachev_221_353/
COPY *.h /root/Tolkachev_221_353/
COPY *.pro /root/Tolkachev_221_353/

RUN qmake hallServer.pro
RUN make

ENTRYPOINT ["./hallServer"]