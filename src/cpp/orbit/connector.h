#pragma once

// local includes
#include "orbit/msgs.h"

// kelvin includes
#include <kelvin/streamer.h>
#include <kelvin/bytebuffer.h>
#include <kelvin/streamer_client.h>

///////////////////////////////////////////////////////////////////////////////

namespace K273::Orbit {

    class Connector : public Kelvin::Streamer::ConnectingProtocol {

    public:
        Connector(Kelvin::Streamer::ConnectorBase*, int orbit_client_id);
        virtual ~Connector();

    public:
        virtual void onBuffer(Kelvin::ByteBuffer&);

        void onMessage(Connection::MessageHeader*);
        void handleInitialiseClient(Connection::InitialiseClientMessage*);
        void handlePing(Connection::PingMessage*);

        virtual void connectionMade();
        virtual void connectionLost();
        virtual std::string repr() const;

        // called once connected
        void run();

    private:
        void onInitialise();

    private:
        bool is_connected;

        int orbit_client_id;
        std::string orbit_name;

        uint32_t poll_type;
        //XXX uint32_t number_of_channels;

        // used when we recieve handleInitialiseClient
        DEFERRED(Initialiser, Connector, onInitialise);
        Initialiser initialiser;
    };

}
