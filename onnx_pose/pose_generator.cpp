#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <memory>
#include <unistd.h>
#include <iostream>
#include <typeinfo>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <filesystem>
#include <csignal>
#include "MPPose.h"
#include "MPPersonDet.h"
#include <opencv2/opencv.hpp>
#include "processFrame.h"
#include  "json.hpp"
const long double _M_PI = 3.141592653589793238L;
using namespace std;
using namespace cv;
using namespace dnn;
namespace fs = std::filesystem;
using json = nlohmann::json;


processFrame* pFrame = nullptr; 


bool sigint=false;
void handle_sigint(int sig) {
    std::cout << "\nCaught signal " << sig << " (SIGINT). Exiting gracefully...\n";
    if (pFrame){
        pFrame->sendExitMessage();
    }
    cv::destroyAllWindows();
    sigint=true; // Close all OpenCV windows
    sleep(2);
    exit(0); // Exit the program
}

void writeToLog(const std::string& message) {
    // Open the file in append mode
    std::ofstream logFile("log.txt", std::ios::app);

    // Check if the file is open
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }

    // Get the current time
    std::time_t now = std::time(nullptr);
    char* dt = std::ctime(&now); // Convert time_t to string

    // Remove the newline character from ctime output
    std::string dateTime(dt);
    dateTime.pop_back();

    // Write the datetime and message to the file
    logFile << dateTime << ": " << message << std::endl;

    // Close the file
    logFile.close();
}


//predict_cam

//predict_video (predict from videos with input directory) --> video_directory, output_images_directory

//show image --> input_imnage_path

//show_video  --> input_video_path
//videos_to_csvs -->video_directory, output_images_directory

int main(int argc, char** argv)
{
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigint);

    writeToLog("in main\n");
 
   // Get the current working directory
        std::filesystem::path cwd = std::filesystem::current_path();

        // Append the file name to the current working directory path
        std::filesystem::path configFile = cwd / "onnx_pose/config.json";

        // Open the configuration file
        std::ifstream file(configFile);

        //std::ifstream file("/home/berke/PAES-QT/onnx_pose/config.json");

        if (!file.is_open()) {
            std::cerr << "Could not open the config file at: " << configFile << std::endl;
            writeToLog("Could not open the config file at: \n");

            return 1;
        }

        // Parse the JSON from the file
        json config;
        file >> config;


    // Access the parameters
    std::string mode = config["mode"];
    std::string input_videos_directory = config["video_directory"];
    std::string output_images_directory = config["output_images_directory"];
    std::string input_video_path = config["input_video_path"];
    std::string input_image_path = config["input_image_path"];
    string person_model_path=config["person_detection_path"];
    string pose_model_path=config["pose_detection_path"];
    bool save_images=config["save_images"];
    int FPS = config["FPS"];
    if (pose_model_path.empty())
    {
        CV_Error(Error::StsError, "Model file " + pose_model_path + " not found");
        cout << "pose model not found\n";
        writeToLog("pose model not found: \n");

        return 0;
    }
    if (person_model_path.empty())
    {
        CV_Error(Error::StsError, "Model file " + pose_model_path + " not found");
        cout << "person model not found\n";
         writeToLog("person model not found: \n");

        return 0;
    }
    
    writeToLog("MODEL IS OKAY\n");

    const int max_cameras = 10;

    /*std::cout << "Checking for available cameras...\n";

    for (int i = 0; i < max_cameras; ++i) {
        cv::VideoCapture cap(i);
        if (cap.isOpened()) {
            std::cout << "Camera " << i << " is available.\n";
            cap.release();  // Release the camera
        } else {
            std::cout << "Camera " << i << " is not available.\n";
        }
    }

    std::cout << "Camera check complete.\n";
    */
    if (mode.compare("show_video")==0 && !sigint){
        cv::VideoCapture cap=cv::VideoCapture(input_video_path); 
        cap.set(cv::CAP_PROP_FPS, 10);
 

        cv::VideoWriter writer; // creating writer

        // Initializing the camera process   
        
        // imgpro.connect_server();
        processFrame frame_processor(person_model_path,pose_model_path);
         pFrame = &frame_processor; 
        while(cap.isOpened() && !sigint) 
        {
            cv::Mat frame;
            if (cap.isOpened()) 
            {
                cap.read(frame); // open camera and read the images from camera
            } 
            if (frame.empty()) {cout<<"image is empty"<<endl; }// check image
            


            frame_processor.Process(frame);
    
       
        }
        cap.release();

    }
    else if(mode.compare("show_image")==0 &&!sigint){
        processFrame frame_processor(person_model_path,pose_model_path);
         pFrame = &frame_processor; 
        cv::Mat image = imread(input_image_path, 
                       cv::IMREAD_COLOR); 
        frame_processor.Process(image);
        
    }
    else if(mode.compare("predict_video")==0 && !sigint){
        fs::path directoryPath =input_videos_directory;
        std::string outputDir = output_images_directory;
        if (!fs::exists(directoryPath)) {
            std::cerr << "Error: Directory '" << directoryPath << "' does not exist." << std::endl;
            return -1;
        }

        // Create the output directory if it doesn't exist
        if (!fs::exists(outputDir) && save_images) {
            fs::create_directory(outputDir);
        }

        // Initialize parameters for ImageProcessor
        bool connect = false;
        std::string mode = "send";
        processFrame frame_processor(person_model_path,pose_model_path);
          pFrame = &frame_processor; 
        // Initializing the camera process   
        frame_processor.connect_server();
       
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry) && (fs::path(entry).extension() == ".mp4"||fs::path(entry).extension() == ".MOV")) {
                // Create a subdirectory for each video
                std::string videoName = fs::path(entry).stem().string();
                std::string videoOutputDir = outputDir + "/" + videoName;
                

                // Set output files for each video
                std::string txtFileName = videoOutputDir + "/output.txt";
                std::string csvFileName = videoOutputDir + "/output.csv";
                frame_processor.set_engine(txtFileName, csvFileName, connect, mode);

                // Open the video file
                cv::VideoCapture cap(entry.path().string());
                frame_processor.set_index(0);
                cv::Mat image;
                std::cout << "Processing video: " << entry.path().string() << std::endl;
                while (cap.isOpened() && !sigint) {
                    cap.read(image);
                    if (image.empty()) {
                        break;
                    }
                    frame_processor.Process(image);

                    // Save the processed frame
                    std::string filenameStr = videoOutputDir + "/processed_" + std::to_string(frame_processor.get_index()) + ".jpg";
                    fs::path filename(filenameStr);
                    if (save_images)
                        {
                        if (!cv::imwrite(filenameStr, image)) {
                            std::cerr << "Error saving image: " << filename << std::endl;
                        }
                    }
                    frame_processor.set_index(frame_processor.get_index() + 1);
                }
                if(sigint){
                    cap.release();
                    break;
                }
            }
        }
    }
    else if(mode.compare("predict_cam")==0){
       
        // Initialize parameters for ProcessFrame
        bool connect = false;
        std::string mode = "send";
        processFrame frame_processor(person_model_path,pose_model_path);
        pFrame = &frame_processor; 
        writeToLog("Before connect server\n");

        frame_processor.connect_server();
        writeToLog("after connect server\n");


        std::string videoOutputDir = output_images_directory + "/" + "cam_predict";
        if (!fs::exists(videoOutputDir) && save_images) {
            fs::create_directory(videoOutputDir);
        }

        // Set output files for each video
        std::string txtFileName = videoOutputDir + "/output.txt";
        std::string csvFileName = videoOutputDir + "/output.csv";
        frame_processor.set_engine(txtFileName, csvFileName, connect, mode);

        // Open the video file "/dev/video2"
        cv::VideoCapture cap("/dev/video0");
        cap.set(cv::CAP_PROP_FPS, FPS);
        writeToLog("After camera is set\n");

        frame_processor.set_index(0);
        cv::Mat image;
        while (cap.isOpened() && !sigint) 
        {
            cap.read(image);
            if (image.empty()) {
                break;
            }

            frame_processor.Process(image);

            if (save_images){
                std::string filenameStr = videoOutputDir + "/processed_" + std::to_string(frame_processor.get_index()) + ".jpg";
                fs::path filename(filenameStr);
                if (!cv::imwrite(filenameStr, image)) {
                    std::cerr << "Error saving image: " << filename << std::endl;
                }
            }

            frame_processor.set_index(frame_processor.get_index() + 1);
        }

        cap.release();
        
        
    }
    else if(mode.compare("videos_to_csvs")==0){
        fs::path directoryPath =input_videos_directory;
        std::string outputDir = output_images_directory;
        if (!fs::exists(directoryPath)) {
            std::cerr << "Error: Directory '" << directoryPath << "' does not exist." << std::endl;
            return -1;
        }

        // Create the output directory if it doesn't exist
        if (!fs::exists(outputDir) &&save_images) {
            fs::create_directory(outputDir);
        }

        // Initialize parameters for ImageProcessor
        bool connect = false;
        std::string mode = "database";
        processFrame frame_processor(person_model_path,pose_model_path);
        pFrame = &frame_processor; 
        // Initializing the camera process   
        
       
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry) && (fs::path(entry).extension() == ".mp4"||fs::path(entry).extension() == ".MOV")) {
                // Create a subdirectory for each video
                std::string videoName = fs::path(entry).stem().string();
                std::string videoOutputDir = outputDir + "/" + videoName;
                if (!fs::exists(videoOutputDir)) {
                    fs::create_directory(videoOutputDir);
                }

                // Set output files for each video
                std::string txtFileName = videoOutputDir + "/output.txt";
                std::string csvFileName = videoOutputDir + "/output.csv";
                frame_processor.set_engine(txtFileName, csvFileName, connect, mode);

                // Open the video file
                cv::VideoCapture cap(entry.path().string());
                frame_processor.set_index(0);
                cv::Mat image;
                std::cout << "Processing video: " << entry.path().string() << std::endl;
                while (cap.isOpened()) {
                    cap.read(image);
                    if (image.empty()) {
                        break;
                    }
                    frame_processor.Process(image);

                    // Save the processed frame
                    std::string filenameStr = videoOutputDir + "/processed_" + std::to_string(frame_processor.get_index()) + ".jpg";
                    fs::path filename(filenameStr);
                    if (save_images){
                        if (!cv::imwrite(filenameStr, image)) {
                            std::cerr << "Error saving image: " << filename << std::endl;
                        }
                    }
                    frame_processor.set_index(frame_processor.get_index() + 1);
                }
            }
        }
    }
   
    else{
        cout<<"Modes :\n"<<"predict_cam\n"<<"predict_video --- predict from videos with input directory\n"<<"show image\n"<<"show_video\nvideos_to_csvs";
    }
   

    return 0;
}























































