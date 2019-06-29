// Making server

#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_service io_service;   // service declaration for making acceptor

		tcp::endpoint endpoint(tcp::v4(), 13);   // endpoint : 통신 끝점  v4: version4, 13: port number
		tcp::acceptor acceptor(io_service, endpoint);  // connect acceptor with endpoint

		std::cout << "Server started" << std::endl;

		for (;;)   // same as while(true) .. unlimited loop for connecting with client
		{
			const std::string message_to_send = "Hello From Server";
			boost::asio::ip::tcp::iostream stream;

			std::cout << "Check 1" << std::endl;

			boost::system::error_code ec;	  // error code declaration
			acceptor.accept(*stream.rdbuf(), ec);  // update error code by using as a parameter and read buff

			std::cout << "Check 2" << std::endl;

			if (!ec)   // succeed in connecting with client!!  
				// TODO: How to take care of multiple clients? Multi-threading?
			{
				// receive message from client
				std::string line;
				std::getline(stream, line);  // read through tcp::iostream
				std::cout << line << std::endl;

				// send message to client
				stream << message_to_send;
				stream << std::endl;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}