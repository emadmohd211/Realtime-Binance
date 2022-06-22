// RealtimeBinance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <binapi/api.hpp>
#include <binapi/websocket.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>

#include <iostream>

int main() {
    boost::asio::io_context ioctx;

    binapi::ws::websockets ws{
         ioctx
        ,"stream.binance.com"
        ,"9443"
    };
    std::cout << "************************************************************************************************" << std::endl;
    std::cout << "***                           REAL-TIME BINANCE DATA OF BTC/USDT                             ***" << std::endl;
    std::cout << "************************************************************************************************" << std::endl;

    ws.part_depth("BTCUSDT", binapi::e_levels::_5, binapi::e_freq::_100ms,
        [](const char* fl, int ec, std::string emsg, auto depths) {
            if (ec) {
                std::cerr << "subscribe part_depth error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;

                return false;
            }

            std::cout << "part_depths: " << depths << std::endl;

            return true;
        }
    );

    ws.diff_depth("BTCUSDT", binapi::e_freq::_100ms,
        [](const char* fl, int ec, std::string emsg, auto depths) {
            if (ec) {
                std::cerr << "subscribe diff_depth error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;

                return false;
            }

            std::cout << "diff_depths: " << depths << std::endl;

            return true;
        }
    );

    ws.trade("BTCUSDT",
        [](const char* fl, int ec, std::string emsg, auto trades) {
            if (ec) {
                std::cerr << "subscribe trades error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;

                return false;
            }

            std::cout << "trades: " << trades << std::endl;

            return true;
        }
    );
   
    ioctx.run();

    return EXIT_SUCCESS;
}

