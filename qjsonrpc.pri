QJSONRPC_SRC = $$PWD/qjsonrpc/src

include($$QJSONRPC_SRC/http-parser/http-parser.pri)

INCLUDEPATH += $$QJSONRPC_SRC
DEFINES += QJSONRPC_STATIC

QT += network

# check if we need to build qjson
lessThan(QT_MAJOR_VERSION, 5) {
    include($$QJSONRPC_SRC/json/json.pri)
}

PRIVATE_HEADERS += \
    $$QJSONRPC_SRC/qjsonrpcservice_p.h \
    $$QJSONRPC_SRC/qjsonrpcsocket_p.h \
    $$QJSONRPC_SRC/qjsonrpcabstractserver_p.h \
    $$QJSONRPC_SRC/qjsonrpcservicereply_p.h \
    $$QJSONRPC_SRC/qjsonrpchttpserver_p.h

INSTALL_HEADERS += \
    $$QJSONRPC_SRC/qjsonrpcmessage.h \
    $$QJSONRPC_SRC/qjsonrpcservice.h \
    $$QJSONRPC_SRC/qjsonrpcsocket.h \
    $$QJSONRPC_SRC/qjsonrpcserviceprovider.h \
    $$QJSONRPC_SRC/qjsonrpcabstractserver.h \
    $$QJSONRPC_SRC/qjsonrpclocalserver.h \
    $$QJSONRPC_SRC/qjsonrpctcpserver.h \
    $$QJSONRPC_SRC/qjsonrpcglobal.h \
    $$QJSONRPC_SRC/qjsonrpcservicereply.h \
    $$QJSONRPC_SRC/qjsonrpchttpclient.h \
    $$QJSONRPC_SRC/qjsonrpchttpserver.h

greaterThan(QT_MAJOR_VERSION, 4) {
    greaterThan(QT_MINOR_VERSION, 1) {
        INSTALL_HEADERS += $$QJSONRPC_SRC/qjsonrpcmetatype.h
    }
}

HEADERS += \
    $${INSTALL_HEADERS} \
    $${PRIVATE_HEADERS}

SOURCES += \
    $$QJSONRPC_SRC/qjsonrpcmessage.cpp \
    $$QJSONRPC_SRC/qjsonrpcservice.cpp \
    $$QJSONRPC_SRC/qjsonrpcsocket.cpp \
    $$QJSONRPC_SRC/qjsonrpcserviceprovider.cpp \
    $$QJSONRPC_SRC/qjsonrpcabstractserver.cpp \
    $$QJSONRPC_SRC/qjsonrpclocalserver.cpp \
    $$QJSONRPC_SRC/qjsonrpctcpserver.cpp \
    $$QJSONRPC_SRC/qjsonrpcservicereply.cpp \
    $$QJSONRPC_SRC/qjsonrpchttpclient.cpp \
    $$QJSONRPC_SRC/qjsonrpchttpserver.cpp


