/*
 *   C++ UDP socket server for live image upstreaming
 *   Modified from http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/practical/UDPEchoServer.cpp
 *   Copyright (C) 2015
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "PracticalSocket.h"      // For UDPSocket and SocketException
#include <iostream>               // For cout and cerr
#include <cstdlib>                // For atoi()

#include "opencv2/opencv.hpp"
#include "opencv/cv.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "MyGaze.hpp"
//#include <XnCppWrapper.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "config.h"

#define BUF_LEN 65540 // Larger than maximum UDP packet size

using namespace cv;
using namespace std;
//using namespace xn;

int eyeGazeX = 0;
int eyeGazeY = 0;
int gazeX = 0;
int gazeY = 0;
int beforGazeX[5] = {};
int beforGazeY[5] = {};
int currentGazeX = 0;
int currentGazeY = 0;
int gazeCount = 0;

/*
void EyeData(int x, int y) {
    
    currentGazeX = x;   currentGazeY = y;
    
    if (gazeCount > 0) {
        
        eyeGazeX = beforGazeX * 0.9 + currentGazeX * 0.1;
        eyeGazeY = beforGazeY * 0.9 + currentGazeY * 0.1;
    }
    beforGazeX = currentGazeX;
    beforGazeY = currentGazeY;
    
    if (gazeCount == 0) {
        gazeCount++;
    }
}*/

void EyeData(int x, int y) {
    
    currentGazeX = x;   currentGazeY = y;
    
    if (gazeCount > 4) {
        
        eyeGazeX = (beforGazeX[0] + beforGazeX[1] + beforGazeX[2] + beforGazeX[3] + beforGazeX[4]) / 5;
        eyeGazeY = (beforGazeY[0] + beforGazeY[1] + beforGazeY[2] + beforGazeY[3] + beforGazeY[4]) / 5;
    }
    beforGazeX[4] = beforGazeX[3];
    beforGazeX[3] = beforGazeX[2];
    beforGazeX[2] = beforGazeX[1];
    beforGazeX[1] = beforGazeX[0];
    beforGazeX[0] = currentGazeX;

    beforGazeY[4] = beforGazeY[3];
    beforGazeY[3] = beforGazeY[2];
    beforGazeY[2] = beforGazeY[1];
    beforGazeY[1] = beforGazeY[0];
    beforGazeY[0] = currentGazeY;
    
    if (gazeCount <= 4) {
        gazeCount++;
    }
}

MyGaze::MyGaze() {
    // Connect to the server in push mode on the default TCP port (6555)
    if( m_api.connect( true ) ) {
        // Enable GazeData notifications
        m_api.add_listener( *this );
    }
}

MyGaze::~MyGaze() {
    m_api.remove_listener( *this );
    m_api.disconnect();
}


void MyGaze::on_gaze_data( gtl::GazeData const & gaze_data ) {
    if( gaze_data.state & gtl::GazeData::GD_STATE_TRACKING_GAZE ) {
        
        gtl::Point2D const & smoothedCoordinates = gaze_data.avg;
        
        // Move GUI point, do hit-testing, log coordinates, etc.
        // std::cout << "x = " << smoothedCoordinates.x << " y = " << smoothedCoordinates.y << std::endl;
        EyeData(smoothedCoordinates.x, smoothedCoordinates.y);
    }
}


int main() {

    MyGaze *gaze;
    gaze = new MyGaze();

    unsigned short servPort = atoi("12345"); // First arg:  local port

    // namedWindow("recv", CV_WINDOW_AUTOSIZE);
    Mat rawData;
    Mat frame;
    Mat Image(1280, 720, CV_8UC3);
    
    try {

        /* TCP transfer gaze_x */
        int sock_gazeX;
        struct sockaddr_in addr_gazeX;
        struct sockaddr_in client_gazeX;
        socklen_t len_gazeX;
        int ret_gazeX;
        ssize_t n_gazeX = 0;
        
        sock_gazeX = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_gazeX < 0) {
            perror("socket");
            // return 1;
        }
        addr_gazeX.sin_family = AF_INET;
        addr_gazeX.sin_port = htons(22333);
        addr_gazeX.sin_addr.s_addr = INADDR_ANY;
        if (::bind(sock_gazeX, (struct sockaddr *)&addr_gazeX, sizeof(addr_gazeX)) != 0) {
            perror("bind");
            // return 1;
        }
        if (listen(sock_gazeX, 5) != 0) {
            perror("listen");
            // return 1;
        }
        
        /* TCP transfer gaze_y */
        int sock_gazeY;
        struct sockaddr_in addr_gazeY;
        struct sockaddr_in client_gazeY;
        socklen_t len_gazeY;
        int ret_gazeY;
        ssize_t n_gazeY = 0;
        
        sock_gazeY = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_gazeY < 0) {
            perror("socket");
            // return 1;
        }
        addr_gazeY.sin_family = AF_INET;
        addr_gazeY.sin_port = htons(33222);
        addr_gazeY.sin_addr.s_addr = INADDR_ANY;
        if (::bind(sock_gazeY, (struct sockaddr *)&addr_gazeY, sizeof(addr_gazeY)) != 0) {
            perror("bind");
            // return 1;
        }
        if (listen(sock_gazeY, 5) != 0) {
            perror("listen");
            // return 1;
        }
        
        /* UDP transfer */
        UDPSocket sock(servPort);
        char buffer[BUF_LEN];       // Buffer for echo string
        int recvMsgSize;            // Size of received message
        string sourceAddress;       // Address of datagram source
        unsigned short sourcePort;  // Port of datagram source
        
        // clock_t last_cycle = clock();

        while (1) {

            gazeX = eyeGazeX;
            gazeY = eyeGazeY;
            
            try {
                /* Send gaze_x data to jetson */
                len_gazeX = sizeof(client_gazeX);
                ret_gazeX = accept(sock_gazeX, (struct sockaddr *)&client_gazeX, &len_gazeX);
                if (ret_gazeX < 0) {
                    perror("accept");
                    // break;
                }
                if (0 <= gazeX <= 1280) {
                    n_gazeX = write(ret_gazeX, &gazeX, sizeof(gazeX));
                    if (n_gazeX < 1) {
                        perror("write");
                        // break;
                    }
                }
                if(gazeX > 1280) {
                    gazeX = 1280;
                    n_gazeX = write(ret_gazeX, &gazeX, sizeof(gazeX));
                    if (n_gazeX < 1) {
                        perror("write");
                        // break;
                    }
                }
                else if (gazeX < 0) {
                    gazeX = 0;
                    n_gazeX = write(ret_gazeX, &gazeX, sizeof(gazeX));
                    if (n_gazeX < 1) {
                        perror("write");
                        // break;
                    }
                }
                close(ret_gazeX);
            
                /* Send gaze_y data to jetson */
                len_gazeY = sizeof(client_gazeY);
                ret_gazeY = accept(sock_gazeY, (struct sockaddr *)&client_gazeY, &len_gazeY);
                if (ret_gazeY < 0) {
                    perror("accept");
                    // break;
                }
                if (0 <= gazeY <= 720) {
                    n_gazeY = write(ret_gazeY, &gazeY, sizeof(gazeX));
                    if (n_gazeX < 1) {
                        perror("write");
                        // break;
                    }
                }
                if(gazeY > 720) {
                    gazeY = 720;
                    n_gazeY = write(ret_gazeY, &gazeY, sizeof(gazeY));
                    if (n_gazeY < 1) {
                        perror("write");
                        // break;
                    }
                }
                if (gazeY < 0) {
                    gazeY = 0;
                    n_gazeY = write(ret_gazeY, &gazeY, sizeof(gazeY));
                    if (n_gazeX < 1) {
                        perror("write");
                        // break;
                    }
                }
                close(ret_gazeY);
            }
            catch (SocketException & e) {
                cerr << e.what() << endl;
                // exit(1);
            }
            
            cout << "x :" << gazeX << " y :" << gazeY << endl;
            // cout << "x :" << Gaze[0] << " y :" << Gaze[1] << endl;
            
            /* Block until receive message from a client */
            do {
                recvMsgSize = sock.recvFrom(buffer, BUF_LEN, sourceAddress, sourcePort);
            } while (recvMsgSize > sizeof(int));
            int total_pack = ((int * ) buffer)[0];

            // cout << "expecting length of packs:" << total_pack << endl;
            char * longbuf = new char[PACK_SIZE * total_pack];
            for (int i = 0; i < total_pack; i++) {
                recvMsgSize = sock.recvFrom(buffer, BUF_LEN, sourceAddress, sourcePort);
                if (recvMsgSize != PACK_SIZE) {
                    cerr << "Received unexpected size pack:" << recvMsgSize << endl;
                    continue;
                }
                memcpy( & longbuf[i * PACK_SIZE], buffer, PACK_SIZE);
            }

            // cout << "Received packet from " << sourceAddress << ":" << sourcePort << endl;
 
            rawData = Mat(1, PACK_SIZE * total_pack, CV_8UC1, longbuf);
            frame = imdecode(rawData, CV_LOAD_IMAGE_COLOR);
            if (frame.size().width == 0) {
                cerr << "decode failure!" << endl;
                continue;
            }
            //resize(frame, Image, Size(640, 480));
            resize(frame, Image, Size(1280, 720));
            
            // gazeSend();
            circle(Image, cv::Point(gazeX, gazeY), 10, cv::Scalar(0,0,200), 3, 4);
            imshow("recv", Image);
            free(longbuf);
            
            int key = waitKey(10);
            if (key == 'q') {
                break;
            }

            waitKey(1);
            
            /*clock_t next_cycle = clock();
            double duration = (next_cycle - last_cycle) / (double) CLOCKS_PER_SEC;
            cout << "\teffective FPS:" << (1 / duration) << " \tkbps:" << (PACK_SIZE * total_pack / duration / 1024 * 8) << endl;

            cout << next_cycle - last_cycle;
            last_cycle = next_cycle;*/
        }
        close(sock_gazeX);
        close(sock_gazeY);
        
    } catch (SocketException & e) {
        cerr << e.what() << endl;
        // exit(1);
    }

    return 0;
}
