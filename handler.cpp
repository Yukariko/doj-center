#include "include/handler.h"

handler::handler()
{
    //ctor
}
handler::handler(utility::string_t url):m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&handler::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));

}
handler::~handler()
{
    //dtor
}

void handler::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error, Log it if a logger is available
    }
}


//
// Get Request 
//
void handler::handle_get(http_request message)
{
    ucout << message.to_string() << endl;
    message.reply(status_codes::OK, message.to_string());
    return;

};

//
// A POST request
//
void handler::handle_post(http_request message)
{
    ucout << message.to_string() << endl;
    auto body = message.extract_string().then([](utility::string_t body) {
        ucout << body << endl;
    }).wait();
    auto kv = uri::split_query(message.relative_uri().query());
    ucout << kv["submit"] << endl;
    message.reply(status_codes::OK,message.to_string());
    return ;
};

//
// A DELETE request
//
void handler::handle_delete(http_request message)
{
    ucout <<  message.to_string() << endl;

    string rep = U("WRITE YOUR OWN DELETE OPERATION");
    message.reply(status_codes::OK,rep);
    return;
};


//
// A PUT request 
//
void handler::handle_put(http_request message)
{
    ucout <<  message.to_string() << endl;
    string rep = U("WRITE YOUR OWN PUT OPERATION");
    message.reply(status_codes::OK,rep);
    return;
};
