FROM amazonlinux
RUN yum update  
COPY sms.sh .
RUN chmod ugo+x sms.sh
CMD ./sms.sh

