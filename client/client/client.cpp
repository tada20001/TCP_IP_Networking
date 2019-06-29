#include <iostream>
#include <string>
#include <boost/asio.hpp>

// stream style
// https://www.boost.org/doc/libs/1_68_0/doc/html/boost_asio/overview/networking/iostreams.html

using boost::asio::ip::tcp;

int main(int argc, char* argv[])   // receive server address(127.0.0.1) through argc
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: Client <host>" << std::endl;
			return 1;
		}

		tcp::iostream stream(argv[1], std::to_string(int(13)));  // port number 13
		if (!stream)
		{
			std::cout << "Unable to connect: " << stream.error().message() << std::endl;
			return 1;
		}

		// send message to server
		stream << "Hello from client";
		stream << std::endl;   // send new-line to end receiver's stream getline

		// receive message from server
		std::string line;
		std::getline(stream, line);
		std::cout << line << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}