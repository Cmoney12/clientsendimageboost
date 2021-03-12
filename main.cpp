#include <iostream>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/asio.hpp>
#include <opencv2/imgcodecs.hpp>


void receive_image(boost::asio::ip::tcp::socket& socket) {
    enum {header_size = 5 };
    boost::system::error_code ignored_error;
    char header_data[header_size + 1];
    boost::asio::read(socket, boost::asio::buffer(header_data, header_size));

    char header[header_size + 1] = "";
    std::strncat(header, header_data, header_size);
    std::size_t body_length_ = std::atoi(header);
    std::cout << body_length_ << std::endl;
    //char buff[body_length_ + 1];
    std::vector<uchar> buff(body_length_);
    boost::asio::read(socket, boost::asio::buffer(buff, body_length_), ignored_error);



    std::cout << "Read " << std::endl;
    //std::cout << buff.size() << std::endl;

    cv::Mat imgbuf = cv::Mat(1280, 960, CV_8UC3, buff.data());
    cv::Mat imgMat = cv::imdecode(cv::Mat(buff), cv::IMREAD_COLOR);
    cv::Mat dec;
    dec = imdecode(buff, cv::IMREAD_COLOR);
    namedWindow("Display window2", cv::WINDOW_AUTOSIZE);
    imshow("Display window2", dec);
    cv::waitKey(0);
}

int main() {

    boost::asio::io_service io_service;

    // Listening for any new incomming connection
    // at port 9999 with IPv4 protocol
    boost::asio::ip::tcp::acceptor acceptor_server(
            io_service,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234));

    // Creating socket object
    boost::asio::ip::tcp::socket server_socket(io_service);

    // waiting for connection
    acceptor_server.accept(server_socket);

    receive_image(server_socket);

    return 0;
}
