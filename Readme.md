# Description

This is a implementation of simple smtp client,
which creating in the scope of programming
assignment of the "Computer Networking: A Top - Down Approach"
book.

# Requirements

This assignment have next description:


> Assignment 3: Mail Client
The goal of this programming assignment is to create a simple mail client that sends e-mail to any
recipient. Your client will need to establish a TCP connection with a mail server (e.g., a Google mail
server), dialogue with the mail server using the SMTP protocol, send an e-mail message to a recipient(e.g., your friend) via the mail server, and finally close the TCP connection with the mail server.
For this assignment, the Companion Website provides the skeleton code for your client. Your job is to
complete the code and test your client by sending e-mail to different user accounts. You may also try
sending through different servers (for example, through a Google mail server and through your
university mail server).


So requirements to application is next:
- Application should have possibility to
send an emails to any recipient;
- Application should work throught GMail mail
services, since without that, probably most
mail services will reject incoming messages;
- Application should support gmail authorization;
- Application should implement SMTP protocol;