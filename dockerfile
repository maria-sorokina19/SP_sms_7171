FROM ubuntu
RUN apt update && apt install build-essential -y && apt-get install gcc-multilib -y   
COPY 7171.s .
RUN gcc -m32 -fno-pie -no-pie 7171.s -o 7171_sms -g  
CMD ./7171_sms

