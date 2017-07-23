//
// Created by Edison Martinez on 3/2/17
//


#include <cms.h>
#include <CMS_ConnectionFactory.h>
#include <CMS_Connection.h>
#include <CMS_Session.h>
#include <CMS_Message.h>
#include <CMS_MessageProducer.h>
#include <CMS_Destination.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    cms_initialize();

    const char *brokerUri = "tcp://127.0.0.1:61616";
    const char *queueName = "cppTestQueue";

    CMS_ConnectionFactory *factory = NULL;
    CMS_Connection *connection = NULL;
    CMS_Session *session = NULL;
    CMS_Destination *destination = NULL;
    CMS_MessageProducer *producer = NULL;
    CMS_Message *txtMessage = NULL;

    if (cms_createConnectionFactory(&factory, brokerUri, NULL, NULL) != CMS_SUCCESS) {
        printf("[ERROR] no se pudo crear el factory\n");
        exit(1);
    }

    if (cms_createDefaultConnection(factory, &connection) != CMS_SUCCESS) {
        printf("[ERROR] no se pudo crear la conexion\n");
        exit(1);
    }

    cms_destroyConnectionFactory(factory);

    if (cms_createDefaultSession(connection, &session) != CMS_SUCCESS) {
        printf("[ERROR] no se pudo crear la sesion\n");
        exit(1);
    }

    if (cms_createDestination(session, CMS_QUEUE, queueName, &destination) != CMS_SUCCESS) {
        printf("[ERROR] no se pudo crear el destino\n");
        exit(1);
    }

    if (cms_createProducer(session, destination, &producer) != CMS_SUCCESS) {
        printf("[ERROR] no se pudo crear el producer\n");
        exit(1);
    }

    CMS_Message *message = NULL;
    cms_createTextMessage(session, &message, "[INFO] Hello world! from activemqcpp");
    cms_setCMSMessageType(message, "text/plain");

    if (cms_producerSendWithDefaults(producer, message) != CMS_SUCCESS) {
        printf("[ERROR] no se pudo enviar el mensaje\n");
        cms_destroyMessage(message);
        exit(1);
    }

    printf("[INFO] Sending Message: %a\n", message);

    cms_destroyMessage(message);


    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
    cms_destroySession(session);
    cms_destroyConnection(connection);

    cms_terminate();
}
