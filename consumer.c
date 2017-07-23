//
// Created by Edison Martinez on 3/2/17
//

#include <cms.h>
#include <CMS_ConnectionFactory.h>
#include <CMS_Connection.h>
#include <CMS_Session.h>
#include <CMS_Message.h>
#include <CMS_TextMessage.h>
#include <CMS_MessageConsumer.h>
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
    CMS_MessageConsumer *consumer = NULL;

    if (cms_createConnectionFactory(&factory, brokerUri, NULL, NULL) != CMS_SUCCESS) {
        printf("[ERROR] no se pudo crear factory\n");
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

    if (cms_createDefaultConsumer(session, destination, &consumer) != CMS_SUCCESS) {
        printf("[ERROR] no se pudo crear el consumidor\n");
        exit(1);
    }

    if (cms_startConnection(connection) != CMS_SUCCESS) {
        printf("[ERROR] no se pudo iniciar la conexion\n");
        exit(1);
    }

    CMS_Message *message = NULL;
    if (cms_consumerReceive(consumer, &message) != CMS_SUCCESS) {
        printf("[ERROR] error esperando por mensjes.");
        exit(1);
    }


    int type = -1;

    cms_getMessageType(message, &type);

    if (type == CMS_TEXT_MESSAGE) {
        char text[256];
        text[255] = 0;
        int numProperties = 0;

        if (cms_getMessageText(message, text, 256) == CMS_ERROR) {
            printf("[ERROR] error leyendo texto del mensaje.\n");
            exit(1);
        }

        printf("[INFO] Got message: %s.\n", text);
    } else {
        printf("[INFO] se recibió mensaje de tipo desconocido.\n");
    }

    cms_destroyMessage(message);


    cms_destroyConsumer(consumer);
    cms_destroyDestination(destination);
    cms_destroySession(session);
    cms_destroyConnection(connection);

    cms_terminate();
}