#include <boost/network/protocol/http/server.hpp>
#include <iostream>

namespace http = boost::network::http;

/*<< Defines the server. >>*/
struct Submit;
typedef http::server<Submit> server;

/*<< Defines the request handler.  It's a class that defines two
     functions, `operator()` and `log()` >>*/
struct Submit {
  /*<< This is the function that handles the incoming request. >>*/
  void operator()(server::request const &request, server::connection_ptr connection) {
    server::string_type ip = source(request);
    unsigned int port = request.source_port;
    std::ostringstream data;
    data << "Hello, " << ip << ':' << port << '!';
    connection->write(data.str());
  }
};

int main(int argc, char *argv[]) {

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " address port" << std::endl;
    return 1;
  }

  try {
    /*<< Creates the request handler. >>*/
    Submit handler;
    /*<< Creates the server. >>*/
    server::options options(handler);
    server server_(options.address(argv[1]).port(argv[2]));
    /*<< Runs the server. >>*/
    server_.run();
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
//]
