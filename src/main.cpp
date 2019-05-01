#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

boost::mutex global_stream_lock;

typedef void (* pfun)(void);

void printmsg(pfun f)
{
    global_stream_lock.lock();
    f();
    global_stream_lock.unlock();
}


void worker(boost::shared_ptr<boost::asio::io_service> io_service)
{
    printmsg([](){ std::cout << "[" << boost::this_thread::get_id() << "] Worker thread start" << std::endl; });

    io_service->run();

    printmsg([](){ std::cout << "[" << boost::this_thread::get_id() << "] Worker thread ended" << std::endl; });
}

int main()
{
    // Welcome
    std::cout << "Welcome to the Ad eXchange Application Server (ADXAS)" << std::endl;
    std::cout << "version 0.0.1 (c) Copyright Lars Tungen 2019" << std::endl;
    std::cout << "Press [return] to exit." << std::endl;

    // Start service
    boost::shared_ptr<boost::asio::io_service> io_service(
        new boost::asio::io_service
    );

    boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work( *io_service )
	);

    boost::thread_group worker_threads;
    for (int x=0;x<4;x++)
    {
        worker_threads.create_thread(boost::bind(&worker, io_service));
    }
 
    // Wait for keypress
	std::cin.get();

    // Stop services
    printmsg([](){ std::cout << "Stopping services..." << std::endl; });
 
    io_service->stop();  
    worker_threads.join_all();

    return 0;
}
