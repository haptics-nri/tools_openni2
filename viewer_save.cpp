#include <viewer.h>

/**
  * Creates the timestamped directory structure to save the data.
  */
void Viewer::create_dir(){
    // get timestamp
    std::string folder;
    std::stringstream strstream;
    int ret = -1;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [20];

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,20,"%Y.%m.%d-%H.%M.%S",timeinfo);
    strstream << buffer;
    strstream >> folder;
    // create the directory
    ret = mkdir(folder.c_str(), 0775);


    // if successfull write the name in the variable
    if (ret == 0){
        std::cout << "The folder " << folder << " was created." << std::endl;
        folder_name = folder;

        // create subfolders
        ret = mkdir((folder + "//rgb").c_str(), 0775);
        if (ret == 0){
            std::cout << "The folder " << (folder + "/rgb") << " was created." << std::endl;
        } else {
            std::cout << "The folder " << (folder + "/rgb") << " could not be created and the program will exit." << std::endl;
            exit(0);
        }
        ret = mkdir((folder + "//depth").c_str(), 0775);
        if (ret == 0){
            std::cout << "The folder " << (folder + "/depth") << " was created." << std::endl;
        } else {
            std::cout << "The folder " << (folder + "/depth") << " could not be created and the program will exit." << std::endl;
            exit(0);
        }
        ret = mkdir((folder + "//pcl").c_str(), 0775);
        if (ret == 0){
            std::cout << "The folder " << (folder + "/pcl") << " was created." << std::endl;
        } else {
            std::cout << "The folder " << (folder + "/pcl") << " could not be created and the program will exit." << std::endl;
            exit(0);
        }
        ret = mkdir((folder + "//depth_viz").c_str(), 0775);
        if (ret == 0){
            std::cout << "The folder " << (folder + "/depth_viz") << " was created." << std::endl;
        } else {
            std::cout << "The folder " << (folder + "/depth_viz") << " could not be created and the program will exit." << std::endl;
            exit(0);
        }
        ret = mkdir((folder + "//rgbd").c_str(), 0775);
        if (ret == 0){
            std::cout << "The folder " << (folder + "/rgbd") << " was created." << std::endl;
        } else {
            std::cout << "The folder " << (folder + "/rgbd") << " could not be created and the program will exit." << std::endl;
            exit(0);
        }
    }else {
        std::cout << "The folder " << (folder) << " could not be created and the program will exit." << std::endl;
        exit(0);
    }
}


void Viewer::saveToDisk(){
    for(int i = 0; i < (int)point_clouds.size() ; i++){
        std::cout << "Saving frame " << i << std::endl;
        // generate filenames
        std::ostringstream     ss, srgb;
        ss << std::setfill('0') << std::setw(8);
        ss << i+1 ;
        std::string fileNamePcl = folder_name + "/pcl" + "/" + ss.str() + ".pcd";
        std::string fileNameRGB = folder_name + "/rgb" + "/" + ss.str() + ".png";
        std::string fileNameRGBD = folder_name + "/rgbd" + "/" + ss.str() + ".png";
        std::string fileNameDepthS = folder_name + "/depth_viz" + "/" + ss.str() + ".png";
        std::string fileNameDepthI = folder_name + "/depth" + "/" + ss.str() + ".yml";

        // save pcl
        pcl::io::savePCDFile( fileNamePcl, point_clouds[i], false );

        // save RGB, RGBD and Depths images
        cv::imwrite(fileNameRGB, rgb_images[i]);
        cv::imwrite(fileNameRGBD, rgbd_images[i]);
        cv::imwrite(fileNameDepthS, depth_show[i]);

        // save the depth info

        cv::FileStorage fs(fileNameDepthI, cv::FileStorage::WRITE);
        fs << "depth" << depth_viz[i];
        fs.release();

    }
}